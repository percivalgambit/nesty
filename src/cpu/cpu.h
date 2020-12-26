#ifndef CPU_CPU_H_
#define CPU_CPU_H_

#include <cstdint>

#include "cpu/instruction.h"
#include "cpu/memory.h"
#include "cpu/registers.h"

namespace nesty {

class Cpu {
 public:
 private:
  Instruction DecodeInsruction();
  void ExecuteInstruction(const Instruction& instruction);

  uint8_t* GetOperand(const AddressingMode& addressingMode);

  uint8_t GetByteAndAdvancePc();
  uint8_t* GetBytePointerAndAdvancePc();
  Address GetAddressAndAdvancePc();

  void PushStack(const uint8_t value);
  uint8_t PopStack();

  void SetDefaultFlags(const uint8_t value);

  void Adc(const uint8_t operand);

  Registers regs_;
  Memory mem_;
};

}  // namespace nesty

#endif  // CPU_CPU_H_
