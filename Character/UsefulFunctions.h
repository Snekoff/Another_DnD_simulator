#pragma once
#include <iostream>
#include <random>


#ifndef ANOTHER_DND_SIMULATOR_USEFULFUNCTIONS_H
#define ANOTHER_DND_SIMULATOR_USEFULFUNCTIONS_H

struct Existing_Types {
  int minHeight[11] = {6, 4, 6, 3, 3, 5, 5, 3, 5, 5, 5 };
  int maxHeight[11] = {6, 5, 6, 4, 4, 6, 6, 3, 6, 6, 6 };
  int minWeight[11] = {10, 4, 6, 3, 3, 5, 5, 3, 5, 5, 5 };
  int maxWeight[11] = {140, 140, 140, 140, 140, 140, 140, 140, 145, 140, 140 };
  int minAge[11] = {3, 4, 6, 3, 3, 5, 5, 3, 5, 5, 5 };
  int maxAge[11] = {120, 140, 140, 140, 140, 140, 140, 140, 200, 140, 140 };//
  //std::string item[9] = {"equipment","potions","food","ammo_holder","shield","weapon","armor","ammo","usable"};
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

  std::string  stories[13] = {"Acolyte", "Charlatan", "Criminal", "Entertainer", "FolkHero", "GuildArtisan",
        "Hermit", "Noble", "Outlander", "Sage", "Sailor", "Soldier", "Urchin"};
  std::string params[90] = {" storyline_i(1)", " sex(2)", " experience(3)", " level(4)", " health(5)", " maxhealth(6)",
                            " health_dice(7)", " Str(8)", " Dex(9)", " Con(10)", " Int(11)", " Wis(12)", " Cha(13)",
                            " armor_class(14)", " deathsaves_s(15)", " deathsaves_f(16)",
                            " money[0]()", " money[1]", " money[2]",
                            " money[3]", " money[4]", " state()", " type()", " ",
                             " architype()", " type()", " height()",
                            " weight()", " age()", " Movement()", " Size", " Darkvision()",
                            " damage_resistance()", " subtype()", " raceFeatures()",
                            " advantage()",
                            " disadvantage()", " perception_advantage()", " perception_disadvantage()",
                            " *s_b[]", " *s_b[1]", " *s_b[2]", " *s_b[3]", " *s_b[4]", " *s_b[5]", " *s_b[6]",
                            " *s_b[7]", " *s_b[8]", " *s_b[9]", " *s_b[10]", " *s_b[11]", " *s_b[12]", " *s_b[13]",
                            " *s_b[14]", " *s_b[15]", " *s_b[16]", " *s_b[17]",
                            " saving_throw_proficiencies[0]", " saving_throw_proficiencies[1]",
                            " saving_throw_proficiencies[2]", " saving_throw_proficiencies[3]",
                            " saving_throw_proficiencies[4]", " saving_throw_proficiencies[5]",
                            " armor_and_weapon_proficiencies[0]", " armor_and_weapon_proficiencies[1]",
                            " armor_and_weapon_proficiencies[2]", " armor_and_weapon_proficiencies[3]",
                            " armor_and_weapon_proficiencies[4]", " armor_and_weapon_proficiencies[5]",
                            " armor_and_weapon_proficiencies[6]",
                             " exhaustion",  " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
                            " ", " ", " ", " ", " ", ""
 };
}; //
template <typename T>
T Correctness_of_input(T a, T lowerlimit, T higherlimit);

class Random_Generator_ {
 private:
  std::random_device rd;
  //std::mt19937 mt;
 public:
  Random_Generator_();
  ~Random_Generator_();

  int Rand(int lowerlimit, int higherlimit);
};

int Health_Level_Up(Random_Generator_ * Rand_gen, int health_dice, int ConModifier, int maxhealth);

template <typename T>
T IsNumber(T a, T lowerlimit, T higherlimit);


#endif //ANOTHER_DND_SIMULATOR_USEFULFUNCTIONS_H
