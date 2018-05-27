#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"
#include "TestInitMacros.h"

#pragma warning(disable:4310)
#pragma warning(disable:4189)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace sleepy
{
	TEST_CLASS(CpuFirmware_SBC_A_V8)
	{
		TEST_METHOD(SBC_A_V8_SubtractionIsCorrect_NoFlags)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& sbc_a_a = instMap[OPCODE(0x9F)];
			CpuInstructionDef& sbc_a_b = instMap[OPCODE(0x98)];
			CpuInstructionDef& sbc_a_c = instMap[OPCODE(0x99)];
			CpuInstructionDef& sbc_a_d = instMap[OPCODE(0x9A)];
			CpuInstructionDef& sbc_a_e = instMap[OPCODE(0x9B)];
			CpuInstructionDef& sbc_a_h = instMap[OPCODE(0x9C)];
			CpuInstructionDef& sbc_a_l = instMap[OPCODE(0x9D)];
			CpuInstructionDef& sbc_a_phl = instMap[OPCODE(0x9E)];
			CpuInstructionDef& sbc_a_d8 = instMap[OPCODE(0xDE)];

			regs.ResetAllFlags();
			regs.A = 0xA0;
			sbc_a_a.Call(nullptr);
			Assert::IsTrue((0xA0 - 0xA0) == regs.A);

			regs.ResetAllFlags();
			regs.A = 0xA0;
			regs.B = 0x0B;
			sbc_a_b.Call(nullptr);
			Assert::IsTrue((0xA0 - 0x0B) == regs.A);

			regs.ResetAllFlags();
			regs.A = 0xA0;
			regs.C = 0x0C;
			sbc_a_c.Call(nullptr);
			Assert::IsTrue((0xA0 - 0x0C) == regs.A);

			regs.ResetAllFlags();
			regs.A = 0xA0;
			regs.D = 0x0D;
			sbc_a_d.Call(nullptr);
			Assert::IsTrue((0xA0 - 0x0D) == regs.A);

			regs.ResetAllFlags();
			regs.A = 0xA0;
			regs.E = 0x0E;
			sbc_a_e.Call(nullptr);
			Assert::IsTrue((0xA0 - 0x0E) == regs.A);

			regs.ResetAllFlags();
			regs.A = 0xA0;
			regs.H = 0x0F;
			sbc_a_h.Call(nullptr);
			Assert::IsTrue((0xA0 - 0x0F) == regs.A);

			regs.ResetAllFlags();
			regs.A = 0xA0;
			regs.L = 0x1F;
			sbc_a_l.Call(nullptr);
			Assert::IsTrue((0xA0 - 0x1F) == regs.A);

			regs.ResetAllFlags();
			ADDR addrHL = 0xF0F0;
			mem.WriteByte(addrHL, 0x22);
			regs.SetHL(addrHL);
			regs.A = 0xA0;
			sbc_a_phl.Call(nullptr);
			Assert::IsTrue((0xA0 - 0x22) == regs.A);

			regs.ResetAllFlags();
			regs.A = 0xA0;
			BYTE d8 = 0x1F;
			sbc_a_d8.Call(&d8);
			Assert::IsTrue((0xA0 - 0x1F) == regs.A);
		}

		TEST_METHOD(SBC_A_V8_SubtractionIsCorrect_WithFlags)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& sbc_a_a = instMap[OPCODE(0x9F)];
			CpuInstructionDef& sbc_a_b = instMap[OPCODE(0x98)];
			CpuInstructionDef& sbc_a_c = instMap[OPCODE(0x99)];
			CpuInstructionDef& sbc_a_d = instMap[OPCODE(0x9A)];
			CpuInstructionDef& sbc_a_e = instMap[OPCODE(0x9B)];
			CpuInstructionDef& sbc_a_h = instMap[OPCODE(0x9C)];
			CpuInstructionDef& sbc_a_l = instMap[OPCODE(0x9D)];
			CpuInstructionDef& sbc_a_phl = instMap[OPCODE(0x9E)];

			regs.ResetAllFlags();
			regs.SetFlag(FLAG_CARRY);
			regs.A = 0x0A;
			sbc_a_a.Call(nullptr);
			Assert::IsTrue((BYTE)(0x0A - 0x0A - 1) == regs.A);

			regs.ResetAllFlags();
			regs.SetFlag(FLAG_CARRY);
			regs.A = 0x0A;
			regs.B = 0x0B;
			sbc_a_b.Call(nullptr);
			Assert::IsTrue((BYTE)(0x0A - 0x0B - 1) == regs.A);

			regs.ResetAllFlags();
			regs.SetFlag(FLAG_CARRY);
			regs.A = 0x0A;
			regs.C = 0x0C;
			sbc_a_c.Call(nullptr);
			Assert::IsTrue((BYTE)(0x0A - 0x0C - 1) == regs.A);

			regs.ResetAllFlags();
			regs.SetFlag(FLAG_CARRY);
			regs.A = 0x0A;
			regs.D = 0x0D;
			sbc_a_d.Call(nullptr);
			Assert::IsTrue((BYTE)(0x0A - 0x0D - 1) == regs.A);

			regs.ResetAllFlags();
			regs.SetFlag(FLAG_CARRY);
			regs.A = 0x0A;
			regs.E = 0x0E;
			sbc_a_e.Call(nullptr);
			Assert::IsTrue((BYTE)(0x0A - 0x0E - 1) == regs.A);

			regs.ResetAllFlags();
			regs.SetFlag(FLAG_CARRY);
			regs.A = 0x0A;
			regs.H = 0xA0;
			sbc_a_h.Call(nullptr);
			Assert::IsTrue((BYTE)(0x0A - 0xA0 - 1) == regs.A);

			regs.ResetAllFlags();
			regs.SetFlag(FLAG_CARRY);
			regs.A = 0x0A;
			regs.L = 0xAF;
			sbc_a_l.Call(nullptr);
			Assert::IsTrue((BYTE)(0x0A - 0xAF - 1) == regs.A);

			regs.ResetAllFlags();
			regs.SetFlag(FLAG_CARRY);
			ADDR addrHL = 0xF0F0;
			mem.WriteByte(addrHL, 0xAA);
			regs.SetHL(addrHL);
			regs.A = 0x0A;
			sbc_a_phl.Call(nullptr);
			Assert::IsTrue((BYTE)(0x0A - 0xAA - 1) == regs.A);
		}

		TEST_METHOD(SBC_A_V8_FlagsAreCorrect)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& sbc_a_a = instMap[OPCODE(0x9F)];
			CpuInstructionDef& sbc_a_b = instMap[OPCODE(0x98)];
			CpuInstructionDef& sbc_a_c = instMap[OPCODE(0x99)];
			CpuInstructionDef& sbc_a_d = instMap[OPCODE(0x9A)];
			CpuInstructionDef& sbc_a_e = instMap[OPCODE(0x9B)];
			CpuInstructionDef& sbc_a_h = instMap[OPCODE(0x9C)];
			CpuInstructionDef& sbc_a_l = instMap[OPCODE(0x9D)];
			CpuInstructionDef& sbc_a_phl = instMap[OPCODE(0x9E)];

			regs.ResetAllFlags();

			regs.ResetFlag(FLAG_CARRY);
			regs.A = 0x00;
			sbc_a_a.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));

			regs.SetFlag(FLAG_CARRY);
			regs.A = 0x00;
			sbc_a_a.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));

			regs.ResetFlag(FLAG_CARRY);
			regs.A = 0x10;
			regs.B = 0x01;
			sbc_a_b.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));

			regs.SetFlag(FLAG_CARRY);
			regs.A = 0xFF;
			regs.B = 0x10;
			sbc_a_b.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));

			regs.ResetFlag(FLAG_CARRY);
			regs.A = 0xFF;
			regs.B = 0x00;
			sbc_a_b.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));

			regs.SetFlag(FLAG_CARRY);
			regs.A = 0x00;
			regs.B = 0x00;
			sbc_a_b.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));
		}
	};
}