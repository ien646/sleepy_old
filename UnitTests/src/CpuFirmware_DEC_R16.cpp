#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"
#include "TestInitMacros.h"

#pragma warning(disable:4189)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sleepy;

namespace sleepy
{
	TEST_CLASS(CpuFirmware_DEC_R16)
	{
	public:
		TEST_METHOD(DEC_R16_CorrectOperation)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& dec_bc = instMap[OPCODE(0x0B)];
			CpuInstructionDef& dec_de = instMap[OPCODE(0x1B)];
			CpuInstructionDef& dec_hl = instMap[OPCODE(0x2B)];
			CpuInstructionDef& dec_sp = instMap[OPCODE(0x3B)];

			regs.SetBC(0x0000);
			dec_bc.Call(nullptr);
			Assert::IsTrue(regs.ReadBC() == 0xFFFF);
			regs.SetBC(0x0100);
			dec_bc.Call(nullptr);
			Assert::IsTrue(regs.ReadBC() == 0x00FF);
			regs.SetBC(0x0001);
			dec_bc.Call(nullptr);
			Assert::IsTrue(regs.ReadBC() == 0x0000);

			regs.SetDE(0x0000);
			dec_de.Call(nullptr);
			Assert::IsTrue(regs.ReadDE() == 0xFFFF);
			regs.SetDE(0x0100);
			dec_de.Call(nullptr);
			Assert::IsTrue(regs.ReadDE() == 0x00FF);
			regs.SetDE(0x0001);
			dec_de.Call(nullptr);
			Assert::IsTrue(regs.ReadDE() == 0x0000);

			regs.SetHL(0x0000);
			dec_hl.Call(nullptr);
			Assert::IsTrue(regs.ReadHL() == 0xFFFF);
			regs.SetHL(0x0100);
			dec_hl.Call(nullptr);
			Assert::IsTrue(regs.ReadHL() == 0x00FF);
			regs.SetHL(0x0001);
			dec_hl.Call(nullptr);
			Assert::IsTrue(regs.ReadHL() == 0x0000);

			regs.SP = (0x0000);
			dec_sp.Call(nullptr);
			Assert::IsTrue(regs.SP == 0xFFFF);
			regs.SP = (0x0100);
			dec_sp.Call(nullptr);
			Assert::IsTrue(regs.SP == 0x00FF);
			regs.SP = (0x0001);
			dec_sp.Call(nullptr);
			Assert::IsTrue(regs.SP == 0x0000);
		}
	};
}