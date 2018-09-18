

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <math.h>
#include "Race_Class_Background.h"
#include "Classes.h"
#include "UsefulFunctions.h"
#include "Inventory(Item)/Item.h"
#include "Inventory(Item)/Items_Factory.h"

using namespace std;

struct Skills {
  
};

vector<Race*> multirace;

class Character {
 private:
  Race* race_of_character;
  Class classType;
  string storyline;
  int experience, level;
  int health, maxhealth;
  int health_dice;
  int Str, Dex, Con, Int, Wis, Cha;
  int StrModifier, DexModifier, ConModifier, IntModifier, WisModifier, ChaModifier;
  int AC;
  int deathsaves_s, deathsaves_f;//success/failure
  int passive_perception, proficiency;
  bool advantage, disadvantage;
  bool perception_advantage;
  bool perception_disadvantage;
  int *s[18];
  /*acrobatics 0,animalHandling 1,arcana 2,athletics 3,deception 4,
history 5,insight 6,intimidation 7,investigation 8,medicine 9,
nature 10,perception 11,performance 12,persuasion 13,religion 14,
sleightOfHand 15,stealth 16,survival 17*/
  bool *s_b[18];
  int money[4]; // copper, silver, gold, platinum
  vector<Item *> inventory;
  map<std::string, Item *> items_map;
  Existing_Types E;
 public:
  Character() : race_of_character(race_of_character) {
    //race.set(24);//human
    //classType.set(0);//barbarian
    storyline = "Acolyte";
    experience = 0;
    level = 0 ;
    health = 0 ;
    maxhealth = 0 ;
    health_dice = 0 ;
    Str = 0 ;Dex = 0 ; Con = 0 ; Int = 0 ; Wis = 0 ; Cha = 0 ;
    StrModifier = 0 ; DexModifier = 0 ; ConModifier = 0 ;
    IntModifier = 0 ; WisModifier = 0 ; ChaModifier = 0 ;
    AC = 0 ;
    deathsaves_s = 0 ;
    deathsaves_f = 0 ;//success/failure
    passive_perception = 0 ;
    proficiency = 0 ;
    advantage = false; disadvantage = false;
    perception_advantage = false;
    perception_disadvantage = false;
  }
  Character(string &storyl, int exp, int levl, int Stre, int Dext,
      int Cons, int Inte, int Wisd, int Charisma){
    exp = Less_than_zero(exp);
    levl = Less_than_zero(levl);
    Stre = Less_than_zero(Stre);
    Dext = Less_than_zero(Dext);
    Cons = Less_than_zero(Cons);
    Inte = Less_than_zero(Inte);
    Wisd = Less_than_zero(Wisd);
    Charisma = Less_than_zero(Charisma);
    //ArmorClass = Less_than_zero(ArmorClass);
    health = 0 ;
    maxhealth = 0 ;
    health_dice = 0 ;
    storyline = storyl;
    if(exp < E.experience_per_level[levl - 1]){ exp = E.experience_per_level[level - 1]; }
    experience = exp;
    Str = Stre;
    Dex = Dext;
    Con = Cons;
    Int = Inte;
    Wis = Wisd;
    Cha = Charisma;
    AC = 0;
    //AC = ArmorClass;
    deathsaves_s = 0 ;
    deathsaves_f = 0 ;
    passive_perception = 0 ;
    proficiency = 0 ;
    advantage = false; disadvantage = false;
    perception_advantage = false;
    perception_disadvantage = false;
    ConcreteAbilityModifier();
    for(int i = 0; i < 18;i++){
      *s[i] = 0;
      *s_b[i] = false;
    }
    money[0] = 0;//copper
    money[1] = 0;
    money[2] = 0;
    money[3] = 0;//Pt
    SetSkill(s);
    proficiency = ProficiencySetter();
    passive_perception = PassivePerceptionSetter(WisModifier, perception_advantage, perception_disadvantage);
    Race_Choosal();
    StorySetsSkills(s,s_b,storyline);
    SetClass();
    Starting_Health();
    if(race_of_character->get(0) == 0) AC = 10 + DexModifier + ConModifier;
    level = 0;
    Level_Up();
  }

