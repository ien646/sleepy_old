#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"
#include "TestInitMacros.h"

#pragma warning(disable:4189)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sleepy;

namespace sleepy
{
	TEST_CLASS(CpuFirmware_INC_R16)
	{
	public:
		TEST_METHOD(INC_R16_CorrectOperation)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& inc_bc = instMap[OPCODE(0x03)];
			CpuInstructionDef& inc_de = instMap[OPCODE(0x13)];
			CpuInstructionDef& inc_hl = instMap[OPCODE(0x23)];
			CpuInstructionDef& inc_sp = instMap[OPCODE(0x33)];

			regs.SetBC(0x0000);
			inc_bc.Call(nullptr);
			Assert::IsTrue(regs.ReadBC() == 0x0001);
			regs.SetBC(0x00FF);
			inc_bc.Call(nullptr);
			Assert::IsTrue(regs.ReadBC() == 0x0100);
			regs.SetBC(0xFFFF);
			inc_bc.Call(nullptr);
			Assert::IsTrue(regs.ReadBC() == 0x0000);

			regs.SetDE(0x0000);
			inc_de.Call(nullptr);
			Assert::IsTrue(regs.ReadDE() == 0x0001);
			regs.SetDE(0x00FF);
			inc_de.Call(nullptr);
			Assert::IsTrue(regs.ReadDE() == 0x0100);
			regs.SetDE(0xFFFF);
			inc_de.Call(nullptr);
			Assert::IsTrue(regs.ReadDE() == 0x0000);

			regs.SetHL(0x0000);
			inc_hl.Call(nullptr);
			Assert::IsTrue(regs.ReadHL() == 0x0001);
			regs.SetHL(0x00FF);
			inc_hl.Call(nullptr);
			Assert::IsTrue(regs.ReadHL() == 0x0100);
			regs.SetHL(0xFFFF);
			inc_hl.Call(nullptr);
			Assert::IsTrue(regs.ReadHL() == 0x0000);

			regs.SP = (0x0000);
			inc_sp.Call(nullptr);
			Assert::IsTrue(regs.SP == 0x0001);
			regs.SP = (0x00FF);
			inc_sp.Call(nullptr);
			Assert::IsTrue(regs.SP == 0x0100);
			regs.SP = (0xFFFF);
			inc_sp.Call(nullptr);
			Assert::IsTrue(regs.SP == 0x0000);
		}
	};
}