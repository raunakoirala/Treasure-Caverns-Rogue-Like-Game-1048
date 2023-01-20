/**************************************************
  Project: Assignment 4
  Author: Raunak Koirala
  Student No. 32509987

  Date Updated:31/10/2022
  Purpose: Manages Player Class

 **************************************************/

#include "Player.h"


 //constructor methods

Player::Player() {

	playerName = "Raunak";


	playerInventory = {};

	setHealth();
	setAttack();
	setDefence();
	setDamage();
	setLuck();

}

Player::Player(string name) {

	playerName = name;


	playerInventory = {};

	setHealth();
	setAttack();
	setDefence();
	setDamage();
	setLuck();


}

Player::Player(string name, Location location) {

	playerName = name;


	playerInventory = {};

	setHealth();
	setAttack();
	setDefence();
	setDamage();
	setLuck();
	setLocation(location);


}


Player::~Player() {//destructor method

}

//accessor methods

string Player::getName() {
	return playerName;
}

int Player::getHealth() {
	return playerHealth;
}

int Player::getAttack() {
	return playerAttack;
}

int Player::getDefence() {
	return playerDefence;
}

int Player::getDamage() {
	return playerDamage;
}

int Player::getLuck() {
	return playerLuck;
}

//gets raw vector inventory for any index manipulation of inventory
vector<Item*> Player::getInventory() {
	return playerInventory;
}





//converts vector to string for getDetails function and to easily search for items within it
string Player::convertInventoryToString()
{
	stringstream inventoryDetails;
	inventoryDetails << "Inventory:\n";
	for (int i = 0; i < playerInventory.size(); i++) {
		inventoryDetails << i + 1 << ". " << playerInventory[i]->getName() << " (" << playerInventory[i]->getUses() << ")" << endl;
	}
	if (playerInventory.size() == 0) {
		cout << "\t...is empty" << endl;
	}

	inventoryDetails << "\n";

	return inventoryDetails.str();
}


Location Player::getLocation() {
	return playerLocation;
}


//mutator methods to set random initial values

void Player::setHealth() {

	playerHealth = (rand() % 12 + 4) + 12;
}

void Player::setAttack() {
	playerAttack = (playerHealth / 6);
}

void Player::setDefence() {
	playerDefence = (playerAttack / 2);
}

void Player::setDamage() {
	playerDamage = (playerAttack / 3) + 2;
}

void Player::setLuck() {

	playerLuck = (rand() % 6 + 2) + 6;
}

void Player::setLocation(Location location) {
	playerLocation = location;
}


//mutator methods to update the values
void Player::updateHealth(int health) {
	playerHealth += health;
}

void Player::updateAttack(int attack) {
	playerAttack += attack;
}

void Player::updateDefence(int defence) {
	playerDefence += defence;
}

void Player::updateDamage(int damage) {
	playerDamage += damage;
}

void Player::updateLuck(int luck) {
	playerLuck += luck;
}

void Player::updateInventory(Item* it) {
	playerInventory.push_back(it);
}

void Player::addToInventory(Item* it, int index) {
	playerInventory.insert(playerInventory.begin() + index, it);
}

void Player::removeItemFromInventory(int index) {
	delete playerInventory[index];
	playerInventory[index] = nullptr;
	playerInventory.erase(playerInventory.begin() + index);
}




string Player::getDetails() {
	// returns details of the player as formatted string

	stringstream detailsOfPlayer;

	detailsOfPlayer << "--------------------------------------------\n";
	detailsOfPlayer << " Player: " << getName() << "\n";
	detailsOfPlayer << " Health: " << getHealth() << "\n";
	detailsOfPlayer << " Attack: " << getAttack() << "\n";
	detailsOfPlayer << " Defence: " << getDefence() << "\n";
	detailsOfPlayer << " Damage: " << getDamage() << "\n";
	detailsOfPlayer << " Luck: " << getLuck() << "\n";
	detailsOfPlayer << "" << convertInventoryToString() << "\n";
	detailsOfPlayer << "--------------------------------------------\n";

	return detailsOfPlayer.str();
}