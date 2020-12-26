#ifndef CPU_MEMORY_H_
#define CPU_MEMORY_H_

#include "util/strong_int.h"

#include <array>
#include <cstdint>
#include <limits>

namespace nesty {

DEFINE_STRONG_INT_TYPE(Address, uint16_t);

class Memory {
 public:
  uint8_t &operator[](const Address address);
  const uint8_t &operator[](const Address address) const;

 private:
  std::array<uint8_t, std::numeric_limits<uint16_t>::max()> mem_;
};

}  // namespace nesty

#endif  // CPU_MEMORY_H_
