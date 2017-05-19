#pragma once
#include "interface.Container.h"

template <class T>
class Deque : public Container<T> {
public:
	virtual bool pushFront(const T& value) = 0;
	virtual bool pushBack(const T& value) = 0;
	virtual T popFront() = 0;
	virtual T popBack() = 0;
	virtual T peekFront() const = 0;
	virtual T peekBack() const = 0;
	virtual T& peekFront() = 0;
	virtual T& peekBack() = 0;

	virtual ~Deque() = 0{}
};