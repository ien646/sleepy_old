#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"
#include "TestInitMacros.h"

#pragma warning(disable:4189)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sleepy;

namespace sleepy
{
	TEST_CLASS(CpuFirmware_LD_R16_D16)
	{
	public:
		TEST_METHOD(LD_R16_D16_CorrectOperation)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& ld_bc_d16 = instMap[OPCODE(0x01)];
			CpuInstructionDef& ld_de_d16 = instMap[OPCODE(0x11)];
			CpuInstructionDef& ld_hl_d16 = instMap[OPCODE(0x21)];
			CpuInstructionDef& ld_sp_d16 = instMap[OPCODE(0x31)];

			WORD args;

			regs.SetBC(0x0000);
			args = 0xBCCB;
			ld_bc_d16.Call((BYTE*)(&args));
			Assert::IsTrue(regs.ReadBC() == 0xBCCB);

			regs.SetDE(0x0000);
			args = 0xDEED;
			ld_de_d16.Call((BYTE*)(&args));
			Assert::IsTrue(regs.ReadDE() == 0xDEED);

			regs.SetHL(0x0000);
			args = 0x9889;
			ld_hl_d16.Call((BYTE*)(&args));
			Assert::IsTrue(regs.ReadHL() == 0x9889);

			regs.SP = 0x0000;
			args = 0x5775;
			ld_sp_d16.Call((BYTE*)(&args));
			Assert::IsTrue(regs.SP == 0x5775);
		}
	};
}