#include "interface.Container.h"
#include "PushPopContainer.h"
#include "interface.IndexedContainer.h"
#include "interface.InsertableContainer.h"
#include "Deque.h"
#include "Stack.h"
#include "Queue.h"
#include "StaticArray.h"
#include "LinkedList.h"
#include <iostream>
#include <conio.h>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

int main()
{
	//const int n = 5;
	//
	//vector<PushPopContainer<int>*> arr1({ new LinkedList<int>(), new Queue<int>(), new Stack<int>() });
	//vector<IndexedContainer<int>*> arr2({ new StaticArray<int>(n) });

	//for (int i = 0; i < n; i++){
	//	for (int j = 0; j < arr1.size(); j++)
	//	arr1[j]->push(i);
	//	for (int j = 0; j < arr2.size(); j++)
	//		arr2[j]->set(i, i);
	//}
	//for (int j = 0; j < arr1.size(); j++){
	//	cout << "Arr1: " << arr1[j]->toString() << endl;
	//	cout << "Size: " << arr1[j]->Size() << endl;
	//}
	//for (int j = 0; j < arr2.size(); j++)
	//	cout << "Arr2: " <<arr2[j]->toString() << endl;

	////Проверка сортировки
	//StaticArray<int> ars(10);
	//for (int j = 0; j <10; j++)
	//	ars[j] = 9 - j;
	//cout << "StaticArray: " <<ars << endl;
	//ars.Sort();
	//cout << "Sort StaticArray: " <<ars << endl;

	PushPopContainer<int> *c = new LinkedList<int>();
	c->Sort();
	cout << *c << endl;

	c->push(1);
	c->Sort();
	cout << *c << endl;

	c->push(-1);
	c->Sort();
	cout << *c << endl;

	c->push(-2);
	c->Sort();
	cout << *c << endl;

	LinkedList<int> list;
	list.push(-2);
	list.push(-1);
	list.push(1);

	cout << list.toString() << endl;
	cout << (*static_cast<PushPopContainer<int>*>(&list) == *c) << endl;

	system("pause");
	return 0;
}