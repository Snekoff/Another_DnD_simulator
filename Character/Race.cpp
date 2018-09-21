
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
  Race() {
    Str = 0;
    Dex = 0;
    Con = 0;
    Int = 0;
    Wis = 0;
    Cha = 0;
    type = 0;
    height = 0;
    weight = 0;
    age = 0;
    Movement = 0;
    Size = 0;
    Darkvision = 0;
    damage_resistance = 0;
  }

  ~Race() = default;

  void set(int a) {
    type = a;
    height = Random_Generator(E.minHeight[type], E.maxHeight[type]);
    weight = Random_Generator(E.minWeight[type], E.maxWeight[type]);
    age = Random_Generator(E.minAge[type], E.maxAge[type]);
  }

  void set(int a, int b, int c, int d) {
    type = a;
    height = b;
    weight = c;
    age = d;
    SetRaceAbilityBonus();
    RaceAbilityBonus();
  }

  void Create(int sub_type, int a, int b, int c) {
    type = sub_type;
    //subtype = sub_type;
    height = a;
    weight = b;
    age = c;
    //subRaceFeatures();
  }

  int get(int w) {
    if (w == 0) return type;
    else if (w == 1) return height;
    else if (w == 2) return weight;
    else if (w == 3) return age;
    else if (w == 4) return Str;
    else if (w == 5) return Dex;
    else if (w == 6) return Con;
    else if (w == 7) return Int;
    else if (w == 8) return Wis;
    else if (w == 9) return Cha;
    else if (w == 10) return Movement;
    else if (w == 11) return Size;
    else if (w == 12) return Darkvision;
    else if (w == 13) return damage_resistance;
    return -1;
  }

  void RaceFeature() {}

  void SetRaceAbilityBonus() {
    int a, b;
    if (type < 15 || (type > 19 && type != 25 && type != 37)) {// 15-19(3)  25(2) 37(Dex or Cha)
      printf("%s \n", "Your type got non flexible ability bonuses");
    } else if (type == 25) {
      printf("%s \n", "type two most wanted abilities to improve (1 - 6)");
      std::cin >> a >> b;
      a = Correctness_of_input(a, 1, 6);
      b = Correctness_of_input(b, 1, 6);
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
      a = Correctness_of_input(a, 1, 6);
      b = Correctness_of_input(b, 1, 6);
      while (a - 1 == 5 || b - 1 == 5) {
        printf("%s \n", "Your charisma is already raised, choose another one");
        std::cin >> a >> b;
        a = Correctness_of_input(a, 1, 6);
        b = Correctness_of_input(b, 1, 6);
      }
      E.race_ability_bonus[a - 1][type] += 1;
      E.race_ability_bonus[b - 1][type] += 1;
    }
  }

  void RaceAbilityBonus() {
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
  Dragonborn() : Race() { subtype = 0; }
  Dragonborn(int sub_type, int a, int b, int c) {
    Create(sub_type, a, b, c);
  }
  ~Dragonborn() = default;
  void subRaceFeatures() {
    Str += 2;
    Cha += 1;
    Movement = 30;
    Size = 1;
    Darkvision = 0;
    damage_resistance = 1;
    if (subtype == 0) {
      damage_resistance = 1;
      raceFeatures = "fits,Acid,Draconic";
    } else if (subtype == 1) {
      damage_resistance = 2;
      raceFeatures = "fits,Lightning,Draconic";
    } else if (subtype == 2) {
      damage_resistance = 3;
      raceFeatures = "Fire,fits,Fire,Draconic";
    } else if (subtype == 3) {
      damage_resistance = 2;
      raceFeatures = "fits,Lightning,Draconic";
    } else if (subtype == 4) {
      damage_resistance = 1;
      raceFeatures = "fits,Acid,Draconic";
    } else if (subtype == 5) {
      damage_resistance = 3;
      raceFeatures = "fits,Fire,Draconic";
    } else if (subtype == 6) {
      damage_resistance = 5;
      raceFeatures = "fits,Poison,Draconic";
    } else if (subtype == 7) {
      damage_resistance = 3;
      raceFeatures = "fits,Fire,Draconic";
    } else if (subtype == 8) {
      damage_resistance = 4;
      raceFeatures = "fits,Cold,Draconic";
    } else if (subtype == 9) {
      damage_resistance = 4;
      raceFeatures = "fits,Cold,Draconic";
    }
  }

  void Create(int sub_type, int a, int b, int c) {
    Str = 0;
    Dex = 0;
    Con = 0;
    Int = 0;
    Wis = 0;
    Cha = 0;
    Movement = 0;
    Size = 0;
    Darkvision = 0;
    damage_resistance = 0;
    type = 1;
    subtype = sub_type;
    height = a;
    weight = b;
    age = c;
    subRaceFeatures();
  }
};

