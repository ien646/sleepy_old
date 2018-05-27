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

	CpuInstructionDef::CpuInstructionDef(CpuInstructionDef && mvsrc)
	{
		Opcode = std::move(mvsrc.Opcode);
		Mnemonic = std::move(mvsrc.Mnemonic);
		Cycles = mvsrc.Cycles;
		ArgsLen = mvsrc.ArgsLen;
		Call = std::move(mvsrc.Call);
	}
}