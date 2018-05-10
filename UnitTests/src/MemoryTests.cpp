#include "CppUnitTest.h"

#include "Memory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sleepy;

namespace UnitTests
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
	};
}