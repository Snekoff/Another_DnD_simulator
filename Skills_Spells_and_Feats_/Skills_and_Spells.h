#pragma once
#include <iostream>
#include "../Character/UsefulFunctions.h"

#ifndef ANOTHER_DND_SIMULATOR_SKILLS_AND_SPELLS_H
#define ANOTHER_DND_SIMULATOR_SKILLS_AND_SPELLS_H
class Spell {
 private:
  std::string name;
  int spell_level;
 public:
  Spell();

  ~Spell();

  int get();

  void set();

};
#endif //ANOTHER_DND_SIMULATOR_SKILLS_AND_SPELLS_H

