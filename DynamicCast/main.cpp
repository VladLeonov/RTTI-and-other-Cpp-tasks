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


RTTI_CLASS(O)
RTTI_PARENTS_LIST_END
RTTI_CLASS_END
public:
	char name = 'O';
};


RTTI_CLASS(B)
RTTI_VIRTUAL_PARENT(A,
RTTI_VIRTUAL_PARENT(O,
RTTI_PARENTS_LIST_END))
RTTI_CLASS_END 
public:
	char name = 'B';
};


RTTI_CLASS(C)
RTTI_VIRTUAL_PARENT(A,
RTTI_PARENT(O,
RTTI_PARENTS_LIST_END))
RTTI_CLASS_END
public:
	char name = 'C';
};


RTTI_CLASS(X)
RTTI_PARENTS_LIST_END
RTTI_CLASS_END
public:
	char name = 'X';
};



RTTI_CLASS(D)
RTTI_PARENT(B,
RTTI_PARENT(C,
RTTI_PARENT(X,
RTTI_PARENTS_LIST_END)))
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
	}
	catch (...) {
		std::cout << "Cast to " << typeid(T1).name() << "failed by unknown reason";
	}
	std::cout << std::endl << std::endl;
}


#define TEST_SET(type) \
									/*for pointer		for object*/ \
 \
	testDynamicCast<B>(dd##type);	/*Parent			Parent*/ \
	testDynamicCast<C>(bd##type);	/*Not_Relationship	Parent*/ \
	testDynamicCast<B>(bd##type);	/*Same				Parent*/ \
 \
	testDynamicCast<A>(bd##type);	/*Virtual_Parent	Virtual_Parent		WRONG*/ \
	testDynamicCast<A>(xd##type);	/*Not_Relationship	Virtual_Parent		WRONG*/ \
	testDynamicCast<A>(ad##type);	/*Same				Virtual_Parent*/ \
 \
	testDynamicCast<C>(bb##type);	/*Not_relationship	Not_relationship*/ \
 \
	testDynamicCast<O>(cd##type);	/*Parent			Ambiguous			wrong?*/ \
	testDynamicCast<O>(bd##type);	/*Virtual_Parent	Ambiguous*/ \
	testDynamicCast<O>(xd##type);	/*Not_Relationship	Ambiguous*/ \
	testDynamicCast<O>(dd##type);	/*Ambiguous			Ambiguous*/ \
	testDynamicCast<O>(od##type);	/*Same				Ambiguous*/ \
 \
	testDynamicCast<D>(bd##type);	/*Not_Relationship	Same*/ \
	testDynamicCast<D>(dd##type);	/*Same				Same*/

int main() {

	A().registerClass();
	O().registerClass();
	B().registerClass();
	C().registerClass();
	X().registerClass();
	D().registerClass();

	D d = D();
	B *bdPtr = &d;
	B &bdRef = d;
	D *ddPtr = &d;
	D &ddRef = d;
	X *xdPtr = &d;
	X &xdRef = d;
	A *adPtr = &d;
	A &adRef = d;
	C *cdPtr = &d;
	C &cdRef = d;

	C cd = D();
	O *odPtr = &cd;
	O &odRef = cd;

	B b = B();
	B *bbPtr = &b;
	B &bbRef = b;
	
	TEST_SET(Ptr)
	TEST_SET(Ref)

	D *nul = nullptr;
	testDynamicCast<D>(nul);	//Test null

	std::cout << ddPtr - my_dynamic_cast<void*>(bdPtr) << std::endl;	//Test cast to void*
}
