#pragma once
#include <map>
#include <list>
#include <typeinfo>

namespace dynamicCast {

	#define RTTI_CLASS(className) \
		class className :

	#define RTTI_NOT_CASTING_PARENT(modifier, className, nextPart) \
		modifier className, \
		nextPart \

	#define RTTI_PARENT(className, nextPart) \
		public className, \
		nextPart \
		parents.push_back({typeid(className).name(), false, getOffset<className>(this)});

	#define RTTI_VIRTUAL_PARENT(className, nextPart) \
		public virtual className, \
		nextPart \
		parents.push_back({typeid(className).name(), true, getOffset<className>(this)});		

	#define RTTI_PARENTS_LIST_END \
		public virtual DynamicCastBaseClass { \
		public: \
			void registerClass() { \
				list<ClassParentData> parents = {}; \

	#define RTTI_CLASS_END \
				VirtualTable::registerClass(typeid(*this).name(), parents); \
			} \
		private:

	using namespace std;

	class DynamicCastBaseClass {
	public:
		virtual string getTypeName() {
			return typeid(*this).name();
		}
	};


	struct ClassParentData {
		string typeName;
		bool isInheritedVirtually;
		size_t offset;
	};


	class VirtualTable {
	public:

		struct ClassesRelationship {
			enum {
				PARENT, VIRTUAL_PARENT, NOT_RELATIONSHIP, AMBIGUOUS, SAME
			} state;
			size_t offset;
		};

		static void registerClass(string className, list<ClassParentData> parentsData) {
			data[className] = parentsData;
		};
		static ClassesRelationship getRelationship(string derivativeClassName, string baseClassName);

	private:
		static map<string, list<ClassParentData>> data;

		VirtualTable() {};
		~VirtualTable() {};
		VirtualTable(VirtualTable const&);
		VirtualTable& operator= (VirtualTable const&);
	};


	template<class base, class derivative>
	size_t getOffset(derivative *obj) {
		return reinterpret_cast<char*>(static_cast<base*>(obj)) - reinterpret_cast<char*>(obj);
	}


	class badCastException {};


	template<class T1, class T2>
	T1 my_dynamic_cast(T2) throw(badCastException);
}

#include "dynamicCast.hpp"