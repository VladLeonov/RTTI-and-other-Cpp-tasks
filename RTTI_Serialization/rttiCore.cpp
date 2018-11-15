#include "pch.h"
#include "rttiCore.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include "rttiInfo.h"

namespace rtti {

	void RttiCore::registerClass(string fullClassName, RttiClassInfo classInfo) {
		classesInfo[fullClassName] = classInfo;
	}


	void RttiCore::registerEnum(string fullEnumName, RttiEnumInfo enumInfo) {
		enumsInfo[fullEnumName] = enumInfo;
	}
	

	RttiClassInfo RttiCore::findClassInfo(string fullClassName) {
		return classesInfo.at(fullClassName);
	}


	RttiEnumInfo RttiCore::findEnumInfo(string fullEnumName) {
		return enumsInfo.at(fullEnumName);
	}


	bool isEnumTypeName(string name) {
		return name.compare(0, 5, "enum ") == 0;
	}


	bool isClassTypeName(string name) {
		return name.compare(0, 6, "class ") == 0;
	}


	bool isStringTypeName(string name) {
		return name.compare(typeid(string).name()) == 0;
	}


	inline string getIndentString(int indent) {
		return string(indent, '\t');
	}


	inline void writeField(std::ofstream &outputFile, void * fieldPointer, string type) {
		if (type.compare(typeid(int).name()) == 0) {
			outputFile << *((int*)fieldPointer) << std::endl;

		} else if (type.compare(typeid(float).name()) == 0) {
			outputFile << *((float*)fieldPointer) << std::endl;

		} else if (type.compare(typeid(string).name()) == 0) {
			outputFile << *((string*)fieldPointer) << '\0' << std::endl;
		}
	}


	inline void writeEnum(std::ofstream &outputFile, void * fieldPointer, RttiEnumInfo enumInfo) {
		outputFile << enumInfo.stringFromIntMap.at(*((int*)fieldPointer)) << std::endl;
	}


	void writeRttiBaseObject(std::ofstream &outputFile, RttiBase * pObject, int indent) {
		RttiCore &core = RttiCore::instance();
		RttiClassInfo classInfo = core.findClassInfo(typeid(*pObject).name());
		outputFile << classInfo.name << '\0' << ' ' << core.keyWordsStrings.at(core.CLASS) << std::endl;

		for (auto field = classInfo.fields.begin(); field != classInfo.fields.end(); field++) {
			void *fieldPointer = (void*)((int)pObject + field->second.offset);
			outputFile << getIndentString(indent + 1) <<core.keyWordsStrings.at(core.FIELD) << ' ' << field->first << ' ';

			if ((isClassTypeName(field->second.type)) && !(isStringTypeName(field->second.type))) {
				writeRttiBaseObject(outputFile, (RttiBase*)fieldPointer, indent + 1);
			} else if (isEnumTypeName(field->second.type)) {
				writeEnum(outputFile, fieldPointer, core.findEnumInfo(field->second.type));
			} else {
				writeField(outputFile, fieldPointer, field->second.type);
			}
		}

		outputFile << getIndentString(indent) << core.keyWordsStrings.at(core.CLASS_END) << std::endl;
	}


	string readNullTerminatedString(std::ifstream &inputFile) {
		string value = "";
		char c;
		while ((inputFile.get(c)) && (((c == ' ')) || ((c == '\n')) || ((c == '\t')))) {}
		value += c;
		while ((inputFile.get(c)) && (c != '\0')) {
			value += c;
		}
		return value;
	}


	void readField(std::ifstream &inputFile, RttiClassInfo classInfo, RttiBase *rttiObject) {
		string name;
		inputFile >> name;
		RttiFieldInfo fieldInfo = classInfo.fields.at(name);
		void *fieldPointer = (void*)((int)rttiObject + fieldInfo.offset);

		if (isEnumTypeName(fieldInfo.type)) {
			string stringValue;
			inputFile >> stringValue;
			int intValue = RttiCore::instance().findEnumInfo(fieldInfo.type).intFromStringMap.at(stringValue);
			memcpy(fieldPointer, &intValue, sizeof(int));

		} else if (isStringTypeName(fieldInfo.type)) {
			*((string*)fieldPointer) = readNullTerminatedString(inputFile);

		} else if (fieldInfo.type.compare(typeid(int).name()) == 0) {
			inputFile >> *((int*)fieldPointer);

		} else if (fieldInfo.type.compare(typeid(float).name()) == 0) {
			inputFile >> *((float*)fieldPointer);

		} else if (isClassTypeName(fieldInfo.type)) {
			size_t size;
			RttiBase *object = readRttiBaseObject(inputFile, &size);
			memcpy(fieldPointer, object, size);
		}
	}


	RttiBase *readRttiBaseObject(std::ifstream &inputFile, size_t *pSize) {
		RttiCore &core = RttiCore::instance();
		RttiClassInfo classInfo = core.findClassInfo(readNullTerminatedString(inputFile));
		RttiBase *rttiObject = classInfo.createInstanceMethod();
		string keyword;
		inputFile >> keyword;
		while (!inputFile.eof()) {
			inputFile >> keyword;
			if (keyword.compare(core.keyWordsStrings.at(core.FIELD)) == 0) {
				readField(inputFile, classInfo, rttiObject);
			} else if (keyword.compare(core.keyWordsStrings.at(core.CLASS_END)) == 0) {
				break;
			}
		}
		if (pSize != nullptr) {
			*pSize = classInfo.size;
		}
		return rttiObject;
	}
}

