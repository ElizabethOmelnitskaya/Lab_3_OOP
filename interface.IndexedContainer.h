#pragma once
#include "interface.Container.h"

template<class T>
class IndexedContainer : public virtual Container<T> {
public:
	virtual T get(int index) const = 0;
	virtual T& get(int index);
	virtual void set(int index, T const& value) = 0;

	virtual ~IndexedContainer() = 0{};
};