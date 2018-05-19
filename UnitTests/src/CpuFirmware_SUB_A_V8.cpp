#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"
#include "TestInitMacros.h"

#pragma warning(disable:4310)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace sleepy
{
	TEST_CLASS(CpuFirmware_SUB_A_V8)
	{
		TEST_METHOD(SUB_A_V8_SubtractionIsCorrect)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef sub_a_a = instMap[OPCODE(0x97)];
			CpuInstructionDef sub_a_b = instMap[OPCODE(0x90)];
			CpuInstructionDef sub_a_c = instMap[OPCODE(0x91)];
			CpuInstructionDef sub_a_d = instMap[OPCODE(0x92)];
			CpuInstructionDef sub_a_e = instMap[OPCODE(0x93)];
			CpuInstructionDef sub_a_h = instMap[OPCODE(0x94)];
			CpuInstructionDef sub_a_l = instMap[OPCODE(0x95)];
			CpuInstructionDef sub_a_phl = instMap[OPCODE(0x96)];

			BYTE expectedValue = 0x00;

			regs.A = 0xFA;
			sub_a_a.Call(nullptr);
			expectedValue = (BYTE)(0xFA - 0xFA);
			Assert::IsTrue(expectedValue == regs.A);

			regs.A = 0xFA;
			regs.B = 0x0B;
			sub_a_b.Call(nullptr);
			expectedValue = (BYTE)(0xFA - 0x0B);
			Assert::IsTrue(expectedValue == regs.A);

			regs.A = 0xFA;
			regs.C = 0x0C;
			sub_a_c.Call(nullptr);
			expectedValue = (BYTE)(0xFA - 0x0C);
			Assert::IsTrue(expectedValue == regs.A);

			regs.A = 0xFA;
			regs.D = 0x0D;
			sub_a_d.Call(nullptr);
			expectedValue = (BYTE)(0xFA - 0x0D);
			Assert::IsTrue(expectedValue == regs.A);

			regs.A = 0xFA;
			regs.E = 0x0E;
			sub_a_e.Call(nullptr);
			expectedValue = (BYTE)(0xFA - 0x0E);
			Assert::IsTrue(expectedValue == regs.A);

			regs.A = 0xFA;
			regs.H = 0xA0;
			sub_a_h.Call(nullptr);
			expectedValue = (BYTE)(0xFA - 0xA0);
			Assert::IsTrue(expectedValue == regs.A);

			regs.A = 0xFA;
			regs.L = 0xAF;
			sub_a_l.Call(nullptr);
			expectedValue = (BYTE)(0xFA - 0xAF);
			Assert::IsTrue(expectedValue == regs.A);

			ADDR addrHL = 0xF0F0;
			mem.WriteByte(addrHL, 0xAA);
			regs.SetHL(addrHL);
			regs.A = 0xFA;
			sub_a_phl.Call(nullptr);
			expectedValue = (BYTE)(0xFA - 0xAA);
			Assert::IsTrue(expectedValue == regs.A);
		}		

		TEST_METHOD(SUB_A_V8_UnderflowCorrectlyHandled)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef sub_a_a = instMap[OPCODE(0x97)];
			CpuInstructionDef sub_a_b = instMap[OPCODE(0x90)];
			CpuInstructionDef sub_a_c = instMap[OPCODE(0x91)];
			CpuInstructionDef sub_a_d = instMap[OPCODE(0x92)];
			CpuInstructionDef sub_a_e = instMap[OPCODE(0x93)];
			CpuInstructionDef sub_a_h = instMap[OPCODE(0x94)];
			CpuInstructionDef sub_a_l = instMap[OPCODE(0x95)];
			CpuInstructionDef sub_a_phl = instMap[OPCODE(0x96)];

			BYTE expectedValue = 0x00;

			regs.A = 0xFA;
			sub_a_a.Call(nullptr);
			expectedValue = (BYTE)(0xFA - 0xFA);
			Assert::IsTrue(expectedValue == regs.A);

			regs.A = 0xFA;
			regs.B = 0xFF;
			sub_a_b.Call(nullptr);
			expectedValue = (BYTE)(0xFA - 0xFF);
			Assert::IsTrue(expectedValue == regs.A);

			regs.A = 0xFA;
			regs.C = 0xFF;
			sub_a_c.Call(nullptr);
			expectedValue = (BYTE)(0xFA - 0xFF);
			Assert::IsTrue(expectedValue == regs.A);

			regs.A = 0xFA;
			regs.D = 0xFF;
			sub_a_d.Call(nullptr);
			expectedValue = (BYTE)(0xFA - 0xFF);
			Assert::IsTrue(expectedValue == regs.A);

			regs.A = 0xFA;
			regs.E = 0xFF;
			sub_a_e.Call(nullptr);
			expectedValue = (BYTE)(0xFA - 0xFF);
			Assert::IsTrue(expectedValue == regs.A);

			regs.A = 0xFA;
			regs.H = 0xFF;
			sub_a_h.Call(nullptr);
			expectedValue = (BYTE)(0xFA - 0xFF);
			Assert::IsTrue(expectedValue == regs.A);

			regs.A = 0xFA;
			regs.L = 0xFF;
			sub_a_l.Call(nullptr);
			expectedValue = (BYTE)(0xFA - 0xFF);
			Assert::IsTrue(expectedValue == regs.A);

			ADDR addrHL = 0xF0F0;
			mem.WriteByte(addrHL, 0xFF);
			regs.SetHL(addrHL);
			regs.A = 0xFA;
			sub_a_phl.Call(nullptr);
			expectedValue = (BYTE)(0xFA - 0xFF);
			Assert::IsTrue(expectedValue == regs.A);
		}

		TEST_METHOD(SUB_A_V8_FlagsAreCorrect)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef sub_a_a = instMap[OPCODE(0x97)];
			CpuInstructionDef sub_a_b = instMap[OPCODE(0x90)];
			CpuInstructionDef sub_a_c = instMap[OPCODE(0x91)];
			CpuInstructionDef sub_a_d = instMap[OPCODE(0x92)];
			CpuInstructionDef sub_a_e = instMap[OPCODE(0x93)];
			CpuInstructionDef sub_a_h = instMap[OPCODE(0x94)];
			CpuInstructionDef sub_a_l = instMap[OPCODE(0x95)];
			CpuInstructionDef sub_a_phl = instMap[OPCODE(0x96)];

			regs.A = 0x00;
			sub_a_a.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));
			Assert::IsTrue(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));

			regs.A = 0x00;
			regs.B = 0x01;
			sub_a_b.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));

			regs.A = 0x10;
			regs.B = 0x01;
			sub_a_b.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));

			regs.A = 0x11;
			regs.B = 0x01;
			sub_a_b.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
		}
	};
}