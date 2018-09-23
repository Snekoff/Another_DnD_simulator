

#include <iostream>
#include "character.h"

using namespace std;

Character::Character() {
  race_of_character = new Race();
  storyline = "Acolyte";
  sex = 0;
  experience = 0;
  level = 0;
  health = 0;
  maxhealth = 0;
  health_dice = 0;
  Str = 0;
  Dex = 0;
  Con = 0;
  Int = 0;
  Wis = 0;
  Cha = 0;
  StrModifier = 0;
  DexModifier = 0;
  ConModifier = 0;
  IntModifier = 0;
  WisModifier = 0;
  ChaModifier = 0;
  armor_class = 0;
  deathsaves_s = 0;
  deathsaves_f = 0;//success/failure
  passive_perception = 0;
  proficiency = 0;
  advantage = false;
  disadvantage = false;
  perception_advantage = false;
  perception_disadvantage = false;
}

Character::Character(Random_Generator_ * Rand_gen,string &storyl, int exp, int levl, int Stre, int Dext,
                     int Cons, int Inte, int Wisd, int Charisma, int sex_) {
  printf("Control reach 1\n");
  exp = Less_than_zero(exp);
  //levl = Less_than_zero(levl);
  Stre = Less_than_zero(Stre);
  Dext = Less_than_zero(Dext);
  Cons = Less_than_zero(Cons);
  Inte = Less_than_zero(Inte);
  Wisd = Less_than_zero(Wisd);
  Charisma = Less_than_zero(Charisma);
  //ArmorClass = Less_than_zero(ArmorClass);
  health = 0;
  maxhealth = 0;
  health_dice = 0;
  storyline = storyl;
  sex = sex_;
  if (exp < E.experience_per_level[levl - 1]) { exp = E.experience_per_level[levl - 1]; }
  experience = exp;
  Str = Stre;
  Dex = Dext;
  Con = Cons;
  Int = Inte;
  Wis = Wisd;
  Cha = Charisma;
  int t1 = Ability_Random_Sets(Rand_gen);
  printf("Control reach 2\n");
  armor_class = 0;
  deathsaves_s = 0;
  deathsaves_f = 0;
  passive_perception = 0;
  proficiency = 0;
  advantage = false;
  disadvantage = false;
  perception_advantage = false;
  perception_disadvantage = false;
  printf("Control reach 3\n");
  ConcreteAbilityModifier();
  s = new int[18];
  s_b = new bool[18];
  money[0] = 0;//copper
  money[1] = 0;
  money[2] = 0;
  money[3] = 0;//Pt
  money[4] = 0;
  Equiped = new Item[10];
  printf("Control reach 4\n");
  SetSkill(s);
  printf("Control reach 5\n");
  proficiency = ProficiencySetter();
  printf("Control reach 6\n");
  passive_perception = PassivePerceptionSetter(WisModifier, perception_advantage, perception_disadvantage);
  printf("Control reach 7\n");
  Race_Choosal(Rand_gen);
  printf("Control reach 8\n");
  StorySetsSkills(s, s_b, storyline);
  printf("Control reach 9\n");
  SetClass(Rand_gen);
  printf("Control reach 10\n");
  Starting_Health();
  printf("Control reach 11\n");
  if (classType.get(0) == 0) armor_class = 10 + DexModifier + ConModifier;
  level = 0;
  printf("Control reach 12\n");
  cout << experience << " " << level << endl;
  t1 = Level_Up(Rand_gen);
  printf("Control reach 13\n");
  Add_To_Inventory();
  printf("Control reach 14\n");
  state = 0;
  Equiping_Item();
}

Character::~Character() {
  delete race_of_character;
  delete[] s;
  delete[] s_b;
  inventory.clear();
  items_map.clear();
  delete[] Equiped;
};

