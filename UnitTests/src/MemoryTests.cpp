#include "CppUnitTest.h"

#include "Memory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sleepy;

namespace sleepy
{		
	TEST_CLASS(MemoryTests)
	{
	public:
		TEST_METHOD(WriteWord_CorrectEndianess)
		{
			// Setup
			Memory memory;
			BYTE* data = memory.data();

			// Run
			memory.WriteWord((ADDR)0x0000, (WORD)0xF0AE);
			
			// Assert
			Assert::IsTrue(0xAE == data[0]);
			Assert::IsTrue(0xF0 == data[1]);
		}

		TEST_METHOD(ReadWord_CorrectEndianess)
		{
			// Setup
			Memory memory;
			BYTE* data = memory.data();
			((WORD*)memory.data())[0] = 0xF0AE;

			// Run
			WORD res = memory.ReadWord((ADDR)0x0000);

			// Assert
			Assert::IsTrue(0xAE == data[0]);
			Assert::IsTrue(0xF0 == data[1]);

			Assert::IsTrue(0xF0AE == res);
		}

		TEST_METHOD(Write_Read_Byte_CorrectAddr)
		{
			// Setup
			Memory memory;
			memory.WriteByte(0xFA0F, 0xAD);
			memory.WriteByte(0xAA0A, 0xB7);

			Assert::IsTrue(0xAD == memory.ReadByte(0xFA0F));
			Assert::IsTrue(0xB7 == memory.ReadByte(0xAA0A));
		}

		TEST_METHOD(Write_Read_Word_CorrectAddr)
		{
			// Setup
			Memory memory;
			memory.WriteWord(0xFA0F, 0xADAD);
			memory.WriteWord(0xAA0A, 0xB7B7);

			Assert::IsTrue(0xADAD == memory.ReadWord(0xFA0F));
			Assert::IsTrue(0xB7B7 == memory.ReadWord(0xAA0A));
		}

		TEST_METHOD(MemoryRangeTest)
		{
			Memory memory;
			memory.WriteByte(0x0000, 0x00);
			memory.WriteByte(0xFFFF, 0x00);
		}
	};
}