#pragma once
#include "PushPopContainer.h"
#include "Node.h"

template<class T>
class Stack : public PushPopContainer<T> {
private:
	node<T> *head;
	int size;// Емкость стека
public:
	Stack();

	int Size() const; // получить размер стека
	bool isEmpty() const; // пуст ли стек
	char *toString() const;

	T peek() const;
	T& peek();
	T pop(); // удалить элемент из стека
	bool push(T const&); // добавить элемент в стек

	~Stack();
};

template<class T>
Stack<T>::Stack()
{
	head = NULL;
	size = 0;
}

template<class T>
int Stack<T>::Size() const { return size; } // вернуть размер стека

template<class T>
bool Stack<T>::isEmpty() const { return head == NULL; }

template<class T>
char* Stack<T>::toString() const {
	node<T> *tmp = head; // текущий элемент
	char *res = new char[100]{ NULL };

	strcat(res, "Stack:\n ");
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
T Stack<T>::pop() {
	if (isEmpty()) throw "Stack is empty!";

	T tmp_val = head->value;

	node<T> *tmp_del = head->next;
	delete head;
	head = tmp_del;
	if (!isEmpty()) head->prev = NULL;
	size--;
	return tmp_val;
}

template<class T>
T Stack<T>::peek() const { return head->value; }

template <class T>
T& Stack<T>::peek() { return head->value; }


template<class T>
bool Stack<T>::push(T const& value) {
	node<T> *newNode = new node<T>;

	newNode->value = value;
	newNode->next = head;
	newNode->prev = NULL;
	if (!isEmpty()) {
		head->prev = newNode;
	}
	head = newNode;
	size++;
	return true;
}

template<class T>
Stack<T>::~Stack()
{
	node<T> *tmp;
	while (head) {
		tmp = head->next;
		delete head;
		head = tmp;
	}
}