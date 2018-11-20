#pragma once
#include "dynamicCast.h"

namespace dynamicCast {

	typedef VirtualTable::ClassesRelationship vtcr;

	template<class T1, class T2>
	T1* my_dynamic_cast(T2* ptr) {

		if (ptr == nullptr) {
			return (T1*) nullptr;
		}
		
		vtcr relationship = VirtualTable::getRelationship(ptr->getTypeName(), typeid(T1).name());

		switch (relationship.state) {
			case vtcr::SAME:
				return (T1*) ptr;
				break;
			case vtcr::PARENT:
			case vtcr::VIRTUAL_PARENT:
				return reinterpret_cast<T1*>(reinterpret_cast<char*>(ptr) - relationship.offset);
				break;
		}

		relationship = VirtualTable::getRelationship(typeid(T1).name(), ptr->getTypeName());

		//
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