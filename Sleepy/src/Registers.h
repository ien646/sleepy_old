#pragma once

#include "Common.h"

namespace sleepy
{
	class Registers
	{
	public:
		enum class FLAG : BYTE
		{
			ZERO	= 1 << 7,
			SUB		= 1 << 6,
			HCARRY	= 1 << 5,
			CARRY	= 1 << 4,
			NULL_3	= 1 << 3,
			NULL_2	= 1 << 2,
			NULL_1	= 1 << 1,
			NULL_0	= 1 << 0,
		};

		REG_8BIT A;
		REG_8BIT F;
		REG_8BIT B;
		REG_8BIT C;
		REG_8BIT D;
		REG_8BIT E;
		REG_8BIT H;
		REG_8BIT L;

		REG_16BIT PC;
		REG_16BIT SP;

		void setAF(WORD value);
		void setBC(WORD value);
		void setDE(WORD value);
		void setHL(WORD value);

		WORD readAF();
		WORD readBC();
		WORD readDE();
		WORD readHL();

		void SetFlag(FLAG flagMask);
		void ResetFlag(FLAG flagMask);
	};
}