class Dwarf : public Race {
 private:
  int subtype;
 public:
  Dwarf() : Race() { subtype = 0; }
  Dwarf(int sub_type, int a, int b, int c) {
    Create(sub_type, a, b, c);
  }
  ~Dwarf() = default;
  void subRaceFeatures() {
    Movement = 25;
    Size = 1;
    Darkvision = 120;
    damage_resistance = 5;
    if (subtype == 0) {
      Str += 1;
      Con += 2;
      raceFeatures = "25,Medium,Darkvision,skill like firebreath,fits,Languages";
    } else if (subtype == 1) {
      Con += 2;
      Wis += 1;
      raceFeatures = "25,Medium,Darkvision,skill like firebreath,fits,Languages";
    } else if (subtype == 2) {
      Str += 2;
      Con += 2;
      raceFeatures = "25,Medium,Darkvision,skill like firebreath,fits,Languages";
    }
  }

  void Create(int sub_type, int a, int b, int c) {
    Str = 0;
    Dex = 0;
    Con = 0;
    Int = 0;
    Wis = 0;
    Cha = 0;
    Movement = 0;
    Size = 0;
    Darkvision = 0;
    damage_resistance = 0;
    subtype = sub_type;
    type = 2;
    height = a;
    weight = b;
    age = c;
    subRaceFeatures();
  }
};

class Elf : public Race {
 private:
  int subtype;
 public:
  Elf() : Race() { subtype = 0; }
  Elf(int sub_type, int a, int b, int c) {
    Create(sub_type, a, b, c);
  }
  ~Elf() = default;
  void subRaceFeatures() {
    Movement = 30;
    Size = 1;
    Darkvision = 120;
    damage_resistance = 0;
    if (subtype == 0) {
      Dex += 2;
      Cha += 1;
      raceFeatures = "fits,Languages";
    } else if (subtype == 1) {
      Dex += 2;
      Int += 1;
      raceFeatures = "fits,Languages";
    } else if (subtype == 2) {
      Dex += 2;
      Cha += 1;
      raceFeatures = "fits,Languages";
    } else if (subtype == 3) {
      Dex += 2;
      Int += 1;
      raceFeatures = "fits,Languages";
    } else if (subtype == 4) {
      Dex += 2;
      Con += 1;
      raceFeatures = "fits,Languages";
    } else if (subtype == 5) {
      Dex += 2;
      Con += 1;
      raceFeatures = "fits,Languages";
    } else if (subtype == 6) {
      Dex += 2;
      Wis += 1;
      raceFeatures = "fits,Languages";
    }
  }

