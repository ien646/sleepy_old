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

	TEST_CLASS(CpuFirmware_CP_V8)
	{
		TEST_METHOD(CP_V8_FlagsAreCorrect)
		{
			System sys;
			sys.Initialize();
			auto& instMap = sys.CPU.Firmware.InstructionMap;
			auto& regs = sys.CPU.Registers;
			auto& mem = sys.Memory;
			memset(mem.data(), 0, (0xFFFF * sizeof(BYTE)));
			regs.ZeroRegisters(true);

			CpuInstructionDef cp_a = instMap[OPCODE(0xBF)];
			CpuInstructionDef cp_b = instMap[OPCODE(0xB8)];
			CpuInstructionDef cp_c = instMap[OPCODE(0xB9)];
			CpuInstructionDef cp_d = instMap[OPCODE(0xBA)];
			CpuInstructionDef cp_e = instMap[OPCODE(0xBB)];
			CpuInstructionDef cp_h = instMap[OPCODE(0xBC)];
			CpuInstructionDef cp_l = instMap[OPCODE(0xBD)];
			CpuInstructionDef cp_phl = instMap[OPCODE(0xBE)];

			regs.A = 0x00;
			cp_a.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));
			Assert::IsTrue(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));

			regs.A = 0x00;
			regs.B = 0x01;
			cp_b.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));

			regs.A = 0x10;
			regs.B = 0x01;
			cp_b.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));

			regs.A = 0x11;
			regs.B = 0x01;
			cp_b.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY)); 
		}
	};
}