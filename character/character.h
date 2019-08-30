//
// MIT License
// Copyright (c) 2019 Snekoff. All rights reserved.
//
#pragma once

#include "../json_parse_by_nlohmann/json.hpp"

#include "common_functions.h"
#include "../monsters/creature.h"
#include "class.h"
#include "race.h"


#ifndef ANOTHER_DND_SIMULATOR_CHARACTER_H
#define ANOTHER_DND_SIMULATOR_CHARACTER_H

#endif //ANOTHER_DND_SIMULATOR_CHARACTER_H

const int kGet_Skills_shift = 108;
using namespace std;

class Character : public Creature {
 private:
  Race *race_of_character;
  Class class_type;  //TODO: rework
  int storyline_i;
  Existing_Types E;
  int exhaustion;
 public:
  Character();
  Character(Random_Generator_ *Rand_gen, int storyline_, int exp, int levl, int Stre, int Dext,
            int Cons, int Inte, int Wisd, int Charisma, int sex_, int rand_seed_change, Allowance *alowance);

  void Starting_Maxhealth();

  void Character_All_Set();

  ~Character();

  void Set_Party(int party_);

  int Ability_Random_Sets(Random_Generator_ *Rand_gen, int rand_seed_change);

  int Less_than_zero(int a);

  void Maximum_Parameter_Value();

  void Minimum_Parameter_Value();

  //int AbilityModifier(int ability);

  void ConcreteAbilityModifier();

  int ProficiencySetter();

  void PassivePerceptionSetter();

  void Skill_Proficiencies();

  void StorySetsSkills(Allowance *allowance);

  int Check_Ability_Reach_Maximum(int ability);

  void Ability_improve();

  void Race_Choosal(Allowance *alowance);

  void Race_Get_Abilities();

  void Set(int what, int value);

  virtual int Get(int what);

  bool Get_bool(int what);

  virtual string Get_string(int what);

  vector<int> Get_inventory();

  Item *Factory_Complex(string &name_, int quantity);

  void Add_Money(int type, int sum);

  void Add_To_Item_Map(string &name_);

  bool Paying_Money(int how_many_copper);

  int Add_To_Inventory();

  void Equip_Item(int where, Item *what);

  void Equiping_Item();

  void Unequip_Item(int where);

  int Healing_Injuring(int value);

  int Level_Up(Random_Generator_ *Rand_gen);

  void Class_Set_Wealth(Random_Generator_ *Rand_gen);

  void SetClass(Allowance *alowance, Random_Generator_ *Rand_gen);

  void SetSkill();

  int GetSkill(int what);

  void Inventory_Load(vector<int> item_);

  void Starting_Health();

  bool Load(int parameter_i[], bool parameter_b[], vector<string> persona, vector<int> item_);

  void Name_And_Appearance_Set();

  void Race_Call_Load(int parameters[]);

  void Race_Call_race_features();

};