  void Create(int sub_type, int a, int b, int c) {
    Str = 0;
    Dex = 0;
    Con = 0;
    Int = 0;
    Wis = 0;
    Cha = 0;
    Movement = 0;
    Size = 0;
    Darkvision = 0;
    damage_resistance = 0;
    type = 3;
    subtype = sub_type;
    height = a;
    weight = b;
    age = c;
    subRaceFeatures();
  }
};
class Gnome : public Race {
 private:
  int subtype;
 public:
  Gnome() : Race() { subtype = 0; }
  Gnome(int sub_type, int a, int b, int c) {
    Create(sub_type, a, b, c);
  }
  ~Gnome() = default;
  void subRaceFeatures() {
    Movement = 25;
    Size = 1;
    Darkvision = 120;
    damage_resistance = 0;
    if (subtype == 0) {
      Dex += 1;
      Int += 2;
      raceFeatures = "25,Small,Darkvision,skill like firebreath,fits,Languages";
    } else if (subtype == 1) {
      Dex += 1;
      Int += 2;
      raceFeatures = "25,Small,Darkvision,skill like firebreath,fits,Languages";
    } else if (subtype == 2) {
      Con += 1;
      Int += 2;
      raceFeatures = "25,Small,Darkvision,skill like firebreath,fits,Languages";
    }
  }

  void Create(int sub_type, int a, int b, int c) {
    Str = 0;
    Dex = 0;
    Con = 0;
    Int = 0;
    Wis = 0;
    Cha = 0;
    Movement = 0;
    Size = 0;
    Darkvision = 0;
    damage_resistance = 0;
    type = 4;
    subtype = sub_type;
    height = a;
    weight = b;
    age = c;
    subRaceFeatures();
  }
};

class Goblin : public Race {
 private:
  int subtype;
 public:
  Goblin() : Race() { subtype = 0; }
  Goblin(int sub_type, int a, int b, int c) {
    Create(sub_type, a, b, c);
  }
  ~Goblin() = default;
  void subRaceFeatures() {
    Movement = 30;
    Size = 1;
    Darkvision = 60;
    damage_resistance = 0;
    Dex += 2;
    Con += 1;
    raceFeatures = "30,Small,Darkvision,skill like firebreath,fits,Languages";
  }

  void Create(int sub_type, int a, int b, int c) {
    Str = 0;
    Dex = 0;
    Con = 0;
    Int = 0;
    Wis = 0;
    Cha = 0;
    Movement = 0;
    Size = 0;
    Darkvision = 0;
    damage_resistance = 0;
    type = 5;
    subtype = sub_type;
    height = a;
    weight = b;
    age = c;
    subRaceFeatures();
  }
};

class Half_Elf : public Race {
 private:
  int subtype;
 public:
  Half_Elf() : Race() { subtype = 0; }
  Half_Elf(int sub_type, int a, int b, int c) {
    Create(sub_type, a, b, c);
  }
  ~Half_Elf() = default;
  void subRaceFeatures() {
    Movement = 30;
    Size = 2;
    Darkvision = 60;
    damage_resistance = 0;
    Cha += 2;
    int a, b;
    printf("%s \n", "type two most wanted abilities to improve except Charisma (1 - 5)");
    std::cin >> a >> b;
    a = Correctness_of_input(a, 1, 5);
    b = Correctness_of_input(b, 1, 5);
    E.race_ability_bonus[a - 1][15 + subtype] += 1;
    E.race_ability_bonus[b - 1][15 + subtype] += 1;
    if (subtype == 0) {
      raceFeatures = "fits,Languages";
    } else if (subtype == 1) {
      raceFeatures = "fits,Languages";
    } else if (subtype == 2) {
      raceFeatures = "fits,Languages";
    } else if (subtype == 3) {
      raceFeatures = "fits,Languages";
    } else if (subtype == 4) {
      raceFeatures = "fits,Languages";
    }
    RaceAbilityBonus();
    E.race_ability_bonus[a - 1][15 + subtype] -= 1;
    E.race_ability_bonus[b - 1][15 + subtype] -= 1;
  }

  void Create(int sub_type, int a, int b, int c) {
    Str = 0;
    Dex = 0;
    Con = 0;
    Int = 0;
    Wis = 0;
    Cha = 0;
    Movement = 0;
    Size = 0;
    Darkvision = 0;
    damage_resistance = 0;
    type = 6;
    subtype = sub_type;
    height = a;
    weight = b;
    age = c;
    subRaceFeatures();
  }
};

