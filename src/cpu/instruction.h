#ifndef CPU_INSTRUCTION_H_
#define CPU_INSTRUCTION_H_

#include <cstdint>

#include "cpu/memory.h"

namespace nesty {

enum class Opcode {
  LDA,  // Load Accumulator
  LDX,  // Load X Register
  LDY,  // Load Y Register
  STA,  // Store Accumulator
  STX,  // Store X Register
  STY,  // Store Y Register
  TAX,  // Transfer accumulator to X
  TAY,  // Transfer accumulator to Y
  TXA,  // Transfer X to accumulator
  TYA,  // Transfer Y to accumulator
  TSX,  // Transfer stack pointer to X
  TXS,  // Transfer X to stack pointer
  PHA,  // Push accumulator on stack
  PHP,  // Push processor status on stack
  PLA,  // Pull accumulator from stack
  PLP,  // Pull processor status from stack
  AND,  // Logical AND
  EOR,  // Exclusive OR
  ORA,  // Logical inclusive OR
  BIT,  // Bit test
  ADC,  // Add with carry
  SBC,  // Subtrack with carry
  CMP,  // Compare accumulator
  CPX,  // Compare X register
  CPY,  // Compare Y register
  INC,  // Increment a memory location
  INX,  // Increment the X register
  INY,  // Increment the Y register
  DEC,  // Decrement a memory location
  DEX,  // Decrement the X register
  DEY,  // Decrement the Y register
  ASL,  // Arithmetic shift left
  LSR,  // Logical shift right
  ROL,  // Rotate left
  ROR,  // Rotate right
  JMP,  // Jump to another location
  JSR,  // Jump to a subroutine
  RTS,  // Return from subroutine
  BCC,  // Branch if carry flag clear
  BCS,  // Branch if carry flag set
  BEQ,  // Branch if zero flag set
  BMI,  // Branch if negative flag set
  BNE,  // Branch if zero flag clear
  BPL,  // Branch if negative flag clear
  BVC,  // Branch if overflow flag clear
  BVS,  // Branch if overflow flag set
  CLC,  // Clear carry flag
  CLD,  // Clear decimal mode flag
  CLI,  // Clear interrupt disable flag
  CLV,  // Clear overflow flag
  SEC,  // Set carry flag
  SED,  // Set decimal mode flag
  SEI,  // Set interrupt disable flag
  BRK,  // Force an interrupt
  NOP,  // No operation
  RTI,  // Return from interrupt
};

enum class AddressingMode {
  kImplicit,
  kAccumulator,
  kImmediate,
  kZeroPage,
  kZeroPageX,
  kZeroPageY,
  kRelative,
  kAbsolute,
  kAbsoluteX,
  kAbsoluteY,
  kIndirect,
  kIndexedIndirect,
  kIndirectIndexed,
};

struct InstructionInfo {
  Opcode opcode;
  AddressingMode addressing_mode;
};

struct Instruction {
  Instruction(const Opcode opcode, uint8_t* operand)
      : opcode(opcode), operand(operand) {}

  Opcode opcode;
  uint8_t* operand;
};

InstructionInfo GetInstructionInfo(const uint8_t operand);

}  // namespace nesty

#endif  // CPU_INSTRUCTION_H_
