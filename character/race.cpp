
#include "race.h"

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
    movement = 0;
    size = 0;
    darkvision = 0;
  damage_resistance = 0;
}
Race::~Race() = default;
/*void Race::set(Random_Generator_ * Rand_gen,int a) {
  //type = a;
  height = Rand_gen->Rand(E.minHeight[type], E.maxHeight[type]);
  weight = Rand_gen->Rand(E.minWeight[type], E.maxWeight[type]);
  age = Rand_gen->Rand(E.minAge[type], E.maxAge[type]);
}*/
void Race::set(int type_, int height_, int weight_, int age_, Allowance *allowance) {
  type = type_;
  height = height_;
  weight = weight_;
  age = age_;
  if (!allowance->Is_Character_Set()) {
    SetRaceAbilityBonus();
    RaceAbilityBonus();
  }
}
void Race::Create(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  type = sub_type;
  //subtype = sub_type;
  height = height_;
  weight = weight_;
  age = age_;
  //subRaceFeatures();
}
int Race::get(int what) {
  switch (what) {
    case 0 : return type;
    case 1 : return height;
    case 2 : return weight;
    case 3 : return age;
    case 4 : return Str;
    case 5 : return Dex;
    case 6 : return Con;
    case 7 : return Int;
    case 8 : return Wis;
    case 9 : return Cha;
    case 10 : return movement;
    case 11 : return size;
    case 12 : return darkvision;
    case 13 : return damage_resistance;
    case 14 : return subtype;
    default: return -1;
  }
}

void Race::SetRaceAbilityBonus() {
  int a = 0, b = 0;
  if (type < 15 || (type > 19 && type != 25 && type != 37)) {// 15-19(3)  25(2) 37(Dex or Cha)
    std::cout << "Your type got non flexible ability bonuses\n";
  } else if (type == 25) {
    std::cout << "type two most wanted abilities to improve (1 - 6)\n";
    a = IsNumber(a, 1, kAbilities_Num);
    b = IsNumber(b, 1, kAbilities_Num);
    E.race_ability_bonus[a - 1][type] += 1;
    E.race_ability_bonus[b - 1][type] += 1;
  } else if (type == 37) {
    std::cout << "Choose only one ability Dexterity(2) or Charisma(6) )\n";
    a = IsNumber(a, 2, kAbilities_Num);
    while (a != 2 && a != kAbilities_Num) {
      std::cout << "Choose only one ability Dexterity(2) or Charisma(6) )\n";
      a = IsNumber(a, 2, kAbilities_Num);
    }
    E.race_ability_bonus[a - 1][type] += 1;
  } else {
    std::cout << "type two most wanted abilities to improve (1 - 6)\n";
    a = IsNumber(a, 1, kAbilities_Num);
    b = IsNumber(b, 1, kAbilities_Num);
    while (a - 1 == 5 || b - 1 == 5) {
      std::cout << "Your charisma is already raised, choose another pair\n";
      a = IsNumber(a, 1, kAbilities_Num);
      b = IsNumber(b, 1, kAbilities_Num);
    }
    E.race_ability_bonus[a - 1][type] += 1;
    E.race_ability_bonus[b - 1][type] += 1;
  }
}
void Race::subRaceFeatures() {
  std::cout << "No subrace\n";
}
void Race::RaceAbilityBonus() {
  Str = E.race_ability_bonus[0][type];
  Dex = E.race_ability_bonus[1][type];
  Con = E.race_ability_bonus[2][type];
  Int = E.race_ability_bonus[3][type];
  Wis = E.race_ability_bonus[4][type];
  Cha = E.race_ability_bonus[5][type];
}
void Race::Size_Set() {
  auto Rand_gen = new Random_Generator_();
  std::cout <<
            "insert height(ft), weight(lbs) and age(y) of your character or type zero(s) (0 100 0) to random\n";
  std::cout <<
            "Normal parameters for your race are: height(ft) from " <<
            E.minHeight[type] <<
            " to " <<
            E.maxHeight[type] <<
            " weight(lbs)from " <<
            E.minWeight[type] <<
            " to " <<
            E.maxWeight[type] <<
            " and age(y) from " <<
            E.minAge[type] <<
            " to " <<
            E.maxAge[type] << std::endl;
  height = IsNumber(height, 0, E.maxHeight[type]);
  weight = IsNumber(weight, 0, E.maxWeight[type]);
  age = IsNumber(age, 0, E.maxAge[type]);
  if (height < E.minHeight[type]) { height = Rand_gen->Rand(E.minHeight[type], E.maxHeight[type]); }
  if (weight < E.minWeight[type]) { weight = Rand_gen->Rand(E.minWeight[type], E.maxWeight[type]); }
  if (age < E.minAge[type]) { age = Rand_gen->Rand(E.minAge[type], E.maxAge[type]); }
}
bool Race::Load(int parameters_i[]) {
  type = parameters_i[kRace_Load_parameters_shift];
  height = parameters_i[kRace_Load_parameters_shift + 1];
  weight = parameters_i[kRace_Load_parameters_shift + 2];
  age = parameters_i[kRace_Load_parameters_shift + 3];
    movement = parameters_i[kRace_Load_parameters_shift + 4];
    size = parameters_i[kRace_Load_parameters_shift + 5];
    darkvision = parameters_i[kRace_Load_parameters_shift + 6];
  damage_resistance = parameters_i[kRace_Load_parameters_shift + 7];
  subtype = parameters_i[kRace_Load_parameters_shift + 8];
  Str = 0;
  Dex = 0;
  Con = 0;
  Int = 0;
  Wis = 0;
  Cha = 0;
  raceFeatures = "loaded " + std::to_string((char) parameters_i[35]);
  return true;
}

