#include <iostream>
#include "GameObjects.h"
#include "rttiCore.h"
#include <fstream>

struct A {
	int a;
};

struct B {
	int b;
};

struct C : public A, B {
	int c;
};

int main() {

	using namespace gameObjects;

	RTTI_REGISTER_ENUM(Size)
	RTTI_REGISTER_CLASS(Weapon)
	RTTI_REGISTER_CLASS(Monster)
	RTTI_REGISTER_CLASS(BigBoss)

	std::ofstream outputFile;
	outputFile.open("OutputFiles/testObjects.txt");

	Weapon sword("Sword", 1.5f, Size::MEDIUM);
	Monster goblin("Goblin", 100);
	BigBoss bigGoblin("Big Goblin", 150, sword);

	rtti::writeRttiBaseObject(outputFile, &sword);
	rtti::writeRttiBaseObject(outputFile, &goblin);
	rtti::writeRttiBaseObject(outputFile, &bigGoblin);

	outputFile.close();

	//---

	std::ifstream inputFile;
	inputFile.open("OutputFiles/testObjects.txt");

	Weapon sword2 = *((Weapon*) rtti::readRttiBaseObject(inputFile));
	Monster goblin2 = *((Monster*)rtti::readRttiBaseObject(inputFile));
	BigBoss bigGoblin2 = *((BigBoss*)rtti::readRttiBaseObject(inputFile));

	outputFile.open("OutputFiles/testObjects2.txt");

	rtti::writeRttiBaseObject(outputFile, &sword2);
	rtti::writeRttiBaseObject(outputFile, &goblin2);
	rtti::writeRttiBaseObject(outputFile, &bigGoblin2);

	inputFile.close();
	outputFile.close();
}
