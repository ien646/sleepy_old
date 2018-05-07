#include "CpuInstructionDef.h"

namespace sleepy
{
	CpuInstructionDef::CpuInstructionDef(OPCODE opc, const std::string mnem, BYTE cycc, BYTE argsLen, OP_CALL opCall)
	{
		Opcode = opc;
		Mnemonic = mnem;
		Cycles = cycc;
		ArgsLen = argsLen;
		Call = opCall;
	}
}