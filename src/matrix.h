#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>

template<typename Type, size_t Size>
struct Matrix
{
	Matrix();
	Matrix(std::initializer_list<std::initializer_list<Type>> list);
	Type m[Size][Size] = {0};

	template<typename T, size_t S>
	friend std::ostream& operator << (std::ostream & out, const Matrix<T, S> & matrix);

	inline Type * operator [] (size_t index) const;

	inline Matrix<Type, Size> operator + (const Matrix<Type, Size> & right) const;
	inline Matrix<Type, Size> & operator += (const Matrix<Type, Size> & other);
	inline Matrix<Type, Size> operator - (const Matrix<Type, Size> & right) const;
	inline Matrix<Type, Size> & operator -= (const Matrix<Type, Size> & other);
};

#include "matrix.tpp"

typedef Matrix<float, 4> Mat4x4f;

#endif // MATRIX_H
