#pragma once

#include <iostream>
#include <string>
#include <utility>
#include "Interface_races_classes_background.h"
#include "Race_Class_Background.cpp"
#include "UsefulFunctions.cpp"
#include "Inventory.cpp"

using namespace std;

struct Skills {
  int s[18] = {0};/*acrobatics 0,animalHandling 1,arcana 2,athletics 3,deception 4,
history 5,insight 6,intimidation 7,investigation 8,medicine 9,
nature 10,perception 11,performance 12,persuasion 13,religion 14,
sleightOfHand 15,stealth 16,survival 17*/
};

const int kPLAYER_COUNT = 10;
int dragonborn_count = 0;
int dwarf_count = 0;
int elf_count = 0;
int gnome_count = 0;
int goblin_count = 0;
int half_elf_count = 0;
int half_orc_count = 0;
int halfling_count = 0;
int human_count = 0;
int lizardfolk_count = 0;
int tiefling_count = 0;

auto *dragonborn = new Dragonborn[kPLAYER_COUNT]();
auto *dwarf = new Dwarf [kPLAYER_COUNT]();
auto *elf = new Elf [kPLAYER_COUNT]();
auto *gnome = new Gnome [kPLAYER_COUNT]();
auto *goblin = new Goblin[kPLAYER_COUNT]();
auto *half_elf = new Half_Elf[kPLAYER_COUNT]();
auto *half_orc = new Half_Orc[kPLAYER_COUNT]();
auto *halfling = new Halfling [kPLAYER_COUNT]();
auto *human = new Human [kPLAYER_COUNT]();
auto *lizardfolk = new Lizardfolk [kPLAYER_COUNT]();
auto *tiefling = new Tiefling [kPLAYER_COUNT]();


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
  Item item;
  string inventory;
  Existing_Types E;
 public:
  Character() {
    //race.set(24);//human
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
    inventory = "empty";//
  }
  Character(string storyl, int exp, int levl, int Stre, int Dext,
      int Cons, int Inte, int Wisd, int Charisma, int ArmorClass){
    exp = Less_than_zero(exp);
    levl = Less_than_zero(levl);
    Stre = Less_than_zero(Stre);
    Dext = Less_than_zero(Dext);
    Cons = Less_than_zero(Cons);
    Inte = Less_than_zero(Inte);
    Wisd = Less_than_zero(Wisd);
    Charisma = Less_than_zero(Charisma);
    ArmorClass = Less_than_zero(ArmorClass);
    health = 0 ;
    maxhealth = 0 ;
    health_dice = 0 ;
    storyline = std::move(storyl);
    if(exp < E.experience_per_level[levl - 1]){ exp = E.experience_per_level[level - 1]; }
    experience = exp;
    Str = Stre;
    Dex = Dext;
    Con = Cons;
    Int = Inte;
    Wis = Wisd;
    Cha = Charisma;
    AC = ArmorClass;
    deathsaves_s = 0 ;
    deathsaves_f = 0 ;
    passive_perception = 0 ;
    proficiency = 0 ;
    advantage = false; disadvantage = false;
    perception_advantage = false;
    perception_disadvantage = false;
    inventory = "";
    StrModifier = AbilityModifier(Str);
    DexModifier = AbilityModifier(Dex);
    ConModifier = AbilityModifier(Con);
    IntModifier = AbilityModifier(Int);
    WisModifier = AbilityModifier(Wis);
    ChaModifier = AbilityModifier(Cha);
    SetSkill(skill);
    proficiency = ProficiencySetter(level);
    passive_perception = PassivePerceptionSetter(WisModifier, perception_advantage, perception_disadvantage);
    Race_Choosal();
    StorySetsSkills(skill,storyline);
    // reserved for @Class gives health dice"
    level = 0;
    Level_Up();
  }

  ~Character() = default;

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

  void Size_Set(int a, int b, int c,int race1,int subrace,int negative){
    // negative for class dragonborn

    printf("%s \n",
           "insert height(ft), weight(lbs) and age(y) of your character or type zero(s) (0 100 0) to random");
    printf("%s %d %s %d %s %d %s %d %s %d %s %d \n",
           "Normal parameters for your race are: height(ft) from ",E.minHeight[race1 - 1] ,"to ", E.maxHeight[race1 - 1]," weight(lbs)from ",
           E.minWeight[race1 - 1],"to ", E.maxWeight[race1 - 1]," and age(y) from ",E.minAge[race1 - 1] ,"to ", E.maxAge[race1 - 1]);
    cin >> a >> b >> c;
    if (a <= 0 || a > E.maxHeight[race1 - 1]) { a = Random_Generator(E.minHeight[race1 - 1], E.maxHeight[race1 - 1]); }
    if (b <= 0 || b > E.maxWeight[race1 - 1]) { b = Random_Generator(E.minWeight[race1 - 1], E.maxWeight[race1 - 1]); }
    if (c <= 0 || c > E.maxAge[race1 - 1]) { c = Random_Generator(E.minAge[race1 - 1], E.maxAge[race1 - 1]); }
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
    if (level == 4 || level == 8) {
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

  void Race_Choosal(){
    printf("%s \n", "It is time to choose your race. What it will be?");
    printf("%s \n", "1. Dragonborn (10 subraces)\n"
                    "2. Dwarf (3 subraces)\n"
                    "3. Elf (7 subraces)\n"
                    "4. Gnome (3 subraces)\n"
                    "5. Goblin\n"
                    "6. Half-Elf (5 subraces)\n"
                    "7. Half-Orc ( or Orc )\n"
                    "8. Halfling (3 subraces)\n"
                    "9. Human (2 subraces)\n"
                    "10. Lizardfolk\n"
                    "11. Tiefling (11 subraces)\n"
                    "Type number, and proceed");
    int race = 9;
    std::cin >> race;
    race = Correctness(race, 1, 11);
    int subrace = 0;
    if (race == 1) {
      printf("%s \n", "Choose your subrace. What it will be?");
      printf("%s \n", "1. Black (Acid) 30ft. line\n"
                      "2. Blue (Lightning) 30ft. line\n"
                      "3. Brass (Fire) 30ft. line\n"
                      "4. Bronze (Lightning) 30ft. line\n"
                      "5. Copper (Acid) 30ft. line\n"
                      "6. Gold (Fire) 15ft. cone\n"
                      "7. Green (Poison) 15ft. cone\n"
                      "8. Red (Fire) 15ft. cone\n"
                      "9. Silver (Cold) 15ft. cone\n"
                      "10. White (Cold) 15ft. cone\n"
                      "Type number, and proceed");
      cin >> subrace;
      subrace = Correctness(subrace, 1, 10);
      int a = 0, b = 0, c = 0;
      Size_Set(a,b,c,race,subrace,subrace);
      dragonborn[dragonborn_count].Create(subrace, a, b, c);
      race_of_character = &dragonborn[dragonborn_count];
      dragonborn_count++;
    } else if (race == 2) {
      printf("%s \n", "Choose your subrace. What it will be?");
      printf("%s \n", "1. Duergar\n"
                      "2. Hill\n"
                      "3. Mountain\n"
                      "Type number, and proceed");
      cin >> subrace;
      subrace = Correctness(subrace, 1, 3);
      int a = 0, b = 0, c = 0;
      Size_Set(a,b,c,race,subrace,subrace);
      dwarf[dwarf_count].Create(subrace, a, b, c);
      race_of_character = &dwarf[dwarf_count];
      dwarf_count++;

    } else if (race == 3) {
      printf("%s \n", "Choose your subrace. What it will be?");
      printf("%s \n", "1. \n"
                      "2. \n"
                      "3. \n"
                      "4. \n"
                      "5. \n"
                      "6. \n"
                      "7. \n"
                      "8. \n"
                      "9. \n"
                      "10. \n"
                      "Type number, and proceed");
      cin >> subrace;
      subrace = Correctness(subrace, 1, 10);
      int a = 0, b = 0, c = 0;
      Size_Set(a,b,c,race,subrace,subrace);
      elf[elf_count].Create(subrace, a, b, c);
      race_of_character = &elf[elf_count];
      elf_count++;

    } else if (race == 4) {
      printf("%s \n", "Choose your subrace. What it will be?");
      printf("%s \n", "1. \n"
                      "2. \n"
                      "3. \n"
                      "4. \n"
                      "5. \n"
                      "6. \n"
                      "7. \n"
                      "8. \n"
                      "9. \n"
                      "10. \n"
                      "Type number, and proceed");
      cin >> subrace;
      subrace = Correctness(subrace, 1, 10);
      int a = 0, b = 0, c = 0;
      Size_Set(a,b,c,race,subrace,subrace);
      gnome[gnome_count].Create(subrace, a, b, c);
      race_of_character = &gnome[gnome_count];
      gnome_count++;

    } else if (race == 5) {
      int a = 0, b = 0, c = 0;
      Size_Set(a,b,c,race,subrace,subrace);
      goblin[goblin_count].Create(subrace, a, b, c);
      race_of_character = &goblin[goblin_count];
      goblin_count++;

    } else if (race == 6) {
      printf("%s \n", "Choose your subrace. What it will be?");
      printf("%s \n", "1. \n"
                      "2. \n"
                      "3. \n"
                      "4. \n"
                      "5. \n"
                      "Type number, and proceed");
      cin >> subrace;
      subrace = Correctness(subrace, 1, 10);
      int a = 0, b = 0, c = 0;
      Size_Set(a,b,c,race,subrace,subrace);
      half_elf[half_elf_count].Create(subrace, a, b, c);
      race_of_character = &half_elf[half_elf_count];
      half_elf_count++;

    } else if (race == 7) {
      printf("%s \n", "Choose your subrace. What it will be?");
      printf("%s \n", "1. \n"
                      "2. \n"
                      "Type number, and proceed");
      cin >> subrace;
      subrace = Correctness(subrace, 1, 10);
      int a = 0, b = 0, c = 0;
      Size_Set(a,b,c,race,subrace,subrace);
      half_orc[half_orc_count].Create(subrace, a, b, c);
      race_of_character = &half_orc[half_orc_count];
      half_orc_count++;

    } else if (race == 8) {
      printf("%s \n", "Choose your subrace. What it will be?");
      printf("%s \n", "1. \n"
                      "2. \n"
                      "3. \n"
                      "Type number, and proceed");
      cin >> subrace;
      subrace = Correctness(subrace, 1, 10);
      int a = 0, b = 0, c = 0;
      Size_Set(a,b,c,race,subrace,subrace);
      halfling[halfling_count].Create(subrace, a, b, c);
      race_of_character = &halfling[halfling_count];
      halfling_count++;

    } else if (race == 9) {
      printf("%s \n", "Choose your subrace. What it will be?");
      printf("%s \n", "1. \n"
                      "2. \n"
                      "Type number, and proceed");
      cin >> subrace;
      subrace = Correctness(subrace, 1, 10);
      int a = 0, b = 0, c = 0;
      Size_Set(a,b,c,race,subrace,subrace);
      human[human_count].Create(subrace, a, b, c);
      race_of_character = &human[human_count];
      human_count++;

    } else if (race == 10) {
      int a = 0, b = 0, c = 0;
      Size_Set(a,b,c,race,subrace,subrace);
      lizardfolk[lizardfolk_count].Create(subrace, a, b, c);
      race_of_character = &lizardfolk[lizardfolk_count];
      lizardfolk_count++;

    } else if (race == 11) {
      printf("%s \n", "Choose your subrace. What it will be?");
      printf("%s \n", "1. \n"
                      "2. \n"
                      "3. \n"
                      "4. \n"
                      "5. \n"
                      "6. \n"
                      "7. \n"
                      "8. \n"
                      "9. \n"
                      "10. \n"
                      "11. \n"
                      "Type number, and proceed");
      cin >> subrace;
      subrace = Correctness(subrace, 1, 10);
      int a = 0, b = 0, c = 0;
      Size_Set(a,b,c,race,subrace,subrace);
      tiefling[tiefling_count].Create(subrace, a, b, c);
      race_of_character = &tiefling[tiefling_count];
      tiefling_count++;
    }
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
    if (level < 4 && experience >= 300 * pow(3, level)) {
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




