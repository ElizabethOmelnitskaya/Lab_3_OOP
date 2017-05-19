#pragma once
#include "interface.InsertableContainer.h"
#include "PushPopContainer.h"
#include "Node.h"

template <class T>
class LinkedList :
	public PushPopContainer<T>, public InsertableContainer<T>
{
private:
	template<class S> struct Node;
	Node<T> *head;
	Node<T> *tail;
	int size;
public:
	LinkedList();
	LinkedList(const LinkedList<T>& st);
	LinkedList<T>& operator=(const LinkedList<T>& st);
	int Size() const override;
	bool isEmpty() const override;
	std::string toString() const override;
	bool push(const T& value) override;
	T pop() override;
	T peek() const override;
	T& peek() override;
	T get(int index) const override;
	T& get(int index) override;
	bool set(int index, const T& value) override;
	bool insertAt(int index, const T& value) override;
	bool removeAt(int index) override;

	//итератор
	template <class S>
	class ListIterator : public JavaIterator<S> {
	private:
		friend class LinkedList<S>;
		Node<S>* current;

	public:
		ListIterator(Node<S>* cur) {
			current = cur;
		}
		bool hasNext() override {
			return current != nullptr;
		}
		S& next() override {
			S& tmp = current->value;
			if (current != nullptr)
				current = current->next;
			return tmp;
		}
	};

	//константный итератор
	template <class S, class Node>
	class ListConstIterator : public JavaIterator<S> {
	private:
		friend class LinkedList<S>;
		Node* current;
	public:
		ListConstIterator(Node* cur) { current = cur; }
		bool hasNext() override { return current != nullptr; }
		const S& next() override {
			S const& tmp = current->value;
			if (current != nullptr)
				current = current->next;
			return tmp;
		}
	};

	friend class ListIterator<T>;
	friend class ListConstIterator<const T, Node<T>>;
	JavaIterator<T> *createIterator() override;
	JavaIterator<const T> *createConstIterator() const override;

	virtual ~LinkedList();
};

template <class T>
template<class S>
struct LinkedList<T>::Node {
	S value;
	Node *next;
	Node(const S& value) : value(value), next(nullptr){}
};

template<class T>
JavaIterator<T>* LinkedList<T>::createIterator() {
	return new ListIterator<T>(this->tail);
}

template<class T>
JavaIterator<const T>* LinkedList<T>::createConstIterator() const {
	return new ListConstIterator<const T, Node<T>>(this->tail);
}

template <class T>
LinkedList<T>::LinkedList() {
	size = 0;
	head = tail = nullptr;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& st)
{
	auto iter = st.createConstIterator();
	while (iter->hasNext())
	{
		push(iter->next());
	}
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& st)
{
	while (!isEmpty())
		pop();
	auto iter = st.createConstIterator();
	while (iter->hasNext())
	{
		push(iter->next());
	}
	return *this;
}

template <class T>
int LinkedList<T>::Size() const { return size; }

template <class T>
bool LinkedList<T>::isEmpty() const { return head == nullptr; }

template <class T>
std::string LinkedList<T>::toString() const
{
	Node<T>* tmp = tail;
	string result = "";
	while (tmp != nullptr)
	{
		result.append(to_string(tmp->value));
		result.append(" ");
		tmp = tmp->next;
	}
	return result;
}

template <class T>
bool LinkedList<T>::push(const T& value)
{
	try {
		if (isEmpty())
			head = tail = new Node<T>(value);
		else
		{
			Node<T>* tmp = new Node<T>(value);
			tmp->next = tail;
			tail = tmp;
		}
		size++;
		return true;
	}
	catch (...)
	{
		return false;
	}
}

template <class T>
T LinkedList<T>::pop()
{
	if (!isEmpty())
	{
		T result = tail->value;
		Node<T>* tmp = tail->next;
		delete tail;
		tail = tmp;
		size--;
		return result;
	}
	throw "The container is empty";
}

template <class T>
T LinkedList<T>::peek() const
{
	if (!isEmpty())
		return tail->value;
	throw "The container is empty";
}

template <class T>
T& LinkedList<T>::peek()
{
	if (!isEmpty())
		return tail->value;
	throw "The container is empty";
}

template <class T>
T LinkedList<T>::get(int index) const
{
	if (index < size)
	{
		index = size - index;
		Node<T>* tmp = tail;
		for (int i = 0; i < index; i++)
		{
			tmp = tmp->next;
		}
		return tmp->value;
	}
	throw "The container is empty";
}

template <class T>
T& LinkedList<T>::get(int index)
{
	if (index < size)
	{
		index = size - index;
		Node<T>* tmp = tail;
		for (int i = 0; i < index; i++)
		{
			tmp = tmp->next;
		}
		return tmp->value;
	}
	throw "The container is empty";
}

template <class T>
bool LinkedList<T>::set(int index, const T& value)
{
	if (index < size)
	{
		index = size - index;
		Node<T>* tmp = tail;
		for (int i = 0; i < index; i++)
		{
			tmp = tmp->next;
		}
		tmp->value = value;
		return true;
	}
	return false;
}

template <class T>
bool LinkedList<T>::insertAt(int index, const T& value)
{
	if (index < size)
	{
		index = size - index;
		Node<T>* tmp = tail;
		for (int i = 0; i < index; i++)
		{
			tmp = tmp->next;
		}
		Node<T> *nd = new Node<T>(value);
		nd->next = tmp->next;
		tmp->next = nd;
		size++;
		return true;
	}
	return false;
}

template <class T>
bool LinkedList<T>::removeAt(int index)
{
	if (index < size)
	{
		index = size - index;
		Node<T>* tmp;
		if (index == 1)
		{
			tmp = tail->next;
			delete tail;
			tail = tmp;
			size--;
			return true;
		}
		tmp = tail;
		for (int i = 0; i < index - 1; i++)
		{
			tmp = tmp->next;
		}
		Node<T>* tmp2 = tmp->next;
		tmp->next = tmp2->next;
		delete tmp2;
		return true;
	}
	return false;
}

template <class T>
LinkedList<T>::~LinkedList()
{
	Node<T>* tmp = tail;
	while (tmp != nullptr)
	{
		tail = tmp->next;
		delete tmp;
		tmp = tail;
	}
}