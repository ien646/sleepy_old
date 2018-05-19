#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"
#include "TestInitMacros.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sleepy;

namespace sleepy
{
	TEST_CLASS(CpuFirmware_EI_DI)
	{
		TEST_METHOD(CpuFirmware_EI_EnablesInterrupts)
		{
			CPUFW_SLEEPY_TESTINIT();

			auto ei = instMap[OPCODE(0xFB)];

			sys.CPU.DisableInterrupts();
			ei.Call(nullptr);
			Assert::
		}
	};
}