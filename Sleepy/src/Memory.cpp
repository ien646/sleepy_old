#include "Memory.h"

namespace sleepy
{
	Memory::Memory()
	{
		_memory = std::unique_ptr<BYTE[]>(new BYTE[TOTAL_MEM_SZ]);
	}

	BYTE Memory::readByte(ADDR address)
	{
		return _memory[address];
	}

	WORD Memory::readWord(ADDR address)
	{
		return *((WORD*)(&_memory[address]));
	}

	BYTE * Memory::data()
	{
		return &_memory[0];
	}

	void Memory::writeByte(ADDR address, BYTE value)
	{
		_memory[address] = value;
	}

	void Memory::writeWord(ADDR address, WORD value)
	{
		*((WORD*)(&_memory[address])) = value;
	}
}