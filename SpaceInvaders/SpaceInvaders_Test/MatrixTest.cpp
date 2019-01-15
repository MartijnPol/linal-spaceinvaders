#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SpaceInvaders/Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace math;

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

		const auto result = translate(first_matrix, 2.0f, 2.0f);

		const auto expected_result = math::Matrix<float>(3, 3, { 1, 2, 3,
																 4, 5, 6,
																 0, 0, 0 });
		Assert::IsTrue(expected_result == result);
	}

	TEST_METHOD(matrix_2d_rotate_test)
	{

		auto first_matrix = math::Matrix<float>(3, 3, { 1, 2, 3,
														4, 5, 6,
														0, 0, 0 });

		const auto result = rotate(first_matrix, 2.0f);

		const auto expected_result = math::Matrix<float>(3, 3, { 0.859792829f, 1.82428420f, 2.78877544f,
																 4.03246307f, 5.06675291f, 6.10104370f,
																 0, 0, 0 });
		Assert::IsTrue(expected_result == result);
	}

	TEST_METHOD(matrix_3d_scale_test)
	{

		auto scale_vector = Vector3D<float>{ 2.0f, 2.0f, 2.0f };

		const auto result = scale(scale_vector);

		const auto expected_result = math::Matrix<float>(4, 4, { 2, 0, 0, 0,
																 0, 2, 0, 0,
																 0, 0, 2, 0,
																 0, 0, 0, 1 });

		Assert::IsTrue(expected_result == result);
	}

	TEST_METHOD(matrix_3d_scale_translate_test)
	{
		auto scale_matrix = math::Matrix<float>(4, 4, { 2, 2, 4, 4,
														4, 6, 6, 6,
														8, 4, 2, 4,
														0, 0, 0, 1 });

		auto scale_vector = Vector3D<float>{ 2.0f, 2.0f, 2.0f };

		const auto result = scale(scale_matrix, scale_vector);

		const auto expected_result = math::Matrix<float>(4, 4, { 4, 4, 8, 8,
																 8, 12, 12, 12,
																 16, 8, 4, 8,
																 0, 0, 0, 1 });

		Assert::IsTrue(expected_result == result);
	}

	TEST_METHOD(matrix_3d_translate_test)
	{
		auto scale_matrix = math::Matrix<float>(4, 4, { 2, 2, 4, 4,
														4, 6, 6, 6,
														8, 4, 2, 4,
														0, 0, 0, 1 });

		const auto translate_vector = Vector3D<float>{ 2.0f, 2.0f, 2.0f };

		const auto result = translate(scale_matrix, translate_vector);

		const auto expected_result = math::Matrix<float>(4, 4, { 2, 2, 4, 6,
																 4, 6, 6, 8,
																 8, 4, 2, 6,
																 0, 0, 0, 1 });

		Assert::IsTrue(expected_result == result);
	}

	TEST_METHOD(matrix_3d_rotate_x_test)
	{
		const auto result = rotate_x(2.0f);

		const auto expected_result = math::Matrix<float>(4, 4, { 1, 0, 0, 0,
																 0, -0.416146845f, -0.909297407f, 0,
																 0, 0.909297407f, -0.416146845f, 0,
																 0, 0, 0, 1 });

		Assert::IsTrue(expected_result == result);
	}

	TEST_METHOD(matrix_3d_rotate_y_test)
	{
		const auto result = rotate_y(2.0f);

		const auto expected_result = math::Matrix<float>(4, 4, { -0.416146845f, 0, 0.909297407f, 0,
																 0, 1, 0 , 0,
																 -0.909297407f, 0, -0.416146845f, 0,
																 0, 0, 0, 1 });

		Assert::IsTrue(expected_result == result);
	}

	TEST_METHOD(matrix_3d_rotate_z_test)
	{
		const auto result = rotate_z(2.0f);

		const auto expected_result = math::Matrix<float>(4, 4, { -0.416146845f, -0.909297407f, 0, 0,
																 0.909297407f, -0.416146845f, 0 , 0,
																 0, 0, 1, 0,
																 0, 0, 0, 1 });

		Assert::IsTrue(expected_result == result);
	}
};
