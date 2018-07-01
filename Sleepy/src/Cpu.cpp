#include "Cpu.h"
#include "System.h"

namespace sleepy
{
	Cpu::Cpu(System& sys) :
		_sys(sys),
		_memory(sys.Memory),
		Firmware(sys)
	{
		this->Registers.ZeroRegisters();
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