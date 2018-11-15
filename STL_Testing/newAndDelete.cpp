#include "pch.h"
#include "newAndDelete.h"
#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>

using namespace std;


void * operator new(size_t n) throw(bad_alloc) {
	void *p = malloc(n);
	cout << "new \t" << n << " bytes \t" << p << endl;
	return p;
}


void operator delete(void * p, size_t n) throw() {
	cout << "delete \t" << n << " bytes \t" << p << endl;
	free(p);
}


template<class Container>
void testContainer() {
	cout << typeid(Container).name() << endl;
	Container *container = new Container();
	delete container;
	//{Container container;}
	cout << endl;
}


void testNewAndDelete() {
	typedef int type;
	//Sequence containers
	testContainer<array<type, 10>>();
	testContainer<vector<type>>();
	testContainer<deque<type>>();
	testContainer<forward_list<type>>();
	testContainer<list<type>>();
	//Container adaptors
	testContainer<stack<type>>();
	testContainer<queue<type>>();
	testContainer<priority_queue<type>>();
	//Sorted containers
	testContainer<set<type>>();
	testContainer<multiset<type>>();
	testContainer<map<type, type>>();
	testContainer<multimap<type, type>>();
}