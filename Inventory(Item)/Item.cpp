
#include "Item.h"

Item::Item() : name(" ") { // : name(name) first initialise with reference
  equiped = false;
  count = 0;
  num_equiped = 0;
  stackable = false;
  cost = 0;
  weight = 0;
  what_class_is_it = "Item";
}
Item::~Item() = default;

std::string Item::get_name() {
  return name;
};
int Item::show() { return count; };
void Item::set_count(int a) { count += a; };
int Item::get(int a) {//armor class
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  /*else if(a == 3){ return num_of_dices; }
  else if(a == 4){ return damage_dice; }
  else if(a == 5){ return type_of_elemental_damage;}

  else if(a == 6){ return num_of_dices; }
  else if(a == 7){ return damage_dice; }
  else if(a == 8){ return type_of_elemental_damage;}
  else if(a == 9){ return aiming_range; }
  else if(a == 10){ return max_range;}

  else if(a == 11){ return type_of_armor; }
  else if(a == 12){ return armor_class; }
  else if (a == 13){ return strength_needed;}
  else if (a == 14) { return stealth_disadvantage ? -1 : 1; }

  else if(a == 15){ return is_obstacle ? 1 : -1; }

  else if(a == 16){ return ammo_damage; }
  else if(a == 17){ return element; }

  else if(a == 18){ return healing_dice; }
  else if(a == 19){ return num_of_healing_dices; }
  else if (a == 20){ return passive_healing;}
  else if(a == 21){ return arcane_focus ? 1 : -1; }
  else if(a == 22){ return druidic_focus ? 1 : -1; }
  else if(a == 23){ return holy_symbol ? 1 : -1; }*/
  return -1;
}
void Item::equip(int a) {
  if(abs(a) > count){
    if(a > 0) a = count;
    else a = (-1)*count;
  }
  num_equiped += a;
  equiped = (num_equiped == count);
}
bool Item::is_equiped() { return equiped; }
std::string Item::What_class() {
  return what_class_is_it;
}

Weapon::Weapon() = default;
Weapon::Weapon(std::string &name_) {
  set(name_, 1);
}
Weapon::Weapon(std::string &name_, int count_) {
  num_of_dices = 0;
  damage_dice = 0;
  type_of_elemental_damage = 0;
  set(name_, count_);
}
/*Weapon::Weapon(std::string &name_, int count_, int num_of_dices_, int damage_dice_, int type_of_elemental_damage_) {
  set(name_, count_, num_of_dices_, damage_dice_, type_of_elemental_damage_);
}*/
Weapon::~Weapon() = default;
void Weapon::set(std::string &name_, int count_) {
  //std::cout << "Control reach Item:Weapon:set 0\n";
  Existing_Items E_I;
  equiped = false;
  for (int i = 0; i < kWeapon_NUM; i++) {
    if (E_I.Weapon_s[i] == name_) {
      cost = E_I.Weapon_i[i][0];
      num_of_dices = E_I.Weapon_i[i][1];
      damage_dice = E_I.Weapon_i[i][2];
      weight = E_I.Weapon_i[i][3];
      type_of_elemental_damage = E_I.Weapon_i[i][4];
      stackable = false;
      break;
    }
  }
  //std::cout << "Control reach Item:Weapon:set 1\n";
  //
  name = name_;
  count = count_;
  what_class_is_it = "Weapon";
}
int Weapon::show() {
  Existing_Items E_I;
  std::cout << name << std::endl;
  std::cout << "Damage " << num_of_dices << "d" << damage_dice <<
            " element: " << E_I.elements[type_of_elemental_damage] << std::endl;
  return damage_dice;
}
int Weapon::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  else if (a == 3) { return num_of_dices; }
  else if (a == 4) { return damage_dice; }
  else if (a == 5) { return type_of_elemental_damage; }
  else if (a == 6) { return num_equiped; }
  return -1;
}

