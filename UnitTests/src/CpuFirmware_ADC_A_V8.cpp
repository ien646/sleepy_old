#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"
#include "TestInitMacros.h"

#pragma warning(disable:4310)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace sleepy
{
	TEST_CLASS(CpuFirmware_ADC_A_V8)
	{
		TEST_METHOD(ADC_A_V8_AdditionIsCorrect_NoFlags)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef adc_a_a = instMap[OPCODE(0x8F)];
			CpuInstructionDef adc_a_b = instMap[OPCODE(0x88)];
			CpuInstructionDef adc_a_c = instMap[OPCODE(0x89)];
			CpuInstructionDef adc_a_d = instMap[OPCODE(0x8A)];
			CpuInstructionDef adc_a_e = instMap[OPCODE(0x8B)];
			CpuInstructionDef adc_a_h = instMap[OPCODE(0x8C)];
			CpuInstructionDef adc_a_l = instMap[OPCODE(0x8D)];
			CpuInstructionDef adc_a_phl = instMap[OPCODE(0x8E)];

			regs.ResetAllFlags();
			regs.A = 0x0A;
			adc_a_a.Call(nullptr);
			Assert::IsTrue((0x0A + 0x0A) == regs.A);

			regs.ResetAllFlags();
			regs.A = 0x0A;
			regs.B = 0x0B;
			adc_a_b.Call(nullptr);
			Assert::IsTrue((0x0A + 0x0B) == regs.A);

			regs.ResetAllFlags();
			regs.A = 0x0A;
			regs.C = 0x0C;
			adc_a_c.Call(nullptr);
			Assert::IsTrue((0x0A + 0x0C) == regs.A);

			regs.ResetAllFlags();
			regs.A = 0x0A;
			regs.D = 0x0D;
			adc_a_d.Call(nullptr);
			Assert::IsTrue((0x0A + 0x0D) == regs.A);

			regs.ResetAllFlags();
			regs.A = 0x0A;
			regs.E = 0x0E;
			adc_a_e.Call(nullptr);
			Assert::IsTrue((0x0A + 0x0E) == regs.A);

			regs.ResetAllFlags();
			regs.A = 0x0A;
			regs.H = 0xA0;
			adc_a_h.Call(nullptr);
			Assert::IsTrue((0x0A + 0xA0) == regs.A);

			regs.ResetAllFlags();
			regs.A = 0x0A;
			regs.L = 0xAF;
			adc_a_l.Call(nullptr);
			Assert::IsTrue((0x0A + 0xAF) == regs.A);

			regs.ResetAllFlags();
			ADDR addrHL = 0xF0F0;
			mem.WriteByte(addrHL, 0xAA);
			regs.SetHL(addrHL);
			regs.A = 0x0A;
			adc_a_phl.Call(nullptr);
			Assert::IsTrue((0x0A + 0xAA) == regs.A);
		}

		TEST_METHOD(ADC_A_V8_AdditionIsCorrect_WithFlags)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef adc_a_a = instMap[OPCODE(0x8F)];
			CpuInstructionDef adc_a_b = instMap[OPCODE(0x88)];
			CpuInstructionDef adc_a_c = instMap[OPCODE(0x89)];
			CpuInstructionDef adc_a_d = instMap[OPCODE(0x8A)];
			CpuInstructionDef adc_a_e = instMap[OPCODE(0x8B)];
			CpuInstructionDef adc_a_h = instMap[OPCODE(0x8C)];
			CpuInstructionDef adc_a_l = instMap[OPCODE(0x8D)];
			CpuInstructionDef adc_a_phl = instMap[OPCODE(0x8E)];

			regs.ResetAllFlags();
			regs.SetFlag(FLAG_CARRY);
			regs.A = 0x0A;
			adc_a_a.Call(nullptr);
			Assert::IsTrue((0x0A + 0x0A + 1) == regs.A);

			regs.ResetAllFlags();
			regs.SetFlag(FLAG_CARRY);
			regs.A = 0x0A;
			regs.B = 0x0B;
			adc_a_b.Call(nullptr);
			Assert::IsTrue((0x0A + 0x0B + 1) == regs.A);

			regs.ResetAllFlags();
			regs.SetFlag(FLAG_CARRY);
			regs.A = 0x0A;
			regs.C = 0x0C;
			adc_a_c.Call(nullptr);
			Assert::IsTrue((0x0A + 0x0C + 1) == regs.A);

			regs.ResetAllFlags();
			regs.SetFlag(FLAG_CARRY);
			regs.A = 0x0A;
			regs.D = 0x0D;
			adc_a_d.Call(nullptr);
			Assert::IsTrue((0x0A + 0x0D + 1) == regs.A);

			regs.ResetAllFlags();
			regs.SetFlag(FLAG_CARRY);
			regs.A = 0x0A;
			regs.E = 0x0E;
			adc_a_e.Call(nullptr);
			Assert::IsTrue((0x0A + 0x0E + 1) == regs.A);

			regs.ResetAllFlags();
			regs.SetFlag(FLAG_CARRY);
			regs.A = 0x0A;
			regs.H = 0xA0;
			adc_a_h.Call(nullptr);
			Assert::IsTrue((0x0A + 0xA0 + 1) == regs.A);

			regs.ResetAllFlags();
			regs.SetFlag(FLAG_CARRY);
			regs.A = 0x0A;
			regs.L = 0xAF;
			adc_a_l.Call(nullptr);
			Assert::IsTrue((0x0A + 0xAF + 1) == regs.A);

			regs.ResetAllFlags();
			regs.SetFlag(FLAG_CARRY);
			ADDR addrHL = 0xF0F0;
			mem.WriteByte(addrHL, 0xAA);
			regs.SetHL(addrHL);
			regs.A = 0x0A;
			adc_a_phl.Call(nullptr);
			Assert::IsTrue((0x0A + 0xAA + 1) == regs.A);
		}

		TEST_METHOD(ADC_A_V8_FlagsAreCorrect)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef adc_a_a = instMap[OPCODE(0x8F)];
			CpuInstructionDef adc_a_b = instMap[OPCODE(0x88)];
			CpuInstructionDef adc_a_c = instMap[OPCODE(0x89)];
			CpuInstructionDef adc_a_d = instMap[OPCODE(0x8A)];
			CpuInstructionDef adc_a_e = instMap[OPCODE(0x8B)];
			CpuInstructionDef adc_a_h = instMap[OPCODE(0x8C)];
			CpuInstructionDef adc_a_l = instMap[OPCODE(0x8D)];
			CpuInstructionDef adc_a_phl = instMap[OPCODE(0x8E)];

			regs.ResetAllFlags();

			regs.ResetFlag(FLAG_CARRY);
			regs.A = 0x00;
			adc_a_a.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.SetFlag(FLAG_CARRY);
			regs.A = 0x00;
			adc_a_a.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.ResetFlag(FLAG_CARRY);
			regs.A = 0x0F;
			regs.B = 0x01;
			adc_a_b.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.SetFlag(FLAG_CARRY);
			regs.A = 0x0F;
			regs.B = 0x00;
			adc_a_b.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.ResetFlag(FLAG_CARRY);
			regs.A = 0xFF;
			regs.B = 0x00;
			adc_a_b.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.SetFlag(FLAG_CARRY);
			regs.A = 0xFF;
			regs.B = 0x00;
			adc_a_b.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_ZERO));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
		}
	};
}