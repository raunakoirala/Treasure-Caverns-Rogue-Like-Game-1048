/**************************************************
  Project: Assignment 4
  Author: Raunak Koirala
  Student No. 32509987

  Date Updated:31/10/2022
  Purpose: Manages Item Class

 **************************************************/

#include "Item.h"




Item::Item() {//constructor

	itemName = "Potion Flask";
	itemType = POTION;
	itemUses = 1;

}


Item::Item(string name, ItemType type, int uses) {//constructor

	setName(name);
	setType(type);
	setUses(uses);
}



Item::~Item() {//destructor

}



//accessor methods

string Item::getName() {
	return itemName;
}


ItemType Item::getType() {
	return itemType;
}


string Item::convertTypeToString() {

	switch (getType()) {

	case ARTEFACT:
		return "Artefact";

	case POTION:
		return "Potion";

	case WEAPON:
		return "Weapon";

	case ARMOUR:
		return "Armour";

	case ITEM:
		return "Item";

	default:
		return "No valid item type given";

	}
}


int Item::getUses() {
	return itemUses;
}



//mutator methods to set and update

void Item::setName(string name) {
	itemName = name;
}


void Item::setType(ItemType type) {
	itemType = type;
}


void Item::setUses(int uses) {
	itemUses = uses;
}

void Item::updateUses(int uses) {
	itemUses -= uses;
}



string Item::getDetails() {

	stringstream detailsOfItem;

	detailsOfItem << "------------------------------------------\n";
	detailsOfItem << " Item Name: " << getName() << "\n";
	detailsOfItem << " Item Type: " << convertTypeToString() << "\n";
	detailsOfItem << " Item Uses: " << getUses() << "\n";
	detailsOfItem << "------------------------------------------\n";

	return detailsOfItem.str();
}
