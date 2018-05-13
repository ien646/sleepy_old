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

	TEST_CLASS(CpuFirmware_AND_A_V8)
	{
		TEST_METHOD(AND_A_V8_CorrectOperation)
		{
			System sys;
			sys.Initialize();
			auto& instMap = sys.CPU.Firmware.InstructionMap;
			auto& regs = sys.CPU.Registers;
			auto& mem = sys.Memory;
			memset(mem.data(), 0, (0xFFFF * sizeof(BYTE)));
			regs.ZeroRegisters(true);

			CpuInstructionDef and_a_a = instMap[OPCODE(0xA7)];
			CpuInstructionDef and_a_b = instMap[OPCODE(0xA0)];
			CpuInstructionDef and_a_c = instMap[OPCODE(0xA1)];
			CpuInstructionDef and_a_d = instMap[OPCODE(0xA2)];
			CpuInstructionDef and_a_e = instMap[OPCODE(0xA3)];
			CpuInstructionDef and_a_h = instMap[OPCODE(0xA4)];
			CpuInstructionDef and_a_l = instMap[OPCODE(0xA5)];
			CpuInstructionDef and_a_phl = instMap[OPCODE(0xA6)];

			regs.A = 0xFF;
			and_a_a.Call(nullptr);
			Assert::IsTrue(0xFF == regs.A);

			regs.A = 0x00;
			and_a_a.Call(nullptr);
			Assert::IsTrue(0x00 == regs.A);

			regs.A = 0xFF;
			regs.B = 0xDD;
			and_a_b.Call(nullptr);
			Assert::IsTrue((0xFF & 0xDD) == regs.A);

			regs.A = 0x00;
			regs.B = 0xDD;
			and_a_b.Call(nullptr);
			Assert::IsTrue((0x00 & 0xDD) == regs.A);
		}

		TEST_METHOD(AND_A_V8_FlagsAreCorrect)
		{
			System sys;
			sys.Initialize();
			auto& instMap = sys.CPU.Firmware.InstructionMap;
			auto& regs = sys.CPU.Registers;
			auto& mem = sys.Memory;
			memset(mem.data(), 0, (0xFFFF * sizeof(BYTE)));
			regs.ZeroRegisters(true);

			CpuInstructionDef and_a_a = instMap[OPCODE(0xA7)];
			CpuInstructionDef and_a_b = instMap[OPCODE(0xA0)];
			CpuInstructionDef and_a_c = instMap[OPCODE(0xA1)];
			CpuInstructionDef and_a_d = instMap[OPCODE(0xA2)];
			CpuInstructionDef and_a_e = instMap[OPCODE(0xA3)];
			CpuInstructionDef and_a_h = instMap[OPCODE(0xA4)];
			CpuInstructionDef and_a_l = instMap[OPCODE(0xA5)];
			CpuInstructionDef and_a_phl = instMap[OPCODE(0xA6)];

			regs.A = 0xFF;
			and_a_a.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));

			regs.A = 0x00;
			and_a_a.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));

			regs.A = 0x00;
			regs.B = 0x00;
			and_a_b.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));

			regs.A = 0xFF;
			regs.B = 0x00;
			and_a_b.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));

			regs.A = 0xFF;
			regs.B = 0x0F;
			and_a_b.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));

			regs.A = 0xFF;
			regs.B = 0x10;
			and_a_b.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));
		}
	};
}