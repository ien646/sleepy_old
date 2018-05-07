#pragma once

#include <memory>
#include <array>

#include "Common.h"

namespace sleepy
{
	class Memory
	{
	public:
		Memory();

		void writeByte(ADDR address, BYTE value);
		void writeWord(ADDR address, WORD value);
		BYTE readByte(ADDR address);
		WORD readWord(ADDR address);

		/* Return raw pointer to memory address 0x0000 */
		BYTE* data();

	private:		
		static const size_t TOTAL_MEM_SZ = 0xFFFF;
		std::unique_ptr<BYTE[]> _memory;
	};
}