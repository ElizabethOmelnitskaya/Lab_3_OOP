#pragma once
#include "PushPopContainer.h"
#include "Node.h"

template <class T>
class Stack : public PushPopContainer<T> {
private:
	node<T> *head;
	int size;// Емкость стека
public:
	Stack<T>& operator=(Stack<T> const&);

	Stack();
	Stack(Stack<T> const&);

	JavaIterator<T&>* createIterator();
	JavaIterator<T const&>* createIterator() const;

	int Size() const; // получить размер стека
	char *toString() const;

	T peek() const;
	T& peek();
	T pop(); // удалить элемент из стека
	bool push(T const&); // добавить элемент в стек

	~Stack();
};

template <typename T>
Stack<T>::Stack()
{
	head = NULL;
	size = 0;
}

template <typename T>
int Stack<T>::Size() const { return size; } // вернуть размер стека

template <typename T>
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

template <typename T> T Stack<T>::pop() {
	if (isEmpty()) throw "Stack is empty!";
	T tmp_val = head->value;
	node<T> *tmp_del = head->next;
	delete head;
	head = tmp_del;
	size--;
	if (!isEmpty()) head->prev = NULL;
	return tmp_val;
}

template <typename T>
T Stack<T>::peek() const { return head->value; }

template <typename T>
T& Stack<T>::peek() { return head->value; }

template <typename T> bool Stack<T>::push(T const& value) {
	node<T> *newNode = new node<T>(value);

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

template <typename T> Stack<T>::~Stack()
{
	node<T> *tmp;
	while (head) {
		tmp = head->next;
		delete head;
		head = tmp;
	}
}

template<class T>
Stack<T>& Stack<T>::operator=(Stack<T> const& other) {
	node<T> * tmp;
	while (head) {
		tmp = head->next;
		delete head;
		head = tmp;
	}
	tmp = other.tail;
	size = 0;
	while (tmp) {
		this->push(tmp->value);
		tmp = tmp->prev;
	}
	return *this;
}

template <class T, class U> class StackIterator : public JavaIterator<U> {
private:
	node<T> *currentIter;
public:
	StackIterator(node<T>*);

	U next();
	bool hasNext() const;
};

template <typename T, typename U>
StackIterator<T, U>::StackIterator(node<T> *initNode) { currentIter = initNode; }

template <typename T, typename U>
bool StackIterator<T, U>::hasNext() const {
	return currentIter != NULL &&
		currentIter->next != NULL;
}

template <typename T, typename U>
U StackIterator<T, U>::next() {
	T value = NULL;
	if (currentIter == NULL) return value;

	value = currentIter->value;
	currentIter = currentIter->next;

	return value;
}

template <typename T>
JavaIterator<T&>* Stack<T>::createIterator() {
	return new StackIterator<T, T&>(head);
}

template <typename T>
JavaIterator<T const&>* Stack<T>::createIterator() const {
	return new StackIterator<T, T const&>(head);
}

template <typename T>
Stack<T>::Stack(Stack<T> const& copy) {
	node<T> *tmpCopy = copy.head;
	node<T> *tmp = NULL, *prev = NULL;

	do {
		if (tmp == NULL) {
			head = new node<T>(tmpCopy->value);
			tmp = head;
		}
		else {
			prev = tmp;
			tmp = new node<T>(tmpCopy->value);

			prev->next = tmp;
			tmp->prev = prev;
		}
	} while ((tmpCopy = tmpCopy->next) != NULL);

	size = copy.size;
}