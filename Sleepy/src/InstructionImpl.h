#pragma once

#include "Common.h"

namespace sleepy
{
	// -- Forward declarations --
	class System;
	class Cpu;
	class Memory;
	class Registers;
	// --------------------------

	class InstructionImpl
	{
	private:
		System& _sys;
		Cpu& _cpu;
		Memory& _mem;
		Registers& _regs;

	public:
		InstructionImpl() = delete;
		InstructionImpl(System& sys);

		void Opcode_ADD_A_V8(BYTE v8);
		void Opcode_ADD_HL_V16(WORD v16);
		void Opcode_SUB_A_V8(BYTE v8);
		void Opcode_ADC_A_V8(BYTE v8);
		void Opcode_SBC_A_V8(BYTE v8);

		void Opcode_AND_A_V8(BYTE v8);
		void Opcode_OR_A_V8(BYTE v8);
		void Opcode_XOR_A_V8(BYTE v8);
		void Opcode_INC_R8(REG_8BIT& reg);
		void Opcode_DEC_R8(REG_8BIT & reg);
		void Opcode_CP_R8(BYTE reg);

		void Opcode_RRCA();
		void Opcode_RRA();
		void Opcode_RLCA();
		void Opcode_RLA();
		void Opcode_CPL();
		void Opcode_CCF();
		void Opcode_DAA();
	};

}