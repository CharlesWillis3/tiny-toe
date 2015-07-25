#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\stdafx.h"
#include "..\TinyToeCore.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TinyToeTests
{		
	
	TEST_CLASS(CoreTests)
	{

	public:
		
		TEST_CLASS_INITIALIZE(InitTinyToeCore)
		{
			
		}

		TEST_METHOD(Test_CheckForWins)
		{
			auto core = TinyToe::TinyToeCore::TinyToeCore();
			Assert::Fail(L"Not yet implemented");
		}

	};
}