/**************************************************
  Project: Assignment 4
  Author: Raunak Koirala
  Student No. 32509987

  Date Updated:31/10/2022
  Purpose: Header definition file for Monster

 **************************************************/

#ifndef Monster_H
#define Monster_H

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iostream>


#include "Item.h"
#include "Enums.h"


using namespace std;


class Monster {


private:
	string monsterName;
	int monsterHealth;
	int monsterAttack;
	int monsterDefence;
	int monsterDamage;
	int monsterLevel;



public:


	Monster();
	Monster(string name);
	~Monster();//destructor


	//accessor methods
	string getName();
	int getHealth();
	int getAttack();
	int getDefence();
	int getDamage();
	int getLevel();



	string getDetails();


	//mutator methods to set values
	void setName(string name);
	void setHealth();
	void setAttack();
	void setDefence();
	void setDamage();
	void setLevel();

	void updateHealth(int health);//mutator method to update values (only health needs to be updated for monsters)




};



#endif
