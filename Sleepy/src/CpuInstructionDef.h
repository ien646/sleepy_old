#pragma once

#include "Common.h"
#include <string>
#include <functional>

namespace sleepy
{
	class CpuInstructionDef
	{
	public:
		typedef std::function<void(const BYTE*)> OP_CALL;

		// Cpu instruction memory-ordered opcode
		OPCODE Opcode = OPCODE(0xFF, 0x00);

		// Instruction textual representation
		std::string Mnemonic = "Uninitialized Mnemonic";

		// Execution time in cycles
		BYTE Cycles = 0xFF;

		// Arguments length in bytes
		BYTE ArgsLen = 0;

		// Instruction call
		OP_CALL Call = nullptr;

		CpuInstructionDef() noexcept {};

		CpuInstructionDef(OPCODE opc, const std::string& mnem, BYTE cycc, BYTE argsLen, OP_CALL opCall);

		CpuInstructionDef(const CpuInstructionDef& copy_src) = delete;

		CpuInstructionDef(CpuInstructionDef&& move_src) = default;
	};
}