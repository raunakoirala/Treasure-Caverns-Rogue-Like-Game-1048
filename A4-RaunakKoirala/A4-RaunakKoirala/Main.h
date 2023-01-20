/**************************************************
  Project: Assignment 4
  Author: Raunak Koirala
  Student No. 32509987

  Date Updated:31/10/2022
  Purpose: Header definition file for Main

 **************************************************/

#ifndef Main_H
#define Main_H

#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

#include "Player.h"
#include "Item.h"
#include "Location.h"
#include "Monster.h"
#include "Dragon.h"

#include "Enums.h"

using namespace std;






//Dragon dragon;

vector<Location> map;
Player player;

void selectDifficulty();
void buyItems();
void changeDragonLocation();

void displayTextData(std::string filename);
char getCharInput();
string getInput();
int getNumber(int min);
string battleAction();
void generateLocations();
Player createPlayer();
void runMenu();
void pickItem(int number);
void pickArtefact(int number);
bool checkforBattle();
void displayExits();
void displayLocation();
void displayMenu();
void changePlayerLocation(Location loc);
Location getRoom(char direction, vector<string> exits, Location playerPosition);
void removeFuel();
void gameEndCheck();
void updateStats();
bool checkInput(char userChoice);

int main();


int fireCount = 0;
int swordPickup = 0;
int armourPickup = 0;
int axePickup = 0;
int chainmailPickup = 0;
int bootsPickup = 0;


skillLevel difficulty;
int turn;

#endif
