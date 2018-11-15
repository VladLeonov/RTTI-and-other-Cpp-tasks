#pragma once
#include <string>
#include <map>
#include "rttiBase.h"

namespace rtti {

	using std::string;
	class RttiBase;

	struct RttiFieldInfo {
		string type;
		size_t offset;
	};

	typedef RttiBase* (*createRttiBaseMethod)();

	struct RttiClassInfo {
		string name;
		std::map<string, RttiFieldInfo> fields;
		createRttiBaseMethod createInstanceMethod;
		size_t size;

		RttiClassInfo() {};
		RttiClassInfo(string name) : name(name) {}

		void addField(string type, string name, size_t offset) {
			fields[name] = { type, offset };
		}
	};


	struct RttiEnumInfo {
		std::map<int, string> stringFromIntMap;
		std::map<string, int> intFromStringMap;
	};
}