#pragma once
#ifndef ANOTHER_DND_SIMULATOR_MONSTER_H
#define ANOTHER_DND_SIMULATOR_MONSTER_H
#include "../Character/character.h"

const int kMonster_NUM = 50;
const int kMonster_Parameter_NUM = 6;

struct Exsisting_Monsters{
  std::string All_s[kMonster_NUM] = {};
  int All_i[kMonster_NUM][kMonster_Parameter_NUM] = {};
};

class Monster : public Character {
 private:
  int monster_type;
  int experience;
 public:
  Monster(int type_, int level_);

  Monster(int type_,int level_, int hp, int armor_class_);

  int Get(int w) override;

  ~Monster();

  bool Load(int a[]);
};

#endif //ANOTHER_DND_SIMULATOR_MONSTER_H
