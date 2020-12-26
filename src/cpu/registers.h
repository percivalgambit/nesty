#ifndef CPU_REGISTERS_H_
#define CPU_REGISTERS_H_

#include <cstdint>

namespace nesty {

struct ProcessorStatus {
  uint8_t carry : 1;
  uint8_t zero : 1;
  uint8_t interrupt_disable : 1;
  uint8_t decimal_mode : 1;
  uint8_t break_command : 1;
  uint8_t overflow : 1;
  uint8_t : 1;
  uint8_t negative : 1;
};

struct Registers {
  uint16_t pc;
  uint8_t sp;
  uint8_t acc;
  uint8_t x;
  uint8_t y;
  union {
    uint8_t status_byte;
    ProcessorStatus status;
  };
};

}  // namespace nesty

#endif  // CPU_REGISTERS_H_
