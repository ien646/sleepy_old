#pragma once

#include "Common.h"
#include <string>
#include <functional>

namespace sleepy
{
	/* -- Forward declarations -- */
	class System;
	/* -------------------------- */

	class CpuInstructionDef
	{
	public:
		typedef std::function<void(BYTE*)> OP_CALL;

		// Cpu instruction memory-ordered opcode
		OPCODE Opcode;

		// Instruction textual representation
		std::string Mnemonic;

		// Execution time in cycles
		BYTE Cycles;

		// Arguments length in bytes
		BYTE ArgsLen;

		// Instruction call
		OP_CALL Call;

		CpuInstructionDef() {};

		CpuInstructionDef(OPCODE opc, const std::string mnem, BYTE cycc, BYTE argsLen, OP_CALL opCall);
	};
}