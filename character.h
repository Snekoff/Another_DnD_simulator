#pragma once
#ifndef ANOTHER_DND_SIMULATOR_CHARACTER_H
#define ANOTHER_DND_SIMULATOR_CHARACTER_H

#endif //ANOTHER_DND_SIMULATOR_CHARACTER_H

#include <iostream>
#include "UsefulFunctions.h"
#include "Classes.h"
#include "Race_Class_Background.h"
#include "Inventory(Item)/Item.h"
#include "Inventory(Item)/Items_Factory.h"

using namespace std;

struct Skills {
  int s[18];/*acrobatics 0,animalHandling 1,arcana 2,athletics 3,deception 4,
history 5,insight 6,intimidation 7,investigation 8,medicine 9,
nature 10,perception 11,performance 12,persuasion 13,religion 14,
sleightOfHand 15,stealth 16,survival 17*/
};

int dragonborn_count;
int dwarf_count;
int elf_count;
int gnome_count;
int goblin_count;
int half_elf_count;
int half_orc_count;
int halfling_count;
int human_count;
int lizardfolk_count;
int tiefling_count;

class Character {
 private:
  Race* race_of_character;
  Class classType;
  string storyline;
  int experience, level;
  int health, maxhealth;
  int health_dice;
  int Str, Dex, Con, Int, Wis, Cha;
  int StrModifier, DexModifier, ConModifier, IntModifier, WisModifier, ChaModifier;
  int AC;
  int deathsaves_s, deathsaves_f;//success/failure
  int passive_perception, proficiency;
  bool advantage, disadvantage ;
  bool perception_advantage;
  bool perception_disadvantage;
  Skills skill;
  //Item item;
  string inventory;
  Existing_Types E;
 public:
  Character();
  Character(string &storyl, int exp, int levl, int Stre, int Dext,
            int Cons, int Inte, int Wisd, int Charisma);

  ~Character() = default;

  int Less_than_zero(int a);

  int AbilityModifier(int a);

  void ConcreteAbilityModifier();

  int ProficiencySetter();

  void Size_Set(int a, int b, int c,int race1,int subrace,int negative);

  int PassivePerceptionSetter(int a, bool b, bool c);

  void StorySetsSkills(int *s[],bool *s_b[], string &b);

  void Ability_improve();

  void Race_Choosal();

  void Race_Get_Abilities();

  void Set(int a, int b);

  int Get(int a);

  void Open_Inventory();

  void Level_Up();

  void SetSkill(int *c[]);

  void SetClass();

  void Starting_Health();

  int GetSkill(int a);
};




