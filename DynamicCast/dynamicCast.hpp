#pragma once
#include "dynamicCast.h"

namespace dynamicCast {

	template<class T1, class T2>
	T1* my_dynamic_cast(T2* ptr) {

		if (ptr == nullptr) {
			return (T1*) nullptr;
		}
		
		VirtualTable::ClassesRelationship vtcr = VirtualTable::getRelationship(ptr->getTypeName(), typeid(T1).name());
	}


	template<class T2>
	void* my_dynamic_cast(T2* ptr) {
		VirtualTable::ClassesRelationship vtcr = VirtualTable::getRelationship(ptr->getTypeName(), typeid(T2).name());
		return reinterpret_cast<void*>(reinterpret_cast<char*>(ptr) - vtcr.offset);
	}


	template<class T1, class T2>
	T1& my_dynamic_cast(T2& obj) throw(badCastException) {
		//
	}
}