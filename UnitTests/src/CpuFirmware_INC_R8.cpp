#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"
#include "TestInitMacros.h"

#pragma warning(disable:4189)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sleepy;

namespace sleepy
{
	TEST_CLASS(CpuFirmware_INC_R8)
	{
	public:
		TEST_METHOD(INC_R8_CorrectOperation)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& inc_a = instMap[OPCODE(0x3C)];
			CpuInstructionDef& inc_b = instMap[OPCODE(0x04)];
			CpuInstructionDef& inc_c = instMap[OPCODE(0x0C)];
			CpuInstructionDef& inc_d = instMap[OPCODE(0x14)];
			CpuInstructionDef& inc_e = instMap[OPCODE(0x1C)];
			CpuInstructionDef& inc_h = instMap[OPCODE(0x24)];
			CpuInstructionDef& inc_l = instMap[OPCODE(0x2C)];
			CpuInstructionDef& inc_phl = instMap[OPCODE(0x34)];

			regs.A = 0x00;
			inc_a.Call(nullptr);
			Assert::IsTrue(0x01 == regs.A);

			regs.A = 0x11;
			inc_a.Call(nullptr);
			Assert::IsTrue(0x12 == regs.A);
		}

		TEST_METHOD(INC_R8_CorrectFlags)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& inc_a = instMap[OPCODE(0x3C)];
			CpuInstructionDef& inc_b = instMap[OPCODE(0x04)];
			CpuInstructionDef& inc_c = instMap[OPCODE(0x0C)];
			CpuInstructionDef& inc_d = instMap[OPCODE(0x14)];
			CpuInstructionDef& inc_e = instMap[OPCODE(0x1C)];
			CpuInstructionDef& inc_h = instMap[OPCODE(0x24)];
			CpuInstructionDef& inc_l = instMap[OPCODE(0x2C)];
			CpuInstructionDef& inc_phl = instMap[OPCODE(0x24)];

			regs.A = 0x00;
			inc_a.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));

			regs.A = 0x01;
			inc_a.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));

			regs.A = 0x0F;
			inc_a.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));

			regs.A = 0xFF;
			inc_a.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsTrue(regs.ReadFlag(FLAG_ZERO));
		}
	};
}