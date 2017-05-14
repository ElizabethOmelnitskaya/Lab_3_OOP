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
#include <iostream>
#include <conio.h>
#include <ctime>

using namespace std;

int main()
{
	const int elem = 15;
	const int elemPop = 5;
	const int elemPushFront = 5;

	Container<int> **arr = new Container<int>*[2];

	arr[0] = new Stack<int>;
	arr[1] = new StaticDeque<int>;
	
	PushPopContainer<int>*A;
	Deque<int>*D;

	for (int i = 0; i < 2; i++) {
		if (A = dynamic_cast < PushPopContainer<int>* >(arr[i])) {
			for (int j = 1; j < 5; j++)
				A->push(j);
		}
		if (D = dynamic_cast < Deque<int>* >(arr[i])) {
			for (int j = 1; j < 5; j++) {
				D->pushFront(j);
				D->pushBack(-(j));
			}
		}
		cout << arr[i]->toString() << endl;
		cout <<"Size: " << arr[i]->Size() << endl;
	}
	cout << endl;

	for (int i = 0; i < 2; i++) {
		while (!arr[i]->isEmpty()){
			int val;
			if (A = dynamic_cast <PushPopContainer<int>*>(arr[i])){
				val = A->pop();
			}
			cout << endl;
			if (D = dynamic_cast <Deque<int>*>(arr[i])){
				val = D->popBack();
			}
			cout <<"Val: " <<val << endl;
			cout << "Size: "<< arr[i]->Size() << endl;
		}
	}
	cout << endl;
		
	Stack<int> *a = new Stack<int>();
	a->push(10);

	Stack<int> a1(*a), a2 = *a;

	cout << *a << endl << a1 << endl << a2;


	system("pause");
	return 0;
}