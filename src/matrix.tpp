#include <iostream>
#include <algorithm>
#include "error.h"

template<typename Type, int Size>
Matrix<Type, Size>::Matrix<Type, Size>() {}

template<typename Type, int Size>
Matrix<Type, Size>::Matrix<Type, Size>(std::initializer_list<std::initializer_list<Type>> list)
{
	DEBUG_ASSERT(list.size() == Size, "Size in initializer_list does not match the declared size in Matrix");
	auto inner_list = list.begin();
	for (int i = 0; i < list.size(); i++)
	{
		DEBUG_ASSERT(inner_list->size() == Size, "Size in initializer_list does not match the declared size in Matrix");
		std::copy(inner_list->begin(), inner_list->end(), m[i]);
		inner_list++;
	}
}

template<typename Type, int Size>
std::ostream& operator << (std::ostream & out, const Matrix<Type, Size> & matrix)
{
	out << std::endl;
	for (int i = 0; i < Size; i++)
	{
		out << "[ ";
		for (int j = 0; j < Size; j++)
		{
			out << matrix.m[i][j] << " ";
		}
		out << "]" << std::endl;
	}
	return out;
}