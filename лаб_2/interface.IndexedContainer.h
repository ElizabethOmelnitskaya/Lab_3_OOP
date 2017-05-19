#pragma once
#include "interface.Container.h"

template <class T>
class IndexedContainer : public Container<T> {
public:
	virtual T get(int index) const = 0;
	virtual T& get(int index) = 0;
	virtual bool set(int index, const T& value) = 0;

	T& operator [](int index){ return get(index); }

	virtual ~IndexedContainer() = 0{}
};