//
//
//

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>

#include "../items/item.h"
#include "../character/common_functions.h"
#include "../items/items_factory.h"

#ifndef ANOTHER_DND_SIMULATOR_CREATURE_H
#define ANOTHER_DND_SIMULATOR_CREATURE_H

using namespace std;

const int kData_size = 99;
const int kString_Data_size = 4;
const int kParameterMinimum = 0;
const int kMoney_types = 5;
const int kEquip_places = 10;
const int kAbility_Roll_Minimum_Score = 10;
const int kAbility_Maximum_Score = 20;
//const int kAbility_Minimum_Score = 0;
const int kAbility_Starting_Maximum = 16;
const int kSkills_b_shift = 4;
const int kGender_Num = 4;
const int kDeathsave_Max = 3;
//const int kDeathsave_Min = 0;
const int kCoordinates_shift = 36;
const int kGetAbilities_Shift = 8;
const int kClass_type_parameter = 23;
const int kClassType_get_bool_shift = 16;
const int kClass_archetype_parameter = 35;
const int kStates_shift = 35;
const int kBarbarian_Unarmored_Defence = 10;
const int kWealth_Set_parameters = 3;
const int kDice_Minimum_value = 1;
const int kExhaustion_MAX_Level = 8;
const int kSpellMaxLevel = 10;
const int kCoordinates_NUM = 3;
const int kSpeed_types_NUM = 4;

struct SpellAndUsageTimes {
  string spell_name;
  int max_charges;
  int charges;
};

class Creature {
 protected:
  int sex; //0 - female,1 - male, 2 - Futanari, 3 - creature
  int experience, level;
  int health, maxhealth;
  int health_dice;
  int health_dice_num;
  int health_modifier;
  int Str, Dex, Con, Int, Wis, Cha;//13
  int StrModifier, DexModifier, ConModifier, IntModifier, WisModifier, ChaModifier;
  int armor_class;
  int deathsaves_s, deathsaves_f;//success/failure
  int passive_perception, proficiency;
  vector<int> spellSlots;
  bool advantage, disadvantage;
  bool perception_advantage;
  bool perception_disadvantage;//20
  vector<int> skills;
  /*acrobatics 0,animalHandling 1,arcana 2,athletics 3,deception 4,
history 5,insight 6,intimidation 7,investigation 8,medicine 9,
nature 10,perception 11,performance 12,persuasion 13,religion 14,
sleightOfHand 15,stealth 16,survival 17*/
  vector<bool> skills_b;//38
  int money[kMoney_types]; // copper, silver, gold, platinum, Total money(in copper equivalent)
  vector<Item *> inventory;
  map<std::string, Item *> items_map;
  vector<Item *> equipped;
  /* 0.fine, 1.blinded, 2.charmed, 3.deafened, 4.frightened, 5.grappled, 6.incapacitated, 7.invisible, 8.petrified,
   * 9.poisoned, 10.prone, 11.restrained, 12.stunned, 13.unconscious, 14.dead, 15.disease 16. ??*/
  bool state[kCondition_NUM];
  // walk, swim, climb, fly
  int speed[kSpeed_types_NUM];
  string fly_condition;
  bool can_hover;
  vector <string> resistance;
  vector <string> resistance_note;
  vector <string>  immune;
  vector <string>  condition_imune;
  vector <string> senses;
  vector<string> languages;
  vector<string> language_tags;
  vector<string> sense_tags;
  int party;
  int coordinates[kCoordinates_NUM];
  string character_name;
  string player_name;
  string character_type;
  string appearance;//appearance
  int reaction;// how many reactions
  int reach;//feets
  bool isNPC;
  string hp_formula;
  vector<string> trait;
  vector<string> action;
  vector<string> spellcasting_name_and_entries;
  vector<SpellAndUsageTimes> spellcast_daily;
  string spellcasting_ability;
  vector <string> spellcasting_will;
  vector <vector <string>> spells;
  vector<string> trait_tags;
  vector<string> action_tags;
  vector<string> legendary;
  vector<string> variant;
  string legendary_group;
  int legendary_actions;
  bool is_named_creature;
 public:
  int Hp_Formula_Parse(string hpFormula, int returnHitDiceOrNumOfDicesOrHealthModifier);
  int HealthRoll(Random_Generator_ *Rand_gen, int hitDice, int numOfDices);

  int AbilityModifier(int ability);

  vector <vector <string>> spellsParse (const nlohmann::basic_json<> &j, string whatAreLookedFor);
  vector <int> spellSlotsParse (const nlohmann::basic_json<> &j, string whatAreLookedFor);
  vector <string> spellcastingWillParse (const nlohmann::basic_json<> &j);
  vector <SpellAndUsageTimes> spellcastingDailyParse (const nlohmann::basic_json<> &j);
  vector <string> commonForTraitAndActionAndSpellNameAndSpellHeaderEntriesAndLegendaryParse (const nlohmann::basic_json<> &j, string howEntriesNamed);
  vector<string> commonForImmuneAndConditionImmuneAndSensesAndLanguageParse(const nlohmann::basic_json<> &MonsterJson, string whatAreLookedFor);
  vector<string> ImmuneParse(const nlohmann::basic_json<> &MonsterJson, string whatAreLookedFor);
  vector<string> commonVariantParse(const nlohmann::basic_json<> &MonsterJson, string whatAreLookedFor);
  vector<string> commonForAllTagsParse(const nlohmann::basic_json<> &MonsterJson, string whatAreLookedFor);

  vector<string> commonVectorStringParse(const nlohmann::basic_json<> &MonsterJson, string whatAreLookedFor);
  string commonStringParse(const nlohmann::basic_json<> &MonsterJson, string whatAreLookedFor);
  int commonIntParse(const nlohmann::basic_json<> &MonsterJson, string whatAreLookedFor);
  bool commonBoolParse(const nlohmann::basic_json<> &MonsterJson, string whatAreLookedFor);

};

#endif //ANOTHER_DND_SIMULATOR_CREATURE_H

