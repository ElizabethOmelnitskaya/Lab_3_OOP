#pragma once

template <class T>
class Node
{
public:
	T value;
	Node *prev;
	Node *next;

	Node(T);
	Node(Node<T> const&);
};

template <class T>
Node<T>::Node(T val)
{
	value = val;
	next = NULL;
	prev = NULL;
}

template <typename T>
Node<T>::Node(Node<T> const& copy) {
	value = copy.value;
}