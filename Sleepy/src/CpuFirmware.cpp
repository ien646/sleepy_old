#include "CpuFirmware.h"
#include "Common.h"
#include "System.h"

#define DEF_INST(opc,mnem,cycc,argbl,call) (AddInstruction(opc,mnem,cycc,argbl,call))

#define SYS _sys
#define MEM _sys->Memory
#define CPU _sys->CPU
#define REG CPU.Registers
#define RET_NO_ARGS_REF UNREFERENCED_PARAMETER(args);return

namespace sleepy
{
	const Registers::FLAG FLAG_SUB = Registers::FLAG::SUB;
	const Registers::FLAG FLAG_ZERO = Registers::FLAG::ZERO;
	const Registers::FLAG FLAG_HCARRY = Registers::FLAG::HALF_CARRY;
	const Registers::FLAG FLAG_CARRY = Registers::FLAG::CARRY;

	void CpuFirmware::Initialize(System* sys)
	{
		_sys = sys;
		InitInstructionMap();
	}

	void CpuFirmware::InitInstructionMap()
	{
		InitMap_Misc();

		InitMap_LD_A_X8();
		InitMap_LD_B_X8();
		InitMap_LD_C_X8();
		InitMap_LD_D_X8();
		InitMap_LD_E_X8();
		InitMap_LD_H_X8();
		InitMap_LD_L_X8();
		InitMap_LD_pHL_X8();

		InitMap_ADD_A_X8();
	}

