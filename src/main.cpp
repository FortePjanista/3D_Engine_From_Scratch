#include <iostream>
#include "matrix.h"

int main()
{
	Mat4x4f matrix = {
	{1.2f, 1.3f, 1.5f, 6.2f},
	{1.2f, 1.3f, 1.5f, 6.2f},
	{1.2f, 1.3f, 1.5f, 6.2f},
	{1.2f, 1.3f, 1.5f, 6.2f}
	};
	Mat4x4f matrix1 = {
	{1.0f, 1.0f, 1.0f, 1.0f},
	{1.0f, 1.0f, 1.0f, 1.0f},
	{1.0f, 1.0f, 1.0f, 1.0f},
	{1.2f, 1.3f, 1.5f, 6.2f}
	};
	Mat4x4f matrix2 = {
	{1.0f, 1.0f, 1.0f, 1.0f},
	{1.0f, 1.0f, 1.0f, 1.0f},
	{2.0f, 2.0f, 2.0f, 2.0f},
	{1.2f, 1.3f, 1.5f, 6.2f}
	};
	Mat4x4f matrix3;
	matrix3 = matrix1 + matrix2;
	std::cout << "The matrix: " << matrix << std::endl;
	std::cout << "The matrix1: " << matrix1 << std::endl;
	std::cout << "The matrix2: " << matrix2 << std::endl;
	std::cout << "The matrix3: " << matrix3 << std::endl;
	system("Pause");
	return 0;
}