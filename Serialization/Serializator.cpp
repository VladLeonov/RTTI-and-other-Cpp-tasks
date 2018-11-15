#include "pch.h"
#include "Serializator.h"
#include "serializable.h"
#include <fstream>
#include <type_traits>


Serializator::Serializator() {
}


Serializator::~Serializator() {
}


inline std::string Serializator::getIndentString() {
	return useBinaryMode ? "" : std::string(indent, '\t');
}


void Serializator::serializeInt(const std::string tag, const int value) {
	if (fileState == OUTPUT) {
		outputFile << getIndentString() << tag << ": " << value << std::endl;
	}
}


void Serializator::serializeFloat(const std::string tag, const float value) {
	if (fileState == OUTPUT) {
		outputFile << getIndentString() << tag << ": " << value << std::endl;
	}
}


/*template<typename Enum>
void Serializator::serializeEnumID(const std::string tag, const Enum value) {
	if ((fileState == OUTPUT) && (std::is_enum<Enum>::value)) {
		outputFile << getIndentString() << tag << ": " 
			       << static_cast<int>(value) << std::endl;
	}
}*/


void Serializator::serializeString(const std::string tag, const std::string value) {
	if (fileState == OUTPUT) {
		outputFile << getIndentString() << tag << ": " << value.c_str() << '\0' << std::endl;
	}
}


void Serializator::serializeComplexType(const std::string tag, const Serializable& value) {
	if (fileState == OUTPUT) {
		outputFile << getIndentString() << tag << ": {" << std::endl;
		indent++;
		value.serialize(*this);
		indent--;
		outputFile << getIndentString() << '}' << std::endl;
	}
}

void Serializator::startSerialization(std::string filePath, bool useBinaryMode) {
	if (fileState == NO_IO) {
		indent = 0;
		this->useBinaryMode = useBinaryMode;
		if (useBinaryMode) {
			outputFile.open(filePath, std::ios::binary);
		} else {
			outputFile.open(filePath);
		}
		fileState = OUTPUT;
		outputFile << '{' << std::endl;
		indent++;
	}
}


void Serializator::endSerialization() {
	if (fileState == OUTPUT) {
		outputFile << '}';
		outputFile.close();
		fileState = NO_IO;
	}
}


int Serializator::deserializeInt() {
	int value = 0;
	if (fileState == INPUT) {
		std::string skip;
		inputFile >> skip >> value;
	}
	return value;
}


float Serializator::deserializeFloat() {
	float value = 0;
	if (fileState == INPUT) {
		std::string skip;
		inputFile >> skip >> value;
	}
	return value;
}


std::string Serializator::deserializeString() {
	std::string value = "";
	if (fileState == INPUT) {
		std::string skip;
		char c;
		inputFile >> skip;
		inputFile.get(c);
		while (inputFile.get(c)) {
			if (c != '\0') {
				value += c;
			} else {
				break;
			}
		}
	}
	return value;
}


int Serializator::deserializeEnumID() {
	int value = 0;
	if (fileState == INPUT) {
		std::string skip;
		inputFile >> skip >> value;
	}
	return value;
}


/*template<typename SerializableType>
SerializableType Serializator::deserializeComplexType() {
	SerializableType value;
	if (fileState == INPUT) {
		std::string skip;
		inputFile >> skip >> skip;
		value.deserialize(*this);
		inputFile >> skip;
	}
	return value;
}*/


void Serializator::startDeserialization(std::string filePath, bool useBinaryMode) {
	if (fileState == NO_IO) {
		this->useBinaryMode = useBinaryMode;
		if (useBinaryMode) {
			inputFile.open(filePath, std::ios::binary);
		}
		else {
			inputFile.open(filePath);
		}
		fileState = INPUT;
		std::string skip;
		inputFile >> skip;
	}
}


void Serializator::endDeserialization() {
	if (fileState == INPUT) {
		inputFile.close();
		fileState = NO_IO;
	}
}