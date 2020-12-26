#include "cpu/cpu.h"

#include <cassert>
#include <cstdint>

#include "cpu/instruction.h"
#include "cpu/memory.h"
#include "util/bit_manip.h"
#include "util/logging.h"

namespace nesty {

constexpr uint16_t kStackPage = 0x0100;
constexpr uint16_t kInterruptPage = 0xFFFE;

Instruction Cpu::DecodeInsruction() {
  const uint8_t header = mem_[Address(regs_.pc++)];
  const InstructionInfo& info = GetInstructionInfo(header);
  uint8_t* operand = GetOperand(info.addressing_mode);

  return Instruction(info.opcode, operand);
}

void Cpu::ExecuteInstruction(const Instruction& instruction) {
  switch (instruction.opcode) {
    case Opcode::LDA:
      assert(instruction.operand != nullptr);
      regs_.acc = *instruction.operand;
      SetDefaultFlags(regs_.acc);
      break;
    case Opcode::LDX:
      assert(instruction.operand != nullptr);
      regs_.x = *instruction.operand;
      SetDefaultFlags(regs_.x);
      break;
    case Opcode::LDY:
      assert(instruction.operand != nullptr);
      regs_.y = *instruction.operand;
      SetDefaultFlags(regs_.y);
      break;
    case Opcode::STA:
      assert(instruction.operand != nullptr);
      *instruction.operand = regs_.acc;
      break;
    case Opcode::STX:
      assert(instruction.operand != nullptr);
      *instruction.operand = regs_.x;
      break;
    case Opcode::STY:
      assert(instruction.operand != nullptr);
      *instruction.operand = regs_.y;
      break;
    case Opcode::TAX:
      regs_.x = regs_.acc;
      SetDefaultFlags(regs_.x);
      break;
    case Opcode::TAY:
      regs_.y = regs_.acc;
      SetDefaultFlags(regs_.y);
      break;
    case Opcode::TXA:
      regs_.acc = regs_.x;
      SetDefaultFlags(regs_.acc);
      break;
    case Opcode::TYA:
      regs_.acc = regs_.y;
      SetDefaultFlags(regs_.acc);
      break;
    case Opcode::TSX:
      regs_.x = regs_.sp;
      SetDefaultFlags(regs_.x);
      break;
    case Opcode::TXS:
      regs_.sp = regs_.x;
      break;
    case Opcode::PHA:
      PushStack(regs_.acc);
      break;
    case Opcode::PHP:
      PushStack(regs_.status_byte);
      break;
    case Opcode::PLA:
      regs_.acc = PopStack();
      SetDefaultFlags(regs_.acc);
      break;
    case Opcode::PLP:
      regs_.status_byte = PopStack();
      break;
    case Opcode::AND:
      assert(instruction.operand != nullptr);
      regs_.acc &= *instruction.operand;
      SetDefaultFlags(regs_.acc);
      break;
    case Opcode::EOR:
      assert(instruction.operand != nullptr);
      regs_.acc ^= *instruction.operand;
      SetDefaultFlags(regs_.acc);
      break;
    case Opcode::ORA:
      assert(instruction.operand != nullptr);
      regs_.acc |= *instruction.operand;
      SetDefaultFlags(regs_.acc);
      break;
    case Opcode::BIT: {
      assert(instruction.operand != nullptr);
      const uint8_t test = regs_.acc & *instruction.operand;
      SetDefaultFlags(test);
      regs_.status.overflow = !!(test & 0b01000000);
      break;
    }
    case Opcode::ADC: {
      assert(instruction.operand != nullptr);
      Adc(*instruction.operand);
      break;
    }
    case Opcode::SBC:
      assert(instruction.operand != nullptr);
      Adc(~*instruction.operand);
      break;
    case Opcode::CMP:
      assert(instruction.operand != nullptr);
      SetDefaultFlags(regs_.acc - *instruction.operand);
      regs_.status.carry = regs_.acc >= *instruction.operand;
      break;
    case Opcode::CPX:
      assert(instruction.operand != nullptr);
      SetDefaultFlags(regs_.x - *instruction.operand);
      regs_.status.carry = regs_.x >= *instruction.operand;
      break;
    case Opcode::CPY:
      assert(instruction.operand != nullptr);
      SetDefaultFlags(regs_.y - *instruction.operand);
      regs_.status.carry = regs_.y >= *instruction.operand;
      break;
    case Opcode::INC:
      assert(instruction.operand != nullptr);
      *instruction.operand += 1;
      SetDefaultFlags(*instruction.operand);
      break;
    case Opcode::INX:
      regs_.x++;
      SetDefaultFlags(regs_.x);
      break;
    case Opcode::INY:
      regs_.y++;
      SetDefaultFlags(regs_.y);
      break;
    case Opcode::DEC:
      assert(instruction.operand != nullptr);
      *instruction.operand -= 1;
      SetDefaultFlags(*instruction.operand);
      break;
    case Opcode::DEX:
      regs_.x--;
      SetDefaultFlags(regs_.x);
      break;
    case Opcode::DEY:
      regs_.y--;
      SetDefaultFlags(regs_.y);
      break;
    case Opcode::ASL:
      assert(instruction.operand != nullptr);
      regs_.status.carry = !!(*instruction.operand & 0b10000000);
      *instruction.operand <<= 1;
      SetDefaultFlags(*instruction.operand);
      break;
    case Opcode::LSR:
      assert(instruction.operand != nullptr);
      regs_.status.carry = *instruction.operand & 0b1;
      *instruction.operand >>= 1;
      *instruction.operand &= 0b01111111;
      SetDefaultFlags(*instruction.operand);
      break;
    case Opcode::ROL:
      assert(instruction.operand != nullptr);
      regs_.status.carry = !!(*instruction.operand & 0b10000000);
      *instruction.operand <<= 1;
      *instruction.operand |= regs_.status.carry;
      SetDefaultFlags(*instruction.operand);
      break;
    case Opcode::ROR:
      assert(instruction.operand != nullptr);
      regs_.status.carry = *instruction.operand & 0b1;
      *instruction.operand >>= 1;
      *instruction.operand &= 0x7F;
      *instruction.operand |= (regs_.status.carry << 7);
      SetDefaultFlags(*instruction.operand);
      break;
    case Opcode::JMP:
      assert(instruction.operand != nullptr);
      regs_.pc = static_cast<uint16_t>(instruction.operand - &mem_[Address(0)]);
      break;
    case Opcode::JSR: {
      assert(instruction.operand != nullptr);
      const uint16_t pc = regs_.pc - 1;
      PushStack((pc >> 8) & 0xFF);
      PushStack(pc & 0xFF);
      regs_.pc = static_cast<uint16_t>(instruction.operand - &mem_[Address(0)]);
      break;
    }
    case Opcode::RTS: {
      const uint16_t pc_lo = PopStack();
      const uint16_t pc_hi = PopStack();
      regs_.pc = static_cast<uint16_t>((pc_hi << 8) | pc_lo) + 1;
      break;
    }
    case Opcode::BCC:
      assert(instruction.operand != nullptr);
      if (!regs_.status.carry) {
        regs_.pc =
            static_cast<uint16_t>(instruction.operand - &mem_[Address(0)]);
      }
      break;
    case Opcode::BCS:
      assert(instruction.operand != nullptr);
      if (regs_.status.carry) {
        regs_.pc =
            static_cast<uint16_t>(instruction.operand - &mem_[Address(0)]);
      }
      break;
    case Opcode::BEQ:
      assert(instruction.operand != nullptr);
      if (regs_.status.zero) {
        regs_.pc =
            static_cast<uint16_t>(instruction.operand - &mem_[Address(0)]);
      }
      break;
    case Opcode::BMI:
      assert(instruction.operand != nullptr);
      if (regs_.status.negative) {
        regs_.pc =
            static_cast<uint16_t>(instruction.operand - &mem_[Address(0)]);
      }
      break;
    case Opcode::BNE:
      assert(instruction.operand != nullptr);
      if (!regs_.status.zero) {
        regs_.pc =
            static_cast<uint16_t>(instruction.operand - &mem_[Address(0)]);
      }
      break;
    case Opcode::BPL:
      assert(instruction.operand != nullptr);
      if (!regs_.status.negative) {
        regs_.pc =
            static_cast<uint16_t>(instruction.operand - &mem_[Address(0)]);
      }
      break;
    case Opcode::BVC:
      assert(instruction.operand != nullptr);
      if (!regs_.status.overflow) {
        regs_.pc =
            static_cast<uint16_t>(instruction.operand - &mem_[Address(0)]);
      }
      break;
    case Opcode::BVS:
      assert(instruction.operand != nullptr);
      if (regs_.status.overflow) {
        regs_.pc =
            static_cast<uint16_t>(instruction.operand - &mem_[Address(0)]);
      }
      break;
    case Opcode::CLC:
      regs_.status.carry = 0;
      break;
    case Opcode::CLD:
      regs_.status.decimal_mode = 0;
      break;
    case Opcode::CLI:
      regs_.status.interrupt_disable = 0;
      break;
    case Opcode::CLV:
      regs_.status.overflow = 0;
      break;
    case Opcode::SEC:
      regs_.status.carry = 1;
      break;
    case Opcode::SED:
      regs_.status.decimal_mode = 1;
      break;
    case Opcode::SEI:
      regs_.status.interrupt_disable = 1;
      break;
    case Opcode::BRK:
      regs_.status.break_command = 1;
      PushStack((regs_.pc >> 8) & 0xFF);
      PushStack(regs_.pc & 0xFF);
      PushStack(regs_.status_byte);
      regs_.pc = kInterruptPage;
      break;
    case Opcode::NOP:
      break;
    case Opcode::RTI: {
      regs_.status_byte = PopStack();
      regs_.status.break_command = 0;
      const uint16_t pc_lo = PopStack();
      const uint16_t pc_hi = PopStack();
      regs_.pc = static_cast<uint16_t>((pc_hi << 8) | pc_lo) + 1;
      break;
    }
    default:
      FATAL("Invalid opcode");
  }
}

uint8_t* Cpu::GetOperand(const AddressingMode& addressing_mode) {
  switch (addressing_mode) {
    case AddressingMode::kImplicit:
      return nullptr;
    case AddressingMode::kAccumulator:
      return &regs_.acc;
    case AddressingMode::kImmediate:
      return &mem_[Address(regs_.pc++)];
    case AddressingMode::kZeroPage: {
      const uint8_t addr = GetByteAndAdvancePc();
      return &mem_[Address(addr)];
    }
    case AddressingMode::kZeroPageX: {
      const uint8_t addr = GetByteAndAdvancePc() + regs_.x;
      return &mem_[Address(addr)];
    }
    case AddressingMode::kZeroPageY: {
      const uint8_t addr = GetByteAndAdvancePc() + regs_.y;
      return &mem_[Address(addr)];
    }
    case AddressingMode::kRelative: {
      const uint16_t pc = regs_.pc;
      return &mem_[Address(pc + GetByteAndAdvancePc())];
    }
    case AddressingMode::kAbsolute:
      return &mem_[GetAddressAndAdvancePc()];
    case AddressingMode::kAbsoluteX:
      return &mem_[GetAddressAndAdvancePc() + regs_.x];
    case AddressingMode::kAbsoluteY:
      return &mem_[GetAddressAndAdvancePc() + regs_.y];
    case AddressingMode::kIndirect: {
      const Address addr = GetAddressAndAdvancePc();
      return &mem_[Address(GetUint16(&mem_[addr]))];
    }
    case AddressingMode::kIndexedIndirect: {
      const Address addr = GetAddressAndAdvancePc() + regs_.x;
      return &mem_[Address(GetUint16(&mem_[addr]))];
    }
    case AddressingMode::kIndirectIndexed: {
      const Address addr = GetAddressAndAdvancePc();
      return &mem_[Address(GetUint16(&mem_[addr])) + regs_.y];
    }
    default:
      FATAL("Unknown addressing mode");
  }
}

uint8_t Cpu::GetByteAndAdvancePc() { return mem_[Address(regs_.pc++)]; }

uint8_t* Cpu::GetBytePointerAndAdvancePc() {
  return &mem_[Address(regs_.pc++)];
}

Address Cpu::GetAddressAndAdvancePc() {
  const Address addr = Address(GetUint16(&mem_[Address(regs_.pc)]));
  regs_.pc += 2;
  return addr;
}

void Cpu::PushStack(const uint8_t value) {
  mem_[Address(regs_.sp-- | kStackPage)] = value;
}

uint8_t Cpu::PopStack() { return mem_[Address(regs_.sp++ | kStackPage)]; }

void Cpu::SetDefaultFlags(const uint8_t value) {
  regs_.status.zero = value == 0;
  regs_.status.negative = !!(value & 0b10000000);
}

void Cpu::Adc(const uint8_t operand) {
  const uint16_t result = regs_.acc + operand + regs_.status.carry;
  regs_.status.carry = !!(result & 0x100);
  regs_.status.overflow =
      !!(~(regs_.acc ^ operand) & (regs_.acc ^ result) & 0x80);
  regs_.acc = result & 0xFF;
  SetDefaultFlags(regs_.acc);
}

}  // namespace nesty
