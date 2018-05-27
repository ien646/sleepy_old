#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"
#include "TestInitMacros.h"

#pragma warning(disable:4310)
#pragma warning(disable:4189)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace sleepy
{
	TEST_CLASS(CpuFirmware_RST)
	{
		TEST_METHOD(RST_Correct_PC_Value)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& rst_00 = instMap[OPCODE(0xC7)];
			CpuInstructionDef& rst_08 = instMap[OPCODE(0xCF)];
			CpuInstructionDef& rst_10 = instMap[OPCODE(0xD7)];
			CpuInstructionDef& rst_18 = instMap[OPCODE(0xDF)];
			CpuInstructionDef& rst_20 = instMap[OPCODE(0xE7)];
			CpuInstructionDef& rst_28 = instMap[OPCODE(0xEF)];
			CpuInstructionDef& rst_30 = instMap[OPCODE(0xF7)];
			CpuInstructionDef& rst_38 = instMap[OPCODE(0xFF)];

			regs.PC = 0xFFFF;
			rst_00.Call(nullptr);
			Assert::IsTrue(regs.PC == 0x0000);

			regs.PC = 0xFFFF;
			rst_08.Call(nullptr);
			Assert::IsTrue(regs.PC == 0x0008);

			regs.PC = 0xFFFF;
			rst_10.Call(nullptr);
			Assert::IsTrue(regs.PC == 0x0010);

			regs.PC = 0xFFFF;
			rst_18.Call(nullptr);
			Assert::IsTrue(regs.PC == 0x0018);

			regs.PC = 0xFFFF;
			rst_20.Call(nullptr);
			Assert::IsTrue(regs.PC == 0x0020);

			regs.PC = 0xFFFF;
			rst_28.Call(nullptr);
			Assert::IsTrue(regs.PC == 0x0028);

			regs.PC = 0xFFFF;
			rst_30.Call(nullptr);
			Assert::IsTrue(regs.PC == 0x0030);

			regs.PC = 0xFFFF;
			rst_38.Call(nullptr);
			Assert::IsTrue(regs.PC == 0x0038);
		}
	};
}