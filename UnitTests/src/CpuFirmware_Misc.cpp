#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"
#include "TestInitMacros.h"

#pragma warning(disable:4189)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sleepy;

namespace sleepy
{
	TEST_CLASS(CpuFirmware_LD_R8_D8)
	{
	public:
		TEST_METHOD(EI_EnablesInterrupts)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& ei = instMap[OPCODE(0xFB)];

			sys.CPU.DisableInterrupts();
			ei.Call(nullptr);
			Assert::IsTrue(sys.CPU.AreInterruptsEnabled());

			sys.CPU.EnableInterrupts();
			ei.Call(nullptr);
			Assert::IsTrue(sys.CPU.AreInterruptsEnabled());
		}

		TEST_METHOD(DI_DisablesInterrupts)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& di = instMap[OPCODE(0xF3)];

			sys.CPU.DisableInterrupts();
			di.Call(nullptr);
			Assert::IsFalse(sys.CPU.AreInterruptsEnabled());

			sys.CPU.EnableInterrupts();
			di.Call(nullptr);
			Assert::IsFalse(sys.CPU.AreInterruptsEnabled());
		}

		TEST_METHOD(CPL_CorrectOperationAndFlags)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& cpl = instMap[OPCODE(0x2F)];

			regs.A = 0x00;
			cpl.Call(nullptr);
			Assert::IsTrue(regs.A == 0xFF);
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));

			regs.A = 0x44;
			cpl.Call(nullptr);
			Assert::IsTrue(regs.A == (0xFF ^ 0x44));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_SUB));
		}

		TEST_METHOD(CCF_CorrectOperationAndFlags)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& ccf = instMap[OPCODE(0x3F)];			

			regs.SetFlag(FLAG_CARRY);
			ccf.Call(nullptr);
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			ccf.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));
		}

		TEST_METHOD(DAA_CorrectOperation)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& daa = instMap[OPCODE(0x27)];

			regs.ResetAllFlags();
			regs.A = 0x00;
			daa.Call(nullptr);
			Assert::IsTrue(regs.A == 0x00);
			Assert::IsTrue(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.ResetAllFlags();
			regs.A = 0x99;
			daa.Call(nullptr);
			Assert::IsTrue(regs.A == 0x99);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.ResetAllFlags();
			regs.A = 0xAA;
			daa.Call(nullptr);
			Assert::IsTrue(regs.A == 0x10);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.ResetAllFlags();
			regs.A = 0xCC;
			daa.Call(nullptr);
			Assert::IsTrue(regs.A == 0x32);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.ResetAllFlags();
			regs.A = 0xEE;
			daa.Call(nullptr);
			Assert::IsTrue(regs.A == 0x54);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.ResetAllFlags();
			regs.A = 0xFF;
			daa.Call(nullptr);
			Assert::IsTrue(regs.A == 0x65);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.ResetAllFlags();
			regs.A = 0xA0;
			daa.Call(nullptr);
			Assert::IsTrue(regs.A == 0x00);
			Assert::IsTrue(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.ResetAllFlags();
			regs.A = 0x0A;
			daa.Call(nullptr);
			Assert::IsTrue(regs.A == 0x10);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));

			regs.ResetAllFlags();
			regs.A = 0xB1;
			daa.Call(nullptr);
			Assert::IsTrue(regs.A == 0x11);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
		}

		TEST_METHOD(SCF_CorrectOperation)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& scf = instMap[OPCODE(0x37)];

			regs.ResetAllFlags();
			scf.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));

			regs.SetFlag(FLAG_CARRY);
			scf.Call(nullptr);
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));
		}

		TEST_METHOD(ADD_SP_d8)
		{
			CPUFW_SLEEPY_TESTINIT();

			CpuInstructionDef& add_sp_d8 = instMap[0xE8];

			BYTE d8 = 0x00;

			regs.SP = 0xAAAA;
			d8 = 0xBB;
			add_sp_d8.Call(&d8);
			Assert::IsTrue(regs.SP == (0xAAAA + 0xBB));

			regs.SP = 0x0000;
			d8 = 0x0F;
			add_sp_d8.Call(&d8);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsFalse(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));

			regs.SP = 0x0001;
			d8 = 0x0F;
			add_sp_d8.Call(&d8);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));

			regs.SP = 0x00F0;
			d8 = 0x0F;
			add_sp_d8.Call(&d8);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsFalse(regs.ReadFlag(FLAG_CARRY));

			regs.SP = 0x00F1;
			d8 = 0x0F;
			add_sp_d8.Call(&d8);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));

			regs.SP = 0xFFF0;
			d8 = 0x0F;
			add_sp_d8.Call(&d8);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));

			regs.SP = 0xFFF1;
			d8 = 0x0F;
			add_sp_d8.Call(&d8);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));

			regs.SP = 0xFFFF;
			d8 = 0x0F;
			add_sp_d8.Call(&d8);
			Assert::IsFalse(regs.ReadFlag(FLAG_ZERO));
			Assert::IsFalse(regs.ReadFlag(FLAG_SUB));
			Assert::IsTrue(regs.ReadFlag(FLAG_HCARRY));
			Assert::IsTrue(regs.ReadFlag(FLAG_CARRY));
		}
	};
}