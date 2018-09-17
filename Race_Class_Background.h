#pragma  once
//#include "Race_Class_Background.cpp"

#ifndef ANOTHER_DND_SIMULATOR_RACE_CLASS_BACKGROUND_H
#define ANOTHER_DND_SIMULATOR_RACE_CLASS_BACKGROUND_H

#endif //ANOTHER_DND_SIMULATOR_RACE_CLASS_BACKGROUND_H


#include <iostream>
#include <string>
#include "Skills_and_Spells.h"
#include "UsefulFunctions.h"

//
class Race {
 private:
 protected:
  int type;
  int height, weight, age;
  int Str, Dex, Con, Int, Wis, Cha;
  int Movement;
  int Size; // 0 - small,1 - medium, etc.
  int Darkvision;
  int damage_resistance;

  Spell spell;
  std::string raceFeatures;
  Existing_Types E;
  // Movement,Size,Darkvision,skill like firebreath,fits,type of damage resistance,Languages//
 public:
  Race() = default;

  ~Race() = default;

  void set(int a) ;

  void set(int a, int b, int c, int d) ;

  void Create(int sub_type,int a, int b, int c);

  int get(int w) ;

  void RaceFeature() ;

  void SetRaceAbilityBonus() ;

  void RaceAbilityBonus();
};

class Dragonborn : public Race {
 private:
  int subtype;
 public:
  Dragonborn() : Race() { }
  Dragonborn(int sub_type,int a, int b, int c);
  ~Dragonborn() = default;
  void subRaceFeatures();

  void Create(int sub_type,int a, int b, int c);
};

class Dwarf  : public Race {
 private:
  int subtype;
 public:
  Dwarf() : Race() { }
  Dwarf(int sub_type,int a, int b, int c);
  ~Dwarf() = default;
  void subRaceFeatures();

  void Create(int sub_type,int a, int b, int c);
};

class Elf  : public Race {
 private:
  int subtype;
 public:
  Elf():Race(){}
  Elf(int sub_type,int a, int b, int c);
  ~Elf() = default;
  void subRaceFeatures() ;

  void Create(int sub_type,int a, int b, int c);
};
class Gnome  : public Race {
 private:
  int subtype;
 public:
  Gnome():Race(){}
  Gnome(int sub_type,int a, int b, int c);
  ~Gnome() = default;
  void subRaceFeatures() ;

  void Create(int sub_type,int a, int b, int c);
};

class Goblin : public Race {
 private:
  int subtype;
 public:
  Goblin():Race(){}
  Goblin(int sub_type,int a, int b, int c);
  ~Goblin() = default;
  void subRaceFeatures() ;

  void Create(int sub_type,int a, int b, int c);
};

class Half_Elf : public Race {
 private:
  int subtype;
 public:
  Half_Elf():Race(){}
  Half_Elf(int sub_type,int a, int b, int c);
  ~Half_Elf() = default;
  void subRaceFeatures() ;

  void Create(int sub_type,int a, int b, int c);
};

class Half_Orc : public Race {
 private:
  int subtype;
 public:
  Half_Orc():Race(){}
  Half_Orc(int sub_type,int a, int b, int c);
  ~Half_Orc() = default;
  void subRaceFeatures() ;

  void Create(int sub_type,int a, int b, int c);
};

class Halfling : public Race {
 private:
  int subtype;
 public:
  Halfling():Race(){}
  Halfling(int sub_type,int a, int b, int c);
  ~Halfling() = default;
  void subRaceFeatures() ;

  void Create(int sub_type,int a, int b, int c);
};

class Human : public Race {
 private:
  int subtype;
 public:
  Human():Race(){}
  Human(int sub_type,int a, int b, int c);
  ~Human() = default;
  void subRaceFeatures() ;

  void Create(int sub_type,int a, int b, int c);
};
class Lizardfolk : public Race {
 private:
  int subtype;
 public:
  Lizardfolk():Race(){}
  Lizardfolk(int sub_type,int a, int b, int c);
  ~Lizardfolk() = default;
  void subRaceFeatures() ;

  void Create(int sub_type,int a, int b, int c);
};

class Tiefling : public Race {
 private:
  int subtype;
 public:
  Tiefling():Race(){}
  Tiefling(int sub_type,int a, int b, int c);
  ~Tiefling() = default;
  void subRaceFeatures();

  void Create(int sub_type,int a, int b, int c);
};

// &&&&&&&&^^%^#QQQQQQQQQQQQQQQQQQQ$$$$$$$$$$$$$$$$$$$$$$$##############EEEEEEEEEEEEEEEERRRRRRRRRRRRRRRREEWW
// factory