#include "cpu/memory.h"

#include <cstdint>

namespace nesty {

uint8_t &Memory::operator[](const Address address) {
  return mem_[address.value()];
}
const uint8_t &Memory::operator[](const Address address) const {
  return mem_[address.value()];
}

}  // namespace nesty
