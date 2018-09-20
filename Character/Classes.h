//
// Created by Oleg on 14.09.2018.
//

#ifndef ANOTHER_DND_SIMULATOR_CLASSES_H
#define ANOTHER_DND_SIMULATOR_CLASSES_H

#include <iostream>

class Class {
 protected:
  int type;
  int hit_dice;
  bool primary_ability[6];
  bool saving_throw_proficiencies[6];
  bool armor_and_weapon_proficiencies[6];
  int s[18];
  std::string architype;
 public:
  Class();

  Class(int type_,bool * s_b[]);

  ~Class() = default;

  virtual void set(int type_,bool * s_b[]);

  virtual void set_architype();

  virtual void set_skills(bool * s_b[]);

  virtual int get(int what);
};

#endif //ANOTHER_DND_SIMULATOR_CLASSES_H
