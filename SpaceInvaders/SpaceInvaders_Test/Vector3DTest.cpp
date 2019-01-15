#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SpaceInvaders/Vector3D.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace math;

TEST_CLASS(Vector3DTest)
{
public:
	TEST_METHOD(vector_3d_addition_test)
	{
		auto first_vector_3d = Vector3D<float>(1, 2, 3);

		const auto second_vector_3d = Vector3D<float>(2, 4, 2);

		const auto expected_result = Vector3D<float>(3, 6, 5);

		first_vector_3d += second_vector_3d;

		Assert::IsTrue(expected_result == first_vector_3d);
	}

	TEST_METHOD(vector_3d_minus_test)
	{
		auto first_vector_3d = Vector3D<float>(1, 2, 3);

		const auto second_vector_3d = Vector3D<float>(2, 4, 2);

		const auto expected_result = Vector3D<float>(-1, -2, 1);

		first_vector_3d -= second_vector_3d;

		Assert::IsTrue(expected_result == first_vector_3d);
	}

	TEST_METHOD(vector_3d_multiply_test)
	{
		auto first_vector_3d = Vector3D<float>(1, 2, 3);

		const auto scalar = 3.f;

		const auto expected_result = Vector3D<float>(3, 6, 9);

		first_vector_3d *= scalar;

		Assert::IsTrue(expected_result == first_vector_3d);
	}

	TEST_METHOD(vector_3d_inner_product_test)
	{
		const auto first_vector_3d = Vector3D<float>(1, 2, 3);

		const auto second_vector_3d = Vector3D<float>(2, 4, 6);

		const auto expected_result = 28.0f;

		const auto result = first_vector_3d.inner_product(second_vector_3d);

		Assert::IsTrue(expected_result == result);
	}

	TEST_METHOD(vector_3d_angle_test)
	{
		const auto first_vector_3d = Vector3D<float>(1, 2, 3);

		const auto second_vector_3d = Vector3D<float>(2, 4, 6);

		const auto expected_result = std::acos(28.0f / (3.74165738677f * 7.48331477355f));

		const auto result = first_vector_3d.angle(second_vector_3d);

		Assert::IsTrue(expected_result == result);
	}

	TEST_METHOD(vector_3d_length_test)
	{
		const auto first_vector_3d = Vector3D<float>(1, 2, 3);

		const auto expected_result = 3.74165738677f;

		const auto result = first_vector_3d.length();

		Assert::IsTrue(expected_result == result);
	}

	TEST_METHOD(vector_3d_cross_product_test)
	{
		const auto first_vector_3d = Vector3D<float>(1, 2, 3);

		const auto second_vector_3d = Vector3D<float>(2, 4, 6);

		const auto expected_result = Vector3D<float>(0, 0, 0);

		const auto result = first_vector_3d.cross_product(second_vector_3d);

		Assert::IsTrue(expected_result == result);
	}

	TEST_METHOD(vector_3d_normalize_test)
	{
		auto first_vector_3d = Vector3D<float>(2, 4, 6);

		const auto expected_result = Vector3D<float>(2 / 7.48331477355f, 4 / 7.48331477355f, 6 / 7.48331477355f);

		first_vector_3d.normalize();

		Assert::IsTrue(expected_result == first_vector_3d);
	}
};
