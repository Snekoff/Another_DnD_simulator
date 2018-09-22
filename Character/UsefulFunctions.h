#pragma once
#include <iostream>
#include <random>


#ifndef ANOTHER_DND_SIMULATOR_USEFULFUNCTIONS_H
#define ANOTHER_DND_SIMULATOR_USEFULFUNCTIONS_H

struct Existing_Types {
  int minHeight[11] = {6, 4, 6, 3, 3, 5, 5, 3, 5, 5, 5 };
  int maxHeight[11] = {6, 5, 6, 4, 4, 6, 6, 3, 6, 6, 6 };
  int minWeight[11] = {10};
  int maxWeight[11] = {140};
  int minAge[11] = {3};
  int maxAge[11] = {120};//
  std::string item[9] = {"equipment","potions","food","ammo_holder","shield","weapon","armor","ammo","usable"};
  int race_ability_bonus[39][6] =
      {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
  int experience_per_level[21] = {0,300,900,2700,6500,14000,23000,34000,48000,64000,85000,100000,120000,140000,165000,195000,225000,265000,305000,355000,120000002};
}; //

int Correctness_of_input(int a, int lowerlimit, int higherlimit);

int Random_Generator(int lowerlimit, int higherlimit);

int Health_Level_Up(int health_dice, int ConModifier, int maxhealth);
#endif //ANOTHER_DND_SIMULATOR_USEFULFUNCTIONS_H
