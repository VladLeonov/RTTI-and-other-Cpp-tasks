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
	T1 *t = my_dynamic_cast<T1*>(ptr);
	if (t != nullptr) {
		std::cout << "Cast to " << typeid(T1).name() << ": " << t->name << std::endl;
	} else {
		std::cout << "Cast to " << typeid(T1).name() << " return nullptr" << std::endl;
	}
}

template<class T1, class T2>
void testDynamicCast(T2& obj) {
	try {
		T1 &t = my_dynamic_cast<T1&>(obj);
		std::cout << "Cast to " << typeid(T1).name() << ": " << t.name << std::endl;
	}
	catch (badCastException) {
		std::cout << "Cast to " << typeid(T1).name() << " throw badCastException" << std::endl;
	}
	catch (...) {
		std::cout << "Cast to " << typeid(T1).name() << "failed by unknown reason" << std::endl;
	}
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
	testDynamicCast<O>(cd##type);	/*Parent			Ambiguous*/ \
	testDynamicCast<O>(bd##type);	/*Virtual_Parent	Ambiguous*/ \
	testDynamicCast<O>(xd##type);	/*Not_Relationship	Ambiguous*/ \
	testDynamicCast<O>(dd##type);	/*Ambiguous			Ambiguous*/ \
	testDynamicCast<O>(ocd##type);	/*Same				Ambiguous*/ \
 \
	testDynamicCast<D>(bd##type);	/*Not_Relationship	Same*/ \
	testDynamicCast<D>(dd##type);	/*Same				Same*/


#define CREATE_TEST_VARIABLES(type, lowerCaseType, targetObject) \
	type *lowerCaseType##targetObject##Ptr = &targetObject; \
	type &lowerCaseType##targetObject##Ref = targetObject;


int main() {

	A().registerClass();
	O().registerClass();
	B().registerClass();
	C().registerClass();
	X().registerClass();
	D().registerClass();

	D d = D();
	CREATE_TEST_VARIABLES(A, a, d)
	CREATE_TEST_VARIABLES(B, b, d)
	CREATE_TEST_VARIABLES(C, c, d)
	CREATE_TEST_VARIABLES(D, d, d)
	CREATE_TEST_VARIABLES(X, x, d)

	C cd = D();
	CREATE_TEST_VARIABLES(O, o, cd)

	B b = B();
	CREATE_TEST_VARIABLES(B, b, b)

	std::cout << std::endl << "---Pointer casts---" << std::endl << std::endl;
	TEST_SET(Ptr)

	std::cout << std::endl << "---References casts---" << std::endl << std::endl;
	TEST_SET(Ref)

	std::cout << std::endl << "---Special casts---" << std::endl << std::endl;

	D *nul = nullptr;
	testDynamicCast<D>(nul);	

	if (ddPtr - my_dynamic_cast<void*>(bdPtr) == 0) {
		std::cout << "Cast to void* succeed" << std::endl;
	} else {
		std::cout << "Cast to void* failed" << std::endl;
	}	
}