class Half_Orc : public Race {
 private:
  int subtype;
 public:
  Half_Orc() : Race() { subtype = 0; }
  Half_Orc(int sub_type, int a, int b, int c) {
    Create(sub_type, a, b, c);
  }
  ~Half_Orc() = default;
  void subRaceFeatures() {
    Movement = 30;
    Size = 2;
    Darkvision = 60;
    damage_resistance = 0;
    if (subtype == 0) {
      Str += 2;
      Con += 1;
      raceFeatures = "fits,Languages";
    } else if (subtype == 1) {
      Str += 2;
      Con += 1;
      Int -= 2;
      raceFeatures = "fits,Languages";
    }
  }

  void Create(int sub_type, int a, int b, int c) {
    Str = 0;
    Dex = 0;
    Con = 0;
    Int = 0;
    Wis = 0;
    Cha = 0;
    Movement = 0;
    Size = 0;
    Darkvision = 0;
    damage_resistance = 0;
    type = 7;
    subtype = sub_type;
    height = a;
    weight = b;
    age = c;
    subRaceFeatures();
  }
};

class Halfling : public Race {
 private:
  int subtype;
 public:
  Halfling() : Race() { subtype = 0; }
  Halfling(int sub_type, int a, int b, int c) {
    Create(sub_type, a, b, c);
  }
  ~Halfling() = default;
  void subRaceFeatures() {
    Movement = 25;
    Size = 1;
    Darkvision = 0;
    damage_resistance = 0;
    Dex += 2;
    if (subtype == 0) {
      Wis += 1;
      raceFeatures = "25,Small,Darkvision,skill like firebreath,fits,Languages";
    } else if (subtype == 1) {
      Cha += 1;
      raceFeatures = "25,Small,Darkvision,skill like firebreath,fits,Languages";
    } else if (subtype == 2) {
      Con += 1;
      raceFeatures = "25,Small,Darkvision,skill like firebreath,fits,Languages";
    }
  }

  void Create(int sub_type, int a, int b, int c) {
    Str = 0;
    Dex = 0;
    Con = 0;
    Int = 0;
    Wis = 0;
    Cha = 0;
    Movement = 0;
    Size = 0;
    Darkvision = 0;
    damage_resistance = 0;
    type = 8;
    subtype = sub_type;
    height = a;
    weight = b;
    age = c;
    subRaceFeatures();
  }
};

class Human : public Race {
 private:
  int subtype;
 public:
  Human() : Race() { subtype = 0; }
  Human(int sub_type, int a, int b, int c) {
    Create(sub_type, a, b, c);
  }
  ~Human() = default;
  void subRaceFeatures() {
    Movement = 30;
    Size = 2;
    Darkvision = 0;
    damage_resistance = 0;
    if (subtype == 0) {
      Str += 1;
      Dex += 1;
      Con += 1;
      Int += 1;
      Wis += 1;
      Cha += 1;
      raceFeatures = "30,Medium,No,skill like firebreath,No,Languages";
    } else if (subtype == 1) {
      int a, b;
      printf("%s \n", "type two most wanted abilities to improve (1 - 6)");
      std::cin >> a >> b;
      a = Correctness_of_input(a, 1, 6);
      b = Correctness_of_input(b, 1, 6);
      E.race_ability_bonus[a - 1][24 + subtype] += 1;
      E.race_ability_bonus[b - 1][24 + subtype] += 1;
      raceFeatures = "fits,Languages";
      RaceAbilityBonus();
      E.race_ability_bonus[a - 1][24 + subtype] -= 1;
      E.race_ability_bonus[b - 1][24 + subtype] -= 1;
    }
  }

