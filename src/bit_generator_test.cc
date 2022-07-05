#include "bitgen/bit_generator.h"

#include <cmath>
#include <bitset>

#include <gtest/gtest.h>

namespace bitgen {
namespace {

template <size_t N, bool (BitGenerator::*F)()>
std::bitset<N> *GenerateSet() {
  static BitGenerator kBitGenerator(0.927725, 0.437884);

  // FIXME(velvetrage): Find a better solution.
  std::bitset<N> *set = new std::bitset<N>();
  for (size_t i = 0; i < set->size(); ++i) {
    (*set)[i] = (kBitGenerator.*F)();
  }
  return set;
}

class BitGeneratorFixture
    : public testing::TestWithParam<std::bitset<0x1000000> *> {};

// The purpose of the frequency test is to determine whether the number of
// ones and zeros in a sequence are approximately the same as would be
// expected for a truly random sequence. The test assesses the closeness of
// the fraction of ones to 1/2, that is, the number of ones and zeroes in a
// sequence should be about the same.
TEST_P(BitGeneratorFixture, FrequencyTest) {
  const auto *set = GetParam();
  const size_t size = set->size();
  const size_t ones = set->count();

  const int n = 2 * ones - size;
  const double s = std::abs(n) / std::sqrt(size);
  const double p = std::erfc(s / M_SQRT2);

  EXPECT_GE(p, 0.01);
}

// The purpose of the runs test is to determine whether the number of runs of
// ones and zeros of various lengths is as expected for a random sequence. In
// particular, this test determines whether the oscillation between such zeros
// and ones is too fast or too slow.
TEST_P(BitGeneratorFixture, RunsTest) {
  const auto *set = GetParam();
  const size_t size = set->size();
  const size_t ones = set->count();

  size_t v = 1;
  for (size_t i = 1; i < size; ++i) {
    v += (*set)[i] != (*set)[i - 1];
  }

  const double f = static_cast<double>(ones) / size;
  const double p = std::erfc(std::abs(v - 2.0 * size * f * (1.0 - f)) /
                             (2.0 * std::sqrt(2.0 * size) * f * (1.0 - f)));

  EXPECT_GE(p, 0.01);
}

const char *const kSetTypes[] = {"Regular", "Neumann", "Xor"};

INSTANTIATE_TEST_SUITE_P(
    BitGeneratorTests, BitGeneratorFixture,
    testing::Values(GenerateSet<0x1000000, &BitGenerator::Next>(),
                    GenerateSet<0x1000000, &BitGenerator::Neumann>(),
                    GenerateSet<0x1000000, &BitGenerator::Xor>()),
    [](const testing::TestParamInfo<BitGeneratorFixture::ParamType> &info) {
      return kSetTypes[info.index];
    });

}  // namespace
}  // namespace bitgen
