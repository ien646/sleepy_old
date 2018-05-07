#include "Cpu.h"

sleepy::Cpu::Cpu()
{
}

void sleepy::Cpu::Initialize(Memory * mem)
{
	Firmware.Initialize();
}