int Character::Ability_Random_Sets(Random_Generator_ * Rand_gen) {
  //std::random_device rd;
  //std::mt19937 mt(rd());
  //std::uniform_int_distribution<int> dist(10,16);
  //return dist(mt);
  //Random_Generator_ * Rand_gen = new Random_Generator_();
  if (Str == 0 && Dex == 0 && Con == 0 && Int == 0 && Wis == 0 && Cha == 0) {
    int Sets[12] = {0};
    for (int k = 0; k < 12; k++) {
      if (k == 0) cout << "Set 1:\n";
      if (k == 6) cout << "\nSet 2:\n";
      Sets[k] = Rand_gen->Rand(10,16);
          //dist(mt);
          //Random_Generator(mt,10, 16);
      cout << " " << Sets[k] << " ";
    }
    cout << "which one do you prefer most?";
    cout << "*Or type 13 to re-roll\n";
    int s[7];
    cin >> s[6];
    if (s[6] == 13) return Ability_Random_Sets(Rand_gen);
    s[6] = Correctness_of_input(s[6], 1, 2);
    cout << "type six numbers what represents to what skill you apply each value "
            "Str(1),Dex(2),Con(3),Int(4),Wis(5),Cha(6)\n";
    for (int i = 0; i < 6; i++) {
      cin >> s[i];
      if (i == 0) { Str = Sets[(int) (pow(6, s[6] - 1)) - 1 + i]; }
      else if (i == 1) { Dex = Sets[(int) (pow(6, s[6] - 1)) - 1 + i]; }
      else if (i == 2) { Con = Sets[(int) (pow(6, s[6] - 1)) - 1 + i]; }
      else if (i == 3) { Int = Sets[(int) (pow(6, s[6] - 1)) - 1 + i]; }
      else if (i == 4) { Wis = Sets[(int) (pow(6, s[6] - 1)) - 1 + i]; }
      else if (i == 5) { Cha = Sets[(int) (pow(6, s[6] - 1)) - 1 + i]; }
    }
    //printf("Control reach end of Ability random sets\n");
    return 0;
  }
  delete Rand_gen;
  return -2;
}

int Character::Less_than_zero(int a) {
  return a < 0 ? 0 : a;
}

int Character::AbilityModifier(int a) {
  return (a - 10) / 2;
}

void Character::ConcreteAbilityModifier() {
  StrModifier = AbilityModifier(Str);
  DexModifier = AbilityModifier(Dex);
  ConModifier = AbilityModifier(Con);
  IntModifier = AbilityModifier(Int);
  WisModifier = AbilityModifier(Wis);
  ChaModifier = AbilityModifier(Cha);
}
//new
int Character::ProficiencySetter() {
  if (level < 5) return 2;
  else if (level > 4 && level < 9) return 3;
  else if (level > 8 && level < 13) return 4;
  else if (level > 12 && level < 17) return 5;
  else if (level > 16 && level < 21) return 6;
  return -3;
}

void Character::Size_Set(Random_Generator_ * Rand_gen,int a, int b, int c, int race1, int subrace, int negative) {
  // negative for class dragonborn

  printf("%s \n",
         "insert height(ft), weight(lbs) and age(y) of your character or type zero(s) (0 100 0) to random");
  printf("%s %d %s %d %s %d %s %d %s %d %s %d \n",
         "Normal parameters for your race are: height(ft) from ",
         E.minHeight[race1 - 1],
         "to ",
         E.maxHeight[race1 - 1],
         " weight(lbs)from ",
         E.minWeight[race1 - 1],
         "to ",
         E.maxWeight[race1 - 1],
         " and age(y) from ",
         E.minAge[race1 - 1],
         "to ",
         E.maxAge[race1 - 1]);
  cin >> a >> b >> c;
  if (a <= 0 || a > E.maxHeight[race1 - 1]) { a = Rand_gen->Rand(E.minHeight[race1 - 1], E.maxHeight[race1 - 1]); }
  if (b <= 0 || b > E.maxWeight[race1 - 1]) { b = Rand_gen->Rand(E.minWeight[race1 - 1], E.maxWeight[race1 - 1]); }
  if (c <= 0 || c > E.maxAge[race1 - 1]) { c = Rand_gen->Rand(E.minAge[race1 - 1], E.maxAge[race1 - 1]); }
}

int Character::PassivePerceptionSetter(int a, bool b, bool c) {
  if (b) a += 5;
  if (c) a -= 5;
  return 10 + a;
}

