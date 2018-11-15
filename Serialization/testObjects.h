#pragma once

#include "serializable.h"
#include "Serializator.h"
#include <string>
#include "enumToStringConverter.h"


enum Size {
	SMALL = 0, MEDIUM = 1, BIG = 2
};


class SizeEnumToStringConverter : public EnumToStringConverter<Size, Size> {
private:
	void initializeMaps() {
		mapEnumToString = { {SMALL, "SMALL"}, {MEDIUM, "MEDIUM"}, {BIG, "BIG"} };
		mapStringToEnum = { {"SMALL", SMALL}, {"MEDIUM" ,MEDIUM}, {"BIG", BIG} };
	}
public:
	SizeEnumToStringConverter() {
		initializeMaps();
	}
};


class GameObject : public Serializable {
private:
	std::string name;
	Size size;

public:
	GameObject() {}
	GameObject(std::string name, Size size) : name(name), size(size) {};
	void serialize(Serializator &serializator) const;
	void deserialize(Serializator &serializator);
	void print() const;
};


class Monster : public Serializable {
protected:
	std::string name;
	int maxHP;

public:
	Monster() {}
	Monster(std::string name, int maxHP) : name(name), maxHP(maxHP) {};
	void print() const;
	void serialize(Serializator &serializator) const;
	void deserialize(Serializator &serializator);
};


class Weapon : public Serializable {
private:
	std::string name;
	float weight;

public:
	Weapon() {}
	Weapon(std::string name, float weight) : name(name), weight(weight) {};
	void print() const;
	void serialize(Serializator &serializator) const;
	void deserialize(Serializator &serializator);
};


class BigBoss : public Monster {
private:
	Weapon weapon;

public:
	BigBoss() {}
	BigBoss(std::string name, int maxHP, Weapon weapon) : Monster(name, maxHP), weapon(weapon) {};
	void print() const;
	void serialize(Serializator &serializator) const;
	void deserialize(Serializator &serializator);
};