#include "pch.h"
#include "testObjects.h"
#include "Serializator.h"
#include <iostream>


void GameObject::serialize(Serializator &serializator) const {
	serializator.serializeString("Name", name);
	//serializator.serializeEnumID<Size>("SizeID", size);
	serializator.serializeEnum<Size>("Size", size, SizeEnumToStringConverter());
}


void GameObject::deserialize(Serializator &serializator) {
	name = serializator.deserializeString();
	//size = static_cast<Size>(serializator.deserializeEnumID());
	size = serializator.deserializeEnum<Size>(SizeEnumToStringConverter());
}


void GameObject::print() const {
	std::cout << "Name: " << name << std::endl;
	//std::cout << "SizeID: " << size << std::endl;
	std::cout << "Size: " << SizeEnumToStringConverter().getStringFromEnum(size) << std::endl;
}


void Monster::serialize(Serializator &serializator) const {
	serializator.serializeString("Name", name);
	serializator.serializeInt("MaxHP", maxHP);
}


void Monster::deserialize(Serializator &serializator) {
	name = serializator.deserializeString();
	maxHP = serializator.deserializeInt();
}


void Monster::print() const {
	std::cout << "Name: " << name << std::endl;
	std::cout << "MaxHP: " << maxHP << std::endl;
}


void Weapon::serialize(Serializator &serializator) const {
	serializator.serializeString("Name", name);
	serializator.serializeFloat("Weight", weight);
}


void Weapon::deserialize(Serializator &serializator) {
	name = serializator.deserializeString();
	weight = serializator.deserializeFloat();
}


void Weapon::print() const {
	std::cout << "Name: " << name << std::endl;
	std::cout << "Weight: " << weight << std::endl;
}


void BigBoss::serialize(Serializator &serializator) const {
	Monster::serialize(serializator);
	serializator.serializeComplexType("Weapon", weapon);
}


void BigBoss::deserialize(Serializator &serializator) {
	Monster::deserialize(serializator);
	weapon = serializator.deserializeComplexType<Weapon>();
}


void BigBoss::print() const {
	Monster::print();
	std::cout << "Weapon: " << std::endl;
	weapon.print();
}