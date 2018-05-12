#pragma once

#include "Common.h"

namespace sleepy
{
	class Registers
	{
	public:
		Registers() noexcept {}

		enum class FLAG : BYTE
		{
			ZERO	= 1 << 7,
			SUB		= 1 << 6,
			HALF_CARRY	= 1 << 5,
			CARRY	= 1 << 4,
			NULL_3	= 1 << 3,
			NULL_2	= 1 << 2,
			NULL_1	= 1 << 1,
			NULL_0	= 1 << 0,
		};

		REG_8BIT A = 0x00;
		REG_8BIT F = 0x00;
		REG_8BIT B = 0x00;
		REG_8BIT C = 0x00;
		REG_8BIT D = 0x00;
		REG_8BIT E = 0x00;
		REG_8BIT H = 0x00;
		REG_8BIT L = 0x00;

		REG_16BIT PC = 0x0000;
		REG_16BIT SP = 0x0000;

		void SetAF(WORD value);
		void SetBC(WORD value);
		void SetDE(WORD value);
		void SetHL(WORD value);

		WORD ReadAF();
		WORD ReadBC();
		WORD ReadDE();
		WORD ReadHL();

		void SetFlag(FLAG flagMask);
		void ResetFlag(FLAG flagMask);

		bool ReadFlag(FLAG flagMask);

		void ResetAllFlags();

		void ZeroRegisters(bool zero_PC_SP = false);
	};
}