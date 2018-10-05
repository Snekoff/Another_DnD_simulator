

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
  deathsaves_f = 0;
  passive_perception = 0;
  proficiency = 0;
  advantage = false;
  disadvantage = false;
  perception_advantage = false;
  perception_disadvantage = false;
  skills.resize(kSkills_Num);
  skills_b.resize(kSkills_Num);
  for (int i = 0; i < kMoney_types; i++) {
    money[i] = 0;
  }
  Equipped.resize(kEquip_places);
  state = 0;
  exhaustion = 0;
  for(int i = 0; i < kCoordinates_NUM;i++){
    Coordinates[i] = 0;
  }
}

Character::Character(Random_Generator_ *Rand_gen, int storyline_, int exp, int levl, int Stre, int Dext,
                     int Cons, int Inte, int Wisd, int Charisma, int sex_, int rand_seed_change) {
  //cout << "Control reach 1\n";
  exp = Less_than_zero(exp);
  Stre = Less_than_zero(Stre);
  Dext = Less_than_zero(Dext);
  Cons = Less_than_zero(Cons);
  Inte = Less_than_zero(Inte);
  Wisd = Less_than_zero(Wisd);
  Charisma = Less_than_zero(Charisma);
  party = -1;
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
  int t1 = Ability_Random_Sets(Rand_gen, rand_seed_change);
  //cout << "Control reach 2\n";
  armor_class = 0;
  deathsaves_s = 0;
  deathsaves_f = 0;
  passive_perception = 0;
  proficiency = 0;
  advantage = false;
  disadvantage = false;
  perception_advantage = false;
  perception_disadvantage = false;
  //cout << "Control reach 3\n";
  ConcreteAbilityModifier();
  skills.resize(kSkills_Num);
  skills_b.resize(kSkills_Num);
  for (int i = 0; i < kMoney_types; i++) {
    money[i] = 0;
  }
  /*money[0] copper
  money[1]
  money[2]
  money[3] Pt
  money[kMoney_types - 1]  sum in copper
   */
  Equipped.resize(kEquip_places);
  //cout << "Control reach 4\n";
  SetSkill();
  //cout << "Control reach 5\n";
  proficiency = ProficiencySetter();
  //cout << "Control reach 6\n";
  PassivePerceptionSetter();
  //cout << "Control reach 7\n";
  Race_Choosal();
  //cout << "Control reach 8\n";
  StorySetsSkills();
  //cout << "Control reach 9\n";
  SetClass(Rand_gen);
  //cout << "Control reach 10\n";
  Starting_Health();
  //cout << "Control reach 11 armor class = " << armor_class << endl;
  if (classType.get(0) == 0) armor_class = kBarbarian_Unarmored_Defence + DexModifier + ConModifier;
  level = 1;
  //cout << "Control reach 12\n" << armor_class;
  cout << experience << " " << level << endl;
  t1 = Level_Up(Rand_gen);
  //cout << "Control reach 13\n";
  Skill_Proficiencies();
  Add_To_Inventory();
  //cout << "Control reach 14\n";
  state = 0;
  exhaustion = 0;
  Equiping_Item();
  for(int i = 0; i < kCoordinates_NUM;i++){
    Coordinates[i] = 0;
  }
}

Character::~Character() {
  delete race_of_character;
  //race_of_character = nullptr;
  skills.clear();
  skills_b.clear();
  inventory.clear();
  items_map.clear();
};

void Character::Maximum_Parameter_Value() {
  if (Str > kAbility_Maximum_Score) Str = kAbility_Maximum_Score;
  if (Dex > kAbility_Maximum_Score) Dex = kAbility_Maximum_Score;
  if (Con > kAbility_Maximum_Score) Con = kAbility_Maximum_Score;
  if (Int > kAbility_Maximum_Score) Int = kAbility_Maximum_Score;
  if (Wis > kAbility_Maximum_Score) Wis = kAbility_Maximum_Score;
  if (Cha > kAbility_Maximum_Score) Cha = kAbility_Maximum_Score;
}

void Character::Set_Party(int party_) {
  party = party_;
}

