#pragma once

template <class T>
class node
{
public:
	int value;
	node *prev;
	node *next;

	node(T);
};

template <class T>
node<T>::node(T val)
{
	value = val;
	next = NULL;
	prev = NULL;
}