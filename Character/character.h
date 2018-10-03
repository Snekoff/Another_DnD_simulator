#pragma once
#ifndef ANOTHER_DND_SIMULATOR_CHARACTER_H
#define ANOTHER_DND_SIMULATOR_CHARACTER_H

#endif //ANOTHER_DND_SIMULATOR_CHARACTER_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <math.h>
#include "UsefulFunctions.h"
#include "Classes.h"
#include "Race.h"
#include "../Inventory(Item)/Item.h"
#include "../Inventory(Item)/Items_Factory.h"
#include "../json_nlohmann/single_include/nlohmann/json.hpp"

using namespace std;

const int kData_size = 72;
const int kMoney_types = 5;
const int kEquip_places = 10;

class Character {
 private:
  Race* race_of_character;
  Class classType;
  string storyline;
  int storyline_i;
  Existing_Types E;

  int exhaustion;
 protected:
  int sex; //0 - female,1 - male, 3 - Futa, 4 - creature
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
 public:
  Character();
  Character(Random_Generator_ * Rand_gen,int storyline_, int exp, int levl, int Stre, int Dext,
            int Cons, int Inte, int Wisd, int Charisma, int sex_, int rand_seed_change);

  ~Character();

  void Set_Party(int party_);

  int Ability_Random_Sets(Random_Generator_ * Rand_gen, int rand_seed_change);

  int Less_than_zero(int a);

  void Maximum_Parameter_Value();

  int AbilityModifier(int ability);

  void ConcreteAbilityModifier();
  //new
  int ProficiencySetter();

  int PassivePerceptionSetter(int WisModifier_, bool perception_advantage_, bool perception_disadvantage_);

  void Skill_Proficiences();

  void StorySetsSkills(int storyline_i);

  int Check_Ability_Reach_Maximum(int ability);

  void Ability_improve();

  void Race_Choosal(Random_Generator_ * Rand_gen);

  void Race_Get_Abilities();

  void Set(int what, int value);

  virtual int Get(int what);

  bool Get_bool(int what);

  vector<int> Get_inventory();

  Item * Factory_Complex(string &name_, int quantity);

  void Add_Money(int type,int sum);

  void Add_To_Item_Map(string &name_);

  bool Paying_Money(int how_many_copper);

  int Add_To_Inventory();

  void Equip_Item(int where, Item *what);

  void Equiping_Item();

  void Unequip_Item(int where);

  int Healing_Injuring(int value);

  int Level_Up(Random_Generator_ * Rand_gen);

  void Class_Set_Wealth(Random_Generator_ * Rand_gen);

  void SetClass(Random_Generator_ * Rand_gen);

  void SetSkill();

  int GetSkill(int what);

  void Inventory_Load(vector<int> item_);

  void Starting_Health();

  bool Load(int parameter_i[], bool parameter_b[], vector<int> item_);

};