  ~Character() = default;

  int Less_than_zero(int a) {
    return a < 0 ? 0 : a;
  }

  int AbilityModifier(int a) {
    return (a - 10) / 2;
  }

  void ConcreteAbilityModifier(){
    StrModifier = AbilityModifier(Str);
    DexModifier = AbilityModifier(Dex);
    ConModifier = AbilityModifier(Con);
    IntModifier = AbilityModifier(Int);
    WisModifier = AbilityModifier(Wis);
    ChaModifier = AbilityModifier(Cha);
  }
  //new
  int ProficiencySetter() {
    if (level < 5) return 2;
    else if (level > 4 && level < 9) return 3;
    else if (level > 8 && level < 13) return 4;
    else if (level > 12 && level < 17) return 5;
    else if (level > 16 && level < 21) return 6;
  }

  void Size_Set(int a, int b, int c,int race1,int subrace,int negative){
    // negative for class dragonborn

    printf("%s \n",
           "insert height(ft), weight(lbs) and age(y) of your character or type zero(s) (0 100 0) to random");
    printf("%s %d %s %d %s %d %s %d %s %d %s %d \n",
           "Normal parameters for your race are: height(ft) from ",E.minHeight[race1 - 1] ,"to ", E.maxHeight[race1 - 1]," weight(lbs)from ",
           E.minWeight[race1 - 1],"to ", E.maxWeight[race1 - 1]," and age(y) from ",E.minAge[race1 - 1] ,"to ", E.maxAge[race1 - 1]);
    cin >> a >> b >> c;
    if (a <= 0 || a > E.maxHeight[race1 - 1]) { a = Random_Generator(E.minHeight[race1 - 1], E.maxHeight[race1 - 1]); }
    if (b <= 0 || b > E.maxWeight[race1 - 1]) { b = Random_Generator(E.minWeight[race1 - 1], E.maxWeight[race1 - 1]); }
    if (c <= 0 || c > E.maxAge[race1 - 1]) { c = Random_Generator(E.minAge[race1 - 1], E.maxAge[race1 - 1]); }
  }

  int PassivePerceptionSetter(int a, bool b, bool c) {
    if (b) a += 5;
    if (c) a -= 5;
    return 10 + a;
  }
  
  void StorySetsSkills(int *s[],bool *s_b[], string &b) {
    if (b == "Acolyte") {
      if (!*s_b[6]) {
        *s[6] += proficiency;
        *s_b[6] = true;
      }
      if (!*s_b[14]) {
        *s[14] += proficiency;
        *s_b[14] = true;
      }
    } else if (b == "Charlatan") {
      if (!*s_b[4]) {
        *s[4] += proficiency;
        *s_b[4] = true;
      }
      if (!*s_b[15]) {
        *s[15] += proficiency;
        *s_b[15] = true;
      }
    } else if (b == "Criminal") {
      if (!*s_b[4]) {
        *s[4] += proficiency;
        *s_b[4] = true;
      }
      if (!*s_b[16]) {
        *s[16] += proficiency;
        *s_b[16] = true;
      }
    } else if (b == "Entertainer") {
      if (!*s_b[0]) {
        *s[0] += proficiency;
        *s_b[0] = true;
      }
      if (!*s_b[12]) {
        *s[12] += proficiency;
        *s_b[12] = true;
      }
    } else if (b == "FolkHero") {
      if (!*s_b[1]) {
        *s[1] += proficiency;
        *s_b[1] = true;
      }
      if (!*s_b[17]) {
        *s[17] += proficiency;
        *s_b[17] = true;
      }
    } else if (b == "GuildArtisan") {
      if (!*s_b[6]) {
        *s[6] += proficiency;
        *s_b[6] = true;
      }
      if (!*s_b[13]) {
        *s[13] += proficiency;
        *s_b[13] = true;
      }
    } else if (b == "Hermit") {
      if (!*s_b[9]) {
        *s[9] += proficiency;
        *s_b[9] = true;
      }
      if (!*s_b[14]) {
        *s[14] += proficiency;
        *s_b[14] = true;
      }
    } else if (b == "Noble") {
      if (!*s_b[5]) {
        *s[5] += proficiency;
        *s_b[5] = true;
      }
      if (!*s_b[13]) {
        *s[13] += proficiency;
        *s_b[13] = true;
      }
    } else if (b == "Outlander") {
      if (!*s_b[3]) {
        *s[3] += proficiency;
        *s_b[3] = true;
      }
      if (!*s_b[17]) {
        *s[17] += proficiency;
        *s_b[17] = true;
      }
    } else if (b == "Sage") {
      if (!*s_b[2]) {
        *s[2] += proficiency;
        *s_b[2] = true;
      }
      if (!*s_b[5]) {
        *s[5] += proficiency;
        *s_b[5] = true;
      }
    } else if (b == "Sailor") {
      if (!*s_b[3]) {
        *s[3] += proficiency;
        *s_b[3] = true;
      }
      if (!*s_b[11]) {
        *s[11] += proficiency;
        *s_b[11] = true;
      }
    } else if (b == "Soldier") {
      if (!*s_b[3]) {
        *s[3] += proficiency;
        *s_b[3] = true;
      }
      if (!*s_b[7]) {
        *s[7] += proficiency;
        *s_b[7] = true;
      }
    } else if (b == "Urchin") {
      if (!*s_b[15]) {
        *s[15] += proficiency;
        *s_b[15] = true;
      }
      if (!*s_b[16]) {
        *s[16] += proficiency;
        *s_b[16] = true;
      }
    }
  }

