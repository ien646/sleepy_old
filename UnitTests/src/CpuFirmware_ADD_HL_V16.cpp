#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"
#include "TestInitMacros.h"

#pragma warning(disable:4310)
#pragma warning(disable:4189)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace sleepy
{
	TEST_CLASS(CpuFirmware_ADD_HL_V16)
	{
		TEST_METHOD(ADD_HL_V16_AdditionIsCorrect)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& add_hl_bc = instMap[OPCODE(0x09)];
			CpuInstructionDef& add_hl_de = instMap[OPCODE(0x19)];
			CpuInstructionDef& add_hl_hl = instMap[OPCODE(0x29)];
			CpuInstructionDef& add_hl_sp = instMap[OPCODE(0x39)];

			regs.SetHL(0x1100);
			regs.SetBC(0x00BC);
			add_hl_bc.Call(nullptr);
			Assert::IsTrue(regs.ReadHL() == (WORD)(0x1100 + 0x00BC));

			regs.SetHL(0x2200);
			regs.SetDE(0x00DE);
			add_hl_de.Call(nullptr);
			Assert::IsTrue(regs.ReadHL() == (WORD)(0x2200 + 0x00DE));

			regs.SetHL(0x2200);
			add_hl_hl.Call(nullptr);
			Assert::IsTrue(regs.ReadHL() == (WORD)(0x2200 + 0x2200));

			regs.SetHL(0x4444);
			regs.SP = (0x0055);
			add_hl_sp.Call(nullptr);
			Assert::IsTrue(regs.ReadHL() == (WORD)(0x4444 + 0x0055));
		}

		TEST_METHOD(ADD_HL_V16_OverflowingIsCorrect)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& add_hl_bc = instMap[OPCODE(0x09)];
			CpuInstructionDef& add_hl_de = instMap[OPCODE(0x19)];
			CpuInstructionDef& add_hl_hl = instMap[OPCODE(0x29)];
			CpuInstructionDef& add_hl_sp = instMap[OPCODE(0x39)];

			regs.SetHL(0xFF00);
			regs.SetBC(0x1111);
			add_hl_bc.Call(nullptr);
			Assert::IsTrue(regs.ReadHL() == (WORD)(0xFF00 + 0x1111));

			regs.SetHL(0xFF44);
			regs.SetDE(0x1DDD);
			add_hl_de.Call(nullptr);
			Assert::IsTrue(regs.ReadHL() == (WORD)(0xFF44 + 0x1DDD));

			regs.SetHL(0xDDDD);
			add_hl_hl.Call(nullptr);
			Assert::IsTrue(regs.ReadHL() == (WORD)(0xDDDD + 0xDDDD));

			regs.SetHL(0xEEEE);
			regs.SP = (0x2222);
			add_hl_sp.Call(nullptr);
			Assert::IsTrue(regs.ReadHL() == (WORD)(0xEEEE + 0x2222));
		}

		TEST_METHOD(ADD_HL_V16_FlagsAreCorrect)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& add_hl_bc = instMap[OPCODE(0x09)];
			CpuInstructionDef& add_hl_de = instMap[OPCODE(0x19)];
			CpuInstructionDef& add_hl_hl = instMap[OPCODE(0x29)];
			CpuInstructionDef& add_hl_sp = instMap[OPCODE(0x39)];

			regs.ResetAllFlags();
			regs.SetHL(0x0000);
			regs.SetBC(0x0000);
			add_hl_bc.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));

			regs.ResetAllFlags();
			regs.SetHL(0x00FF);
			regs.SetBC(0x0001);
			add_hl_bc.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));

			regs.ResetAllFlags();
			regs.SetHL(0xFFFF);
			regs.SetBC(0x0001);
			add_hl_bc.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
		}
	};
}