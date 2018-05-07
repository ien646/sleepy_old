#include "CpuFirmware.h"

namespace sleepy
{
	void CpuFirmware::Initialize()
	{

	}

	void CpuFirmware::NOP()
	{
		return;
	}

	void CpuFirmware::STOP()
	{
		return;
	}

	void CpuFirmware::LD_r8_v8(REG_8BIT& reg, BYTE byte)
	{
		reg = byte;
	}
}