	void CpuFirmware::InitMap_Misc()
	{
		DEF_INST(OPCODE(0x00), "NOP", 4, 0, [&](BYTE* args)
		{
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x10), "STOP", 4, 1, [&](BYTE* args)
		{
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x76), "HALT", 4, 0, [&](BYTE* args)
		{
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0xF3), "DI", 4, 0, [&](BYTE* args)
		{
			CPU.DisableInterrupts();
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0xFB), "EI", 4, 0, [&](BYTE* args)
		{
			CPU.EnableInterrupts();
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_LD_A_X8()
	{
		DEF_INST(OPCODE(0x7F), "LD A,A", 4, 0, [&](BYTE* args)
		{
			REG.A = REG.A;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x78), "LD A,B", 4, 0, [&](BYTE* args)
		{
			REG.A = REG.B;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x79), "LD A,C", 4, 0, [&](BYTE* args)
		{
			REG.A = REG.C;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x7A), "LD A,D", 4, 0, [&](BYTE* args)
		{
			REG.A = REG.D;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x7B), "LD A,E", 4, 0, [&](BYTE* args)
		{
			REG.A = REG.E;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x7C), "LD A,H", 4, 0, [&](BYTE* args)
		{
			REG.A = REG.H;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x7D), "LD A,L", 4, 0, [&](BYTE* args)
		{
			REG.A = REG.L;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x7E), "LD A,(HL)", 8, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)REG.ReadHL();
			REG.A = MEM.ReadByte(addr);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_LD_B_X8()
	{
		DEF_INST(OPCODE(0x47), "LD B,A", 4, 0, [&](BYTE* args)
		{
			REG.B = REG.A;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x40), "LD B,B", 4, 0, [&](BYTE* args)
		{
			REG.B = REG.B;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x41), "LD B,C", 4, 0, [&](BYTE* args)
		{
			REG.B = REG.C;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x42), "LD B,D", 4, 0, [&](BYTE* args)
		{
			REG.B = REG.D;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x43), "LD B,E", 4, 0, [&](BYTE* args)
		{
			REG.B = REG.E;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x44), "LD B,H", 4, 0, [&](BYTE* args)
		{
			REG.B = REG.H;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x45), "LD B,L", 4, 0, [&](BYTE* args)
		{
			REG.B = REG.L;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x46), "LD B,(HL)", 8, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)REG.ReadHL();
			REG.B = MEM.ReadByte(addr);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_LD_C_X8()
	{
		DEF_INST(OPCODE(0x4F), "LD C,A", 4, 0, [&](BYTE* args)
		{
			REG.C = REG.A;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x48), "LD C,B", 4, 0, [&](BYTE* args)
		{
			REG.C = REG.B;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x49), "LD C,C", 4, 0, [&](BYTE* args)
		{
			REG.C = REG.C;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x4A), "LD C,D", 4, 0, [&](BYTE* args)
		{
			REG.C = REG.D;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x4B), "LD C,E", 4, 0, [&](BYTE* args)
		{
			REG.C = REG.E;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x4C), "LD C,H", 4, 0, [&](BYTE* args)
		{
			REG.C = REG.H;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x4D), "LD C,L", 4, 0, [&](BYTE* args)
		{
			REG.C = REG.L;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x4E), "LD C,(HL)", 8, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)REG.ReadHL();
			REG.C = MEM.ReadByte(addr);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_LD_D_X8()
	{
		DEF_INST(OPCODE(0x57), "LD D,A", 4, 0, [&](BYTE* args)
		{
			REG.D = REG.A;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x50), "LD D,B", 4, 0, [&](BYTE* args)
		{
			REG.D = REG.B;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x51), "LD D,C", 4, 0, [&](BYTE* args)
		{
			REG.D = REG.C;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x52), "LD D,D", 4, 0, [&](BYTE* args)
		{
			REG.D = REG.D;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x53), "LD D,E", 4, 0, [&](BYTE* args)
		{
			REG.D = REG.E;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x54), "LD D,H", 4, 0, [&](BYTE* args)
		{
			REG.D = REG.H;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x55), "LD D,L", 4, 0, [&](BYTE* args)
		{
			REG.D = REG.L;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x56), "LD D,(HL)", 8, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)REG.ReadHL();
			REG.D = MEM.ReadByte(addr);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_LD_E_X8()
	{
		DEF_INST(OPCODE(0x5F), "LD E,A", 4, 0, [&](BYTE* args)
		{
			REG.E = REG.A;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x58), "LD E,B", 4, 0, [&](BYTE* args)
		{
			REG.E = REG.B;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x59), "LD E,C", 4, 0, [&](BYTE* args)
		{
			REG.E = REG.C;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x5A), "LD E,D", 4, 0, [&](BYTE* args)
		{
			REG.E = REG.D;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x5B), "LD E,E", 4, 0, [&](BYTE* args)
		{
			REG.E = REG.E;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x5C), "LD E,H", 4, 0, [&](BYTE* args)
		{
			REG.E = REG.H;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x5D), "LD E,L", 4, 0, [&](BYTE* args)
		{
			REG.E = REG.L;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x5E), "LD E,(HL)", 8, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)REG.ReadHL();
			REG.E = MEM.ReadByte(addr);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_LD_H_X8()
	{
		DEF_INST(OPCODE(0x67), "LD H,A", 4, 0, [&](BYTE* args)
		{
			REG.H = REG.A;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x60), "LD H,B", 4, 0, [&](BYTE* args)
		{
			REG.H = REG.B;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x61), "LD H,C", 4, 0, [&](BYTE* args)
		{
			REG.H = REG.C;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x62), "LD H,D", 4, 0, [&](BYTE* args)
		{
			REG.H = REG.D;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x63), "LD H,E", 4, 0, [&](BYTE* args)
		{
			REG.H = REG.E;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x64), "LD H,H", 4, 0, [&](BYTE* args)
		{
			REG.H = REG.H;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x65), "LD H,L", 4, 0, [&](BYTE* args)
		{
			REG.H = REG.L;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x66), "LD H,(HL)", 8, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)REG.ReadHL();
			REG.H = MEM.ReadByte(addr);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_LD_L_X8()
	{
		DEF_INST(OPCODE(0x6F), "LD L,A", 4, 0, [&](BYTE* args)
		{
			REG.L = REG.A;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x68), "LD L,B", 4, 0, [&](BYTE* args)
		{
			REG.L = REG.B;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x69), "LD L,C", 4, 0, [&](BYTE* args)
		{
			REG.L = REG.C;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x6A), "LD L,D", 4, 0, [&](BYTE* args)
		{
			REG.L = REG.D;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x6B), "LD L,E", 4, 0, [&](BYTE* args)
		{
			REG.L = REG.E;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x6C), "LD L,H", 4, 0, [&](BYTE* args)
		{
			REG.L = REG.H;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x6D), "LD L,L", 4, 0, [&](BYTE* args)
		{
			REG.L = REG.L;
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x6E), "LD L,(HL)", 8, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)REG.ReadHL();
			REG.L = MEM.ReadByte(addr);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_LD_pHL_X8()
	{
		DEF_INST(OPCODE(0x77), "LD (HL),A", 8, 0, [&](BYTE* args)
		{
			MEM.WriteByte(REG.ReadHL(), REG.A);
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x70), "LD (HL),B", 8, 0, [&](BYTE* args)
		{
			MEM.WriteByte(REG.ReadHL(), REG.B);
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x71), "LD (HL),C", 8, 0, [&](BYTE* args)
		{
			MEM.WriteByte(REG.ReadHL(), REG.C);
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x72), "LD (HL),D", 8, 0, [&](BYTE* args)
		{
			MEM.WriteByte(REG.ReadHL(), REG.D);
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x73), "LD (HL),E", 8, 0, [&](BYTE* args)
		{
			MEM.WriteByte(REG.ReadHL(), REG.E);
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x74), "LD (HL),H", 8, 0, [&](BYTE* args)
		{
			MEM.WriteByte(REG.ReadHL(), REG.H);
			RET_NO_ARGS_REF;
		});

		DEF_INST(OPCODE(0x75), "LD (HL),L", 8, 0, [&](BYTE* args)
		{
			MEM.WriteByte(REG.ReadHL(), REG.L);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_ADD_A_X8()
	{
		DEF_INST(0x87, "ADD A,A", 4, 0, [&](BYTE* args)
		{
			Opcode_ADD_A_V8(REG.A);
			RET_NO_ARGS_REF;
		});

		DEF_INST(0x80, "ADD A,B", 4, 0, [&](BYTE* args)
		{
			Opcode_ADD_A_V8(REG.B);
			RET_NO_ARGS_REF;
		});

		DEF_INST(0x81, "ADD A,C", 4, 0, [&](BYTE* args)
		{
			Opcode_ADD_A_V8(REG.C);
			RET_NO_ARGS_REF;
		});

		DEF_INST(0x82, "ADD A,D", 4, 0, [&](BYTE* args)
		{
			Opcode_ADD_A_V8(REG.D);
			RET_NO_ARGS_REF;
		});

		DEF_INST(0x83, "ADD A,E", 4, 0, [&](BYTE* args)
		{
			Opcode_ADD_A_V8(REG.E);
			RET_NO_ARGS_REF;
		});

		DEF_INST(0x84, "ADD A,H", 4, 0, [&](BYTE* args)
		{
			Opcode_ADD_A_V8(REG.H);
			RET_NO_ARGS_REF;
		});

		DEF_INST(0x85, "ADD A,L", 4, 0, [&](BYTE* args)
		{
			Opcode_ADD_A_V8(REG.L);
			RET_NO_ARGS_REF;
		});

		DEF_INST(0x86, "ADD A,(HL)", 8, 0, [&](BYTE* args)
		{
			Opcode_ADD_A_V8(MEM.ReadByte(REG.ReadHL()));
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::AddInstruction(OPCODE opc, const std::string & mnem, BYTE cycc, BYTE argl, CpuInstructionDef::OP_CALL call)
	{
		CpuInstructionDef inst(opc, mnem, cycc, argl, call);
		auto pair = std::make_pair(opc, inst);
		auto trash = InstructionMap.insert(pair);
	}

	void CpuFirmware::Opcode_ADD_A_V8(BYTE v8)
	{
		REG.ResetAllFlags();

		WORD result = REG.A + v8;

		if ((BYTE)result == 0x00)
		{
			REG.SetFlag(FLAG_ZERO);
		}
		else if (result > 0xFF)
		{
			REG.SetFlag(FLAG_CARRY);
			REG.SetFlag(FLAG_HCARRY);
		}
		else if (result > 0x0F)
		{
			REG.SetFlag(FLAG_HCARRY);
		}
		REG.A = (BYTE)result;
	}
}