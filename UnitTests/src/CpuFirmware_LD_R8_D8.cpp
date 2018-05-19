#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"
#include "TestInitMacros.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sleepy;

namespace sleepy
{
	TEST_CLASS(CpuFirmware_LD_R8_D8)
	{
	public:
		TEST_METHOD(LD_R8_D8_CorrectOperation)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef ld_a_d8 = instMap[OPCODE(0x3E)];
			CpuInstructionDef ld_b_d8 = instMap[OPCODE(0x06)];
			CpuInstructionDef ld_c_d8 = instMap[OPCODE(0x0E)];
			CpuInstructionDef ld_d_d8 = instMap[OPCODE(0x16)];
			CpuInstructionDef ld_e_d8 = instMap[OPCODE(0x1E)];
			CpuInstructionDef ld_h_d8 = instMap[OPCODE(0x26)];
			CpuInstructionDef ld_l_d8 = instMap[OPCODE(0x2E)];
			CpuInstructionDef ld_phl_d8 = instMap[OPCODE(0x36)];

			BYTE d8 = 0xAF;

			ld_a_d8.Call(&d8); 
			ld_b_d8.Call(&d8); 
			ld_c_d8.Call(&d8); 
			ld_d_d8.Call(&d8); 
			ld_e_d8.Call(&d8); 
			ld_h_d8.Call(&d8); 
			ld_l_d8.Call(&d8); 

			Assert::IsTrue(regs.A == 0xAF);
			Assert::IsTrue(regs.B == 0xAF);
			Assert::IsTrue(regs.C == 0xAF);
			Assert::IsTrue(regs.D == 0xAF);
			Assert::IsTrue(regs.E == 0xAF);
			Assert::IsTrue(regs.H == 0xAF);
			Assert::IsTrue(regs.L == 0xAF);

			ADDR phl = 0xFAFA;
			regs.SetHL(phl);
			ld_phl_d8.Call(&d8);
			BYTE mval = mem.ReadByte(regs.ReadHL());
			Assert::IsTrue(mval == 0xAF);
		}
	};
}