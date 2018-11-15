#pragma once
#include <string>
#include "rttiCore.h"
#include "rttiBase.h"


namespace gameObjects {

	enum class Size {
		SMALL, MEDIUM, LARGE
	};

	RTTI_ENUM_START(Size)
	RTTI_ENUM_VALUE(SMALL)
	RTTI_ENUM_VALUE(MEDIUM)
	RTTI_ENUM_VALUE(LARGE)
	RTTI_ENUM_END()


	class Weapon : public rtti::RttiBase {
	private:
		std::string name;
		float weight;
		Size size;

	public:
		Weapon() {}
		Weapon(std::string name, float weight, Size size) : name(name), weight(weight), size(size) {};

		RTTI_CLASS_START(Weapon)
		RTTI_CLASS_FIELD(name)
		RTTI_CLASS_FIELD(weight)
		RTTI_CLASS_FIELD(size)
		RTTI_CLASS_END()
	};


	class Monster : public rtti::RttiBase {
	protected:
		std::string name;
		int maxHP;

	public:
		Monster() {}
		Monster(std::string name, int maxHP) : name(name), maxHP(maxHP) {};

		RTTI_CLASS_START(Monster)
		RTTI_CLASS_FIELD(name)
		RTTI_CLASS_FIELD(maxHP)
		RTTI_CLASS_END()
	};


	class BigBoss : public Monster {
	private:
		Weapon weapon;

	public:
		BigBoss() {}
		BigBoss(std::string name, int maxHP, Weapon weapon) : Monster(name, maxHP), weapon(weapon) {};

		RTTI_CLASS_START(BigBoss)
		RTTI_CLASS_PARENT(Monster)
		RTTI_CLASS_FIELD(weapon)
		RTTI_CLASS_END()
	};

}