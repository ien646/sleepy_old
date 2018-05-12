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

		Cpu() noexcept;
		void Initialize(System* sys);
		void EnableInterrupts();
		void DisableInterrupts();		

	private:
		bool _interruptsEnabled = false;
		Memory* _memory = nullptr;
		System* _sys = nullptr;
	};
}