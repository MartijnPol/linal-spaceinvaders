#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SpaceInvaders/Math.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(DegreesToRadiusTest)
{
public:
	TEST_METHOD(degrees_radius_test)
	{
		const auto result = math::Math::degrees_to_radius(0.6);
		const auto expected_result = 31;
		Assert::IsTrue(expected_result == result);
	}
};