  void Ability_improve(){
    if (level == 4 || level == 8 || level == 12 || level == 16  || level == 19) {
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

  void Race_Choosal() {
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
      Size_Set(a, b, c, race, subrace, subrace);
      multirace.push_back(new Dragonborn());
      multirace[multirace.size() - 1]->Create(subrace - 1, a, b, c);
      race_of_character = multirace[multirace.size() - 1];
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
      Size_Set(a, b, c, race, subrace, subrace);
      multirace.push_back(new Dwarf());
      multirace[multirace.size() - 1]->Create(subrace - 1, a, b, c);
      race_of_character = multirace[multirace.size() - 1];
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
      Size_Set(a, b, c, race, subrace, subrace);
      multirace.push_back(new Elf());
      multirace[multirace.size() - 1]->Create(subrace - 1, a, b, c);
      race_of_character = multirace[multirace.size() - 1];
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
      Size_Set(a, b, c, race, subrace, subrace);
      multirace.push_back(new Gnome());
      multirace[multirace.size() - 1]->Create(subrace - 1, a, b, c);
      race_of_character = multirace[multirace.size() - 1];
      Race_Get_Abilities();
      ConcreteAbilityModifier();
    } else if (race == 5) {
      int a = 0, b = 0, c = 0;
      Size_Set(a, b, c, race, subrace, subrace);
      multirace.push_back(new Goblin());
      multirace[multirace.size() - 1]->Create(subrace - 1, a, b, c);
      race_of_character = multirace[multirace.size() - 1];
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
      Size_Set(a, b, c, race, subrace, subrace);
      multirace.push_back(new Half_Elf());
      multirace[multirace.size() - 1]->Create(subrace - 1, a, b, c);
      race_of_character = multirace[multirace.size() - 1];
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
      Size_Set(a, b, c, race, subrace, subrace);
      multirace.push_back(new Half_Orc());
      multirace[multirace.size() - 1]->Create(subrace - 1, a, b, c);
      race_of_character = multirace[multirace.size() - 1];
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
      Size_Set(a, b, c, race, subrace, subrace);
      multirace.push_back(new Halfling());
      multirace[multirace.size() - 1]->Create(subrace - 1, a, b, c);
      race_of_character = multirace[multirace.size() - 1];
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
      Size_Set(a, b, c, race, subrace, subrace);
      multirace.push_back(new Human());
      multirace[multirace.size() - 1]->Create(subrace - 1, a, b, c);
      race_of_character = multirace[multirace.size() - 1];
      Race_Get_Abilities();
      ConcreteAbilityModifier();
    } else if (race == 10) {
      int a = 0, b = 0, c = 0;
      Size_Set(a, b, c, race, subrace, subrace);
      multirace.push_back(new Lizardfolk());
      multirace[multirace.size() - 1]->Create(subrace - 1, a, b, c);
      race_of_character = multirace[multirace.size() - 1];
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
      Size_Set(a, b, c, race, subrace, subrace);
      multirace.push_back(new Tiefling());
      multirace[multirace.size() - 1]->Create(subrace - 1, a, b, c);
      race_of_character = multirace[multirace.size() - 1];
      Race_Get_Abilities();
      ConcreteAbilityModifier();
    }
  }

  void Race_Get_Abilities(){
    Str += race_of_character->get(4);
    Dex += race_of_character->get(5);
    Con += race_of_character->get(6);
    Int += race_of_character->get(7);
    Wis += race_of_character->get(8);
    Cha += race_of_character->get(9);
  }
  
  void Set(int a, int b) {// a - what parameter will be changed, b - modifier(can be negative)
    a = Correctness_of_input(a, 0, 14);
    if (a == 1) { experience += b; }
    else if (a == 2) { health += b; }
    else if (a == 3) { Str += b; }
    else if (a == 4) { Dex += b; }
    else if (a == 5) { Con += b; }
    else if (a == 6) { Int += b; }
    else if (a == 7) { Wis += b; }
    else if (a == 8) { Cha += b; }
    else if (a == 9) { AC += b; }
    else if (a == 10) { if (b < 0)deathsaves_f++; else deathsaves_s++; }
    else if (a == 11) { printf("%s \n", "reserved for Skills"); }
    else if (a == 12) { printf("%s \n", "reserved for weapon"); }
    else if (a == 13) { printf("%s \n", "reserved for inventory"); }
    else if (a == 14) { printf("%s \n", "reserved for story/background"); }
  }

  int Get(int a) {
    a = Correctness_of_input(a, 0, 15);
    if (a == 1) { return experience; }
    else if (a == 2) { return health; }
    else if (a == 3) { return Str; }
    else if (a == 4) { return Dex; }
    else if (a == 5) { return Con; }
    else if (a == 6) { return Int; }
    else if (a == 7) { return Wis; }
    else if (a == 8) { return Cha; }
    else if (a == 9) { return AC; }
    else if (a == 10) { return deathsaves_f; }
    else if (a == 11) { return deathsaves_s; }
    else if (a == 12) { return -1; } //reserved for weapon
    else if (a == 13) { return -1; } //reserved for inventory
    else if (a == 14) { return -1; }//reserved for story/background
    else if (a == 15) { return passive_perception; }
    return -1;
  }

  Item * Factory_Complex(string &a){
    Items_Factory<Weapon> Weapon_Factory;
    Items_Factory<Ranged_Weapon> Ranged_Weapon_Factory;
    Items_Factory<Armor> Armor_Factory;
    Items_Factory<Usables> Usables_Factory;
    Items_Factory<Ammo> Ammo_Factory;
    Items_Factory<Magic_Items> Magic_Items_Factory;
    Existing_Items E_I;
    for(int i = 0;i < kUsable_NUM;i++){
      if(a == E_I.Weapon_s[i]){return Weapon_Factory.create(a);}
      else if(a == E_I.Ranged_Weapon_s[i]){return Ranged_Weapon_Factory.create(a);}
      else if(a == E_I.Armor_s[i]){return Armor_Factory.create(a);}
      else if(a == E_I.Usable_s[i]){return Usables_Factory.create(a);}
      else if(a == E_I.Ammo_s[i]){return Ammo_Factory.create(a);}
      else if(a == E_I.Magic_Items_s[i]){return Magic_Items_Factory.create(a);}
      else if(i == kUsable_NUM-1){printf("Error in Factory complex\n");return nullptr;}
    }
  }

  void Add_Money(int type,int sum){
    money[type] += sum;
  }

  int Add_To_Inventory(){
    Items_Factory<Usables> Usables_Factory1;
    string a = "Backpack";
    inventory.push_back(Usables_Factory1.create(a));
    auto iter = items_map.find(inventory[inventory.size() - 1]->get_name());
    if(iter != items_map.end()){
      inventory.pop_back();
    }
    else{
      items_map.insert(std::pair(a,inventory[inventory.size() - 1]));
    }
    printf("Your Backpack is a black hole without any limits, but you can carry not as much weight,"
           " so choose wisely what to take with you in future journeys\n");
    printf("Do you want to take anything with you ? (Y)/(N)\n");
    cin >> a;
    if(a[0] == 'N'){
      return 0;
    } else {
      bool some_more = true;
      while(some_more){
        int item_;
        printf("You can add this types of items:\n"
               "1. Weapon\n"
               "2. Ranged weapon\n"
               "3. Armor\n"
               "4. Usables\n"
               "5. Ammo\n"
               "6. Magic Items\n"
               "(this list will be extended in future versions)\n");
        cin >> item_;
        item_ = Correctness_of_input(item_,1,6);
        int limit[7] = {0,kWeapon_NUM,kRanged_Weapon_NUM + limit[1],kArmor_NUM+ limit[2],kUsable_NUM+ limit[3],
                        kAmmo_NUM+ limit[4],kMagic_Items_NUM+ limit[5]};
        Existing_Items E_P;
        for(int i = limit[item_ - 1];i < limit[item_];i++){
          cout << i + 1<< ". " << E_P.All_s[i];
        }
        cin >> item_;
        item_ = Correctness_of_input(item_,1,limit[6] + 1);
        a = E_P.All_s[item_ - 1];
        inventory.push_back(Factory_Complex(a));
        iter = items_map.find(inventory[inventory.size() - 1]->get_name());
        if(iter != items_map.end()){
          items_map.at(inventory[inventory.size() - 1]->get_name())->set_count(inventory[inventory.size() - 1]->get_count());
          inventory.pop_back();
        }
        else{
          items_map.insert(std::pair(a,inventory[inventory.size() - 1]));
        }
        printf("Do you want to add something?(Y)/(N)\n");
        cin >> a;
        if(a[0] == 'N'){
          some_more = false;
        }
      }
      return 0;
    }
  }

  void Level_Up() {
    Existing_Types E;
    if(experience > E.experience_per_level[level]){
      level++;
      proficiency = ProficiencySetter();
      health = maxhealth;
      Ability_improve();
      ConcreteAbilityModifier();
      maxhealth = Health_Level_Up(health_dice, ConModifier, maxhealth);
      Level_Up();
    }
    printf("%s %d \n", "Your level:", level);
    printf("%s %d \n", "Your max health:", maxhealth);
    printf("%s %d \n", "Your health:", health);
  }

  void SetClass() {
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
    class_type_ = Correctness_of_input(class_type_,1,11);
    classType.set(class_type_ -1,s_b);
    health_dice = classType.get(20);
    proficiency = ProficiencySetter();
    //21-38 => s[0] - s[17]
    for(int i = 21; i < 38;i++){
      if(classType.get(i) == 1 && !s_b[i-21]){
        *s[i-21] += proficiency;
        *s_b[i-21] = true;
      }
    }
  }

  void SetSkill(int *c[]) {
    for (int j = 0; j < 18; j++) {
      if (j == 0 || j == 2 || j == 5 || j == 8 || j == 10 ||
          j == 14) { *c[j] += IntModifier; }//acrobatics,arcana,history,investigation,nature,religion
      else if (j == 1 || j == 6 || j == 9 || j == 11 ||
          j == 17) { *c[j] += WisModifier; }//animalHandling,.s[6],medicine,perception,survival
      else if (j == 3) { *c[j] += StrModifier; }//athletics
      else if (j == 4 || j == 7 || j == 12 ||
          j == 13) { *c[j] += ChaModifier; }//deception,intimidation,performance,persuasion
      else if (j == 15 || j == 16) { *c[j] += DexModifier; }//sleightOfHand,stealth
    }
  }

  int GetSkill(int a) {
    a = Correctness_of_input(a,0,17);
    return *s[a];
  }

  void Starting_Health(){
    if(maxhealth == 0){
      maxhealth = health_dice + ConModifier;
    }
    else{
      printf("Health Increase: Error\n");
    }
  }

  void Starting_Wealth(){

  }
};




