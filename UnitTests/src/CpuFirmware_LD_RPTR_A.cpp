#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"
#include "TestInitMacros.h"

#pragma warning(disable:4189)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sleepy;

namespace sleepy
{
	TEST_CLASS(CpuFirmware_LD_RPTR_A)
	{
	public:
		TEST_METHOD(LD_RPTR_A_CorrectOperation)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& ld_pbc_a = instMap[OPCODE(0x02)];
			CpuInstructionDef& ld_pde_a = instMap[OPCODE(0x12)];
			CpuInstructionDef& ld_phli_a = instMap[OPCODE(0x22)];
			CpuInstructionDef& ld_phld_a = instMap[OPCODE(0x32)];

			BYTE val = 0x00;

			regs.A = 0xBC;
			regs.SetBC(0x01BC);
			ld_pbc_a.Call(nullptr);
			val = mem.ReadByte(0x01BC);
			Assert::IsTrue(0xBC == val);

			regs.A = 0xDE;
			regs.SetDE(0x02DE);
			ld_pde_a.Call(nullptr);
			val = mem.ReadByte(0x02DE);
			Assert::IsTrue(0xDE == val);

			regs.A = 0x0F;
			regs.SetHL(0x0F0F);
			ld_phli_a.Call(nullptr);
			val = mem.ReadByte(0x0F0F);
			Assert::IsTrue(0x0F == val);
			Assert::IsTrue(0x0F10 == regs.ReadHL());

			regs.A = 0xF0;
			regs.SetHL(0xF0F0);
			ld_phld_a.Call(nullptr);
			val = mem.ReadByte(0xF0F0);
			Assert::IsTrue(0xF0 == val);
			Assert::IsTrue((0xF0F0 - 1) == regs.ReadHL());
		}
	};
}