/**************************************************
  Project: Assignment 4
  Author: Raunak Koirala
  Student No. 32509987

  Date Updated:31/10/2022
  Purpose: Header definition file for Dragon

 **************************************************/

#ifndef Dragon_H
#define Dragon_H

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iostream>

#include "Monster.h"
#include "Player.h"
#include "Enums.h"

using namespace std;



class Dragon : public Monster {

private:

	int fireDamage;

public:

	Dragon();//constructor
	~Dragon();//destructor

	//accessors
	int getFireDamage();

	//mutators
	void setFireDamage();

	void performSpecialSkill();
};

#endif



