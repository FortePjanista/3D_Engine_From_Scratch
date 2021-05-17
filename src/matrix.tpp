#include <iostream>
#include <algorithm>
#include "error.h"

template<typename Type, size_t Rows, size_t Columns>
Matrix<Type, Rows, Columns>::Matrix() {}

template<typename Type, size_t Rows, size_t Columns>
Matrix<Type, Rows, Columns>::Matrix(std::initializer_list<std::initializer_list<Type>> list)
{
	DEBUG_ASSERT(list.size() == Rows, "Size in initializer_list does not match the declared size in Matrix");
	auto inner_list = list.begin();
	for (unsigned i = 0; i < list.size(); i++)
	{
		DEBUG_ASSERT(inner_list->size() == Columns, "Size in initializer_list does not match the declared size in Matrix");
		std::copy(inner_list->begin(), inner_list->end(), m[i]);
		inner_list++;
	}
}

template<typename Type, size_t Rows, size_t Columns>
std::ostream & operator << (std::ostream & out, const Matrix<Type, Rows, Columns> & matrix)
{
	out << std::endl;
	for (unsigned i = 0; i < Rows; i++)
	{
		out << "[ ";
		for (unsigned j = 0; j < Columns; j++)
		{
			out << matrix.m[i][j] << " ";
		}
		out << "]" << std::endl;
	}
	return out;
}

template<typename Type, size_t Rows, size_t Columns>
inline Type * Matrix<Type, Rows, Columns>::operator [] (size_t index) const
{
	return (Type *)(&m[index]);
}

template<typename Type, size_t Rows, size_t Columns>
inline Matrix<Type, Rows, Columns> & Matrix<Type, Rows, Columns>::operator += (const Matrix<Type, Rows, Columns> & other)
{
	for (unsigned i = 0; i < Rows; i++)
	{
		for (unsigned j = 0; j < Columns; j++)
		{
			m[i][j] += other[i][j];
		}
	}
	return *this;
}

template<typename Type, size_t Rows, size_t Columns>
inline Matrix<Type, Rows, Columns> Matrix<Type, Rows, Columns>::operator + (const Matrix<Type, Rows, Columns> & right) const
{
	Matrix<Type, Rows, Columns> tmp(*this);
	tmp += right;
	return tmp;
}

template<typename Type, size_t Rows, size_t Columns>
inline Matrix<Type, Rows, Columns> & Matrix<Type, Rows, Columns>::operator -= (const Matrix<Type, Rows, Columns> & other)
{
	for (unsigned i = 0; i < Rows; i++)
	{
		for (unsigned j = 0; j < Columns; j++)
		{
			m[i][j] -= other[i][j];
		}
	}
	return *this;
}

template<typename Type, size_t Rows, size_t Columns>
inline Matrix<Type, Rows, Columns> Matrix<Type, Rows, Columns>::operator - (const Matrix<Type, Rows, Columns> & right) const
{
	Matrix<Type, Rows, Columns> tmp(*this);
	tmp -= right;
	return tmp;
}

template<typename Type, size_t Rows, size_t Columns>
template<size_t RowsOfTheSecondMatrix, size_t ColumnsOfSecondMatrix>
inline Matrix<Type, Rows, ColumnsOfSecondMatrix> Matrix<Type, Rows, Columns>::operator * (const Matrix<Type, RowsOfTheSecondMatrix, ColumnsOfSecondMatrix> & right) const
{
	static_assert(Columns == RowsOfTheSecondMatrix, "The number of columns in the first matrix should be equal to the number of rows in the second one.");
	Matrix<Type, Rows, ColumnsOfSecondMatrix> tmp;

	for (unsigned i = 0; i < Rows; i++)
	{
		for (unsigned c = 0; c < ColumnsOfSecondMatrix; c++)
		{
			for (unsigned j = 0; j < Columns; j++)
			{
				tmp[i][c] += m[i][j] * right[j][c];
			}
		}
	}

	return tmp;
}