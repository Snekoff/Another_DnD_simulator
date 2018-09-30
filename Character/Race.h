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
  int subtype;
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

  void set(Random_Generator_ *Rand_gen, int a);

  void set(int a, int b, int c, int d);

  virtual void Create(int sub_type, int a, int b, int c);

  int get(int w);

  void RaceFeature();

  void SetRaceAbilityBonus();

  void RaceAbilityBonus();

  void Size_Set();

  bool Load(int a[]);

};

class Dragonborn : public Race {
 private:
  //int subtype;
 public:
  Dragonborn();
  Dragonborn(int sub_type, int a, int b, int c);
  ~Dragonborn();
  void subRaceFeatures();

  void Create(int sub_type, int a, int b, int c) override;
};

class Dwarf : public Race {
 private:
  //int subtype;
 public:
  Dwarf();
  Dwarf(int sub_type, int a, int b, int c);
  ~Dwarf();
  void subRaceFeatures();

  void Create(int sub_type, int a, int b, int c) override;
};

class Elf : public Race {
 private:
  //int subtype;
 public:
  Elf();
  Elf(int sub_type, int a, int b, int c);
  ~Elf();
  void subRaceFeatures();

  void Create(int sub_type, int a, int b, int c) override;
};

class Gnome : public Race {
 private:
  //int subtype;
 public:
  Gnome();
  Gnome(int sub_type, int a, int b, int c);
  ~Gnome();
  void subRaceFeatures();

  void Create(int sub_type, int a, int b, int c) override;
};

class Goblin : public Race {
 private:
  //int subtype;
 public:
  Goblin();
  Goblin(int sub_type, int a, int b, int c);
  ~Goblin();
  void subRaceFeatures();

  void Create(int sub_type, int a, int b, int c) override;
};

class Half_Elf : public Race {
 private:
  //int subtype;
 public:
  Half_Elf();
  Half_Elf(int sub_type, int a, int b, int c);
  ~Half_Elf();
  void subRaceFeatures();

  void Create(int sub_type, int a, int b, int c) override;
};

class Half_Orc : public Race {
 private:
  //int subtype;
 public:
  Half_Orc();
  Half_Orc(int sub_type, int a, int b, int c);
  ~Half_Orc();
  void subRaceFeatures();

  void Create(int sub_type, int a, int b, int c) override;
};

class Halfling : public Race {
 private:
  //int subtype;
 public:
  Halfling();
  Halfling(int sub_type, int a, int b, int c);
  ~Halfling();
  void subRaceFeatures();

  void Create(int sub_type, int a, int b, int c) override;
};

class Human : public Race {
 private:
  //int subtype;
 public:
  Human();
  Human(int sub_type, int a, int b, int c);
  ~Human();
  void subRaceFeatures();

  void Create(int sub_type, int a, int b, int c) override;
};
class Lizardfolk : public Race {
 private:
  //int subtype;
 public:
  Lizardfolk();
  Lizardfolk(int sub_type, int a, int b, int c);
  ~Lizardfolk();
  void subRaceFeatures();

  void Create(int sub_type, int a, int b, int c) override;
};

class Tiefling : public Race {
 private:
  //int subtype;
 public:
  Tiefling();
  Tiefling(int sub_type, int a, int b, int c);
  ~Tiefling();
  void subRaceFeatures();

  void Create(int sub_type, int a, int b, int c) override;
};

class Dragonborn_Factory {
 public:
  Dragonborn *Create(int subtype) {
    return new Dragonborn(subtype, 0, 0, 0);
  }
};
class Dwarf_Factory {
 public:
  Dwarf *Create(int subtype) {
    return new Dwarf(subtype, 0, 0, 0);
  }
};
class Elf_Factory {
 public:
  Elf *Create(int subtype) {
    return new Elf(subtype, 0, 0, 0);
  }
};
class Gnome_Factory {
 public:
  Gnome *Create(int subtype) {
    return new Gnome(subtype, 0, 0, 0);
  }
};
class Goblin_Factory {
 public:
  Goblin *Create(int subtype) {
    return new Goblin(subtype, 0, 0, 0);
  }
};
class Half_Elf_Factory {
 public:
  Half_Elf *Create(int subtype) {
    return new Half_Elf(subtype, 0, 0, 0);
  }
};
class Half_Orc_Factory {
 public:
  Half_Orc *Create(int subtype) {
    return new Half_Orc(subtype, 0, 0, 0);
  }
};
class Halfling_Factory {
 public:
  Halfling *Create(int subtype) {
    return new Halfling(subtype, 0, 0, 0);
  }
};
class Human_Factory {
 public:
  Human *Create(int subtype) {
    return new Human(subtype, 0, 0, 0);
  }
};
class Lizardfolk_Factory {
 public:
  Lizardfolk *Create(int subtype) {
    return new Lizardfolk(subtype, 0, 0, 0);
  }
};
class Tiefling_Factory {
 public:
  Tiefling *Create(int subtype) {
    return new Tiefling(subtype, 0, 0, 0);
  }
};

class Race_Factory {
 public:
  Race *Create(int type, int subtype) {
    if (type == 0) {
      Dragonborn_Factory Dragonborn_;
      return Dragonborn_.Create(subtype);
    }
    else if (type == 1) {
      Dwarf_Factory Dwarf_;
      return Dwarf_.Create(subtype);
    }
    else if (type == 2) {
      Elf_Factory Elf_;
      return Elf_.Create(subtype);
    }
    else if (type == 3) {
      Gnome_Factory Gnome_;
      return Gnome_.Create(subtype);
    }
    else if (type == 4) {
      Goblin_Factory Goblin_;
      return Goblin_.Create(subtype);
    }
    else if (type == 5) {
      Half_Elf_Factory Half_Elf_;
      return Half_Elf_.Create(subtype);
    }
    else if (type == 6) {
      Half_Orc_Factory Half_Orc_;
      return Half_Orc_.Create(subtype);
    }
    else if (type == 7) {
      Halfling_Factory Halfling_;
      return Halfling_.Create(subtype);
    }
    else if (type == 8) {
      Human_Factory Human_;
      return Human_.Create(subtype);
    }
    else if (type == 9) {
      Lizardfolk_Factory Lizardfolk_;
      return Lizardfolk_.Create(subtype);
    }
    else if (type == 10) {
      Tiefling_Factory Tiefling_;
      return Tiefling_.Create(subtype);
    }
    return new Race();
  }
};
#endif //ANOTHER_DND_SIMULATOR_RACE_CLASS_BACKGROUND_H

