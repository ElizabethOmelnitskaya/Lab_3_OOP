#pragma once
#include "interface.InsertableContainer.h"
#include "PushPopContainer.h"
#include "Node.h"

template<class T>
class LinkedList : public InsertableContainer<T>, public PushPopContainer<T>
{
private:
	node<T> *head, *tail;
	int size;
public:
	LinkedList();

	// Container
	int Size() const;
	bool isEmpty() const;
	char* toString() const;
	
	// PushPopContainer
	bool push(T const&);
	T peek() const;
	T& peek();
	T pop();

	// IndexedContainer
	T get(int) const;
	T& get(int);
	void set(int, T const&);

	// InsertableContainer
	bool insertAt(int, T const&);
	T removeAt(int);

	~LinkedList();
};

template<class T>
LinkedList<T>::LinkedList()
{
	head = tail = NULL;
	size = 0;
}

template<class T>
int LinkedList<T>::Size() const { return size; }

template<class T>
bool LinkedList<T>::isEmpty() const { return size == 0; }

template<class T>
char* LinkedList<T>::toString() const {
	node<T> *tmp = head;
	char *res = new char[100]{ NULL };

	strcat(res, "Linked list:\n ");
	do {
		if (tmp != head) {
			strcat(res, ", ");
		}
		char *val = new char[100]{ NULL };

		itoa(tmp->value, val, 10);
		strcat(res, val);

		tmp = tmp->next;

		delete val;
	} while (tmp != NULL);

	strcat(res, "  ");
	delete tmp;

	return res;
}

// PushPopContainer
template<class T>
T LinkedList<T>::peek() const { return tail->value; }

template <class T>
T& LinkedList<T>::peek() { return &(tail->value); }

template<class T>
T LinkedList<T>::pop() {
	if (isEmpty()) throw 1;

	node<T> *tmp_del = tail->prev;
	T tmp_val = tail->value;
	delete tail;
	tail = tmp_del;
	if (tail) tail->next = NULL;
	else head = NULL;
	size--;
	return tmp_val;
}

template<class T>
bool LinkedList<T>::push(T const& value) {
	node<T> *tmp = new node<T>;

	tmp->value = value;
	tmp->next = NULL;
	tmp->prev = tail;
	if (isEmpty())
		head = tmp;
	else
		tail->next = tmp;
	tail = tmp;
	size++;

	return true;
}

// IndexedContainer 
template<class T>
T LinkedList<T>::get(int index) const {
	if (isEmpty()) throw 1;
	else if (index >= size || index < 0)
		throw 2;
	node<T> *tmp = head;
	for (int i = 1; i <= index; i++)
		tmp = tmp->next;
	return tmp->value;
}

template <class T>
T& LinkedList<T>::get(int index) {
	if (isEmpty()) throw 1;
	else if (index >= size || index < 0)
		throw 2;
	node<T> *tmp = head;
	for (int i = 1; i <= index; i++)
		tmp = tmp->next;
	return &tmp->value;
}

template<class T>
void LinkedList<T>::set(int index, T const& value) {
	if (isEmpty()) throw 1;
	else if (index >= size || index < 0) throw 2;
	node<T> *tmp = head;
	for (int i = 1; i <= index; i++)
		tmp = tmp->next;
	tmp->value = value;
}

// InsertableContainer
template<class T>
bool LinkedList<T>::insertAt(int index, T const& value) {
	if (index == size()) {
		return push(value);
	}
	else if (index == 0) {
		return pushFront(value);
	}
	else{
		T tmp_value;
		node<T> *tmp_node = new node<T>;
		tmp_node->value = value;
		tmp_node->next = head;
		tmp_node->prev = NULL;
		if (isEmpty()) tail = tmp_node;
		else head->prev = tmp_node;
		head = tmp_node;
		size++;
		for (int i = 0; i < index; i++)
		{
			tmp_value = get(i);
			set(i, get(i + 1));
			set(i + 1, tmp_value);
		}
		return true;
	}
}

template<class T>
T LinkedList<T>::removeAt(int index) {
	if (isEmpty()) throw 1;
	else if (index >= size || index < 0) throw 2;

	if (index == 0) {
		return popFront();
	}
	else if (index == size() - 1) {
		return pop();
	}
	else{
		T tmp_head_val = head->value, tmp_val;
		node<T> *tmp_node = head->next;
		delete head;
		head = tmp_node;
		if (head)
			head->prev = NULL;
		else
			tail = NULL;
		size--;
		for (int i = index - 1; i > 0; i--)
			set(i, get(i - 1));
		if (index)
			set(0, tmp_head_val);
		return tmp_val;
	}
}

template<class T>
LinkedList<T>::~LinkedList()
{
	node<T> *tmp;

	while (head) {
		tmp = head->next;
		delete head;
		head = tmp;
	}
}