void Character::StorySetsSkills(int s[], bool s_b[], string &b) {
  Add_Money(2, 15);
  if (b == "Acolyte") {
    if (!s_b[6]) {
      s[6] += proficiency;
      s_b[6] = true;
    }
    if (!s_b[14]) {
      s[14] += proficiency;
      s_b[14] = true;
    }
  } else if (b == "Charlatan") {
    if (!s_b[4]) {
      s[4] += proficiency;
      s_b[4] = true;
    }
    if (!s_b[15]) {
      s[15] += proficiency;
      s_b[15] = true;
    }
  } else if (b == "Criminal") {
    if (!s_b[4]) {
      s[4] += proficiency;
      s_b[4] = true;
    }
    if (!s_b[16]) {
      s[16] += proficiency;
      s_b[16] = true;
    }
  } else if (b == "Entertainer") {
    if (!s_b[0]) {
      s[0] += proficiency;
      s_b[0] = true;
    }
    if (!s_b[12]) {
      s[12] += proficiency;
      s_b[12] = true;
    }
  } else if (b == "FolkHero") {
    if (!s_b[1]) {
      s[1] += proficiency;
      s_b[1] = true;
    }
    if (!s_b[17]) {
      s[17] += proficiency;
      s_b[17] = true;
    }
  } else if (b == "GuildArtisan") {
    if (!s_b[6]) {
      s[6] += proficiency;
      s_b[6] = true;
    }
    if (!s_b[13]) {
      s[13] += proficiency;
      s_b[13] = true;
    }
  } else if (b == "Hermit") {
    if (!s_b[9]) {
      s[9] += proficiency;
      s_b[9] = true;
    }
    if (!s_b[14]) {
      s[14] += proficiency;
      s_b[14] = true;
    }
  } else if (b == "Noble") {
    if (!s_b[5]) {
      s[5] += proficiency;
      s_b[5] = true;
    }
    if (!s_b[13]) {
      s[13] += proficiency;
      s_b[13] = true;
    }
  } else if (b == "Outlander") {
    if (!s_b[3]) {
      s[3] += proficiency;
      s_b[3] = true;
    }
    if (!s_b[17]) {
      s[17] += proficiency;
      s_b[17] = true;
    }
  } else if (b == "Sage") {
    if (!s_b[2]) {
      s[2] += proficiency;
      s_b[2] = true;
    }
    if (!s_b[5]) {
      s[5] += proficiency;
      s_b[5] = true;
    }
  } else if (b == "Sailor") {
    if (!s_b[3]) {
      s[3] += proficiency;
      s_b[3] = true;
    }
    if (!s_b[11]) {
      s[11] += proficiency;
      s_b[11] = true;
    }
  } else if (b == "Soldier") {
    if (!s_b[3]) {
      s[3] += proficiency;
      s_b[3] = true;
    }
    if (!s_b[7]) {
      s[7] += proficiency;
      s_b[7] = true;
    }
  } else if (b == "Urchin") {
    if (!s_b[15]) {
      s[15] += proficiency;
      s_b[15] = true;
    }
    if (!s_b[16]) {
      s[16] += proficiency;
      s_b[16] = true;
    }
  }
}

void Character::Ability_improve() {
  if (level == 4 || level == 8 || level == 12 || level == 16 || level == 19) {
    printf("%s %d %s \n",
           "You reached",
           level,
           " level, that means that you have to choose whether improve one ability +2(type 1) or two abilities +1(type 2)");
    int one_or_two_abilities = -1;//abilityLevel_Up
    cin >> one_or_two_abilities;
    one_or_two_abilities = Correctness_of_input(one_or_two_abilities, 1, 2);
    if (one_or_two_abilities == 1) {
      printf("%s \n", "What ability do you want to improve +2 ? Str(1),Dex(2),Con(3),Int(4),Wis(5),Cha(6)");
      cin >> one_or_two_abilities;
      one_or_two_abilities = Correctness_of_input(one_or_two_abilities, 1, 6);
      Set(one_or_two_abilities + 2, 2);
    } else {
      printf("%s \n",
             "What abilities do you want to improve +1 ? Str(1),Dex(2),Con(3),Int(4),Wis(5),Cha(6) *Type 2 spaced numbers*");
      int one_or_two_abilities1 = 0;
      cin >> one_or_two_abilities >> one_or_two_abilities1;
      one_or_two_abilities = Correctness_of_input(one_or_two_abilities, 1, 6);
      one_or_two_abilities1 = Correctness_of_input(one_or_two_abilities1, 1, 6);
      Set(one_or_two_abilities + 2, 1);
      Set(one_or_two_abilities1 + 2, 1);
    }
  }
}

