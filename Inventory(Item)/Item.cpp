
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

const int kWeapon_NUM = 29;
const int kRanged_Weapon_NUM = 9;
const int kAmmo_NUM = 4;
const int kArmor_NUM = 13;
const int kUsable_NUM = 81;
const int kMagic_Items_NUM = 13;
const int kAll_Num = kWeapon_NUM + kRanged_Weapon_NUM + kAmmo_NUM + kArmor_NUM + kUsable_NUM + kMagic_Items_NUM;

struct Existing_Items {
  std::string Weapon_s[kWeapon_NUM] = {"Club", "Dagger", "Greatclub", "Handaxe", "Javelin", "Light_hammer",
                                       "Mace", "Quarterstaff", "Sickle", "Spear", "Unarmed_strike", "Battleaxe",
                                       "Flail", "Glaive",
                                       "Greataxe", "Greatsword", "Halberd", "Lance", "Longsword", "Maul",
                                       "Morningstar", "Pike", "Rapier", "Scimitar", "Shortsword", "Trident",
                                       "War_pick", "Warhammer", "Whip"};
  int Weapon_i[kWeapon_NUM][5] =
      {{10, 1, 4, 2, 0}, {200, 1, 4, 2, 0}, {20, 1, 8, 10, 0}, {500, 1, 6, 2, 0}, {50, 1, 6, 2, 0},
       {200, 1, 4, 2, 0}, {500, 1, 6, 4, 0}, {20, 1, 6, 4, 0}, {100, 1, 4, 2, 0}, {100, 1, 6, 3, 0},
       {0, 1, 1, 0, 0}, {1000, 1, 8, 4, 0}, {1000, 1, 8, 2, 0}, {2000, 1, 10, 6, 0},
       {3000, 1, 12, 7, 0}, {5000, 2, 6, 6, 0}, {2000, 1, 10, 6, 0}, {1000, 1, 12, 6, 0},
       {1500, 1, 8, 3, 0}, {1000, 2, 6, 10, 0}, {1500, 1, 8, 4, 0}, {500, 1, 10, 18, 0},
       {2500, 1, 8, 2, 0}, {2500, 1, 6, 3, 0}, {1000, 1, 6, 2, 0}, {500, 1, 6, 4, 0},
       {500, 1, 8, 2, 0}, {1500, 1, 8, 2, 0}, {200, 1, 4, 3, 0}};
  //cost(copper), num_of_dices, damage_dice, weight, type_of_elemental_damage
  std::string Ranged_Weapon_s[kRanged_Weapon_NUM] = {"Crossbow_light", "Dart", "Shortbow", "Sling", "Blowgun",
                                                     "Crossbow_hand", "Crossbow_heavy", "Longbow", "Net"};
  int Ranged_Weapon_i[kRanged_Weapon_NUM][7] =
      {{2500, 1, 8, 5, 0, 80, 320}, {5, 1, 4, 0, 0, 20, 60}, {2500, 1, 6, 2, 0, 80, 320}, {10, 1, 4, 0, 0, 30, 120},
       {1000, 1, 1, 1, 0, 25, 100}, {7500, 1, 6, 3, 0, 30, 120}, {5000, 1, 10, 18, 0, 100, 400},
       {5000, 1, 8, 2, 0, 150, 600},
       {100, 0, 0, 3, 0, 5, 15}};
  //cost(copper), num_of_dices, damage_dice, weight, type_of_elemental_damage , aiming_range, max_range
  std::string Ammo_s[kAmmo_NUM] = {"Arrows", "Blowgun_needles", "Crossbow_bolts", "Sling_bullets"};
  int Ammo_i[kAmmo_NUM][4] = {{1 * 100, 1, 0, 0}, {1 * 100, 1, 0, 0}, {1 * 100, 1, 0, 0}, {4, 1, 0, 0}};
  //cost, weight, ammo damage, element
  std::string Armor_s[kArmor_NUM] = {"Padded", "Leather", "Studded_leather",
                                     "Hide", "Chain_shirt", "Scale_mail", "Breastplate", "Half_plate",
                                     "Ring_mail", "Chain_mail", "Splint", "Plate",
                                     "Shield"};
  int Armor_i[kArmor_NUM][6] = {{500, 0, 11, 0, 1, 8}, {1000, 0, 11, 0, 0, 10}, {4500, 0, 12, 0, 0, 13},
                                {1000, 1, 12, 0, 0, 12}, {5000, 1, 13, 0, 0, 20}, {5000, 1, 14, 0, 1, 45},
                                {40000, 1, 14, 0, 0, 20}, {75000, 1, 15, 0, 1, 40},
                                {3000, 2, 14, 0, 1, 40}, {7500, 2, 16, 13, 1, 55}, {20000, 2, 17, 15, 1, 60},
                                {150000, 2, 18, 15, 1, 65},
                                {1000, 2, 2, 0, 0, 6}};
  //Cost , Type , Armor_Class , Strength_needed , stealth_disadvantage, weight
  std::string Usable_s[kUsable_NUM] = {"Abacus",
                                       "Acid_vial", "Alchemists_fire_flask",
                                       "Antitoxin", "Backpack", "Ball_bearings", "Barrel", "Basket", "Bedroll", "Bell",
                                       "Blanket", "Block_and_tackle", "Book", "Bottle_glass", "Bucket", "Caltrops",
                                       "Candle", "Case_crossbow_bolt", "Case_map_or_scroll", "Chain", "Chalk", "Chest",
                                       "Climber`s_kit", "Clothes_common", "Clothes_costume", "Clothes_fine",
                                       "Clothes_traveler`s", "Component_pounch", "Crowbar", "Fishing_tackle",
                                       "Flask_or_tankard", "Grappling_hook", "Hammer", "Hammer_sledge", "Healer`s kit",
                                       "Holy_water", "Hourglass", "Hunting_trap", "Ink", "Ink_pen", "Jug_or_pitcher",
                                       "Ladder", "Lamp", "Lantern_bullseye", "Lantern_hooded", "Lock",
                                       "Magnifying_glass", "Manacles", "Mess_kit", "Oil", "Paper", "Parchment",
                                       "Perfume",
                                       "Pick_miner`s", "Piton", "Poison_basic", "Pole", "Pot_iron", "Pouch", "Quiver",
                                       "Ram_portable", "Rations", "Robes", "Rope_hempen", "Rope_silk", "Sack",
                                       "Scale_merchant`s", "Sealing_wax", "Shovel", "Signal_whistle", "Signet_ring",
                                       "Soap", "Spellbook", "Spikes_iron", "Spyglass", "Tent_two_person", "Tinderbox",
                                       "Torch", "Vial", "Waterskin", "Whetstone"};
  int Usable_i[kUsable_NUM][3] = {{200, 2, 0},
                                  {25 * 100, 1, 0}, {50 * 100, 1, 0},
                                  {50 * 100, 0, 0}, {2 * 100, 5, 0}, {1 * 100, 2, 1}, {2 * 100, 70, 0}, {4 * 10, 2, 0},
                                  {1 * 100, 7, 0}, {1 * 100, 0, 0},
                                  {5 * 10, 3, 0}, {1 * 100, 5, 0}, {25 * 100, 5, 0}, {2 * 100, 2, 0}, {5 * 10, 2, 0},
                                  {1 * 100, 2, 0},
                                  {1 * 10, 0, 0}, {1 * 100, 1, 0}, {1 * 100, 1, 0}, {5 * 100, 10, 0}, {1 * 10, 0, 0},
                                  {5 * 100, 25, 0},
                                  {25 * 100, 12, 0}, {5 * 10, 3, 0}, {5 * 100, 4, 0}, {15 * 100, 6, 0},
                                  {2 * 100, 4, 0}, {25 * 100, 2, 0}, {2 * 100, 4, 0}, {1 * 100, 4, 0},
                                  {2, 1, 0}, {2 * 100, 4, 0}, {1 * 100, 3, 0}, {2 * 100, 10, 0}, {5 * 100, 3, 0},
                                  {25 * 100, 1, 0}, {25 * 100, 1, 0}, {5 * 100, 25, 0}, {10 * 100, 0, 0}, {2, 0, 0},
                                  {2, 4, 0},
                                  {1 * 10, 25, 0}, {5 * 10, 1, 0}, {10 * 100, 2, 0}, {5 * 100, 2, 0}, {10 * 100, 1, 0},
                                  {100 * 100, 0, 0}, {2 * 100, 6, 0}, {2 * 10, 1, 0}, {1 * 10, 1, 0}, {2 * 10, 0, 0},
                                  {1 * 10, 0, 0}, {5 * 100, 0, 0},
                                  {2 * 100, 10, 0}, {5, 1, 0}, {100 * 100, 0, 0}, {5, 7, 0}, {2 * 100, 10, 0},
                                  {5 * 10, 1, 0}, {1 * 100, 1, 0},
                                  {4 * 100, 35, 0}, {5 * 10, 2, 0}, {1 * 100, 4, 0}, {1 * 100, 10, 0}, {10 * 100, 5, 0},
                                  {1, 1, 0},
                                  {5 * 100, 3, 0}, {5 * 10, 0, 0}, {2 * 100, 5, 0}, {5, 0, 0}, {5 * 100, 0, 0},
                                  {2, 0, 0}, {50 * 100, 3, 0}, {1 * 100, 5, 0}, {1000 * 100, 1, 0}, {2 * 100, 20, 0},
                                  {5 * 10, 1, 0},
                                  {1, 1, 0}, {1 * 100, 0, 0}, {2 * 10, 5, 0}, {1, 1, 0}};
  //cost, weight, is_obstacle,
  std::string
      Magic_Items_s[kMagic_Items_NUM] = {"Crystal", "Orb", "Rod", "Staff", "Wand", "Spring_of_mistletoe", "Totem",
                                         "Wooden_staff", "Yew_wand", "Amulet", "Emblem", "Reliquary",
                                         "Potion_of_healing"};
  int Magic_Items_i[kMagic_Items_NUM][6] = {{1000, 1, 0, 1, 0, 0}, {2000, 3, 0, 1, 0, 0}, {1000, 2, 0, 1, 0, 0},
                                            {500, 4, 0, 1, 0, 0}, {1000, 1, 0, 1, 0, 0}, {100, 0, 0, 0, 1, 0},
                                            {100, 0, 0, 0, 1, 0},
                                            {500, 4, 0, 0, 1, 0}, {1000, 1, 0, 0, 1, 0}, {500, 1, 0, 0, 0, 1},
                                            {500, 0, 0, 0, 0, 1},
                                            {500, 2, 0, 0, 0, 1},
                                            {5000, 1, 2, 0, 0, 0}};//2d4 + 2
  //cost, weight, healing, arcane_focus, druidic_focus, holy_symbol;
  std::string All_s[kAll_Num] = {"Club", "Dagger", "Greatclub", "Handaxe", "Javelin", "Light_hammer",
                                 "Mace", "Quarterstaff", "Sickle", "Spear", "Unarmed_strike", "Battleaxe", "Flail",
                                 "Glaive",
                                 "Greataxe", "Greatsword", "Halberd", "Lance", "Longsword", "Maul",
                                 "Morningstar", "Pike", "Rapier", "Scimitar", "Shortsword", "Trident",
                                 "War_pick", "Warhammer", "Whip",
                                 "Crossbow_light", "Dart", "Shortbow", "Sling", "Blowgun",
                                 "Crossbow_hand", "Crossbow_heavy", "Longbow", "Net",
                                 "Arrows", "Blowgun_needles", "Crossbow_bolts", "Sling_bullets",
                                 "Padded", "Leather", "Studded_leather",
                                 "Hide", "Chain_shirt", "Scale_mail", "Breastplate", "Half_plate",
                                 "Ring_mail", "Chain_mail", "Splint", "Plate",
                                 "Shield",
                                 "Abacus",
                                 "Acid_vial", "Alchemists_fire_flask",
                                 "Antitoxin", "Backpack", "Ball_bearings", "Barrel", "Basket", "Bedroll", "Bell",
                                 "Blanket", "Block_and_tackle", "Book", "Bottle_glass", "Bucket", "Caltrops",
                                 "Candle", "Case_crossbow_bolt", "Case_map_or_scroll", "Chain", "Chalk", "Chest",
                                 "Climber`s_kit", "Clothes_common", "Clothes_costume", "Clothes_fine",
                                 "Clothes_traveler`s", "Component_pounch", "Crowbar", "Fishing_tackle",
                                 "Flask_or_tankard", "Grappling_hook", "Hammer", "Hammer_sledge", "Healer`s kit",
                                 "Holy_water", "Hourglass", "Hunting_trap", "Ink", "Ink_pen", "Jug_or_pitcher",
                                 "Ladder", "Lamp", "Lantern_bullseye", "Lantern_hooded", "Lock",
                                 "Magnifying_glass", "Manacles", "Mess_kit", "Oil", "Paper", "Parchment", "Perfume",
                                 "Pick_miner`s", "Piton", "Poison_basic", "Pole", "Pot_iron", "Pouch", "Quiver",
                                 "Ram_portable", "Rations", "Robes", "Rope_hempen", "Rope_silk", "Sack",
                                 "Scale_merchant`s", "Sealing_wax", "Shovel", "Signal_whistle", "Signet_ring",
                                 "Soap", "Spellbook", "Spikes_iron", "Spyglass", "Tent_two_person", "Tinderbox",
                                 "Torch", "Vial", "Waterskin", "Whetstone",
                                 "Crystal", "Orb", "Rod", "Staff", "Wand", "Spring_of_mistletoe", "Totem",
                                 "Wooden_staff", "Yew_wand", "Amulet", "Emblem", "Reliquary", "Potion_of_healing"};
};

