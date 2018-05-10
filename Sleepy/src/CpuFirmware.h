#pragma once

#include "Common.h"
#include "CpuInstructionDef.h"
#include <string>
#include <map>

namespace sleepy
{
	class System;

	class CpuFirmware
	{
	public:
		void Initialize(System* sys);
		std::map<OPCODE, CpuInstructionDef> InstructionMap;

	private:
		System* _sys;

		void InitInstructionMap();

		void InitMap_Misc();

		void InitMap_LD_A_X();
		void InitMap_LD_B_X();
		void InitMap_LD_C_X();
		void InitMap_LD_D_X();
		void InitMap_LD_E_X();
		void InitMap_LD_H_X();
		void InitMap_LD_L_X();
		void InitMap_LD_pHL_X();

		void AddInstruction(OPCODE opc, const std::string& mnem, BYTE cycc, BYTE argl, CpuInstructionDef::OP_CALL call);
	};
}