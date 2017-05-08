#pragma once
#include "interface.IndexedContainer.h"

template<class T>
class StaticArray : public IndexedContainer<T> {
private:
	T *arr;
	int size;
public:
	StaticArray(int);

	int Size() const;
	bool isEmpty() const;
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

template<class T>
int StaticArray<T>::Size() const { return size; }

template<class T>
bool StaticArray<T>::isEmpty() const { return size == 0; }

template<class T>
char* StaticArray<T>::toString() const {
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

template<class T>
T StaticArray<T>::get(int index) const{
	if (isEmpty()) return -1;
	else if (index >= size || index < 0) throw 2;
	return arr[index];
}

template<class T>
T& StaticArray<T>::get(int index) {
	if (isEmpty()) return -1;
	else if (index >= size || index < 0) throw 2;
	return &(arr[index]);
}

template<class T>
void StaticArray<T>::set(int index, T const& value) {
	if (isEmpty()) throw 1;
	else if (index >= size || index < 0) throw 2;
	arr[index] = value;
}

template<class T>
StaticArray<T>::~StaticArray() { delete[] arr; }

