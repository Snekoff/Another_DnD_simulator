#pragma once
#include <iostream>
#include <random>

//#include "../gtest/googletest/include/gtest/gtest.h"
//#include "../gtest/googlemock/include/gmock/gmock.h"

#include "../aditional_tools/allowance.h"

#ifndef ANOTHER_DND_SIMULATOR_USEFULFUNCTIONS_H
#define ANOTHER_DND_SIMULATOR_USEFULFUNCTIONS_H

const int kRace_Num = 11;
const int kRace_with_subraces_Num = 39;
const int kRace_Load_parameters_shift = 26;
const int kAbilities_Num = 6;
const int kLevels_Num = 20;
const int kStory_Num = 13;
const int kCondition_NUM = 16;
const int kOutput_Num = 90;
const int kSkills_Num = 18;
const int kLevel_Minimum = 1;
const int kExperience_Max = 355000;
const int kExperience_Min = 0;

const double kEpsilon = 0.00001;

struct Existing_Types {
  int minHeight[kRace_Num] = {6, 4, 6, 3, 3, 5, 5, 3, 5, 5, 5 };
  int maxHeight[kRace_Num] = {6, 5, 6, 4, 4, 6, 6, 3, 6, 6, 6 };
  int minWeight[kRace_Num] = {10, 4, 6, 3, 3, 5, 5, 3, 5, 5, 5 };
  int maxWeight[kRace_Num] = {140, 140, 140, 140, 140, 140, 140, 140, 145, 140, 140 };
  int minAge[kRace_Num] = {3, 4, 6, 3, 3, 5, 5, 3, 5, 5, 5 };
  int maxAge[kRace_Num] = {120, 140, 140, 140, 140, 140, 140, 140, 200, 140, 140 };//
  std::string Condition[kCondition_NUM] = {"0.fine", " 1.blinded", " 2.charmed", " 3.deafened", " 4.frightened", " 5.grappled",
                        " 6.incapacitated", " 7.invisible", " 8.petrified", "9.poisoned", " 10.prone",
                        " 11.restrained", " 12.stunned", " 13.unconscious", " 14.dead", " 15.disease"};
  int race_ability_bonus[kRace_with_subraces_Num][kAbilities_Num] =
      {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
  int experience_per_level[kLevels_Num] = {0,300,900,2700,6500,14000,23000,34000,48000,64000,85000,100000,120000,140000,165000,195000,225000,265000,305000,kExperience_Max};
  std::string  stories[kStory_Num] = {"Acolyte", "Charlatan", "Criminal", "Entertainer", "FolkHero", "GuildArtisan",
        "Hermit", "Noble", "Outlander", "Sage", "Sailor", "Soldier", "Urchin"};
  std::string params_i[kOutput_Num] = { " party"," storyline_i", " sex", " experience", " level", " health", " maxhealth",
                            " health_dice", " Str", " Dex", " Con", " Int", " Wis", " Cha",
                            " armor_class", " deathsaves_s", " deathsaves_f",
                            " money[0]", " money[1]", " money[2]",
                            " money[3]", " money[4]", " exhaustion", " ClassType", " ",
                             " archetype", " RaceType", " height",
                            " weight", " age", " movement", " size", " darkvision",
                            " damage_resistance", " subtype", " raceFeatures",
                            " coordinates[0]",
                            " coordinates[1]", " coordinates[2]", " ",
                            " ", " ", " ", " ", " ", " ", " ",
                            " ", " ", " ", " ", " ", " ", " ",
                            " ", " ", " ", " ",
                            " ", " ",
                            " ", " ",
                            " ", " ",
                            " ", " ",
                            " ", " ",
                            " ", " ",
                            " ",
                             " ",   " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
                            " ", " ", " ", " ", " ", " "
 };
  std::string params_b[kOutput_Num] = {"advantage"," disadvantage", " perception_advantage", " perception_disadvantage",
                                       " *skills_b[]", " *skills_b[1]", " *skills_b[2]", " *skills_b[3]",
                                       " *skills_b[4]", " *skills_b[5]", " *skills_b[6]", " *skills_b[7]",
                                       " *skills_b[8]", " *skills_b[9]", " *skills_b[10]", " *skills_b[11]",
                                       " *skills_b[12]", " *skills_b[13]", " *skills_b[14]", " *skills_b[15]",
                                       " *skills_b[16]", " *skills_b[17]",
                                       " saving_throw_proficiencies[0]", " saving_throw_proficiencies[1]",
                                       " saving_throw_proficiencies[2]", " saving_throw_proficiencies[3]",
                                       " saving_throw_proficiencies[4]", " saving_throw_proficiencies[5]",
                                       " armor_and_weapon_proficiencies[0]", " armor_and_weapon_proficiencies[1]",
                                       " armor_and_weapon_proficiencies[2]", " armor_and_weapon_proficiencies[3]",
                                       " armor_and_weapon_proficiencies[4]", " armor_and_weapon_proficiencies[5]",
                                       " armor_and_weapon_proficiencies[6]",
                                       "state[0]",  "state[1]", "state[2]", "state[3]", "state[4]", "state[5]",
                                       "state[6]", "state[7]", "state[8]", "state[9]", "state[10]", "state[11]",
                                       "state[12]", "state[13]", "state[14]", "state[15]", " ", " ", " ", " ", " ",
                                       " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
                                       " ", " ", " ", " ", " ", " ", " ",  " ", " ", " ", " ", " ", " ", " ", " ",
                                       " ", " ", " ", " ", " ",
                                       " ",

  };
  int fake_parameter = 0;
}; //
template <typename T>
T Correctness_of_input(T a, T lower_limit, T higher_limit);

class Random_Generator_ {
 private:
  std::random_device rd;
  //std::mt19937 mt;
 public:
  Random_Generator_();
  ~Random_Generator_();

  int Rand(int lower_limit, int higher_limit);
};

int Health_Level_Up(Random_Generator_ * Rand_gen, int health_dice, int ConModifier, int maxHealth);

template <typename T>
T IsNumber(T a, T lower_limit, T higher_limit);


#endif //ANOTHER_DND_SIMULATOR_USEFULFUNCTIONS_H
