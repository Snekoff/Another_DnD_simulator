
#include "Race.h"

//

Race::Race() {
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
Race::~Race() = default;
void Race::set(Random_Generator_ * Rand_gen,int a) {
  type = a;
  height = Rand_gen->Rand(E.minHeight[type], E.maxHeight[type]);
  weight = Rand_gen->Rand(E.minWeight[type], E.maxWeight[type]);
  age = Rand_gen->Rand(E.minAge[type], E.maxAge[type]);
}
void Race::set(int a, int b, int c, int d) {
  type = a;
  height = b;
  weight = c;
  age = d;
  SetRaceAbilityBonus();
  RaceAbilityBonus();
}
void Race::Create(int sub_type, int a, int b, int c) {
  type = sub_type;
  //subtype = sub_type;
  height = a;
  weight = b;
  age = c;
  //subRaceFeatures();
}
int Race::get(int w) {
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
void Race::RaceFeature() {}
void Race::SetRaceAbilityBonus() {
  int a = 0, b = 0;
  if (type < 15 || (type > 19 && type != 25 && type != 37)) {// 15-19(3)  25(2) 37(Dex or Cha)
    printf("%s \n", "Your type got non flexible ability bonuses");
  } else if (type == 25) {
    printf("%s \n", "type two most wanted abilities to improve (1 - 6)");
    //std::cin >> a >> b;
    a = IsNumber(a, 1, 6);
    b = IsNumber(b, 1, 6);
    E.race_ability_bonus[a - 1][type] += 1;
    E.race_ability_bonus[b - 1][type] += 1;
  } else if (type == 37) {
    printf("%s \n", "Choose only one ability Dexterity(2) or Charisma(6) )");
    //std::cin >> a;
    a = IsNumber(a, 2, 6);
    while (a != 2 && a != 6) {
      printf("%s \n", "Choose only one ability Dexterity(2) or Charisma(6) )");
      //std::cin >> a;
      a = IsNumber(a, 2, 6);
    }
    E.race_ability_bonus[a - 1][type] += 1;
  } else {
    printf("%s \n", "type two most wanted abilities to improve (1 - 6)");
    //std::cin >> a >> b;
    a = IsNumber(a, 1, 6);
    b = IsNumber(b, 1, 6);
    while (a - 1 == 5 || b - 1 == 5) {
      printf("%s \n", "Your charisma is already raised, choose another pair");
      //std::cin >> a >> b;
      a = IsNumber(a, 1, 6);
      b = IsNumber(b, 1, 6);
    }
    E.race_ability_bonus[a - 1][type] += 1;
    E.race_ability_bonus[b - 1][type] += 1;
  }
}
void Race::RaceAbilityBonus() {
  Str = E.race_ability_bonus[0][type];
  Dex = E.race_ability_bonus[1][type];
  Con = E.race_ability_bonus[2][type];
  Int = E.race_ability_bonus[3][type];
  Wis = E.race_ability_bonus[4][type];
  Cha = E.race_ability_bonus[5][type];
}

Dragonborn::Dragonborn() : Race() { subtype = 0; }
Dragonborn::Dragonborn(int sub_type, int a, int b, int c) {
  Create(sub_type, a, b, c);
}
Dragonborn::~Dragonborn() = default;
void Dragonborn::subRaceFeatures() {
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
void Dragonborn::Create(int sub_type, int a, int b, int c) {
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

Dwarf::Dwarf() : Race() { subtype = 0; }
Dwarf::Dwarf(int sub_type, int a, int b, int c) {
  Create(sub_type, a, b, c);
}
Dwarf::~Dwarf() = default;
void Dwarf::subRaceFeatures() {
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
void Dwarf::Create(int sub_type, int a, int b, int c) {
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

Elf::Elf() : Race() { subtype = 0; }
Elf::Elf(int sub_type, int a, int b, int c) {
  Create(sub_type, a, b, c);
}
Elf::~Elf() = default;
void Elf::subRaceFeatures() {
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
void Elf::Create(int sub_type, int a, int b, int c) {
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

Gnome::Gnome() : Race() { subtype = 0; }
Gnome::Gnome(int sub_type, int a, int b, int c) {
  Create(sub_type, a, b, c);
}
Gnome::~Gnome() = default;
void Gnome::subRaceFeatures() {
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
void Gnome::Create(int sub_type, int a, int b, int c) {
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

Goblin::Goblin() : Race() { subtype = 0; }
Goblin::Goblin(int sub_type, int a, int b, int c) {
  Create(sub_type, a, b, c);
}
Goblin::~Goblin() = default;
void Goblin::subRaceFeatures() {
  Movement = 30;
  Size = 1;
  Darkvision = 60;
  damage_resistance = 0;
  Dex += 2;
  Con += 1;
  raceFeatures = "30,Small,Darkvision,skill like firebreath,fits,Languages";
}
void Goblin::Create(int sub_type, int a, int b, int c) {
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

Half_Elf::Half_Elf() : Race() { subtype = 0; }
Half_Elf::Half_Elf(int sub_type, int a, int b, int c) {
  Create(sub_type, a, b, c);
}
Half_Elf::~Half_Elf() = default;
void Half_Elf::subRaceFeatures() {
  Movement = 30;
  Size = 2;
  Darkvision = 60;
  damage_resistance = 0;
  Cha += 2;
  int a, b;
  printf("%s \n", "type two most wanted abilities to improve except Charisma (1 - 5)");
  //std::cin >> a >> b;
  a = IsNumber(a, 1, 5);
  b = IsNumber(b, 1, 5);
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
void Half_Elf::Create(int sub_type, int a, int b, int c) {
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

Half_Orc::Half_Orc() : Race() { subtype = 0; }
Half_Orc::Half_Orc(int sub_type, int a, int b, int c) {
  Create(sub_type, a, b, c);
}
Half_Orc::~Half_Orc() = default;
void Half_Orc::subRaceFeatures() {
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
void Half_Orc::Create(int sub_type, int a, int b, int c) {
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

Halfling::Halfling() : Race() { subtype = 0; }
Halfling::Halfling(int sub_type, int a, int b, int c) {
  Create(sub_type, a, b, c);
}
Halfling::~Halfling() = default;
void Halfling::subRaceFeatures() {
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
void Halfling::Create(int sub_type, int a, int b, int c) {
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

Human::Human() : Race() { subtype = 0; }
Human::Human(int sub_type, int a, int b, int c) {
  Create(sub_type, a, b, c);
}
Human::~Human() = default;
void Human::subRaceFeatures() {
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
    //std::cin >> a >> b;
    a = IsNumber(a, 1, 6);
    b = IsNumber(b, 1, 6);
    E.race_ability_bonus[a - 1][24 + subtype] += 1;
    E.race_ability_bonus[b - 1][24 + subtype] += 1;
    raceFeatures = "fits,Languages";
    RaceAbilityBonus();
    E.race_ability_bonus[a - 1][24 + subtype] -= 1;
    E.race_ability_bonus[b - 1][24 + subtype] -= 1;
  }
}
void Human::Create(int sub_type, int a, int b, int c) {
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

Lizardfolk::Lizardfolk() : Race() { subtype = 0; }
Lizardfolk::Lizardfolk(int sub_type, int a, int b, int c) {
  Create(sub_type, a, b, c);
}
Lizardfolk::~Lizardfolk() = default;
void Lizardfolk::subRaceFeatures() {
  printf(
      "You gain proficiency with two of the following skills of your choice: Animal Handling(2), Nature(11), Perception(12), Stealth(17), and Survival(18).\n");
  int a, b;
  //std::cin >> a >> b;
  a = IsNumber(a, 2, 18);
  b = IsNumber(b, 2, 18);
  Movement = 30;
  Size = 2;
  Darkvision = 0;
  damage_resistance = 0;
  Con += 2;
  Wis += 1;
  raceFeatures = "fits,Languages,s[" + std::to_string(a) + "],s[" + std::to_string(b) + "]";
}
void Lizardfolk::Create(int sub_type, int a, int b, int c) {
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

Tiefling::Tiefling() : Race() { subtype = 0; }
Tiefling::Tiefling(int sub_type, int a, int b, int c) {
  Create(sub_type, a, b, c);
}
Tiefling::~Tiefling() = default;
void Tiefling::subRaceFeatures() {
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
    //std::cin >> a;
    a = IsNumber(a, 2, 6);
    while (a != 2 && a != 6) {
      printf("%s \n", "Choose only one ability Dexterity(2) or Charisma(6) )");
      //std::cin >> a;
      a = IsNumber(a, 2, 6);
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
void Tiefling::Create(int sub_type, int a, int b, int c) {
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