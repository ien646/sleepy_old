#include "Cpu.h"
#include "System.h"

sleepy::Cpu::Cpu()
{

}

void sleepy::Cpu::Initialize(System* sys)
{
	_sys = sys;
	_memory = &(_sys->Memory);	
	Firmware.Initialize(_sys);
}
