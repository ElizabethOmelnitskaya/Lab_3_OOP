#pragma once
#include "PushPopContainer.h"
#include "Node.h"

template <class T>
class Queue : public PushPopContainer<T> {
private:

	template <class S> struct Node;
	Node<T> *head;
	Node<T> *tail;
	int size;
public:

	Queue();
	Queue(const Queue<T>& st);
	Queue<T>& operator=(const Queue<T>& st);
	int Size() const override;
	bool isEmpty() const override;
	bool push(const T& value) override;
	T pop() override;
	T peek() const override;
	T& peek()  override;

	//итератор
	template <class S>
	class QueueIterator : public JavaIterator<S>
	{
	private:
		friend class Queue<S>;
		Node<S>* current;

	public:
		QueueIterator(Node<S>* cur)
		{
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
	class QueueConstIterator : public JavaIterator<S>
	{
	private:
		friend class Queue<S>;
		Node* current;
	public:
		QueueConstIterator(Node* cur)
		{
			current = cur;
		}
		bool hasNext() override {
			return current != nullptr;
		}
		const S& next() override {
			S& tmp = current->value;
			if (current != nullptr)
				current = current->next;
			return tmp;
		}
	};


	friend class QueueIterator<T>;
	friend class QueueConstIterator<const T, Node<T>>;
	JavaIterator<T> *createIterator() override;
	JavaIterator<const T> *createConstIterator() const override;
	virtual ~Queue();
};

template <class T>
template <class S>
struct Queue<T>::Node {
	S value;
	Node *next;
	Node(const S& value) : value(value), next(nullptr)
	{ }
};

template<class T>
JavaIterator<T>* Queue<T>::createIterator()
{
	return new QueueIterator<T>(this->head);
}
template<class T>
JavaIterator<const T>* Queue<T>::createConstIterator() const {
	return new QueueConstIterator<const T, Node<T>>(this->head);
}

template <class T>
Queue<T>::Queue() {
	size = 0;
	head = tail = nullptr;
}

template<class T>
Queue<T>::Queue(const Queue<T>& st) {
	auto iter = st.createConstIterator();
	while (iter->hasNext())
	{
		push(iter->next());
	}
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& st)
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
int Queue<T>::Size() const { return size; }

template <class T>
bool Queue<T>::isEmpty() const { return head == nullptr; }

template <class T>
bool Queue<T>::push(const T& value)
{
	try {
		if (isEmpty())
			head = tail = new Node<T>(value);
		else {
			tail->next = new Node<T>(value);
			tail = tail->next;
		}
		size++;
		return true;
	}
	catch (...) {
		return false;
	}
}

template <class T>
T Queue<T>::pop() {
	if (!isEmpty()) {
		T result = head->value;
		Node<T>* tmp = head->next;
		delete head;
		head = tmp;
		size--;
		return result;
	}
	throw "The Queue is empty!";
}

template <class T>
T Queue<T>::peek() const {
	if (!isEmpty())
		return head->value;
	throw "The Queue is empty!";
}

template <class T>
T& Queue<T>::peek() {
	if (!isEmpty())
		return head->value;
	throw "The Queue is empty!";
}


template <class T>
Queue<T>::~Queue() {
	Node<T>* tmp = head;
	while (tmp != nullptr) {
		head = tmp->next;
		delete tmp;
		tmp = head;
	}
}