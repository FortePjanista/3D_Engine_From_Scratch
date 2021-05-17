template<typename Type, size_t Size>
Vector<Type, Size>::Vector() {}

template<typename Type, size_t Size>
Vector<Type, Size>::Vector(std::initializer_list<Type> list)
{
	DEBUG_ASSERT(list.size() == Size, "Size in initializer_list does not match the declared size in the Vector");
	auto it = list.begin();
	for(int i = 0; i < Size; i++)
	{
		Parent::m[i][0] = *it++;
	}
}

template<typename Type, size_t Size>
std::ostream & operator << (std::ostream & out, Vector<Type, Size> & vector)
{
	out << "(";
	for (unsigned i = 0; i < Size - 1; i++)
	{
		out << vector[i] << ", ";
	}
	out << vector[Size - 1] << ")";
	return out;
}

template<typename Type, size_t Size>
inline Type & Vector<Type, Size>::operator [] (size_t index)
{
	return reinterpret_cast<Type *>(Parent::m)[index];
}

template<typename Type, size_t Size>
inline Type Vector<Type, Size>::operator [] (size_t index) const
{
	return (Parent::m)[index][0];
}

template<typename Type, size_t Size, size_t Rows, size_t Columns>
inline Vector<Type, Size> operator * (const Matrix<Type, Rows, Columns> & matrix, const Vector<Type, Size> & vector)
{
	return (Vector<Type, Size> &)(matrix * (Matrix<Type, Size, 1> &)vector);
}