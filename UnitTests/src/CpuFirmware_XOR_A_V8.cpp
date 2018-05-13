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

	TEST_CLASS(CpuFirmware_XOR_A_V8)
	{
		TEST_METHOD(XOR_A_V8_CorrectOperation)
		{
			System sys;
			sys.Initialize();
			auto& instMap = sys.CPU.Firmware.InstructionMap;
			auto& regs = sys.CPU.Registers;
			auto& mem = sys.Memory;
			memset(mem.data(), 0, (0xFFFF * sizeof(BYTE)));
			regs.ZeroRegisters(true);

			CpuInstructionDef xor_a_a = instMap[OPCODE(0xAF)];
			CpuInstructionDef xor_a_b = instMap[OPCODE(0xA8)];
			CpuInstructionDef xor_a_c = instMap[OPCODE(0xA9)];
			CpuInstructionDef xor_a_d = instMap[OPCODE(0xAA)];
			CpuInstructionDef xor_a_e = instMap[OPCODE(0xAB)];
			CpuInstructionDef xor_a_h = instMap[OPCODE(0xAC)];
			CpuInstructionDef xor_a_l = instMap[OPCODE(0xAD)];
			CpuInstructionDef xor_a_phl = instMap[OPCODE(0xAE)];

			regs.A = 0xFF;
			xor_a_a.Call(nullptr);
			Assert::IsTrue((0xFF ^ 0xFF) == regs.A);

			regs.A = 0x00;
			xor_a_a.Call(nullptr);
			Assert::IsTrue((0x00 ^ 0x00) == regs.A);

			regs.A = 0x00;
			regs.B = 0xFF;
			xor_a_b.Call(nullptr);
			Assert::IsTrue((0x00 ^ 0xFF) == regs.A);

			regs.A = 0xDD;
			regs.B = 0xAA;
			xor_a_b.Call(nullptr);
			Assert::IsTrue((0xDD ^ 0xAA) == regs.A);
		}

		TEST_METHOD(XOR_A_V8_FlagsAreCorrect)
		{
			System sys;
			sys.Initialize();
			auto& instMap = sys.CPU.Firmware.InstructionMap;
			auto& regs = sys.CPU.Registers;
			auto& mem = sys.Memory;
			memset(mem.data(), 0, (0xFFFF * sizeof(BYTE)));
			regs.ZeroRegisters(true);

			CpuInstructionDef xor_a_a = instMap[OPCODE(0xAF)];
			CpuInstructionDef xor_a_b = instMap[OPCODE(0xA8)];
			CpuInstructionDef xor_a_c = instMap[OPCODE(0xA9)];
			CpuInstructionDef xor_a_d = instMap[OPCODE(0xAA)];
			CpuInstructionDef xor_a_e = instMap[OPCODE(0xAB)];
			CpuInstructionDef xor_a_h = instMap[OPCODE(0xAC)];
			CpuInstructionDef xor_a_l = instMap[OPCODE(0xAD)];
			CpuInstructionDef xor_a_phl = instMap[OPCODE(0xAE)];

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