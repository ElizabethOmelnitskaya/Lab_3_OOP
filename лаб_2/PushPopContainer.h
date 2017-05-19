#pragma once
#include "interface.Container.h"

template <class T>
class PushPopContainer : public virtual Container<T> {
public:
	virtual bool push(const T& value) = 0;
	virtual T pop() = 0;
	virtual T peek() const = 0;
	virtual T& peek() = 0;

	virtual ~PushPopContainer() = 0 {};
};