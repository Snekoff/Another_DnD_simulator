
#ifndef ANOTHER_DND_SIMULATOR_CLASSES_H
#define ANOTHER_DND_SIMULATOR_CLASSES_H

#include <iostream>
#include "UsefulFunctions.h"
const int kClass_Num = 12;
const int kAttributes_Num = 20;
const int kGetHealth_dice = 20;
const int kArmor_Weapon_proficiencies_Num = 7;
const int kSaving_Throw_shift = 22;
const int kArmor_Weapon_shift = 28;
const int kClassType_get_shift = 21;

struct Existing_classes{ // classes simplified! (weapon proficiencies)
  int Class_atribute[kClass_Num][kAttributes_Num] = {{12,1,0,0,0,0,0,1,0,1,0,0,0,1,1,0,1,0,1,0},{8,0,0,0,0,0,1,0,1,0,0,0,1,1,0,0,1,1,1,0},
                                {8,0,0,0,0,1,0,0,0,0,0,1,1,1,1,0,1,0,0,0},{8,0,0,0,0,1,0,0,0,0,1,1,0,1,1,0,1,1,0,0},
                                {10,0,0,0,0,0,0,1,0,1,0,0,0,1,1,1,1,0,1,0},{8,0,1,0,0,1,0,1,1,0,0,0,0,0,0,0,1,0,0,0},
                                {10,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,0,1,0},{10,0,1,0,0,1,0,1,1,0,0,0,0,1,1,0,1,0,1,0},
                                {8,0,1,0,0,0,0,0,1,0,1,0,0,1,0,0,1,1,1,0},{6,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1,1,0,0},
                                {8,0,0,0,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0},{6,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0}};
  //hit_dice(0), primary ability (1-6) , saving_throw_proficiencies (7-12) , armor_and_weapon_proficiencies (13-19)
  std::string skills_s[kSkills_Num] = {"acrobatics", "animal handling", "arcana", "athletics", "deception", "history",
                                       "insight", "intimidation", "investigation", "medicine", "nature", "perception",
                                       "performance", "persuasion", "religion", "sleight of hand", "stealth",
                                       "survival"};
  std::vector<std::vector<int>> skills_per_class_i = {{1, 3, 7, 10, 11, 17},
                                                      {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17},
                                                      {5, 6, 9, 13, 14}, {3, 1, 6, 9, 10, 11, 14, 17},
                                                      {0, 1, 3, 5, 6, 7, 11, 17}, {0, 3, 5, 6, 14, 17},
                                                      {3, 6, 7, 9, 14}, {1, 3, 6, 8, 10, 11, 16, 17},
                                                      {0, 3, 4, 6, 7, 8, 11, 12, 13, 15, 16}, {2, 4, 6, 7, 13, 15},
                                                      {2, 4, 5, 7, 8, 10, 14}, {2, 5, 6, 8, 9, 14}};
  int fake_parameter = 0;// to avoid IDE warnings
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
  int archetype;
 public:
  Class();

  Class(Allowance * alowance, int type_, std::vector<bool> skills_b);
  ~Class();

  virtual void set(Allowance * alowance, int type_, std::vector<bool> skills_b);

  virtual void set_archetype();

  virtual void set_skills(std::vector<bool> skills_b);

  int Had_Skill_Been_Chosen(std::vector<bool> skills_b, std::vector<int> skills_access, int skill_1);
  int Had_Skill_Been_Chosen(std::vector<bool> skills_b, std::vector<int> skills_access, int skill_1, int skill_2);
  int Had_Skill_Been_Chosen(std::vector<bool> skills_b, std::vector<int> skills_access, int skill_1, int skill_2, int skill_3);
  int Had_Skill_Been_Chosen(std::vector<bool> skills_b, std::vector<int> skills_access, int skill_1, int skill_2, int skill_3, int skill_4);

  bool Load(int type_, bool b[], int archetype_);

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
