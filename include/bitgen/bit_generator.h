#ifndef BITGEN_BIT_GENERATOR_H__
#define BITGEN_BIT_GENERATOR_H__

namespace bitgen {

class BitGenerator {
 public:
  BitGenerator(double x, double y) noexcept : x_(x), y_(y) {}

  // TODO(velvetrage): Read `A novel pseudorandom number generator based on
  // pseudorandomly enhanced logistic map` (DOI: 10.1007/s11071-016-3051-3)
  bool Next() noexcept;

  // John von Neumann randomness extractor. Takes two bits from the input; if
  // they match, no output is generated; if the bits differ, the value of the
  // first bit is returned.
  //
  // See https://en.wikipedia.org/wiki/Bernoulli_process#Randomness_extraction
  // for more information.
  bool Neumann() noexcept;

  // Takes two bits from the input and XORs them. A slightly faster alternative
  // to the von Neumann extractor, also slightly more biased and therefore less
  // entropy per bit.
  bool Xor() noexcept;

 private:
  double x_;
  double y_;
};

}  // namespace bitgen

#endif  // BITGEN_BIT_GENERATOR_H__
