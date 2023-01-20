/**************************************************
  Project: Assignment 4
  Author: Raunak Koirala
  Student No. 32509987

  Date Updated:31/10/2022
  Purpose: Header definition file for Item

 **************************************************/

#ifndef Item_H
#define Item_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Enums.h"

using namespace std;


class Item {

private:
	string itemName;
	ItemType itemType;
	int itemUses;
	int itemAmount;

	//vector<Item> specialEffects;


public:

	Item();

	Item(string name, ItemType type, int uses);


	~Item();//destructor


	// accessor methods
	string getName();
	ItemType getType();
	string convertTypeToString();
	int getUses();
	string getDetails();

	//string getLocation(Location location);

	// mutator methods
	void setName(string name);
	void setType(ItemType type);
	void setUses(int uses);
	void updateUses(int uses);


};



#endif