Dragonborn::Dragonborn() = default;
Dragonborn::Dragonborn(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  Create(sub_type, height_, weight_, age_, allowance);
}
Dragonborn::~Dragonborn() = default;
void Dragonborn::subRaceFeatures() {
  Str += 2;
  Cha += 1;
    movement = 30;
    size = 2;
    darkvision = 0;
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
void Dragonborn::Create(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  Str = 0;
  Dex = 0;
  Con = 0;
  Int = 0;
  Wis = 0;
  Cha = 0;
    movement = 0;
    size = 0;
    darkvision = 0;
  damage_resistance = 0;
  type = 0;
  subtype = sub_type;
  height = height_;
  weight = weight_;
  age = age_;
  if (!allowance->Is_Tested()) { Size_Set(); };
  if (!allowance->Is_Character_Set()) {
    subRaceFeatures();
  };
}

Dwarf::Dwarf() = default;
Dwarf::Dwarf(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  Create(sub_type, height_, weight_, age_, allowance);
}
Dwarf::~Dwarf() = default;
void Dwarf::subRaceFeatures() {
    movement = 25;
    size = 1;
    darkvision = 120;
  damage_resistance = 5;
  if (subtype == 0) {
    Str += 1;
    Con += 2;
    raceFeatures = "25,Medium,darkvision,skill like firebreath,fits,Languages";
  } else if (subtype == 1) {
    Con += 2;
    Wis += 1;
    raceFeatures = "25,Medium,darkvision,skill like firebreath,fits,Languages";
  } else if (subtype == 2) {
    Str += 2;
    Con += 2;
    raceFeatures = "25,Medium,darkvision,skill like firebreath,fits,Languages";
  }
}
void Dwarf::Create(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  Str = 0;
  Dex = 0;
  Con = 0;
  Int = 0;
  Wis = 0;
  Cha = 0;
    movement = 0;
    size = 0;
    darkvision = 0;
  damage_resistance = 0;
  subtype = sub_type;
  type = 1;
  height = height_;
  weight = weight_;
  age = age_;
  if (!allowance->Is_Tested()) { Size_Set(); };
  if (!allowance->Is_Character_Set()) {
    subRaceFeatures();
  };
}

Elf::Elf() = default;
Elf::Elf(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  Create(sub_type, height_, weight_, age_, allowance);
}
Elf::~Elf() = default;
void Elf::subRaceFeatures() {
    movement = 30;
    size = 2;
    darkvision = 120;
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
void Elf::Create(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  Str = 0;
  Dex = 0;
  Con = 0;
  Int = 0;
  Wis = 0;
  Cha = 0;
    movement = 0;
    size = 0;
    darkvision = 0;
  damage_resistance = 0;
  type = 2;
  subtype = sub_type;
  height = height_;
  weight = weight_;
  age = age_;
  if (!allowance->Is_Tested()) { Size_Set(); };
  if (!allowance->Is_Character_Set()) {
    subRaceFeatures();
  };
}

Gnome::Gnome() = default;
Gnome::Gnome(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  Create(sub_type, height_, weight_, age_, allowance);
}
Gnome::~Gnome() = default;
void Gnome::subRaceFeatures() {
    movement = 25;
    size = 1;
    darkvision = 120;
  damage_resistance = 0;
  if (subtype == 0) {
    Dex += 1;
    Int += 2;
    raceFeatures = "25,Small,darkvision,skill like firebreath,fits,Languages";
  } else if (subtype == 1) {
    Dex += 1;
    Int += 2;
    raceFeatures = "25,Small,darkvision,skill like firebreath,fits,Languages";
  } else if (subtype == 2) {
    Con += 1;
    Int += 2;
    raceFeatures = "25,Small,darkvision,skill like firebreath,fits,Languages";
  }
}
void Gnome::Create(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  Str = 0;
  Dex = 0;
  Con = 0;
  Int = 0;
  Wis = 0;
  Cha = 0;
    movement = 0;
    size = 0;
    darkvision = 0;
  damage_resistance = 0;
  type = 3;
  subtype = sub_type;
  height = height_;
  weight = weight_;
  age = age_;
  if (!allowance->Is_Tested()) { Size_Set(); };
  if (!allowance->Is_Character_Set()) {
    subRaceFeatures();
  };
}

Goblin::Goblin() = default;
Goblin::Goblin(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  Create(sub_type, height_, weight_, age_, allowance);
}
Goblin::~Goblin() = default;
void Goblin::subRaceFeatures() {
    movement = 30;
    size = 1;
    darkvision = 60;
  damage_resistance = 0;
  Dex += 2;
  Con += 1;
  raceFeatures = "30,Small,darkvision,skill like firebreath,fits,Languages";
}
void Goblin::Create(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  Str = 0;
  Dex = 0;
  Con = 0;
  Int = 0;
  Wis = 0;
  Cha = 0;
    movement = 0;
    size = 0;
    darkvision = 0;
  damage_resistance = 0;
  type = 4;
  subtype = sub_type;
  height = height_;
  weight = weight_;
  age = age_;
  if (!allowance->Is_Tested()) { Size_Set(); };
  if (!allowance->Is_Character_Set()) {
    subRaceFeatures();
  };
}

Half_Elf::Half_Elf() = default;
Half_Elf::Half_Elf(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  Create(sub_type, height_, weight_, age_, allowance);
}
Half_Elf::~Half_Elf() = default;
void Half_Elf::subRaceFeatures() {
    movement = 30;
    size = 2;
    darkvision = 60;
  damage_resistance = 0;
  Cha += 2;
  int a = 0, b = 0;
  std::cout << "type two most wanted abilities to improve except Charisma (1 - 5)\n";
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
void Half_Elf::Create(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  Str = 0;
  Dex = 0;
  Con = 0;
  Int = 0;
  Wis = 0;
  Cha = 0;
    movement = 0;
    size = 0;
    darkvision = 0;
  damage_resistance = 0;
  type = 5;
  subtype = sub_type;
  height = height_;
  weight = weight_;
  age = age_;
  if (!allowance->Is_Tested()) { Size_Set(); };
  if (!allowance->Is_Character_Set()) {
    subRaceFeatures();
  };
}

Half_Orc::Half_Orc() = default;
Half_Orc::Half_Orc(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  Create(sub_type, height_, weight_, age_, allowance);
}
Half_Orc::~Half_Orc() = default;
void Half_Orc::subRaceFeatures() {
    movement = 30;
    size = 2;
    darkvision = 60;
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
void Half_Orc::Create(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  Str = 0;
  Dex = 0;
  Con = 0;
  Int = 0;
  Wis = 0;
  Cha = 0;
    movement = 0;
    size = 0;
    darkvision = 0;
  damage_resistance = 0;
  type = 6;
  subtype = sub_type;
  height = height_;
  weight = weight_;
  age = age_;
  if (!allowance->Is_Tested()) { Size_Set(); };
  if (!allowance->Is_Character_Set()) {
    subRaceFeatures();
  };
}

Halfling::Halfling() = default;
Halfling::Halfling(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  Create(sub_type, height_, weight_, age_, allowance);
}
Halfling::~Halfling() = default;
void Halfling::subRaceFeatures() {
    movement = 25;
    size = 1;
    darkvision = 0;
  damage_resistance = 0;
  Dex += 2;
  if (subtype == 0) {
    Wis += 1;
    raceFeatures = "25,Small,darkvision,skill like firebreath,fits,Languages";
  } else if (subtype == 1) {
    Cha += 1;
    raceFeatures = "25,Small,darkvision,skill like firebreath,fits,Languages";
  } else if (subtype == 2) {
    Con += 1;
    raceFeatures = "25,Small,darkvision,skill like firebreath,fits,Languages";
  }
}
void Halfling::Create(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  Str = 0;
  Dex = 0;
  Con = 0;
  Int = 0;
  Wis = 0;
  Cha = 0;
    movement = 0;
    size = 0;
    darkvision = 0;
  damage_resistance = 0;
  type = 7;
  subtype = sub_type;
  height = height_;
  weight = weight_;
  age = age_;
  if (!allowance->Is_Tested()) { Size_Set(); };
  if (!allowance->Is_Character_Set()) {
    subRaceFeatures();
  };
}

Human::Human() = default;
Human::Human(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  Create(sub_type, height_, weight_, age_, allowance);
}
Human::~Human() = default;
void Human::subRaceFeatures() {
    movement = 30;
    size = 2;
    darkvision = 0;
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
    int a = 0, b = 0;
    std::cout << "type two most wanted abilities to improve (1 - 6)\n";
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
void Human::Create(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  Str = 0;
  Dex = 0;
  Con = 0;
  Int = 0;
  Wis = 0;
  Cha = 0;
    movement = 0;
    size = 0;
    darkvision = 0;
  damage_resistance = 0;
  type = 8;
  subtype = sub_type;
  height = height_;
  weight = weight_;
  age = age_;
  if (!allowance->Is_Tested()) { Size_Set(); };
  if (!allowance->Is_Character_Set()) {
    subRaceFeatures();
  };
}

Lizardfolk::Lizardfolk() = default;
Lizardfolk::Lizardfolk(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  Create(sub_type, height_, weight_, age_, allowance);
}
Lizardfolk::~Lizardfolk() = default;
void Lizardfolk::subRaceFeatures() {
  std::cout <<
            "You gain proficiency with two of the following skills of your choice: Animal Handling(2), Nature(11), Perception(12), Stealth(17), and Survival(18).\n";
  int a = 0, b = 0;
  //std::cin >> a >> b;
  a = IsNumber(a, 2, 18);
  b = IsNumber(b, 2, 18);
    movement = 30;
    size = 2;
    darkvision = 0;
  damage_resistance = 0;
  Con += 2;
  Wis += 1;
  raceFeatures = "fits,Languages,s[" + std::to_string(a) + "],s[" + std::to_string(b) + "]";
}
void Lizardfolk::Create(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  Str = 0;
  Dex = 0;
  Con = 0;
  Int = 0;
  Wis = 0;
  Cha = 0;
    movement = 0;
    size = 0;
    darkvision = 0;
  damage_resistance = 0;
  type = 9;
  subtype = sub_type;
  height = height_;
  weight = weight_;
  age = age_;
  if (!allowance->Is_Tested()) { Size_Set(); };
  if (!allowance->Is_Character_Set()) {
    subRaceFeatures();
  };
}

Tiefling::Tiefling() = default;
Tiefling::Tiefling(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  Create(sub_type, height_, weight_, age_, allowance);
}
Tiefling::~Tiefling() = default;
void Tiefling::subRaceFeatures() {
    movement = 30;
    size = 2;
    darkvision = 60;
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
    int a = 0;
    std::cout << "Choose only one ability Dexterity(2) or Charisma(6) )\n";
    //std::cin >> a;
    a = IsNumber(a, 2, 6);
    while (a != 2 && a != 6) {
      std::cout << "Choose only one ability Dexterity(2) or Charisma(6) )\n";
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
void Tiefling::Create(int sub_type, int height_, int weight_, int age_, Allowance *allowance) {
  Str = 0;
  Dex = 0;
  Con = 0;
  Int = 0;
  Wis = 0;
  Cha = 0;
    movement = 0;
    size = 0;
    darkvision = 0;
  damage_resistance = 0;
  type = 10;
  subtype = sub_type;
  height = height_;
  weight = weight_;
  age = age_;
  if (!allowance->Is_Tested()) { Size_Set(); };
  if (!allowance->Is_Character_Set()) {
    subRaceFeatures();
  };
}