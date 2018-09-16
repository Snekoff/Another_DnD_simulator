//
// Created by Oleg on 14.09.2018.
//
#include <iostream>
#include "UsefulFunctions.h"
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
  /*acrobatics 0,animalHandling 1,arcana 2,athletics 3,deception 4,
history 5,insight 6,intimidation 7,investigation 8,medicine 9,
nature 10,perception 11,performance 12,persuasion 13,religion 14,
sleightOfHand 15,stealth 16,survival 17*/
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
    int skill_1 = 0,skill_2 = 0,skill_3 = 0,skill_4 = 0; //tmp
    if(type == 0){
      printf("%s \n", "Choose two from Animal Handling(0), Athletic(1), Intimidation(2), Nature(3), "
                      "Perception and Survival(4)");
      std::cin >> skill_1 >> skill_2;
      skill_1 = Correctness_of_input(skill_1,0,4);
      skill_2 = Correctness_of_input(skill_2,0,4);
      while(skill_2 == skill_1) {
        skill_2 = -1;
        skill_2 = Correctness_of_input(skill_2,0,4);
      }
      int skills_identifier[5] = {1,3,7,10,17};
      s[skills_identifier[skill_1]] = 1;
      s[skills_identifier[skill_2]] = 1;
    }
    else if(type == 1){
      printf("%s \n", "Choose any three (0-18)");
      std::cin >> skill_1 >> skill_2 >> skill_3;
      skill_1 = Correctness_of_input(skill_1,0,18);
      skill_2 = Correctness_of_input(skill_2,0,18);
      while(skill_2 == skill_1) {
        skill_2 = -1;
        skill_2 = Correctness_of_input(skill_2,0,18);
      }
      skill_3 = Correctness_of_input(skill_3,0,18);
      while(skill_2 == skill_3 || skill_1 == skill_3) {
        skill_3 = -1;
        skill_3 = Correctness_of_input(skill_3,0,18);
      }
      s[skill_1] = 1;
      s[skill_2] = 1;
      s[skill_3] = 1;
    }
    else if(type == 2){
      printf("%s \n", "Choose two from History(0), Insight(1), Medicine(2), Persuasion(3) and Religion(4)");
      std::cin >> skill_1 >> skill_2 ;
      skill_1 = Correctness_of_input(skill_1,0,4);
      skill_2 = Correctness_of_input(skill_2,0,4);
      while(skill_2 == skill_1) {
        skill_2 = -1;
        skill_2 = Correctness_of_input(skill_2,0,4);
      }
      int skills_identifier[5] = {5,6,9,13,14};
      s[skills_identifier[skill_1]] = 1;
      s[skills_identifier[skill_2]] = 1;
    }
    else if(type == 3){
      printf("%s \n", "Choose two from Arcana(0), Animal Handling(1), Insight(2), Medicine(3), Nature(4), "
                      "Perception(5), Religion(6) and Survival(7)");
      std::cin >> skill_1 >> skill_2;
      skill_1 = Correctness_of_input(skill_1,0,7);
      skill_2 = Correctness_of_input(skill_2,0,7);
      while(skill_2 == skill_1) {
        skill_2 = -1;
        skill_2 = Correctness_of_input(skill_2,0,7);
      }
      int skills_identifier[8] = {3,1,6,9,10,11,14,17};
      s[skills_identifier[skill_1]] = 1;
      s[skills_identifier[skill_2]] = 1;
    }
    else if(type == 4){
      printf("%s \n", "Choose two from Acrobatics(0), AnimalHandling(1), Athletics(2), History(3), Insight(4), "
                      "Intimidation(5), Perception(6) and Survival(7)");
      std::cin >> skill_1 >> skill_2;
      skill_1 = Correctness_of_input(skill_1,0,7);
      skill_2 = Correctness_of_input(skill_2,0,7);
      while(skill_2 == skill_1) {
        skill_2 = -1;
        skill_2 = Correctness_of_input(skill_2,0,7);
      }
      int skills_identifier[8] = {0,1,3,5,6,7,11,17};
      s[skills_identifier[skill_1]] = 1;
      s[skills_identifier[skill_2]] = 1;
    }
    else if(type == 5){
      printf("%s \n", "Choose two from Acrobatics(0), Athletics(1), History(2), Insight(3), Religion(4), "
                      "and Stealth(5)");
      std::cin >> skill_1 >> skill_2;
      skill_1 = Correctness_of_input(skill_1,0,5);
      skill_2 = Correctness_of_input(skill_2,0,5);
      while(skill_2 == skill_1) {
        skill_2 = -1;
        skill_2 = Correctness_of_input(skill_2,0,5);
      }
      int skills_identifier[6] = {0,3,5,6,14,17};
      s[skills_identifier[skill_1]] = 1;
      s[skills_identifier[skill_2]] = 1;
    }
    else if(type == 6){
      printf("%s \n", "Choose two from Athletics(0), Insight(1), Intimidation(2), Medicine(3), Persuasion(4), "
                      "and Religion(5)");
      std::cin >> skill_1 >> skill_2 ;
      skill_1 = Correctness_of_input(skill_1,0,5);
      skill_2 = Correctness_of_input(skill_2,0,5);
      while(skill_2 == skill_1) {
        skill_2 = -1;
        skill_2 = Correctness_of_input(skill_2,0,5);
      }
      int skills_identifier[6] = {3,6,7,9,14};
      s[skills_identifier[skill_1]] = 1;
      s[skills_identifier[skill_2]] = 1;
    }
    else if(type == 7){
      printf("%s \n", "Choose two from Animal Handling(0), Athletics(1), Insight(2), Investigation(3), Nature(4), "
                      "Perception(5), Stealth(6) and Survival(7)");
      std::cin >> skill_1 >> skill_2;
      skill_1 = Correctness_of_input(skill_1,0,7);
      skill_2 = Correctness_of_input(skill_2,0,7);
      while(skill_2 == skill_1) {
        skill_2 = -1;
        skill_2 = Correctness_of_input(skill_2,0,7);
      }
      int skills_identifier[8] = {1,3,6,8,10,11,16,17};
      s[skills_identifier[skill_1]] = 1;
      s[skills_identifier[skill_2]] = 1;
    }
    else if(type == 8){
      printf("%s \n", "Choose four from Acrobatics(0), Athletics(1), Deception(2), Insight(3), Intimidation(4), "
                      "Investigation(5), Perception(6), Performance(7), Persuasion(8), Sleight of Hand(9) "
                      "and Stealth(10)");
      std::cin >> skill_1 >> skill_2 >> skill_3 >> skill_4;
      skill_1 = Correctness_of_input(skill_1,0,10);
      skill_2 = Correctness_of_input(skill_2,0,10);
      while(skill_2 == skill_1) {
        skill_2 = -1;
        skill_2 = Correctness_of_input(skill_2,0,10);
      }
      skill_3 = Correctness_of_input(skill_3,0,10);
      while(skill_2 == skill_3 || skill_1 == skill_3) {
        skill_3 = -1;
        skill_3 = Correctness_of_input(skill_3,0,10);
      }
      skill_4 = Correctness_of_input(skill_4,0,10);
      while(skill_2 == skill_4 || skill_1 == skill_4 || skill_3 == skill_4) {
        skill_4 = -1;
        skill_4 = Correctness_of_input(skill_4,0,10);
      }
      int skills_identifier[11] = {0,3,4,6,7,8,11,12,13,15,16};
      s[skills_identifier[skill_1]] = 1;
      s[skills_identifier[skill_2]] = 1;
      s[skills_identifier[skill_3]] = 1;
      s[skills_identifier[skill_4]] = 1;
    }
    else if(type == 9){
      printf("%s \n", "Choose two from Arcana(0), Deception(1), Insight(2), Intimidation(3), Persuasion(4), "
                      "and Religion(5)");
      std::cin >> skill_1 >> skill_2;
      skill_1 = Correctness_of_input(skill_1,0,5);
      skill_2 = Correctness_of_input(skill_2,0,5);
      while(skill_2 == skill_1) {
        skill_2 = -1;
        skill_2 = Correctness_of_input(skill_2,0,5);
      }
      int skills_identifier[6] = {2,4,6,7,13,4};
      s[skills_identifier[skill_1]] = 1;
      s[skills_identifier[skill_2]] = 1;
    }
    else if(type == 10){
      printf("%s \n", "Choose two from Arcana(0), Deception(1), History(2), Intimidation(3), Investigation(4), "
                      "Nature(5), and Religion(6)");
      std::cin >> skill_1 >> skill_2;
      skill_1 = Correctness_of_input(skill_1,0,6);
      skill_2 = Correctness_of_input(skill_2,0,6);
      while(skill_2 == skill_1) {
        skill_2 = -1;
        skill_2 = Correctness_of_input(skill_2,0,6);
      }
      int skills_identifier[7] = {2,4,5,7,8,10,14};
      s[skills_identifier[skill_1]] = 1;
      s[skills_identifier[skill_2]] = 1;
    }
    else if(type == 11){
      printf("%s \n", "Choose two from Arcana(0), History(1), Insight(2), Investigation(3), Medicine(4), "
                      "and Religion(5)");
      std::cin >> skill_1 >> skill_2 ;
      skill_1 = Correctness_of_input(skill_1,0,5);
      skill_2 = Correctness_of_input(skill_2,0,5);
      while(skill_2 == skill_1) {
        skill_2 = -1;
        skill_2 = Correctness_of_input(skill_2,0,5);
      }
      int skills_identifier[6] = {2,5,6,8,9,14};
      s[skills_identifier[skill_1]] = 1;
      s[skills_identifier[skill_2]] = 1;
    }
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