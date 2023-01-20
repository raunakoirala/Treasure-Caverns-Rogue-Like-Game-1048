/**************************************************
  Project: Assignment 4
  Author: Raunak Koirala
  Student No. 32509987

  Date Updated:31/10/2022
  Purpose: Header definition file for Location

 **************************************************/

#ifndef Location_H
#define Location_H

#include <iostream>
#include <sstream>
#include <vector>
#include <limits>
#include <string>

#include "Enums.h"
#include "Item.h"
#include "Monster.h"



using namespace std;

class Location {


private:

	string locationName;
	string locationDescription;
	string visibleExits;

	bool hasItem;
	bool hasMonster;

	Item* item;
	Monster* monster;

	int mapID;


public:
	//constructor
	Location();
	Location(string name, string description, string exits);
	Location(string name, string description, string exits, int id);

	//destructor
	~Location();


	//accessor methods
	string getName();
	string getDescription();
	string getVisibleExits();
	int getID();
	vector<string> convertVisibleExits();
	bool containsItem();
	bool containsMonster();

	Item* getItem();
	Monster* getMonster();


	string getDetails();

	//mutator methods
	void setName(string name);
	void setDescription(string description);
	void setVisibleExits(string directions);

	void removeItem();
	void addItem(Item* item);

	void removeMonster();
	void addMonster(Monster* monster);



};



#endif