#include "util/bit_manip.h"

#include <cstdint>

uint16_t GetUint16(const uint8_t* ptr) {
  uint16_t lo_byte = ptr[0];
  uint16_t hi_byte = ptr[1];
  return lo_byte | static_cast<uint16_t>(hi_byte << 8);
}
