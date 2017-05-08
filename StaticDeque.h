#pragma once
#include "Deque.h"
#include "Node.h"

template<class T>
class StaticDeque : public Deque<T> {
private:
	node<T> *head, *tail;
	int size;
	T *arr;
public:
	StaticDeque(T default_value);

	int Size() const;
	bool isEmpty() const;
	char* toString() const;

	bool pushBack(T const&);
	bool pushFront(T const&);
	T popBack();
	T popFront();
	T peekBack() const;
	T peekFront() const;
	T& peekBack();
	T& peekFront();

	~StaticDeque();
};

template<class T>
StaticDeque<T>::StaticDeque(T default_value)
{
	head = tail = NULL;
	size = 0;
}

template<class T>
StaticDeque<T>::~StaticDeque() { delete[] arr; }

template<class T>
int StaticDeque<T>::Size() const { return size; }

template<class T>
bool StaticDeque<T>::isEmpty() const { return size == 0; }

template<class T>
char* StaticDeque<T>::toString() const {
	node <T>*tmp = head;
	char *res = new char[100]{ NULL };

	strcat(res, "StaticDeque:\n ");
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

template<class T>
bool StaticDeque<T>::pushBack(T const& value) {
	node<T> *newNode = new node<T>();

	newNode->value = value;

	if (isEmpty()) {
		head = newNode;
		tail = newNode;
	}
	else {
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}

	size++;

	return true;
}

template<class T>
bool StaticDeque<T>::pushFront(T const& value) {
	node<T> *newNode = new node<T>;

	newNode->value = value;

	if (isEmpty()) {
		head = newNode;
		tail = newNode;
	}
	else {
		head->prev = newNode;
		newNode->next = head;
		head = newNode;
	}
	size++;
	return true;
}

template<class T>
T StaticDeque<T>::peekBack() const { return arr[size - 1]; }

template <class T>
T& StaticDeque<T>::peekBack() { return arr[size - 1];  }

template<class T>
T StaticDeque<T>::peekFront() const { return arr[0]; }

template<class T>
T& StaticDeque<T>::peekFront() { return arr[0]; }

template<class T>
T StaticDeque<T>::popBack() {
	if (isEmpty()) return -1;

	T value = tail->value;
	if (Size() == 1) {
		delete tail;

		tail = NULL;
		head = NULL;
	}
	else {
		node<T> *elemPop = tail;
		tail = tail->prev;
		tail->next = NULL;

		delete elemPop;
	}
	size--;

	return value;
}

template<class T>
T StaticDeque<T>::popFront() {

	if (isEmpty()) return NULL;

	T value = tail->value;
	if (Size() == 1) {
		delete tail;

		tail = NULL;
		head = NULL;
	}
	else {
		node<T> *elemPop = head;
		head = head->next;
		head->prev = NULL;

		delete elemPop;
	}
	size--;

	return value;
}

