#pragma once

template<class T>
class Container{
public:

	virtual int Size() const = 0;
	virtual bool isEmpty() const { return Size() == 0; }
	virtual char* toString() const = 0;

	virtual ~Container() = 0{};
};