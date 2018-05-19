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
			Assert::IsTrue(sys.CPU.AreInterruptsEnabled());

			sys.CPU.EnableInterrupts();
			ei.Call(nullptr);
			Assert::IsTrue(sys.CPU.AreInterruptsEnabled());
		}

		TEST_METHOD(CpuFirmware_DI_EnablesInterrupts)
		{
			CPUFW_SLEEPY_TESTINIT();

			auto di = instMap[OPCODE(0xF3)];

			sys.CPU.EnableInterrupts();
			di.Call(nullptr);
			Assert::IsFalse(sys.CPU.AreInterruptsEnabled());

			sys.CPU.DisableInterrupts();
			di.Call(nullptr);
			Assert::IsFalse(sys.CPU.AreInterruptsEnabled());
		}
	};
}