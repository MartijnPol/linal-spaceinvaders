#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SpaceInvaders/Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(MatrixTest)
{
public:
	TEST_METHOD(matrix_multiply_test)
	{
		const auto first_matrix = math::Matrix<float>(1, 2, { 1, 2 });

		const auto second_matrix = math::Matrix<float>(2, 1, { 3,
															   4 });

		const auto first_expected_result = math::Matrix<float>(1, 1, { 11 });
		const auto first_result = first_matrix * second_matrix;
		Assert::IsTrue(first_expected_result == first_result);
	}

	TEST_METHOD(matrix_2d_scale_test)
	{
		auto first_matrix = math::Matrix<float>(3, 3, { 1, 2, 3,
														4, 5, 6,
														0, 0, 0 });

		const auto expected_result = math::Matrix<float>(3, 3, { 2, 4,  6,
																 8, 10, 12,
																 0, 0,  0 });
		const auto result = scale(first_matrix, 2.0f, 2.0f);
		Assert::IsTrue(expected_result == result);
	}

	TEST_METHOD(matrix_2d_translate_test)
	{

		auto first_matrix = math::Matrix<float>(3, 3, { 1, 2, 3,
														4, 5, 6,
														0, 0, 0 });

		const auto result = math::translate(first_matrix, 2.0f, 2.0f);

		const auto expected_result = math::Matrix<float>(3, 3, { 1, 2, 3,
																 4, 5, 6,
																 0, 0, 0 });
		Assert::IsTrue(expected_result == result);
	}
};
