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

	TEST_CLASS(CpuFirmware_OR_A_V8)
	{
		TEST_METHOD(OR_A_V8_CorrectOperation)
		{
			System sys;
			sys.Initialize();
			auto& instMap = sys.CPU.Firmware.InstructionMap;
			auto& regs = sys.CPU.Registers;
			auto& mem = sys.Memory;
			memset(mem.data(), 0, (0xFFFF * sizeof(BYTE)));
			regs.ZeroRegisters(true);

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
			Assert::IsTrue(0xFF == regs.A);

			regs.A = 0x00;
			or_a_a.Call(nullptr);
			Assert::IsTrue(0x00 == regs.A);

			regs.A = 0xFF;
			regs.B = 0xDD;
			or_a_b.Call(nullptr);
			Assert::IsTrue((0xFF | 0xDD) == regs.A);

			regs.A = 0x00;
			regs.B = 0xDD;
			or_a_b.Call(nullptr);
			Assert::IsTrue((0x00 | 0xDD) == regs.A);
		}

		TEST_METHOD(OR_A_V8_FlagsAreCorrect)
		{
			System sys;
			sys.Initialize();
			auto& instMap = sys.CPU.Firmware.InstructionMap;
			auto& regs = sys.CPU.Registers;
			auto& mem = sys.Memory;
			memset(mem.data(), 0, (0xFFFF * sizeof(BYTE)));
			regs.ZeroRegisters(true);

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