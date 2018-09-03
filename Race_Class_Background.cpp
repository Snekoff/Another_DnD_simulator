
#include "interface_races_classes_background.h"
#include <iostream>
#include "Skills_and_Spells.cpp"
#include "UsefulFunctions.cpp"
Existing_Types E;

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

  virtual void set(int a, int b, int c, int d) {
    type = a;
    height = b;
    weight = c;
    age = d;
    SetRaceAbilityBonus();
    RaceAbilityBonus();
  }

  virtual int get() {}

  void RaceFeature() {}

  void SetRaceAbilityBonus() {
    int a, b;
    if (type < 15 || (type > 19 && type != 25 && type != 37)) {// 15-19(3)  25(2) 37(Dex or Cha)
      printf("%s \n", "Your type got non flexible ability bonuses");
    } else if (type == 25) {
      printf("%s \n", "type two most wanted abilities to improve (1 - 6)");
      std::cin >> a >> b;
      a = Correctness(a, 1, 6);
      b = Correctness(b, 1, 6);
      E.race_ability_bonus[a - 1][type] += 1;
      E.race_ability_bonus[b - 1][type] += 1;
    } else if (type == 37) {
      printf("%s \n", "Choose only one ability Dexterity(2) or Charisma(6) )");
      std::cin >> a;
      while (a != 2 && a != 6) {
        printf("%s \n", "Choose only one ability Dexterity(2) or Charisma(6) )");
        std::cin >> a;
        E.race_ability_bonus[a - 1][type] += 1;
      }
    } else {
      printf("%s \n", "type two most wanted abilities to improve (1 - 6)");
      std::cin >> a >> b;
      a = Correctness(a, 1, 6);
      b = Correctness(b, 1, 6);
      while (a - 1 == 5 || b - 1 == 5) {
        printf("%s \n", "Your charisma is already raised, choose another one");
        std::cin >> a >> b;
        a = Correctness(a, 1, 6);
        b = Correctness(b, 1, 6);
      }
      E.race_ability_bonus[a - 1][type] += 1;
      E.race_ability_bonus[b - 1][type] += 1;
    }
  }

  void RaceAbilityBonus(){
    Str = E.race_ability_bonus[0][type];
    Dex = E.race_ability_bonus[1][type];
    Con = E.race_ability_bonus[2][type];
    Int = E.race_ability_bonus[3][type];
    Wis = E.race_ability_bonus[4][type];
    Cha = E.race_ability_bonus[5][type];
  }
};

class Dragonborn : public Race {
 private:
  int subtype;
 public:
  Dragonborn():Race(){}
  ~Dragonborn(){}
  void subRaceFeatures() {}
};

class Dwarf  : public Race {
 private:
  int subtype;
 public:
  Dwarf():Race(){}
  ~Dwarf(){}
  void subRaceFeatures() {}
};

class Elf  : public Race {
 private:
  int subtype;
 public:
  Elf():Race(){}
  ~Elf(){}
  void subRaceFeatures() {}
};
class Gnome  : public Race {
 private:
  int subtype;
 public:
  Gnome():Race(){}
  ~Gnome(){}
  void subRaceFeatures() {}
};

class Goblin : public Race {
 private:
  int subtype;
 public:
  Goblin():Race(){}
  ~Goblin(){}
  void subRaceFeatures() {}
};

class Half_Elf : public Race {
 private:
  int subtype;
 public:
  Half_Elf():Race(){}
  ~Half_Elf(){}
  void subRaceFeatures() {}
};

class Half_Orc : public Race {
 private:
  int subtype;
 public:
  Half_Orc():Race(){}
  ~Half_Orc(){}
  void subRaceFeatures() {}
};

class Halfling : public Race {
 private:
  int subtype;
 public:
  Halfling():Race(){}
  ~Halfling(){}
  void subRaceFeatures() {}
};

class Human : public Race {
 private:
  int subtype;
 public:
  Human():Race(){}
  ~Human(){}
  void subRaceFeatures() {}
};
class Lizardfolk : public Race {
 private:
  int subtype;
 public:
  Lizardfolk():Race(){}
  ~Lizardfolk(){}
  void subRaceFeatures() {}
};

class Tiefling : public Race {
 private:
  int subtype;
 public:
  Tiefling():Race(){}
  ~Tiefling(){}
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

