#pragma once
#include "JavaIterator.h"
#include <sstream>
#include <string>

using namespace std;

template <class T>
class Container {
public:
	bool operator==(Container<T> const& cont) const {
		JavaIterator<T const&> *iter1 = createIterator();
		JavaIterator<T const&> *iter2 = cont.createIterator();
		T val1, val2;

		while ((val1 = iter1->next()) != NULL &&
			(val2 = iter2->next()) != NULL) {
			if (val1 != val2)
				return false;

			val1 = NULL;
			val2 = NULL;
		}
		return val1 == val2;
	}

	bool operator!=(Container<T> const& cont) const {
		return !(this == cont);
	}

	virtual int Size() const = 0;
	virtual bool isEmpty() const { return Size() == 0; }
	virtual char* toString() const {
		JavaIterator<T const&> *iter1 = createIterator();

		char *res = new char[100]{ NULL };
		T val;

		stringstream stream;

		while ((val = iter1->next()) != NULL) {
			char *line = new char[100]{ NULL };
			stream << val;
			stream >> line;
			strcat(res, line);
			delete line;
		}
		return res;
	}

	virtual JavaIterator<T&>* createIterator() = 0;
	virtual JavaIterator<T const&>* createIterator() const = 0;

	virtual ~Container() = 0{};
};

template <typename T>
ostream& operator<<(ostream& os, Container<T> const& container) {
	os << container.toString();
	return os;
}