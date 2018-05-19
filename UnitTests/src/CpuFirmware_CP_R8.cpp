#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"
#include "TestInitMacros.h"

#pragma warning(disable:4310)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace sleepy
{
	TEST_CLASS(CpuFirmware_CP_V8)
	{
		TEST_METHOD(CP_V8_FlagsAreCorrect)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef cp_a = instMap[OPCODE(0xBF)];
			CpuInstructionDef cp_b = instMap[OPCODE(0xB8)];
			CpuInstructionDef cp_c = instMap[OPCODE(0xB9)];
			CpuInstructionDef cp_d = instMap[OPCODE(0xBA)];
			CpuInstructionDef cp_e = instMap[OPCODE(0xBB)];
			CpuInstructionDef cp_h = instMap[OPCODE(0xBC)];
			CpuInstructionDef cp_l = instMap[OPCODE(0xBD)];
			CpuInstructionDef cp_phl = instMap[OPCODE(0xBE)];
			CpuInstructionDef cp_d8 = instMap[OPCODE(0xFE)];

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