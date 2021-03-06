//
// MIT License
// Copyright (c) 2019 Snekoff. All rights reserved.
//

#pragma once

#include <iomanip>
#include <fstream>

#include "character/character.h"
#include "local_map/battleground.h"
#include "monsters/monster.h"
#include "local_map/local_map_user_usage.h"

#ifndef ANOTHER_DND_SIMULATOR_GAMEOFIMAGINATION_H
#define ANOTHER_DND_SIMULATOR_GAMEOFIMAGINATION_H

const int kOutput = 99;
const int kCharacter_Get_Bool_shift = 35;
const int kCharacter_get_fake_parameter = 24;

using json = nlohmann::json;
class Game {
 private:
  vector<Character*> characters;
  vector<Creature*> monsters_met;
  Random_Generator_ * Rand_gen;
  Allowance * allowance;
 public:
  Game();

  Game(int start, int journey);

  ~Game();

  void Party_create(Random_Generator_ *Rand_gen);

  vector<int> Set_Character_Abilities(vector<int> abilities);

  bool is_Created();

  void Character_Show_Parameters(int who);

  bool Party_Save();

  bool Party_Load();

};

#endif //ANOTHER_DND_SIMULATOR_GAMEOFIMAGINATION_H
