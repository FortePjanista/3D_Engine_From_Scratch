#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>

template<typename Type, int Size>
struct Matrix
{
	Matrix();
	Matrix(std::initializer_list<std::initializer_list<Type>> list);
	Type m[Size][Size] = {0};

	template<typename T, int S>
	friend std::ostream& operator << (std::ostream & out, const Matrix<T, S> & matrix);
};

#include "matrix.tpp"

typedef Matrix<float, 4> Mat4x4f;

#endif // MATRIX_H
