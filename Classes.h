//
// Created by Oleg on 14.09.2018.
//

#ifndef ANOTHER_DND_SIMULATOR_CLASSES_H
#define ANOTHER_DND_SIMULATOR_CLASSES_H

class Class {
 protected:
  int type;
  int hit_dice;
  bool primary_ability[6];
  bool saving_throw_proficiencies[6];
  bool armor_and_weapon_proficiencies[6];
  int s[18];
 public:
  Class();

  ~Class() = default;

  virtual void set(int a);

  virtual void set(int a, int b, int c, int d);

  virtual int get();

  void ClassFeatures();
};

#endif //ANOTHER_DND_SIMULATOR_CLASSES_H
