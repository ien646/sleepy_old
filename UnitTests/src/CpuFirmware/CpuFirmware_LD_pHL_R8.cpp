#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sleepy;

namespace UnitTests
{
	TEST_CLASS(CpuFirmwareTests_LD_pHL_R8)
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

		TEST_METHOD(LD_pHL_R8)
		{			
			// Setup
			ADDR phlAddr = 0xDA0F;
			System sys;
			sys.Initialize();
			ZeroRegisters(sys);
			auto& instMap = sys.CPU.Firmware.InstructionMap;
			auto& regs = sys.CPU.Registers;
			auto& mem = sys.Memory;
			memset(mem.data(), 0, (0xFFFF * sizeof(BYTE)));

			CpuInstructionDef ld_phl_a = instMap[OPCODE(0x77)];
			CpuInstructionDef ld_phl_b = instMap[OPCODE(0x70)];
			CpuInstructionDef ld_phl_c = instMap[OPCODE(0x71)];
			CpuInstructionDef ld_phl_d = instMap[OPCODE(0x72)];
			CpuInstructionDef ld_phl_e = instMap[OPCODE(0x73)];
			CpuInstructionDef ld_phl_h = instMap[OPCODE(0x74)];
			CpuInstructionDef ld_phl_l = instMap[OPCODE(0x75)];

			// A
			regs.SetHL(phlAddr);
			regs.A = 0xA0;
			ld_phl_a.Call(nullptr);
			Assert::IsTrue(mem.ReadByte(phlAddr) == 0xA0);

			// B
			regs.SetHL(phlAddr);
			regs.B = 0xB0;
			ld_phl_b.Call(nullptr);
			Assert::IsTrue(mem.ReadByte(phlAddr) == 0xB0);

			// C
			regs.SetHL(phlAddr);
			regs.C = 0xC0;
			ld_phl_c.Call(nullptr);
			Assert::IsTrue(mem.ReadByte(phlAddr) == 0xC0);

			// D
			regs.SetHL(phlAddr);
			regs.D = 0xD0;
			ld_phl_d.Call(nullptr);
			Assert::IsTrue(mem.ReadByte(phlAddr) == 0xD0);

			// E
			regs.SetHL(phlAddr);
			regs.E = 0xE0;
			ld_phl_e.Call(nullptr);
			Assert::IsTrue(mem.ReadByte(phlAddr) == 0xE0);

			// H
			regs.SetHL(phlAddr);
			ld_phl_h.Call(nullptr);
			BYTE datah = mem.ReadByte(phlAddr);
			Assert::IsTrue(datah == regs.H);

			// L
			regs.SetHL(phlAddr);
			regs.L = 0xFF;
			ld_phl_l.Call(nullptr);
			BYTE datal = mem.ReadByte(phlAddr);
			Assert::IsTrue(datal == regs.H);
		}
	};
}