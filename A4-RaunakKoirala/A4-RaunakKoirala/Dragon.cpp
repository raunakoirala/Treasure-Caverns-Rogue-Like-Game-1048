/**************************************************
  Project: Assignment 4
  Author: Raunak Koirala
  Student No. 32509987

  Date Updated:31/10/2022
  Purpose: Manages Dragon Class

 **************************************************/

#include "Dragon.h"


 //constructor
Dragon::Dragon() {

	setFireDamage();

}


//destructor
Dragon::~Dragon() {
}


int Dragon::getFireDamage() {
	return fireDamage;
}

//used to perfrom skill of breathign fire during combat
void performSpecialSkill() {

} //to be implemented


//mutators for random values


void Dragon::setFireDamage() {

	fireDamage = (rand() % 3 + 2);

}

//action that Dragon can do (uses fire damage)
void Dragon::performSpecialSkill() {

	cout << "The dragon breathes fire on you inflicting ";
}




