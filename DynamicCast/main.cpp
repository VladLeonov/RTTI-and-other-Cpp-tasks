#include "pch.h"
#include <iostream>
#include "dynamicCast.h"

using namespace dynamicCast;

RTTI_CLASS(A)
RTTI_PARENTS_LIST_END
RTTI_CLASS_END
public:
	char name = 'A';
	void introduceSelf() {
		std::cout << name << std::endl;
	}
};


RTTI_CLASS(B)
RTTI_VIRTUAL_PARENT(A,
RTTI_PARENTS_LIST_END)
RTTI_CLASS_END 
public:
	char name = 'B';
	void introduceSelf() {
		std::cout << name << std::endl;
	}
};


RTTI_CLASS(C)
RTTI_VIRTUAL_PARENT(A,
RTTI_PARENTS_LIST_END)
RTTI_CLASS_END
public:
	char name = 'C';
	void introduceSelf() {
		std::cout << name << std::endl;
	}
};


RTTI_CLASS(D)
RTTI_PARENT(B,
RTTI_PARENT(C,
RTTI_PARENTS_LIST_END))
RTTI_CLASS_END
public:
	char name = 'D';
	void introduceSelf() {
		std::cout << name << std::endl;
	}
};


template<class T1, class T2>
void testDynamicCast(T2* ptr) {
	T1 *t= my_dynamic_cast<T1*>(ptr);
	if (t != nullptr) {
		std::cout << "Cast to " << typeid(T1).name() << ": ";
		t->introduceSelf();
		std::cout << "Address: " << t << " ; True address: " << dynamic_cast<T1*>(ptr) << std::endl;
	} else {
		std::cout << "Cast to " << typeid(T1).name() << "failed";
		t->introduceSelf();
	}
	std::cout << std::endl;
}


int main() {

	A().registerClass();
	B().registerClass();
	C().registerClass();
	D().registerClass();

	D d = D();
	B *b = &d;

	testDynamicCast<A>(b);
	testDynamicCast<B>(b);
	testDynamicCast<C>(b);
	testDynamicCast<D>(b);
}
