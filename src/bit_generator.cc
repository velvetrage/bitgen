#include "bitgen/bit_generator.h"

namespace bitgen {

bool BitGenerator::Next() noexcept {
  x_ = 4.0 * x_ * (1.0 - x_);
  y_ = 4.0 * y_ * (1.0 - y_);
  return x_ > y_;
}

bool BitGenerator::Neumann() noexcept {
  bool x;
  while ((x = Next()) == Next()) continue;
  return x;
}

bool BitGenerator::Xor() noexcept { return Next() ^ Next(); }

}  // namespace bitgen
