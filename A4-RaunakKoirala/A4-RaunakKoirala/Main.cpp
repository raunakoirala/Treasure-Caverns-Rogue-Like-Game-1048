/**************************************************
  Project: Assignment 4
  Author: Raunak Koirala
  Student No. 32509987

  Date Updated:31/10/2022
  Purpose: Manages main logic of game and temporarily stores all test files to check all functions work well

 **************************************************/

#include "Main.h"

void selectDifficulty() {//allows player to choose a difficulty (extra fucntionality) [2]

	std::cout << "Select a difficulty:" << endl;
	std::cout << "[R] Rookie" << endl;
	std::cout << "[A] Adventurer" << endl;
	std::cout << "[E] Expert" << endl;

	char input = 'X';

	while (input != 'R' || input != 'A' || input != 'E') {

		input = getCharInput();


		if (input == 'R') {
			difficulty = skillLevel::ROOKIE;
			break;
		}


		else if (input == 'A') {
			difficulty = skillLevel::ADVENTURER;
			break;
		}


		else if (input == 'E') {
			difficulty = skillLevel::EXPERT;
			break;
		}

		else {
			std::cout << "Please enter an appropriate difficulty" << endl;
		}


	}

	switch (difficulty) {
	case skillLevel::ROOKIE://Rookie

		std::cout << "Set Difficulty: ROOKIE" << endl;
		break;
	case skillLevel::ADVENTURER://Adventurer
		std::cout << "Set Difficulty: ADVENTURER" << endl;
		break;
	case skillLevel::EXPERT://Expert
		std::cout << "Set Difficulty: EXPERT" << endl;
		break;

	default:
		cout << "Choose a appropriate difficulty!" << endl;
	}
	std::system("pause");
	std::system("cls");
}


void buyItems() {//allows player to buy items and boosts before game (extra fucntionality) [4]

	int balance = 50;

	std::cout << "You have been given 50 gold to spend in the shop! You wont be able to keep this money so spend it all!" << endl;
	std::cout << "" << endl;
	std::cout << "Choose the items or boost you want to buy!" << endl;
	std::cout << "" << endl;
	std::cout << "[A] Boost of 5 health! (10 coins)" << endl;
	std::cout << "[B] Boost of 10 fuel in lantern! (10 coins)" << endl;
	std::cout << "[C] Boost of 1 provisons! (10 coins)" << endl;
	std::cout << " " << endl;




	char input = 'X';

	while ((input != 'A' || input != 'B' || input != 'C') && (balance >= 10)) {//ensures that choice is within these characters

		std::cout << " " << endl;
		std::cout << "Balance: " << balance << endl;
		std::cout << " " << endl;

		std::cout << "Enter a choice: " << endl;

		input = getCharInput();

		if (input == 'A' && balance >= 10) {

			std::cout << "You have gained 5 health " << endl;
			player.updateHealth(5);
			balance = balance - 10;
		}


		else if (input == 'B' && balance >= 10) {

			std::cout << "You have recieved 10 fuel extra in your lantern: " << endl;

			int uses = player.getInventory()[1]->getUses() + 10;

			player.removeItemFromInventory(1);

			player.addToInventory(new Item("Lantern", ITEM, uses), 1); //creates a new lantern item and puts it in the same index position, except with subtracted used from random value


			balance = balance - 10;
		}


		else if (input == 'C' && balance >= 10) {

			std::cout << "You have recieved 1 provision extra in your inventory" << endl;

			int uses = player.getInventory()[2]->getUses() + 1;

			player.removeItemFromInventory(2);

			player.addToInventory(new Item("Provison", ITEM, uses), 2);


			balance = balance - 10;
		}

		else if (input == 'A' || input == 'B' || input == 'C') {
			std::cout << "You dont have enough coins!" << endl;
		}

		else {
			std::cout << "Please enter a valid input!" << endl;
		}


	}


}

