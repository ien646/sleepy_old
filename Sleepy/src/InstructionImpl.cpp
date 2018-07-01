#include "InstructionImpl.h"
#include "System.h"

namespace sleepy
{
	InstructionImpl::InstructionImpl(System& sys):
		_sys(sys),
		_mem(sys.Memory),
		_cpu(sys.CPU),
		_regs(sys.CPU.Registers)
	{

	}

	void InstructionImpl::Opcode_ADD_A_V8(BYTE v8)
	{
		_regs.ResetAllFlags();

		WORD result = _regs.A + v8;

		if ((BYTE)result == 0x00)
		{
			_regs.SetFlag(FLAG_ZERO);
		}

		if (result > 0xFF)
		{
			_regs.SetFlag(FLAG_CARRY);
			_regs.SetFlag(FLAG_HCARRY);
		}
		else if (result > 0x0F)
		{
			_regs.SetFlag(FLAG_HCARRY);
		}

		_regs.A = (BYTE)result;
	}

	void InstructionImpl::Opcode_ADD_HL_V16(WORD v16)
	{
		_regs.ResetFlag(FLAG_SUB);

		DWORD result = _regs.ReadHL() + v16;
		if (result > 0x0000FFFF)
		{
			_regs.SetFlag(FLAG_CARRY);
			_regs.SetFlag(FLAG_HCARRY);
		}
		else if (result > 0x000000FF)
		{
			_regs.SetFlag(FLAG_HCARRY);
		}

		_regs.SetHL((WORD)result);
	}

	void InstructionImpl::Opcode_SUB_A_V8(BYTE v8)
	{
		_regs.ResetAllFlags();
		_regs.SetFlag(FLAG_SUB);

		WORD result = _regs.A - v8;

		if ((BYTE)result == 0x00)
		{
			_regs.SetFlag(FLAG_ZERO);
		}
		if (result > 0xFF)
		{
			_regs.SetFlag(FLAG_CARRY);
			_regs.SetFlag(FLAG_HCARRY);
		}
		else if (result > 0x0F)
		{
			_regs.SetFlag(FLAG_HCARRY);
		}

		_regs.A = (BYTE)result;
	}

	void InstructionImpl::Opcode_ADC_A_V8(BYTE v8)
	{
		WORD result = _regs.A + v8 + (_regs.ReadFlag(FLAG_CARRY) ? 1 : 0);

		_regs.ResetAllFlags();

		if ((BYTE)result == 0x00)
		{
			_regs.SetFlag(FLAG_ZERO);
		}

		if (result > 0xFF)
		{
			_regs.SetFlag(FLAG_CARRY);
			_regs.SetFlag(FLAG_HCARRY);
		}
		else if (result > 0x0F)
		{
			_regs.SetFlag(FLAG_HCARRY);
		}

		_regs.A = (BYTE)result;
	}

	void InstructionImpl::Opcode_SBC_A_V8(BYTE v8)
	{
		WORD result = _regs.A - (v8 + (_regs.ReadFlag(FLAG_CARRY) ? 1 : 0));

		_regs.ResetAllFlags();
		_regs.SetFlag(FLAG_SUB);

		if ((BYTE)result == 0x00)
		{
			_regs.SetFlag(FLAG_ZERO);
		}

		if (result > 0xFF)
		{
			_regs.SetFlag(FLAG_CARRY);
			_regs.SetFlag(FLAG_HCARRY);
		}
		else if (result > 0x0F)
		{
			_regs.SetFlag(FLAG_HCARRY);
		}

		_regs.A = (BYTE)result;
	}

	void InstructionImpl::Opcode_AND_A_V8(BYTE v8)
	{
		_regs.ResetAllFlags();
		_regs.SetFlag(FLAG_SUB);

		BYTE result = (_regs.A & v8);

		if (result == 0x00)
		{
			_regs.SetFlag(FLAG_ZERO);
		}

		_regs.A = result;
	}

	void InstructionImpl::Opcode_OR_A_V8(BYTE v8)
	{
		_regs.ResetAllFlags();

		BYTE result = (_regs.A | v8);

		if (result == 0x00)
		{
			_regs.SetFlag(FLAG_ZERO);
		}

		_regs.A = result;
	}

