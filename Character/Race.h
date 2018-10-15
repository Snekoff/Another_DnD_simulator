#pragma  once
#include <iostream>
#include <string>
#include "../Skills_Spells_and_Feats_/Skills_and_Spells.h"
#include "UsefulFunctions.h"

#ifndef ANOTHER_DND_SIMULATOR_RACE_H
#define ANOTHER_DND_SIMULATOR_RACE_H

class Race {
 private:
 protected:
  int type;
  int subtype;
  int height, weight, age;
  int Str, Dex, Con, Int, Wis, Cha;
  int Movement;// how many feets you can move (your speed)
  int Size; // 0 - small,1 - medium, etc.
  int Darkvision;//Darkvision.value means that you see in darkness up to "value" feets
  int damage_resistance;//You take half as much damage of this type
  std::string raceFeatures;
  Existing_Types E;
  // Movement,Size,Darkvision,skill like firebreath,fits,type of damage resistance,Languages//
 public:
  Race();

  ~Race();

  //void set(Random_Generator_ *Rand_gen, int a);

  void set(int type_, int height_, int weight_, int age_);

  virtual void Create(int sub_type, int height_, int weight_, int age_);

  int get(int what);

  void SetRaceAbilityBonus();

  void RaceAbilityBonus();

  void Size_Set();

  bool Load(int parameters_i[]);

  virtual void subRaceFeatures();

};

class Dragonborn : public Race {
 private:
  //int subtype;
 public:
  Dragonborn();
  Dragonborn(int sub_type, int height_, int weight_, int age_);
  ~Dragonborn();
  void subRaceFeatures();

  void Create(int sub_type, int height_, int weight_, int age_) override;
};

class Dwarf : public Race {
 private:
  //int subtype;
 public:
  Dwarf();
  Dwarf(int sub_type, int height_, int weight_, int age_);
  ~Dwarf();
  void subRaceFeatures();

  void Create(int sub_type, int height_, int weight_, int age_) override;
};

class Elf : public Race {
 private:
  //int subtype;
 public:
  Elf();
  Elf(int sub_type, int height_, int weight_, int age_);
  ~Elf();
  void subRaceFeatures();

  void Create(int sub_type, int height_, int weight_, int age_) override;
};

class Gnome : public Race {
 private:
  //int subtype;
 public:
  Gnome();
  Gnome(int sub_type, int height_, int weight_, int age_);
  ~Gnome();
  void subRaceFeatures();

  void Create(int sub_type, int height_, int weight_, int age_) override;
};

class Goblin : public Race {
 private:
  //int subtype;
 public:
  Goblin();
  Goblin(int sub_type, int height_, int weight_, int age_);
  ~Goblin();
  void subRaceFeatures();

  void Create(int sub_type, int height_, int weight_, int age_) override;
};

class Half_Elf : public Race {
 private:
  //int subtype;
 public:
  Half_Elf();
  Half_Elf(int sub_type, int height_, int weight_, int age_);
  ~Half_Elf();
  void subRaceFeatures();

  void Create(int sub_type, int height_, int weight_, int age_) override;
};

class Half_Orc : public Race {
 private:
  //int subtype;
 public:
  Half_Orc();
  Half_Orc(int sub_type, int height_, int weight_, int age_);
  ~Half_Orc();
  void subRaceFeatures();

  void Create(int sub_type, int height_, int weight_, int age_) override;
};

class Halfling : public Race {
 private:
  //int subtype;
 public:
  Halfling();
  Halfling(int sub_type, int height_, int weight_, int age_);
  ~Halfling();
  void subRaceFeatures();

  void Create(int sub_type, int height_, int weight_, int age_) override;
};

class Human : public Race {
 private:
  //int subtype;
 public:
  Human();
  Human(int sub_type, int height_, int weight_, int age_);
  ~Human();
  void subRaceFeatures();

