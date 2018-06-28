#pragma once

#include "Common.h"
#include "Cpu.h"
#include "Memory.h"

namespace sleepy
{
	class System
	{
	public:
		UPTR<Memory> Memory;
		UPTR<Cpu> CPU;

		System() noexcept;
		void Initialize();
	};
}