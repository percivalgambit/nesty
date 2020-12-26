#include "cpu/instruction.h"

#include "util/logging.h"

#include <cstdint>

namespace nesty {

InstructionInfo GetInstructionInfo(uint8_t opcode) {
  switch (opcode) {
    case 0x00:
      return {Opcode::BRK, AddressingMode::kImplicit};
    case 0x01:
      return {Opcode::ORA, AddressingMode::kIndexedIndirect};
    case 0x05:
      return {Opcode::ORA, AddressingMode::kZeroPage};
    case 0x06:
      return {Opcode::ASL, AddressingMode::kZeroPage};
    case 0x08:
      return {Opcode::PHP, AddressingMode::kImplicit};
    case 0x09:
      return {Opcode::ORA, AddressingMode::kImmediate};
    case 0x0A:
      return {Opcode::ASL, AddressingMode::kAccumulator};
    case 0x0D:
      return {Opcode::ORA, AddressingMode::kAbsolute};
    case 0x0E:
      return {Opcode::ASL, AddressingMode::kAbsolute};
    case 0x10:
      return {Opcode::BPL, AddressingMode::kRelative};
    case 0x11:
      return {Opcode::ORA, AddressingMode::kIndirectIndexed};
    case 0x15:
      return {Opcode::ORA, AddressingMode::kZeroPageX};
    case 0x16:
      return {Opcode::ASL, AddressingMode::kZeroPageX};
    case 0x18:
      return {Opcode::CLC, AddressingMode::kImplicit};
    case 0x19:
      return {Opcode::ORA, AddressingMode::kAbsoluteY};
    case 0x1D:
      return {Opcode::ORA, AddressingMode::kAbsoluteX};
    case 0x1E:
      return {Opcode::ASL, AddressingMode::kAbsoluteX};
    case 0x20:
      return {Opcode::JSR, AddressingMode::kAbsolute};
    case 0x21:
      return {Opcode::AND, AddressingMode::kIndexedIndirect};
    case 0x24:
      return {Opcode::BIT, AddressingMode::kZeroPage};
    case 0x25:
      return {Opcode::AND, AddressingMode::kZeroPage};
    case 0x26:
      return {Opcode::ROL, AddressingMode::kZeroPage};
    case 0x28:
      return {Opcode::PLP, AddressingMode::kImplicit};
    case 0x29:
      return {Opcode::AND, AddressingMode::kImmediate};
    case 0x2A:
      return {Opcode::ROL, AddressingMode::kAccumulator};
    case 0x2C:
      return {Opcode::BIT, AddressingMode::kAbsolute};
    case 0x2D:
      return {Opcode::AND, AddressingMode::kAbsolute};
    case 0x2E:
      return {Opcode::ROL, AddressingMode::kAbsolute};
    case 0x30:
      return {Opcode::BMI, AddressingMode::kRelative};
    case 0x31:
      return {Opcode::AND, AddressingMode::kIndirectIndexed};
    case 0x35:
      return {Opcode::AND, AddressingMode::kZeroPageX};
    case 0x36:
      return {Opcode::ROL, AddressingMode::kZeroPageX};
    case 0x38:
      return {Opcode::SEC, AddressingMode::kImplicit};
    case 0x39:
      return {Opcode::AND, AddressingMode::kAbsoluteY};
    case 0x3D:
      return {Opcode::AND, AddressingMode::kAbsoluteX};
    case 0x3E:
      return {Opcode::ROL, AddressingMode::kAbsoluteX};
    case 0x40:
      return {Opcode::RTI, AddressingMode::kImplicit};
    case 0x41:
      return {Opcode::EOR, AddressingMode::kIndexedIndirect};
    case 0x45:
      return {Opcode::EOR, AddressingMode::kZeroPage};
    case 0x46:
      return {Opcode::LSR, AddressingMode::kZeroPage};
    case 0x48:
      return {Opcode::PHA, AddressingMode::kImplicit};
    case 0x49:
      return {Opcode::EOR, AddressingMode::kImmediate};
    case 0x4A:
      return {Opcode::LSR, AddressingMode::kAccumulator};
    case 0x4C:
      return {Opcode::JMP, AddressingMode::kAbsolute};
    case 0x4D:
      return {Opcode::EOR, AddressingMode::kAbsolute};
    case 0x4E:
      return {Opcode::LSR, AddressingMode::kAbsolute};
    case 0x50:
      return {Opcode::BVC, AddressingMode::kRelative};
    case 0x51:
      return {Opcode::EOR, AddressingMode::kIndirectIndexed};
    case 0x55:
      return {Opcode::EOR, AddressingMode::kZeroPageX};
    case 0x56:
      return {Opcode::LSR, AddressingMode::kZeroPageX};
    case 0x58:
      return {Opcode::CLI, AddressingMode::kImplicit};
    case 0x59:
      return {Opcode::EOR, AddressingMode::kAbsoluteY};
    case 0x5D:
      return {Opcode::EOR, AddressingMode::kAbsoluteX};
    case 0x5E:
      return {Opcode::LSR, AddressingMode::kAbsoluteX};
    case 0x60:
      return {Opcode::RTS, AddressingMode::kImplicit};
    case 0x61:
      return {Opcode::ADC, AddressingMode::kIndexedIndirect};
    case 0x65:
      return {Opcode::ADC, AddressingMode::kZeroPage};
    case 0x66:
      return {Opcode::ROR, AddressingMode::kZeroPage};
    case 0x68:
      return {Opcode::PLA, AddressingMode::kImplicit};
    case 0x69:
      return {Opcode::ADC, AddressingMode::kImmediate};
    case 0x6A:
      return {Opcode::ROR, AddressingMode::kAccumulator};
    case 0x6C:
      return {Opcode::JMP, AddressingMode::kIndirect};
    case 0x6D:
      return {Opcode::ADC, AddressingMode::kAbsolute};
    case 0x6E:
      return {Opcode::ROR, AddressingMode::kAbsolute};
    case 0x70:
      return {Opcode::BVS, AddressingMode::kRelative};
    case 0x71:
      return {Opcode::ADC, AddressingMode::kIndirectIndexed};
    case 0x75:
      return {Opcode::ADC, AddressingMode::kZeroPageX};
    case 0x76:
      return {Opcode::ROR, AddressingMode::kZeroPageX};
    case 0x78:
      return {Opcode::SEI, AddressingMode::kImplicit};
    case 0x79:
      return {Opcode::ADC, AddressingMode::kAbsoluteY};
    case 0x7D:
      return {Opcode::ADC, AddressingMode::kAbsoluteX};
    case 0x7E:
      return {Opcode::ROR, AddressingMode::kAbsoluteX};
    case 0x81:
      return {Opcode::STA, AddressingMode::kIndexedIndirect};
    case 0x84:
      return {Opcode::STY, AddressingMode::kZeroPage};
    case 0x85:
      return {Opcode::STA, AddressingMode::kZeroPage};
    case 0x86:
      return {Opcode::STX, AddressingMode::kZeroPage};
    case 0x88:
      return {Opcode::DEY, AddressingMode::kImplicit};
    case 0x8A:
      return {Opcode::TXA, AddressingMode::kImplicit};
    case 0x8C:
      return {Opcode::STY, AddressingMode::kAbsolute};
    case 0x8D:
      return {Opcode::STA, AddressingMode::kAbsolute};
    case 0x8E:
      return {Opcode::STX, AddressingMode::kAbsolute};
    case 0x90:
      return {Opcode::BCC, AddressingMode::kRelative};
    case 0x91:
      return {Opcode::STA, AddressingMode::kIndirectIndexed};
    case 0x94:
      return {Opcode::STY, AddressingMode::kZeroPageX};
    case 0x95:
      return {Opcode::STA, AddressingMode::kZeroPageX};
    case 0x96:
      return {Opcode::STX, AddressingMode::kZeroPageX};
    case 0x98:
      return {Opcode::TYA, AddressingMode::kImplicit};
    case 0x99:
      return {Opcode::STA, AddressingMode::kAbsoluteY};
    case 0x9A:
      return {Opcode::TXS, AddressingMode::kImplicit};
    case 0x9D:
      return {Opcode::STA, AddressingMode::kAbsoluteX};
    case 0xA0:
      return {Opcode::LDY, AddressingMode::kImmediate};
    case 0xA1:
      return {Opcode::LDA, AddressingMode::kIndexedIndirect};
    case 0xA2:
      return {Opcode::LDX, AddressingMode::kImmediate};
    case 0xA4:
      return {Opcode::LDY, AddressingMode::kZeroPage};
    case 0xA5:
      return {Opcode::LDA, AddressingMode::kZeroPage};
    case 0xA6:
      return {Opcode::LDX, AddressingMode::kZeroPage};
    case 0xA8:
      return {Opcode::TAY, AddressingMode::kImplicit};
    case 0xA9:
      return {Opcode::LDA, AddressingMode::kImmediate};
    case 0xAA:
      return {Opcode::TAX, AddressingMode::kImplicit};
    case 0xAC:
      return {Opcode::LDY, AddressingMode::kAbsolute};
    case 0xAD:
      return {Opcode::LDA, AddressingMode::kAbsolute};
    case 0xAE:
      return {Opcode::LDX, AddressingMode::kAbsolute};
    case 0xB0:
      return {Opcode::BCS, AddressingMode::kRelative};
    case 0xB1:
      return {Opcode::LDA, AddressingMode::kIndirectIndexed};
    case 0xB4:
      return {Opcode::LDY, AddressingMode::kZeroPageX};
    case 0xB5:
      return {Opcode::LDA, AddressingMode::kZeroPageX};
    case 0xB6:
      return {Opcode::LDX, AddressingMode::kZeroPageX};
    case 0xB8:
      return {Opcode::CLV, AddressingMode::kImplicit};
    case 0xB9:
      return {Opcode::LDA, AddressingMode::kAbsoluteY};
    case 0xBA:
      return {Opcode::TSX, AddressingMode::kImplicit};
    case 0xBC:
      return {Opcode::LDY, AddressingMode::kAbsoluteX};
    case 0xBD:
      return {Opcode::LDA, AddressingMode::kAbsoluteX};
    case 0xBE:
      return {Opcode::LDX, AddressingMode::kAbsoluteX};
    case 0xC0:
      return {Opcode::CPY, AddressingMode::kImmediate};
    case 0xC1:
      return {Opcode::CMP, AddressingMode::kIndexedIndirect};
    case 0xC4:
      return {Opcode::CPY, AddressingMode::kZeroPage};
    case 0xC5:
      return {Opcode::CMP, AddressingMode::kZeroPage};
    case 0xC6:
      return {Opcode::DEC, AddressingMode::kZeroPage};
    case 0xC8:
      return {Opcode::INY, AddressingMode::kImplicit};
    case 0xC9:
      return {Opcode::CMP, AddressingMode::kImmediate};
    case 0xCA:
      return {Opcode::DEX, AddressingMode::kImplicit};
    case 0xCC:
      return {Opcode::CPY, AddressingMode::kAbsolute};
    case 0xCD:
      return {Opcode::CMP, AddressingMode::kAbsolute};
    case 0xCE:
      return {Opcode::DEC, AddressingMode::kAbsolute};
    case 0xD0:
      return {Opcode::BNE, AddressingMode::kRelative};
    case 0xD1:
      return {Opcode::CMP, AddressingMode::kIndirectIndexed};
    case 0xD5:
      return {Opcode::CMP, AddressingMode::kZeroPageX};
    case 0xD6:
      return {Opcode::DEC, AddressingMode::kZeroPageX};
    case 0xD8:
      return {Opcode::CLD, AddressingMode::kImplicit};
    case 0xD9:
      return {Opcode::CMP, AddressingMode::kAbsoluteY};
    case 0xDD:
      return {Opcode::CMP, AddressingMode::kAbsoluteX};
    case 0xDE:
      return {Opcode::DEC, AddressingMode::kAbsoluteX};
    case 0xE0:
      return {Opcode::CPX, AddressingMode::kImmediate};
    case 0xE1:
      return {Opcode::SBC, AddressingMode::kIndexedIndirect};
    case 0xE4:
      return {Opcode::CPX, AddressingMode::kZeroPage};
    case 0xE5:
      return {Opcode::SBC, AddressingMode::kZeroPage};
    case 0xE6:
      return {Opcode::INC, AddressingMode::kZeroPage};
    case 0xE8:
      return {Opcode::INX, AddressingMode::kImplicit};
    case 0xE9:
      return {Opcode::SBC, AddressingMode::kImmediate};
    case 0xEA:
      return {Opcode::NOP, AddressingMode::kImplicit};
    case 0xEC:
      return {Opcode::CPX, AddressingMode::kAbsolute};
    case 0xED:
      return {Opcode::SBC, AddressingMode::kAbsolute};
    case 0xEE:
      return {Opcode::INC, AddressingMode::kAbsolute};
    case 0xF0:
      return {Opcode::BEQ, AddressingMode::kRelative};
    case 0xF1:
      return {Opcode::SBC, AddressingMode::kIndirectIndexed};
    case 0xF5:
      return {Opcode::SBC, AddressingMode::kZeroPageX};
    case 0xF6:
      return {Opcode::INC, AddressingMode::kZeroPageX};
    case 0xF8:
      return {Opcode::SED, AddressingMode::kImplicit};
    case 0xF9:
      return {Opcode::SBC, AddressingMode::kAbsoluteY};
    case 0xFD:
      return {Opcode::SBC, AddressingMode::kAbsoluteX};
    case 0xFE:
      return {Opcode::INC, AddressingMode::kAbsoluteX};
    default:
      FATAL("Unknown opcode");
  }
}

}  // namespace nesty
