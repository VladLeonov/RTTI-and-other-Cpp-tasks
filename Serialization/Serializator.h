#pragma once

#include <string>
#include <fstream>
#include "serializable.h"
#include "enumToStringConverter.h"

class Serializable;

class Serializator {
private:
	enum ioState {
		NO_IO, INPUT, OUTPUT
	};
	ioState fileState;
	std::ifstream inputFile;
	std::ofstream outputFile;
	int indent = 0;
	bool useBinaryMode;
	inline std::string getIndentString();

public:

	Serializator();
	~Serializator();

	void serializeInt(const std::string tag, const int);
	void serializeFloat(const std::string tag, const float);
	void serializeString(const std::string tag, const std::string);
	void serializeComplexType(const std::string tag, const Serializable&);

	template<typename Enum>
	void serializeEnumID(const std::string tag, const Enum value) {
		if ((fileState == OUTPUT) && (std::is_enum<Enum>::value)) {
			outputFile << getIndentString() << tag << ": "
				<< static_cast<int>(value) << std::endl;
		}
	}

	template<typename Enum>
	void serializeEnum(const std::string tag, const Enum value, EnumToStringConverter<Enum, Enum> converter) {
		if ((fileState == OUTPUT) && (std::is_enum<Enum>::value)) {
			serializeString(tag, converter.getStringFromEnum(value));
		}
	}

	void startSerialization(std::string filePath, bool useBinaryMode);
	void endSerialization();

	int deserializeInt();
	float deserializeFloat();
	std::string deserializeString();
	int deserializeEnumID();

	template<typename Enum>
	Enum deserializeEnum(EnumToStringConverter<Enum, Enum> converter) {
		Enum value;
		if (fileState == INPUT) {
			std::string enumString = deserializeString();
			value = converter.getEnumFromString(enumString);
		}
		return value;
	}

	template<typename SerializableType>
	SerializableType deserializeComplexType() {
		SerializableType value;
		if (fileState == INPUT) {
			std::string skip;
			inputFile >> skip >> skip;
			value.deserialize(*this);
			inputFile >> skip;
		}
		return value;
	}
	
	void startDeserialization(std::string filePath, bool useBinaryMode);
	void endDeserialization();
};