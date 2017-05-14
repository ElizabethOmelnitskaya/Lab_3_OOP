#pragma once
#include "interface.IndexedContainer.h"

template<class T>
class StaticArray : public IndexedContainer<T> {
private:
	int *arr;
	int size;
	int maxNumber;
public:
	StaticArray<T>& operator=(StaticArray<T> const&);

	JavaIterator<T&>* createIterator();
	JavaIterator<T const&>* createIterator() const;

	StaticArray(int);
	StaticArray(StaticArray<T> const&);

	int Size() const;
	char* toString() const;

	T get(int) const;
	T& get(int);
	void set(int, T const&);

	~StaticArray();
};

template<class T>
StaticArray<T>::StaticArray(int _maxNumber)
{
	arr = new T[_maxNumber];
	size = _maxNumber;
}

template <typename T>
StaticArray<T>::StaticArray(StaticArray<T> const& copy) {
	maxNumber = copy->maxNumber;

	for (int i = 0; i < copy->size(); i++) {
		addElement(copy[i]);
	}
}

template<class T>
int StaticArray<T>::Size() const { return size; }

template<class T> char* StaticArray<T>::toString() const {
	char *res = new char[100]{ NULL };

	strcat(res, "StaticArray:\n ");
	for (int i = 0; i < Size(); i++) {
		if (i != 0) {
			strcat(res, ", ");
		}
		char *val = new char[100]{ NULL };

		itoa(arr[i], val, 10);
		strcat(res, val);

		delete val;
	}
	strcat(res, "  ");
	return res;
}

template<class T> T StaticArray<T>::get(int index) const{
	if (isEmpty()) return -1;
	else if (index >= size || index < 0) throw 2;
	return arr[index];
}

template<class T> T& StaticArray<T>::get(int index){
	if (isEmpty()) return -1;
	else if (index >= size || index < 0) throw 2;
	return arr[index];
}

template<class T> void StaticArray<T>::set(int index, T const& value) {
	if (isEmpty()) throw 1;
	else if (index >= size || index < 0) throw 2;
	arr[index] = value;
}

template<class T> StaticArray<T>::~StaticArray() { delete[] arr; }


template <class T, class U>
class StaticArrayIterator : public JavaIterator<U> {
private:
	int currentIterIndex;
	T *elements;
	int length;
public:
	StaticArrayIterator(T*, int);

	U next();
	bool hasNext() const;
};

template <typename T, typename U>
StaticArrayIterator<T, U>::StaticArrayIterator(T *initialElements, int _length) {
	elements = initialElements;
	length = _length
}

template <typename T, typename U>
U StaticArrayIterator<T, U>::next() {
	T value = NULL;
	if (currentIterIndex >= length) return value;
	value = elements[currentIterIndex++]

		return value;
}

template <typename T, typename U>
bool StaticArrayIterator<T, U>::hasNext() const {
	return currentIterIndex < length;
}

template <typename T>
JavaIterator<T&>* StaticArray<T>::createIterator() {
	return new StaticArrayIterator<T, T&>(elements, numberOfElements);
}

template <typename T>
JavaIterator<T const&>* StaticArray<T>::createIterator() const {
	return new StaticArrayIterator<T, T const&>(elements, numberOfElements);
}

template<class T>
StaticArray<T>& StaticArray<T>::operator=(const StaticArray<T>& other) {
	delete[] arr;
	this->size = other.size;
	arr = new T[size];
	for (int i = 0; i < size; i++)
		this->arr[i] = other.arr[i];
}

