#pragma once

#include "Common.h"
#include "CpuInstructionDef.h"
#include <string>
#include <map>

namespace sleepy
{
	class System;
	class Memory;
	class Registers;

	class CpuFirmware
	{
	public:
		void Initialize(System* sys);
		std::map<OPCODE, CpuInstructionDef> InstructionMap;

	private:
		System* _sys;
		Memory* _mem;
		Registers* _regs;

		void InitInstructionMap();
		void AddInstruction(OPCODE opc, const std::string& mnem, BYTE cycc, BYTE argl, CpuInstructionDef::OP_CALL call);
	};
}