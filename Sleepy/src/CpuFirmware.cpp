#include "CpuFirmware.h"
#include "Common.h"
#include "System.h"

#define DEF_INST(opc,mnem,cycc,argbl,call) (AddInstruction(opc,mnem,cycc,argbl,call))
#define CF_LAMB [&](BYTE* args) 

#define SYS _sys
#define MEM _sys->Memory
#define CPU _sys->CPU
#define REG CPU.Registers

namespace sleepy
{
	void CpuFirmware::Initialize(System* sys)
	{
		_sys = sys;
		InitInstructionMap();
	}

	void CpuFirmware::InitInstructionMap()
	{
		InitMap_Misc();
	}

	void CpuFirmware::InitMap_Misc()
	{
		DEF_INST(OPCODE(0x00), "NOP", 4, 0, [&](BYTE* args)
		{
			return;
		});

		DEF_INST(OPCODE(0x00), "STOP", 4, 1, [&](BYTE* args)
		{
			return;
		});

		DEF_INST(OPCODE(0x00), "HALT", 4, 0, [&](BYTE* args)
		{
			return;
		});

		DEF_INST(OPCODE(0x00), "DI", 4, 0, [&](BYTE* args)
		{
			CPU.DisableInterrupts();
		});

		DEF_INST(OPCODE(0x00), "EI", 4, 0, [&](BYTE* args)
		{
			CPU.EnableInterrupts();
		});
	}

