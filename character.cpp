#pragma once

#include <iostream>
#include <string>
#include "interface_races_classes_background.h"
#include "Race_Class_Background.cpp"
#include "UsefulFunctions.cpp"
#include "inventory.cpp"

using namespace std;

struct Skills {
  int s[18] = {0};/* acrobatics 0,animalHandling 1,arcana 2,athletics 3,deception 4,
history 5,insight 6,intimidation 7,investigation 8,medicine 9,
nature 10,perception 11,performance 12,persuasion 13,religion 14,
sleightOfHand 15,stealth 16,survival 17*/
};

class Character {
 private:
  Race race;
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
  Item item;
  string inventory;
 public:
  Character() {
    race.set(24);//human
    //classType.set(0);//barbarian
    storyline = "Acolyte";
    experience = 0;
    level = 0 ;
    health = 0 ;
    maxhealth = 0 ;
    health_dice = 0 ;
    Str = 0 ;Dex = 0 ; Con = 0 ; Int = 0 ; Wis = 0 ; Cha = 0 ;
    StrModifier = 0 ; DexModifier = 0 ; ConModifier = 0 ;
    IntModifier = 0 ; WisModifier = 0 ; ChaModifier = 0 ;
    AC = 0 ;
    deathsaves_s = 0 ;
    deathsaves_f = 0 ;//success/failure
    passive_perception = 0 ;
    proficiency = 0 ;
    advantage = false; disadvantage = false;
    perception_advantage = false;
    perception_disadvantage = false;
    //item.set();
    inventory = "empty";
  }

  ~Character() {}

  int Less_than_zero(int a) {
    return a < 0 ? 0 : a;
  }

  int AbilityModifier(int a) {
    return (a - 10) / 2;
  }

  int ProficiencySetter(int level) {
    if (level < 4) return 2;
    else if (level > 3 && level < 8) return 3;
    else return 4;
  }

  int PassivePerceptionSetter(int a, bool b, bool c) {
    if (b) a += 5;
    if (c) a -= 5;
    return 10 + a;
  }
  
  void StorySetsSkills(Skills a, string b) {
    if (b == "Acolyte") {
      if (a.s[6] == WisModifier)a.s[6] += proficiency;
      if (a.s[14] == IntModifier)a.s[14] += proficiency;
    } else if (b == "Charlatan") {
      if (a.s[4] == ChaModifier)a.s[4] += proficiency;
      if (a.s[15] == DexModifier)a.s[15] += proficiency;
    } else if (b == "Criminal") {
      if (a.s[4] == ChaModifier)a.s[4] += proficiency;
      if (a.s[16] == DexModifier)a.s[16] += proficiency;
    } else if (b == "Entertainer") {
      if (a.s[0] == IntModifier)a.s[0] += proficiency;
      if (a.s[12] == ChaModifier)a.s[12] += proficiency;
    } else if (b == "FolkHero") {
      if (a.s[1] == WisModifier)a.s[1] += proficiency;
      if (a.s[17] == WisModifier)a.s[17] += proficiency;
    } else if (b == "GuildArtisan") {
      if (a.s[6] == WisModifier)a.s[6] += proficiency;
      if (a.s[13] == ChaModifier)a.s[13] += proficiency;
    } else if (b == "Hermit") {
      if (a.s[9] == WisModifier)a.s[9] += proficiency;
      if (a.s[14] == IntModifier)a.s[14] += proficiency;
    } else if (b == "Noble") {
      if (a.s[5] == IntModifier)a.s[5] += proficiency;
      if (a.s[13] == ChaModifier)a.s[13] += proficiency;
    } else if (b == "Outlander") {
      if (a.s[3] == StrModifier)a.s[3] += proficiency;
      if (a.s[17] == WisModifier)a.s[17] += proficiency;
    } else if (b == "Sage") {
      if (a.s[2] == IntModifier)a.s[2] += proficiency;
      if (a.s[5] == IntModifier)a.s[5] += proficiency;
    } else if (b == "Sailor") {
      if (a.s[3] == StrModifier)a.s[3] += proficiency;
      if (a.s[11] == WisModifier)a.s[11] += proficiency;
    } else if (b == "Soldier") {
      if (a.s[3] == StrModifier)a.s[3] += proficiency;
      if (a.s[7] == ChaModifier)a.s[7] += proficiency;
    } else if (b == "Urchin") {
      if (a.s[15] == DexModifier)a.s[15] += proficiency;
      if (a.s[16] == DexModifier)a.s[16] += proficiency;
    }
  }

  void Ability_improve(){
    if (level == 3 || level == 7) {
      printf("%s %d %s \n",
             "You reached",
             level,
             " level, that means that you have to choose whether improve one ability +2(type 1) or two abilities +1(type 2)");
      int one_or_two_abilities = -1;//abilityLevel_Up
      cin >> one_or_two_abilities;
      one_or_two_abilities = Correctness(one_or_two_abilities, 1, 2);
      if (one_or_two_abilities == 1) {
        printf("%s \n", "What ability do you want to improve +2 ? Str(1),Dex(2),Con(3),Int(4),Wis(5),Cha(6)");
        cin >> one_or_two_abilities;
        one_or_two_abilities = Correctness(one_or_two_abilities, 1, 6);
        Set(one_or_two_abilities + 2, 2);
      } else {
        printf("%s \n",
               "What abilities do you want to improve +1 ? Str(1),Dex(2),Con(3),Int(4),Wis(5),Cha(6) *Type 2 spaced numbers*");
        int one_or_two_abilities1 = 0;
        cin >> one_or_two_abilities >> one_or_two_abilities1;
        one_or_two_abilities = Correctness(one_or_two_abilities, 1, 6);
        one_or_two_abilities1 = Correctness(one_or_two_abilities1, 1, 6);
        Set(one_or_two_abilities + 2, 1);
        Set(one_or_two_abilities1 + 2, 1);
      }
    }
  }

