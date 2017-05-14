#pragma once
#include "interface.IndexedContainer.h"
#include "Deque.h"

template <class T>
class InsertableContainer : public IndexedContainer<T>, public Deque<T> {
public:
	virtual bool insertAt(int index, T const& value) = 0;
	virtual T removeAt(int index) = 0;

	virtual ~InsertableContainer() = 0{};
};