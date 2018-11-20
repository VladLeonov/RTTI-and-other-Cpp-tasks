#include "pch.h"
#include <iostream>
#include "dynamicCast.h"

using namespace dynamicCast;

RTTI_CLASS(A)
RTTI_PARENTS_LIST_END
RTTI_CLASS_END };

RTTI_CLASS(B)
RTTI_VIRTUAL_PARENT(A,
RTTI_PARENTS_LIST_END)
RTTI_CLASS_END };

RTTI_CLASS(C)
RTTI_VIRTUAL_PARENT(A,
RTTI_PARENTS_LIST_END)
RTTI_CLASS_END };

RTTI_CLASS(D)
RTTI_PARENT(B,
RTTI_PARENT(C,
RTTI_PARENTS_LIST_END))
RTTI_CLASS_END };

int main() {

	A().registerClass();
	B().registerClass();
	C().registerClass();
	D().registerClass();

	VirtualTable::ClassesRelationship vtcr = VirtualTable::getRelationship(typeid(D).name(), typeid(A).name());

	int i;
}
