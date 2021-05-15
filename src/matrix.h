#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>

template<typename Type, size_t Rows, size_t Columns>
struct Matrix
{
	Matrix();
	Matrix(std::initializer_list<std::initializer_list<Type>> list);
	Type m[Rows][Columns] = {0};

	template<typename T, size_t R, size_t C>
	friend std::ostream& operator << (std::ostream & out, const Matrix<T, R, C> & matrix);

	inline Type * operator [] (size_t index) const;

	inline Matrix<Type, Rows, Columns> & operator += (const Matrix<Type, Rows, Columns> & other);
	inline Matrix<Type, Rows, Columns> operator + (const Matrix<Type, Rows, Columns> & right) const;
	inline Matrix<Type, Rows, Columns> & operator -= (const Matrix<Type, Rows, Columns> & other);
	inline Matrix<Type, Rows, Columns> operator - (const Matrix<Type, Rows, Columns> & right) const;
};

#include "matrix.tpp"

typedef Matrix<float, 4, 4> Mat4x4f;

#endif // MATRIX_H
