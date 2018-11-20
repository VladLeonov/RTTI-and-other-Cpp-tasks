#pragma once
#include <map>
#include <list>
#include <typeinfo>

namespace dynamicCast {

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
				PARENT, VIRTUAL_PARENT, NOT_RELATIONSHIP, AMBIGUOUS
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
	size_t getOffset() {
		derivative obj;
		return reinterpret_cast<char*>(static_cast<base*>(&obj)) - reinterpret_cast<char*>(&obj);
	}


	template<class T1, class T2>
	T1* my_dynamic_cast(T2*);


	template<class T1, class T2>
	T1& my_dynamic_cast(T2&);
}