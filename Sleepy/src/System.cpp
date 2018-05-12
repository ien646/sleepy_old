#include "System.h"

sleepy::System::System() noexcept
{
	CPU.Initialize(this);
}

void sleepy::System::Initialize()
{
	CPU.Initialize(this);
}
