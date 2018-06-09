#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"
#include "TestInitMacros.h"

#pragma warning(disable:4189)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sleepy;

namespace sleepy
{
	TEST_CLASS(CpuFirmware_LD_Misc)
	{
	public:
		TEST_METHOD(LD_pFF00C_A)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& ld_pff00c_a = instMap[OPCODE(0xE2)];

			regs.A = 0xAA;
			regs.C = 0x00;
			ld_pff00c_a.Call(nullptr);
			Assert::IsTrue(mem.ReadByte(0xFF00 + 0x00) == 0xAA);

			regs.A = 0xAB;
			regs.C = 0x01;
			ld_pff00c_a.Call(nullptr);
			Assert::IsTrue(mem.ReadByte(0xFF00 + 0x01) == 0xAB);

			regs.A = 0xCA;
			regs.C = 0x10;
			ld_pff00c_a.Call(nullptr);
			Assert::IsTrue(mem.ReadByte(0xFF00 + 0x10) == 0xCA);

			regs.A = 0x1F;
			regs.C = 0xFF;
			ld_pff00c_a.Call(nullptr);
			Assert::IsTrue(mem.ReadByte(0xFFFF) == 0x1F);
		}

		TEST_METHOD(LD_A_pFF00C)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& ld_a_pff00c = instMap[OPCODE(0xF2)];
			ADDR addr;

			regs.C = 0x00;
			mem.WriteByte(0xFF00 + regs.C, 0xAA);
			ld_a_pff00c.Call(nullptr);
			Assert::IsTrue(regs.A == 0xAA);

			regs.C = 0x05;
			mem.WriteByte(0xFF00 + regs.C, 0xBB);
			ld_a_pff00c.Call(nullptr);
			Assert::IsTrue(regs.A == 0xBB);

			regs.C = 0x10;
			mem.WriteByte(0xFF00 + regs.C, 0xCC);
			ld_a_pff00c.Call(nullptr);
			Assert::IsTrue(regs.A == 0xCC);

			regs.C = 0xFF;
			mem.WriteByte(0xFF00 + regs.C, 0xDD);
			ld_a_pff00c.Call(nullptr);
			Assert::IsTrue(regs.A == 0xDD);
		}

		TEST_METHOD(LD_d16_SP)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& ld_d16_sp = instMap[OPCODE(0x08)];

			WORD val = 0xFAA7;
			WORD args = 0xADD3;

			regs.SP = val;
			ld_d16_sp.Call((BYTE*)&args);
			Assert::IsTrue(mem.ReadWord(args) == val);
		}
	};
}