int Character::Ability_Random_Sets(Random_Generator_ *Rand_gen, int rand_seed_change) {
  if (Str == 0 && Dex == 0 && Con == 0 && Int == 0 && Wis == 0 && Cha == 0) {
    for (int i = 0; i < rand_seed_change; i++) {
      int g = Rand_gen->Rand(10, 16);
    }// to randomize starting numbers
    int Sets[kAbilities_Num * 2] = {0};
    for (int k = 0; k < kAbilities_Num * 2; k++) {
      if (k == 0) cout << "Set 1:\n";
      if (k == 6) cout << "\nSet 2:\n";
      Sets[k] = Rand_gen->Rand(kAbility_Minimum_Score, kAbility_Starting_Maximum);
      //dist(mt);
      cout << " " << Sets[k] << " ";
    }
    cout << "which one do you prefer most?";
    cout << "*Or type 3 to re-roll\n";
    int first_or_second_set = -1;
    int ability_[kAbilities_Num];
    bool checked[kAbilities_Num] = {false};
    first_or_second_set = IsNumber<int>(first_or_second_set, 1, 3);
    if (first_or_second_set == 3) return Ability_Random_Sets(Rand_gen, 0);
    cout << "type six numbers what represents to what ability  you apply each value "
            "1.Str, 2.Dex, 3.Con, 4.Int, 5.Wis, 6.Cha\n";
    for (int i = 0; i < kAbilities_Num; i++) {
      ability_[i] = IsNumber<int>(ability_[i], 1, kAbilities_Num);
      if (!checked[ability_[i] - 1]) checked[ability_[i] - 1] = true;
      else {
        while (checked[ability_[i]]) {
          cout << "You have already used this number ";
          cout << ability_[i] << endl;
          ability_[i] = IsNumber<int>(ability_[i], 1, kAbilities_Num);
        }
      }
      if (i == 0) { Str = Sets[(int) (pow(kAbilities_Num, first_or_second_set - 1)) - 1 + i]; }
      else if (i == 1) { Dex = Sets[(int) (pow(kAbilities_Num, first_or_second_set - 1)) - 1 + i]; }
      else if (i == 2) { Con = Sets[(int) (pow(kAbilities_Num, first_or_second_set - 1)) - 1 + i]; }
      else if (i == 3) { Int = Sets[(int) (pow(kAbilities_Num, first_or_second_set - 1)) - 1 + i]; }
      else if (i == 4) { Wis = Sets[(int) (pow(kAbilities_Num, first_or_second_set - 1)) - 1 + i]; }
      else if (i == 5) { Cha = Sets[(int) (pow(kAbilities_Num, first_or_second_set - 1)) - 1 + i]; }
    }
    //cout <<"Control reach end of Ability random sets\n";
    return 0;
  }
  delete Rand_gen;
  return -2;
}

int Character::Less_than_zero(int a) {
  return a < 0 ? 0 : a;
}