void Character::Race_Choosal(Random_Generator_ * Rand_gen) {
  printf("%s \n", "It is time to choose your race. What it will be?");
  printf("%s \n", "1. Dragonborn (10 subraces)\n"
                  "2. Dwarf (3 subraces)\n"
                  "3. Elf (7 subraces)\n"
                  "4. Gnome (3 subraces)\n"
                  "5. Goblin\n"
                  "6. Half-Elf (5 subraces)\n"
                  "7. Half-Orc ( or Orc )\n"
                  "8. Halfling (3 subraces)\n"
                  "9. Human (2 subraces)\n"
                  "10. Lizardfolk\n"
                  "11. Tiefling (11 subraces)\n"
                  "Type number, and proceed");
  int race = 9;
  std::cin >> race;
  race = Correctness_of_input(race, 1, 11);
  int subrace = 0;
  if (race == 1) {
    printf("%s \n", "Choose your subrace. What it will be?");
    printf("%s \n", "1. Black (Acid) 30ft. line\n"
                    "2. Blue (Lightning) 30ft. line\n"
                    "3. Brass (Fire) 30ft. line\n"
                    "4. Bronze (Lightning) 30ft. line\n"
                    "5. Copper (Acid) 30ft. line\n"
                    "6. Gold (Fire) 15ft. cone\n"
                    "7. Green (Poison) 15ft. cone\n"
                    "8. Red (Fire) 15ft. cone\n"
                    "9. Silver (Cold) 15ft. cone\n"
                    "10. White (Cold) 15ft. cone\n"
                    "Type number, and proceed");
    cin >> subrace;
    subrace = Correctness_of_input(subrace, 1, 10);
    int a = 0, b = 0, c = 0;
    Size_Set(Rand_gen, a, b, c, race, subrace, subrace);
    race_of_character = new Dragonborn();
    race_of_character->Create(subrace - 1, a, b, c);
    Race_Get_Abilities();
    ConcreteAbilityModifier();
  } else if (race == 2) {
    printf("%s \n", "Choose your subrace. What it will be?");
    printf("%s \n", "1. Duergar\n"
                    "2. Hill\n"
                    "3. Mountain\n"
                    "Type number, and proceed");
    cin >> subrace;
    subrace = Correctness_of_input(subrace, 1, 3);
    int a = 0, b = 0, c = 0;
    Size_Set(Rand_gen, a, b, c, race, subrace, subrace);
    //multirace
    race_of_character = new Dwarf();
    race_of_character->Create(subrace - 1, a, b, c);
    Race_Get_Abilities();
    ConcreteAbilityModifier();
  } else if (race == 3) {
    printf("%s \n", "Choose your subrace. What it will be?");
    printf("%s \n", "1. Drow \n"
                    "2. Eladrin \n"
                    "3. High\n"
                    "4. Sea\n"
                    "5. Shadar-kai\n"
                    "6. Wood\n"
                    "Type number, and proceed");
    cin >> subrace;
    subrace = Correctness_of_input(subrace, 1, 6);
    int a = 0, b = 0, c = 0;
    Size_Set(Rand_gen, a, b, c, race, subrace, subrace);
    race_of_character = new Elf();
    race_of_character->Create(subrace - 1, a, b, c);
    Race_Get_Abilities();
    ConcreteAbilityModifier();
  } else if (race == 4) {
    printf("%s \n", "Choose your subrace. What it will be?");
    printf("%s \n", "1. Deep/Svirfneblin\n"
                    "2. Forest\n"
                    "3. Rock\n"
                    "Type number, and proceed");
    cin >> subrace;
    subrace = Correctness_of_input(subrace, 1, 3);
    int a = 0, b = 0, c = 0;
    Size_Set(Rand_gen, a, b, c, race, subrace, subrace);

    race_of_character = new Gnome();
    race_of_character->Create(subrace - 1, a, b, c);
    Race_Get_Abilities();
    ConcreteAbilityModifier();
  } else if (race == 5) {
    int a = 0, b = 0, c = 0;
    Size_Set(Rand_gen, a, b, c, race, subrace, subrace);

    race_of_character = new Goblin();
    race_of_character->Create(subrace - 1, a, b, c);
    Race_Get_Abilities();
    ConcreteAbilityModifier();
  } else if (race == 6) {
    printf("%s \n", "Choose your subrace. What it will be?");
    printf("%s \n", "1. Common\n"
                    "2. Aquatic Elf Descent\n"
                    "3. Drow Descent\n"
                    "4. Moon Elf or Sun Elf Descent\n"
                    "5. Wood Elf Descent\n"
                    "Type number, and proceed");
    cin >> subrace;
    subrace = Correctness_of_input(subrace, 1, 5);
    int a = 0, b = 0, c = 0;
    Size_Set(Rand_gen, a, b, c, race, subrace, subrace);
    race_of_character = new Half_Elf();
    race_of_character->Create(subrace - 1, a, b, c);
    Race_Get_Abilities();
    ConcreteAbilityModifier();
  } else if (race == 7) {
    printf("%s \n", "Choose your subrace. What it will be?");
    printf("%s \n", "1. Half-Orc\n"
                    "2. Orc\n"
                    "Type number, and proceed");
    cin >> subrace;
    subrace = Correctness_of_input(subrace, 1, 10);
    int a = 0, b = 0, c = 0;
    Size_Set(Rand_gen, a, b, c, race, subrace, subrace);
    race_of_character = new Half_Orc();
    race_of_character->Create(subrace - 1, a, b, c);
    Race_Get_Abilities();
    ConcreteAbilityModifier();
  } else if (race == 8) {
    printf("%s \n", "Choose your subrace. What it will be?");
    printf("%s \n", "1. Ghostwise\n"
                    "2. Lightfoot\n"
                    "3. Stout\n"
                    "Type number, and proceed");
    cin >> subrace;
    subrace = Correctness_of_input(subrace, 1, 3);
    int a = 0, b = 0, c = 0;
    Size_Set(Rand_gen, a, b, c, race, subrace, subrace);
    race_of_character = new Halfling();
    race_of_character->Create(subrace - 1, a, b, c);
    Race_Get_Abilities();
    ConcreteAbilityModifier();
  } else if (race == 9) {
    printf("%s \n", "Choose your subrace. What it will be?");
    printf("%s \n", "1. Common\n"
                    "2. Variant\n"
                    "Type number, and proceed");
    cin >> subrace;
    subrace = Correctness_of_input(subrace, 1, 10);
    int a = 0, b = 0, c = 0;
    Size_Set(Rand_gen, a, b, c, race, subrace, subrace);

    race_of_character = new Human();
    race_of_character->Create(subrace - 1, a, b, c);
    Race_Get_Abilities();
    ConcreteAbilityModifier();
  } else if (race == 10) {
    int a = 0, b = 0, c = 0;
    Size_Set(Rand_gen, a, b, c, race, subrace, subrace);

    race_of_character = new Lizardfolk();
    race_of_character->Create(subrace - 1, a, b, c);
    Race_Get_Abilities();
    ConcreteAbilityModifier();
  } else if (race == 11) {
    printf("%s \n", "Choose your subrace. What it will be?");
    printf("%s \n", "1. Common\n"
                    "2. Asmodeus\n"
                    "3. Baalzebul\n"
                    "4. Dispater\n"
                    "5. Fierna\n"
                    "6. Glasya\n"
                    "7. Levistus\n"
                    "8. Mammon\n"
                    "9. Mephistopheles\n"
                    "10. Variant\n"
                    "11. Zariel\n"
                    "Type number, and proceed");
    cin >> subrace;
    subrace = Correctness_of_input(subrace, 1, 11);
    int a = 0, b = 0, c = 0;
    Size_Set(Rand_gen, a, b, c, race, subrace, subrace);

    race_of_character = new Tiefling();
    race_of_character->Create(subrace - 1, a, b, c);
    Race_Get_Abilities();
    ConcreteAbilityModifier();
  }
}

