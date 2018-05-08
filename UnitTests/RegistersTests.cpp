#include "stdafx.h"
#include "CppUnitTest.h"
#include "Registers.h"
#include "Memory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sleepy;

namespace UnitTests
{
	TEST_CLASS(MemoryTests)
	{
		TEST_METHOD(Set_8Bit_RegisterPair_As16bit_Endianess)
		{
			// Setup
			Registers r;

			// Run
			r.SetAF(0xFF00);
			r.SetBC(0xEE11);
			r.SetDE(0xDD22);
			r.SetHL(0xCC33);
			
			// Assert
			Assert::IsTrue(0x00 == r.F);
			Assert::IsTrue(0xFF == r.A);

			Assert::IsTrue(0x11 == r.C);
			Assert::IsTrue(0xEE == r.B);

			Assert::IsTrue(0x22 == r.E);
			Assert::IsTrue(0xDD == r.D);

			Assert::IsTrue(0x33 == r.L);
			Assert::IsTrue(0xCC == r.H);
		}

		TEST_METHOD(Read_8Bit_RegisterPair_As16bit_Endianess)
		{
			// Setup
			Registers r;
			r.A = 0xFF;
			r.F = 0x00;
			r.B = 0xEE;
			r.C = 0x11;
			r.D = 0xDD;
			r.E = 0x22;
			r.H = 0xCC;
			r.L = 0x33;

			// Run
			WORD AF = r.ReadAF();
			WORD BC = r.ReadBC();
			WORD DE = r.ReadDE();
			WORD HL = r.ReadHL();

			// Assert
			Assert::IsTrue((WORD)0xFF00 == AF);
			Assert::IsTrue((WORD)0xEE11 == BC);
			Assert::IsTrue((WORD)0xDD22 == DE);
			Assert::IsTrue((WORD)0xCC33 == HL);
		};

		TEST_METHOD(Set_Flags_CorrectBit)
		{
			Registers r;

			r.F = 0x00;
			r.SetFlag(Registers::FLAG::NULL_0);
			Assert::IsTrue(0b00000001 == r.F);

			r.F = 0x00;
			r.SetFlag(Registers::FLAG::NULL_1);
			Assert::IsTrue(0b00000010 == r.F);

			r.F = 0x00;
			r.SetFlag(Registers::FLAG::NULL_2);
			Assert::IsTrue(0b00000100 == r.F);

			r.F = 0x00;
			r.SetFlag(Registers::FLAG::NULL_3);
			Assert::IsTrue(0b00001000 == r.F);

			r.F = 0x00;
			r.SetFlag(Registers::FLAG::CARRY);
			Assert::IsTrue(0b00010000 == r.F);

			r.F = 0x00;
			r.SetFlag(Registers::FLAG::HCARRY);
			Assert::IsTrue(0b00100000 == r.F);

			r.F = 0x00;
			r.SetFlag(Registers::FLAG::SUB);
			Assert::IsTrue(0b01000000 == r.F);

			r.F = 0x00;
			r.SetFlag(Registers::FLAG::ZERO);
			Assert::IsTrue(0b10000000 == r.F);
		}

		TEST_METHOD(Reset_Flags_CorrectBit)
		{
			Registers r;

			r.F = 0xFF;
			r.ResetFlag(Registers::FLAG::NULL_0);
			Assert::IsTrue(0b11111110 == r.F);

			r.F = 0xFF;
			r.ResetFlag(Registers::FLAG::NULL_1);
			Assert::IsTrue(0b11111101 == r.F);

			r.F = 0xFF;
			r.ResetFlag(Registers::FLAG::NULL_2);
			Assert::IsTrue(0b11111011 == r.F);

			r.F = 0xFF;
			r.ResetFlag(Registers::FLAG::NULL_3);
			Assert::IsTrue(0b11110111 == r.F);

			r.F = 0xFF;
			r.ResetFlag(Registers::FLAG::CARRY);
			Assert::IsTrue(0b11101111 == r.F);

			r.F = 0xFF;
			r.ResetFlag(Registers::FLAG::HCARRY);
			Assert::IsTrue(0b11011111 == r.F);

			r.F = 0xFF;
			r.ResetFlag(Registers::FLAG::SUB);
			Assert::IsTrue(0b10111111 == r.F);

			r.F = 0xFF;
			r.ResetFlag(Registers::FLAG::ZERO);
			Assert::IsTrue(0b01111111 == r.F);
		}
	};
}