  void Create(int sub_type, int height_, int weight_, int age_) override;
};
class Lizardfolk : public Race {
 private:
  //int subtype;
 public:
  Lizardfolk();
  Lizardfolk(int sub_type, int height_, int weight_, int age_);
  ~Lizardfolk();
  void subRaceFeatures();

  void Create(int sub_type, int height_, int weight_, int age_) override;
};

class Tiefling : public Race {
 private:
  //int subtype;
 public:
  Tiefling();
  Tiefling(int sub_type, int height_, int weight_, int age_);
  ~Tiefling();
  void subRaceFeatures();

  void Create(int sub_type, int height_, int weight_, int age_) override;
};

template<class C>
class Concrete_Factory {
 public:
  C *Create(int subtype) {
    return new C(subtype, 0, 0, 0);
  }

  C *Load() {
    return new C();
  }
};

class Race_Factory {
 public:
  Race *Create(int type, int subtype) {
    if (type == 0) {
      Concrete_Factory<Dragonborn> Dragonborn_;
      return Dragonborn_.Create(subtype);
    } else if (type == 1) {
      Concrete_Factory<Dwarf> Dwarf_;
      return Dwarf_.Create(subtype);
    } else if (type == 2) {
      Concrete_Factory<Elf> Elf_;
      return Elf_.Create(subtype);
    } else if (type == 3) {
      Concrete_Factory<Gnome> Gnome_;
      return Gnome_.Create(subtype);
    } else if (type == 4) {
      Concrete_Factory<Goblin> Goblin_;
      return Goblin_.Create(subtype);
    } else if (type == 5) {
      Concrete_Factory<Half_Elf> Half_Elf_;
      return Half_Elf_.Create(subtype);
    } else if (type == 6) {
      Concrete_Factory<Half_Orc> Half_Orc_;
      return Half_Orc_.Create(subtype);
    } else if (type == 7) {
      Concrete_Factory<Halfling> Halfling_;
      return Halfling_.Create(subtype);
    } else if (type == 8) {
      Concrete_Factory<Human> Human_;
      return Human_.Create(subtype);
    } else if (type == 9) {
      Concrete_Factory<Lizardfolk> Lizardfolk_;
      return Lizardfolk_.Create(subtype);
    } else if (type == 10) {
      Concrete_Factory<Tiefling> Tiefling_;
      return Tiefling_.Create(subtype);
    }
    return new Race();
  }

  Race *Load(int type) {
    if (type == 0) {
      Concrete_Factory<Dragonborn> Dragonborn_;
      return Dragonborn_.Load();
    } else if (type == 1) {
      Concrete_Factory<Dwarf> Dwarf_;
      return Dwarf_.Load();
    } else if (type == 2) {
      Concrete_Factory<Elf> Elf_;
      return Elf_.Load();
    } else if (type == 3) {
      Concrete_Factory<Gnome> Gnome_;
      return Gnome_.Load();
    } else if (type == 4) {
      Concrete_Factory<Goblin> Goblin_;
      return Goblin_.Load();
    } else if (type == 5) {
      Concrete_Factory<Half_Elf> Half_Elf_;
      return Half_Elf_.Load();
    } else if (type == 6) {
      Concrete_Factory<Half_Orc> Half_Orc_;
      return Half_Orc_.Load();
    } else if (type == 7) {
      Concrete_Factory<Halfling> Halfling_;
      return Halfling_.Load();
    } else if (type == 8) {
      Concrete_Factory<Human> Human_;
      return Human_.Load();
    } else if (type == 9) {
      Concrete_Factory<Lizardfolk> Lizardfolk_;
      return Lizardfolk_.Load();
    } else if (type == 10) {
      Concrete_Factory<Tiefling> Tiefling_;
      return Tiefling_.Load();
    }
    return new Race();
  }
};
#endif //ANOTHER_DND_SIMULATOR_RACE_CLASS_BACKGROUND_H