void Character::Race_Get_Abilities() {
  Str += race_of_character->get(4);
  Dex += race_of_character->get(5);
  Con += race_of_character->get(6);
  Int += race_of_character->get(7);
  Wis += race_of_character->get(8);
  Cha += race_of_character->get(9);
}

void Character::Set(int a, int b) {// a - what parameter will be changed, b - modifier(can be negative)
  a = Correctness_of_input(a, 0, 14);
  if (a == 1) { experience += b; }
  else if (a == 2) { health += b; }
  else if (a == 3) { Str += b; }
  else if (a == 4) { Dex += b; }
  else if (a == 5) { Con += b; }
  else if (a == 6) { Int += b; }
  else if (a == 7) { Wis += b; }
  else if (a == 8) { Cha += b; }
  else if (a == 9) { armor_class += b; }
  else if (a == 10) { if (b < 0)deathsaves_f++; else deathsaves_s++; }
  else if (a == 11) { printf("%s \n", "reserved for Skills"); }
  else if (a == 12) { printf("%s \n", "reserved for weapon"); }
  else if (a == 13) { printf("%s \n", "reserved for inventory"); }
  else if (a == 14) { printf("%s \n", "reserved for story/background"); }
}

int Character::Get(int a) {
  if (a == 1) { return experience; }
  else if (a == 2) { return health; }
  else if (a == 3) { return Str; }
  else if (a == 4) { return Dex; }
  else if (a == 5) { return Con; }
  else if (a == 6) { return Int; }
  else if (a == 7) { return Wis; }
  else if (a == 8) { return Cha; }
  else if (a == 9) { return armor_class; }
  else if (a == 10) { return deathsaves_f; }
  else if (a == 11) { return deathsaves_s; }
  else if (a == 12) {
    cout << Equiped[0].get_name() << endl;
    return -3;
  } // left_hand
  else if (a == 13) {
    cout << Equiped[1].get_name() << endl;
    return -3;
  } // right_hand
  else if (a == 14) {
    cout << Equiped[2].get_name() << endl;
    return -3;
  }
  else if (a == 15) {
    cout << storyline << endl;
    return 1;
  }//reserved for story/background
  else if (a == 16) { return passive_perception; }
  else if (a == 17) { return state; }
  else if (a == 18) { return sex; }
  else if (a == 19) { return money[4]; }
  else if (a == 20) { return maxhealth; }
  else if (a == 21) { return health_dice; }
  else if (a == 22) { return advantage; }
  else if (a == 23) { return disadvantage; }
  else if (a == 24) { return perception_advantage; }
  else if (a == 25) { return classType.get(0); }
  else if (a == 26) { return race_of_character->get(0); }//type
  else if (a == 27) { return race_of_character->get(1); }//height
  else if (a == 28) { return race_of_character->get(2); }//weight
  else if (a == 29) { return race_of_character->get(10); }//Movement
  else if (a == 31) { return race_of_character->get(11); }//Size
  else if (a == 32) { return race_of_character->get(12); }//Darkvision
  else if (a == 33) { return race_of_character->get(13); }//damage resist
  //else if (a == ) { return ; }
  //else if (a == ) { return ; }
  //else if (a == ) { return ; }
  //else if (a == ) { return ; }
  return -1;
}

