#include "pch.h"
#include <iostream>
#include "dynamicCast.h"

using namespace dynamicCast;

RTTI_CLASS(A)
RTTI_PARENTS_LIST_END
RTTI_CLASS_END
public:
	char name = 'A';
};


RTTI_CLASS(B)
RTTI_VIRTUAL_PARENT(A,
RTTI_PARENTS_LIST_END)
RTTI_CLASS_END 
public:
	char name = 'B';
};


RTTI_CLASS(C)
RTTI_VIRTUAL_PARENT(A,
RTTI_PARENTS_LIST_END)
RTTI_CLASS_END
public:
	char name = 'C';
};


RTTI_CLASS(D)
RTTI_PARENT(B,
RTTI_PARENT(C,
RTTI_PARENTS_LIST_END))
RTTI_CLASS_END
public:
	char name = 'D';
};


template<class T1, class T2>
void testDynamicCast(T2* ptr) {
	T1 *t= (T1*) my_dynamic_cast<T1*>(ptr);
	if (t != nullptr) {
		std::cout << "Cast to " << typeid(T1).name() << ": " << t->name << std::endl;
		std::cout << "Address: " << t << " ; True address: " << dynamic_cast<T1*>(ptr);
	} else {
		std::cout << "Cast to " << typeid(T1).name() << " failed";
	}
	std::cout << std::endl << std::endl;
}

template<class T1, class T2>
void testDynamicCast(T2& obj) {
	try {
		T1 &t = my_dynamic_cast<T1&>(obj);
		std::cout << "Cast to " << typeid(T1).name() << ": " << t.name << std::endl;
		std::cout << "Address: " << &t << " ; True address: " << &(dynamic_cast<T1&>(obj));
	}
	catch (badCastException) {
		std::cout << "Cast to " << typeid(T1).name() << " failed";
		return;
	}
	catch (...) {
		std::cout << "Cast to " << typeid(T1).name() << "failed by unknown reason";
		return;
	}
	std::cout << std::endl << std::endl;
}


int& foo(int& a) {
	return *(reinterpret_cast<int*>(reinterpret_cast<char*>(&a)));
}


int main() {

	int a = 5;
	int &b = a;
	//int* c = foo(b);

	A().registerClass();
	B().registerClass();
	C().registerClass();
	D().registerClass();

	D d = D();
	B *bPtr = &d;
	B &bRef = d;

	testDynamicCast<A>(bPtr);
	testDynamicCast<B>(bPtr);
	testDynamicCast<C>(bPtr);
	testDynamicCast<D>(bPtr);

	testDynamicCast<A>(bRef);
	testDynamicCast<B>(bRef);
	testDynamicCast<C>(bRef);
	testDynamicCast<D>(bRef);
}
