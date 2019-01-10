#ifndef MATRIX_TEST_H
#define MATRIX_TEST_H

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SpaceInvaders/Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace space_invaders
{
	TEST_CLASS(MatrixTest)
	{
	public:
		TEST_METHOD(matrix_addition_test)
		{
			const auto first_matrix = math::Matrix<float>(2, 3, { 2, 0, -1,
																 -3, 2, 4 });

			const auto second_matrix = math::Matrix<float>(2, 3, { -2, 4, 3,
																   3, 2, 0 });

			const auto expected_result = math::Matrix<float>(2, 3, { 0, 4, 2,
																	 0, 4, 4 });

			Assert::AreEqual(expected_result, first_matrix * second_matrix);
		}
	};
}

#endif