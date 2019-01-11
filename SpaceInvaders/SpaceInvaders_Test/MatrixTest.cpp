#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SpaceInvaders/Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(MatrixTest)
{
public:
	TEST_METHOD(matrix_addition_test)
	{
		const auto first_matrix = math::Matrix<float>(1, 2, { 1, 2});

		const auto second_matrix = math::Matrix<float>(2, 1, { 3,
															   4 });

		const auto expected_result = math::Matrix<float>(1, 1, { 11 });
		
		const auto result = first_matrix * second_matrix;
		Assert::IsTrue(expected_result == result);
	}
};
