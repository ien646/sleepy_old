#include "stdafx.h"
#include "CppUnitTest.h"

#include "System.h"
#include "CpuFirmware.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sleepy;

namespace UnitTests
{
	TEST_CLASS(MemoryTests)
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

		TEST_METHOD(CPUF_LD_REG8_VAL8)
		{
			// Setup
			System sys;
			sys.Initialize();
			ZeroRegisters(sys);

			// -- LD RX, A
			CpuInstructionDef def = sys.CPU.Firmware.InstructionMap[OPCODE(0x7F)];
		}
	};
}