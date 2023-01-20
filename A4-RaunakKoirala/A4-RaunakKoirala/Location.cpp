/**************************************************
  Project: Assignment 4
  Author: Raunak Koirala
  Student No. 32509987

  Date Updated:31/10/2022
  Purpose: Manages Location Class

 **************************************************/

#include "Location.h"


 // constructor

Location::Location() {

	locationName = "";
	locationDescription = "";
	visibleExits = "NSEW";

}


Location::Location(string name, string description, string exits) {

	setName(name);
	setDescription(description);
	visibleExits = exits;

	monster = nullptr;
	hasMonster = false;
	item = nullptr;
	hasItem = false;

}

Location::Location(string name, string description, string exits, int id) {

	setName(name);
	setDescription(description);
	visibleExits = exits;

	monster = nullptr;
	hasMonster = false;
	item = nullptr;
	hasItem = false;

	mapID = id;
}

//destructor

Location::~Location() {

}



//accessor methods


string Location::getName() {
	return locationName;
}


string Location::getDescription() {
	return locationDescription;
}


string Location::getVisibleExits() {
	return visibleExits;
}

int Location::getID() {
	return mapID;
}


//gets Item from Location
Item* Location::getItem() {
	return item;
}


//checks if Location has an Item
bool Location::containsItem() {
	return hasItem;
}

//gets Monster from Location
Monster* Location::getMonster() {
	return monster;
}

//checks for Monster in Location
bool Location::containsMonster() {
	return hasMonster;
}

//converts exits from string to vector
vector<string> Location::convertVisibleExits() {
	vector<string> vector;
	istringstream ss(visibleExits);
	string token;

	while (getline(ss, token, ',')) {
		string exit;

		for (int i = 0; i < token.size(); i++) {
			exit += std::tolower(token[i]);
		}

		vector.push_back(exit);
	}

	return vector;
}




//mutator methods

void Location::setName(string name) {
	locationName = name;
}


void Location::setDescription(string description) {
	locationDescription = description;
}

void Location::setVisibleExits(string exits) {
	visibleExits = exits;
}

//adds the item to Location
void Location::addItem(Item* it) {
	item = it;
	hasItem = true;
}

//removes the item from Location and resets item value
void Location::removeItem() {
	if (containsItem()) {
		hasItem = false;
		delete item;
		item = nullptr;
	}
	else {
		cout << "No item at location" << endl;
	}
}

//adds the monster to Location
void Location::addMonster(Monster* mons) {
	monster = mons;
	hasMonster = true;
}

//removes the monster from Location and resets item value
void Location::removeMonster() {
	if (containsMonster()) {
		hasMonster = false;
		delete monster;
		monster = nullptr;
	}
	else {
		cout << "No monster at location" << endl;
	}
}

string Location::getDetails() {
	//gets details of the location as formatted string

	stringstream locationDetails;

	locationDetails << "--------------------------------------------------------------------------------\n";
	locationDetails << " Location Name: " << getName() << "\n";
	locationDetails << " Location Description: " << getDescription() << "\n";
	locationDetails << " Location Exits: " << getVisibleExits() << "\n";
	locationDetails << "--------------------------------------------------------------------------------\n";

	return locationDetails.str();
}

