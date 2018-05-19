#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"
#include "TestInitMacros.h"

#pragma warning(disable:4310)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace sleepy
{
	TEST_CLASS(CpuFirmware_AND_A_V8)
	{
		TEST_METHOD(AND_A_V8_CorrectOperation)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef and_a_a = instMap[OPCODE(0xA7)];
			CpuInstructionDef and_a_b = instMap[OPCODE(0xA0)];
			CpuInstructionDef and_a_c = instMap[OPCODE(0xA1)];
			CpuInstructionDef and_a_d = instMap[OPCODE(0xA2)];
			CpuInstructionDef and_a_e = instMap[OPCODE(0xA3)];
			CpuInstructionDef and_a_h = instMap[OPCODE(0xA4)];
			CpuInstructionDef and_a_l = instMap[OPCODE(0xA5)];
			CpuInstructionDef and_a_phl = instMap[OPCODE(0xA6)];

			regs.A = 0xFF;
			and_a_a.Call(nullptr);
			Assert::IsTrue(0xFF == regs.A);

			regs.A = 0x00;
			and_a_a.Call(nullptr);
			Assert::IsTrue(0x00 == regs.A);

			regs.A = 0xFF;
			regs.B = 0xDD;
			and_a_b.Call(nullptr);
			Assert::IsTrue((0xFF & 0xDD) == regs.A);

			regs.A = 0x00;
			regs.B = 0xDD;
			and_a_b.Call(nullptr);
			Assert::IsTrue((0x00 & 0xDD) == regs.A);
		}

		TEST_METHOD(AND_A_V8_FlagsAreCorrect)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef and_a_a = instMap[OPCODE(0xA7)];
			CpuInstructionDef and_a_b = instMap[OPCODE(0xA0)];
			CpuInstructionDef and_a_c = instMap[OPCODE(0xA1)];
			CpuInstructionDef and_a_d = instMap[OPCODE(0xA2)];
			CpuInstructionDef and_a_e = instMap[OPCODE(0xA3)];
			CpuInstructionDef and_a_h = instMap[OPCODE(0xA4)];
			CpuInstructionDef and_a_l = instMap[OPCODE(0xA5)];
			CpuInstructionDef and_a_phl = instMap[OPCODE(0xA6)];

			regs.A = 0xFF;
			and_a_a.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));

			regs.A = 0x00;
			and_a_a.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));

			regs.A = 0x00;
			regs.B = 0x00;
			and_a_b.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));

			regs.A = 0xFF;
			regs.B = 0x00;
			and_a_b.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));

			regs.A = 0xFF;
			regs.B = 0x0F;
			and_a_b.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));

			regs.A = 0xFF;
			regs.B = 0x10;
			and_a_b.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));
		}
	};
}