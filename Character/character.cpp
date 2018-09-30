

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

Character::Character(Random_Generator_ * Rand_gen,int storyline_, int exp, int levl, int Stre, int Dext,
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
  storyline_i = storyline_;
  storyline = "";
  sex = sex_;
  if (exp < E.experience_per_level[levl - 1]) { exp = E.experience_per_level[levl - 1]; }
  experience = exp;
  Str = Stre;
  Dex = Dext;
  Con = Cons;
  Int = Inte;
  Wis = Wisd;
  Cha = Charisma;
  Maximum_Parameter_Value();
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
  Equiped.resize(10);
  printf("Control reach 4\n");
  SetSkill(s);
  printf("Control reach 5\n");
  proficiency = ProficiencySetter();
  printf("Control reach 6\n");
  passive_perception = PassivePerceptionSetter(WisModifier, perception_advantage, perception_disadvantage);
  printf("Control reach 7\n");
  Race_Choosal(Rand_gen);
  printf("Control reach 8\n");
  StorySetsSkills(s, s_b, storyline_i);
  printf("Control reach 9\n");
  SetClass(Rand_gen);
  printf("Control reach 10\n");
  Starting_Health();
  printf("%s %d \n","Control reach 11 armor class = ", armor_class);
  if (classType.get(0) == 0) armor_class = 10 + DexModifier + ConModifier;
  level = 1;
  printf("%s %d ","Control reach 12\n", armor_class);
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
  //race_of_character = nullptr;
  delete[] s;
  delete[] s_b;
  inventory.clear();
  items_map.clear();
  //delete[] Equiped;
};

void Character::Maximum_Parameter_Value(){
  if(Str > 20) Str = 20;
  if(Dex > 20) Dex = 20;
  if(Con > 20) Con = 20;
  if(Int > 20) Int = 20;
  if(Wis > 20) Wis = 20;
  if(Cha > 20) Cha = 20;
}

