/**************************************************
  Project: Assignment 4
  Author: Raunak Koirala
  Student No. 32509987

  Date Updated:31/10/2022
  Purpose: Header definition file for Player

 **************************************************/

#ifndef Player_H
#define Player_H

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iostream>



#include "Item.h"
#include "Location.h"

#include "Enums.h"


using namespace std;


class Player {


private:
	string playerName;
	int playerHealth;
	int playerAttack;
	int playerDefence;
	int playerDamage;
	int playerLuck;
	Location playerLocation;

	string strPlayerInventory;

	vector<Item*> playerInventory;


public:


	Player();
	Player(string name);
	Player(string name, Location location);
	~Player();//destructor


	//accessor methods
	string getName();
	int getHealth();
	int getAttack();
	int getDefence();
	int getDamage();
	int getLuck();
	Location getLocation();

	vector<Item*> getInventory();

	string convertInventoryToString();

	string getDetails();



	//mutator methods to set values
	void setHealth();
	void setAttack();
	void setDefence();
	void setDamage();
	void setLuck();
	void setLocation(Location location);

	//mutator methods to update values
	void updateHealth(int health);
	void updateAttack(int attack);
	void updateDefence(int defence);
	void updateDamage(int damage);
	void updateLuck(int luck);

	void addToInventory(Item* it, int index);

	void updateInventory(Item* it);
	void removeItemFromInventory(int index);

};



#endif