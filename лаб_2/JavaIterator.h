#pragma once

template <class T>
class JavaIterator {
public:
	virtual T& next() = 0;
	virtual bool hasNext() = 0;
	virtual ~JavaIterator() {};
};