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
	node<T> *tmp = head; // текущий элемент
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

	node<T> *tmp_del = head->next;// измен€ем адрес головы

	delete head;// удал€ем старую голову
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
	node<T> *newNode = new node<T>;// ¬ыдел€ем пам€ть под новый хвост очереди

	newNode->value = value;//«аполн€ем поле значени€ нового хвоста
	newNode->next = NULL;// «аписываем в поле адреса нового хвоста ноль, так как за ничего нету
	newNode->prev = tail;// «аписываем в поле адреса старого хвоста адрес нового хвоста

	if (isEmpty()) head = newNode;
	else tail->next = newNode;
	tail = newNode;//«аписываем в указель хвоста адрес действительного хвоста
	size++;//  ол-во элементов очереди увеличиваетс€
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