Ranged_Weapon::Ranged_Weapon() = default;
Ranged_Weapon::Ranged_Weapon(std::string &name_) {
  set(name_, 1);
}
Ranged_Weapon::Ranged_Weapon(std::string &name_, int count_) {
  num_of_dices = 0;
  damage_dice = 0;
  type_of_elemental_damage = 0;
  aiming_range = 0;
  max_range = 0;
  set(name_, count_);
}
/*Ranged_Weapon::Ranged_Weapon(std::string &name_,
                             int count_,
                             int num_of_dices_,
                             int damage_dice_,
                             int type_of_elemental_damage_,
                             int aiming_range_,
                             int max_range_) {
  set(name_, count_, num_of_dices_, damage_dice_, type_of_elemental_damage_, aiming_range_, max_range_);
}*/
Ranged_Weapon::~Ranged_Weapon() = default;
void Ranged_Weapon::set(std::string &name_, int count_) {
  Existing_Items E_I;
  equiped = false;
  //int count_ = 1, num_of_dices_ = 0, damage_dice_ = 0, type_of_elemental_damage_ = 0;
  //int aiming_range_ = 0, max_range_ = 0;
  for (int i = 0; i < kRanged_Weapon_NUM; i++) {
    if (E_I.Ranged_Weapon_s[i] == name_) {
      cost = E_I.Ranged_Weapon_i[i][0];
      num_of_dices = E_I.Ranged_Weapon_i[i][1];
      damage_dice = E_I.Ranged_Weapon_i[i][2];
      weight = E_I.Ranged_Weapon_i[i][3];
      type_of_elemental_damage = E_I.Ranged_Weapon_i[i][4];
      aiming_range = E_I.Ranged_Weapon_i[i][5];
      max_range = E_I.Ranged_Weapon_i[i][6];
      stackable = false;
      break;
    }
  }
  name = name_;
  count = count_;
  what_class_is_it = "Ranged_Weapon";
}
int Ranged_Weapon::show() {
  Existing_Items E_I;
  std::cout << name << std::endl;
  std::cout << "Damage " << num_of_dices << "d" << damage_dice <<
            " element:" << E_I.elements[type_of_elemental_damage] << std::endl;
  return damage_dice;
}
int Ranged_Weapon::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  else if (a == 3) { return num_of_dices; }
  else if (a == 4) { return damage_dice; }
  else if (a == 5) { return type_of_elemental_damage; }
  else if (a == 6) { return aiming_range; }
  else if (a == 7) { return max_range; }
  else if (a == 8) { return num_equiped; }
  return -1;
}

/*class Food : public Item {
 public:
  Food(std::string &name_, int count_) {
    set(name_, count_);
  }
  ~Food() = default;
  void set(std::string &name_, int count_) {
    name = name_;
    count = count_;
    stackable = true;
  }
  int show() {
    printf("%s", "Usable:");
    std::cout << name << std::endl;
    return count;
  }
};*/


Armor::Armor(std::string &name_) {
  set(name_, 1);
}
Armor::Armor(std::string &name_, int count_) {
  type_of_armor = 0;
  armor_class = 0;
  strength_needed = 0;
  stealth_disadvantage = false;
  set(name_, count_);
}
/*Armor::Armor(std::string &name_,
             int type_,
             int count_,
             int armor_class_,
             int strength_needed_,
             bool stealth_disadvantage_) {
  set(name_, type_, count_, armor_class_, strength_needed_, stealth_disadvantage_);
}*/
Armor::~Armor() = default;
void Armor::set(std::string &name_, int count_) {
  //std::cout << "Control reach Item:Armor:set 0\n";
  Existing_Items E_I;
  equiped = false;
  for (int i = 0; i < kArmor_NUM; i++) {
    if (E_I.Armor_s[i] == name_) {
      //std::cout << "Control reach Item:Armor:set 1\n";
      cost = E_I.Armor_i[i][0];
      type_of_armor = E_I.Armor_i[i][1];
      armor_class = E_I.Armor_i[i][2];
      strength_needed = E_I.Armor_i[i][3];
      stealth_disadvantage = E_I.Armor_b[i];
      weight = E_I.Armor_i[i][4];
      stackable = false;
      break;
    }
  }
  //std::cout << "AC = " << armor_class << std::endl;
  //std::cout << "Control reach Item:Armor:set 2\n";
  name = name_;
  count = count_;
  what_class_is_it = "Armor";
}
int Armor::show() {
  std::cout << name << std::endl;
  printf("%s %d %s %d \n", "Armor Class:", armor_class, "stealth disadvantage:", stealth_disadvantage);
  return armor_class;
}
int Armor::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  else if (a == 3) { return type_of_armor; }
  else if (a == 4) { return armor_class; }
  else if (a == 5) { return strength_needed; }
  else if (a == 6) { return stealth_disadvantage ? -1 : 1; }
  return -1;
}

