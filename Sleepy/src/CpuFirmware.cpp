#include "CpuFirmware.h"
#include "Common.h"
#include "System.h"

namespace sleepy
{
	void CpuFirmware::Initialize(System* sys)
	{
		_sys = sys;
		_mem = &(_sys->Memory);
		_regs = &(sys->CPU.Registers);
		InitInstructionMap();
	}

	void CpuFirmware::InitInstructionMap()
	{
		AddInstruction(OPCODE(0x00), "NOP", 4, 0, [&](BYTE* args) { return; });
		AddInstruction(OPCODE(0x10), "STOP", 4, 1, [&](BYTE* args) { return; });
	}

	void CpuFirmware::AddInstruction(OPCODE opc, const std::string & mnem, BYTE cycc, BYTE argl, CpuInstructionDef::OP_CALL call)
	{
		InstructionMap.insert(std::make_pair(opc, CpuInstructionDef(opc, mnem, cycc, argl, call)));
	}
}