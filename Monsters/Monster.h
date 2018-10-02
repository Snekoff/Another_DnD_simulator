
#ifndef ANOTHER_DND_SIMULATOR_MONSTER_H
#define ANOTHER_DND_SIMULATOR_MONSTER_H
#include "../Character/character.h"
class Monster : public Character {
 private:
  int monster_type;
 public:
  Monster(int type_, int level_);

  Monster(int type_,int level_, int hp, int armor_class_);

  ~Monster();
};

#endif //ANOTHER_DND_SIMULATOR_MONSTER_H
