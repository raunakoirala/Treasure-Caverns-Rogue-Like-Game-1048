/**************************************************
  Project: Assignment 4
  Author: Raunak Koirala
  Student No. 32509987

  Date Updated:31/10/2022
  Purpose: Manages Monster Class

 **************************************************/

#include "Monster.h"

 //constructors
Monster::Monster() {

	monsterName = "Goblin";


	monsterLevel = 1;
	monsterHealth = 2;
	monsterAttack = 3;
	monsterDefence = 3;
	monsterDamage = 1;


}


Monster::Monster(string name) {

	setName(name);
	setLevel();
	setHealth();
	setAttack();
	setDefence();
	setDamage();


}

//destructor
Monster::~Monster() {

}


//accesors
string Monster::getName() {
	return monsterName;
}

int Monster::getHealth() {
	return monsterHealth;
}

int Monster::getAttack() {
	return monsterAttack;
}

int Monster::getDefence() {
	return monsterDefence;
}

int Monster::getDamage() {
	return monsterDamage;
}

int Monster::getLevel() {
	return monsterLevel;
}




//mutators
void Monster::setName(string name) {
	monsterName = name;
}

//based on monster stats
void Monster::setHealth() {


	if (monsterName == "Goblin") {
		monsterHealth = monsterLevel + (rand() % 3 + 2);
	}
	else if (monsterName == "Hobgoblin") {
		monsterHealth = monsterLevel + (rand() % 5 + 3);
	}
	else if (monsterName == "Ogre") {
		monsterHealth = monsterLevel + (rand() % 6 + 4);
	}
	else if (monsterName == "Troll") {
		monsterHealth = monsterLevel + (rand() % 7 + 5);
	}
	else if (monsterName == "Dragon") {
		monsterHealth = monsterLevel + (rand() % 8 + 6);
	}
}

void Monster::setAttack() {


	if (monsterName == "Goblin") {
		monsterAttack = monsterLevel + (rand() % 3 + 1);
	}
	else if (monsterName == "Hobgoblin") {
		monsterAttack = monsterLevel + (rand() % 4 + 2);
	}
	else if (monsterName == "Ogre") {
		monsterAttack = monsterLevel + (rand() % 5 + 3);
	}
	else if (monsterName == "Troll") {
		monsterAttack = monsterLevel + (rand() % 7 + 4);
	}
	else if (monsterName == "Dragon") {
		monsterAttack = monsterLevel + (rand() % 10 + 6);
	}
}

void Monster::setDefence() {

	if (monsterName == "Goblin") {
		monsterDefence = monsterLevel + (rand() % 2 + 1);
	}
	else if (monsterName == "Hobgoblin") {
		monsterDefence = monsterLevel + (rand() % 3 + 1);
	}
	else if (monsterName == "Ogre") {
		monsterDefence = monsterLevel + (rand() % 4 + 2);
	}
	else if (monsterName == "Troll") {
		monsterDefence = monsterLevel + (rand() % 5 + 2);
	}
	else if (monsterName == "Dragon") {
		monsterDefence = monsterLevel + (rand() % 12 + 6);
	}
}

void Monster::setDamage() {

	if (monsterName == "Goblin") {
		monsterDamage = monsterLevel;
	}
	else if (monsterName == "Hobgoblin") {
		monsterDamage = monsterLevel + (rand() % 2 + 1);
	}
	else if (monsterName == "Ogre") {
		monsterDamage = monsterLevel + (rand() % 3 + 1);
	}
	else if (monsterName == "Troll") {
		monsterDamage = monsterLevel + (rand() % 4 + 2);
	}
	else if (monsterName == "Dragon") { //claw damage
		monsterDamage = monsterDamage + (rand() % 6 + 4);
	}
}

void Monster::setLevel() {

	if (monsterName == "Goblin") {
		monsterLevel = 1;
	}
	else if (monsterName == "Hobgoblin") {
		monsterLevel = 2;
	}
	else if (monsterName == "Ogre") {
		monsterLevel = 3;
	}
	else if (monsterName == "Troll") {
		monsterLevel = 4;
	}
	else if (monsterName == "Dragon") {
		monsterLevel = 5;
	}
}




void Monster::updateHealth(int health) {
	if (health != 0) {
		monsterHealth += health;
	}
}



string Monster::getDetails() {
	// returns details of the monster as formatted string

	stringstream detailsOfMonster;

	detailsOfMonster << "--------------------------------------------\n";
	detailsOfMonster << " Monster Name: " << getName() << "\n";
	detailsOfMonster << " Monster Level: " << getLevel() << "\n";
	detailsOfMonster << " Monster Health: " << getHealth() << "\n";
	detailsOfMonster << " Monster Attack: " << getAttack() << "\n";
	detailsOfMonster << " Monster Defence: " << getDefence() << "\n";
	detailsOfMonster << " Monster Damage: " << getDamage() << "\n";
	detailsOfMonster << "--------------------------------------------\n";

	return detailsOfMonster.str();

}