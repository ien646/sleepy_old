#include "Memory.h"

namespace sleepy
{
	Memory::Memory() noexcept
	{
		_memory = std::unique_ptr<BYTE[]>(new BYTE[TOTAL_MEM_SZ]);
	}

	BYTE Memory::ReadByte(ADDR address)
	{
		return _memory[address];
	}

	WORD Memory::ReadWord(ADDR address)
	{
		return *((WORD*)(&_memory[address]));
	}

	BYTE * Memory::data()
	{
		return &_memory[0];
	}

	void Memory::WriteByte(ADDR address, BYTE value)
	{
		_memory[address] = value;
	}

	void Memory::WriteWord(ADDR address, WORD value)
	{
		*((WORD*)(&_memory[address])) = value;
	}
}