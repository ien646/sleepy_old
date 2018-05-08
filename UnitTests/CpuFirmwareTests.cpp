#include "stdafx.h"
#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sleepy;

namespace UnitTests
{
	TEST_CLASS(CpuFirmwareTests)
	{
	public:
		void ZeroRegisters(System& sys)
		{
			sys.CPU.Registers.A = 0x00;
			sys.CPU.Registers.F = 0x00;
			sys.CPU.Registers.B = 0x00;
			sys.CPU.Registers.C = 0x00;
			sys.CPU.Registers.D = 0x00;
			sys.CPU.Registers.E = 0x00;
			sys.CPU.Registers.H = 0x00;
			sys.CPU.Registers.L = 0x00;
		}

		TEST_METHOD(CPUF_LD_A_X)
		{
			// Setup
			System sys;
			sys.Initialize();
			ZeroRegisters(sys);
			auto& instMap = sys.CPU.Firmware.InstructionMap;
			auto& regs = sys.CPU.Registers;
			regs.A = 0xCA;
			CpuInstructionDef ld_a_a = instMap[OPCODE(0x7F)];
			CpuInstructionDef ld_b_a = instMap[OPCODE(0x47)];
			CpuInstructionDef ld_c_a = instMap[OPCODE(0x4F)];
			CpuInstructionDef ld_d_a = instMap[OPCODE(0x57)];
			CpuInstructionDef ld_e_a = instMap[OPCODE(0x5F)];
			CpuInstructionDef ld_h_a = instMap[OPCODE(0x67)];
			CpuInstructionDef ld_l_a = instMap[OPCODE(0x6F)];

			// Run
			ld_a_a.Call(nullptr);
			ld_b_a.Call(nullptr);
			ld_c_a.Call(nullptr);
			ld_d_a.Call(nullptr);
			ld_e_a.Call(nullptr);
			ld_h_a.Call(nullptr);
			ld_l_a.Call(nullptr);

			// Assert
			Assert::IsTrue(regs.A == (BYTE)0xCA);
			Assert::IsTrue(regs.B == (BYTE)0xCA);
			Assert::IsTrue(regs.C == (BYTE)0xCA);
			Assert::IsTrue(regs.D == (BYTE)0xCA);
			Assert::IsTrue(regs.E == (BYTE)0xCA);
			Assert::IsTrue(regs.H == (BYTE)0xCA);
			Assert::IsTrue(regs.L == (BYTE)0xCA);
		}
	};
}