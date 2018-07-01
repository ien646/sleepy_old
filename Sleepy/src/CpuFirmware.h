#pragma once

#include "Common.h"
#include "CpuInstructionDef.h"
#include "InstructionImpl.h"

#include <string>
#include <map>

namespace sleepy
{
	// -- Forward declarations --
	class System;
	class Registers;
	class Cpu;
	class Memory;
	// --------------------------

	class CpuFirmware
	{
	public:
		CpuFirmware() = delete;
		CpuFirmware(System& sys);
		std::map<OPCODE, CpuInstructionDef> InstructionMap;

	private:
		System& _sys;
		Registers& _regs;
		Cpu& _cpu;
		Memory& _mem;
		InstructionImpl _instImpl;

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
		void InitMap_LD_R8_D8();
		void InitMap_LD_PTR_A();
		void InitMap_LD_A_PTR();
		void InitMap_LD_R16_D16();
		void InitMap_LD_Misc();

		void InitMap_ADD_A_X8();
		void InitMap_ADD_HL_R16();
		void InitMap_SUB_A_X8();
		void InitMap_ADC_A_X8();
		void InitMap_SBC_A_X8();

		void InitMap_AND_A_X8();
		void InitMap_OR_A_X8();

		void InitMap_XOR_A_X8();

		void InitMap_INC_R8();
		void InitMap_INC_R16();
		void InitMap_DEC_R8();
		void InitMap_DEC_R16();

		void InitMap_CP_R8();

		void InitMap_BitRotations();

		void InitMap_RST();

		void AddInstruction(OPCODE opc, const std::string& mnem, BYTE cycc, BYTE argl, const CpuInstructionDef::OP_CALL& call);
	};
}