#pragma once

#include "Common.h"
#include "CpuInstructionDef.h"
#include "Registers.h"
#include "Memory.h"

#include <string>
#include <map>

namespace sleepy
{
	class System;
	class Cpu;

	class CpuFirmware
	{
	public:
		void Initialize(System* sys);
		std::map<OPCODE, CpuInstructionDef> InstructionMap;

	private:
		System* _sys = nullptr;
		Registers* _regs = nullptr;
		Cpu* _cpu = nullptr;
		Memory* _mem = nullptr;

		void InitInstructionMap();

		void InitMap_Misc();

		void InitMap_LD_A_X8();
		void InitMap_LD_B_X8();
		void InitMap_LD_C_X8();
		void InitMap_LD_D_X8();
		void InitMap_LD_E_X8();
		void InitMap_LD_H_X8();
		void InitMap_LD_L_X8();
		void InitMap_LD_pHL_X8();

		void InitMap_LD_R8_V8();

		void InitMap_ADD_A_X8();
		void InitMap_SUB_A_X8();
		void InitMap_ADC_A_X8();
		void InitMap_SBC_A_X8();

		void InitMap_AND_A_X8();
		void InitMap_OR_A_X8();

		void InitMap_XOR_A_X8();

		void InitMap_INC_R8();

		void InitMap_DEC_R8();

		void InitMap_CP_R8();

		void AddInstruction(OPCODE opc, const std::string& mnem, BYTE cycc, BYTE argl, CpuInstructionDef::OP_CALL call);

		void Opcode_ADD_A_V8(BYTE v8);
		void Opcode_SUB_A_V8(BYTE v8);
		void Opcode_ADC_A_V8(BYTE v8);
		void Opcode_SBC_A_V8(BYTE v8);

		void Opcode_AND_A_V8(BYTE v8);
		void Opcode_OR_A_V8(BYTE v8);
		void Opcode_XOR_A_V8(BYTE v8);
		void Opcode_INC_R8(REG_8BIT& reg);
		void Opcode_DEC_R8(REG_8BIT & reg);
		void Opcode_CP_R8(BYTE reg);
	};
}