  void SetF(string a, string b, string story, int l, int h, int s, int d, int c, int i, int w, int cha) {
    l = Less_than_zero(l);
    h = Less_than_zero(h);
    s = Less_than_zero(s);
    d = Less_than_zero(d);
    c = Less_than_zero(c);
    i = Less_than_zero(i);
    w = Less_than_zero(w);
    cha = Less_than_zero(cha);
    level = l;
    health = h;
    maxhealth = h;
    Str = s;
    Dex = d;
    Con = c;
    Int = i;
    Wis = w;
    Cha = cha;
    StrModifier = AbilityModifier(Str);
    DexModifier = AbilityModifier(Dex);
    ConModifier = AbilityModifier(Con);
    IntModifier = AbilityModifier(Int);
    WisModifier = AbilityModifier(Wis);
    ChaModifier = AbilityModifier(Cha);
    SetSkill(skill);
    proficiency = ProficiencySetter(level);
    passive_perception = PassivePerceptionSetter(WisModifier, perception_advantage, perception_disadvantage);
    StorySetsSkills(skill,storyline);
  }

  void Set(int a, int b) {// a - what parameter will be changed, b - modifier(can be negative)
    a = Correctness(a, 0, 14);
    if (a == 1) { experience += b; }
    else if (a == 2) { health += b; }
    else if (a == 3) { Str += b; }
    else if (a == 4) { Dex += b; }
    else if (a == 5) { Con += b; }
    else if (a == 6) { Int += b; }
    else if (a == 7) { Wis += b; }
    else if (a == 8) { Cha += b; }
    else if (a == 9) { AC += b; }
    else if (a == 10) { if (b < 0)deathsaves_f++; else deathsaves_s++; }
    else if (a == 11) { printf("%s \n", "reserved for Skills"); }
    else if (a == 12) { printf("%s \n", "reserved for weapon"); }
    else if (a == 13) { printf("%s \n", "reserved for inventory"); }
    else if (a == 14) { printf("%s \n", "reserved for story/background"); }
  }

  int Get(int a) {
    a = Correctness(a, 0, 15);
    if (a == 1) { return experience; }
    else if (a == 2) { return health; }
    else if (a == 3) { return Str; }
    else if (a == 4) { return Dex; }
    else if (a == 5) { return Con; }
    else if (a == 6) { return Int; }
    else if (a == 7) { return Wis; }
    else if (a == 8) { return Cha; }
    else if (a == 9) { return AC; }
    else if (a == 10) { return deathsaves_f; }
    else if (a == 11) { return deathsaves_s; }
    else if (a == 12) { return -1; } //reserved for weapon
    else if (a == 13) { return -1; } //reserved for inventory
    else if (a == 14) { return -1; }//reserved for story/background
    else if (a == 15) { return passive_perception; }
    return -1;
  }

  void Level_Up() {
    if (level < 4 && experience > 300 * pow(3, level - 1)) {
      level++;
      proficiency++;
      maxhealth = Health_Level_Up(health_dice, ConModifier, maxhealth);
      health = maxhealth;
      Ability_improve();
      Level_Up();
    } else if (level == 4 && experience > 6499) {
      level++;
      maxhealth = Health_Level_Up(health_dice, ConModifier, maxhealth);
      health = maxhealth;
      Level_Up();
    } else if (level == 5 && experience > 13999) {
      level++;
      maxhealth = Health_Level_Up(health_dice, ConModifier, maxhealth);
      health = maxhealth;
      Level_Up();
    } else if (level == 6 && experience > 22999) {
      level++;
      maxhealth = Health_Level_Up(health_dice, ConModifier, maxhealth);
      health = maxhealth;
      Level_Up();
    } else if (level == 7 && experience > 33999) {
      level++;
      proficiency++;
      maxhealth = Health_Level_Up(health_dice, ConModifier, maxhealth);
      health = maxhealth;
      Ability_improve();
      Level_Up();
    } else if (level == 8 && experience > 47999) {
      level++;
      maxhealth = Health_Level_Up(health_dice, ConModifier, maxhealth);
      health = maxhealth;
      Level_Up();
    } else if (level == 9 && experience > 64999) {
      level++;
      maxhealth = Health_Level_Up(health_dice, ConModifier, maxhealth);
      health = maxhealth;
      Level_Up();
    }
    printf("%s %d \n", "Your level:", level);
    printf("%s %d \n", "Your health:", health);
  }

  void SetSkill(Skills c) {
    for (int j = 0; j < 18; j++) {
      if (j == 0 || j == 2 || j == 5 || j == 8 || j == 10 ||
          j == 14) { c.s[j] += IntModifier; }//acrobatics,arcana,history,investigation,nature,religion
      else if (j == 1 || j == 6 || j == 9 || j == 11 ||
          j == 17) { c.s[j] += WisModifier; }//animalHandling,.s[6],medicine,perception,survival
      else if (j == 3) { c.s[j] += StrModifier; }//athletics
      else if (j == 4 || j == 7 || j == 12 ||
          j == 13) { c.s[j] += ChaModifier; }//deception,intimidation,performance,persuasion
      else if (j == 15 || j == 16) { c.s[j] += DexModifier; }//sleightOfHand,stealth
    }
  }

  int GetSkill(int a) {
    a = Correctness(a,0,17);
    return skill.s[a];
  }
};




