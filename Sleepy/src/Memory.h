#pragma once

#include <memory>
#include <array>

#include "Common.h"

namespace sleepy
{
	class Memory
	{
	public:
		Memory() noexcept;

		void WriteByte(ADDR address, BYTE value);
		void WriteWord(ADDR address, WORD value);
		BYTE ReadByte(ADDR address);
		WORD ReadWord(ADDR address);

		/* Return raw pointer to memory address 0x0000 */
		BYTE* data();

	private:		
		static const size_t TOTAL_MEM_SZ = 0x10000;
		std::unique_ptr<BYTE[]> _memory;
	};
}