void changeDragonLocation() {//this is used to move the dragon to an adjacent room to the player every 10 turns [3]

	vector<string> exits = player.getLocation().convertVisibleExits();

	int locationID;

	std::string exitsString;
	for (std::vector<std::string>::const_iterator i = exits.begin(); i != exits.end(); ++i)
		exitsString += *i;

	if (exitsString.find("n") != string::npos) {
		Location location = getRoom(tolower('n'), exits, player.getLocation());
		locationID = getRoom(tolower('n'), exits, player.getLocation()).getID();
	}

	else if (exitsString.find("s") != string::npos) {
		Location location = getRoom(tolower('s'), exits, player.getLocation());
		locationID = getRoom(tolower('s'), exits, player.getLocation()).getID();
	}
	else {
		std::cout << "Couldn't move dragon!" << endl;
	}


	for (int i = 0; i < map.size(); i++) {
		if (map[i].getMonster()->getName() == "Dragon") {
			map[i].removeMonster();

			map[locationID].addMonster(new Monster("Dragon"));

			std::cout << "Dragon has moved to an adjacent room!";
		}


	}

}



void displayTextData(std::string filename) { //used to display multiple display screens, such as map, menu and more

	ifstream fileToRead(filename);

	if (fileToRead.is_open()) {
		string line = "";
		while (!fileToRead.eof()) {
			getline(fileToRead, line);
			std::cout << line << "\n";
		}
	}
	else {
		std::cout << "\n" + filename + " not found.\n";
	}
	fileToRead.close();

}


char getCharInput() { //used to get character input and convert it to uppercase (so user can enter both upper or lowercase), this is utilised by the main game when player is making decisions

	string userInput;

	while (!userInput.length() == 1) {
		getline(cin, userInput);
	}

	return std::toupper(userInput[0]);
}

string getInput() { //gets normal string input and returns it
	string userInput;
	std::cout << flush;
	while (!userInput.length()) {
		getline(cin, userInput);
	}

	return userInput;
}



int getNumber(int min) { //gets number as input, this is used to let player decide what items from inventory to remove
	double userInput = -1;
	bool valid = false;
	do
	{
		cin >> userInput;
		if (cin.good())
		{
			if (userInput > min) {
				valid = true;
			}
			else {
				valid = false;
			}
			valid = true;
		}

		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << "You can't get rid of that item!" << endl;
		}
	} while (!valid);

	return (userInput);
}


string battleAction() { //used to test battle action

	int playerLocationID = player.getLocation().getID(); //gets players id on the map

	Location playerLocation = map[playerLocationID];


	std::cout << player.getDetails() << endl; //show players stats

	int round = 1; //keeps track of the times player and monster hit each other


	while (player.getHealth() > 0 && playerLocation.getMonster()->getHealth() > 0) {

		std::cout << "" << endl;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		std::cout << "Round No: " << round << endl;
		std::cout << " " << endl;
		std::cout << "Player Health: " << player.getHealth() << "       " << "      Monster Health: " << playerLocation.getMonster()->getHealth() << endl;

		int playerAttack = player.getAttack() + rand() % 10 + 2; //attack + random value from 2 to 10
		int monsterAttack = playerLocation.getMonster()->getAttack() + rand() % 10 + 2; //attack + random value from 2 to 10


		std::cout << "Player attack + random: " << playerAttack << "       " << "     Monster attack + random: " << monsterAttack << endl; //show these values for player to see who has more attack for that round
		std::cout << " " << endl;


		if (playerAttack > monsterAttack) { //if player has greater attack for that round

			int damageInflicted = player.getDamage() - playerLocation.getMonster()->getDefence();

			if (damageInflicted == 0 || damageInflicted < 0) { //Needs to be added in the case when defence and damage of the player and monster are the same, resulting in infinite loop
				damageInflicted = 1;
			}

			std::cout << "Player attacks " << playerLocation.getMonster()->getName() << " for " << damageInflicted << " damage" << endl;

			playerLocation.getMonster()->updateHealth(0 - damageInflicted);

			if (playerLocation.getMonster()->getHealth() <= 0) {//checks if player has done enough damage for monster to be dead

				std::cout << " " << endl;
				std::cout << "Player has won" << endl;
				std::cout << " " << endl;
				system("pause");
				return "win";
			}
		}


		else if (playerAttack < monsterAttack) {

			if (playerLocation.getMonster()->getName() == "Dragon" && (rand() % 100 + 1) < 40 && fireCount == 0) { //40% chance to breathe fire, firecount is used to ensure fire attack can only be done once

				Dragon dragon = Dragon();

				int damageInflicted = dragon.getFireDamage() - player.getDefence();

				fireCount = fireCount + 1;

				if (damageInflicted == 0 || damageInflicted < 0) { //Needs to be added in the case when defence and damage of the player and monster are the same, resulting in infinite loop
					damageInflicted = 1;
				}

				dragon.performSpecialSkill(); //dragon breathes fire

				std::cout << std::to_string(damageInflicted) << " damage" << endl;

				player.updateHealth(0 - damageInflicted);

			}

			else {

				int damageInflicted = playerLocation.getMonster()->getDamage() - player.getDefence();

				if (damageInflicted == 0 || damageInflicted < 0) { //Needs to be added in the case when defence and damage of the player and monster are the same, resulting in infinite loop
					damageInflicted = 1;
				}

				std::cout << playerLocation.getMonster()->getName() << " attacks Player for " << damageInflicted << " damage" << endl;
				player.updateHealth(0 - damageInflicted);

			}


			if (player.getHealth() <= 0) { //checks if player is dead
				std::cout << " " << endl;
				std::cout << "Monster has won" << endl;
				std::cout << " " << endl;
				system("pause");
				return "loss";
			}
		}

		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		system("pause");
		round = round + 1;
	}


}


