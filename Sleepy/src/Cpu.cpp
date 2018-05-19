#include "Cpu.h"
#include "System.h"

namespace sleepy
{

	Cpu::Cpu() noexcept
	{
		this->Registers.ZeroRegisters();
	}

	void Cpu::Initialize(System* sys)
	{
		_sys = sys;
		_memory = &(_sys->Memory);
		Firmware.Initialize(_sys);
		Registers.ZeroRegisters(true);
	}

	void Cpu::EnableInterrupts()
	{
		_interruptsEnabled = true;
	}

	void Cpu::DisableInterrupts()
	{
		_interruptsEnabled = false;
	}

	bool Cpu::AreInterruptsEnabled()
	{
		return _interruptsEnabled;
	}
}