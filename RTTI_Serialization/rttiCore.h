#pragma once
#include <string>
#include <list>
#include <map>
#include "rttiBase.h"
#include "rttiInfo.h"
#include <fstream>
#include <iostream>

#define RTTI_CLASS_START(Class) \
typedef Class RttiClassName; \
static rtti::RttiBase *createInstance() { \
	return new RttiClassName(); \
} \
rtti::RttiClassInfo getRttiInfo() { \
	rtti::RttiClassInfo info(typeid(RttiClassName).name()); \
	info.createInstanceMethod = (rtti::createRttiBaseMethod) &createInstance; \
	info.size = sizeof(RttiClassName); \
	rtti::RttiClassInfo parentInfo; \
	rtti::RttiCore &core = rtti::RttiCore::instance();

#define RTTI_CLASS_PARENT(parent) \
	parentInfo = core.findClassInfo(typeid(parent).name()); \
	RttiClassName obj; \
	size_t offsetDelta = reinterpret_cast<char *>(static_cast<parent *>(&obj)) - reinterpret_cast<char *>(&obj); \
	for (auto field = parentInfo.fields.begin(); field != parentInfo.fields.end(); field++) { \
		info.addField(field->second.type, field->first, field->second.offset + offsetDelta); \
	}

#define RTTI_CLASS_FIELD(field) \
	info.addField(typeid(field).name(), #field, (int)offsetof(RttiClassName, field));

#define RTTI_CLASS_END() \
	return info;} \
void rttiRegister() { \
	rtti::RttiCore::instance().registerClass(typeid(RttiClassName).name(), getRttiInfo()); \
}

#define RTTI_ENUM_START(Enum) \
void rttiRegisterEnum##Enum() { \
	rtti::RttiEnumInfo enumInfo; \
	typedef Enum RttiEnumName;

#define RTTI_ENUM_VALUE(value) \
	enumInfo.stringFromIntMap[static_cast<int>(RttiEnumName::value)] = #value; \
	enumInfo.intFromStringMap[#value] = static_cast<int>(RttiEnumName::value);

#define RTTI_ENUM_END() \
	rtti::RttiCore::instance().registerEnum(typeid(RttiEnumName).name(), enumInfo); \
}

#define RTTI_REGISTER_CLASS(Class) \
	Class().rttiRegister();

#define RTTI_REGISTER_ENUM(Enum) \
	rttiRegisterEnum##Enum();


namespace rtti {

	using std::string;


	class RttiCore {
	public:

		static RttiCore& instance() {
			static RttiCore s;
			return s;
		}

		void registerClass(string fullClassName, RttiClassInfo classInfo);
		void registerEnum(string fullEnumName, RttiEnumInfo enumInfo);
		RttiClassInfo findClassInfo(string fullClassName);
		RttiEnumInfo findEnumInfo(string fullEnumName);

		enum keyWord {
			CLASS, FIELD, CLASS_END
		};

		const std::map<keyWord, string> keyWordsStrings{
			std::make_pair(CLASS, "{"),
			std::make_pair(FIELD, "FIELD"),
			std::make_pair(CLASS_END, "}")
		};

	private:
		std::map<string, RttiClassInfo> classesInfo;
		std::map<string, RttiEnumInfo> enumsInfo;
		RttiCore() {};
		~RttiCore() {};
		RttiCore(RttiCore const&);
		RttiCore& operator= (RttiCore const&);
	};


	void writeRttiBaseObject(std::ofstream &outputFile, RttiBase *p, int indent = 0);
	RttiBase *readRttiBaseObject(std::ifstream &inputFile, size_t *pSize = nullptr);
}