#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"
#include "TestInitMacros.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sleepy;

#pragma warning(disable:4189)

namespace sleepy
{
	TEST_CLASS(CpuFirmware_DEC_R8)
	{
	public:
		TEST_METHOD(DEC_R8_CorrectOperation)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& dec_a = instMap[OPCODE(0x3D)];
			CpuInstructionDef& dec_b = instMap[OPCODE(0x05)];
			CpuInstructionDef& dec_c = instMap[OPCODE(0x0D)];
			CpuInstructionDef& dec_d = instMap[OPCODE(0x15)];
			CpuInstructionDef& dec_e = instMap[OPCODE(0x1D)];
			CpuInstructionDef& dec_h = instMap[OPCODE(0x25)];
			CpuInstructionDef& dec_l = instMap[OPCODE(0x2D)];
			CpuInstructionDef& dec_phl = instMap[OPCODE(0x35)];

			regs.A = 0x01;
			dec_a.Call(nullptr);
			Assert::IsTrue(0x00 == regs.A);

			regs.A = 0x00;
			dec_a.Call(nullptr);
			Assert::IsTrue(0xFF == regs.A);
		}

		TEST_METHOD(DEC_R8_CorrectFlags)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& dec_a = instMap[OPCODE(0x3D)];
			CpuInstructionDef& dec_b = instMap[OPCODE(0x05)];
			CpuInstructionDef& dec_c = instMap[OPCODE(0x0D)];
			CpuInstructionDef& dec_d = instMap[OPCODE(0x15)];
			CpuInstructionDef& dec_e = instMap[OPCODE(0x1D)];
			CpuInstructionDef& dec_h = instMap[OPCODE(0x25)];
			CpuInstructionDef& dec_l = instMap[OPCODE(0x2D)];
			CpuInstructionDef& dec_phl = instMap[OPCODE(0x35)];

			regs.A = 0x00;
			dec_a.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));

			regs.A = 0x01;
			dec_a.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));
			Assert::IsTrue(regs.ReadFlag(FLAG_ZERO));

			regs.A = 0x0F;
			dec_a.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));

			regs.A = 0xFF;
			dec_a.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
		}
	};
}