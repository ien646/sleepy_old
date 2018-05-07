#pragma once

#include <cinttypes>
#include <memory>

#define UNREFERENCED_PARAMETER(x) x
#define UPTR std::unique_ptr

namespace sleepy
{
	/* -- Memory data types -- */
	typedef uint8_t BYTE;
	typedef uint16_t WORD;
	typedef uint16_t ADDR;

	/* -- Register value types -- */
	typedef uint8_t REG_8BIT;
	typedef uint16_t REG_16BIT;

	constexpr inline BYTE highByte(WORD val) 	
	{ 
		return (BYTE)(val >> 8); 
	}

	constexpr inline BYTE lowByte(WORD val)
	{
		return (BYTE)val;
	}

	constexpr inline WORD composeWord(BYTE hibyte, BYTE lobyte)
	{
		return (hibyte << 8) | lobyte;
	}

	constexpr inline WORD readWord(BYTE* addr)
	{
		return composeWord(addr[1], addr[0]);
	}

	constexpr inline bool getBit(BYTE value, BYTE index)
	{
		return (value & (1 << index)) == value;
	}

	constexpr inline bool getBit(WORD value, BYTE index)
	{
		return (value & (1 << index)) == value;
	}

	struct OPCODE
	{
		BYTE prefix;
		BYTE value;

		OPCODE() { }

		OPCODE(BYTE val)
		{
			prefix = 0x00;
			value = val;
		}

		OPCODE(BYTE prefx, BYTE val)
		{
			prefix = prefx;
			value = val;
		}

		OPCODE(const OPCODE& copy)
		{
			this->prefix = copy.prefix;
			this->value = copy.value;
		}

		WORD get()
		{
			return (prefix << 8) | (value);
		}

		bool operator ==(const OPCODE& o) const
		{
			return composeWord(o.prefix, prefix) == composeWord(o.value,value);
		}

		bool operator <(const OPCODE& o) const
		{
			return composeWord(o.prefix, prefix) < composeWord(o.value, value);
		}

		bool operator >(const OPCODE& o) const
		{
			return composeWord(o.prefix, prefix) > composeWord(o.value, value);
		}
	};
}