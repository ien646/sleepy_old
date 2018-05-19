#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"
#include "TestInitMacros.h"

#pragma warning(disable:4310)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace sleepy
{
	TEST_CLASS(CpuFirmware_BITROT)
	{
		TEST_METHOD(RRCA)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef rrca = instMap[0x0F];

			regs.A = 0x00;
			rrca.Call(nullptr);
			Assert::IsTrue(regs.A == 0x00);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.A = 0x01;
			rrca.Call(nullptr);
			Assert::IsTrue(regs.A == 0x80);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.A = 0x80;
			rrca.Call(nullptr);
			Assert::IsTrue(regs.A == 0x40);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
		}

		TEST_METHOD(RRA)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef rra = instMap[0x1F];

			regs.A = 0x00;
			rra.Call(nullptr);
			Assert::IsTrue(regs.A == 0x00);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.A = 0x01;
			rra.Call(nullptr);
			Assert::IsTrue(regs.A == 0x00);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.A = 0x80;
			rra.Call(nullptr);
			Assert::IsTrue(regs.A == 0x40);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
		}
	};
}