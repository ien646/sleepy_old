#pragma once

#include "Common.h"
#include "Memory.h"
#include "Registers.h"
#include "CpuFirmware.h"

namespace sleepy
{
	class Cpu
	{
	public:
		Registers Registers;
		CpuFirmware Firmware;

		Cpu();
		void Initialize(Memory* mem);

	private:
		bool _interruptsEnabled;
		Memory* _memory;
	};
}