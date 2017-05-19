#pragma once
#include "Deque.h"

template <class T>
class LinkedDeque : public Deque<T>
{
private:
	template<class S> struct Node;
	Node<T>* head;
	Node<T>* tail;
	int size;
public:
	LinkedDeque();
	LinkedDeque(const LinkedDeque<T>& st);
	LinkedDeque<T>& operator=(const LinkedDeque<T>& st);
	int Size() const override;
	bool isEmpty() const override;
	std::string toString() const override;
	bool pushFront(const T& value) override;
	bool pushBack(const T& value) override;
	T popFront() override;
	T popBack() override;
	T peekFront() const override;
	T peekBack() const override;
	T& peekFront() override;
	T& peekBack() override;

	//итератор
	template <class S>
	class DequeIterator : public JavaIterator<S>{
	private:
		friend class LinkedDeque<S>;
		Node<S>* current;

	public:
		DequeIterator(Node<S>* cur){ current = cur; }
		bool hasNext() override { return current != nullptr; }
		S& next() override {
			S& tmp = current->value;
			if (current != nullptr)
				current = current->next;
			return tmp;
		}
	};

	//константный итератор
	template <class S, class Node>
	class DequeConstIterator : public JavaIterator<S>{
	private:
		friend class LinkedDeque<S>;
		Node* current;
	public:
		DequeConstIterator(Node* cur){ current = cur; }
		bool hasNext() override { return current != nullptr; }
		const S& next() override {
			S& tmp = current->value;
			if (current != nullptr)
				current = current->next;
			return tmp;
		}
	};

	friend class DequeIterator<T>;
	friend class DequeConstIterator<const T, Node<T>>;

	JavaIterator<T> *createIterator() override;
	JavaIterator<const T> *createConstIterator() const override;

	virtual ~LinkedDeque();
};

template <class T>
template<class S>
struct LinkedDeque<T>::Node {
	S value;
	Node *next;
	Node *prev;
	Node(const S& value) : value(value), next(nullptr), prev(nullptr){}
};

template<class T>
JavaIterator<T>* LinkedDeque<T>::createIterator() {
	return new DequeIterator<T>(this->head);
}

template<class T>
JavaIterator<const T>* LinkedDeque<T>::createConstIterator() const {
	return new DequeConstIterator<const T, Node<T>>(this->head);
}

template <class T>
LinkedDeque<T>::LinkedDeque() :size(0), head(nullptr), tail(nullptr){}

template<class T>
LinkedDeque<T>::LinkedDeque(const LinkedDeque<T>& st) {
	auto iter = st.createConstIterator();
	while (iter->hasNext()) {
		pushFront(iter->next());
	}
}

template<class T>
LinkedDeque<T>& LinkedDeque<T>::operator=(const LinkedDeque<T>& st) {
	while (!isEmpty())
		popBack();
	auto iter = st.createConstIterator();
	while (iter->hasNext()) {
		pushFront(iter->next());
	}
	return *this;
}

template <class T>
int LinkedDeque<T>::Size() const { return size; }

template <class T>
bool LinkedDeque<T>::isEmpty() const { return size == 0; }

template <class T>
std::string LinkedDeque<T>::toString() const {
	Node<T>* tmp = head;
	string result = "";
	while (tmp != nullptr) {
		result.append(to_string(tmp->value));
		result.append(" ");
		tmp = tmp->next;
	}
	return result;
}

template <class T>
bool LinkedDeque<T>::pushFront(const T& value) {
	if (isEmpty()) {
		head = tail = new Node<T>(value);
		size++;
		return true;
	}
	else {
		head->prev = new Node<T>(value);
		Node<T> *tmp = head;
		head = head->prev;
		head->next = tmp;
		size++;
		return true;
	}
	return false;
}

template <class T>
bool LinkedDeque<T>::pushBack(const T& value) {
	if (isEmpty()) {
		head = tail = new Node<T>(value);
		size++;
		return true;
	}
	else {
		tail->next = new Node<T>(value);
		Node<T> *tmp = tail;
		tail = tail->next;
		tail->prev = tmp;
		size++;
		return true;
	}
	return false;
}

template <class T>
T LinkedDeque<T>::popFront() {
	T result = head->value;
	Node<T>* tmp = head->next;
	delete head;
	head = tmp;
	size--;
	return result;
}

template <class T>
T LinkedDeque<T>::popBack() {
	T result = tail->value;
	Node<T>* tmp = tail->prev;
	delete tail;
	tail = tmp;
	size--;
	return result;
}

template <class T>
T LinkedDeque<T>::peekFront() const { return head->value; }

template <class T>
T LinkedDeque<T>::peekBack() const { return tail->value; }

template <class T>
T& LinkedDeque<T>::peekFront() { return head->value; }

template <class T>
T& LinkedDeque<T>::peekBack() { return tail->value; }

template <class T>
LinkedDeque<T>::~LinkedDeque() {
	Node<T>* tmp = head;
	while (tmp != nullptr) {
		head = tmp->next;
		delete tmp;
		tmp = head;
	}
}