Item * Character::Factory_Complex(string &a) {
  printf("Control reached Factory_complex 0\n");
  Items_Factory<Weapon> Weapon_Factory;
  Items_Factory<Ranged_Weapon> Ranged_Weapon_Factory;
  Items_Factory<Armor> Armor_Factory;
  Items_Factory<Usables> Usables_Factory;
  Items_Factory<Ammo> Ammo_Factory;
  Items_Factory<Magic_Items> Magic_Items_Factory;
  Existing_Items E_I;
  printf("Control reached Factory_complex 1\n");
  for (int i = 0; i < kAll_Num; i++) {
    if (i < kWeapon_NUM && a == E_I.Weapon_s[i]) {printf("Control reached Factory_complex 1_1\n"); return Weapon_Factory.create(a); }
    else if (i < kRanged_Weapon_NUM &&a == E_I.Ranged_Weapon_s[i]) {printf("Control reached Factory_complex 1_2\n"); return Ranged_Weapon_Factory.create(a); }
    else if (i < kAmmo_NUM &&a == E_I.Ammo_s[i]) {printf("Control reached Factory_complex 1_5\n"); return Ammo_Factory.create(a); }
    else if (i < kArmor_NUM &&a == E_I.Armor_s[i]) {printf("Control reached Factory_complex 1_3\n"); return Armor_Factory.create(a); }
    else if (i < kUsable_NUM &&a == E_I.Usable_s[i]) {printf("Control reached Factory_complex 1_4\n"); return Usables_Factory.create(a); }
    else if (i < kMagic_Items_NUM &&a == E_I.Magic_Items_s[i]) {printf("Control reached Factory_complex 1_6\n"); return Magic_Items_Factory.create(a); }
    else if (i == kUsable_NUM - 1) {
      printf("Error in Factory complex\n");
      return nullptr;
    }
  }
  printf("Control reached Factory_complex 3\n");
  return nullptr;
}

void Character::Add_Money(int type, int sum) {
  type = Correctness_of_input(type, 0, 3);
  money[type] += sum;
  money[4] += static_cast<int>(money[type] * pow(10, type)); // im sure integer will be in "()"
}

void Character::Add_To_Item_Map(string &a) {
  auto iter = items_map.find(inventory[inventory.size() - 1]->get_name());
  if (iter != items_map.end()) {
    if (a != "Backpack") {
      items_map.at(inventory[inventory.size() - 1]->get_name())
          ->set_count(inventory[inventory.size() - 1]->get_count());
    }
    inventory.pop_back();
  } else {
    items_map.insert(std::pair(a, inventory[inventory.size() - 1]));
  }
}

bool Character::Paying_Money(int how_many_copper) {
  if (money[4] < how_many_copper) {
    return false;
  } else {
    money[4] -= how_many_copper;
    int dif = 1, i = 0;
    while (dif != 0) {
      if (how_many_copper > 0) {
        dif = static_cast<int>(how_many_copper - money[i] * pow(10, i));
        money[i] = 0;
        how_many_copper = dif;
      } else {
        dif = how_many_copper;
        i = 3;
      }
      if (how_many_copper < 0) {
        dif *= (-1);
        for (int j = i; j > -1; j--) {
          int t = static_cast<int>(dif / pow(10, j));
          //cout <<"t = " << t << endl;
          money[j] += t;
          dif -= t * pow(10, j);
          if (dif == 0) break;
        }
        break;
      }
      i++;
    }
  }
  return true;
}