void generateLocations() { //uses the location files (name, description and exits), to takes all values and create location classes for them, which is then sotred in a vector map

	vector<string> locationNames;


	ifstream namesFile("locationNames.txt");
	if (namesFile.is_open()) {
		string line = "";
		while (!namesFile.eof()) {
			getline(namesFile, line);
			locationNames.push_back(line);
		}
	}
	else {
		std::cout << "" << endl;
		std::cout << "Names files not found!" << endl;
		std::cout << "" << endl;
	}

	namesFile.close();

	vector<string> locationDescriptions;

	ifstream descriptionFile("locationDescriptions.txt");
	if (descriptionFile.is_open()) {
		string line = "";
		while (!descriptionFile.eof()) {
			getline(descriptionFile, line);
			locationDescriptions.push_back(line);
		}
	}


	else {
		std::cout << "" << endl;
		std::cout << "Description files not found!" << endl;
		std::cout << "" << endl;
	}

	descriptionFile.close();

	vector<string> locationVisibleExits;
	ifstream exitsFile("locationExits.txt");
	if (exitsFile.is_open()) {
		string line = "";
		while (!exitsFile.eof()) {
			getline(exitsFile, line);
			locationVisibleExits.push_back(line);
		}
	}
	else {
		std::cout << "" << endl;
		std::cout << "Exits files not found!" << endl;
		std::cout << "" << endl;
	}

	exitsFile.close();

	for (int i = 0; i < locationNames.size(); i++) {//loop used to create location instances for each line and append to vector map
		Location location = Location(locationNames[i], locationDescriptions[i], locationVisibleExits[i], i);
		map.push_back(location);
	}
}


Player createPlayer() { //creates the player and returns it
	std::cout << "To begin you need to enter your name\n";

	std::cout.clear();
	cin.clear();
	string name = getInput();

	if (difficulty == skillLevel::ROOKIE) {
		player = Player(name);
		player.updateAttack(10);
		player.updateHealth(10);
		player.updateDefence(10);
	}

	else if (difficulty == skillLevel::ADVENTURER) {
		player = Player(name);
		player.updateAttack(5);
		player.updateHealth(5);
		player.updateDefence(5);
	}

	else {
		player = Player(name);
	}


	std::cout << "" << endl;
	std::cout << "Welcome " << player.getName() << "!" << endl;

	system("pause");

	return player;
}




void runMenu() { //displays the main menu 
	std::cout << "    " << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "    Welcome to Treasure Caverns" << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "" << std::endl;
	displayTextData("HowToPlay.txt"); //display the game objective and keybind info (this can be accessed later using H as well)
	std::cout << "" << std::endl;

	generateLocations(); //reads all text files and creates the locations to add to vector map

	player.setLocation(map[0]); //sets players lcoation at the entrance at the bottom of the map

	player.updateInventory(new Item("Map", ITEM, 999)); //adds map to player inventory

	player.updateInventory(new Item("Lantern", ITEM, 120)); //adds lantern to player inventory

	player.updateInventory(new Item("Provisons", ITEM, rand() % 4 + 2)); //adds provisons to the players inventory

	player.updateInventory(new Item("Sword", WEAPON, 1)); //add sword to player inventory



	int randomCaveID;


	randomCaveID = rand() % 19 + 1;
	map[randomCaveID].addItem(new Item("Gems", ITEM, rand() % 3 + 1));//add gems at random location

	randomCaveID = rand() % 19 + 1;
	map[randomCaveID].addItem(new Item("Gold", ITEM, rand() % 12 + 6));//add gold at random location


	randomCaveID = rand() % 19 + 1;
	map[randomCaveID].addItem(new Item("Leather Armour", ARMOUR, 1));//add armour at random location


	randomCaveID = rand() % 19 + 1;
	map[randomCaveID].addMonster(new Monster("Goblin"));//add goblin at random location

	randomCaveID = rand() % 19 + 1;
	map[randomCaveID].addMonster(new Monster("Hobgoblin"));//add hobgoblin at random location

	randomCaveID = rand() % 19 + 1;
	map[randomCaveID].addMonster(new Monster("Ogre"));//add ogre at random location

	randomCaveID = rand() % 19 + 1;
	map[randomCaveID].addMonster(new Monster("Troll"));//add troll at random location

	randomCaveID = rand() % 19 + 1;
	map[randomCaveID].addMonster(new Monster("Dragon"));//add dragon at random location


}

