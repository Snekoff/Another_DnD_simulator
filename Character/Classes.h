
#ifndef ANOTHER_DND_SIMULATOR_CLASSES_H
#define ANOTHER_DND_SIMULATOR_CLASSES_H

#include <iostream>
#include "UsefulFunctions.h"
const int kClass_Num = 12;
const int kAttributes_Num = 20;
const int kArmor_Weapon_proficiencies_Num = 7;
const int kSaving_Throw_shift = 23;
const int kArmor_Weapon_shift = 29;
const int kClassType_get_shift = 21;

struct Existing_classes{ // classes simplified! (weapon proficiencies)
  int Class_atribute[kClass_Num][kAttributes_Num] = {{12,1,0,0,0,0,0,1,0,1,0,0,0,1,1,0,1,0,1,0},{8,0,0,0,0,0,1,0,1,0,0,0,1,1,0,0,1,1,1,0},
                                {8,0,0,0,0,1,0,0,0,0,0,1,1,1,1,0,1,0,0,0},{8,0,0,0,0,1,0,0,0,0,1,1,0,1,1,0,1,1,0,0},
                                {10,0,0,0,0,0,0,1,0,1,0,0,0,1,1,1,1,0,1,0},{8,0,1,0,0,1,0,1,1,0,0,0,0,0,0,0,1,0,0,0},
                                {10,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,0,1,0},{10,0,1,0,0,1,0,1,1,0,0,0,0,1,1,0,1,0,1,0},
                                {8,0,1,0,0,0,0,0,1,0,1,0,0,1,0,0,1,1,1,0},{6,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1,1,0,0},
                                {8,0,0,0,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0},{6,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0}};
  //hit_dice(0), primary ability (1-6) , saving_throw_proficiencies (7-12) , armor_and_weapon_proficiencies (13-19)
};

class Class {
 protected:
  int type;
  int hit_dice;
  bool primary_ability[kAbilities_Num];
  bool saving_throw_proficiencies[kAbilities_Num];
  bool armor_and_weapon_proficiencies[kArmor_Weapon_proficiencies_Num];
  int skills[kSkills_Num];
  /*acrobatics 0,animalHandling 1,arcana 2,athletics 3,deception 4,
history 5,insight 6,intimidation 7,investigation 8,medicine 9,
nature 10,perception 11,performance 12,persuasion 13,religion 14,
sleightOfHand 15,stealth 16,survival 17*/
  int architype;
 public:
  Class();

  Class(int type_, bool *skills_b[]);
  ~Class();

  virtual void set(int type_, bool *skills_b[]);

  virtual void set_architype();

  virtual void set_skills(bool *skills_b[]);

  bool Load(int type_, bool b[], int architype_);

  virtual int get(int what);

  bool get_bool(int what);
};

class MultiClass : public Class {
 private:
  int multitype;
 public:
  MultiClass();
  ~MultiClass();
  void subClassFeatures();
};

#endif //ANOTHER_DND_SIMULATOR_CLASSES_H
