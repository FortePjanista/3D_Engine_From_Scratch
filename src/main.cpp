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
	std::cout << "The matrix: " << matrix << std::endl;
	system("Pause");
	return 0;
}