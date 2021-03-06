#include "pch.h"
#include <iostream>
#include "testObjects.h"
#include "Serializator.h"


class TestSet {
private:
	GameObject table;
	Monster goblin;
	Weapon axe;
	BigBoss goblinLeader;
	Serializator serializator;

public:
	TestSet() : table("Table", MEDIUM), goblin("Goblin", 100), 
		axe("Axe", 2.5f), goblinLeader("Goblin Leader", 150, axe) {};

	void print() {
		table.print();
		std::cout << std::endl;
		goblin.print();
		std::cout << std::endl;
		axe.print();
		std::cout << std::endl;
		goblinLeader.print();
		std::cout << std::endl;
	}

	void serializeAll(std::string path, bool useBinaryMode) {
		serializator.startSerialization(path, useBinaryMode);
		serializator.serializeComplexType("Table", table);
		serializator.serializeComplexType("Goblin", goblin);
		serializator.serializeComplexType("Axe", axe);
		serializator.serializeComplexType("GoblinLeader", goblinLeader);
		serializator.endSerialization();
	}

	void deserializeAll(std::string path, bool useBinaryMode) {
		serializator.startDeserialization(path, useBinaryMode);
		table = serializator.deserializeComplexType<GameObject>();
		goblin = serializator.deserializeComplexType<Monster>();
		axe = serializator.deserializeComplexType<Weapon>();
		goblinLeader = serializator.deserializeComplexType<BigBoss>();
		serializator.endDeserialization();
	}
};


int main() {
	bool useBinaryMode = false;
	TestSet testSet;
	testSet.print();
	testSet.serializeAll("OutputFiles/testObjects.txt", useBinaryMode);
	testSet.deserializeAll("OutputFiles/testObjects.txt", useBinaryMode);
	std::cout << "---" << std::endl << std::endl;
	testSet.print();
}