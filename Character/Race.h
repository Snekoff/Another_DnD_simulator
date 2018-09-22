#pragma  once
#include <iostream>
#include <string>
#include "Skills_and_Spells.h"
#include "UsefulFunctions.h"

#ifndef ANOTHER_DND_SIMULATOR_RACE_H
#define ANOTHER_DND_SIMULATOR_RACE_H

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
  Race();

  ~Race();

  void set(int a);

  void set(int a, int b, int c, int d);

  virtual void Create(int sub_type, int a, int b, int c);

  int get(int w);

  void RaceFeature();

  void SetRaceAbilityBonus();

  void RaceAbilityBonus();
};

class Dragonborn : public Race {
 private:
  int subtype;
 public:
  Dragonborn();
  Dragonborn(int sub_type, int a, int b, int c);
  ~Dragonborn();
  void subRaceFeatures();

  void Create(int sub_type, int a, int b, int c) override;
};

class Dwarf : public Race {
 private:
  int subtype;
 public:
  Dwarf();
  Dwarf(int sub_type, int a, int b, int c);
  ~Dwarf();
  void subRaceFeatures();

  void Create(int sub_type, int a, int b, int c) override;
};

class Elf : public Race {
 private:
  int subtype;
 public:
  Elf();
  Elf(int sub_type, int a, int b, int c);
  ~Elf();
  void subRaceFeatures();

  void Create(int sub_type, int a, int b, int c) override;
};
class Gnome : public Race {
 private:
  int subtype;
 public:
  Gnome();
  Gnome(int sub_type, int a, int b, int c);
  ~Gnome();
  void subRaceFeatures();

  void Create(int sub_type, int a, int b, int c) override;
};

class Goblin : public Race {
 private:
  int subtype;
 public:
  Goblin();
  Goblin(int sub_type, int a, int b, int c);
  ~Goblin();
  void subRaceFeatures();

  void Create(int sub_type, int a, int b, int c) override;
};

class Half_Elf : public Race {
 private:
  int subtype;
 public:
  Half_Elf();
  Half_Elf(int sub_type, int a, int b, int c);
  ~Half_Elf();
  void subRaceFeatures();

  void Create(int sub_type, int a, int b, int c) override;
};

class Half_Orc : public Race {
 private:
  int subtype;
 public:
  Half_Orc();
  Half_Orc(int sub_type, int a, int b, int c);
  ~Half_Orc();
  void subRaceFeatures();

  void Create(int sub_type, int a, int b, int c) override;
};

class Halfling : public Race {
 private:
  int subtype;
 public:
  Halfling();
  Halfling(int sub_type, int a, int b, int c);
  ~Halfling();
  void subRaceFeatures();

  void Create(int sub_type, int a, int b, int c) override;
};

class Human : public Race {
 private:
  int subtype;
 public:
  Human();
  Human(int sub_type, int a, int b, int c);
  ~Human();
  void subRaceFeatures();

  void Create(int sub_type, int a, int b, int c) override;
};
class Lizardfolk : public Race {
 private:
  int subtype;
 public:
  Lizardfolk();
  Lizardfolk(int sub_type, int a, int b, int c);
  ~Lizardfolk();
  void subRaceFeatures();

  void Create(int sub_type, int a, int b, int c) override;
};

class Tiefling : public Race {
 private:
  int subtype;
 public:
  Tiefling();
  Tiefling(int sub_type, int a, int b, int c);
  ~Tiefling();
  void subRaceFeatures();

  void Create(int sub_type, int a, int b, int c) override;
};

#endif //ANOTHER_DND_SIMULATOR_RACE_CLASS_BACKGROUND_H

