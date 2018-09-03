
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
  // 30,Size,Darkvision,skill like firebreath,fits,type of damage resistance,Languages//
 public:
  Race() {
    type = 0;
    height = 0;
    weight = 0;
    age = 0;
  }

  ~Race() = default;

  virtual void set(int a) {
    type = a;
    height = Random_Generator(E.minHeight[type],E.maxHeight[type]);
    weight = Random_Generator(E.minWeight[type],E.maxWeight[type]);
    age = Random_Generator(E.minAge[type],E.maxAge[type]);
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
  Dragonborn() : Race() { subtype = 0; }
  Dragonborn(int sub_type,int a, int b, int c){
    subtype = sub_type;
    height = a;
    weight = b;
    age = c;
    subRaceFeatures();
  }
  ~Dragonborn() = default;
  void subRaceFeatures() {
    Str +=2;
    Cha +=1;
    if(subtype == 0){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 1){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 2){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 3){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 4){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 5){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 6){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 7){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 8){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 9){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
  }
};

class Dwarf  : public Race {
 private:
  int subtype;
 public:
  Dwarf() : Race() { subtype = 0; }
  Dwarf(int sub_type,int a, int b, int c){
    subtype = sub_type;
    height = a;
    weight = b;
    age = c;
    subRaceFeatures();
  }
  ~Dwarf() = default;
  void subRaceFeatures() {
    if(subtype == 0){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 1){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 2){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
  }
};

class Elf  : public Race {
 private:
  int subtype;
 public:
  Elf():Race(){subtype = 0;}
  Elf(int sub_type,int a, int b, int c){
    subtype = sub_type;
    height = a;
    weight = b;
    age = c;
    subRaceFeatures();
  }
  ~Elf() = default;
  void subRaceFeatures() {
    if(subtype == 0){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 1){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 2){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 3){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 4){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 5){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 6){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
  }
};
class Gnome  : public Race {
 private:
  int subtype;
 public:
  Gnome():Race(){subtype = 0;}
  Gnome(int sub_type,int a, int b, int c){
    subtype = sub_type;
    height = a;
    weight = b;
    age = c;
    subRaceFeatures();
  }
  ~Gnome() = default;
  void subRaceFeatures() {
    if(subtype == 0){
      raceFeatures = "25,Small,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 1){
      raceFeatures = "25,Small,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 2){
      raceFeatures = "25,Small,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
  }
};

class Goblin : public Race {
 private:
  int subtype;
 public:
  Goblin():Race(){subtype = 0;}
  Goblin(int sub_type,int a, int b, int c){
    subtype = sub_type;
    height = a;
    weight = b;
    age = c;
    subRaceFeatures();
  }
  ~Goblin() = default;
  void subRaceFeatures() {
    raceFeatures = "30,Small,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
  }
};

class Half_Elf : public Race {
 private:
  int subtype;
 public:
  Half_Elf():Race(){subtype = 0;}
  Half_Elf(int sub_type,int a, int b, int c){
    subtype = sub_type;
    height = a;
    weight = b;
    age = c;
    subRaceFeatures();
  }
  ~Half_Elf() = default;
  void subRaceFeatures() {
    if(subtype == 0){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 1){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 2){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 3){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 4){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
  }
};

class Half_Orc : public Race {
 private:
  int subtype;
 public:
  Half_Orc():Race(){subtype = 0;}
  Half_Orc(int sub_type,int a, int b, int c){
    subtype = sub_type;
    height = a;
    weight = b;
    age = c;
    subRaceFeatures();
  }
  ~Half_Orc() = default;
  void subRaceFeatures() {
    if(subtype == 0){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 1){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
  }
};

class Halfling : public Race {
 private:
  int subtype;
 public:
  Halfling():Race(){subtype = 0;}
  Halfling(int sub_type,int a, int b, int c){
    subtype = sub_type;
    height = a;
    weight = b;
    age = c;
    subRaceFeatures();
  }
  ~Halfling() = default;
  void subRaceFeatures() {
    if(subtype == 0){
      raceFeatures = "25,Small,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 1){
      raceFeatures = "25,Small,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 2){
      raceFeatures = "25,Small,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
  }
};

class Human : public Race {
 private:
  int subtype;
 public:
  Human():Race(){subtype = 0;}
  Human(int sub_type,int a, int b, int c){
    subtype = sub_type;
    height = a;
    weight = b;
    age = c;
    subRaceFeatures();
  }
  ~Human() = default;
  void subRaceFeatures() {
    if(subtype == 0){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 1){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
  }
};
class Lizardfolk : public Race {
 private:
  int subtype;
 public:
  Lizardfolk():Race(){subtype = 0;}
  Lizardfolk(int sub_type,int a, int b, int c){
    subtype = sub_type;
    height = a;
    weight = b;
    age = c;
    subRaceFeatures();
  }
  ~Lizardfolk() = default;
  void subRaceFeatures() {
    raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
  }
};

class Tiefling : public Race {
 private:
  int subtype;
 public:
  Tiefling():Race(){subtype = 0;}
  Tiefling(int sub_type,int a, int b, int c){
    subtype = sub_type;
    height = a;
    weight = b;
    age = c;
    subRaceFeatures();
  }
  ~Tiefling() = default;
  void subRaceFeatures() {
    if(subtype == 0){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 1){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 2){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 3){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 4){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 5){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 6){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 7){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 8){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 9){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
    else if(subtype == 10){
      raceFeatures = "30,Medium,Darkvision,skill like firebreath,fits,type of damage resistance,Languages";
    }
  }
};

class Class {
 private:
  int type;
 protected:
  std::string features = "";
 public:
  Class() {}

  ~Class()  = default;

  virtual void set(int a) {}

  virtual void set(int a, int b, int c, int d) {}

  virtual int get() {
    return -1;
  }

  void ClassFeatures() {}
};

class SubClass : public Class {
 private:
  int subtype;
 public:
  SubClass() : Class(){}
  ~SubClass()  = default;
  void subClassFeatures() {}
};

