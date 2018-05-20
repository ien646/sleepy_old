#include "Registers.h"

namespace sleepy
{
	void Registers::SetAF(WORD value)
	{
		A = highByte(value);
		F = lowByte(value);
	}

	void Registers::SetBC(WORD value)
	{
		B = highByte(value);
		C = lowByte(value);
	}

	void Registers::SetDE(WORD value)
	{
		D = highByte(value);
		E = lowByte(value);
	}

	void Registers::SetHL(WORD value)
	{
		H = highByte(value);
		L = lowByte(value);
	}

	WORD Registers::ReadAF()
	{
		return composeWord(A, F);
	}

	WORD Registers::ReadBC()
	{
		return composeWord(B, C);
	}

	WORD Registers::ReadDE()
	{
		return composeWord(D, E);
	}

	WORD Registers::ReadHL()
	{
		return composeWord(H, L);
	}

	void Registers::SetFlag(FLAG flagMask)
	{
		F |= (BYTE)flagMask;
	}

	void Registers::ResetFlag(FLAG flagMask)
	{
		F &= ((BYTE)flagMask ^ 0xFF);
	}

	void Registers::InvertFlag(FLAG flagMask)
	{
		F ^= (BYTE)flagMask;
	}

	bool Registers::ReadFlag(FLAG flagMask)
	{
		return ((BYTE)flagMask | F) == F;
	}

	void Registers::ResetAllFlags()
	{
		F &= 0x00;
	}

	void Registers::ZeroRegisters(bool zero_PC_SP)
	{
		A &= 0x00;
		F &= 0x00;
		B &= 0x00;
		C &= 0x00;
		D &= 0x00;
		E &= 0x00;
		H &= 0x00;
		L &= 0x00;

		if (zero_PC_SP)
		{
			PC = 0x0000;
			SP = 0x0000;
		}
	}
}