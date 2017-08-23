#include "..\stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;



namespace GameEngine
{
	namespace EngineItself
	{
		TEST_CLASS(EngineClass)
		{
		private:
			Engine eng;
		public:
			TEST_CLASS_INITIALIZE(methodName)
			{
				// test class initialization  code
			}

			TEST_METHOD(is_sphfluid_initially_null)
			{
				Assert::AreEqual(0, eng.getSPHFluid() == nullptr ? 0 : 1);
			}

			TEST_METHOD(is_sphfluid_remove_crashing_when_null)
			{
				eng.removeSPHFluid();
				Assert::AreEqual(0, eng.getSPHFluid() == nullptr ? 0 : 1);

			}

			TEST_METHOD(is_sphfluid_can_added_success)
			{
				eng.addSPHFluid();
				Assert::AreNotEqual(0, eng.getSPHFluid() == nullptr ? 0 : 1);
			}

			TEST_METHOD(is_sphfluid_can_removed_success)
			{
				std::ofstream file("wow.txt");
				eng.addSPHFluid();
				Assert::AreNotEqual(0, eng.getSPHFluid() == nullptr ? 0 : 1);
				eng.removeSPHFluid();
				Assert::AreEqual(0, eng.getSPHFluid() == nullptr ? 0 : 1);
			}
		};
	}
}