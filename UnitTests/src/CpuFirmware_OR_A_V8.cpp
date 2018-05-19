#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"
#include "TestInitMacros.h"

#pragma warning(disable:4310)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace sleepy
{
	TEST_CLASS(CpuFirmware_OR_A_V8)
	{
		TEST_METHOD(OR_A_V8_CorrectOperation)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef or_a_a = instMap[OPCODE(0xB7)];
			CpuInstructionDef or_a_b = instMap[OPCODE(0xB0)];
			CpuInstructionDef or_a_c = instMap[OPCODE(0xB1)];
			CpuInstructionDef or_a_d = instMap[OPCODE(0xB2)];
			CpuInstructionDef or_a_e = instMap[OPCODE(0xB3)];
			CpuInstructionDef or_a_h = instMap[OPCODE(0xB4)];
			CpuInstructionDef or_a_l = instMap[OPCODE(0xB5)];
			CpuInstructionDef or_a_phl = instMap[OPCODE(0xB6)];
			CpuInstructionDef or_a_d8 = instMap[OPCODE(0xF6)];

			regs.A = 0xFF;
			or_a_a.Call(nullptr);
			Assert::IsTrue(0xFF == regs.A);

			regs.A = 0x00;
			or_a_a.Call(nullptr);
			Assert::IsTrue(0x00 == regs.A);

			regs.A = 0xAD;
			regs.B = 0xDA;
			or_a_b.Call(nullptr);
			Assert::IsTrue((0xAD | 0xDA) == regs.A);

			regs.A = 0xAD;
			regs.C = 0xDA;
			or_a_c.Call(nullptr);
			Assert::IsTrue((0xAD | 0xDA) == regs.A);

			regs.A = 0xAD;
			regs.D = 0xDA;
			or_a_d.Call(nullptr);
			Assert::IsTrue((0xAD | 0xDA) == regs.A);

			regs.A = 0xAD;
			regs.E = 0xDA;
			or_a_e.Call(nullptr);
			Assert::IsTrue((0xAD | 0xDA) == regs.A);

			regs.A = 0xAD;
			regs.H = 0xDA;
			or_a_h.Call(nullptr);
			Assert::IsTrue((0xAD | 0xDA) == regs.A);

			regs.A = 0xAD;
			regs.L = 0xDA;
			or_a_l.Call(nullptr);
			Assert::IsTrue((0xAD | 0xDA) == regs.A);

			regs.A = 0xAD;
			ADDR phl = 0xFAFA;
			regs.SetHL(phl);
			mem.WriteByte(phl, 0xDA);
			or_a_phl.Call(nullptr);
			Assert::IsTrue((0xAD | 0xDA) == regs.A);

			regs.A = 0xAD;
			BYTE d8 = 0xDA;
			or_a_d8.Call(&d8);
			Assert::IsTrue((0xAD | 0xDA) == regs.A);
		}

		TEST_METHOD(OR_A_V8_FlagsAreCorrect)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef or_a_a = instMap[OPCODE(0xB7)];
			CpuInstructionDef or_a_b = instMap[OPCODE(0xB0)];
			CpuInstructionDef or_a_c = instMap[OPCODE(0xB1)];
			CpuInstructionDef or_a_d = instMap[OPCODE(0xB2)];
			CpuInstructionDef or_a_e = instMap[OPCODE(0xB3)];
			CpuInstructionDef or_a_h = instMap[OPCODE(0xB4)];
			CpuInstructionDef or_a_l = instMap[OPCODE(0xB5)];
			CpuInstructionDef or_a_phl = instMap[OPCODE(0xB6)];

			regs.A = 0xFF;
			or_a_a.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.A = 0x00;
			or_a_a.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.A = 0x00;
			regs.B = 0x00;
			or_a_b.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.A = 0xFF;
			regs.B = 0x00;
			or_a_b.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.A = 0xFF;
			regs.B = 0x0F;
			or_a_b.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.A = 0xFF;
			regs.B = 0x10;
			or_a_b.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
		}
	};
}