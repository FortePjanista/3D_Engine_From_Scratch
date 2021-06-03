#ifndef ARRAY_2D_H
#define ARRAY_2D_H

// A dynamic array 2d, held as 1d for performance.
template<typename Type>
class Array2D
{
public:
	Array2D();
	Array2D(unsigned width, unsigned height);
	Array2D(unsigned width, unsigned height, Type initial_values);
	~Array2D();
	inline Type * operator [] (unsigned index);

	unsigned getWidth() const;
	unsigned getHeight() const;
	void resize(unsigned new_width, unsigned new_height);

private:
	Type * array;
	unsigned width;
	unsigned height;
	unsigned reserve;
};

#include "array2d.tpp"

#endif // ARRAY_2D_H
