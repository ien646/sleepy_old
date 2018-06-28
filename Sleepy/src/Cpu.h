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
		UPTR<CpuFirmware> Firmware;

		Cpu(System& sys);
		void EnableInterrupts();
		void DisableInterrupts();		

		bool AreInterruptsEnabled();
	private:
		bool _interruptsEnabled = false;
		UPTR<Memory>& _memory;
		System& _sys;
	};
}