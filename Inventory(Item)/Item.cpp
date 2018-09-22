
#include "Item.h"

Item::Item() : name("Rope") { // : name(name) first initialise with reference
  equiped = false;
  count = 0;
  num_equiped = 0;
  stackable = false;
  cost = 0;
  weight = 0;
}
Item::~Item() = default;

std::string Item::get_name() {
  return name;
};
int Item::show() { return count; };
int Item::get_count() { return count; };
void Item::set_count(int a) { count += a; };
int Item::get_cost() { return cost; }
int Item::get(int a) {
  if (a == 1) return weight;
  return -1;
}
void Item::equip(int a) {
  num_equiped += a;
  if (num_equiped == count) equiped = true; else equiped = false;
}
bool Item::is_equiped() { return equiped; }

Weapon::Weapon() = default;
Weapon::Weapon(std::string &name_) {
  Existing_Items E;
  equiped = false;
  int count_ = 1, num_of_dices_ = 0, damage_dice_ = 0, type_of_elemental_damage_ = 0;
  for (int i = 0; i < kWeapon_NUM; i++) {
    if (E.Weapon_s[i].compare(name_)) {
      cost = E.Weapon_i[i][0];
      num_of_dices_ = E.Weapon_i[i][1];
      damage_dice_ = E.Weapon_i[i][2];
      weight = E.Weapon_i[i][3];
      type_of_elemental_damage_ = E.Weapon_i[i][4];
      stackable = false;
      break;
    }
  }
  set(name_, count_, num_of_dices_, damage_dice_, type_of_elemental_damage_);
}
Weapon::Weapon(std::string &name_, int count_) {
  name = name_;
  count = count_;
  num_of_dices = 0;
  damage_dice = 0;
  type_of_elemental_damage = 0;
}
Weapon::Weapon(std::string &name_, int count_, int num_of_dices_, int damage_dice_, int type_of_elemental_damage_) {
  set(name_, count_, num_of_dices_, damage_dice_, type_of_elemental_damage_);
}
Weapon::~Weapon() = default;
void Weapon::set(std::string &name_, int count_, int num_of_dices_, int damage_dice_, int type_of_elemental_damage_) {
  name = name_;
  count = count_;
  stackable = false;
  num_of_dices = num_of_dices_;
  damage_dice = damage_dice_;
  type_of_elemental_damage = type_of_elemental_damage_;
}
int Weapon::show() {
  std::cout << name << std::endl;
  std::cout << "Damage " << num_of_dices << "d" << damage_dice <<
            " element: " << elements[type_of_elemental_damage] << std::endl;
  return damage_dice;
}
int Weapon::get(int a) { return weight; }

Ranged_Weapon::Ranged_Weapon() = default;
Ranged_Weapon::Ranged_Weapon(std::string &name_) {
  Existing_Items E;
  equiped = false;
  int count_ = 1, num_of_dices_ = 0, damage_dice_ = 0, type_of_elemental_damage_ = 0;
  int aiming_range_ = 0, max_range_ = 0;
  for (int i = 0; i < kWeapon_NUM; i++) {
    if (E.Ranged_Weapon_s[i].compare(name_) == 0) {
      cost = E.Ranged_Weapon_i[i][0];
      num_of_dices_ = E.Ranged_Weapon_i[i][1];
      damage_dice_ = E.Ranged_Weapon_i[i][2];
      weight = E.Ranged_Weapon_i[i][3];
      type_of_elemental_damage_ = E.Ranged_Weapon_i[i][4];
      aiming_range_ = E.Ranged_Weapon_i[i][5];
      max_range_ = E.Ranged_Weapon_i[i][6];
      stackable = false;
      break;
    }
  }
  set(name_, count_, num_of_dices_, damage_dice_, type_of_elemental_damage_, aiming_range_, max_range_);
}
Ranged_Weapon::Ranged_Weapon(std::string &name_, int count_) {
  name = name_;
  count = count_;
  aiming_range = 0;
  max_range = 0;
}
Ranged_Weapon::Ranged_Weapon(std::string &name_,
                             int count_,
                             int num_of_dices_,
                             int damage_dice_,
                             int type_of_elemental_damage_,
                             int aiming_range_,
                             int max_range_) {
  set(name_, count_, num_of_dices_, damage_dice_, type_of_elemental_damage_, aiming_range_, max_range_);
}
Ranged_Weapon::~Ranged_Weapon() = default;
void Ranged_Weapon::set(std::string &name_,
                        int count_,
                        int num_of_dices_,
                        int damage_dice_,
                        int type_of_elemental_damage_,
                        int aiming_range_,
                        int max_range_) {
  name = name_;
  count = count_;
  stackable = false;
  num_of_dices = num_of_dices_;
  damage_dice = damage_dice_;
  type_of_elemental_damage = type_of_elemental_damage_;
  aiming_range = aiming_range_;
  max_range = max_range_;
}
int Ranged_Weapon::show() {
  std::cout << name << std::endl;
  std::cout << "Damage " << num_of_dices << "d" << damage_dice <<
            " element:" << elements[type_of_elemental_damage] << std::endl;
  return damage_dice;
}
int Ranged_Weapon::get(int a) { return weight; }

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
  Existing_Items E;
  equiped = false;
  int count_ = 1, type_ = 0, armor_class_ = 0, strength_needed_ = 0;
  bool stealth_disadvantage_ = false;
  for (int i = 0; i < kWeapon_NUM; i++) {
    if (E.Armor_s[i].compare(name_)) {
      cost = E.Armor_i[i][0];
      type_ = E.Armor_i[i][1];
      armor_class_ = E.Armor_i[i][2];
      strength_needed_ = E.Armor_i[i][3];
      stealth_disadvantage_ = E.Armor_i[i][4];
      weight = E.Armor_i[i][5];
      stackable = false;
      break;
    }
  }
  set(name_, type_, count_, armor_class_, strength_needed_, stealth_disadvantage_);
}
Armor::Armor(std::string &name_, int count_) {
  name = name_;
  count = count_;
  type = 0;
  armor_class = 0;
  strength_needed = 0;
  stealth_disadvantage = false;
}
Armor::Armor(std::string &name_,
             int type_,
             int count_,
             int armor_class_,
             int strength_needed_,
             bool stealth_disadvantage_) {
  set(name_, type_, count_, armor_class_, strength_needed_, stealth_disadvantage_);
}
Armor::~Armor() = default;
void Armor::set(std::string &name_,
                int type_,
                int count_,
                int armor_class_,
                int strength_needed_,
                bool stealth_disadvantage_) {
  name = name_;
  type = type_;
  count = count_;
  stackable = false;
  armor_class = armor_class_;
  strength_needed = strength_needed_;
  stealth_disadvantage = stealth_disadvantage_;
}
int Armor::show() {
  std::cout << name << std::endl;
  printf("%s %d %s %d \n", "Armor Class:", armor_class, "stealth disadvantage:", stealth_disadvantage);
  return armor_class;
}
int Armor::get(int a) {
  if (a == 0) return type;
  else if (a == 1) { return weight; }
  else if (a == 2) { return armor_class; }
  else if (a == 3) { return strength_needed; }
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
  Existing_Items E;
  equiped = false;
  for (int i = 0; i < kMagic_Items_NUM; i++) {
    if (E.Usable_s[i].compare(name_)) {
      name = name_;
      cost = E.Usable_i[i][0];
      weight = E.Usable_i[i][1];
      if (E.Usable_i[i][2] > 0) is_obstacle = true;
      break;
    }
  }
  count = count_;
  stackable = false;
}
int Usables::show() {
  printf("%s", "Usable: ");
  std::cout << name << std::endl;
  return count;
}
int Usables::get(int a) { return weight; }

