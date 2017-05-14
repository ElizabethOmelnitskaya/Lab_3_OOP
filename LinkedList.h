#pragma once
#include "interface.InsertableContainer.h"
#include "PushPopContainer.h"
#include "Node.h"

template <class T> class LinkedList : public InsertableContainer<T>, public PushPopContainer<T>{
private:
	node<T> *head, *tail;
	int size;
public:
	LinkedList<T>& operator=(LinkedList<T> const&);

	LinkedList();
	LinkedList(LinkedList<T> const&);

	JavaIterator<T&>* createIterator();
	JavaIterator<T const&>* createIterator() const;

	// Container
	int Size() const;
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

template <typename T>
LinkedList<T>::LinkedList()
{
	head = tail = NULL;
	size = 0;
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T> const& copy) {
	DataNode<T> *tmpCopy = copy->tail;
	do {
		push(tmpCopy->value);
	} while ((tmpCopy = tmpCopy->prev) != NULL);
}

template <typename T>
int LinkedList<T>::Size() const { return size; }

template <typename T>
char* LinkedList<T>::toString() const {
	node *tmp = head;
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

template <typename T>
T LinkedList<T>::peek() const { return tail->value; }

template <typename T>
T& LinkedList<T>::peek() { return &(tail->value); }

template <typename T> T LinkedList<T>::pop() {
	if (isEmpty()) throw 1;

	node<T> *tmp_del = tail->prev;
	int tmp_val = tail->value;
	delete tail;
	tail = tmp_del;
	if (tail) tail->next = NULL;
	else head = NULL;
	size--;
	return tmp_val;
}

template <typename T>
bool LinkedList<T>::push(T const& value) {
	node<T> *tmp = new node<T>();
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

template <typename T>
T LinkedList<T>::get(int index) const {
	if (isEmpty()) throw 1;
	else if (index >= size || index < 0)
		throw 2;
	node<T> *tmp = head;
	for (int i = 1; i <= index; i++)
		tmp = tmp->next;
	return tmp->value;
}

template <typename T>
T& LinkedList<T>::get(int index) {
	if (isEmpty()) throw 1;
	else if (index >= size || index < 0)
		throw 2;
	node<T> *tmp = head;
	for (int i = 1; i <= index; i++)
		tmp = tmp->next;
	return &(tmp->value);
}

template <typename T>
void LinkedList<T>::set(int index, T const& value) {
	if (isEmpty()) throw 1;
	else if (index >= size || index < 0) throw 2;
	node<T> *tmp = head;
	for (int i = 1; i <= index; i++)
		tmp = tmp->next;
	tmp->value = value;
}

template <typename T>
bool LinkedList<T>::insertAt(int index, T const& value) {
	if (index > size || index < 0 || isEmpty() && index)
		throw 2;
	int tmp_value;
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

template <typename T>
T LinkedList<T>::removeAt(int index) {
	if (isEmpty()) throw 1;
	else if (index >= size || index < 0) throw 2;

	int tmp_head_val = head->value, tmp_val;
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

template <class T> LinkedList<T>::~LinkedList()
{
	node<T> *tmp;

	while (head) {
		tmp = head->next;
		delete head;
		head = tmp;
	}
}

template <class T, class U> class LinkedListIterator : public JavaIterator<U> {
private:
	node<T> *currentIter;
public:
	LinkedListIterator(node<T>*);
	~LinkedListIterator();

	U next();
	bool hasNext() const;
};

template <typename T, typename U>
LinkedListIterator<T, U>::LinkedListIterator(node<T> *initialNode) {
	currentNode = initialNode;
}

template <typename T, typename U>
U LinkedListIterator<T, U>::next() {
	T value = NULL;

	if (currentIter == NULL) return value;

	value = currentIter->value;
	currentIter = current->next;

	return value;
}

template <typename T, typename U>
bool LinkedListIterator<T, U>::hasNext() const {
	return currentIter != NULL &&
		currentIter->next != NULL;
}

template <typename T>
JavaIterator<T&>* LinkedList<T>::createIterator() {
	return new LinkedListIterator<T, T&>(head);
}
template <typename T>
JavaIterator<T const&>* LinkedList<T>::createIterator() const {
	return new LinkedListIterator<T, T const&>(head);
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
	node<T> *tmp;
	while (head) {
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
