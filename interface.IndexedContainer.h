#pragma once
#include "interface.Container.h"

template <class T>
class IndexedContainer : public virtual Container<T> {
public:
	T& operator[](int index) {
		return get(index);
	}

	virtual T get(int index) const = 0;
	virtual T& get(int index) = 0;
	virtual void set(int index, T const& value) = 0;

	void selection_sort();

	virtual ~IndexedContainer() = 0{};
};

template<class T>
void IndexedContainer<T>::selection_sort() {
	T tmp;
	for (int i = 0, min_index; i < get_size(); i++) {
		min_index = i;
		for (int j = i + 1; j < get_size(); j++)
			if (get(min_index) > get(j))
				min_index = j;
		if (min_index != i) {
			tmp = get(min_index);
			set(min_index, get(i));
			set(i, tmp);
		}
	}
}
