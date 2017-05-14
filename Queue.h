#pragma once
#include "PushPopContainer.h"
#include "Node.h"
#include "JavaIterator.h"

template <class T>
class Queue : public PushPopContainer<T> {
private:
	node<T> *head, *tail;
	int size;
public:
	Queue<T>& operator=(Queue<T> const&);

	Queue();
	Queue(Queue<T> const&);

	JavaIterator<T&>* createIterator();
	JavaIterator<T const&>* createIterator() const;

	int Size() const;
	char* toString() const;

	bool push(T const&);
	T pop();
	T peek() const;
	T& peek();
	~Queue();
};

template <class T> Queue<T>::Queue()
{
	head = tail = NULL;
	size = 0;
}

template <typename T>
Queue<T>::Queue(Queue<T> const& copy) {
	node<T> *tmpCopy = copy->tail;
	do {
		push(tmpCopy->value);
	} while ((tmpCopy = tmpCopy->prev) != NULL);
}

template <class T>
int Queue<T>::Size() const { return size; }

template <class T> char* Queue<T>::toString() const {
	node<T> *tmp = head; // ������� �������
	char *res = new char[100]{ NULL };

	strcat(res, "Queue:\n ");

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

	strcat(res, " ");

	delete tmp;
	return res;
}

template <class T> T Queue<T>::pop() {
	if (isEmpty()) throw "Queue is empty!";

	T tmp_val = head->value;

	node<T> *tmp_del = head->next;// �������� ����� ������

	delete head;// ������� ������ ������
	head = tmp_del;

	if (isEmpty()) tail = NULL;
	else head->prev = NULL;
	size--;

	return tmp_val;
}

template <class T> T Queue<T>::peek() const {
	if (isEmpty()) throw "Queue is empty!";
	return head->value;
}

template <class T> T& Queue<T>::peek() {
	if (isEmpty()) throw "Queue is empty!";
	return head->value;
}

template <class T> bool Queue<T>::push(T const& value) {
	node<T> *newNode = new node<T>();// �������� ������ ��� ����� ����� �������

	newNode->value = value;//��������� ���� �������� ������ ������
	newNode->next = NULL;// ���������� � ���� ������ ������ ������ ����, ��� ��� �� ������ ����
	newNode->prev = tail;// ���������� � ���� ������ ������� ������ ����� ������ ������

	if (isEmpty()) head = newNode;
	else tail->next = newNode;
	tail = newNode;//���������� � ������� ������ ����� ��������������� ������
	size++;// ���-�� ��������� ������� �������������
	return true;
}

template <class T> Queue<T>::~Queue() {
	node<T> *tmp;

	while (head) {
		tmp = head->next;
		delete head;
		head = tmp;
	}
}

template <class T, class U> class QueueIterator : public JavaIterator<U> {
private:
	node<T> currentIter;
public:
	QueueIterator(node<T>*);

	U next();
	bool hasNext() const;
};

template <typename T, typename U>
QueueIterator<T, U>::QueueIterator(node<T> *initialNode) {
	currentNode = initialNode;
}

template <typename T, typename U>
U QueueIterator<T, U>::next() {
	T value = NULL;

	if (currentIter == NULL) return value;

	value = currentIter->value;
	currentIter = currentIter->next;

	return value;
}

template <typename T, typename U>
bool QueueIterator<T, U>::hasNext() const {
	return currentIter != NULL &&
		currentIter->next != NULL;
}

template <typename T>
JavaIterator<T&>* Queue<T>::createIterator() {
	return new QueueIterator<T, T&>(head);
}
template <typename T>

JavaIterator<T const&>* Queue<T>::createIterator() const {
	return new QueueIterator<T, T const&>(head);
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
	node<T> * tmp;
	while (head && head->value != STATIC_NULL_VALUE) {
		tmp = head->next;
		delete head;
		head = tmp;
	}
	tmp = other.head;
	size = 0;
	while (tmp) {
		this->push(tmp->value);
		tmp = tmp->next;
	}
	return *this;
}