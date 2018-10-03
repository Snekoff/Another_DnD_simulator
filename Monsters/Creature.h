//
// Created by Oleg on 03.10.2018.
//

#pragma once

#ifndef ANOTHER_DND_SIMULATOR_CREATURE_H
#define ANOTHER_DND_SIMULATOR_CREATURE_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include "../Inventory(Item)/Item.h"
#include "../Inventory(Item)/Items_Factory.h"

using namespace std;

const int kData_size = 71;
const int kMoney_types = 5;
const int kEquip_places = 10;
const int kAbility_Minimum_Score = 10;
const int kAbility_Maximum_Score = 20;
const int kAbility_Starting_Maximum = 16;
const int kSkills_b_shift = 40;
const int kParameter_b_shift = 37;
const int kClassType_get_bool_shift = 51;
const int kBarbarian_Unarmored_Defence = 10;
const int kWealth_Set_parameters = 3;
const int kDice_Minimum_value = 1;
const int kCoordinates_NUM = 3;

class Creature {
 protected:
  int sex; //0 - female,1 - male, 3 - Futanari, 4 - creature
  int experience, level;
  int health, maxhealth;
  int health_dice;
  int Str, Dex, Con, Int, Wis, Cha;//13
  int StrModifier, DexModifier, ConModifier, IntModifier, WisModifier, ChaModifier;
  int armor_class;
  int deathsaves_s, deathsaves_f;//success/failure
  int passive_perception, proficiency;
  bool advantage, disadvantage;
  bool perception_advantage;
  bool perception_disadvantage;//20
  int *skills;
  /*acrobatics 0,animalHandling 1,arcana 2,athletics 3,deception 4,
history 5,insight 6,intimidation 7,investigation 8,medicine 9,
nature 10,perception 11,performance 12,persuasion 13,religion 14,
sleightOfHand 15,stealth 16,survival 17*/
  bool *skills_b;//38
  int money[kMoney_types]; // copper, silver, gold, platinum, Total money(in copper equivalent)
  vector<Item *> inventory;
  map<std::string, Item *> items_map;
  vector<Item *> Equipped;
  int state;
  /* 0.fine, 1.blinded, 2.charmed, 3.deafened, 4.frightened, 5.grappled, 6.incapacitated, 7.invisible, 8.petrified,
   * 9.poisoned, 10.prone, 11.restrained, 12.stunned, 13.unconscious, 14.dead, 15.disease 16. ??*/
  int party;
  int Coordinates[kCoordinates_NUM];
};

#endif //ANOTHER_DND_SIMULATOR_CREATURE_H