	void InstructionImpl::Opcode_XOR_A_V8(BYTE v8)
	{
		_regs.ResetAllFlags();

		BYTE result = (_regs.A ^ v8);

		if (result == 0x00)
		{
			_regs.SetFlag(FLAG_ZERO);
		}

		_regs.A = result;
	}

	void InstructionImpl::Opcode_INC_R8(REG_8BIT& reg)
	{
		_regs.ResetFlag(FLAG_ZERO);
		_regs.ResetFlag(FLAG_HCARRY);
		_regs.ResetFlag(FLAG_SUB);

		++reg;

		if (reg == 0x00)
		{
			_regs.SetFlag(FLAG_ZERO);
		}

		if (reg > 0x0F)
		{
			_regs.SetFlag(FLAG_HCARRY);
		}
	}

	void InstructionImpl::Opcode_DEC_R8(REG_8BIT& reg)
	{
		_regs.ResetFlag(FLAG_ZERO);
		_regs.ResetFlag(FLAG_HCARRY);
		_regs.SetFlag(FLAG_SUB);

		--reg;

		if (reg == 0x00)
		{
			_regs.SetFlag(FLAG_ZERO);
		}

		if (reg > 0x0F)
		{
			_regs.SetFlag(FLAG_HCARRY);
		}
	}

	void InstructionImpl::Opcode_CP_R8(BYTE reg)
	{
		_regs.ResetAllFlags();
		_regs.SetFlag(FLAG_SUB);

		WORD result = _regs.A - reg;

		if ((BYTE)result == 0x00)
		{
			_regs.SetFlag(FLAG_ZERO);
		}
		if (result > 0xFF)
		{
			_regs.SetFlag(FLAG_CARRY);
			_regs.SetFlag(FLAG_HCARRY);
		}
		else if (result > 0x0F)
		{
			_regs.SetFlag(FLAG_HCARRY);
		}
		/* -- omit result -- */
	}

	void InstructionImpl::Opcode_RRCA()
	{
		bool bit_0 = getBit(_regs.A, 0);

		_regs.ResetAllFlags();

		BYTE result = (_regs.A >> 1);
		if (bit_0)
		{
			_regs.SetFlag(FLAG_CARRY);
			result |= 0x80;
		}

		_regs.A = result;
	}

	void InstructionImpl::Opcode_RRA()
	{
		bool bit_0 = getBit(_regs.A, 0);

		_regs.ResetAllFlags();

		BYTE result = (_regs.A >> 1);
		if (bit_0)
		{
			_regs.SetFlag(FLAG_CARRY);
		}

		_regs.A = result;
	}

	void InstructionImpl::Opcode_RLCA()
	{
		bool bit_7 = getBit(_regs.A, 7);

		_regs.ResetAllFlags();

		BYTE result = (_regs.A << 1);
		if (bit_7)
		{
			_regs.SetFlag(FLAG_CARRY);
			result |= 0x01;
		}

		_regs.A = result;
	}

	void InstructionImpl::Opcode_RLA()
	{
		bool bit_7 = getBit(_regs.A, 7);

		_regs.ResetAllFlags();

		BYTE result = (_regs.A << 1);
		if (bit_7)
		{
			_regs.SetFlag(FLAG_CARRY);
		}

		_regs.A = result;
	}

	void InstructionImpl::Opcode_CPL()
	{
		_regs.SetFlag(FLAG_SUB);
		_regs.SetFlag(FLAG_HCARRY);
		_regs.A ^= 0xFF;
	}

	void InstructionImpl::Opcode_CCF()
	{
		_regs.ResetFlag(FLAG_SUB);
		_regs.ResetFlag(FLAG_HCARRY);
		_regs.InvertFlag(FLAG_CARRY);
	}

	void InstructionImpl::Opcode_DAA()
	{
		BYTE lowNibble = 0x0F & _regs.A;
		BYTE hiNibble = (0xF0 & _regs.A) >> 4;
		if ((lowNibble > 9) || (_regs.ReadFlag(FLAG_HCARRY)))
		{
			_regs.A += 0x06;
		}
		if ((hiNibble > 9) || (_regs.ReadFlag(FLAG_CARRY)))
		{
			_regs.A += 0x60;
			_regs.SetFlag(FLAG_CARRY);
		}
		if (_regs.A == 0x00)
		{
			_regs.SetFlag(FLAG_ZERO);
		}
		_regs.ResetFlag(FLAG_HCARRY);
	}
}