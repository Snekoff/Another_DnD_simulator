
#include "interface_races_classes_background.h"
#include <iostream>
#include "Skills_and_Spells.cpp"
#include "UsefulFunctions.cpp"

class Race {
 private:
  int type;
 protected:
  int height, weight, age;
  int Str, Dex, Con, Int, Wis, Cha;
  Spell spell;
  std::string raceFeatures;
  // Abilities0-5,Movement,Size,Darkvision,skill like firebreath,fits,type of damage resistance,Languages//
 public:
  Race() {
    type = 0;
    height = 0;
    weight = 0;
    age = 0;
  }

  ~Race() {}

  virtual void set(int a) {
    type = a;
  }

  virtual void set(int a, int b, int c, int d) {}

  virtual int get() {}

  void raceFeature() {}
};

class SubRace : public Race {
 private:
  int subtype;
 public:
  void subRaceFeatures() {}
};

class Class {
 private:
  int type;
 protected:
  std::string features = "";
 public:
  Class() {}

  ~Class() {}

  virtual void set(int a) {}

  virtual void set(int a, int b, int c, int d) {}

  virtual int get() {}

  void ClassFeatures() {}
};

class SubClass : public Class {
 private:
  int subtype;
 public:
  void subClassFeatures() {}
};

