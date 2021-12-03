template<typename Type>
Array2D<Type>::Array2D() : array(nullptr), width(0), height(0), reserve(0) {}

template<typename Type>
Array2D<Type>::Array2D(unsigned w, unsigned h) : width(w), height(h), reserve(w * h)
{
	unsigned size = width * height;
	array = new Type[size];
}

template<typename Type>
Array2D<Type>::Array2D(unsigned w, unsigned h, Type initial_value) : Array2D(w, h)
{
	for (unsigned i = 0; i < width * height; i++)
	{
		array[i] = initial_value;
	}
}

template<typename Type>
Array2D<Type>::~Array2D()
{
	delete [] array;
}

template<typename Type>
inline Type * Array2D<Type>::operator [] (unsigned index)
{
	return (Type *)(&array[index * width]);
}

template<typename Type>
unsigned Array2D<Type>::getWidth() const
{
	return width;
}

template<typename Type>
unsigned Array2D<Type>::getHeight() const
{
	return height;
}

template<typename Type>
void Array2D<Type>::resize(unsigned new_width, unsigned new_height)
{
	unsigned new_size = new_width * new_height;
	if(new_size > reserve)
	{
		delete array;
		array = new Type[new_size];
		reserve = new_size;
	}

	// Save new size
	this->width = new_width;
	this->height = new_height;
}
