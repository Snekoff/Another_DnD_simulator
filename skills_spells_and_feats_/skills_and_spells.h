#pragma once
#include <iostream>
#include "../Character/common_functions.h"

#ifndef ANOTHER_DND_SIMULATOR_SKILLS_AND_SPELLS_H
#define ANOTHER_DND_SIMULATOR_SKILLS_AND_SPELLS_H
const int kSpell_Num = 1200;

struct Existing_Spells {
  std::string name_s[kSpell_Num] = {};
};

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

