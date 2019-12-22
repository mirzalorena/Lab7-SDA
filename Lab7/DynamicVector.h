#pragma once

template <typename T>
class DynamicVector
{
private:
	T* elements;
	int size;
	int capacity;

public:
	// default constructor for a DynamicVector
	DynamicVector(int capacity = 10);

	// copy constructor for a DynamicVector
	DynamicVector(const DynamicVector& DynamicVector);
	//~DynamicVector();

	// assignment operator for a DynamicVector
	DynamicVector& operator=(const DynamicVector& DynamicVector);



	// Adds an element to the current DynamicVector.
	void add(const T& element);

	void remove(int position);

	T get(int position);
	T set(int position, T newelement);
	T *getAll() const;

	int getSize() const;
	void setSize(int size) { size = size; }

private:
	// Resizes the current DynamicVector, multiplying its capacity by a given factor (real number).
	void resize(double factor = 2);

public:
	class iterator
	{
	private:
		T* ptr;
	public:
		// constructor with parameter T*
		// operator++ - pre-incrementing
		// operator++ - post-incrementing
		// dereferencing operator
		// operator!=
	};

	iterator begin()
	{
		// TODO
	}

	iterator end()
	{
		// TODO
	}
};

template <typename T>
DynamicVector<T>::DynamicVector(int capacity)
{
	this->size = 0;
	this->capacity = capacity;
	this->elements = new T[capacity];
}

template <typename T>
DynamicVector<T>::DynamicVector(const DynamicVector<T>& DynamicVector)
{
	this->size = DynamicVector.size;
	this->capacity = DynamicVector.capacity;
	this->elements = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elements[i] = DynamicVector.elements[i];
}

/*template <typename T>
DynamicVector<T>::~DynamicVector()
{
	delete[] this->elements;
}*/

template <typename T>
DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector<T>& DynamicVector)
{
	if (this == &DynamicVector)
		return *this;

	this->size = DynamicVector.size;
	this->capacity = DynamicVector.capacity;

	delete[] this->elements;
	this->elements = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elements[i] = DynamicVector.elements[i];

	return *this;

}

template <typename T>
void DynamicVector<T>::add(const T& element)
{
	if (this->size == this->capacity)
		this->resize();
	this->elements[this->size] = element;
	this->size++;
}

template <typename T>
void DynamicVector<T>::resize(double factor)
{
	this->capacity *= static_cast<int>(factor);

	T* els = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		els[i] = this->elements[i];

	delete[] this->elements;
	this->elements = els;
}

template <typename T>
int DynamicVector<T>::getSize() const
{
	return this->size;
}

template <typename T>
void DynamicVector<T>::remove(int position)
{
	//if (position >= this->size) {
//		throw std::invalid_argument("Invalid position!");
//	}
	T element = this->elements[position];
	for (int i = position; i < this->size - 1; i++) {
		this->elements[i] = this->elements[i + 1];
	}
	this->size--;
}

template <typename T>
T DynamicVector<T>::get(int position)
{
	return this->elements[position];
}

template <typename T>
T DynamicVector<T>::set(int position, T newelement)
{
	T element = this->elements[position];
	this->elements[position] = newelement;
	return element;
}

template<typename T>
T *DynamicVector<T>::getAll() const
{
	return this->elements;
}