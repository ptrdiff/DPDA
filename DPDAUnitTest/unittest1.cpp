#include "CppUnitTest.h"
#include "../DPDA/DPDA.h"
#include "../DPDA/DPDA.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DPDAUnitTest
{
    TEST_CLASS(UnitTest1)
    {
        DPDA _machine;
    public:

        TEST_METHOD(TestMethod1)
        {
            Assert::AreEqual(true, _machine.conformityCheck("()"));
        }

    };
}