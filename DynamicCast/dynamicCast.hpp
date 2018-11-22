#pragma once
#include <type_traits>

namespace dynamicCast {

	typedef VirtualTable::ClassesRelationship vtcr;


	template<class T1, class T2>
	T1 my_dynamic_cast(T2& obj) throw(badCastException) {

		static_assert(std::is_reference<T1>::value, "Template parameters must be either pointers or references");

		size_t selfOffset = VirtualTable::getRelationship(obj.getTypeName(), typeid(T2).name()).offset;
		vtcr trueRelationship = VirtualTable::getRelationship(obj.getTypeName(), typeid(std::remove_reference<T1>::type).name());
		vtcr relationship = VirtualTable::getRelationship(typeid(T2).name(), typeid(std::remove_reference<T1>::type).name());

		switch (trueRelationship.state) {
		case vtcr::SAME:
			return reinterpret_cast<T1>(obj);
			break;

		case vtcr::PARENT:
			return *(reinterpret_cast<typename std::remove_reference<T1>::type*>(reinterpret_cast<char*>(&obj) + trueRelationship.offset - selfOffset));
			break;

		case vtcr::VIRTUAL_PARENT:
			return *(reinterpret_cast<typename std::remove_reference<T1>::type*>(reinterpret_cast<char*>(&obj) + trueRelationship.offset - selfOffset)); //TODO: offset calculation
			break;

		case vtcr::AMBIGUOUS:
			if (relationship.state == vtcr::PARENT) {
				return *(reinterpret_cast<typename std::remove_reference<T1>::type*>(reinterpret_cast<char*>(&obj) + relationship.offset));
			}
			break;
		}

		throw badCastException();
	}

	template<class T1, class T2>
	T1 my_dynamic_cast(T2* ptr) {

		static_assert(std::is_pointer<T1>::value, "Template parameters must be either pointers or references");

		if (ptr == nullptr) {
			return (T1) nullptr;
		}

		size_t selfOffset = VirtualTable::getRelationship(ptr->getTypeName(), typeid(T2).name()).offset;

		if (std::is_same<void*, typename std::remove_cv<T1>::type>::value) {
			return reinterpret_cast<T1>(reinterpret_cast<char*>(ptr) - selfOffset);
		}

		vtcr trueRelationship = VirtualTable::getRelationship(ptr->getTypeName(), typeid(std::remove_pointer<T1>::type).name());
		vtcr relationship = VirtualTable::getRelationship(typeid(T2).name(), typeid(std::remove_pointer<T1>::type).name());

		switch (trueRelationship.state) {
		case vtcr::SAME:
			return reinterpret_cast<T1>(ptr);
			break;

		case vtcr::PARENT:
			return reinterpret_cast<T1>(reinterpret_cast<char*>(ptr) + trueRelationship.offset - selfOffset);
			break;

		case vtcr::VIRTUAL_PARENT:
			return reinterpret_cast<T1>(reinterpret_cast<char*>(ptr) + trueRelationship.offset - selfOffset); //TODO: offset calculation
			break;

		case vtcr::AMBIGUOUS:
			if (relationship.state == vtcr::PARENT) {
				return reinterpret_cast<T1>(reinterpret_cast<char*>(ptr) + relationship.offset);
			}
			break;
		}

		return (T1) nullptr;
	}
}