int Character::Add_To_Inventory() {
  Items_Factory<Usables> Usables_Factory1;
  string a = "Backpack";
  inventory.push_back(Usables_Factory1.create(a));
  Add_To_Item_Map(a);
  printf("Your Backpack is a black hole without any limits, but you can carry not as much weight,"
         " so choose wisely what to take with you in future journeys\n");
  printf("Do you want to take anything with you ? (Y)/(N)\n");
  cin >> a;
  if (a[0] == 'N') {
    return 0;
  } else {
    bool some_more = true;
    while (some_more) {
      int item_;
      printf("You can add this types of items:\n"
             "1. Weapon\n"
             "2. Ranged weapon\n"
             "3. Ammo\n"
             "4. Armor\n"
             "5. Usables\n"
             "6. Magic Items\n"
             "(this list will be extended in future versions)\n");
      cin >> item_;
      item_ = Correctness_of_input(item_, 1, 6);
      cout << "Control reach method Add_To_Inventory 0\n";
      cout << money[4] << endl;
      int limit[7] = {0, kWeapon_NUM, kRanged_Weapon_NUM + limit[1], kAmmo_NUM + limit[2], kArmor_NUM + limit[3], kUsable_NUM + limit[4],
                       kMagic_Items_NUM + limit[5]};
      Existing_Items E_P;
      cout << "Control reach method Add_To_Inventory 1\n";
      for (int i = limit[item_ - 1]; i < limit[item_]; i++) {
        cout << i + 1 << ". " << E_P.All_s[i] << endl;
      }
      cin >> item_;
      item_ = Correctness_of_input(item_, 1, limit[6] + 1);
      cout << "Control reach method Add_To_Inventory 2\n";
      a = E_P.All_s[item_ - 1];
      cout << "Control reach method Add_To_Inventory 2_2\n";
      inventory.push_back(Factory_Complex(a));
      cout << "Control reach method Add_To_Inventory 3\n";
      if (Paying_Money(inventory[inventory.size() - 1]->get_cost())) {
        cout << "Control reach method Add_To_Inventory 4\n";
        Add_To_Item_Map(a);
      } else
        printf("%s %d %s %d \n",
               "You have not enough money for that. Your money(in copper equivalent) are:",
               money[4],
               " and price is ",
               inventory[inventory.size() - 1]->get_cost());

      printf("Do you want to add something?(Y)/(N)\n");
      cin >> a;
      if (a[0] == 'N') {
        some_more = false;
      }
    }
    return 0;
  }
}

void Character::Equip_Item(int where, Item *what) {
  if (where < 2) {
    if (&Equiped[where] != nullptr) {// need to try it hard
      Equiped[where].equip(-1);
    }
    Equiped[where] = *what;
  } else if (where == 2) {
    if (classType.get(0) == 0) {
      armor_class = 10 + DexModifier + ConModifier;
    } else {
      armor_class = 0;
    }
    Equiped[where] = *what;
    int armor_class_bonus[3] = {DexModifier, min(DexModifier, 2), 0};
    armor_class = Equiped[where].get(2) + armor_class_bonus[Equiped[where].get(0)];
  } else {
    printf("non-standart body\n");
    Equiped[where] = *what;
  }
}

void Character::Equiping_Item() {
  printf("Control reached Equiping_Item 0 \n");
  Item *what;
  cout << "You might Equip Something. Choose where and what.\n";
  cout << "Now lets see what you have got in your backpack\n";
  vector<string> names;
  int k = 0;
  for (auto it = items_map.begin(); it != items_map.end(); it++) {
    names.push_back(it->first);
    cout << k + 1 << '.' << it->first << endl;
    k++;
  }
  printf("Control reached Equiping_Item 1 \n");
  if (k > 1) {
    cout << "You can equip something. Choose what.(type number)\n";
    int what_;
    cin >> what_;
    printf("Control reached Equiping_Item 2 \n");
    if (what_ == 1) {
      cout << " You already got " << names[what_ - 1] << " on you\n";
      what_ = 0;
    }
    printf("Control reached Equiping_Item 3 \n");
    what_ = Correctness_of_input(what_, 1, k + 1);
    if (items_map.find(names[what_ - 1])->second->is_equiped()) {
      cout << "it is already equipped!\n";
    } else {
      printf("Control reached Equiping_Item 4 \n");
      what = items_map.find(names[what_ - 1])->second;
      items_map.find(names[what_ - 1])->second->equip(1);
      cout << "Possible places to equip are:\n";
      cout << "Hands: Left(0), Right(1), extra(3-4)\n";
      cout << "Body: upper/upper+lower(2)\n";
      cout << "Fingers: (5-9)\n";
      int where;
      cin >> where;
      where = Correctness_of_input(where, 0, 9);
      printf("Control reached Equiping_Item 5 \n");
      Equip_Item(where, what);
      printf("Do u want to add something to your equipment? Yes(0), No(1)\n");
      cin >> k;
      delete what;
      if (k == 0) { Equiping_Item(); }
    }
  }
  cout << "You can Equip Nothing.\n";
}

