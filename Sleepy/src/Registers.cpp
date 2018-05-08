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

	void Registers::ResetAllFlags()
	{
		F &= 0x00;
	}
}