int Character::Ability_Random_Sets(Random_Generator_ * Rand_gen) {
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
    cout << "*Or type 3 to re-roll\n";
    int s[7];
    bool checked[6] = {false};
    s[6] = IsNumber(s[6], 1, 3);
    if (s[6] == 3) return Ability_Random_Sets(Rand_gen);
    cout << "type six numbers what represents to what skill you apply each value "
            "1.Str, 2.Dex, 3.Con, 4.Int, 5.Wis, 6.Cha\n";
    for (int i = 0; i < 6; i++) {
      //cin >> s[i];
      s[i] = IsNumber(s[i],1,6);
      if (!checked[s[i] - 1]) checked[s[i] - 1] = true;
      else{
        while(checked[s[i]]){
          printf("You have already used this number ");
          cout << s[i] << endl;
          //cin >> s[i];
          s[i] = IsNumber(s[i],1,6);
        }
      }
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

int Character::ProficiencySetter() {
  if (level < 5) return 2;
  else if (level > 4 && level < 9) return 3;
  else if (level > 8 && level < 13) return 4;
  else if (level > 12 && level < 17) return 5;
  else if (level > 16 && level < 21) return 6;
  return -3;
}

int Character::PassivePerceptionSetter(int a, bool b, bool c) {
  if (b) a += 5;
  if (c) a -= 5;
  return 10 + a;
}

void Character::StorySetsSkills(int s[], bool s_b[], int storyline_i) {
  Existing_Types E;
  storyline = E.stories[storyline_i];
  string b = storyline;
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
} // to be reconsidered?

void Character::Ability_improve() {
  if (level == 4 || level == 8 || level == 12 || level == 16 || level == 19) {
    printf("%s %d %s \n",
           "You reached",
           level,
           " level, that means that you have to choose whether improve one ability +2(type 1) or two abilities +1(type 2)");
    int one_or_two_abilities = -1;//abilityLevel_Up
    //cin >> one_or_two_abilities;
    one_or_two_abilities = IsNumber(one_or_two_abilities, 1, 2);
    if (one_or_two_abilities == 1) {
      printf("%s \n", "What ability do you want to improve +2 ? 1.Str, 2.Dex, 3.Con, 4.Int, 5.Wis, 6.Cha");
      //cin >> one_or_two_abilities;
      one_or_two_abilities = IsNumber(one_or_two_abilities, 1, 6);
      Set(one_or_two_abilities + 2, 2);
    } else {
      printf("%s \n",
             "What abilities do you want to improve +1 ? 1.Str, 2.Dex, 3.Con, 4.Int, 5.Wis, 6.Cha *Type 2 spaced numbers*");
      int one_or_two_abilities1 = 0;
      //cin >> one_or_two_abilities >> one_or_two_abilities1;
      one_or_two_abilities = IsNumber(one_or_two_abilities, 1, 6);
      one_or_two_abilities1 = IsNumber(one_or_two_abilities1, 1, 6);
      Set(one_or_two_abilities + 2, 1);
      Set(one_or_two_abilities1 + 2, 1);
    }
  }
}

void Character::Race_Choosal(Random_Generator_ * Rand_gen) {
  printf("%s \n", "It is time to choose your race. What it will be?");
  Race_Factory Race_Factory_;
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
  int a = 0, b = 0, c = 0;
  race = IsNumber(race, 1, 11);
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
    subrace = IsNumber(subrace, 1, 10);
    printf("Control reach Race_Choosal 1\n");
  } else if (race == 2) {
    printf("%s \n", "Choose your subrace. What it will be?");
    printf("%s \n", "1. Duergar\n"
                    "2. Hill\n"
                    "3. Mountain\n"
                    "Type number, and proceed");
    subrace = IsNumber(subrace, 1, 3);
    printf("Control reach Race_Choosal 2\n");
  } else if (race == 3) {
    printf("%s \n", "Choose your subrace. What it will be?");
    printf("%s \n", "1. Drow \n"
                    "2. Eladrin \n"
                    "3. High\n"
                    "4. Sea\n"
                    "5. Shadar-kai\n"
                    "6. Wood\n"
                    "Type number, and proceed");
    subrace = IsNumber(subrace, 1, 6);
  } else if (race == 4) {
    printf("%s \n", "Choose your subrace. What it will be?");
    printf("%s \n", "1. Deep/Svirfneblin\n"
                    "2. Forest\n"
                    "3. Rock\n"
                    "Type number, and proceed");
    subrace = IsNumber(subrace, 1, 3);
  } else if (race == 5) {
    cout << "Goblin \n";
  } else if (race == 6) {
    printf("%s \n", "Choose your subrace. What it will be?");
    printf("%s \n", "1. Common\n"
                    "2. Aquatic Elf Descent\n"
                    "3. Drow Descent\n"
                    "4. Moon Elf or Sun Elf Descent\n"
                    "5. Wood Elf Descent\n"
                    "Type number, and proceed");
    subrace = IsNumber(subrace, 1, 5);
  } else if (race == 7) {
    printf("%s \n", "Choose your subrace. What it will be?");
    printf("%s \n", "1. Half-Orc\n"
                    "2. Orc\n"
                    "Type number, and proceed");
    subrace = IsNumber(subrace, 1, 10);
  } else if (race == 8) {
    printf("%s \n", "Choose your subrace. What it will be?");
    printf("%s \n", "1. Ghostwise\n"
                    "2. Lightfoot\n"
                    "3. Stout\n"
                    "Type number, and proceed");
    subrace = IsNumber(subrace, 1, 3);
  } else if (race == 9) {
    printf("%s \n", "Choose your subrace. What it will be?");
    printf("%s \n", "1. Common\n"
                    "2. Variant\n"
                    "Type number, and proceed");
    subrace = IsNumber(subrace, 1, 10);
  } else if (race == 10) {
    cout << "Lizardfolk \n";
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
    subrace = IsNumber(subrace, 1, 11);
  }
  race_of_character = Race_Factory_.Create(race - 1,subrace - 1);
  Race_Get_Abilities();
  ConcreteAbilityModifier();
}

void Character::Race_Get_Abilities() {
   /*cout << " type = " << race_of_character->get(0) <<"\n";
  cout << " height = " << race_of_character->get(1) <<"\n";
  cout << " weight = " << race_of_character->get(2) <<"\n";
  cout << " age = " << race_of_character->get(3) <<"\n";
  cout << " Str = " << race_of_character->get(4) <<"\n";
  cout << " Dex = " << race_of_character->get(5) <<"\n";
  cout << " Con = " << race_of_character->get(6) <<"\n";
  cout << " Int = " << race_of_character->get(7) <<"\n";
  cout << " Wis = " << race_of_character->get(8) <<"\n";
  cout << " Cha = " << race_of_character->get(9) <<"\n";
  cout << " Movement = " << race_of_character->get(10) <<"\n";
  cout << " Size = " << race_of_character->get(11) <<"\n";
  cout << " Darkvision = " << race_of_character->get(12) <<"\n";
  cout << " damage_resistance = " << race_of_character->get(13) <<"\n";
  cout << " subtype = " << race_of_character->get(14) <<"\n";*/
  Str += race_of_character->get(4);
  Dex += race_of_character->get(5);
  Con += race_of_character->get(6);
  Int += race_of_character->get(7);
  Wis += race_of_character->get(8);
  Cha += race_of_character->get(9);
  Maximum_Parameter_Value();
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
  Maximum_Parameter_Value();
}

int Character::Get(int a) {
  if (a == 1) { return storyline_i; }
  else if (a == 2) { return sex; }
  else if (a == 3) { return experience; }
  else if (a == 4) { return level; }
  else if (a == 5) { return health; }
  else if (a == 6) { return maxhealth; }
  else if (a == 7) { return health_dice; }
  else if (a == 8) { return Str; }
  else if (a == 9) { return Dex; }
  else if (a == 10) { return Con; }
  else if (a == 11) { return Int; }
  else if (a == 12) { return Wis; }
  else if (a == 13) { return Cha; }
  else if (a == 14) { return armor_class; }
  else if (a == 15) { return deathsaves_s; }
  else if (a == 16) { return deathsaves_f; }
  else if (a == 17) { return money[0]; }
  else if (a == 18) { return money[1]; }
  else if (a == 19) { return money[2]; }
  else if (a == 20) { return money[3]; }
  else if (a == 21) { return money[4]; }
  else if (a == 22) { return state; }
  else if (a == 23) { return classType.get(0); }
  else if (a == 24) { return 0; }
  else if (a == 25) { return classType.get(39); }//architype
  else if (a == 26) { return race_of_character->get(0); }//type
  else if (a == 27) { return race_of_character->get(1); }
  else if (a == 28) { return race_of_character->get(2); }
  else if (a == 29) { return race_of_character->get(3); }
  else if (a == 30) { return race_of_character->get(10); }
  else if (a == 31) { return race_of_character->get(11); }
  else if (a == 32) { return race_of_character->get(12); }//Darkvision
  else if (a == 33) { return race_of_character->get(13); }
  else if (a == 34) { return race_of_character->get(14); }
  else if (a == 35) { return (int)'R'; }
  else if (a == 71) { return inventory.size(); }
  else if (a == 100) { return passive_perception; }
  else if (a == 101) { return proficiency; }
  else if (a == 102) { return StrModifier; }
  else if (a == 103) { return DexModifier; }
  else if (a == 104) { return ConModifier; }
  else if (a == 105) { return IntModifier; }
  else if (a == 106) { return WisModifier; }
  else if (a == 107) { return ChaModifier; }
  return -1;
}

bool Character::Get_bool(int a) {
  if (a == 36) { return advantage; }
  else if (a == 37) { return disadvantage; }
  else if (a == 38) { return perception_advantage; }
  else if (a == 39) { return perception_disadvantage; }
  else if (a == 40) { return s_b[0]; }
  else if (a == 41) { return s_b[1]; }
  else if (a == 42) { return s_b[2]; }
  else if (a == 43) { return s_b[3]; }
  else if (a == 44) { return s_b[4]; }
  else if (a == 45) { return s_b[5]; }
  else if (a == 46) { return s_b[6]; }
  else if (a == 47) { return s_b[7]; }//height
  else if (a == 48) { return s_b[8]; }//weight
  else if (a == 49) { return s_b[9]; }//Movement
  else if (a == 50) { return s_b[10]; }//Size
  else if (a == 51) { return s_b[11]; }//Darkvision
  else if (a == 52) { return s_b[12]; }//damage resist
  else if (a == 53) { return s_b[13]; }
  else if (a == 54) { return s_b[14]; }
  else if (a == 55) { return s_b[15]; }
  else if (a == 56) { return s_b[16]; }
  else if (a == 57) { return s_b[17]; }
  else if (a == 58) { return classType.get_bool(7); }//23
  else if (a == 59) { return classType.get_bool(8); }
  else if (a == 60) { return classType.get_bool(9); }
  else if (a == 61) { return classType.get_bool(10); }
  else if (a == 62) { return classType.get_bool(11); }
  else if (a == 63) { return classType.get_bool(12); }
  else if (a == 64) { return classType.get_bool(13); }
  else if (a == 65) { return classType.get_bool(14); }
  else if (a == 66) { return classType.get_bool(15); }
  else if (a == 67) { return classType.get_bool(16); }
  else if (a == 68) { return classType.get_bool(17); }
  else if (a == 69) { return classType.get_bool(18); }
  else if (a == 70) { return classType.get_bool(19); }
  return false;
}

vector<int> Character::Get_inventory(){
  vector<int> inventory_;
  Existing_Items E;
  //inventory_.resize(inventory.size());
  for(int k = 0;k < inventory.size();k++){
    for(int i = 0; i < kAll_Num;i++){
      if(inventory[k]->get_name() == E.All_s[i]){
        inventory_.push_back(i);
        inventory_.push_back(inventory[k]->get(2));
        break;
      }
    }
  }
  return inventory_;
} // { {(int)name_of_Item1, amount1} , {(int)name_of_Item2, amount2} ... }

Item * Character::Factory_Complex(string &a, int quantity) {
  printf("Control reached Factory_complex 0\n");
  Items_Factory<Weapon> Weapon_Factory;
  Items_Factory<Ranged_Weapon> Ranged_Weapon_Factory;
  Items_Factory<Armor> Armor_Factory;
  Items_Factory<Usables> Usables_Factory;
  Items_Factory<Ammo> Ammo_Factory;
  Items_Factory<Magic_Items> Magic_Items_Factory;
  Existing_Items E_I;
  printf("Control reached Factory_complex 1\n");
  for (int i = 0; i < kWeapon_NUM; i++) {
    if (a == E_I.Weapon_s[i]) {
      printf("Control reached Factory_complex 1_1\n");
      return Weapon_Factory.create(a,quantity);
    }
  }
  for (int i = 0; i < kRanged_Weapon_NUM; i++) {
    if (i < kRanged_Weapon_NUM && a == E_I.Ranged_Weapon_s[i]) {
      printf("Control reached Factory_complex 1_2\n");
      return Ranged_Weapon_Factory.create(a,quantity);
    }
  }
  for (int i = 0; i < kAmmo_NUM; i++) {
    if (i < kAmmo_NUM && a == E_I.Ammo_s[i]) {
      printf("Control reached Factory_complex 1_5\n");
      return Ammo_Factory.create(a,quantity);
    }
  }
  for (int i = 0; i < kArmor_NUM; i++) {
    if (i < kArmor_NUM && a == E_I.Armor_s[i]) {
      printf("Control reached Factory_complex 1_3\n");
      return Armor_Factory.create(a,quantity);
    }
  }
  for (int i = 0; i < kUsable_NUM; i++) {
    if (i < kUsable_NUM && a == E_I.Usable_s[i]) {
      printf("Control reached Factory_complex 1_4\n");
      return Usables_Factory.create(a,quantity);
    }
  }
  for (int i = 0; i < kMagic_Items_NUM; i++) {
    if (i < kMagic_Items_NUM && a == E_I.Magic_Items_s[i]) {
      printf("Control reached Factory_complex 1_6\n");
      return Magic_Items_Factory.create(a,quantity);
    }
  }

  /*for (int i = 0; i < kAll_Num; i++) {
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
  }*/
  printf("Control reached Factory_complex 3\n");
  return nullptr;
}

void Character::Add_Money(int type, int sum) {
  type = Correctness_of_input(type, 0, 3);
  cout <<"Before operation: money[" << type << "] = " << money[type] << endl;
  money[type] += sum;
  cout <<"After operation: money[" << type << "] = " << money[type] << endl;
  money[4] += (int)(money[type] * pow(10, type)); // im sure integer will be in "()"
  cout <<"money[4] = " << money[4] << endl;
}

void Character::Add_To_Item_Map(string &a) {
  auto iter = items_map.find(inventory[inventory.size() - 1]->get_name());
  if (iter != items_map.end()) {
    if (a != "Backpack") {
      items_map.at(inventory[inventory.size() - 1]->get_name())
          ->set_count(inventory[inventory.size() - 1]->get(2));
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
        dif = (int)(how_many_copper - money[i] * pow(10, i));
        money[i] = 0;
        how_many_copper = dif;
      } else {
        dif = how_many_copper;
        i = 3;
      }
      if (how_many_copper < 0) {
        dif *= (-1);
        for (int j = i; j > -1; j--) {
          int t = (int)(dif / pow(10, j));
          cout <<"t = " << t << endl;
          money[j] += t;
          cout <<"money[j] = " << money[j] << endl;
          dif -= (int)(t * pow(10, j));
          cout <<"dif = " << dif << endl;
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
  int choose_to_proceed = 0;
  Add_To_Item_Map(a);
  inventory[inventory.size() - 1]->equip(1);
  printf("Your Backpack is a black hole without any limits, but you can carry not as much weight,"
         " so choose wisely what to take with you in future journeys\n");
  printf("Do you want to take anything with you ?  Yes(1)  No(2) *\n");
  choose_to_proceed = IsNumber(choose_to_proceed,1,2);
  if (choose_to_proceed == 2) {
    return 0;
  } else {
    bool some_more = true;
    while (some_more) {
      int item_ = 0;
      printf("You can add this types of items:\n"
             "1. Weapon\n"
             "2. Ranged weapon\n"
             "3. Ammo\n"
             "4. Armor\n"
             "5. Usables\n"
             "6. Magic Items\n"
             "(this list will be extended in future versions)\n");
      //cin >> item_;
      item_ = IsNumber(item_, 1, 6);
      cout << "Control reach method Add_To_Inventory 0\n";
      cout << money[4] << endl;
      int limit[7] = {0, kWeapon_NUM, kRanged_Weapon_NUM + limit[1], kAmmo_NUM + limit[2], kArmor_NUM + limit[3], kUsable_NUM + limit[4],
                       kMagic_Items_NUM + limit[5]};
      Existing_Items E_P;
      cout << "Control reach method Add_To_Inventory 1\n";
      for (int i = limit[item_ - 1]; i < limit[item_]; i++) {
        cout << i + 1 << ". " << E_P.All_s[i] << endl;//
      }
      //cin >> item_;
      item_ = IsNumber(item_, 1, limit[6] + 1);
      cout << "Control reach method Add_To_Inventory 2\n";
      a = E_P.All_s[item_ - 1];
      int quantity = 1;
      cout << "How many "<< a <<"s do you want ?\n";
      quantity = IsNumber(quantity,1,0);
      cout << "Control reach method Add_To_Inventory 3\n";
      auto b = Factory_Complex(a,quantity);
      if (Paying_Money(b->get(0) * quantity)) {
        inventory.push_back(Factory_Complex(a,quantity));
        cout << "Control reach method Add_To_Inventory 4\n";
        Add_To_Item_Map(a);
      } else{
        printf("%s %d %s %d \n",
               "You have not enough money for that. Your money(in copper equivalent) are:",
               money[4],
               " and price is ",
               b->get(0) * quantity);
      }
      delete b;


      printf("Do you want to add something? Yes(1)  No(2)\n");
      //cin >> item_;
      item_ = IsNumber(item_,1,2);
      if (item_ == 2) {
        some_more = false;
      }
    }
    return 0;
  }
}

void Character::Equip_Item(int where, Item *what) {
  printf("Control reached Equip_Item 0 \n");
  where = Correctness_of_input(where,0,9);
  if (Equiped[where] != nullptr) {// need to try it hard  ->get(2) != 0
    Equiped[where]->equip(-1);
  } else { cout << "null check fine\n";}
  if (where < 2 || (where > 3 && where < 6)) {
    Equiped[where] = what;
    cout << "Equipped " << Equiped[where]->get_name() << endl;
    if(what->get_name() == "Shield") armor_class += 2;
  } else if (where == 2) {
    cout << "equip armor, armor class before: " << armor_class << endl;
    cout << "Control reach Equip_Item 1\n";
    Equiped[where] = what;
    int armor_class_bonus[3] = {DexModifier, min(DexModifier, 2), 0};
    armor_class = Equiped[where]->get(11) + armor_class_bonus[Equiped[where]->get(0)];
    cout << "armor class after: " << armor_class << endl;
    cout << "Equipped " << Equiped[where]->get_name() << endl;
  } else if (where < 10){
    Equiped[where] = what;
    cout << "Equipped " << Equiped[where]->get_name() << endl;
  }
  else {
    printf("non-standart body\n");
    Equiped[where] = what;
    cout << "Equipped " << Equiped[where]->get_name() << endl;
  }
}

void Character::Equiping_Item() {
  printf("Control reached Equiping_Item 0 \n");
  Item *what;
  cout << "You might Equip Something. Choose where and what.\n";
  cout << "Now lets see what you have got in your backpack\n";
  vector<string> names;
  int k = 0;
  for (auto it : items_map) { // = items_map.begin(); it != items_map.end(); it++
    names.push_back(it.first);
    cout << k + 1 << '.' << it.first << endl;
    k++;
  }
  printf("Control reached Equiping_Item 1 \n");
  if (k > 1) {
    cout << "You can equip something. Choose what.(type number)\n";
    int what_ = 0;
    what_ = IsNumber(what_,1,k+1);
    printf("Control reached Equiping_Item 2 \n");
    what_ = Correctness_of_input(what_, 1, k + 1);
    if (items_map.find(names[what_ - 1])->second->is_equiped()) {
      cout << "it is already equipped!\n";
    } else {
      printf("Control reached Equiping_Item 4 \n");
      what = items_map.find(names[what_ - 1])->second;
      cout << "Possible places to equip are:\n";
      cout << "Hands: Left(1), Right(2), extra*(4-5)\n";
      cout << "Body: upper/upper+lower(3)\n";
      cout << "Fingers: (6-10)\n";
      cout << "*only for abnormal bodies\n";
      int where = 0;
      where = IsNumber(where, 1, 10);
      while(where == 3){
        if(what->What_class() != "Armor" || what->get_name() == "Shield"){
          where = -2;
          printf("You can't equip that on your body. Choose where else\n");
          where = IsNumber(where, 1, 10);
        }
        else break;
      }
      while(where > 5 && where < 11){
        if(what->What_class() != "Ring"){
          where = -2;
          printf("You can't equip that on your finger Choose where else\n");
          where = IsNumber(where, 1, 10);
        }
        else break;
      }
      items_map.find(names[what_ - 1])->second->equip(1);
      printf("Control reached Equipping_Item 5 \n");
      Equip_Item(where - 1, items_map.find(names[what_ - 1])->second);
      printf("Do u want to add something to your equipment? Yes(1), No(2)\n");
      k = IsNumber(k,1,2);
      delete what; //bug here?
      if (k == 1) { Equiping_Item(); }
    }
  }
  cout << "You can Equip Nothing.\n";
}

void Character::Unequip_Item(int where) {
  where = Correctness_of_input(where,0,9);
  if (Equiped[where]->get(2) != 0) {// need to try it hard
    Equiped[where]->equip(-1);
    Equiped[where] = nullptr;
  } else { cout << "null check fine\n";}
  if(where == 2){
    if (classType.get(0) == 0) {
      armor_class = 10 + DexModifier + ConModifier;
    } else {
      armor_class = 0;
    }
  }
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
  storyline = E.stories[storyline_i];
  if (experience >= E.experience_per_level[level]) {
    level++;
    proficiency = ProficiencySetter();
    Ability_improve();
    ConcreteAbilityModifier();
    maxhealth = Health_Level_Up(Rand_gen, health_dice, ConModifier, maxhealth);
    health = maxhealth;
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
  int funds = 0;
  for (int i = 0; i < wealth[ctype][0]; i++) {
    funds += Rand_gen->Rand(1, wealth[ctype][1]) * wealth[ctype][2];
  }
  cout << "generated gold coins for your class: " << funds << endl;
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
  //cin >> class_type_;
  class_type_ = IsNumber(class_type_, 1, 12);
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

void Character::Inventory_Load(vector<int> item_){
  Existing_Items E;
  inventory.resize(item_.size());
  for(int i = 0; i < item_.size(); i++){
    inventory.push_back(Factory_Complex(E.All_s[item_[i]],i+1));
    cout << " loaded " << inventory[i]->get_name() << endl;
    Add_To_Item_Map(E.All_s[item_[i]]);
  }
}

void Character::Starting_Health() {
  if (maxhealth == 0) {
    maxhealth = health_dice + ConModifier;
    health = maxhealth;
  } else {
    printf("Health Increase: Error\n");
  }
}

bool Character::Load (int a[], bool b[], vector<int> item_) {
  Existing_Types E;
  s = new int[18];
  s_b = new bool[18];
  Equiped.resize(10);
  printf("Control reach Character method Load 0\n");
  for(int i = 1; i < 70;i++){
    if (i == 1) { printf("Control reach Character method Load 1\n"); storyline_i = a[i]; cout << storyline_i << " is story of " << E.stories[storyline_i] << endl; }
    else if (i == 2) {  sex = a[i]; }
    else if (i == 3) {  printf("Control reach Character method Load 3\n");experience = a[i]; }
    else if (i == 4) {  level = a[i]; }
    else if (i == 5) {  health = a[i]; }
    else if (i == 6) {  maxhealth = a[i]; }
    else if (i == 7) {  health_dice = a[i]; }
    else if (i == 8) {  Str = a[i]; }
    else if (i == 9) {  Dex = a[i]; }
    else if (i == 10) { printf("Control reach Character method Load 10\n"); Con = a[i]; }
    else if (i == 11) {  Int = a[i]; }
    else if (i == 12) {  Wis = a[i]; }
    else if (i == 13) {  Cha = a[i]; }
    else if (i == 14) {  armor_class = a[i]; }
    else if (i == 15) {  deathsaves_s = a[i]; }
    else if (i == 16) {  deathsaves_f = a[i]; }
    else if (i == 17) {  money[0] = a[i]; }
    else if (i == 18) {  money[1] = a[i]; }
    else if (i == 19) {  money[2] = a[i]; }
    else if (i == 20) {  money[3] = a[i]; }
    else if (i == 21) {  money[4] = a[i]; }
    else if (i == 22) { state = a[i]; }
    else if (i == 23) {
      //classType = new Class();
      classType.Load(a[23], b, a[35]);
    } else if (i == 26) {
      printf("Control reach Character method Load 60\n");
      Race_Factory Race_Factory_;
      race_of_character = Race_Factory_.Create(a[i],a[i+8]);//~type
      race_of_character->Load(a);
    } else if (i == 36) { printf("Control reach Character method Load (bool)\n");advantage = b[i - 36]; }
    else if (i == 37) { disadvantage = b[i - 36]; }
    else if (i == 38) { perception_advantage = b[i - 36]; }
    else if (i == 39) { perception_disadvantage = b[i - 36]; }
    else if (i > 39 && i < 58) { s_b[i - 40] = b[i - 36]; }
  }
  proficiency = ProficiencySetter();
  printf("Control reach Character method Load 91\n");
  passive_perception = PassivePerceptionSetter(WisModifier, perception_advantage, perception_disadvantage);
  Maximum_Parameter_Value();
  ConcreteAbilityModifier();
  Inventory_Load(item_);
  Equiping_Item();
  return true;
}