  void Create(int sub_type, int a, int b, int c) {
    Str = 0;
    Dex = 0;
    Con = 0;
    Int = 0;
    Wis = 0;
    Cha = 0;
    Movement = 0;
    Size = 0;
    Darkvision = 0;
    damage_resistance = 0;
    type = 9;
    subtype = sub_type;
    height = a;
    weight = b;
    age = c;
    subRaceFeatures();
  }
};
class Lizardfolk : public Race {
 private:
  int subtype;
 public:
  Lizardfolk() : Race() { subtype = 0; }
  Lizardfolk(int sub_type, int a, int b, int c) {
    Create(sub_type, a, b, c);
  }
  ~Lizardfolk() = default;
  void subRaceFeatures() {
    printf(
        "You gain proficiency with two of the following skills of your choice: Animal Handling(2), Nature(11), Perception(12), Stealth(17), and Survival(18).\n");
    int a, b;
    std::cin >> a >> b;
    a = Correctness_of_input(a, 2, 18);
    b = Correctness_of_input(b, 2, 18);
    Movement = 30;
    Size = 2;
    Darkvision = 0;
    damage_resistance = 0;
    Con += 2;
    Wis += 1;
    raceFeatures = "fits,Languages,s[" + std::to_string(a) + "],s[" + std::to_string(b) + "]";
  }

  void Create(int sub_type, int a, int b, int c) {
    Str = 0;
    Dex = 0;
    Con = 0;
    Int = 0;
    Wis = 0;
    Cha = 0;
    Movement = 0;
    Size = 0;
    Darkvision = 0;
    damage_resistance = 0;
    type = 10;
    subtype = sub_type;
    height = a;
    weight = b;
    age = c;
    subRaceFeatures();
  }
};

class Tiefling : public Race {
 private:
  int subtype;
 public:
  Tiefling() : Race() { subtype = 0; }
  Tiefling(int sub_type, int a, int b, int c) {
    Create(sub_type, a, b, c);
  }
  ~Tiefling() = default;
  void subRaceFeatures() {
    Movement = 30;
    Size = 2;
    Darkvision = 60;
    damage_resistance = 3;
    if (subtype == 0) {
      Int += 1;
      Cha += 2;
      raceFeatures = "fits,Languages";
    } else if (subtype == 1) {
      Int += 1;
      Cha += 2;
      raceFeatures = "fits,Languages";
    } else if (subtype == 2) {
      Int += 1;
      Cha += 2;
      raceFeatures = "fits,Languages";
    } else if (subtype == 3) {
      Dex += 1;
      Cha += 2;
      raceFeatures = "fits,Languages";
    } else if (subtype == 4) {
      Wis += 1;
      Cha += 2;
      raceFeatures = "fits,Languages";
    } else if (subtype == 5) {
      Dex += 1;
      Cha += 2;
      raceFeatures = "fits,Languages";
    } else if (subtype == 6) {
      Con += 1;
      Cha += 2;
      raceFeatures = "fits,Languages";
    } else if (subtype == 7) {
      Int += 1;
      Cha += 2;
      raceFeatures = "fits,Languages";
    } else if (subtype == 8) {
      Int += 1;
      Cha += 2;
      raceFeatures = "fits,Languages";
    } else if (subtype == 9) {
      Int += 1;
      int a;
      printf("%s \n", "Choose only one ability Dexterity(2) or Charisma(6) )");
      std::cin >> a;
      while (a != 2 && a != 6) {
        printf("%s \n", "Choose only one ability Dexterity(2) or Charisma(6) )");
        std::cin >> a;
      }
      E.race_ability_bonus[a - 1][28 + subtype] += 1;
      raceFeatures = "fits,Languages";
      RaceAbilityBonus();
      E.race_ability_bonus[a - 1][28 + subtype] -= 1;
    } else if (subtype == 10) {
      Str += 1;
      Cha += 2;
      raceFeatures = "fits,Languages";
    }
  }

  void Create(int sub_type, int a, int b, int c) {
    Str = 0;
    Dex = 0;
    Con = 0;
    Int = 0;
    Wis = 0;
    Cha = 0;
    Movement = 0;
    Size = 0;
    Darkvision = 0;
    damage_resistance = 0;
    type = 11;
    subtype = sub_type;
    height = a;
    weight = b;
    age = c;
    subRaceFeatures();
  }
};