#pragma once

#include "Common.h"
#include "Registers.h"
#include "CpuFirmware.h"

namespace sleepy
{
	// -- Forward declarations --
	class Memory;
	class System;
	// --------------------------

	class Cpu
	{
	public:
		Registers Registers;
		CpuFirmware Firmware;

		Cpu() = delete;
		Cpu(System& sys);
		Cpu(const Cpu& copy_src) = delete;
		Cpu(Cpu&& move_src) = default;

		void EnableInterrupts();
		void DisableInterrupts();		

		bool AreInterruptsEnabled();
	private:
		bool _interruptsEnabled = false;
		Memory& _memory;
		System& _sys;
	};
}