	void CpuFirmware::InitMap_LD_A_X()
	{
		DEF_INST(OPCODE(0x7F), "LD A,A", 4, 0, [&](BYTE* args)
		{
			REG.A = REG.A;
		});

		DEF_INST(OPCODE(0x78), "LD A,B", 4, 0, [&](BYTE* args)
		{
			REG.A = REG.B;
		});

		DEF_INST(OPCODE(0x79), "LD A,C", 4, 0, [&](BYTE* args)
		{
			REG.A = REG.C;
		});

		DEF_INST(OPCODE(0x7A), "LD A,D", 4, 0, [&](BYTE* args)
		{
			REG.A = REG.D;
		});

		DEF_INST(OPCODE(0x7B), "LD A,E", 4, 0, [&](BYTE* args)
		{
			REG.A = REG.E;
		});

		DEF_INST(OPCODE(0x7C), "LD A,H", 4, 0, [&](BYTE* args)
		{
			REG.A = REG.H;
		});

		DEF_INST(OPCODE(0x7D), "LD A,L", 4, 0, [&](BYTE* args)
		{
			REG.A = REG.L;
		});

		DEF_INST(OPCODE(0x7E), "LD A,(HL)", 4, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)REG.ReadHL();
			REG.A = MEM.ReadByte(addr);
		});
	}

	void CpuFirmware::InitMap_LD_B_X()
	{
		DEF_INST(OPCODE(0x47), "LD B,A", 4, 0, [&](BYTE* args)
		{
			REG.B = REG.A;
		});

		DEF_INST(OPCODE(0x40), "LD B,B", 4, 0, [&](BYTE* args)
		{
			REG.B = REG.B;
		});

		DEF_INST(OPCODE(0x41), "LD B,C", 4, 0, [&](BYTE* args)
		{
			REG.B = REG.C;
		});

		DEF_INST(OPCODE(0x42), "LD B,D", 4, 0, [&](BYTE* args)
		{
			REG.B = REG.D;
		});

		DEF_INST(OPCODE(0x43), "LD B,E", 4, 0, [&](BYTE* args)
		{
			REG.B = REG.E;
		});

		DEF_INST(OPCODE(0x44), "LD B,H", 4, 0, [&](BYTE* args)
		{
			REG.B = REG.H;
		});

		DEF_INST(OPCODE(0x45), "LD B,L", 4, 0, [&](BYTE* args)
		{
			REG.B = REG.L;
		});

		DEF_INST(OPCODE(0x46), "LD B,(HL)", 4, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)REG.ReadHL();
			REG.B = MEM.ReadByte(addr);
		});
	}

	void CpuFirmware::InitMap_LD_C_X()
	{
		DEF_INST(OPCODE(0x4F), "LD C,A", 4, 0, [&](BYTE* args)
		{
			REG.C = REG.A;
		});

		DEF_INST(OPCODE(0x48), "LD C,B", 4, 0, [&](BYTE* args)
		{
			REG.C = REG.B;
		});

		DEF_INST(OPCODE(0x49), "LD C,C", 4, 0, [&](BYTE* args)
		{
			REG.C = REG.C;
		});

		DEF_INST(OPCODE(0x4A), "LD C,D", 4, 0, [&](BYTE* args)
		{
			REG.C = REG.D;
		});

		DEF_INST(OPCODE(0x4B), "LD C,E", 4, 0, [&](BYTE* args)
		{
			REG.C = REG.E;
		});

		DEF_INST(OPCODE(0x4C), "LD C,H", 4, 0, [&](BYTE* args)
		{
			REG.C = REG.H;
		});

		DEF_INST(OPCODE(0x4D), "LD C,L", 4, 0, [&](BYTE* args)
		{
			REG.C = REG.L;
		});

		DEF_INST(OPCODE(0x4E), "LD C,(HL)", 4, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)REG.ReadHL();
			REG.C = MEM.ReadByte(addr);
		});
	}

	void CpuFirmware::InitMap_LD_D_X()
	{
		DEF_INST(OPCODE(0x57), "LD D,A", 4, 0, [&](BYTE* args)
		{
			REG.D = REG.A;
		});

		DEF_INST(OPCODE(0x50), "LD D,B", 4, 0, [&](BYTE* args)
		{
			REG.D = REG.B;
		});

		DEF_INST(OPCODE(0x51), "LD D,C", 4, 0, [&](BYTE* args)
		{
			REG.D = REG.C;
		});

		DEF_INST(OPCODE(0x52), "LD D,D", 4, 0, [&](BYTE* args)
		{
			REG.D = REG.D;
		});

		DEF_INST(OPCODE(0x53), "LD D,E", 4, 0, [&](BYTE* args)
		{
			REG.D = REG.E;
		});

		DEF_INST(OPCODE(0x54), "LD D,H", 4, 0, [&](BYTE* args)
		{
			REG.D = REG.H;
		});

		DEF_INST(OPCODE(0x55), "LD D,L", 4, 0, [&](BYTE* args)
		{
			REG.D = REG.L;
		});

		DEF_INST(OPCODE(0x56), "LD D,(HL)", 4, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)REG.ReadHL();
			REG.D = MEM.ReadByte(addr);
		});
	}

	void CpuFirmware::InitMap_LD_E_X()
	{
		DEF_INST(OPCODE(0x5F), "LD E,A", 4, 0, [&](BYTE* args)
		{
			REG.E = REG.A;
		});

		DEF_INST(OPCODE(0x58), "LD E,B", 4, 0, [&](BYTE* args)
		{
			REG.E = REG.B;
		});

		DEF_INST(OPCODE(0x59), "LD E,C", 4, 0, [&](BYTE* args)
		{
			REG.E = REG.C;
		});

		DEF_INST(OPCODE(0x5A), "LD E,D", 4, 0, [&](BYTE* args)
		{
			REG.E = REG.D;
		});

		DEF_INST(OPCODE(0x5B), "LD E,E", 4, 0, [&](BYTE* args)
		{
			REG.E = REG.E;
		});

		DEF_INST(OPCODE(0x5C), "LD E,H", 4, 0, [&](BYTE* args)
		{
			REG.E = REG.H;
		});

		DEF_INST(OPCODE(0x5D), "LD E,L", 4, 0, [&](BYTE* args)
		{
			REG.E = REG.L;
		});

		DEF_INST(OPCODE(0x5E), "LD E,(HL)", 4, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)REG.ReadHL();
			REG.E = MEM.ReadByte(addr);
		});
	}

	void CpuFirmware::InitMap_LD_H_X()
	{
		DEF_INST(OPCODE(0x67), "LD H,A", 4, 0, [&](BYTE* args)
		{
			REG.H = REG.A;
		});

		DEF_INST(OPCODE(0x60), "LD H,B", 4, 0, [&](BYTE* args)
		{
			REG.H = REG.B;
		});

		DEF_INST(OPCODE(0x61), "LD H,C", 4, 0, [&](BYTE* args)
		{
			REG.H = REG.C;
		});

		DEF_INST(OPCODE(0x62), "LD H,D", 4, 0, [&](BYTE* args)
		{
			REG.H = REG.D;
		});

		DEF_INST(OPCODE(0x63), "LD H,E", 4, 0, [&](BYTE* args)
		{
			REG.H = REG.E;
		});

		DEF_INST(OPCODE(0x64), "LD H,H", 4, 0, [&](BYTE* args)
		{
			REG.H = REG.H;
		});

		DEF_INST(OPCODE(0x65), "LD H,L", 4, 0, [&](BYTE* args)
		{
			REG.H = REG.L;
		});

		DEF_INST(OPCODE(0x66), "LD H,(HL)", 4, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)REG.ReadHL();
			REG.H = MEM.ReadByte(addr);
		});
	}

	void CpuFirmware::InitMap_LD_L_X()
	{
		DEF_INST(OPCODE(0x6F), "LD L,A", 4, 0, [&](BYTE* args)
		{
			REG.H = REG.A;
		});

		DEF_INST(OPCODE(0x68), "LD L,B", 4, 0, [&](BYTE* args)
		{
			REG.H = REG.B;
		});

		DEF_INST(OPCODE(0x69), "LD L,C", 4, 0, [&](BYTE* args)
		{
			REG.H = REG.C;
		});

		DEF_INST(OPCODE(0x6A), "LD L,D", 4, 0, [&](BYTE* args)
		{
			REG.H = REG.D;
		});

		DEF_INST(OPCODE(0x6B), "LD L,E", 4, 0, [&](BYTE* args)
		{
			REG.H = REG.E;
		});

		DEF_INST(OPCODE(0x6C), "LD L,H", 4, 0, [&](BYTE* args)
		{
			REG.H = REG.H;
		});

		DEF_INST(OPCODE(0x6D), "LD L,L", 4, 0, [&](BYTE* args)
		{
			REG.H = REG.L;
		});

		DEF_INST(OPCODE(0x6E), "LD L,(HL)", 4, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)REG.ReadHL();
			REG.H = MEM.ReadByte(addr);
		});
	}

	void CpuFirmware::AddInstruction(OPCODE opc, const std::string & mnem, BYTE cycc, BYTE argl, CpuInstructionDef::OP_CALL call)
	{
		InstructionMap.insert(std::make_pair(opc, CpuInstructionDef(opc, mnem, cycc, argl, call)));
	}
}