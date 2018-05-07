#pragma once

#include "Common.h"
#include "CpuInstructionDef.h"
#include <string>
#include <map>

namespace sleepy
{
	class CpuFirmware
	{
	public:
		void Initialize();
		std::map<OPCODE, CpuInstructionDef> InstructionMap;

	private:
		void NOP();
		void STOP();
		void LD_r8_v8(REG_8BIT& reg, BYTE byte);
	};
}