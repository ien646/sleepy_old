#include "Cpu.h"
#include "System.h"

namespace sleepy
{
	Cpu::Cpu(System& sys) :
		_sys(sys),
		_memory(sys.Memory)
	{
		this->Registers.ZeroRegisters();
		Registers.ZeroRegisters(true);
		Firmware = std::make_unique<CpuFirmware>(sys);
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