int Character::Healing_Injuring(int value) {
  if (value > 0) {
    health += value;
    if (health > maxhealth) health = maxhealth;
  } else {
    if (health <= value && value - health < maxhealth) {
      state = 1; // incapacitated
    } else if (value - health >= maxhealth) {
      state = 3; // instantly dead;
    } else {
      health -= value;
    }
  }
  return health;
}

int Character::Level_Up(Random_Generator_ * Rand_gen) {
  Existing_Types E;
  if (experience > E.experience_per_level[level]) {
    level++;
    proficiency = ProficiencySetter();
    health = maxhealth;
    Ability_improve();
    ConcreteAbilityModifier();
    maxhealth = Health_Level_Up(Rand_gen, health_dice, ConModifier, maxhealth);
    return Level_Up(Rand_gen);
  }
  printf("%s %d \n", "Your level:", level);
  printf("%s %d \n", "Your max health:", maxhealth);
  printf("%s %d \n", "Your health:", health);
  return 0;
}

void Character::Class_Set_Wealth(Random_Generator_ * Rand_gen) {
  int wealth[12][3] = {{2, 4, 10}, {5, 4, 10}, {5, 4, 10}, {2, 4, 10}, {5, 4, 10}, {5, 4, 1},
                       {5, 4, 10}, {5, 4, 10}, {4, 4, 10}, {3, 4, 10}, {4, 4, 10}, {4, 4, 10}};
  int ctype = classType.get(0);
  // num of dices, dice* , modifier
  // *in gold
  int funds = 0;
  for (int i = 0; i < wealth[ctype][0]; i++) {
    funds += Rand_gen->Rand(1, wealth[ctype][1]) * wealth[ctype][2];
  }
  Add_Money(2, funds);
}

void Character::SetClass(Random_Generator_ * Rand_gen) {
  printf("Choose your class: \n");
  int class_type_ = 0;
  printf("1. Barbarian\n"
         "2. Bard\n"
         "3. Cleric\n"
         "4. Druid\n"
         "5. Fighter\n"
         "6. Monk\n"
         "7. Paladin\n"
         "8. Ranger\n"
         "9. Rouge\n"
         "10. Sorcerer\n"
         "11. Warlock\n"
         "12. Wizard\n");
  cin >> class_type_;
  class_type_ = Correctness_of_input(class_type_, 1, 12);
  classType.set(class_type_ - 1, &s_b);
  health_dice = classType.get(20);
  proficiency = ProficiencySetter();
  //21-38 => s[0] - s[17]
  Class_Set_Wealth(Rand_gen);
  for (int i = 21; i < 38; i++) {
    if (classType.get(i) == 1 && !s_b[i - 21]) {
      s[i - 21] += proficiency;
      s_b[i - 21] = true;
    }
  }
}

void Character::SetSkill(int c[]) {
  for (int j = 0; j < 18; j++) {
    if (j == 0 || j == 2 || j == 5 || j == 8 || j == 10 ||
        j == 14) { c[j] += IntModifier; }//acrobatics,arcana,history,investigation,nature,religion
    else if (j == 1 || j == 6 || j == 9 || j == 11 ||
        j == 17) { c[j] += WisModifier; }//animalHandling,.s[6],medicine,perception,survival
    else if (j == 3) { c[j] += StrModifier; }//athletics
    else if (j == 4 || j == 7 || j == 12 ||
        j == 13) { c[j] += ChaModifier; }//deception,intimidation,performance,persuasion
    else if (j == 15 || j == 16) { c[j] += DexModifier; }//sleightOfHand,stealth
  }
}

int Character::GetSkill(int a) {
  a = Correctness_of_input(a, 0, 17);
  return s[a];
}

void Character::Starting_Health() {
  if (maxhealth == 0) {
    maxhealth = health_dice + ConModifier;
    health = maxhealth;
  } else {
    printf("Health Increase: Error\n");
  }
}


