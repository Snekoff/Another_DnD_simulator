#pragma once
//#include "UsefulFunctions.cpp"
#include <iostream>

struct Existing_Types{
  int minHeight[11] ;
int maxHeight[11] ;
int minWeight[11] ;
int maxWeight[11] ;
int minAge[11] ;
int maxAge[11] ;//
std::string item[9] ;
int race_ability_bonus[39][6] ;
int experience_per_level[10];
};

int Correctness_of_input(int , int , int );

int Random_Generator(int lowerlimit, int higherlimit);

int Health_Level_Up(int health_dice, int ConModifier, int maxhealth);

#ifndef ANOTHER_DND_SIMULATOR_USEFULFUNCTIONS_H
#define ANOTHER_DND_SIMULATOR_USEFULFUNCTIONS_H

#endif //ANOTHER_DND_SIMULATOR_USEFULFUNCTIONS_H
