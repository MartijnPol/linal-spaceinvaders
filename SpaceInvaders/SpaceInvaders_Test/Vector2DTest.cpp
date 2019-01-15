#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SpaceInvaders/Vector2D.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace math;

TEST_CLASS(Vector2DTest)
{
public:
	TEST_METHOD(vector_2d_addition_test)
	{
		const auto first_vector_2d = Vector2D<float>(1, 2);

		const auto second_vector_2d = Vector2D<float>(2, 4);

		const auto expected_result = Vector2D<float>(3, 6);

		const auto result = first_vector_2d + second_vector_2d;

		Assert::IsTrue(expected_result == result);
	}

	TEST_METHOD(vector_2d_minus_test)
	{
		const auto first_vector_2d = Vector2D<float>(1, 2);

		const auto second_vector_2d = Vector2D<float>(2, 4);

		const auto expected_result = Vector2D<float>(-1, -2);

		const auto result = first_vector_2d - second_vector_2d;

		Assert::IsTrue(expected_result == result);
	}

	TEST_METHOD(vector_2d_multiply_test)
	{
		const auto first_vector_2d = Vector2D<float>(1, 2);

		const auto scalar = 3.f;

		const auto expected_result = Vector2D<float>(3, 6);

		const auto result = first_vector_2d * scalar;

		Assert::IsTrue(expected_result == result);
	}

	TEST_METHOD(vector_2d_divide_test)
	{
		const auto first_vector_2d = Vector2D<float>(6, 9);

		const auto scalar = 3.f;

		const auto expected_result = Vector2D<float>(2, 3);

		const auto result = first_vector_2d / scalar;

		Assert::IsTrue(expected_result == result);
	}

	TEST_METHOD(vector_2d_inner_product_test)
	{
		const auto first_vector_2d = Vector2D<float>(1, 2);

		const auto second_vector_2d = Vector2D<float>(2, 4);

		const auto expected_result = 10.0f;

		const auto result = first_vector_2d.inner_product(second_vector_2d);

		Assert::IsTrue(expected_result == result);
	}

	TEST_METHOD(vector_2d_angle_test)
	{
		const auto first_vector_2d = Vector2D<float>(1, 2);

		const auto second_vector_2d = Vector2D<float>(2, 4);

		const auto expected_result = std::acos(10.0f / (2.2360679775f * 4.472135955f));

		const auto result = first_vector_2d.angle(second_vector_2d);

		Assert::IsTrue(expected_result == result);
	}

	TEST_METHOD(vector_2d_perpendicular_test)
	{
		const auto first_vector_2d = Vector2D<float>(1, 2);

		const auto expected_result = Vector2D<float>(2, -1);;

		const auto result = first_vector_2d.perpendicular();

		Assert::IsTrue(expected_result == result);
	}
};
