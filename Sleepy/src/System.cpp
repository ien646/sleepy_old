#include "System.h"

namespace sleepy
{
	sleepy::System::System() noexcept
	{

	}

	void sleepy::System::Initialize()
	{
		this->CPU = std::make_unique<sleepy::Cpu>(*this);
		this->Memory = std::make_unique<sleepy::Memory>();
	}
}