#include "CpuFirmware.h"
#include "Common.h"
#include "System.h"

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

		_cpu = &(sys->CPU);
		_regs = &(_sys->CPU.Registers);
		_mem = &(sys->Memory);

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
		InitMap_LD_R8_D8();
		InitMap_LD_PTR_A();
		InitMap_LD_A_PTR();
		InitMap_LD_R16_D16();
		InitMap_LD_Misc();

		InitMap_ADD_A_X8();
		InitMap_ADD_HL_R16();
		InitMap_SUB_A_X8();
		InitMap_ADC_A_X8();
		InitMap_SBC_A_X8();

		InitMap_AND_A_X8();
		InitMap_OR_A_X8();
		InitMap_XOR_A_X8();

		InitMap_INC_R8();
		InitMap_INC_R16();
		InitMap_DEC_R8();
		InitMap_DEC_R16();

		InitMap_CP_R8();

		InitMap_BitRotations();

		InitMap_RST();
	}

	void CpuFirmware::InitMap_Misc()
	{
		AddInstruction(OPCODE(0x00), "NOP", 4, 0, [&](BYTE* args)
		{
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x10), "STOP", 4, 1, [&](BYTE* args)
		{
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x76), "HALT", 4, 0, [&](BYTE* args)
		{
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0xF3), "DI", 4, 0, [&](BYTE* args)
		{
			_cpu->DisableInterrupts();
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0xFB), "EI", 4, 0, [&](BYTE* args)
		{
			_cpu->EnableInterrupts();
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x2F), "CPL", 4, 0, [&](BYTE* args)
		{
			Opcode_CPL();
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x3F), "CCF", 4, 0, [&](BYTE* args)
		{
			Opcode_CCF();
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x27), "DAA", 4, 0, [&](BYTE* args)
		{			
			Opcode_DAA();
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x37), "SCF", 4, 0, [&](BYTE* args)
		{
			_regs->SetFlag(FLAG_CARRY);
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0xE8), "ADD SP,d8", 16, 1, [&](BYTE* args)
		{
			BYTE d8 = *&args[0];
			DWORD val = _regs->SP + d8;
			_regs->SP = (WORD)val;

			_regs->ResetAllFlags();

			if (val > BYTE_MAX)
			{
				_regs->SetFlag(FLAG_CARRY);
				_regs->SetFlag(FLAG_HCARRY);
			}
			else if (val > HBYTE_MAX)
			{
				_regs->SetFlag(FLAG_HCARRY);
			}
		});

		
	}

	void CpuFirmware::InitMap_LD_A_X8()
	{
		AddInstruction(OPCODE(0x7F), "LD A,A", 4, 0, [&](BYTE* args)
		{
			_regs->A = _regs->A;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x78), "LD A,B", 4, 0, [&](BYTE* args)
		{
			_regs->A = _regs->B;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x79), "LD A,C", 4, 0, [&](BYTE* args)
		{
			_regs->A = _regs->C;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x7A), "LD A,D", 4, 0, [&](BYTE* args)
		{
			_regs->A = _regs->D;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x7B), "LD A,E", 4, 0, [&](BYTE* args)
		{
			_regs->A = _regs->E;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x7C), "LD A,H", 4, 0, [&](BYTE* args)
		{
			_regs->A = _regs->H;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x7D), "LD A,L", 4, 0, [&](BYTE* args)
		{
			_regs->A = _regs->L;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x7E), "LD A,(HL)", 8, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)_regs->ReadHL();
			_regs->A = _mem->ReadByte(addr);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_LD_B_X8()
	{
		AddInstruction(OPCODE(0x47), "LD B,A", 4, 0, [&](BYTE* args)
		{
			_regs->B = _regs->A;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x40), "LD B,B", 4, 0, [&](BYTE* args)
		{
			_regs->B = _regs->B;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x41), "LD B,C", 4, 0, [&](BYTE* args)
		{
			_regs->B = _regs->C;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x42), "LD B,D", 4, 0, [&](BYTE* args)
		{
			_regs->B = _regs->D;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x43), "LD B,E", 4, 0, [&](BYTE* args)
		{
			_regs->B = _regs->E;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x44), "LD B,H", 4, 0, [&](BYTE* args)
		{
			_regs->B = _regs->H;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x45), "LD B,L", 4, 0, [&](BYTE* args)
		{
			_regs->B = _regs->L;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x46), "LD B,(HL)", 8, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)_regs->ReadHL();
			_regs->B = _mem->ReadByte(addr);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_LD_C_X8()
	{
		AddInstruction(OPCODE(0x4F), "LD C,A", 4, 0, [&](BYTE* args)
		{
			_regs->C = _regs->A;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x48), "LD C,B", 4, 0, [&](BYTE* args)
		{
			_regs->C = _regs->B;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x49), "LD C,C", 4, 0, [&](BYTE* args)
		{
			_regs->C = _regs->C;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x4A), "LD C,D", 4, 0, [&](BYTE* args)
		{
			_regs->C = _regs->D;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x4B), "LD C,E", 4, 0, [&](BYTE* args)
		{
			_regs->C = _regs->E;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x4C), "LD C,H", 4, 0, [&](BYTE* args)
		{
			_regs->C = _regs->H;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x4D), "LD C,L", 4, 0, [&](BYTE* args)
		{
			_regs->C = _regs->L;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x4E), "LD C,(HL)", 8, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)_regs->ReadHL();
			_regs->C = _mem->ReadByte(addr);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_LD_D_X8()
	{
		AddInstruction(OPCODE(0x57), "LD D,A", 4, 0, [&](BYTE* args)
		{
			_regs->D = _regs->A;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x50), "LD D,B", 4, 0, [&](BYTE* args)
		{
			_regs->D = _regs->B;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x51), "LD D,C", 4, 0, [&](BYTE* args)
		{
			_regs->D = _regs->C;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x52), "LD D,D", 4, 0, [&](BYTE* args)
		{
			_regs->D = _regs->D;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x53), "LD D,E", 4, 0, [&](BYTE* args)
		{
			_regs->D = _regs->E;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x54), "LD D,H", 4, 0, [&](BYTE* args)
		{
			_regs->D = _regs->H;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x55), "LD D,L", 4, 0, [&](BYTE* args)
		{
			_regs->D = _regs->L;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x56), "LD D,(HL)", 8, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)_regs->ReadHL();
			_regs->D = _mem->ReadByte(addr);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_LD_E_X8()
	{
		AddInstruction(OPCODE(0x5F), "LD E,A", 4, 0, [&](BYTE* args)
		{
			_regs->E = _regs->A;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x58), "LD E,B", 4, 0, [&](BYTE* args)
		{
			_regs->E = _regs->B;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x59), "LD E,C", 4, 0, [&](BYTE* args)
		{
			_regs->E = _regs->C;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x5A), "LD E,D", 4, 0, [&](BYTE* args)
		{
			_regs->E = _regs->D;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x5B), "LD E,E", 4, 0, [&](BYTE* args)
		{
			_regs->E = _regs->E;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x5C), "LD E,H", 4, 0, [&](BYTE* args)
		{
			_regs->E = _regs->H;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x5D), "LD E,L", 4, 0, [&](BYTE* args)
		{
			_regs->E = _regs->L;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x5E), "LD E,(HL)", 8, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)_regs->ReadHL();
			_regs->E = _mem->ReadByte(addr);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_LD_H_X8()
	{
		AddInstruction(OPCODE(0x67), "LD H,A", 4, 0, [&](BYTE* args)
		{
			_regs->H = _regs->A;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x60), "LD H,B", 4, 0, [&](BYTE* args)
		{
			_regs->H = _regs->B;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x61), "LD H,C", 4, 0, [&](BYTE* args)
		{
			_regs->H = _regs->C;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x62), "LD H,D", 4, 0, [&](BYTE* args)
		{
			_regs->H = _regs->D;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x63), "LD H,E", 4, 0, [&](BYTE* args)
		{
			_regs->H = _regs->E;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x64), "LD H,H", 4, 0, [&](BYTE* args)
		{
			_regs->H = _regs->H;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x65), "LD H,L", 4, 0, [&](BYTE* args)
		{
			_regs->H = _regs->L;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x66), "LD H,(HL)", 8, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)_regs->ReadHL();
			_regs->H = _mem->ReadByte(addr);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_LD_L_X8()
	{
		AddInstruction(OPCODE(0x6F), "LD L,A", 4, 0, [&](BYTE* args)
		{
			_regs->L = _regs->A;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x68), "LD L,B", 4, 0, [&](BYTE* args)
		{
			_regs->L = _regs->B;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x69), "LD L,C", 4, 0, [&](BYTE* args)
		{
			_regs->L = _regs->C;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x6A), "LD L,D", 4, 0, [&](BYTE* args)
		{
			_regs->L = _regs->D;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x6B), "LD L,E", 4, 0, [&](BYTE* args)
		{
			_regs->L = _regs->E;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x6C), "LD L,H", 4, 0, [&](BYTE* args)
		{
			_regs->L = _regs->H;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x6D), "LD L,L", 4, 0, [&](BYTE* args)
		{
			_regs->L = _regs->L;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x6E), "LD L,(HL)", 8, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)_regs->ReadHL();
			_regs->L = _mem->ReadByte(addr);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_LD_pHL_X8()
	{
		AddInstruction(OPCODE(0x77), "LD (HL),A", 8, 0, [&](BYTE* args)
		{
			_mem->WriteByte(_regs->ReadHL(), _regs->A);
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x70), "LD (HL),B", 8, 0, [&](BYTE* args)
		{
			_mem->WriteByte(_regs->ReadHL(), _regs->B);
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x71), "LD (HL),C", 8, 0, [&](BYTE* args)
		{
			_mem->WriteByte(_regs->ReadHL(), _regs->C);
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x72), "LD (HL),D", 8, 0, [&](BYTE* args)
		{
			_mem->WriteByte(_regs->ReadHL(), _regs->D);
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x73), "LD (HL),E", 8, 0, [&](BYTE* args)
		{
			_mem->WriteByte(_regs->ReadHL(), _regs->E);
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x74), "LD (HL),H", 8, 0, [&](BYTE* args)
		{
			_mem->WriteByte(_regs->ReadHL(), _regs->H);
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x75), "LD (HL),L", 8, 0, [&](BYTE* args)
		{
			_mem->WriteByte(_regs->ReadHL(), _regs->L);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_LD_R8_D8()
	{
		AddInstruction(OPCODE(0x3E), "LD A,d8", 8, 1, [&](BYTE* args)
		{
			BYTE d8 = args[0];
			_regs->A = d8;
		});

		AddInstruction(OPCODE(0x06), "LD B,d8", 8, 1, [&](BYTE* args)
		{
			BYTE d8 = args[0];
			_regs->B = d8;
		});

		AddInstruction(OPCODE(0x0E), "LD C,d8", 8, 1, [&](BYTE* args)
		{
			BYTE d8 = args[0];
			_regs->C = d8;
		});

		AddInstruction(OPCODE(0x16), "LD D,d8", 8, 1, [&](BYTE* args)
		{
			BYTE d8 = args[0];
			_regs->D = d8;
		});

		AddInstruction(OPCODE(0x1E), "LD E,d8", 8, 1, [&](BYTE* args)
		{
			BYTE d8 = args[0];
			_regs->E = d8;
		});

		AddInstruction(OPCODE(0x26), "LD H,d8", 8, 1, [&](BYTE* args)
		{
			BYTE d8 = args[0];
			_regs->H = d8;
		});

		AddInstruction(OPCODE(0x2E), "LD L,d8", 8, 1, [&](BYTE* args)
		{
			BYTE d8 = args[0];
			_regs->L = d8;
		});

		AddInstruction(OPCODE(0x36), "LD (HL),d8", 12, 1, [&](BYTE* args)
		{
			ADDR addr = _regs->ReadHL();
			BYTE d8 = args[0];
			_mem->WriteByte(addr, d8);
		});
	}

	void CpuFirmware::InitMap_LD_PTR_A()
	{
		AddInstruction(OPCODE(0x02), "LD (BC),A", 8, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)(_regs->ReadBC());
			_mem->WriteByte(addr, _regs->A);
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x12), "LD (DE),A", 8, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)(_regs->ReadDE());
			_mem->WriteByte(addr, _regs->A);
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x22), "LD (HL+),A", 8, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)(_regs->ReadHL());
			_mem->WriteByte(addr, _regs->A);
			_regs->SetHL(_regs->ReadHL() + 1);
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x32), "LD (HL-),A", 8, 0, [&](BYTE* args)
		{
			ADDR addr = (ADDR)(_regs->ReadHL());
			_mem->WriteByte(addr, _regs->A);
			_regs->SetHL(_regs->ReadHL() - 1);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_LD_A_PTR()
	{
		AddInstruction(OPCODE(0x0A), "LD A,(BC)", 8, 0, [&](BYTE* args)
		{
			_regs->A = _mem->ReadByte(_regs->ReadBC());
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x1A), "LD A,(DE)", 8, 0, [&](BYTE* args)
		{
			_regs->A = _mem->ReadByte(_regs->ReadDE());
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x2A), "LD A,(HL+)", 8, 0, [&](BYTE* args)
		{
			WORD vhl = _regs->ReadHL();
			_regs->A = _mem->ReadByte(vhl);
			_regs->SetHL(vhl + 1);
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x3A), "LD A,(HL-)", 8, 0, [&](BYTE* args)
		{
			WORD vhl = _regs->ReadHL();
			_regs->A = _mem->ReadByte(vhl);
			_regs->SetHL(vhl - 1);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_LD_R16_D16()
	{
		AddInstruction(OPCODE(0x01), "LD BC,d16", 12, 2, [&](BYTE* args)
		{
			WORD val = readWord(&args[0]);
			_regs->SetBC(val);
		});

		AddInstruction(OPCODE(0x11), "LD DE,d16", 12, 2, [&](BYTE* args)
		{
			WORD val = readWord(&args[0]);
			_regs->SetDE(val);
		});

		AddInstruction(OPCODE(0x21), "LD DE,d16", 12, 2, [&](BYTE* args)
		{
			WORD val = readWord(&args[0]);
			_regs->SetHL(val);
		});

		AddInstruction(OPCODE(0x31), "LD DE,d16", 12, 2, [&](BYTE* args)
		{
			WORD val = readWord(&args[0]);
			_regs->SP = val;
		});
	}

	void CpuFirmware::InitMap_LD_Misc()
	{
		AddInstruction(OPCODE(0xE2), "LD (C),A", 8, 0, [&](BYTE* args)
		{
			_mem->WriteByte((ADDR)(0xFF00 + _regs->C), _regs->A);
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0xF2), "LD A,(C)", 8, 0, [&](BYTE* args)
		{
			_regs->A = _mem->ReadByte(0xFF00 + _regs->C);
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x08), "LD (d16),SP", 20, 2, [&](BYTE* args)
		{
			ADDR addr = readWord(&args[0]);
			WORD val = _regs->SP;
			_mem->WriteWord(addr, val);
		});

		AddInstruction(OPCODE(0xF8), "LD HL, SP + d8", 12, 1, [&](BYTE* args)
		{
			BYTE d8 = *(&args[0]);
			DWORD val = d8 + _regs->SP;
			_regs->SetHL((WORD)val);

			_regs->ResetAllFlags();

			if (val > BYTE_MAX)
			{
				_regs->SetFlag(FLAG_CARRY);
				_regs->SetFlag(FLAG_HCARRY);
			}
			else if (val > HBYTE_MAX)
			{
				_regs->SetFlag(FLAG_HCARRY);
			}
		});

		AddInstruction(OPCODE(0xEA), "LD (a16), A", 16, 2, [&](BYTE* args)
		{
			ADDR a16 = readWord(args);
			BYTE val = _regs->A;
			_mem->WriteByte(a16, val);
		});

		AddInstruction(OPCODE(0xFA), "LD A, (a16)", 16, 2, [&](BYTE* args)
		{
			ADDR a16 = readWord(args);
			BYTE val = _mem->ReadByte(a16);
			_regs->A = val;
		});

		AddInstruction(OPCODE(0xF9), "LD SP,HL", 8, 0, [&](BYTE* args)
		{
			WORD hl = _regs->ReadHL();
			_regs->SP = hl;
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0xE0), "LDH ($FF00+a8), A", 12, 1, [&](BYTE* args)
		{
			BYTE a8 = *&args[0];
			WORD addr = 0xFF00 + a8;
			_mem->WriteByte(addr, _regs->A);
		});

		AddInstruction(OPCODE(0xF0), "LDH A, ($FF00+a8)", 12, 1, [&](BYTE* args)
		{
			BYTE a8 = *&args[0];
			WORD addr = 0xFF00 + a8;
			BYTE val = _mem->ReadByte(addr);
			_regs->A = val;
		});
	}

	void CpuFirmware::InitMap_ADD_A_X8()
	{
		AddInstruction(0x87, "ADD A,A", 4, 0, [&](BYTE* args)
		{
			Opcode_ADD_A_V8(_regs->A);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x80, "ADD A,B", 4, 0, [&](BYTE* args)
		{
			Opcode_ADD_A_V8(_regs->B);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x81, "ADD A,C", 4, 0, [&](BYTE* args)
		{
			Opcode_ADD_A_V8(_regs->C);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x82, "ADD A,D", 4, 0, [&](BYTE* args)
		{
			Opcode_ADD_A_V8(_regs->D);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x83, "ADD A,E", 4, 0, [&](BYTE* args)
		{
			Opcode_ADD_A_V8(_regs->E);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x84, "ADD A,H", 4, 0, [&](BYTE* args)
		{
			Opcode_ADD_A_V8(_regs->H);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x85, "ADD A,L", 4, 0, [&](BYTE* args)
		{
			Opcode_ADD_A_V8(_regs->L);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x86, "ADD A,(HL)", 8, 0, [&](BYTE* args)
		{
			Opcode_ADD_A_V8(_mem->ReadByte(_regs->ReadHL()));
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xC6, "ADD A,d8", 8, 1, [&](BYTE* args)
		{
			BYTE d8 = args[0];
			Opcode_ADD_A_V8(d8);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_ADD_HL_R16()
	{
		AddInstruction(OPCODE(0x09), "ADD HL,BC", 8, 0, [&](BYTE* args)
		{
			Opcode_ADD_HL_V16(_regs->ReadBC());
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x19), "ADD HL,DE", 8, 0, [&](BYTE* args)
		{
			Opcode_ADD_HL_V16(_regs->ReadDE());
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x29), "ADD HL,HL", 8, 0, [&](BYTE* args)
		{
			Opcode_ADD_HL_V16(_regs->ReadHL());
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x39), "ADD HL,SP", 8, 0, [&](BYTE* args)
		{
			Opcode_ADD_HL_V16(_regs->SP);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_SUB_A_X8()
	{
		AddInstruction(0x97, "SUB A,A", 4, 0, [&](BYTE* args)
		{
			Opcode_SUB_A_V8(_regs->A);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x90, "SUB A,B", 4, 0, [&](BYTE* args)
		{
			Opcode_SUB_A_V8(_regs->B);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x91, "SUB A,C", 4, 0, [&](BYTE* args)
		{
			Opcode_SUB_A_V8(_regs->C);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x92, "SUB A,D", 4, 0, [&](BYTE* args)
		{
			Opcode_SUB_A_V8(_regs->D);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x93, "SUB A,E", 4, 0, [&](BYTE* args)
		{
			Opcode_SUB_A_V8(_regs->E);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x94, "SUB A,H", 4, 0, [&](BYTE* args)
		{
			Opcode_SUB_A_V8(_regs->H);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x95, "SUB A,L", 4, 0, [&](BYTE* args)
		{
			Opcode_SUB_A_V8(_regs->L);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x96, "SUB A,(HL)", 8, 0, [&](BYTE* args)
		{
			Opcode_SUB_A_V8(_mem->ReadByte(_regs->ReadHL()));
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xD6, "SUB A,d8", 8, 1, [&](BYTE* args)
		{
			BYTE d8 = args[0];
			Opcode_SUB_A_V8(d8);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_ADC_A_X8()
	{
		AddInstruction(0x8F, "ADC A,A", 4, 0, [&](BYTE* args)
		{
			Opcode_ADC_A_V8(_regs->A);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x88, "ADC A,B", 4, 0, [&](BYTE* args)
		{
			Opcode_ADC_A_V8(_regs->B);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x89, "ADC A,C", 4, 0, [&](BYTE* args)
		{
			Opcode_ADC_A_V8(_regs->C);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x8A, "ADC A,D", 4, 0, [&](BYTE* args)
		{
			Opcode_ADC_A_V8(_regs->D);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x8B, "ADC A,E", 4, 0, [&](BYTE* args)
		{
			Opcode_ADC_A_V8(_regs->E);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x8C, "ADC A,H", 4, 0, [&](BYTE* args)
		{
			Opcode_ADC_A_V8(_regs->H);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x8D, "ADC A,L", 4, 0, [&](BYTE* args)
		{
			Opcode_ADC_A_V8(_regs->L);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x8E, "ADC A,(HL)", 8, 0, [&](BYTE* args)
		{
			Opcode_ADC_A_V8(_mem->ReadByte(_regs->ReadHL()));
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xCE, "ADC A,d8", 8, 1, [&](BYTE* args)
		{
			BYTE d8 = args[0];
			Opcode_ADC_A_V8(d8);
		});
	}

	void CpuFirmware::InitMap_SBC_A_X8()
	{
		AddInstruction(0x9F, "SBC A,A", 4, 0, [&](BYTE* args)
		{
			Opcode_SBC_A_V8(_regs->A);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x98, "SBC A,B", 4, 0, [&](BYTE* args)
		{
			Opcode_SBC_A_V8(_regs->B);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x99, "SBC A,C", 4, 0, [&](BYTE* args)
		{
			Opcode_SBC_A_V8(_regs->C);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x9A, "SBC A,D", 4, 0, [&](BYTE* args)
		{
			Opcode_SBC_A_V8(_regs->D);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x9B, "SBC A,E", 4, 0, [&](BYTE* args)
		{
			Opcode_SBC_A_V8(_regs->E);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x9C, "SBC A,H", 4, 0, [&](BYTE* args)
		{
			Opcode_SBC_A_V8(_regs->H);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x9D, "SBC A,L", 4, 0, [&](BYTE* args)
		{
			Opcode_SBC_A_V8(_regs->L);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x9E, "SBC A,(HL)", 8, 0, [&](BYTE* args)
		{
			Opcode_SBC_A_V8(_mem->ReadByte(_regs->ReadHL()));
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xDE, "SBC A,d8", 8, 1, [&](BYTE* args)
		{
			BYTE d8 = args[0];
			Opcode_SBC_A_V8(d8);
		});
	}

	void CpuFirmware::InitMap_AND_A_X8()
	{
		AddInstruction(0xA7, "AND A,A", 4, 0, [&](BYTE* args)
		{
			Opcode_AND_A_V8(_regs->A);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xA0, "AND A,B", 4, 0, [&](BYTE* args)
		{
			Opcode_AND_A_V8(_regs->B);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xA1, "AND A,C", 4, 0, [&](BYTE* args)
		{
			Opcode_AND_A_V8(_regs->C);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xA2, "AND A,D", 4, 0, [&](BYTE* args)
		{
			Opcode_AND_A_V8(_regs->D);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xA3, "AND A,E", 4, 0, [&](BYTE* args)
		{
			Opcode_AND_A_V8(_regs->E);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xA4, "AND A,H", 4, 0, [&](BYTE* args)
		{
			Opcode_AND_A_V8(_regs->H);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xA5, "AND A,L", 4, 0, [&](BYTE* args)
		{
			Opcode_AND_A_V8(_regs->L);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xA6, "AND A,(HL)", 8, 0, [&](BYTE* args)
		{
			Opcode_AND_A_V8(_mem->ReadByte(_regs->ReadHL()));
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xE6, "AND A,d8", 8, 1, [&](BYTE* args)
		{
			BYTE d8 = args[0];
			Opcode_AND_A_V8(d8);
		});
	}

	void CpuFirmware::InitMap_OR_A_X8()
	{
		AddInstruction(0xB7, "OR A,A", 4, 0, [&](BYTE* args)
		{
			Opcode_OR_A_V8(_regs->A);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xB0, "OR A,B", 4, 0, [&](BYTE* args)
		{
			Opcode_OR_A_V8(_regs->B);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xB1, "OR A,C", 4, 0, [&](BYTE* args)
		{
			Opcode_OR_A_V8(_regs->C);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xB2, "OR A,D", 4, 0, [&](BYTE* args)
		{
			Opcode_OR_A_V8(_regs->D);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xB3, "OR A,E", 4, 0, [&](BYTE* args)
		{
			Opcode_OR_A_V8(_regs->E);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xB4, "OR A,H", 4, 0, [&](BYTE* args)
		{
			Opcode_OR_A_V8(_regs->H);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xB5, "OR A,L", 4, 0, [&](BYTE* args)
		{
			Opcode_OR_A_V8(_regs->L);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xB6, "OR A,(HL)", 8, 0, [&](BYTE* args)
		{
			Opcode_OR_A_V8(_mem->ReadByte(_regs->ReadHL()));
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xF6, "OR A,d8", 8, 1, [&](BYTE* args)
		{
			BYTE d8 = args[0];
			Opcode_OR_A_V8(d8);
		});
	}

	void CpuFirmware::InitMap_XOR_A_X8()
	{
		AddInstruction(0xAF, "XOR A,A", 4, 0, [&](BYTE* args)
		{
			Opcode_XOR_A_V8(_regs->A);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xA8, "XOR A,B", 4, 0, [&](BYTE* args)
		{
			Opcode_XOR_A_V8(_regs->B);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xA9, "XOR A,C", 4, 0, [&](BYTE* args)
		{
			Opcode_XOR_A_V8(_regs->C);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xAA, "XOR A,D", 4, 0, [&](BYTE* args)
		{
			Opcode_XOR_A_V8(_regs->D);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xAB, "XOR A,E", 4, 0, [&](BYTE* args)
		{
			Opcode_XOR_A_V8(_regs->E);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xAC, "XOR A,H", 4, 0, [&](BYTE* args)
		{
			Opcode_XOR_A_V8(_regs->H);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xAD, "XOR A,L", 4, 0, [&](BYTE* args)
		{
			Opcode_XOR_A_V8(_regs->L);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xAE, "XOR A,(HL)", 8, 0, [&](BYTE* args)
		{
			Opcode_XOR_A_V8(_mem->ReadByte(_regs->ReadHL()));
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xEE, "XOR A,d8", 8, 1, [&](BYTE* args)
		{
			BYTE d8 = args[0];
			Opcode_XOR_A_V8(d8);
		});
	}

	void CpuFirmware::InitMap_INC_R8()
	{
		AddInstruction(0x3C, "INC A", 4, 0, [&](BYTE* args)
		{
			Opcode_INC_R8(_regs->A);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x04, "INC B", 4, 0, [&](BYTE* args)
		{
			Opcode_INC_R8(_regs->B);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x0C, "INC C", 4, 0, [&](BYTE* args)
		{
			Opcode_INC_R8(_regs->C);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x14, "INC D", 4, 0, [&](BYTE* args)
		{
			Opcode_INC_R8(_regs->D);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x1C, "INC E", 4, 0, [&](BYTE* args)
		{
			Opcode_INC_R8(_regs->E);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x24, "INC H", 4, 0, [&](BYTE* args)
		{
			Opcode_INC_R8(_regs->H);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x2C, "INC L", 4, 0, [&](BYTE* args)
		{
			Opcode_INC_R8(_regs->E);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x34, "INC (HL)", 12, 0, [&](BYTE* args)
		{
			ADDR addr = _regs->ReadHL();
			BYTE val = _mem->ReadByte(addr);
			Opcode_INC_R8(val);
			_mem->WriteByte(addr, val);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_INC_R16()
	{
		AddInstruction(0x03, "INC BC", 8, 0, [&](BYTE* args)
		{
			WORD val = (WORD)(_regs->ReadBC() + 1);
			_regs->SetBC(val);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x13, "INC DE", 8, 0, [&](BYTE* args)
		{
			WORD val = (WORD)(_regs->ReadDE() + 1);
			_regs->SetDE(val);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x23, "INC HL", 8, 0, [&](BYTE* args)
		{
			WORD val = (WORD)(_regs->ReadHL() + 1);
			_regs->SetHL(val);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x33, "INC SP", 8, 0, [&](BYTE* args)
		{
			_regs->SP += 1;
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_DEC_R8()
	{
		AddInstruction(0x3D, "DEC A", 4, 0, [&](BYTE* args)
		{
			Opcode_DEC_R8(_regs->A);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x05, "DEC B", 4, 0, [&](BYTE* args)
		{
			Opcode_DEC_R8(_regs->B);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x0D, "DEC C", 4, 0, [&](BYTE* args)
		{
			Opcode_DEC_R8(_regs->C);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x15, "DEC D", 4, 0, [&](BYTE* args)
		{
			Opcode_DEC_R8(_regs->D);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x1D, "DEC E", 4, 0, [&](BYTE* args)
		{
			Opcode_DEC_R8(_regs->E);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x25, "DEC H", 4, 0, [&](BYTE* args)
		{
			Opcode_DEC_R8(_regs->H);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x2D, "DEC L", 4, 0, [&](BYTE* args)
		{
			Opcode_DEC_R8(_regs->E);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x35, "DEC (HL)", 12, 0, [&](BYTE* args)
		{
			ADDR addr = _regs->ReadHL();
			BYTE val = _mem->ReadByte(addr);
			Opcode_DEC_R8(val);
			_mem->WriteByte(addr, val);
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_DEC_R16()
	{
		AddInstruction(0x0B, "DEC BC", 8, 0, [&](BYTE* args)
		{
			WORD val = (WORD)(_regs->ReadBC() - 1);
			_regs->SetBC(val);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x1B, "DEC DE", 8, 0, [&](BYTE* args)
		{
			WORD val = (WORD)(_regs->ReadDE() - 1);
			_regs->SetDE(val);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x2B, "DEC HL", 8, 0, [&](BYTE* args)
		{
			WORD val = (WORD)(_regs->ReadHL() - 1);
			_regs->SetHL(val);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0x3B, "DEC SP", 8, 0, [&](BYTE* args)
		{
			_regs->SP -= 1;
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_CP_R8()
	{
		AddInstruction(0xBF, "CP A", 4, 0, [&](BYTE* args)
		{
			Opcode_CP_R8(_regs->A);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xB8, "CP B", 4, 0, [&](BYTE* args)
		{
			Opcode_CP_R8(_regs->B);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xB9, "CP C", 4, 0, [&](BYTE* args)
		{
			Opcode_CP_R8(_regs->C);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xBA, "CP D", 4, 0, [&](BYTE* args)
		{
			Opcode_CP_R8(_regs->D);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xBB, "CP E", 4, 0, [&](BYTE* args)
		{
			Opcode_CP_R8(_regs->E);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xBC, "CP H", 4, 0, [&](BYTE* args)
		{
			Opcode_CP_R8(_regs->H);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xBD, "CP L", 4, 0, [&](BYTE* args)
		{
			Opcode_CP_R8(_regs->L);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xBE, "CP (HL)", 8, 0, [&](BYTE* args)
		{
			Opcode_CP_R8(_regs->L);
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xFE, "CP d8", 8, 1, [&](BYTE* args)
		{
			BYTE d8 = args[0];
			Opcode_CP_R8(d8);
		});
	}

	void CpuFirmware::InitMap_BitRotations()
	{
		AddInstruction(OPCODE(0x0F), "RRCA", 4, 0, [&](BYTE* args)
		{
			Opcode_RRCA();
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x1F), "RRA", 4, 0, [&](BYTE* args)
		{
			Opcode_RRA();
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x07), "RLCA", 4, 0, [&](BYTE* args)
		{
			Opcode_RLCA();
			RET_NO_ARGS_REF;
		});

		AddInstruction(OPCODE(0x17), "RLA", 4, 0, [&](BYTE* args)
		{
			Opcode_RLA();
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::InitMap_RST()
	{
		AddInstruction(0xC7, "RST 00H", 16, 0, [&](BYTE* args)
		{
			_regs->PC = 0x0000;
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xCF, "RST 08H", 16, 0, [&](BYTE* args)
		{
			_regs->PC = 0x0008;
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xD7, "RST 10H", 16, 0, [&](BYTE* args)
		{
			_regs->PC = 0x0010;
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xDF, "RST 18H", 16, 0, [&](BYTE* args)
		{
			_regs->PC = 0x0018;
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xE7, "RST 20H", 16, 0, [&](BYTE* args)
		{
			_regs->PC = 0x0020;
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xEF, "RST 28H", 16, 0, [&](BYTE* args)
		{
			_regs->PC = 0x0028;
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xF7, "RST 30H", 16, 0, [&](BYTE* args)
		{
			_regs->PC = 0x0030;
			RET_NO_ARGS_REF;
		});

		AddInstruction(0xFF, "RST 38H", 16, 0, [&](BYTE* args)
		{
			_regs->PC = 0x0038;
			RET_NO_ARGS_REF;
		});
	}

	void CpuFirmware::AddInstruction(OPCODE opc, const std::string& mnem, BYTE cycc, BYTE argl, const CpuInstructionDef::OP_CALL& call)
	{
		CpuInstructionDef inst(opc, mnem, cycc, argl, call);
		auto pair = std::make_pair(opc, std::move(inst));
		auto trash = InstructionMap.insert(std::move(pair));
	}

	void CpuFirmware::Opcode_ADD_A_V8(BYTE v8)
	{
		_regs->ResetAllFlags();

		WORD result = _regs->A + v8;

		if ((BYTE)result == 0x00)
		{
			_regs->SetFlag(FLAG_ZERO);
		}

		if (result > 0xFF)
		{
			_regs->SetFlag(FLAG_CARRY);
			_regs->SetFlag(FLAG_HCARRY);
		}
		else if (result > 0x0F)
		{
			_regs->SetFlag(FLAG_HCARRY);
		}

		_regs->A = (BYTE)result;
	}

	void CpuFirmware::Opcode_ADD_HL_V16(WORD v16)
	{
		_regs->ResetFlag(FLAG_SUB);

		DWORD result = _regs->ReadHL() + v16;
		if (result > 0x0000FFFF)
		{
			_regs->SetFlag(FLAG_CARRY);
			_regs->SetFlag(FLAG_HCARRY);
		}
		else if (result > 0x000000FF)
		{
			_regs->SetFlag(FLAG_HCARRY);
		}

		_regs->SetHL((WORD)result);
	}

	void CpuFirmware::Opcode_SUB_A_V8(BYTE v8)
	{
		_regs->ResetAllFlags();
		_regs->SetFlag(FLAG_SUB);

		WORD result = _regs->A - v8;

		if ((BYTE)result == 0x00)
		{
			_regs->SetFlag(FLAG_ZERO);
		}
		if (result > 0xFF)
		{
			_regs->SetFlag(FLAG_CARRY);
			_regs->SetFlag(FLAG_HCARRY);
		}
		else if (result > 0x0F)
		{
			_regs->SetFlag(FLAG_HCARRY);
		}

		_regs->A = (BYTE)result;
	}

	void CpuFirmware::Opcode_ADC_A_V8(BYTE v8)
	{
		WORD result = _regs->A + v8 + (_regs->ReadFlag(FLAG_CARRY) ? 1 : 0);

		_regs->ResetAllFlags();

		if ((BYTE)result == 0x00)
		{
			_regs->SetFlag(FLAG_ZERO);
		}

		if (result > 0xFF)
		{
			_regs->SetFlag(FLAG_CARRY);
			_regs->SetFlag(FLAG_HCARRY);
		}
		else if (result > 0x0F)
		{
			_regs->SetFlag(FLAG_HCARRY);
		}

		_regs->A = (BYTE)result;
	}

	void CpuFirmware::Opcode_SBC_A_V8(BYTE v8)
	{
		WORD result = _regs->A - (v8 + (_regs->ReadFlag(FLAG_CARRY) ? 1 : 0));

		_regs->ResetAllFlags();
		_regs->SetFlag(FLAG_SUB);

		if ((BYTE)result == 0x00)
		{
			_regs->SetFlag(FLAG_ZERO);
		}

		if (result > 0xFF)
		{
			_regs->SetFlag(FLAG_CARRY);
			_regs->SetFlag(FLAG_HCARRY);
		}
		else if (result > 0x0F)
		{
			_regs->SetFlag(FLAG_HCARRY);
		}

		_regs->A = (BYTE)result;
	}

	void CpuFirmware::Opcode_AND_A_V8(BYTE v8)
	{
		_regs->ResetAllFlags();
		_regs->SetFlag(FLAG_SUB);

		BYTE result = (_regs->A & v8);

		if (result == 0x00)
		{
			_regs->SetFlag(FLAG_ZERO);
		}

		_regs->A = result;
	}

	void CpuFirmware::Opcode_OR_A_V8(BYTE v8)
	{
		_regs->ResetAllFlags();

		BYTE result = (_regs->A | v8);

		if (result == 0x00)
		{
			_regs->SetFlag(FLAG_ZERO);
		}

		_regs->A = result;
	}

	void CpuFirmware::Opcode_XOR_A_V8(BYTE v8)
	{
		_regs->ResetAllFlags();

		BYTE result = (_regs->A ^ v8);

		if (result == 0x00)
		{
			_regs->SetFlag(FLAG_ZERO);
		}

		_regs->A = result;
	}

	void CpuFirmware::Opcode_INC_R8(REG_8BIT& reg)
	{
		_regs->ResetFlag(FLAG_ZERO);
		_regs->ResetFlag(FLAG_HCARRY);
		_regs->ResetFlag(FLAG_SUB);

		++reg;

		if (reg == 0x00)
		{
			_regs->SetFlag(FLAG_ZERO);
		}

		if (reg > 0x0F)
		{
			_regs->SetFlag(FLAG_HCARRY);
		}
	}

	void CpuFirmware::Opcode_DEC_R8(REG_8BIT& reg)
	{
		_regs->ResetFlag(FLAG_ZERO);
		_regs->ResetFlag(FLAG_HCARRY);
		_regs->SetFlag(FLAG_SUB);

		--reg;

		if (reg == 0x00)
		{
			_regs->SetFlag(FLAG_ZERO);
		}

		if (reg > 0x0F)
		{
			_regs->SetFlag(FLAG_HCARRY);
		}
	}

	void CpuFirmware::Opcode_CP_R8(BYTE reg)
	{
		_regs->ResetAllFlags();
		_regs->SetFlag(FLAG_SUB);

		WORD result = _regs->A - reg;

		if ((BYTE)result == 0x00)
		{
			_regs->SetFlag(FLAG_ZERO);
		}
		if (result > 0xFF)
		{
			_regs->SetFlag(FLAG_CARRY);
			_regs->SetFlag(FLAG_HCARRY);
		}
		else if (result > 0x0F)
		{
			_regs->SetFlag(FLAG_HCARRY);
		}
		/* -- omit result -- */
	}

	void CpuFirmware::Opcode_RRCA()
	{
		bool bit_0 = getBit(_regs->A, 0);

		_regs->ResetAllFlags();

		BYTE result = (_regs->A >> 1);
		if (bit_0)
		{
			_regs->SetFlag(FLAG_CARRY);
			result |= 0x80;
		}

		_regs->A = result;
	}

	void CpuFirmware::Opcode_RRA()
	{
		bool bit_0 = getBit(_regs->A, 0);

		_regs->ResetAllFlags();

		BYTE result = (_regs->A >> 1);
		if (bit_0)
		{
			_regs->SetFlag(FLAG_CARRY);
		}

		_regs->A = result;
	}

	void CpuFirmware::Opcode_RLCA()
	{
		bool bit_7 = getBit(_regs->A, 7);

		_regs->ResetAllFlags();

		BYTE result = (_regs->A << 1);
		if (bit_7)
		{
			_regs->SetFlag(FLAG_CARRY);
			result |= 0x01;
		}

		_regs->A = result;
	}

	void CpuFirmware::Opcode_RLA()
	{
		bool bit_7 = getBit(_regs->A, 7);

		_regs->ResetAllFlags();

		BYTE result = (_regs->A << 1);
		if (bit_7)
		{
			_regs->SetFlag(FLAG_CARRY);
		}

		_regs->A = result;
	}

	void CpuFirmware::Opcode_CPL()
	{
		_regs->SetFlag(FLAG_SUB);
		_regs->SetFlag(FLAG_HCARRY);
		_regs->A ^= 0xFF;
	}

	void CpuFirmware::Opcode_CCF()
	{
		_regs->ResetFlag(FLAG_SUB);
		_regs->ResetFlag(FLAG_HCARRY);
		_regs->InvertFlag(FLAG_CARRY);
	}

	void CpuFirmware::Opcode_DAA()
	{
		BYTE lowNibble = 0x0F & _regs->A;
		BYTE hiNibble = (0xF0 & _regs->A) >> 4;
		if ((lowNibble > 9) || (_regs->ReadFlag(FLAG_HCARRY)))
		{
			_regs->A += 0x06;
		}
		if ((hiNibble > 9) || (_regs->ReadFlag(FLAG_CARRY)))
		{
			_regs->A += 0x60;
			_regs->SetFlag(FLAG_CARRY);
		}
		if (_regs->A == 0x00)
		{
			_regs->SetFlag(FLAG_ZERO);
		}
		_regs->ResetFlag(FLAG_HCARRY);
	}
}