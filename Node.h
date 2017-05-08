#pragma once

template<class T>
class node
{
public:
	T value;
	node *prev, *next;
	node();
};

template <class T> 
node<T>::node()
{
	value = T();
	next = NULL;
	prev = NULL;
}