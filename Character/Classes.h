
#ifndef ANOTHER_DND_SIMULATOR_CLASSES_H
#define ANOTHER_DND_SIMULATOR_CLASSES_H

#include <iostream>
#include "UsefulFunctions.h"

struct Existing_classes{ // classes simplified!
  int Class_atribute[12][20] = {{12,1,0,0,0,0,0,1,0,1,0,0,0,1,1,0,1,0,1,0},{8,0,0,0,0,0,1,0,1,0,0,0,1,1,0,0,1,1,1,0},
                                {8,0,0,0,0,1,0,0,0,0,0,1,1,1,1,0,1,0,0,0},{8,0,0,0,0,1,0,0,0,0,1,1,0,1,1,0,1,1,0,0},
                                {10,1,0,0,0,0,0,1,0,1,0,0,0,1,1,1,1,0,1,0},{8,0,1,0,0,1,0,1,1,0,0,0,0,0,0,0,1,0,0,0},
                                {10,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,0,1,0},{10,0,1,0,0,1,0,1,1,0,0,0,0,1,1,0,1,0,1,0},
                                {8,0,1,0,0,0,0,0,1,0,1,0,0,1,0,0,1,1,1,0},{6,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1,1,0,0},
                                {8,0,0,0,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0},{6,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0}};
  //hit_dice(0), primary ability (1-6) , saving_throw_proficiencies (7-12) , armor_and_weapon_proficiencies (12-19)
};

class Class {
 protected:
  int type;
  int hit_dice;
  bool primary_ability[6];
  bool saving_throw_proficiencies[6];
  bool armor_and_weapon_proficiencies[7];
  int s[18];
  /*acrobatics 0,animalHandling 1,arcana 2,athletics 3,deception 4,
history 5,insight 6,intimidation 7,investigation 8,medicine 9,
nature 10,perception 11,performance 12,persuasion 13,religion 14,
sleightOfHand 15,stealth 16,survival 17*/
  int architype;
 public:
  Class();

  Class(int type_, bool *s_b[]);
  ~Class();

  virtual void set(int type_, bool *s_b[]);

  virtual void set_architype();

  virtual void set_skills(bool *s_b[]);

  bool Load(int a, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11, int a12, int a13, int a14);

  virtual int get(int what);

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
