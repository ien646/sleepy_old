#include "Cpu.h"
#include "System.h"

sleepy::Cpu::Cpu() noexcept
{
	this->Registers.ZeroRegisters();
}

void sleepy::Cpu::Initialize(System* sys)
{
	_sys = sys;
	_memory = &(_sys->Memory);	
	Firmware.Initialize(_sys);
	Registers.ZeroRegisters(true);
}

void sleepy::Cpu::EnableInterrupts()
{
	_interruptsEnabled = true;
}

void sleepy::Cpu::DisableInterrupts()
{
	_interruptsEnabled = false;
}
