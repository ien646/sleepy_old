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

		TEST_METHOD(CPUF_LD_B_X)
		{
			// Setup
			System sys;
			sys.Initialize();
			ZeroRegisters(sys);
			auto& instMap = sys.CPU.Firmware.InstructionMap;
			auto& regs = sys.CPU.Registers;
			regs.B = 0xCA;

			CpuInstructionDef ld_a_b = instMap[OPCODE(0x78)];
			CpuInstructionDef ld_b_b = instMap[OPCODE(0x40)];
			CpuInstructionDef ld_c_b = instMap[OPCODE(0x48)];
			CpuInstructionDef ld_d_b = instMap[OPCODE(0x50)];
			CpuInstructionDef ld_e_b = instMap[OPCODE(0x58)];
			CpuInstructionDef ld_h_b = instMap[OPCODE(0x60)];
			CpuInstructionDef ld_l_b = instMap[OPCODE(0x68)];

			// Run
			ld_a_b.Call(nullptr);
			ld_b_b.Call(nullptr);
			ld_c_b.Call(nullptr);
			ld_d_b.Call(nullptr);
			ld_e_b.Call(nullptr);
			ld_h_b.Call(nullptr);
			ld_l_b.Call(nullptr);

			// Assert
			Assert::IsTrue(regs.A == (BYTE)0xCA);
			Assert::IsTrue(regs.B == (BYTE)0xCA);
			Assert::IsTrue(regs.C == (BYTE)0xCA);
			Assert::IsTrue(regs.D == (BYTE)0xCA);
			Assert::IsTrue(regs.E == (BYTE)0xCA);
			Assert::IsTrue(regs.H == (BYTE)0xCA);
			Assert::IsTrue(regs.L == (BYTE)0xCA);
		}

		TEST_METHOD(CPUF_LD_C_X)
		{
			// Setup
			System sys;
			sys.Initialize();
			ZeroRegisters(sys);
			auto& instMap = sys.CPU.Firmware.InstructionMap;
			auto& regs = sys.CPU.Registers;
			regs.C = 0xCA;

			CpuInstructionDef ld_a_c = instMap[OPCODE(0x79)];
			CpuInstructionDef ld_b_c = instMap[OPCODE(0x41)];
			CpuInstructionDef ld_c_c = instMap[OPCODE(0x49)];
			CpuInstructionDef ld_d_c = instMap[OPCODE(0x51)];
			CpuInstructionDef ld_e_c = instMap[OPCODE(0x59)];
			CpuInstructionDef ld_h_c = instMap[OPCODE(0x61)];
			CpuInstructionDef ld_l_c = instMap[OPCODE(0x69)];

			// Run
			ld_a_c.Call(nullptr);
			ld_b_c.Call(nullptr);
			ld_c_c.Call(nullptr);
			ld_d_c.Call(nullptr);
			ld_e_c.Call(nullptr);
			ld_h_c.Call(nullptr);
			ld_l_c.Call(nullptr);

			// Assert
			Assert::IsTrue(regs.A == (BYTE)0xCA);
			Assert::IsTrue(regs.B == (BYTE)0xCA);
			Assert::IsTrue(regs.C == (BYTE)0xCA);
			Assert::IsTrue(regs.D == (BYTE)0xCA);
			Assert::IsTrue(regs.E == (BYTE)0xCA);
			Assert::IsTrue(regs.H == (BYTE)0xCA);
			Assert::IsTrue(regs.L == (BYTE)0xCA);
		}

		TEST_METHOD(CPUF_LD_D_X)
		{
			// Setup
			System sys;
			sys.Initialize();
			ZeroRegisters(sys);
			auto& instMap = sys.CPU.Firmware.InstructionMap;
			auto& regs = sys.CPU.Registers;
			regs.D = 0xCA;

			CpuInstructionDef ld_a_d = instMap[OPCODE(0x7A)];
			CpuInstructionDef ld_b_d = instMap[OPCODE(0x42)];
			CpuInstructionDef ld_c_d = instMap[OPCODE(0x4A)];
			CpuInstructionDef ld_d_d = instMap[OPCODE(0x52)];
			CpuInstructionDef ld_e_d = instMap[OPCODE(0x5A)];
			CpuInstructionDef ld_h_d = instMap[OPCODE(0x62)];
			CpuInstructionDef ld_l_d = instMap[OPCODE(0x6A)];

			// Run
			ld_a_d.Call(nullptr);
			ld_b_d.Call(nullptr);
			ld_c_d.Call(nullptr);
			ld_d_d.Call(nullptr);
			ld_e_d.Call(nullptr);
			ld_h_d.Call(nullptr);
			ld_l_d.Call(nullptr);

			// Assert
			Assert::IsTrue(regs.A == (BYTE)0xCA);
			Assert::IsTrue(regs.B == (BYTE)0xCA);
			Assert::IsTrue(regs.C == (BYTE)0xCA);
			Assert::IsTrue(regs.D == (BYTE)0xCA);
			Assert::IsTrue(regs.E == (BYTE)0xCA);
			Assert::IsTrue(regs.H == (BYTE)0xCA);
			Assert::IsTrue(regs.L == (BYTE)0xCA);
		}

		TEST_METHOD(CPUF_LD_E_X)
		{
			// Setup
			System sys;
			sys.Initialize();
			ZeroRegisters(sys);
			auto& instMap = sys.CPU.Firmware.InstructionMap;
			auto& regs = sys.CPU.Registers;
			regs.E = 0xCA;

			CpuInstructionDef ld_a_e = instMap[OPCODE(0x7B)];
			CpuInstructionDef ld_b_e = instMap[OPCODE(0x43)];
			CpuInstructionDef ld_c_e = instMap[OPCODE(0x4B)];
			CpuInstructionDef ld_d_e = instMap[OPCODE(0x53)];
			CpuInstructionDef ld_e_e = instMap[OPCODE(0x5B)];
			CpuInstructionDef ld_h_e = instMap[OPCODE(0x63)];
			CpuInstructionDef ld_l_e = instMap[OPCODE(0x6B)];

			// Run
			ld_a_e.Call(nullptr);
			ld_b_e.Call(nullptr);
			ld_c_e.Call(nullptr);
			ld_d_e.Call(nullptr);
			ld_e_e.Call(nullptr);
			ld_h_e.Call(nullptr);
			ld_l_e.Call(nullptr);

			// Assert
			Assert::IsTrue(regs.A == (BYTE)0xCA);
			Assert::IsTrue(regs.B == (BYTE)0xCA);
			Assert::IsTrue(regs.C == (BYTE)0xCA);
			Assert::IsTrue(regs.D == (BYTE)0xCA);
			Assert::IsTrue(regs.E == (BYTE)0xCA);
			Assert::IsTrue(regs.H == (BYTE)0xCA);
			Assert::IsTrue(regs.L == (BYTE)0xCA);
		}

		TEST_METHOD(CPUF_LD_H_X)
		{
			// Setup
			System sys;
			sys.Initialize();
			ZeroRegisters(sys);
			auto& instMap = sys.CPU.Firmware.InstructionMap;
			auto& regs = sys.CPU.Registers;
			regs.H = 0xCA;

			CpuInstructionDef ld_a_h = instMap[OPCODE(0x7C)];
			CpuInstructionDef ld_b_h = instMap[OPCODE(0x44)];
			CpuInstructionDef ld_c_h = instMap[OPCODE(0x4C)];
			CpuInstructionDef ld_d_h = instMap[OPCODE(0x54)];
			CpuInstructionDef ld_e_h = instMap[OPCODE(0x5C)];
			CpuInstructionDef ld_h_h = instMap[OPCODE(0x64)];
			CpuInstructionDef ld_l_h = instMap[OPCODE(0x6C)];

			// Run
			ld_a_h.Call(nullptr);
			ld_b_h.Call(nullptr);
			ld_c_h.Call(nullptr);
			ld_d_h.Call(nullptr);
			ld_e_h.Call(nullptr);
			ld_h_h.Call(nullptr);
			ld_l_h.Call(nullptr);

			// Assert
			Assert::IsTrue(regs.A == (BYTE)0xCA);
			Assert::IsTrue(regs.B == (BYTE)0xCA);
			Assert::IsTrue(regs.C == (BYTE)0xCA);
			Assert::IsTrue(regs.D == (BYTE)0xCA);
			Assert::IsTrue(regs.E == (BYTE)0xCA);
			Assert::IsTrue(regs.H == (BYTE)0xCA);
			Assert::IsTrue(regs.L == (BYTE)0xCA);
		}

		TEST_METHOD(CPUF_LD_L_X)
		{
			// Setup
			System sys;
			sys.Initialize();
			ZeroRegisters(sys);
			auto& instMap = sys.CPU.Firmware.InstructionMap;
			auto& regs = sys.CPU.Registers;
			regs.L = 0xCA;

			CpuInstructionDef ld_a_l = instMap[OPCODE(0x7D)];
			CpuInstructionDef ld_b_l = instMap[OPCODE(0x45)];
			CpuInstructionDef ld_c_l = instMap[OPCODE(0x4D)];
			CpuInstructionDef ld_d_l = instMap[OPCODE(0x55)];
			CpuInstructionDef ld_e_l = instMap[OPCODE(0x5D)];
			CpuInstructionDef ld_h_l = instMap[OPCODE(0x65)];
			CpuInstructionDef ld_l_l = instMap[OPCODE(0x6D)];

			// Run
			ld_a_l.Call(nullptr);
			ld_b_l.Call(nullptr);
			ld_c_l.Call(nullptr);
			ld_d_l.Call(nullptr);
			ld_e_l.Call(nullptr);
			ld_h_l.Call(nullptr);
			ld_l_l.Call(nullptr);

			// Assert
			Assert::IsTrue(regs.A == (BYTE)0xCA);
			Assert::IsTrue(regs.B == (BYTE)0xCA);
			Assert::IsTrue(regs.C == (BYTE)0xCA);
			Assert::IsTrue(regs.D == (BYTE)0xCA);
			Assert::IsTrue(regs.E == (BYTE)0xCA);
			Assert::IsTrue(regs.H == (BYTE)0xCA);
			Assert::IsTrue(regs.L == (BYTE)0xCA);
		}

		TEST_METHOD(CPUF_LD_X_ptrHL)
		{
			// Setup
			System sys;
			sys.Initialize();
			ZeroRegisters(sys);
			auto& instMap = sys.CPU.Firmware.InstructionMap;
			auto& regs = sys.CPU.Registers;
			auto& mem = sys.Memory;

			ADDR addr_a = 0x0220;
			ADDR addr_b = 0x1331;
			ADDR addr_c = 0x2442;
			ADDR addr_d = 0x3553;
			ADDR addr_e = 0x4664;
			ADDR addr_h = 0x5775;
			ADDR addr_l = 0x6886;

			mem.data()[addr_a] = 0x0A;
			mem.data()[addr_b] = 0x0B;
			mem.data()[addr_c] = 0x0C;
			mem.data()[addr_d] = 0x0D;
			mem.data()[addr_e] = 0x0E;
			mem.data()[addr_h] = 0x11;
			mem.data()[addr_l] = 0x22;

			CpuInstructionDef ld_a_phl = instMap[OPCODE(0x7E)];
			CpuInstructionDef ld_b_phl = instMap[OPCODE(0x46)];
			CpuInstructionDef ld_c_phl = instMap[OPCODE(0x4E)];
			CpuInstructionDef ld_d_phl = instMap[OPCODE(0x56)];
			CpuInstructionDef ld_e_phl = instMap[OPCODE(0x5E)];
			CpuInstructionDef ld_h_phl = instMap[OPCODE(0x66)];
			CpuInstructionDef ld_l_phl = instMap[OPCODE(0x6E)];

			// Run
			ld_a_phl.Call(nullptr);
			ld_b_phl.Call(nullptr);
			ld_c_phl.Call(nullptr);
			ld_d_phl.Call(nullptr);
			ld_e_phl.Call(nullptr);
			ld_h_phl.Call(nullptr);
			ld_l_phl.Call(nullptr);

			// Assert

			Assert::IsTrue(mem.ReadByte(addr_a) == 0x0A);
			Assert::IsTrue(mem.ReadByte(addr_b) == 0x0B);
			Assert::IsTrue(mem.ReadByte(addr_c) == 0x0C);
			Assert::IsTrue(mem.ReadByte(addr_d) == 0x0D);
			Assert::IsTrue(mem.ReadByte(addr_e) == 0x0E);
			Assert::IsTrue(mem.ReadByte(addr_h) == 0x11);
			Assert::IsTrue(mem.ReadByte(addr_l) == 0x22);
		}
	};
}