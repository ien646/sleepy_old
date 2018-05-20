#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"
#include "TestInitMacros.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sleepy;

namespace sleepy
{
	TEST_CLASS(CpuFirmware_LD_A_RPTR)
	{
	public:
		TEST_METHOD(LD_A_RPTR_CorrectOperation)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef ld_a_pbc = instMap[0x0A];
			CpuInstructionDef ld_a_pde = instMap[0x1A];
			CpuInstructionDef ld_a_phli = instMap[0x2A];
			CpuInstructionDef ld_a_phld = instMap[0x3A];

			ADDR addr = 0x0000;

			regs.A = 0x00;
			addr = 0x01BC;
			regs.SetBC(0x01BC);
			mem.WriteByte(addr, 0xBC);
			ld_a_pbc.Call(nullptr);
			Assert::IsTrue(regs.A == 0xBC);

			regs.A = 0x00;
			addr = 0x02DE;
			regs.SetDE(0x02DE);
			mem.WriteByte(addr, 0xDE);
			ld_a_pde.Call(nullptr);
			Assert::IsTrue(regs.A == 0xDE);

			regs.A = 0x00;
			addr = 0x030F;
			regs.SetHL(0x030F);
			mem.WriteByte(addr, 0x0F);
			ld_a_phli.Call(nullptr);
			Assert::IsTrue(regs.A == 0x0F);
			Assert::IsTrue(0x0310 == regs.ReadHL());

			regs.A = 0x00;
			addr = 0x03FF;
			regs.SetHL(0x03FF);
			mem.WriteByte(addr, 0xFF);
			ld_a_phld.Call(nullptr);
			Assert::IsTrue(regs.A == 0xFF);
			Assert::IsTrue(0x03FE == regs.ReadHL());
		}
	};
}