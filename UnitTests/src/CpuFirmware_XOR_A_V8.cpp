#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"
#include "TestInitMacros.h"

#pragma warning(disable:4310)
#pragma warning(disable:4189)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace sleepy
{
	TEST_CLASS(CpuFirmware_XOR_A_V8)
	{
		TEST_METHOD(XOR_A_V8_CorrectOperation)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& xor_a_a = instMap[OPCODE(0xAF)];
			CpuInstructionDef& xor_a_b = instMap[OPCODE(0xA8)];
			CpuInstructionDef& xor_a_c = instMap[OPCODE(0xA9)];
			CpuInstructionDef& xor_a_d = instMap[OPCODE(0xAA)];
			CpuInstructionDef& xor_a_e = instMap[OPCODE(0xAB)];
			CpuInstructionDef& xor_a_h = instMap[OPCODE(0xAC)];
			CpuInstructionDef& xor_a_l = instMap[OPCODE(0xAD)];
			CpuInstructionDef& xor_a_phl = instMap[OPCODE(0xAE)];
			CpuInstructionDef& xor_a_d8 = instMap[OPCODE(0xEE)];

			regs.A = 0xFF;
			xor_a_a.Call(nullptr);
			Assert::IsTrue((0xFF ^ 0xFF) == regs.A);

			regs.A = 0x00;
			xor_a_a.Call(nullptr);
			Assert::IsTrue((0x00 ^ 0x00) == regs.A);

			regs.A = 0xDA;
			regs.B = 0xAD;
			xor_a_b.Call(nullptr);
			Assert::IsTrue((0xDA ^ 0xAD) == regs.A);

			regs.A = 0xDA;
			regs.C = 0xAD;
			xor_a_c.Call(nullptr);
			Assert::IsTrue((0xDA ^ 0xAD) == regs.A);

			regs.A = 0xDA;
			regs.D = 0xAD;
			xor_a_d.Call(nullptr);
			Assert::IsTrue((0xDA ^ 0xAD) == regs.A);

			regs.A = 0xDA;
			regs.E = 0xAD;
			xor_a_e.Call(nullptr);
			Assert::IsTrue((0xDA ^ 0xAD) == regs.A);

			regs.A = 0xDA;
			regs.H = 0xAD;
			xor_a_h.Call(nullptr);
			Assert::IsTrue((0xDA ^ 0xAD) == regs.A);

			regs.A = 0xDA;
			regs.L = 0xAD;
			xor_a_l.Call(nullptr);
			Assert::IsTrue((0xDA ^ 0xAD) == regs.A);

			regs.A = 0xDA;
			BYTE d8 = 0xAD;
			xor_a_d8.Call(&d8);
			Assert::IsTrue((0xDA ^ 0xAD) == regs.A);

			ADDR phl = 0xFAFA;
			regs.SetHL(phl);
			mem.WriteByte(regs.ReadHL(), 0xAD);
			regs.A = 0xDA;
			xor_a_phl.Call(&d8);
			Assert::IsTrue((0xDA ^ 0xAD) == regs.A);
		}

		TEST_METHOD(XOR_A_V8_FlagsAreCorrect)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& xor_a_a = instMap[OPCODE(0xAF)];
			CpuInstructionDef& xor_a_b = instMap[OPCODE(0xA8)];
			CpuInstructionDef& xor_a_c = instMap[OPCODE(0xA9)];
			CpuInstructionDef& xor_a_d = instMap[OPCODE(0xAA)];
			CpuInstructionDef& xor_a_e = instMap[OPCODE(0xAB)];
			CpuInstructionDef& xor_a_h = instMap[OPCODE(0xAC)];
			CpuInstructionDef& xor_a_l = instMap[OPCODE(0xAD)];
			CpuInstructionDef& xor_a_phl = instMap[OPCODE(0xAE)];

			regs.A = 0x00;
			xor_a_a.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.A = 0xFF;
			xor_a_a.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.A = 0xDA;
			regs.B = 0xAA;
			xor_a_b.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.A = 0xAA;
			regs.B = 0xAA;
			xor_a_b.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
		}
	};
}