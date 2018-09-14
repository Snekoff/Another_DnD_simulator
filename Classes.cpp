//
// Created by Oleg on 14.09.2018.
//
#include <iostream>
//#include "Classes.h"

struct Existing_classes{ // classes simplified!
  int Class_atribute[12][20] = {{12,1,0,0,0,0,0,1,0,1,0,0,0,1,1,0,1,0,1,0},{8,0,0,0,0,0,1,0,1,0,0,0,1,1,0,0,1,1,1,0},
                                {8,0,0,0,0,1,0,0,0,0,0,1,1,1,1,0,1,0,0,0},{8,0,0,0,0,1,0,0,0,0,1,1,0,1,1,0,1,1,0,0},
                                {10,1,0,0,0,0,0,1,0,1,0,0,0,1,1,1,1,0,1,0},{8,0,1,0,0,1,0,1,1,0,0,0,0,0,0,0,1,0,0,0},
                                {10,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,0,1,0},{10,0,1,0,0,1,0,1,1,0,0,0,0,1,1,0,1,0,1,0},
                                {8,0,1,0,0,0,0,0,1,0,1,0,0,1,0,0,1,1,1,0},{6,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1,1,0,0},
                                {8,0,0,0,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0},{6,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0}};
  //hit_dice(0), primary ability (1-6) , saving_throw_proficiencies (7-12) , armor_and_weapon_proficiencies (12-19)
};

//                                      str, dex, con, int, wis, cha

class Class {
 protected:
  int type;
  int hit_dice;
  bool primary_ability[6];
  bool saving_throw_proficiencies[6];
  bool armor_and_weapon_proficiencies[7];
  int s[18];
  std::string architype;
 public:
  Class() {
    type = 0;
    hit_dice = 0;
    for(int i = 0; i < 6;i++){
      primary_ability[i] = false;
      saving_throw_proficiencies[i] = false;
      armor_and_weapon_proficiencies[i] = false;
      s[i] = 0;
      s[i+6] = 0;
      s[i+12] = 0;
    }
    architype = "";
  }

  Class(int type_) {
    set(type_);
  }
  ~Class() = default;

  virtual void set(int type_) {
    Existing_classes E;
    type = type_;
    hit_dice = E.Class_atribute[type][0];
    for(int i = 0; i < 7;i++){
      if(E.Class_atribute[type][i+1] > 0 && i < 6) primary_ability[i] = true;
      if(E.Class_atribute[type][i+7] > 0 && i < 6) saving_throw_proficiencies[i] = true;
      if(E.Class_atribute[type][i+12] > 0) armor_and_weapon_proficiencies[i] = true;
    }
    set_skills();
    set_architype();
    architype = "";
  }

  virtual void set_architype() {
    if(type == -1){
      std::cout << "Choose your way:\n";
    }
  }

  virtual void set_skills(){

  }

  virtual int get(int what) {
    if(what == 0) { return type; }
    else if( 0 < what && what < 7) return primary_ability[what - 1];
    else if( 6 < what && what < 13) return saving_throw_proficiencies[what - 7];
    else if( 12 < what && what < 20) return armor_and_weapon_proficiencies[what - 13];
    else if(what == 20) return hit_dice;
    else if( 20 < what && what < 39) return s[what - 21];
    return -1;
  }

  void ClassFeatures() {}
};

class MultiClass : public Class {
 private:
  int multitype;
 public:
  MultiClass() : Class() {
    multitype = 0;
  }
  ~MultiClass() = default;
  void subClassFeatures() {}
};