void pickItem(int number) {//used to randomly select an item that monster has


	if (number == 1) {
		map[player.getLocation().getID()].addItem(new Item("Provisions", ITEM, rand() % 4 + 2));

	}
	else if (number == 2) {
		map[player.getLocation().getID()].addItem(new Item("Gold", ITEM, rand() % 12 + 6));
	}

	else if (number == 3) {
		map[player.getLocation().getID()].addItem(new Item("Gems", ITEM, rand() % 3 + 1));
	}

}

void pickArtefact(int number) {//used to randomly select an artefact that monster has

	if (number == 1) {
		map[player.getLocation().getID()].addItem(new Item("Krangs Battle Axe", ARTEFACT, 1));
	}

	else if (number == 2) {
		map[player.getLocation().getID()].addItem(new Item("Krangs Chainmail", ARTEFACT, 1));
	}

	else if (number == 3) {
		map[player.getLocation().getID()].addItem(new Item("Boots of Speed", ARTEFACT, 1));
	}

	else if (number == 3) {
		map[player.getLocation().getID()].addItem(new Item("Elixir Maxima", ARTEFACT, 1));
	}
	else {
		map[player.getLocation().getID()].addItem(new Item("Elixir Maxima", ARTEFACT, 1));
	}

}

bool checkforBattle() { //checks if player location also has monster and gives them choices to flee or attack

	bool val = false; //for return value, stays as false if no monster in cave

	int playerLocationID = player.getLocation().getID(); //gets players location id which is used in map vector to find location



	bool monsterInCave = map[playerLocationID].containsMonster(); //used to check if monster in cave



	if (monsterInCave == true) {

		val = true; //there is a monster in the cave so its will return true at the end


		if (map[playerLocationID].getMonster()->getName() == "Dragon") {//checks if monster is dragon

			std::cout << " " << std::endl;
			std::cout << "You have found the dragon!" << std::endl;
			std::cout << " " << std::endl;

			if (player.convertInventoryToString().find("Krangs Battle") != string::npos && player.convertInventoryToString().find("Boots") != string::npos) {//checks for axe and boots which are required to challenge dragon
				std::cout << "What will you do? (A to Attack, F to Flee)" << endl;
			}

			else {
				std::cout << "You must posses both Krangs Battle Axe and Boots of Speed in order to challenge the dragon. Retreive these items and search for the dragon again. For now you must flee..." << endl;//have to flee
				std::cout << "Press A or F to Flee" << endl;
				std::cout << " " << endl;
				monsterInCave = false;

			}


		}


		else {
			std::cout << " " << std::endl;
			std::cout << "However, there seems to be a " << map[playerLocationID].getMonster()->getName() << " in this cave, what will you do? (A to attack, F to flee)" << std::endl;//shows player what monster is in the location
		}

		string decision = getInput(); //gets response from player
		string result;

		if (decision == "A" && monsterInCave == true) {
			result = battleAction();

			if (map[playerLocationID].containsItem()) {//This is so the player doesn't miss out on the artifact
				map[playerLocationID].removeItem();
			}

			string name = map[playerLocationID].getMonster()->getName();

			int randomValue = rand() % 100 + 1;

			if (result == "win") { //if player has won
				if (name == "Goblin" && randomValue < 40) { //40% chance goblin dropped random item
					pickItem(rand() % 3 + 1);
					std::cout << map[playerLocationID].getMonster()->getName() << " dropped an item";
				}
				if (name == "Hobgoblin" && randomValue < 50) { //40% chance goblin dropped random item
					pickItem(rand() % 3 + 1);
					std::cout << map[playerLocationID].getMonster()->getName() << " dropped an item";
				}
				if (name == "Ogre" && randomValue < 60) { //40% chance goblin dropped random artefact
					pickArtefact(rand() % 4 + 1);
					std::cout << map[playerLocationID].getMonster()->getName() << " dropped an artefact";
				}
				if (name == "Troll" && randomValue < 70) { //40% chance goblin dropped random artefact
					pickArtefact(rand() % 4 + 1);
					std::cout << map[playerLocationID].getMonster()->getName() << " dropped an artefact";
				}
				if (name == "Dragon") { //40% chance goblin dropped random artefact
					pickArtefact(rand() % 4 + 1);
					std::cout << map[playerLocationID].getMonster()->getName() << " dropped an artefact";
				}

				std::cout << " " << endl;


				map[playerLocationID].removeMonster();//removes monster as it is dead
			}

		}

		else {
			result = "fled";


			if (map[playerLocationID].getMonster()->getName() != "Dragon") {

				std::cout << "You flee the battle however take " << std::to_string(map[playerLocationID].getMonster()->getDamage()) << " damage from the " << map[playerLocationID].getMonster()->getName() << endl;
				std::cout << " " << endl;
				player.updateHealth(0 - map[playerLocationID].getMonster()->getDamage());//player still takes damage when fleeing equivalent to monster damage
			}
			else {
				int damage = rand() % 6 + 4;
				std::cout << "You flee the battle however take " << std::to_string(damage) << " damage from the " << map[playerLocationID].getMonster()->getName() << endl;
				std::cout << " " << endl;
				player.updateHealth(0 - damage);//player still takes damage when fleeing equivalent to monster damage
			}

			system("pause");



			map[rand() % 19 + 0].addMonster(map[playerLocationID].getMonster());//add monster to another spot on the map
			map[playerLocationID].removeMonster(); // remove monster from that spot

		}
	}

	else {
		std::cout << "" << endl;
	}

	return val;


}


