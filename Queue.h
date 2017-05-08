#pragma once
#include "PushPopContainer.h"
#include "Node.h"

template<class T>
class Queue : public PushPopContainer<T> {
private:
	node<T> *head, *tail;
	int size;
public:
	Queue();

	int Size() const;
	bool isEmpty() const;
	char* toString() const;

	bool push(T const&);
	T pop();
	T peek() const;
	T& peek();

	~Queue();
};

template<class T>
Queue<T>::Queue()
{
	head = tail = NULL;
	size = 0;
}

template<class T>
int Queue<T>::Size() const { return size; }

template<class T>
bool Queue<T>::isEmpty() const { return head == NULL; }

template<class T>
char* Queue<T>::toString() const {
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

template<class T>
T Queue<T>::pop() {
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

template<class T>
T Queue<T>::peek() const {
	if (isEmpty()) throw "Queue is empty!";
	return head->value;
}

template <class T>
T& Queue<T>::peek() {
	if (isEmpty()) throw "Queue is empty!";
	return head->value;
}

template<class T>
bool Queue<T>::push(T const& value) {
	node<T> *newNode = new node<T>;// �������� ������ ��� ����� ����� �������

	newNode->value = value;//��������� ���� �������� ������ ������
	newNode->next = NULL;// ���������� � ���� ������ ������ ������ ����, ��� ��� �� ������ ����
	newNode->prev = tail;// ���������� � ���� ������ ������� ������ ����� ������ ������

	if (isEmpty()) head = newNode;
	else tail->next = newNode;
	tail = newNode;//���������� � ������� ������ ����� ��������������� ������
	size++;// ���-�� ��������� ������� �������������
	return true;

}

template<class T>
Queue<T>::~Queue()
{
	node<T> *tmp;

	while (head) {
		tmp = head->next;
		delete head;
		head = tmp;
	}
}