Usables::Usables() {
  stackable = false;
  is_obstacle = false;
};
Usables::Usables(std::string &name_, int count_) {
  stackable = false;
  is_obstacle = false;
  set(name_, count_);
}
Usables::Usables(std::string &name_) {
  stackable = false;
  is_obstacle = false;
  set(name_, 1);
}
Usables::~Usables() = default;
void Usables::set(std::string &name_, int count_) {
  Existing_Items E_I;
  equiped = false;
  for (int i = 0; i < kUsable_NUM; i++) {
    if (E_I.Usable_s[i] == name_) {
      name = name_;
      cost = E_I.Usable_i[i][0];
      weight = E_I.Usable_i[i][1];
      if (E_I.Usable_i[i][2] != 0) is_obstacle = true;
      break;
    }
  }
  count = count_;
  stackable = false;
  what_class_is_it = "Usables";
}
int Usables::show() {
  printf("%s", "Usable: ");
  std::cout << name << std::endl;
  return count;
}
int Usables::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  else if (a == 3) { return is_obstacle ? 1 : -1; }
  else if (a == 4) { return num_equiped; }
  return -1;
}

Ammo::Ammo() {
  ammo_damage = 0;
  element = 0;
}
Ammo::Ammo(std::string &name_, int count_) {
  ammo_damage = 0;
  element = 0;
  set(name_, count_);
}
Ammo::Ammo(std::string &name_) {
  set(name_, 1);
}
/*Ammo::Ammo(std::string &name_, int count_, int ammo_damage_, int element_) {
  set(name_, count_, ammo_damage_, element_);
}*/
void Ammo::set(std::string &name_, int count_) {
  Existing_Items E_I;
  equiped = false;
  for (int j = 0; j < kAmmo_NUM; j++) {
    if (E_I.Ammo_s[j] == name_) {
      name = name_;
      cost = E_I.Ammo_i[j][0];
      weight = E_I.Ammo_i[j][1];
      ammo_damage = E_I.Ammo_i[j][2];
      element = E_I.Ammo_i[j][3];
      break;
    }
  }
  name = name_;
  count = count_;
  stackable = true;
  what_class_is_it = "Ammo";
}
int Ammo::show() {
  printf("%s", "Usable:");
  std::cout << name << std::endl;
  return count;
}
int Ammo::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  else if (a == 3) { return ammo_damage; }
  else if (a == 4) { return element; }
  else if (a == 5) { return num_equiped; }
  return -1;
}

Magic_Items::Magic_Items() = default;
Magic_Items::Magic_Items(std::string &name_) {
  set(name_, 1);
}
Magic_Items::Magic_Items(std::string &name_, int count_) {
  healing_dice = 0;
  num_of_healing_dices = 0;
  passive_healing = 0;
  arcane_focus = false;
  druidic_focus = false;
  holy_symbol = false;
  set(name_, count_);
}
Magic_Items::~Magic_Items() = default;
void Magic_Items::set(std::string &name_, int count_) {
  Existing_Items E_I;
  equiped = false;
  for (int i = 0; i < kMagic_Items_NUM; i++) {
    if (E_I.Magic_Items_s[i] == name_) {
      name = name_;
      passive_healing = E_I.Magic_Items_i[i][0];
      if (passive_healing == 2) {
        healing_dice = 4;
        num_of_healing_dices = 2;
      }
      if (E_I.Magic_Items_b[i][0]) arcane_focus = true;
      if (E_I.Magic_Items_b[i][1]) druidic_focus = true;
      if (E_I.Magic_Items_b[i][2]) holy_symbol = true;
      break;
    }
  }
  count = count_;
  stackable = false;
  what_class_is_it = "Magic_Items";
}
int Magic_Items::show() {
  printf("%s", "Usable:");
  std::cout << name << std::endl;
  return count;
}
int Magic_Items::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  else if (a == 3) { return healing_dice; }
  else if (a == 4) { return num_of_healing_dices; }
  else if (a == 5) { return passive_healing; }
  else if (a == 6) { return arcane_focus ? 1 : -1; }
  else if (a == 7) { return druidic_focus ? 1 : -1; }
  else if (a == 8) { return holy_symbol ? 1 : -1; }
  else if (a == 9) { return num_equiped; }
  return -1;
}


