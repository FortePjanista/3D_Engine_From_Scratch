#ifndef VECTOR_H
#define VECTOR_H

#include "matrix.h"

template<typename Type, size_t Size>
struct Vector : public Matrix<Type, Size, 1>
{
	using Parent = Matrix<Type, Size, 1>;

	Vector();
	Vector(std::initializer_list<Type> list);

	template<typename T, size_t S>
	friend std::ostream & operator << (std::ostream & out, Vector<T, S> & vector);

	inline Type & operator [] (size_t index);
	inline Type operator [] (size_t index) const;
};

#include "vector.tpp"

typedef Vector<float, 3> Vec3f;
typedef Vector<float, 4> Vec4f;
typedef Vector<unsigned, 3> Vec3uint;

#endif // VECTOR_H
