#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"

#pragma warning(disable:4310)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace sleepy
{
	const Registers::FLAG FLAG_SUB = Registers::FLAG::SUB;
	const Registers::FLAG FLAG_ZERO = Registers::FLAG::ZERO;
	const Registers::FLAG FLAG_HCARRY = Registers::FLAG::HALF_CARRY;
	const Registers::FLAG FLAG_CARRY = Registers::FLAG::CARRY;

	TEST_CLASS(CpuFirmware_ADD_A_V8)
	{
		TEST_METHOD(ADD_A_V8_AdditionIsCorrect)
		{
			System sys;
			sys.Initialize();
			auto& instMap = sys.CPU.Firmware.InstructionMap;
			auto& regs = sys.CPU.Registers;
			auto& mem = sys.Memory;
			memset(mem.data(), 0, (0xFFFF * sizeof(BYTE)));
			regs.ZeroRegisters(true);			

			CpuInstructionDef add_a_a = instMap[OPCODE(0x87)];
			CpuInstructionDef add_a_b = instMap[OPCODE(0x80)];
			CpuInstructionDef add_a_c = instMap[OPCODE(0x81)];
			CpuInstructionDef add_a_d = instMap[OPCODE(0x82)];
			CpuInstructionDef add_a_e = instMap[OPCODE(0x83)];
			CpuInstructionDef add_a_h = instMap[OPCODE(0x84)];
			CpuInstructionDef add_a_l = instMap[OPCODE(0x85)];
			CpuInstructionDef add_a_phl = instMap[OPCODE(0x86)];

			regs.A = 0x0A;
			add_a_a.Call(nullptr);
			Assert::IsTrue((0x0A + 0x0A) == regs.A);

			regs.A = 0x0A;
			regs.B = 0x0B;
			add_a_b.Call(nullptr);
			Assert::IsTrue((0x0A + 0x0B) == regs.A);

			regs.A = 0x0A;
			regs.C = 0x0C;
			add_a_c.Call(nullptr);
			Assert::IsTrue((0x0A + 0x0C) == regs.A);

			regs.A = 0x0A;
			regs.D = 0x0D;
			add_a_d.Call(nullptr);
			Assert::IsTrue((0x0A + 0x0D) == regs.A);

			regs.A = 0x0A;
			regs.E = 0x0E;
			add_a_e.Call(nullptr);
			Assert::IsTrue((0x0A + 0x0E) == regs.A);

			regs.A = 0x0A;
			regs.H = 0xA0;
			add_a_h.Call(nullptr);
			Assert::IsTrue((0x0A + 0xA0) == regs.A);

			regs.A = 0x0A;
			regs.L = 0xAF;
			add_a_l.Call(nullptr);
			Assert::IsTrue((0x0A + 0xAF) == regs.A);

			ADDR addrHL = 0xF0F0;
			mem.WriteByte(addrHL, 0xAA);
			regs.SetHL(addrHL);
			regs.A = 0x0A;
			add_a_phl.Call(nullptr);
			Assert::IsTrue((0x0A + 0xAA) == regs.A);
		}

		TEST_METHOD(ADD_A_V8_OverflowCorrectlyHandled)
		{
			System sys;
			sys.Initialize();
			auto& instMap = sys.CPU.Firmware.InstructionMap;
			auto& regs = sys.CPU.Registers;
			auto& mem = sys.Memory;
			memset(mem.data(), 0, (0xFFFF * sizeof(BYTE)));
			regs.ZeroRegisters(true);

			CpuInstructionDef add_a_a = instMap[OPCODE(0x87)];
			CpuInstructionDef add_a_b = instMap[OPCODE(0x80)];
			CpuInstructionDef add_a_c = instMap[OPCODE(0x81)];
			CpuInstructionDef add_a_d = instMap[OPCODE(0x82)];
			CpuInstructionDef add_a_e = instMap[OPCODE(0x83)];
			CpuInstructionDef add_a_h = instMap[OPCODE(0x84)];
			CpuInstructionDef add_a_l = instMap[OPCODE(0x85)];
			CpuInstructionDef add_a_phl = instMap[OPCODE(0x86)];

			BYTE expectedValue = 0x00;

			regs.A = 0xF0;
			add_a_a.Call(nullptr);
			expectedValue = (BYTE)(0xF0 + 0xF0);
			Assert::IsTrue(expectedValue == regs.A);

			regs.A = 0xF0;
			regs.B = 0x0B;
			add_a_b.Call(nullptr);
			expectedValue = (BYTE)(0xF0 + 0x0B);
			Assert::IsTrue(expectedValue == regs.A);

			regs.A = 0xF0;
			regs.C = 0x0C;
			add_a_c.Call(nullptr);
			expectedValue = (BYTE)(0xF0 + 0x0C);
			Assert::IsTrue(expectedValue == regs.A);

			regs.A = 0xF0;
			regs.D = 0x0D;
			add_a_d.Call(nullptr);
			expectedValue = (BYTE)(0xF0 + 0x0D);
			Assert::IsTrue(expectedValue == regs.A);

			regs.A = 0xF0;
			regs.E = 0x0E;
			add_a_e.Call(nullptr);
			expectedValue = (BYTE)(0xF0 + 0x0E);
			Assert::IsTrue(expectedValue == regs.A);

			regs.A = 0xF0;
			regs.H = 0x0F;
			add_a_h.Call(nullptr);
			expectedValue = (BYTE)(0xF0 + 0x0F);
			Assert::IsTrue(expectedValue == regs.A);

			regs.A = 0xF0;
			regs.L = 0xFF;
			add_a_l.Call(nullptr);
			expectedValue = (BYTE)(0xF0 + 0xFF);
			Assert::IsTrue(expectedValue == regs.A);

			ADDR addrHL = 0xF0F0;
			mem.WriteByte(addrHL, 0xFA);
			regs.SetHL(addrHL);
			regs.A = 0xF0;
			add_a_phl.Call(nullptr);
			expectedValue = (BYTE)(0xF0 + 0xFA);
			Assert::IsTrue(expectedValue == regs.A);
		}

		TEST_METHOD(ADD_A_V8_FlagsAreCorrect)
		{
			System sys;
			sys.Initialize();
			auto& instMap = sys.CPU.Firmware.InstructionMap;
			auto& regs = sys.CPU.Registers;
			auto& mem = sys.Memory;
			memset(mem.data(), 0, (0xFFFF * sizeof(BYTE)));
			regs.ZeroRegisters(true);

			CpuInstructionDef add_a_a = instMap[OPCODE(0x87)];
			CpuInstructionDef add_a_b = instMap[OPCODE(0x80)];
			CpuInstructionDef add_a_c = instMap[OPCODE(0x81)];
			CpuInstructionDef add_a_d = instMap[OPCODE(0x82)];
			CpuInstructionDef add_a_e = instMap[OPCODE(0x83)];
			CpuInstructionDef add_a_h = instMap[OPCODE(0x84)];
			CpuInstructionDef add_a_l = instMap[OPCODE(0x85)];
			CpuInstructionDef add_a_phl = instMap[OPCODE(0x86)];

			// Zero add zero sets only flag_zero
			regs.ResetAllFlags();
			regs.A = 0x00;
			add_a_a.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));

			// 1 + 1 sets no flags
			regs.ResetAllFlags();
			regs.A = 0x01;
			add_a_a.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));

			// 10 + 10 > 15, sets halfcarry
			regs.ResetAllFlags();
			regs.A = 0x0A;
			add_a_a.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));

			// 160 + 160 > 255, sets halfcarry and carry
			regs.ResetAllFlags();
			regs.A = 0xA0;
			add_a_a.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));
		}
	};
}