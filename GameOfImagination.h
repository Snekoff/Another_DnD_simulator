#pragma once
#include "Character\character.h"
//#include "GameOfImagination.cpp"
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

  void Character_create();

  bool is_Created();
};