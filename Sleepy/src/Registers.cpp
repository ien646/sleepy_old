#include "Registers.h"

namespace sleepy
{
	void Registers::setAF(WORD value)
	{
		A = highByte(value);
		F = lowByte(value);
	}

	void Registers::setBC(WORD value)
	{
		B = highByte(value);
		C = lowByte(value);
	}

	void Registers::setDE(WORD value)
	{
		D = highByte(value);
		E = lowByte(value);
	}

	void Registers::setHL(WORD value)
	{
		H = highByte(value);
		L = lowByte(value);
	}

	WORD Registers::readAF()
	{
		return composeWord(A, F);
	}

	WORD Registers::readBC()
	{
		return composeWord(B, C);
	}

	WORD Registers::readDE()
	{
		return composeWord(D, E);
	}

	WORD Registers::readHL()
	{
		return composeWord(H, L);
	}

	void Registers::setFlag(FLAG flagMask)
	{
		F |= (BYTE)flagMask;
	}

	void Registers::resetFlag(FLAG flagMask)
	{
		F &= ((BYTE)flagMask ^ 0xFF);
	}

	void Registers::resetAllFlags()
	{
		F &= 0x00;
	}
}