void displayExits() { //shows available exits taht player has

	vector<string> exits = player.getLocation().convertVisibleExits();

	for (int i = 0; i < exits.size(); i++) { //loops over vector, converted to string, takes the character of the exit and displays value to player

		std::cout << "  {";
		std::cout << (char)std::toupper(exits[i][0]);
		std::cout << "}";

	}
}


void displayLocation() { //shows location name, description and if there are any items at the lcoation

	int playerLocationID = player.getLocation().getID();

	bool itemInCave = map[playerLocationID].containsItem(); //checks if location has an item

	std::cout << "You have entered " << map[playerLocationID].getName() << " " << map[playerLocationID].getID() << endl;
	std::cout << "" + map[playerLocationID].getDescription() << endl;
	std::cout << " " << endl;
	std::cout << "-> There are a couple of directions you can go." << endl;

	displayExits(); //shows exits available
	std::cout << " " << endl;



	if (itemInCave == true) { //if location has an item

		std::cout << " " << endl;
		std::cout << "-> There is " << map[playerLocationID].getItem()->getName() << " on the ground" << endl;

	}

}


void displayMenu() { //dispalys the main game title and player stats and inventory

	std::cout << "    " << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "         Treasure Caverns" << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "    " << std::endl;
	std::cout << "Player stats:" << std::endl;
	std::cout << player.getDetails() << std::endl;


}

void changePlayerLocation(Location loc) { //changes players location, used when they travel to another cave
	player.setLocation(loc);
}



Location getRoom(char direction, vector<string> exits, Location playerPosition) { //gets direction based on visible exits


	for (int i = 0; i < exits.size(); i++) { //lops visible exits

		if (exits[i].find(direction) != string::npos) {//if exit in list
			string slice = exits[i].substr(1);
			Location location = map[stoi(slice)];//slices to get number and set player ocation

			return location;
		}
	}

	std::cout << "You cannot travel in that direction";
	return playerPosition;

}


void removeFuel() { //removes 2 to 5 fuel, used when player moves around or examines for items

	std::cout << " " << endl;

	int anotherRandom = rand() % 5 + 2; //2-5 oil is removed
	int uses = player.getInventory()[1]->getUses() - anotherRandom;


	player.removeItemFromInventory(1); //removes that lantern item
	player.addToInventory(new Item("Lantern", ITEM, uses), 1); //creates a new lantern item and puts it in the same index position, except with subtracted used from random value

	std::cout << std::to_string(anotherRandom) << " oil has been used from your lantern" << endl; //dispalys how much fuel has been used to the user
	std::cout << " " << endl;

}

