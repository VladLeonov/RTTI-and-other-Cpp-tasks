#pragma once
#include <type_traits>
#include <map>


template<class Enum, class = typename std::enable_if<std::is_enum<Enum>::value>::type>
class EnumToStringConverter {
protected:
	std::map<Enum, std::string> mapEnumToString;
	std::map<std::string, Enum> mapStringToEnum;
	void initializeMaps();

public:
	/*EnumToStringConverter();
	~EnumToStringConverter();

	static Enum getEnumFromString(std::string);
	static std::string getStringFromEnum(Enum);*/
	EnumToStringConverter() {
		//initializeMaps();
	}

	~EnumToStringConverter() {}

	Enum getEnumFromString(std::string value) {
		return mapStringToEnum.at(value);
	}

	std::string getStringFromEnum(Enum value) {
		return mapEnumToString.at(value);
	}
};

