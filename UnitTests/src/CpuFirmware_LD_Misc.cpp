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

		TEST_METHOD(LD_HL_SPd8)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& ld_hl_spd8 = instMap[0xF8];
			BYTE d8 = 0x00;

			regs.SP = 0xAAAA;
			d8 = 0xBB;
			ld_hl_spd8.Call(&d8);
			Assert::IsTrue(regs.ReadHL() == (WORD)(0xAAAA + 0xBB));

			regs.ResetAllFlags();
			regs.SP = 0x0000;
			d8 = HBYTE_MAX;
			ld_hl_spd8.Call(&d8);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));

			regs.ResetAllFlags();
			regs.SP = 0x0001;
			d8 = HBYTE_MAX;
			ld_hl_spd8.Call(&d8);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));

			regs.ResetAllFlags();
			regs.SP = 0x00F0;
			d8 = HBYTE_MAX;
			ld_hl_spd8.Call(&d8);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));

			regs.ResetAllFlags();
			regs.SP = 0x00F1;
			d8 = HBYTE_MAX;
			ld_hl_spd8.Call(&d8);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));

			regs.ResetAllFlags();
			regs.SP = 0xFFF1;
			d8 = HBYTE_MAX;
			ld_hl_spd8.Call(&d8);
			Assert::IsTrue(regs.ReadHL() == 0x0000);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));
		}

		TEST_METHOD(LD_a16_A)
		{
			CPUFW_SLEEPY_TESTINIT();
			CpuInstructionDef& ld_a16_a = instMap[0xEA];
			ADDR a16 = 0x0000;

			regs.A = 0x00;
			a16 = 0xBEBA;
			ld_a16_a.Call((BYTE*)&a16);
			Assert::IsTrue(mem.ReadByte(a16) == 0x00);

			regs.A = 0xCC;
			a16 = 0xACAC;
			ld_a16_a.Call((BYTE*)&a16);
			Assert::IsTrue(mem.ReadByte(a16) == 0xCC);
		}

		TEST_METHOD(LD_A_a16)
		{
			CPUFW_SLEEPY_TESTINIT();
			CpuInstructionDef& ld_a_a16 = instMap[0xFA];

			ADDR a16 = 0x0000;
			BYTE val = 0x00;

			a16 = 0x0000;
			val = 0x00;
			mem.WriteByte(a16, val);
			ld_a_a16.Call((BYTE*)&a16);
			Assert::IsTrue(regs.A == val);

			a16 = 0x1111;
			val = 0x21;
			mem.WriteByte(a16, val);
			ld_a_a16.Call((BYTE*)&a16);
			Assert::IsTrue(regs.A == val);

			a16 = 0xFFFF;
			val = 0xAF;
			mem.WriteByte(a16, val);
			ld_a_a16.Call((BYTE*)&a16);
			Assert::IsTrue(regs.A == val);
		}

		TEST_METHOD(LD_SP_HL)
		{
			CPUFW_SLEEPY_TESTINIT();
			CpuInstructionDef& ld_sp_hl = instMap[0xF9];

			regs.SP = 0xA0AB;
			regs.SetHL(0xFEFE);
			ld_sp_hl.Call(nullptr);
			Assert::IsTrue(regs.SP == 0xFEFE);

			regs.SP = 0xBA0F;
			regs.SetHL(0x0F13);
			ld_sp_hl.Call(nullptr);
			Assert::IsTrue(regs.SP == 0x0F13);
		}
	};
}