#pragma once
#include "Deque.h"
#include "Node.h"
#include "JavaIterator.h"

template <class T>
class StaticDeque : public Deque<T> {
private:
	node<T> *head, *tail;
	int size;
	int *arr;
public:
	StaticDeque<T>& operator=(StaticDeque<T> const&);

	JavaIterator<T&>* createIterator();
	JavaIterator<T const&>* createIterator() const;

	StaticDeque();
	StaticDeque(StaticDeque<T> const&);

	int Size() const;
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

template <typename T> StaticDeque<T>::StaticDeque() {
	head = tail = NULL;
	size = 0;
}

template <typename T>
StaticDeque<T>::StaticDeque(StaticDeque<T> const& copy) {
	DataNode<T> *tmpCopy = copy->tail;

	do {
		pushBack(tmpCopy->value);
	} while ((tmpCopy = tmpCopy->prev) != NULL);
}

template <typename T>
StaticDeque<T>::~StaticDeque() { delete[] arr; }

template <typename T>
int StaticDeque<T>::Size() const { return size; }

template <typename T> char* StaticDeque<T>::toString() const {
	node<T> *tmp = head;
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

template <typename T> bool StaticDeque<T>::pushBack(T const& value) {
	node<T> *newNode = new node<T>(value);
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

template <typename T> bool StaticDeque<T>::pushFront(T const& value) {
	node<T> *newNode = new node<T>(value);
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

template <typename T>
T StaticDeque<T>::peekBack() const { return arr[size - 1]; }

template <typename T>
T& StaticDeque<T>::peekBack() { return arr[size - 1]; }

template <typename T>
T StaticDeque<T>::peekFront() const { return arr[0]; }

template <typename T>
T& StaticDeque<T>::peekFront() { return arr[0]; }

template <typename T> T StaticDeque<T>::popBack() {
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

template <typename T> T StaticDeque<T>::popFront() {

	if (isEmpty()) return -1;

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

template <typename T>
JavaIterator<T&>* StaticDeque<T>::createIterator() {
	return new StaticDequeIterator<T, T&>(head);
}

template <typename T>
JavaIterator<T const&>* StaticDeque<T>::createIterator() const {
	return new StaticDequeIterator<T, T const&>(head);
}

template<class T>
StaticDeque<T>& StaticDeque<T>::operator=(const StaticDeque<T>& other) {
	delete[]arr;
	this->size = other.size;
	arr = new T[size];
	for (int i = 0; i < size; i++)
		this->arr[i] = other.arr[i];
}

template <class T, class U>
class StaticDequeIterator : public JavaIterator<U> {
private:
	node<T> *currentIter;
public:
	StaticDequeIterator(node<T>*);

	U next();
	bool hasNext() const;
};

template <typename T, typename U>
StaticDequeIterator<T, U>::StaticDequeIterator(node<T> *initialNode) {
	currentIter = initialNode;
}

template <typename T, typename U>
U StaticDequeIterator<T, U>::next() {
	T value = NULL;

	if (currentIter == NULL) return value;

	value = currentIter->value;
	currentIter = currentIter->next;

	return value;
}

template <typename T, typename U>
bool StaticDequeIterator<T, U>::hasNext() const {
	return currentIter != NULL &&
		currentIter->next != NULL;
}