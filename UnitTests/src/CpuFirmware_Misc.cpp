#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"
#include "TestInitMacros.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sleepy;

namespace sleepy
{
	TEST_CLASS(CpuFirmware_LD_R8_D8)
	{
	public:
		TEST_METHOD(EI_EnablesInterrupts)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef ei = instMap[OPCODE(0xFB)];

			sys.CPU.DisableInterrupts();
			ei.Call(nullptr);
			Assert::IsTrue(sys.CPU.AreInterruptsEnabled());

			sys.CPU.EnableInterrupts();
			ei.Call(nullptr);
			Assert::IsTrue(sys.CPU.AreInterruptsEnabled());
		}

		TEST_METHOD(DI_DisablesInterrupts)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef di = instMap[OPCODE(0xF3)];

			sys.CPU.DisableInterrupts();
			di.Call(nullptr);
			Assert::IsFalse(sys.CPU.AreInterruptsEnabled());

			sys.CPU.EnableInterrupts();
			di.Call(nullptr);
			Assert::IsFalse(sys.CPU.AreInterruptsEnabled());
		}

		TEST_METHOD(CPL_CorrectOperationAndFlags)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef cpl = instMap[OPCODE(0x2F)];

			regs.A = 0x00;
			cpl.Call(nullptr);
			Assert::IsTrue(regs.A == 0xFF);
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));

			regs.A = 0x44;
			cpl.Call(nullptr);
			Assert::IsTrue(regs.A == (0xFF ^ 0x44));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));
		}

		TEST_METHOD(CCF_CorrectOperationAndFlags)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef ccf = instMap[OPCODE(0x3F)];			

			regs.SetFlag(FLAG_CARRY);
			ccf.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			ccf.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));
		}
	};
}