int Character::AbilityModifier(int ability_) {
  return (ability_ - 10) / 2;
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

void Character::PassivePerceptionSetter() {
  int WisModifier_ = WisModifier;
  if (perception_advantage) WisModifier_ += 5;
  if (perception_disadvantage) WisModifier_ -= 5;
  passive_perception = 10 + WisModifier_;
}

void Character::Skill_Proficiencies() {
  for (int i = 0; i < kAbilities_Num; i++) {
    if (skills_b[i]) skills[i] += proficiency;
  }
}

void Character::StorySetsSkills() {
  Existing_Types E;
  storyline = E.stories[storyline_i];
  //string b = storyline;
  Add_Money(2, 15);
  if (storyline_i == 0) {
    skills_b[6] = true;
    skills_b[14] = true;
  } else if (storyline_i == 1) {
    skills_b[4] = true;
    skills_b[15] = true;
  } else if (storyline_i == 2) {
    skills_b[4] = true;
    skills_b[16] = true;
  } else if (storyline_i == 3) {
    skills_b[0] = true;
    skills_b[12] = true;
  } else if (storyline_i == 4) {
    skills_b[1] = true;
    skills_b[17] = true;
  } else if (storyline_i == 5) {
    skills_b[6] = true;
    skills_b[13] = true;
  } else if (storyline_i == 6) {
    skills_b[9] = true;
    skills_b[14] = true;
  } else if (storyline_i == 7) {
    skills_b[5] = true;
    skills_b[13] = true;
  } else if (storyline_i == 8) {
    skills_b[3] = true;
    skills_b[17] = true;
  } else if (storyline_i == 9) {
    skills_b[2] = true;
    skills_b[5] = true;
  } else if (storyline_i == 10) {
    skills_b[3] = true;
    skills_b[11] = true;
  } else if (storyline_i == 11) {
    skills_b[3] = true;
    skills_b[7] = true;
  } else if (storyline_i == 12) {
    skills_b[15] = true;
    skills_b[16] = true;
  }
} // to be reconsidered and expanded Tool proficiencies and standart equip

int Character::Check_Ability_Reach_Maximum(int ability) {
  int a[kAbilities_Num] = {Str, Dex, Con, Int, Wis, Cha};
  while (a[ability - 1] == kAbility_Maximum_Score) {
    cout << "That ability is at maximum, choose another one\n";
    ability = IsNumber<int>(ability, 1, kAbilities_Num);
  }
  return ability;
}

void Character::Ability_improve() {
  if (level == 4 || level == 8 || level == 12 || level == 16 || level == 19) {
    cout << "You reached " << level <<
         " level, that means that you have to choose whether improve one ability +2(type 1) "
         "or two abilities +1(type 2).\n ~In future here might also be feats\n";
    cout << "Str(" << Str << "), Dex(" << Dex << "), Con("
    << Con << "), Int(" << Int << "), Wis(" << Wis << "), Cha(" << Cha << ")\n";
    int one_or_two_abilities = -1;
    one_or_two_abilities = IsNumber<int>(one_or_two_abilities, 1, 2);
    if (one_or_two_abilities == 1) {
      cout << "What ability do you want to improve +2 ? 1.Str(" << Str << "), 2.Dex(" << Dex << "), 3.Con("
           << Con << "), 4.Int(" << Int << "), 5.Wis(" << Wis << "), 6.Cha(" << Cha << ")" << endl;
      one_or_two_abilities = IsNumber<int>(one_or_two_abilities, 1, 6);
      one_or_two_abilities = Check_Ability_Reach_Maximum(one_or_two_abilities);
      Set(one_or_two_abilities + 2, 2);
    } else {
      cout << "What abilities do you want to improve +1 ?  1.Str(" << Str << "), 2.Dex(" << Dex << "), 3.Con("
           << Con << "), 4.Int(" << Int << "), 5.Wis(" << Wis << "), 6.Cha(" << Cha << ") *Type 2 spaced numbers"
                                                                                       "**Maximum value is "
           << kAbility_Maximum_Score << endl;
      int one_or_two_abilities1 = 0;
      one_or_two_abilities = IsNumber<int>(one_or_two_abilities, 1, 6);
      one_or_two_abilities = Check_Ability_Reach_Maximum(one_or_two_abilities);
      one_or_two_abilities1 = IsNumber<int>(one_or_two_abilities1, 1, 6);
      one_or_two_abilities1 = Check_Ability_Reach_Maximum(one_or_two_abilities1);
      Set(one_or_two_abilities + 2, 1);
      Set(one_or_two_abilities1 + 2, 1);
    }
  }
}

void Character::Race_Choosal() {
  cout << "It is time to choose your race. What it will be?\n";
  Race_Factory Race_Factory_;
  cout << "1. Dragonborn (10 subraces)\n"
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
          "Type number, and proceed\n";
  int race = 9;
  //int a = 0, b = 0, c = 0;
  race = IsNumber<int>(race, 1, kRace_Num);
  int subrace = 0;
  if (race == 1) {
    cout << "Choose your subrace. What it will be?\n";
    cout << "1. Black (Acid) 30ft. line\n"
            "2. Blue (Lightning) 30ft. line\n"
            "3. Brass (Fire) 30ft. line\n"
            "4. Bronze (Lightning) 30ft. line\n"
            "5. Copper (Acid) 30ft. line\n"
            "6. Gold (Fire) 15ft. cone\n"
            "7. Green (Poison) 15ft. cone\n"
            "8. Red (Fire) 15ft. cone\n"
            "9. Silver (Cold) 15ft. cone\n"
            "10. White (Cold) 15ft. cone\n"
            "Type number, and proceed\n";
    subrace = IsNumber<int>(subrace, 1, 10);
    //cout << "Control reach Race_Choosal 1\n";
  } else if (race == 2) {
    cout << "Choose your subrace. What it will be?\n";
    cout << "1. Duergar\n"
            "2. Hill\n"
            "3. Mountain\n"
            "Type number, and proceed\n";
    subrace = IsNumber<int>(subrace, 1, 3);
    //cout << "Control reach Race_Choosal 2\n";
  } else if (race == 3) {
    cout << "Choose your subrace. What it will be?\n";
    cout << "1. Drow \n"
            "2. Eladrin \n"
            "3. High\n"
            "4. Sea\n"
            "5. Shadar-kai\n"
            "6. Wood\n"
            "Type number, and proceed\n";
    subrace = IsNumber<int>(subrace, 1, 6);
  } else if (race == 4) {
    cout << "Choose your subrace. What it will be?\n";
    cout << "1. Deep/Svirfneblin\n"
            "2. Forest\n"
            "3. Rock\n"
            "Type number, and proceed\n";
    subrace = IsNumber<int>(subrace, 1, 3);
  } else if (race == 5) {
    cout << "Goblin \n";
  } else if (race == 6) {
    cout << "Choose your subrace. What it will be?\n";
    cout << "1. Common\n"
            "2. Aquatic Elf Descent\n"
            "3. Drow Descent\n"
            "4. Moon Elf or Sun Elf Descent\n"
            "5. Wood Elf Descent\n"
            "Type number, and proceed\n";
    subrace = IsNumber<int>(subrace, 1, 5);
  } else if (race == 7) {
    cout << "Choose your subrace. What it will be?\n";
    cout << "1. Half-Orc\n"
            "2. Orc\n"
            "Type number, and proceed\n";
    subrace = IsNumber<int>(subrace, 1, 2);
  } else if (race == 8) {
    cout << "Choose your subrace. What it will be?\n";
    cout << "1. Ghostwise\n"
            "2. Lightfoot\n"
            "3. Stout\n"
            "Type number, and proceed\n";
    subrace = IsNumber<int>(subrace, 1, 3);
  } else if (race == 9) {
    cout << "Choose your subrace. What it will be?\n";
    cout << "1. Common\n"
            "2. Variant\n"
            "Type number, and proceed\n";
    subrace = IsNumber<int>(subrace, 1, 2);
  } else if (race == 10) {
    cout << "Lizardfolk \n";
  } else if (race == 11) {
    cout << "Choose your subrace. What it will be?\n";
    cout << "1. Common\n"
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
            "Type number, and proceed\n";
    subrace = IsNumber<int>(subrace, 1, 11);
  }
  race_of_character = Race_Factory_.Create(race - 1, subrace - 1);
  Race_Get_Abilities();
  ConcreteAbilityModifier();
}

void Character::Race_Get_Abilities() {
  /*
 cout << " subtype = " << race_of_character->get(14) <<"\n";*/
  Str += race_of_character->get(4);
  Dex += race_of_character->get(5);
  Con += race_of_character->get(6);
  Int += race_of_character->get(7);
  Wis += race_of_character->get(8);
  Cha += race_of_character->get(9);
  Maximum_Parameter_Value();
}

void Character::Set(int what, int value) {// what - what parameter will be changed, value - modifier(can be negative)
  what = Correctness_of_input<int>(what, 0, 14);
  if (what == 1) { experience += value; }
  else if (what == 2) { health += value; }
  else if (what == 3) { Str += value; }
  else if (what == 4) { Dex += value; }
  else if (what == 5) { Con += value; }
  else if (what == 6) { Int += value; }
  else if (what == 7) { Wis += value; }
  else if (what == 8) { Cha += value; }
  else if (what == 9) { armor_class += value; }
  else if (what == 10) { if (value < 0)deathsaves_f++; else deathsaves_s++; }
  else if (what == 11) { cout << "reserved for Skills"; }
  else if (what == 12) { cout << "reserved for weapon"; }
  else if (what == 13) { cout << "reserved for inventory"; }
  else if (what == 14) { cout << "reserved for story/background"; }
  Maximum_Parameter_Value();
}

int Character::Get(int what) {
  if (what == 0) { return party; }
  else if (what == 1) { return storyline_i; }
  else if (what == 2) { return sex; }
  else if (what == 3) { return experience; }
  else if (what == 4) { return level; }
  else if (what == 5) { return health; }
  else if (what == 6) { return maxhealth; }
  else if (what == 7) { return health_dice; }
  else if (what == 8) { return Str; }
  else if (what == 9) { return Dex; }
  else if (what == 10) { return Con; }
  else if (what == 11) { return Int; }
  else if (what == 12) { return Wis; }
  else if (what == 13) { return Cha; }
  else if (what == 14) { return armor_class; }
  else if (what == 15) { return deathsaves_s; }
  else if (what == 16) { return deathsaves_f; }
  else if (what == 17) { return money[0]; }
  else if (what == 18) { return money[1]; }
  else if (what == 19) { return money[2]; }
  else if (what == 20) { return money[3]; }
  else if (what == 21) { return money[4]; }
  else if (what == 22) { return state; }
  else if (what == 23) { return classType.get(0); }
  else if (what == 24) { return 0; }
  else if (what == 25) { return classType.get(39); }//architype
  else if (what == 26) { return race_of_character->get(0); }//type
  else if (what == 27) { return race_of_character->get(1); }
  else if (what == 28) { return race_of_character->get(2); }
  else if (what == 29) { return race_of_character->get(3); }
  else if (what == 30) { return race_of_character->get(10); }//
  else if (what == 31) { return race_of_character->get(11); }//
  else if (what == 32) { return race_of_character->get(12); }//Darkvision
  else if (what == 33) { return race_of_character->get(13); }//
  else if (what == 34) { return race_of_character->get(14); }
  else if (what == 35) { return (int) 'R'; }
  else if (what == 71) { return exhaustion; }
  else if (what == 99) { return inventory.size() * 2; }
  else if (what == 100) { return passive_perception; }
  else if (what == 101) { return proficiency; }
  else if (what == 102) { return StrModifier; }
  else if (what == 103) { return DexModifier; }
  else if (what == 104) { return ConModifier; }
  else if (what == 105) { return IntModifier; }
  else if (what == 106) { return WisModifier; }
  else if (what == 107) { return ChaModifier; }
  return -1;
}

bool Character::Get_bool(int what) {
  if (what == 36) { return advantage; }
  else if (what == 37) { return disadvantage; }
  else if (what == 38) { return perception_advantage; }
  else if (what == 39) { return perception_disadvantage; }
  else if (what > 39 && what < 58) { return skills_b[what - kSkills_b_shift]; }
  else if (what > 57 && what < 71) { return classType.get_bool(what - kClassType_get_bool_shift); }//
  return false;
}

vector<int> Character::Get_inventory() {
  vector<int> inventory_;
  Existing_Items E_I;
  for (int k = 0; k < inventory.size(); k++) {
    for (int i = 0; i < kAll_Num; i++) {
      if (inventory[k]->get_name() == E_I.All_s[i]) {
        inventory_.push_back(i);
        inventory_.push_back(inventory[k]->get(2));
        break;
      }
    }
  }
  return inventory_;
} // { {(int)name_of_Item1, amount1} , {(int)name_of_Item2, amount2} ... }

Item *Character::Factory_Complex(string &name_, int quantity) {
  //cout << "Control reached Factory_complex 0\n";
  Items_Factory<Weapon> Weapon_Factory;
  Items_Factory<Ranged_Weapon> Ranged_Weapon_Factory;
  Items_Factory<Armor> Armor_Factory;
  Items_Factory<Usables> Usables_Factory;
  Items_Factory<Ammo> Ammo_Factory;
  Items_Factory<Magic_Items> Magic_Items_Factory;
  Existing_Items E_I;
  //cout << "Control reached Factory_complex 1\n";
  for (int i = 0; i < kWeapon_NUM; i++) {
    if (name_ == E_I.Weapon_s[i]) {
      //cout << "Control reached Factory_complex 1_1\n";
      return Weapon_Factory.create(name_, quantity);
    }
  }
  for (int i = 0; i < kRanged_Weapon_NUM; i++) {
    if (i < kRanged_Weapon_NUM && name_ == E_I.Ranged_Weapon_s[i]) {
      //cout << "Control reached Factory_complex 1_2\n";
      return Ranged_Weapon_Factory.create(name_, quantity);
    }
  }
  for (int i = 0; i < kAmmo_NUM; i++) {
    if (i < kAmmo_NUM && name_ == E_I.Ammo_s[i]) {
      //cout << "Control reached Factory_complex 1_5\n";
      return Ammo_Factory.create(name_, quantity);
    }
  }
  for (int i = 0; i < kArmor_NUM; i++) {
    if (i < kArmor_NUM && name_ == E_I.Armor_s[i]) {
      //cout << "Control reached Factory_complex 1_3\n";
      return Armor_Factory.create(name_, quantity);
    }
  }
  for (int i = 0; i < kUsable_NUM; i++) {
    if (i < kUsable_NUM && name_ == E_I.Usable_s[i]) {
      //cout << "Control reached Factory_complex 1_4\n";
      return Usables_Factory.create(name_, quantity);
    }
  }
  for (int i = 0; i < kMagic_Items_NUM; i++) {
    if (i < kMagic_Items_NUM && name_ == E_I.Magic_Items_s[i]) {
      //cout << "Control reached Factory_complex 1_6\n";
      return Magic_Items_Factory.create(name_, quantity);
    }
  }

  /*for (int i = 0; i < kAll_Num; i++) {
    if (i < kWeapon_NUM && a == E_I.Weapon_s[i]) {cout <<"Control reached Factory_complex 1_1\n"; return Weapon_Factory.create(a); }
    else if (i < kRanged_Weapon_NUM &&a == E_I.Ranged_Weapon_s[i]) {cout <<"Control reached Factory_complex 1_2\n"; return Ranged_Weapon_Factory.create(a); }
    else if (i < kAmmo_NUM &&a == E_I.Ammo_s[i]) {cout <<"Control reached Factory_complex 1_5\n"; return Ammo_Factory.create(a); }
    else if (i < kArmor_NUM &&a == E_I.Armor_s[i]) {cout <<"Control reached Factory_complex 1_3\n"; return Armor_Factory.create(a); }
    else if (i < kUsable_NUM &&a == E_I.Usable_s[i]) {cout <<"Control reached Factory_complex 1_4\n"; return Usables_Factory.create(a); }
    else if (i < kMagic_Items_NUM &&a == E_I.Magic_Items_s[i]) {cout <<"Control reached Factory_complex 1_6\n"; return Magic_Items_Factory.create(a); }
    else if (i == kUsable_NUM - 1) {
      cout <<"Error in Factory complex\n";
      return nullptr;
    }
  }*/
  //cout << "Control reached Factory_complex 3\n";
  return nullptr;
}

void Character::Add_Money(int type, int sum) {
  type = Correctness_of_input<int>(type, 0, kMoney_types - 2);
  //cout << "Before operation: money[" << type << "] = " << money[type] << endl;
  money[type] += sum;
  //cout << "After operation: money[" << type << "] = " << money[type] << endl;
  money[kMoney_types - 1] += (int) (sum * pow(10, type));
  //cout << "money[4] = " << money[kMoney_types - 1] << endl;
}

void Character::Add_To_Item_Map(string &name_) {
  auto iter = items_map.find(inventory[inventory.size() - 1]->get_name());
  if (iter != items_map.end()) {
    items_map.at(inventory[inventory.size() - 1]->get_name())
        ->set_count(inventory[inventory.size() - 1]->get(2));
    //cout << "Control reach Add to item map, poped Item:" << inventory[inventory.size() - 1]->get_name() << endl;
    inventory.pop_back();
  } else {
    items_map.insert(std::pair(name_, inventory[inventory.size() - 1]));
  }
}

bool Character::Paying_Money(int how_many_copper) {
  if (money[kMoney_types - 1] < how_many_copper) {
    return false;
  } else {
    money[kMoney_types - 1] -= how_many_copper;
    int dif = 1, i = 0;
    while (dif != 0) {
      if (how_many_copper > 0) {
        dif = (int) (how_many_copper - money[i] * pow(10, i));
        money[i] = 0;
        how_many_copper = dif;
      } else {
        dif = how_many_copper;
        i = 3;
      }
      if (how_many_copper < 0) {
        dif *= (-1);
        for (int j = i; j > -1; j--) {
          int t = (int) (dif / pow(10, j));
          //cout << "t = " << t << endl;
          money[j] += t;
          //cout << "money[j] = " << money[j] << endl;
          dif -= (int) (t * pow(10, j));
          //cout << "dif = " << dif << endl;
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
  string name_ = "Backpack";
  inventory.push_back(Usables_Factory1.create(name_));
  int choose_to_proceed = 0;
  Add_To_Item_Map(name_);
  inventory[inventory.size() - 1]->equip(1);
  cout << "Your Backpack is a black hole without any limits, but you can carry not as much weight,"
          " so choose wisely what to take with you in future journeys\n";
  cout << "Do you want to take anything with you ?  Yes(1)  No(2) *\n";
  choose_to_proceed = IsNumber<int>(choose_to_proceed, 1, 2);
  if (choose_to_proceed == 2) {
    return 0;
  } else {
    bool some_more = true;
    while (some_more) {
      int item_ = 0;
      cout << "You can add this types of items:\n"
              "1. Weapon\n"
              "2. Ranged weapon\n"
              "3. Ammo\n"
              "4. Armor\n"
              "5. Usables\n"
              "6. Magic Items\n"
              "(this list will be extended in future versions)\n";
      item_ = IsNumber<int>(item_, 1, kItem_Types);
      //cout << "Control reach method Add_To_Inventory 0\n";
      cout << "Your funds: " << money[kMoney_types - 1] << endl;
      int limit[kItem_Types + 1] =
          {0, kWeapon_NUM, kRanged_Weapon_NUM + limit[1], kAmmo_NUM + limit[2], kArmor_NUM + limit[3],
           kUsable_NUM + limit[4], kMagic_Items_NUM + limit[5]};
      Existing_Items E_I;
      //cout << "Control reach method Add_To_Inventory 1\n";
      for (int i = limit[item_ - 1]; i < limit[item_]; i++) {
        cout << i + 1 << ". " << E_I.All_s[i] << " price: ";
        if (item_ == 1) { cout << E_I.Weapon_i[i][0]; }
        else if (item_ == 2) { cout << E_I.Ranged_Weapon_i[i - limit[item_ - 1]][0]; }
        else if (item_ == 3) { cout << E_I.Ammo_i[i - limit[item_ - 1]][0]; }
        else if (item_ == 4) { cout << E_I.Armor_i[i - limit[item_ - 1]][0]; }
        else if (item_ == 5) { cout << E_I.Usable_i[i - limit[item_ - 1]][0]; }
        else if (item_ == 6) { cout << E_I.Magic_Items_i[i - limit[item_ - 1]][0]; }
        cout << endl;
      }
      item_ = IsNumber<int>(item_, limit[item_ - 1], limit[item_]);
      //cout << "Control reach method Add_To_Inventory 2\n";
      name_ = E_I.All_s[item_ - 1];
      int quantity = 1;
      cout << "How many " << name_ << "s do you want ?\n";
      quantity = IsNumber<int>(quantity, 1, 0);
      //cout << "Control reach method Add_To_Inventory 3\n";
      auto b = Factory_Complex(name_, quantity);
      if (Paying_Money(b->get(0) * quantity)) {
        inventory.push_back(Factory_Complex(name_, quantity));
        //cout << "Control reach method Add_To_Inventory 4\n";
        Add_To_Item_Map(name_);
      } else {
        cout << "You have not enough money for that. Your money(in copper equivalent) are:" <<
             money[kMoney_types - 1] <<
             " and price is " <<
             b->get(0) * quantity
             << endl;
      }
      delete b;
      cout << "Do you want to add something? Yes(1)  No(2)\n";
      item_ = IsNumber<int>(item_, 1, 2);
      if (item_ == 2) {
        some_more = false;
      }
    }
    return 0;
  }
}

void Character::Equip_Item(int where, Item *what) {
  //cout << "Control reached Equip_Item 0 \n";
  where = Correctness_of_input<int>(where, 0, kEquip_places - 1);
  what->equip(1);
  if (Equipped[where] != nullptr) {// ->get(2) != 0
    Equipped[where]->equip(-1);
  } else { cout << "null check fine\n"; }
  Equipped[where] = what;
  if (where < 2) {
    cout << "Equipped " << Equipped[where]->get_name() << endl;
    if (what->get_name() == "Shield") {
      armor_class += 2;
      cout << "armor_class = "<< armor_class << endl;}
  } else if (where == 2) {
    cout << "equip armor, armor class before: " << armor_class << endl;
    armor_class = 0;
    if (Equipped[0] != nullptr ) {
      if(Equipped[0]->What_class() == "Armor") armor_class = Equipped[where]->get(4);
    }
    else if(Equipped[1] != nullptr ){
      if(Equipped[1]->What_class() == "Armor") armor_class = Equipped[where]->get(4);
    }
    int armor_class_bonus[kArmor_types] = {DexModifier, min(DexModifier, 2), 0};
    armor_class += Equipped[where]->get(4) + armor_class_bonus[Equipped[where]->get(3)];
    cout << "armor class after: " << armor_class << endl;
    cout << "Equipped " << Equipped[where]->get_name() << endl;
  } else if (where < 10 && where > 5) {
    cout << "Equipped " << Equipped[where]->get_name() << endl;
  } else {
    cout << "Non-standart body Nothing equipped\n";
    //Equipped[where] = what;
    //cout << "Equipped " << Equipped[where]->get_name() << endl;
  }
}

void Character::Equiping_Item() {
  //cout << "Control reached Equiping_Item 0 \n";
  //Item *what = new Item();
  cout << "You might Equip Something. Choose where and what.\n";
  cout << "Now lets see what you have got in your backpack\n";
  vector<string> names;
  int k = 0;
  for (auto it = items_map.begin(); it != items_map.end(); it++) { //  : items_map
    names.push_back(it->first);
    //cout << " now will be name: " << it->second->get_name() << endl;
    cout << k + 1 << '.' << it->first;
    if (it->second->is_equiped()) cout << " (equipped)";
    cout << endl;
    k++;
  }
  //cout << "Control reached Equiping_Item 1 \n";
  if (k > 1) {
    cout << "You can equip something. Choose what.(type number)\n";
    cout << "//type \"0\" to exit\n";
    int what_ = 0;
    what_ = IsNumber<int>(what_, 0, k + 1);
    if (what_ != 0) {
      //cout << "Control reached Equiping_Item 2 \n";
      what_ = Correctness_of_input<int>(what_, 1, k + 1);
      if (items_map.find(names[what_ - 1])->second->is_equiped()) {
        cout << "it is already equipped!\n";
      } else {
        //cout << "Control reached Equiping_Item 4 \n";
        //what = items_map.find(names[what_ - 1])->second;
        cout << "Possible places to equip are:\n";
        cout << "Hands: Left(1), Right(2), extra*(4-5)\n";
        cout << "Body: upper/upper+lower(3)\n";
        cout << "Fingers: (6-10)\n";
        cout << "*only for abnormal bodies\n";
        int where = 0;
        where = IsNumber<int>(where, 1, kEquip_places);
        while (where == 3) {
          if (items_map.find(names[what_ - 1])->second->What_class() != "Armor"
              || items_map.find(names[what_ - 1])->second->get_name() == "Shield") {
            where = -2;
            cout << "You can't equip that on your body. Please choose where else\n";
            where = IsNumber<int>(where, 1, kEquip_places);
          } else break;
        }
        while (where > 5 && where < 11) {
          if (items_map.find(names[what_ - 1])->second->What_class() != "Ring") {
            where = -2;
            cout << "You can't equip that on your finger, please choose where else\n";
            where = IsNumber<int>(where, 1, kEquip_places);
          } else break;
        }
        //cout << "Control reached Equipping_Item 5 \n";
        Equip_Item(where - 1, items_map.find(names[what_ - 1])->second);
      }
      cout << "Do u want to add something to your equipment? Yes(1), No(2)\n";
      k = IsNumber<int>(k, 1, 2);
      //delete what;
      if (k == 1) { Equiping_Item(); }
    }
  }
  cout << "You Left Equip Menu.\n";
}

void Character::Unequip_Item(int where) {
  where = Correctness_of_input<int>(where, 0, kEquip_places - 1);
  if (Equipped[where] != nullptr) {// need to try it hard
    Equipped[where]->equip(-1);
    Equipped[where] = nullptr;
    if (where == 2) {
      if (classType.get(0) == 0) {
        armor_class = kBarbarian_Unarmored_Defence + DexModifier + ConModifier;
      } else {
        armor_class = 0;
      }
    }
  } else cout << "nullptr check fine\n";
}

int Character::Healing_Injuring(int value) {
  if (value > 0) {
    health += value;
    if (health > maxhealth) health = maxhealth;
  } else {
    if (health <= value && value - health < maxhealth) {
      state = 6; // incapacitated
    } else if (value - health >= maxhealth) {
      state = 14; // instantly dead;
    } else {
      health += value;
    }
  }
  return health;
}

int Character::Level_Up(Random_Generator_ *Rand_gen) {
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
  cout << "Your level:" << level << endl;
  cout << "Your max health:" << maxhealth << endl;
  cout << "Your health:" << health << endl;
  return 0;
}

void Character::Class_Set_Wealth(Random_Generator_ *Rand_gen) {
  int wealth[kClass_Num][kWealth_Set_parameters] =
      {{2, 4, 10}, {5, 4, 10}, {5, 4, 10}, {2, 4, 10}, {5, 4, 10}, {5, 4, 1},
       {5, 4, 10}, {5, 4, 10}, {4, 4, 10}, {3, 4, 10}, {4, 4, 10}, {4, 4, 10}};
  //how_many_times, dice, dice_value_multiplier
  int ctype = classType.get(0);
  int funds = 0;
  for (int i = 0; i < wealth[ctype][0]; i++) {
    funds += Rand_gen->Rand(kDice_Minimum_value, wealth[ctype][1]) * wealth[ctype][2];
  }
  cout << "generated gold coins for your class: " << funds << endl;
  Add_Money(2, funds);
}

void Character::SetClass(Random_Generator_ *Rand_gen) {
  cout << "Choose your class: \n";
  int class_type_ = 0;
  cout << "1. Barbarian\n"
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
          "12. Wizard\n";
  class_type_ = IsNumber<int>(class_type_, 1, kClass_Num);
  classType.set(class_type_ - 1, skills_b);
  health_dice = classType.get(20);
  proficiency = ProficiencySetter();
  //21-38 => skills[0] - skills[17]
  Class_Set_Wealth(Rand_gen);
  for (int i = 0; i < kSkills_Num; i++) {
    if (classType.get(i + kClassType_get_shift) == 1) {
      skills_b[i] = true;
    }
  }
}

void Character::SetSkill() {
  for (int j = 0; j < kAbilities_Num; j++) {
    if (j == 0 || j == 2 || j == 5 || j == 8 || j == 10 ||
        j == 14) { skills[j] += IntModifier; }//acrobatics,arcana,history,investigation,nature,religion
    else if (j == 1 || j == 6 || j == 9 || j == 11 ||
        j == 17) { skills[j] += WisModifier; }//animalHandling,.skills[6],medicine,perception,survival
    else if (j == 3) { skills[j] += StrModifier; }//athletics
    else if (j == 4 || j == 7 || j == 12 ||
        j == 13) { skills[j] += ChaModifier; }//deception,intimidation,performance,persuasion
    else if (j == 15 || j == 16) { skills[j] += DexModifier; }//sleightOfHand,stealth
  }
}

int Character::GetSkill(int what) {
  what = Correctness_of_input<int>(what, 0, kSkills_Num - 1);
  return skills[what];
}

void Character::Inventory_Load(vector<int> item_) {
  Existing_Items E_I;
  for (int i = 0; i < item_.size(); i += 2) {
    inventory.push_back(Factory_Complex(E_I.All_s[item_[i]], item_[i + 1]));
    cout << "Loaded " << inventory[inventory.size() - 1]->get_name() << endl;
    Add_To_Item_Map(E_I.All_s[item_[i]]);
  }
}

void Character::Starting_Health() {
  if (maxhealth == 0) {
    maxhealth = health_dice + ConModifier;
    health = maxhealth;
  } else {
    cout << "Health Increase: Error\n";
  }
}

bool Character::Load(int parameter_i[], bool parameter_b[], vector<int> item_) {
  Existing_Types E;
  party = -1;
  skills.resize(kSkills_Num);
  skills_b.resize(kSkills_Num);
  Equipped.resize(kEquip_places);
  //cout << "Control reach Character method Load 0\n";
  for (int i = 1; i < kData_size; i++) {
    if (i == 1) {
      //cout <<"Control reach Character method Load 1\n";
      storyline_i = parameter_i[i];
      cout << storyline_i << " is story of " << E.stories[storyline_i] << endl;
    } else if (i == 2) { sex = parameter_i[i]; }
    else if (i == 3) {
      //cout <<"Control reach Character method Load 3\n";
      experience = parameter_i[i];
    } else if (i == 4) { level = parameter_i[i]; }
    else if (i == 5) { health = parameter_i[i]; }
    else if (i == 6) { maxhealth = parameter_i[i]; }
    else if (i == 7) { health_dice = parameter_i[i]; }
    else if (i == 8) { Str = parameter_i[i]; }
    else if (i == 9) { Dex = parameter_i[i]; }
    else if (i == 10) {
      //cout <<"Control reach Character method Load 10\n";
      Con = parameter_i[i];
    } else if (i == 11) { Int = parameter_i[i]; }
    else if (i == 12) { Wis = parameter_i[i]; }
    else if (i == 13) { Cha = parameter_i[i]; }
    else if (i == 14) { armor_class = parameter_i[i]; }
    else if (i == 15) { deathsaves_s = parameter_i[i]; }
    else if (i == 16) { deathsaves_f = parameter_i[i]; }
    else if (i == 17) { money[0] = parameter_i[i]; }
    else if (i == 18) { money[1] = parameter_i[i]; }
    else if (i == 19) { money[2] = parameter_i[i]; }
    else if (i == 20) { money[3] = parameter_i[i]; }
    else if (i == 21) { money[4] = parameter_i[i]; }
    else if (i == 22) { state = parameter_i[i]; }
    else if (i == 23) {
      //classType = new Class();
      classType.Load(parameter_i[23], parameter_b, parameter_i[35]);
    } else if (i == 26) {
      //cout << "Control reach Character method Load 26\n";
      Race_Factory Race_Factory_;
      race_of_character = Race_Factory_.Load(parameter_i[i]);
      race_of_character->Load(parameter_i);
    } else if (i == 36) { exhaustion = parameter_i[i]; }
    else if (i == 37) {
      //cout << "Control reach Character method Load (bool)\n";
      advantage = parameter_b[i - kParameter_b_shift];
    } else if (i == 38) { disadvantage = parameter_b[i - kParameter_b_shift]; }
    else if (i == 39) { perception_advantage = parameter_b[i - kParameter_b_shift]; }
    else if (i == 40) { perception_disadvantage = parameter_b[i - kParameter_b_shift]; }
    else if (i > 40 && i < 59) { skills_b[i - kSkills_b_shift - 1] = parameter_b[i - kParameter_b_shift]; }
  }
  proficiency = ProficiencySetter();
  //cout <<"Control reach Character method Load 91\n";
  PassivePerceptionSetter();
  Maximum_Parameter_Value();
  ConcreteAbilityModifier();
  Skill_Proficiencies();
  Inventory_Load(item_);
  Equiping_Item();
  return true;
}

