#pragma once
#include <iomanip>
#include <fstream>
#include "Character\character.h"
#include "json.hpp"
#ifndef ANOTHER_DND_SIMULATOR_GAMEOFIMAGINATION_H
#define ANOTHER_DND_SIMULATOR_GAMEOFIMAGINATION_H

#endif //ANOTHER_DND_SIMULATOR_GAMEOFIMAGINATION_H
using json = nlohmann::json;
class Game {
 private:
  vector<Character*> characters;
  Random_Generator_ * Rand_gen;
 public:
  Game() = default;

  Game(int start, int journey);

  ~Game();

  void Character_create(Random_Generator_ * Rand_gen);

  bool is_Created();

  bool Party_Save();

  bool Party_Load();

};