void gameEndCheck() { //checks if game has ended, win or lose, this is checked in the main loop every time before player is able to input their action

	int uses = player.getInventory()[1]->getUses();

	if (uses <= 0) { //checks if lantern uses is equal or less than 0
		std::cout << " " << endl;
		std::cout << "You have ran out of fuel! Darkness consumed you! Game over" << endl;
		exit(0);

	}

	int health = player.getHealth();

	if (health <= 0) { //cheks if players health is equal or less than 0
		std::cout << " " << endl;
		std::cout << "You have ran out of health! Game over" << endl;
		exit(0);
	}

	int artefacts = 0; //counts the number of artefacts

	string inventory = player.convertInventoryToString();

	if (inventory.find("Krangs Battle") != string::npos) {
		artefacts = artefacts + 1;
	}

	if (inventory.find("Krangs Chainmail") != string::npos) {
		artefacts = artefacts + 1;
	}

	if (inventory.find("Boots") != string::npos) {
		artefacts = artefacts + 1;
	}

	if (inventory.find("Elixir") != string::npos) {
		artefacts = artefacts + 1;
	}

	if (inventory.find("Spell Tome") != string::npos) {
		artefacts = artefacts + 1;
	}


	if (player.getLocation().getID() == 0 && artefacts == 5) { //checks if player is back at the entrance and if they have all 5 artefacts, if so they win the game
		std::cout << "YOU HAVE WON THE GAME!" << endl;
		exit(0);
	}



}

void updateStats() {

	string inventory = player.convertInventoryToString(); //converts inventory to string to make it easier to find items


	if (inventory.find("Sword") != string::npos && swordPickup == 0) {//ensures stats arent being updated on every loop where item is in inventory

		player.updateAttack(2);

		swordPickup = 1;

	}


	if (inventory.find("Leather Armour") != string::npos && armourPickup == 0) {

		player.updateDefence(4);

		armourPickup = 1;

	}


	if (inventory.find("Krangs Battle") != string::npos && axePickup == 0) {

		player.updateDamage(8);

		axePickup = 1;

	}


	if (inventory.find("Krangs Chainmail") != string::npos && chainmailPickup == 0) {

		player.updateDefence(12);

		chainmailPickup = 1;

	}


	if (inventory.find("Boots of Speed") != string::npos && bootsPickup == 0) {

		player.updateDefence(6);

		bootsPickup = 1;
	}


}