class Item {
 protected:
  bool equiped;
  int num_equiped;
  std::string name;
  int count;
  bool stackable;
  int cost;
  int weight;
 public:
  Item() : name("Rope") { // : name(name) first initialise with reference
    equiped = false;
    count = 0;
    num_equiped = 0;
    stackable = false;
    cost = 0;
    weight = 0;
  }
  ~Item() = default;

  virtual std::string get_name() {
    return name;
  };
  virtual int show() { return count; };
  virtual int get_count() { return count; };
  virtual void set_count(int a) { count += a; };
  virtual int get_cost() { return cost; }
  virtual int get(int a) { if (a == 1) return weight; }
  virtual void equip(int a) { num_equiped+=a;if(num_equiped == count) equiped = true; else equiped = false;}
  virtual bool is_equiped() { return equiped; }
};

class Weapon : public Item {
 protected:
  int num_of_dices;
  int damage_dice;
  int type_of_elemental_damage;
  std::string elements[6] = {"no", "acid", "lightning", "fire", "cold", "poison"};
 public:
  Weapon() = default;
  Weapon(std::string &name_) {
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
  Weapon(std::string &name_, int count_) {
    name = name_;
    count = count_;
    num_of_dices = 0;
    damage_dice = 0;
    type_of_elemental_damage = 0;
  }
  Weapon(std::string &name_, int count_, int num_of_dices_, int damage_dice_, int type_of_elemental_damage_) {
    set(name_, count_, num_of_dices_, damage_dice_, type_of_elemental_damage_);
  }
  ~Weapon() = default;
  void set(std::string &name_, int count_, int num_of_dices_, int damage_dice_, int type_of_elemental_damage_) {
    name = name_;
    count = count_;
    stackable = false;
    num_of_dices = num_of_dices_;
    damage_dice = damage_dice_;
    type_of_elemental_damage = type_of_elemental_damage_;
  }
  int show() {
    std::cout << name << std::endl;
    std::cout << "Damage " << num_of_dices << "d" << damage_dice <<
              " element: " << elements[type_of_elemental_damage] << std::endl;
    return damage_dice;
  }
  int get(int a) { return weight; }
};

class Ranged_Weapon : public Weapon {
 protected:
  int aiming_range;
  int max_range;
 public:
  Ranged_Weapon() = default;
  Ranged_Weapon(std::string &name_) {
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
  Ranged_Weapon(std::string &name_, int count_) {
    name = name_;
    count = count_;
    aiming_range = 0;
    max_range = 0;
  }
  Ranged_Weapon(std::string &name_, int count_, int num_of_dices_, int damage_dice_, int type_of_elemental_damage_,
                int aiming_range_, int max_range_) {
    set(name_, count_, num_of_dices_, damage_dice_, type_of_elemental_damage_, aiming_range_, max_range_);
  }
  ~Ranged_Weapon() = default;
  void set(std::string &name_, int count_, int num_of_dices_, int damage_dice_, int type_of_elemental_damage_,
           int aiming_range_, int max_range_) {
    name = name_;
    count = count_;
    stackable = false;
    num_of_dices = num_of_dices_;
    damage_dice = damage_dice_;
    type_of_elemental_damage = type_of_elemental_damage_;
    aiming_range = aiming_range_;
    max_range = max_range_;
  }

  int show() {
    std::cout << name << std::endl;
    std::cout << "Damage " << num_of_dices << "d" << damage_dice <<
              " element:" << elements[type_of_elemental_damage] << std::endl;
    return damage_dice;
  }

  int get(int a) { return weight; }
};

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

class Armor : public Item {
 protected:
  int type;
  int armor_class;
  int strength_needed;
  bool stealth_disadvantage;
 public:
  Armor(std::string &name_) {
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
  Armor(std::string &name_, int count_) {
    name = name_;
    count = count_;
    type = 0;
    armor_class = 0;
    strength_needed = 0;
    stealth_disadvantage = false;
  }
  Armor(std::string &name_, int type_, int count_, int armor_class_, int strength_needed_, bool stealth_disadvantage_) {
    set(name_, type_, count_, armor_class_, strength_needed_, stealth_disadvantage_);
  }
  ~Armor() = default;
  void set(std::string &name_,
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
  int show() {
    std::cout << name << std::endl;
    printf("%s %d %s %d \n", "Armor Class:", armor_class, "stealth disadvantage:", stealth_disadvantage);
    return armor_class;
  }

  int get(int a) {
    if (a == 0) return type;
    else if (a == 1) { return weight; }
    else if (a == 2) { return armor_class; }
    else if (a == 3) { return strength_needed; }
  }
};

class Usables : public Item {
 private:
  bool is_obstacle;
 public:
  Usables() {
    stackable = false;
    is_obstacle = false;
  };
  Usables(std::string &name_, int count_) {
    stackable = false;
    is_obstacle = false;
    set(name_, count_);
  }
  Usables(std::string &name_) {
    stackable = false;
    is_obstacle = false;
    set(name_, 1);
  }
  ~Usables() = default;
  void set(std::string &name_, int count_) {
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
  int show() {
    printf("%s", "Usable: ");
    std::cout << name << std::endl;
    return count;
  }

  int get(int a) { return weight; }
};

class Ammo : public Usables {
 protected:
  int ammo_damage;
  int element;
 public:
  Ammo() {
    ammo_damage = 0;
    element = 0;
  }
  Ammo(std::string &name_, int count_) {
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
  Ammo(std::string &name_) {
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
  Ammo(std::string &name_, int count_, int ammo_damage_, int element_) {
    set(name_, count_, ammo_damage_, element_);
  }
  void set(std::string &name_, int count_, int ammo_damage_, int element_) {
    name = name_;
    count = count_;
    ammo_damage = ammo_damage_;
    stackable = true;
    element = element_;
  }
  int show() {
    printf("%s", "Usable:");
    std::cout << name << std::endl;
    return count;
  }

  int get(int a) { return weight; }

};

class Magic_Items : public Item {
 private:
  int healing_dice;
  int num_of_dices;
  int passive_healing;
  bool arcane_focus;
  bool druidic_focus;
  bool holy_symbol;
 public:
  Magic_Items() = default;
  Magic_Items(std::string &name_) {
    set(name_, 1);
  }
  ~Magic_Items() = default;
  void set(std::string &name_, int count_) {
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
  int show() {
    printf("%s", "Usable:");
    std::cout << name << std::endl;
    return count;
  }

  int get(int a) { return weight; }
};

