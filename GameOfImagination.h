#pragma once
#include "Character\character.h"
//#include "WorkWithJson.h"
#ifndef ANOTHER_DND_SIMULATOR_GAMEOFIMAGINATION_H
#define ANOTHER_DND_SIMULATOR_GAMEOFIMAGINATION_H

#endif //ANOTHER_DND_SIMULATOR_GAMEOFIMAGINATION_H

class Game {
 private:
  vector<Character*> characters;
 public:
  Game() = default;

  Game(int start, int journey);

  ~Game();

  void Character_create(Random_Generator_ * Rand_gen);

  bool is_Created();

  nlohmann::json * Party_Save();

  bool Party_Load(nlohmann::json party);

};