#include "pch.h"
#include <iostream>
#include "dynamicCast.h"

class base {
public:
	virtual void print() {
		std::cout << typeid(*this).name();
	}
};

class Good : public virtual base {};
class Bad : public Good, public virtual base {};
class A : public virtual Bad, public virtual base {};
class B : public virtual Bad, public virtual base {};
class C : public A, public B, public virtual base {};

template<class base, class derivative>
size_t getOffsetDelta() {
	derivative obj;
	return reinterpret_cast<char*>(static_cast<base*>(&obj)) - reinterpret_cast<char*>(&obj);
}

int main() {
	C c = C();
	Good &g = c;
	Bad &b = dynamic_cast<Bad&>(g);
	//b.print();
	std::cout << getOffsetDelta<A, C>() << std::endl;
	std::cout << getOffsetDelta<B, C>() << std::endl;
	std::cout << getOffsetDelta<Bad, C>() << std::endl;
	std::cout << getOffsetDelta<Good, C>() << std::endl;
}
