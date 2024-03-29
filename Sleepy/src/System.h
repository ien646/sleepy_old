#pragma once

#include "Common.h"
#include "Cpu.h"
#include "Memory.h"

namespace sleepy
{
	class System
	{
	public:
		Memory Memory;
		Cpu CPU;

		System() noexcept;
		System(const System& copy_src) = delete;
		System(System&& move_src) = default;
	};
}