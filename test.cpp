#include <iostream>
#include "interface.Container.h"
#include "PushPopContainer.h"
#include "interface.IndexedContainer.h"
#include "interface.InsertableContainer.h"
#include "Deque.h"
#include "Stack.h"
#include "Queue.h"
#include "StaticArray.h"
#include "StaticDeque.h"
#include "LinkedList.h"
#include <conio.h>

using namespace std;


int main()
{
	Container<int> *arr[3];

	arr[0] = new Stack<int>();
	arr[1] = new StaticDeque<int>(20);
	arr[2] = new Queue<int>;

	for (Container<int>*c:arr){
		PushPopContainer<int>*A = dynamic_cast<PushPopContainer<int>*>(c);
		if (A != NULL){
			A->push(3);
			A->push(15);
			A->push(10);
			A->push(20);
			A->push(11);
			A->push(16);
		}
		Deque<int>*D = dynamic_cast<Deque<int>*>(c);
		if (D != NULL) {
			D->pushFront(1);
			D->pushFront(2);
			D->pushFront(3);
			D->pushBack(30);
			D->pushBack(20);
			D->pushBack(10);
		}
	}

	for (Container<int>*c : arr){
		cout << c->toString() << endl;
		cout << "Size: " << c->Size() << endl << endl;
	}
	for (Container<int>*c : arr){
		PushPopContainer<int>*A = dynamic_cast<PushPopContainer<int>*>(c);
		if (A != NULL) {
			while (!c->isEmpty()){
				cout << "Delete element: " << A->pop() << endl;
				cout << "Size: " << c->Size() << endl;
			}
		}
		Deque<int>*D = dynamic_cast<Deque<int>*>(c);
		if (D != NULL) {
			while (!c->isEmpty()){
				cout << "Delete element: " << D->popBack() << endl;
				cout << "Size: " << c->Size() << endl;
			}
		}
		cout << endl;
	}
	system("pause");
	return 0;
}