bool checkInput(char userChoice) {//used to check for valid input


	if (userChoice == 'X') { //player wants to examine for items

		int playerLocationID = player.getLocation().getID();

		bool monsterInCave = map[playerLocationID].containsMonster();

		bool itemInCave = map[playerLocationID].containsItem();

		if (monsterInCave == false && itemInCave == false) {

			int randomValue = rand() % 100 + 1;

			if (randomValue < 30) {

				pickItem(rand() % 3 + 2); //picks gold or gems with 30% chance

				std::cout << "You find a " << map[playerLocationID].getItem()->getName() << endl;

			}

			else if (randomValue < 20) { //20% chance to pick item
				pickItem(1);

				std::cout << "You find a " << map[playerLocationID].getItem()->getName() << endl;
			}

		}
		else if (monsterInCave = true) { //cant examine cave if monster in the cave, must first flee or attack
			std::cout << "You cannot search this cave!" << endl;
		}

		else if (itemInCave = true) { //cant examine cave if item already in the cave
			std::cout << "You cannot search this cave!" << endl;
		}

		removeFuel();

		system("pause");
	}


	else if (userChoice == 'N') { //player wants to move north

		vector<string> exits = player.getLocation().convertVisibleExits();
		Location location = getRoom(tolower(userChoice), exits, player.getLocation());

		changePlayerLocation(location);

		removeFuel(); //removes fuel after moving in that direction

		system("pause");
	}

	else if (userChoice == 'S') { //if player wants to move south

		vector<string> exits = player.getLocation().convertVisibleExits();
		Location location = getRoom(tolower(userChoice), exits, player.getLocation());

		changePlayerLocation(location);

		removeFuel(); //removes fuel after moving in that direction

		system("pause");
	}

	else if (userChoice == 'E') { //if player wants to move east

		vector<string> exits = player.getLocation().convertVisibleExits();
		Location location = getRoom(tolower(userChoice), exits, player.getLocation());

		changePlayerLocation(location);

		removeFuel(); //removes fuel after moving in that direction

		system("pause");
	}

	else if (userChoice == 'W') { //if player wants to move west

		vector<string> exits = player.getLocation().convertVisibleExits();
		Location location = getRoom(tolower(userChoice), exits, player.getLocation());

		changePlayerLocation(location);

		removeFuel(); //removes fuel after moving in that direction

		system("pause");
	}
	else if (userChoice == 'P') { //if player wants to consume a provision or a potion

		string inventory = player.convertInventoryToString();

		if (inventory.find("Provison") != string::npos && inventory.find("Provison (0)") == string::npos) {
			player.updateHealth(rand() % 10 + 5);

			int uses = player.getInventory()[2]->getUses() - 1;

			player.removeItemFromInventory(2);
			player.addToInventory(new Item("Provison", ITEM, uses), 2);

			std::cout << " " << endl;
			std::cout << "You have consumed a provison" << endl;
		}

		else {
			std::cout << " " << endl;
			std::cout << "You don't have any provisons or potions!" << endl;
		}

		system("pause");
	}
	else if (userChoice == 'T') { //player wants to take item from location

		int playerLocationID = player.getLocation().getID();

		bool itemInCave = map[playerLocationID].containsItem();

		if (itemInCave == true) { //checks if there is an item in the cave

			player.updateInventory(new Item(map[playerLocationID].getItem()->getName(), map[playerLocationID].getItem()->getType(), map[playerLocationID].getItem()->getUses()));//takes item
			std::cout << "You picked up " << map[playerLocationID].getItem()->getName() << endl;
			map[playerLocationID].removeItem();//removes item from location
		}
		else {//no item at location
			std::cout << "No items here to pickup" << endl;
		}

		system("pause");
	}

	else if (userChoice == 'D') {//player wants to drop item 

		int choice;

		std::cout << "What item would you like to drop? Enter number:" << endl; //asks user for numebr so that inventory item can be doped
		choice = getNumber(2);

		if (choice <= 3) { //essentials like map, lantern and provisons cannot be dropped, hwoever all else can
			std::cout << "You need this item!" << endl;
		}

		else if (choice > player.getInventory().size()) {
			std::cout << "You don't have an item in that inventory slot!" << endl;
		}

		else {
			cout << "You dropped " << player.getInventory()[choice - 1]->getName() << " from your inventory " << endl;
			player.removeItemFromInventory(choice - 1);//removes item from inventory, (-1 as the vector starts at 0 however list starts at 1)

		}


		system("pause");
	}

	else if (userChoice == 'M') {//player wishes to view the map
		displayTextData("map.txt");//display map and pause for player to see and skip whenever
		system("pause");
	}

	else if (userChoice == 'H') {//player needs help
		displayTextData("HowToPlay.txt");//display objective and keybinds for player
		system("pause");
	}

	else if (userChoice == 'Q') {//player wishes to quit

	}
	else {
		std::cout << "    " << std::endl;
		std::cout << "Please enter a valid command";
		std::cout << " ";
	}


	return userChoice != 'Q' ? true : false; //if player choice is Q returns false

};



int main() {

	srand(time(NULL));


	bool runProgram = true;//false when player enters Q, starts as true

	selectDifficulty();//allows player to choose difficulty

	player = createPlayer(); //creates the palyer

	system("cls");


	runMenu();//initialises and sets up game using many functions, locations, monsters and items are all setup and player is informed about the game

	buyItems();

	system("pause");

	while ((runProgram)) { //while player doesn't enter Q

		updateStats();

		displayMenu();

		displayLocation();

		if (checkforBattle() == false) { //if there is a monster in the cave, player must first decide to attack or flee before all other actions
			std::cout << "Enter a command below (type 'H' for help): " << endl;
			std::cout << " " << endl;

			runProgram = checkInput(getCharInput());//false if Q
		}
		else {

		}

		turn = turn + 1;


		gameEndCheck(); //this ensures player hasn't won or has lost

	}

	std::cout << "" << std::endl;
	std::cout << "Thank you for testing the game" << std::endl;//end
	system("pause");

	return 0;
};