Ammo::Ammo() {
  ammo_damage = 0;
  element = 0;
}
Ammo::Ammo(std::string &name_, int count_) {
  Existing_Items E;
  equiped = false;
  int ammo_damage_ = 0, element_ = 0;
  for (int j = 0; j < kAmmo_NUM; j++) {
    if (E.Ammo_s[j].compare(name_)) {
      name = name_;
      cost = E.Ammo_i[j][0];
      weight = E.Ammo_i[j][1];
      ammo_damage_ = E.Ammo_i[j][2];
      element_ = E.Ammo_i[j][3];
      stackable = true;
      break;
    }
  }
  set(name_, count_, ammo_damage_, element_);
}
Ammo::Ammo(std::string &name_) {
  Existing_Items E;
  equiped = false;
  int ammo_damage_ = 0, element_ = 0;
  for (int j = 0; j < kAmmo_NUM; j++) {
    if (E.Ammo_s[j].compare(name_)) {
      name = name_;
      cost = E.Ammo_i[j][0];
      weight = E.Ammo_i[j][1];
      ammo_damage_ = E.Ammo_i[j][2];
      element_ = E.Ammo_i[j][3];
      stackable = true;
      break;
    }
  }
  set(name_, 1, ammo_damage_, element_);
}
Ammo::Ammo(std::string &name_, int count_, int ammo_damage_, int element_) {
  set(name_, count_, ammo_damage_, element_);
}
void Ammo::set(std::string &name_, int count_, int ammo_damage_, int element_) {
  name = name_;
  count = count_;
  ammo_damage = ammo_damage_;
  stackable = true;
  element = element_;
}
int Ammo::show() {
  printf("%s", "Usable:");
  std::cout << name << std::endl;
  return count;
}
int Ammo::get(int a) { return weight; }

Magic_Items::Magic_Items() = default;
Magic_Items::Magic_Items(std::string &name_) {
  set(name_, 1);
}
Magic_Items::Magic_Items(std::string &name_, int count_) {
  set(name_, count_);
}
Magic_Items::~Magic_Items() = default;
void Magic_Items::set(std::string &name_, int count_) {
  Existing_Items E;
  equiped = false;
  for (int i = 0; i < kMagic_Items_NUM; i++) {
    if (E.Magic_Items_s[i].compare(name_)) {
      name = name_;
      passive_healing = E.Magic_Items_i[i][0];
      if (passive_healing == 2) {
        healing_dice = 4;
        num_of_dices = 2;
      }
      if (E.Magic_Items_i[i][1] > 0) arcane_focus = true;
      if (E.Magic_Items_i[i][2] > 0) druidic_focus = true;
      if (E.Magic_Items_i[i][3] > 0) holy_symbol = true;
      break;
    }
  }
  count = count_;
  stackable = false;
}
int Magic_Items::show() {
  printf("%s", "Usable:");
  std::cout << name << std::endl;
  return count;
}
int Magic_Items::get(int a) { return weight; }


