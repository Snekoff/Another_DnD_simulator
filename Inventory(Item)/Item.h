#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <fstream>
#include <string>
#include <vector>
#include "../gtest/googletest/include/gtest/gtest.h"
#include "../gtest/googlemock/include/gmock/gmock.h"
#include "../json_parse_by_nlohmann/json.hpp"
#ifndef ANOTHER_DND_SIMULATOR_ITEM_H
#define ANOTHER_DND_SIMULATOR_ITEM_H

const int kElements_Num = 6;
const int kWeapon_NUM = 29;
const int kWeapon_Parameters_Num = 5;
const int kRanged_Weapon_NUM = 9;
const int kRanged_Weapon_Parameters_Num = 7;
const int kAmmo_NUM = 4;
const int kAmmo_Parameters_Num = 4;
const int kArmor_NUM = 13;
const int kArmor_Parameters_Num = 5;
const int kGoods_NUM = 81;
const int kGoods_Parameters_Num = 3;
const int kMagic_Items_NUM = 13;
const int kMagic_Items_Parameters_Num = 3;
const int kAll_Num = kWeapon_NUM + kRanged_Weapon_NUM + kAmmo_NUM + kArmor_NUM + kGoods_NUM + kMagic_Items_NUM;
const int kItem_Types = 6;
const int kDamage_Types = 6;// bludgeoning not included and so on
const int kArmor_types = 3;
const int kClass_NuM = 12;

struct Existing_Items {
  std::string elements[kElements_Num] = {"no", "acid", "lightning", "fire", "cold", "poison"};
  std::string Weapon_s[kWeapon_NUM] = {"Club", "Dagger", "Greatclub", "Handaxe", "Javelin", "Light_hammer",
                                       "Mace", "Quarterstaff", "Sickle", "Spear", "Unarmed_strike", "Battleaxe",
                                       "Flail", "Glaive",
                                       "Greataxe", "Greatsword", "Halberd", "Lance", "Longsword", "Maul",
                                       "Morningstar", "Pike", "Rapier", "Scimitar", "Shortsword", "Trident",
                                       "War_pick", "Warhammer", "Whip"};
  int Weapon_i[kWeapon_NUM][kWeapon_Parameters_Num] =
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
  int Ranged_Weapon_i[kRanged_Weapon_NUM][kRanged_Weapon_Parameters_Num] =
      {{2500, 1, 8, 5, 0, 80, 320}, {5, 1, 4, 0, 0, 20, 60}, {2500, 1, 6, 2, 0, 80, 320}, {10, 1, 4, 0, 0, 30, 120},
       {1000, 1, 1, 1, 0, 25, 100}, {7500, 1, 6, 3, 0, 30, 120}, {5000, 1, 10, 18, 0, 100, 400},
       {5000, 1, 8, 2, 0, 150, 600},
       {100, 0, 0, 3, 0, 5, 15}};
  //cost(copper), num_of_dices, damage_dice, weight, type_of_elemental_damage , aiming_range, max_range
  std::string Ammo_s[kAmmo_NUM] = {"Arrows", "Blowgun_needles", "Crossbow_bolts", "Sling_bullets"};
  int Ammo_i[kAmmo_NUM][kAmmo_Parameters_Num] =
      {{1 * 100, 1, 0, 0}, {1 * 100, 1, 0, 0}, {1 * 100, 1, 0, 0}, {4, 1, 0, 0}};
  //cost, weight, ammo damage, element
  std::string Armor_s[kArmor_NUM] = {"Padded", "Leather", "Studded_leather",
                                     "Hide", "Chain_shirt", "Scale_mail", "Breastplate", "Half_plate",
                                     "Ring_mail", "Chain_mail", "Splint", "Plate",
                                     "Shield"};
  int Armor_i[kArmor_NUM][kArmor_Parameters_Num] = {{500, 0, 11, 0, 8}, {1000, 0, 11, 0, 10}, {4500, 0, 12, 0, 13},
                                                    {1000, 1, 12, 0, 12}, {5000, 1, 13, 0, 20}, {5000, 1, 14, 0, 45},
                                                    {40000, 1, 14, 0, 20}, {75000, 1, 15, 0, 40},
                                                    {3000, 2, 14, 0, 40}, {7500, 2, 16, 13, 55}, {20000, 2, 17, 15, 60},
                                                    {150000, 2, 18, 15, 65},
                                                    {1000, 2, 2, 0, 6}};
  //Cost , Type , Armor_Class , Strength_needed , weight
  bool Armor_b[kArmor_NUM] = {true, false, false,
                              false, false, true,
                              false, true,
                              true, true, true,
                              true,
                              false};
  // stealth_disadvantage
  std::string Goods_s[kGoods_NUM] = {"Abacus",
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
  int Goods_i[kGoods_NUM][kGoods_Parameters_Num] = {{200, 2, 0},
                                                       {25 * 100, 1, 0}, {50 * 100, 1, 0},
                                                       {50 * 100, 0, 0}, {2 * 100, 5, 0}, {1 * 100, 2, 1},
                                                       {2 * 100, 70, 0}, {4 * 10, 2, 0},
                                                       {1 * 100, 7, 0}, {1 * 100, 0, 0},
                                                       {5 * 10, 3, 0}, {1 * 100, 5, 0}, {25 * 100, 5, 0},
                                                       {2 * 100, 2, 0}, {5 * 10, 2, 0},
                                                       {1 * 100, 2, 0},
                                                       {1 * 10, 0, 0}, {1 * 100, 1, 0}, {1 * 100, 1, 0},
                                                       {5 * 100, 10, 0}, {1 * 10, 0, 0},
                                                       {5 * 100, 25, 0},
                                                       {25 * 100, 12, 0}, {5 * 10, 3, 0}, {5 * 100, 4, 0},
                                                       {15 * 100, 6, 0},
                                                       {2 * 100, 4, 0}, {25 * 100, 2, 0}, {2 * 100, 4, 0},
                                                       {1 * 100, 4, 0},
                                                       {2, 1, 0}, {2 * 100, 4, 0}, {1 * 100, 3, 0}, {2 * 100, 10, 0},
                                                       {5 * 100, 3, 0},
                                                       {25 * 100, 1, 0}, {25 * 100, 1, 0}, {5 * 100, 25, 0},
                                                       {10 * 100, 0, 0}, {2, 0, 0},
                                                       {2, 4, 0},
                                                       {1 * 10, 25, 0}, {5 * 10, 1, 0}, {10 * 100, 2, 0},
                                                       {5 * 100, 2, 0}, {10 * 100, 1, 0},
                                                       {100 * 100, 0, 0}, {2 * 100, 6, 0}, {2 * 10, 1, 0},
                                                       {1 * 10, 1, 0}, {2 * 10, 0, 0},
                                                       {1 * 10, 0, 0}, {5 * 100, 0, 0},
                                                       {2 * 100, 10, 0}, {5, 1, 0}, {100 * 100, 0, 0}, {5, 7, 0},
                                                       {2 * 100, 10, 0},
                                                       {5 * 10, 1, 0}, {1 * 100, 1, 0},
                                                       {4 * 100, 35, 0}, {5 * 10, 2, 0}, {1 * 100, 4, 0},
                                                       {1 * 100, 10, 0}, {10 * 100, 5, 0},
                                                       {1, 1, 0},
                                                       {5 * 100, 3, 0}, {5 * 10, 0, 0}, {2 * 100, 5, 0}, {5, 0, 0},
                                                       {5 * 100, 0, 0},
                                                       {2, 0, 0}, {50 * 100, 3, 0}, {1 * 100, 5, 0}, {1000 * 100, 1, 0},
                                                       {2 * 100, 20, 0},
                                                       {5 * 10, 1, 0},
                                                       {1, 1, 0}, {1 * 100, 0, 0}, {2 * 10, 5, 0}, {1, 1, 0}};
  //cost, weight, is_obstacle,
  std::string
      Magic_Items_s[kMagic_Items_NUM] = {"Crystal", "Orb", "Rod", "Staff", "Wand", "Spring_of_mistletoe", "Totem",
                                         "Wooden_staff", "Yew_wand", "Amulet", "Emblem", "Reliquary",
                                         "Potion_of_healing"};
  int Magic_Items_i[kMagic_Items_NUM][kMagic_Items_Parameters_Num] = {{1000, 1, 0}, {2000, 3, 0}, {1000, 2, 0},
                                                                      {500, 4, 0}, {1000, 1, 0}, {100, 0, 0},
                                                                      {100, 0, 0},
                                                                      {500, 4, 0}, {1000, 1, 0}, {500, 1, 0},
                                                                      {500, 0, 0},
                                                                      {500, 2, 0},
                                                                      {5000, 1, 2}};//2d4 + 2
  bool Magic_Items_b[kMagic_Items_NUM][kMagic_Items_Parameters_Num] =
      {{true, false, false}, {true, false, false}, {true, false, false},
       {true, false, false}, {true, false, false}, {false, true, false},
       {false, true, false},
       {false, true, false}, {false, true, false}, {false, false, true},
       {false, false, true},
       {false, false, true},
       {false, false, false}};
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
//types = {"G", "M", "SHP", "AT", "$", "SCF", "S",
// "HA", "INS", "RG", "TAH", "MA", "EXP", "P", "MNT",
// "VEH", "TG", "GS", "EM", "T", "LA", "OTH", "RD", "R"
// "SC", "A", "WD", "GV", "", "", "", "", "", "", "", "", }
// Goods, Melee, Ship, Artisan Tools, Valuables, Spell Casting Focus, Shield,
// Heavy Armor, Instrument (music)?, Ring, To Animal Handle?, MediumArmor, Explosive, Potions, Mounties
// Vehicle, Trade Goods, Gaming Set, ElectronicMachines???, Tools, Light Armor, OTH, Rod, Ranged
// Scroll, Ammo?, Wand, GV?
// No DMG, TftYP, ToA because of (no type)
class Item {
 protected:
  bool equiped;
  int num_equiped;
  std::string name;
  int count;
  bool stackable;
  int cost;
  int weight;
  std::string what_class_is_it;
  std::string source;
  std::string rarity;
  std::string tier;
  std::vector<std::string> entries;
 public:
  Item();
  ~Item();

  virtual std::string get_name();
  virtual int show();
  virtual void set_count(int a);
  virtual int get(int a);
  virtual void equip(int a);
  virtual bool is_equiped();
  virtual std::string What_class();
};

class Melee_Weapon : public Item {
 protected:
  int num_of_dices;
  int damage_dice;
  int type_of_elemental_damage;
 public:
  Melee_Weapon();
  Melee_Weapon(std::string &name_);
  Melee_Weapon(std::string &name_, int count_);
  //Weapon(std::string &name_, int count_, int num_of_dices_, int damage_dice_, int type_of_elemental_damage_);
  ~Melee_Weapon();
  virtual void set(std::string &name_, int count_);
  int show() override;
  virtual int get(int a);
};

class Ranged_Weapon : public Melee_Weapon {
 protected:
  int aiming_range;
  int max_range;
 public:
  Ranged_Weapon();
  Ranged_Weapon(std::string &name_);
  Ranged_Weapon(std::string &name_, int count_);
  /*Ranged_Weapon(std::string &name_, int count_, int num_of_dices_, int damage_dice_, int type_of_elemental_damage_,
                int aiming_range_, int max_range_);*/
  ~Ranged_Weapon();
  void set(std::string &name_, int count_) override;

  int show() override;

  int get(int a) override;
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
    printf("%s", "Goods:");
    std::cout << name << std::endl;
    return count;
  }
};*/

class Armor : public Item {
 protected:
  int type_of_armor;
  int armor_class;
  int strength_needed;
  bool stealth_disadvantage;
 public:
  Armor(std::string &name_);
  Armor(std::string &name_, int count_);
  //Armor(std::string &name_, int type_, int count_, int armor_class_, int strength_needed_, bool stealth_disadvantage_);
  ~Armor();
  void set(std::string &name_, int count_);
  int show() override;

  int get(int a) override;
};

class Goods : public Item {
 private:
  bool is_obstacle;
 public:
  Goods();
  Goods(std::string &name_, int count_);
  Goods(std::string &name_);
  ~Goods();
  virtual void set(std::string &name_, int count_);
  int show() override;

  virtual int get(int a);
};

class Ammo : public Goods {
 protected:
  int ammo_damage;
  int element;
 public:
  Ammo();
  Ammo(std::string &name_, int count_);
  Ammo(std::string &name_);
  //Ammo(std::string &name_, int count_, int ammo_damage_, int element_);
  void set(std::string &name_, int count_) override;
  int show() override;

  int get(int a) override;

};

class Magic_Items : public Item {
 private:
  int healing_dice;
  int num_of_healing_dices;
  int passive_healing;
  bool arcane_focus;
  bool druidic_focus;
  bool holy_symbol;
 public:
  Magic_Items();
  Magic_Items(std::string &name_);
  Magic_Items(std::string &name_, int count_);
  ~Magic_Items();
  void set(std::string &name_, int count_);
  int show() override;

  int get(int a) override;
};

class ArtisanTools : public Item {
 private:
 public:
  ArtisanTools();
  ArtisanTools(std::string &name_);
  ArtisanTools(std::string &name_, int count_);
  ~ArtisanTools();
  void set(std::string &name_, int count_);

  int get(int a) override;
};

class Ship : public Item {
 private:
  int speed;
  int carryingcapacity;
  int crew;
  int vehAc;
  int vehHp;
  int vehDmgThresh;
 public:
  Ship();
  Ship(std::string &name_);
  Ship(std::string &name_, int count_);
  ~Ship();
  void set(std::string &name_, int count_);

  int get(int a) override;
};

class Valuables : public Item {
 private:
 public:
  Valuables();
  Valuables(std::string &name_);
  Valuables(std::string &name_, int count_);
  ~Valuables();
  void set(std::string &name_, int count_);

  int get(int a) override;
};

class SpellCastingFocus : public Item {
 private:
  int scfType;//holy, druid, arcane
 public:
  SpellCastingFocus();
  SpellCastingFocus(std::string &name_);
  SpellCastingFocus(std::string &name_, int count_);
  ~SpellCastingFocus();
  void set(std::string &name_, int count_);

  int get(int a) override;
};

class Shield : public Item {
 private:
  int ac;
 public:
  Shield();
  Shield(std::string &name_);
  Shield(std::string &name_, int count_);
  ~Shield();
  void set(std::string &name_, int count_);

  int get(int a) override;
};

class Instrument : public Item {
 private:

 public:
  Instrument();
  Instrument(std::string &name_);
  Instrument(std::string &name_, int count_);
  ~Instrument();
  void set(std::string &name_, int count_);

  int get(int a) override;
};

class Ring : public Item {
 private:
  int resistance_type;
 public:
  Ring();
  Ring(std::string &name_);
  Ring(std::string &name_, int count_);
  ~Ring();
  void set(std::string &name_, int count_);

  int get(int a) override;
};

class AnimalGear : public Item {
 private:

 public:
  AnimalGear();
  AnimalGear(std::string &name_);
  AnimalGear(std::string &name_, int count_);
  ~AnimalGear();
  void set(std::string &name_, int count_);

  int get(int a) override;
};

class Explosive : public Item {
 private:
  std::string age;
 public:
  Explosive();
  Explosive(std::string &name_);
  Explosive(std::string &name_, int count_);
  ~Explosive();
  void set(std::string &name_, int count_);

  int get(int a) override;
};

class Potion : public Item {
 private:
 public:
  Potion();
  Potion(std::string &name_);
  Potion(std::string &name_, int count_);
  ~Potion();
  void set(std::string &name_, int count_);

  int get(int a) override;
};

class Mounties : public Item {
 private:
  int carryingcapacity;
  int speed;
 public:
  Mounties();
  Mounties(std::string &name_);
  Mounties(std::string &name_, int count_);
  ~Mounties();
  void set(std::string &name_, int count_);

  int get(int a) override;
};

class Vehicle : public Item {
 private:
 public:
  Vehicle();
  Vehicle(std::string &name_);
  Vehicle(std::string &name_, int count_);
  ~Vehicle();
  void set(std::string &name_, int count_);

  int get(int a) override;
};

class TradeGoods : public Item {
 private:

 public:
  TradeGoods();
  TradeGoods(std::string &name_);
  TradeGoods(std::string &name_, int count_);
  ~TradeGoods();
  void set(std::string &name_, int count_);

  int get(int a) override;
};

class GamingSet : public Item {
 private:

 public:
  GamingSet();
  GamingSet(std::string &name_);
  GamingSet(std::string &name_, int count_);
  ~GamingSet();
  void set(std::string &name_, int count_);

  int get(int a) override;
};

class Device : public Item {
 private:
  bool reqAttune;//?
 public:
  Device();//EM
  Device(std::string &name_);
  Device(std::string &name_, int count_);
  ~Device();
  void set(std::string &name_, int count_);

  int get(int a) override;
};

class Tools : public Item {
 private:

 public:
  Tools();
  Tools(std::string &name_);
  Tools(std::string &name_, int count_);
  ~Tools();
  void set(std::string &name_, int count_);

  int get(int a) override;
};

class OTH : public Item {
 private:

 public:
  OTH();
  OTH(std::string &name_);
  OTH(std::string &name_, int count_);
  ~OTH();
  void set(std::string &name_, int count_);

  int get(int a) override;
};

class Rod : public Item {
 private:
  bool reqAttune;
  bool reqAttuneByWho[kClass_NuM];//classes
 public:
  Rod();
  Rod(std::string &name_);
  Rod(std::string &name_, int count_);
  ~Rod();
  void set(std::string &name_, int count_);

  int get(int a) override;
};

class Scroll : public Item {
 private:

 public:
  Scroll();
  Scroll(std::string &name_);
  Scroll(std::string &name_, int count_);
  ~Scroll();
  void set(std::string &name_, int count_);

  int get(int a) override;
};

class Wand : public Item {
 private:
  bool reqAttune;
  bool reqAttuneByWho[kClass_NuM];//classes
 public:
  Wand();
  Wand(std::string &name_);
  Wand(std::string &name_, int count_);
  ~Wand();
  void set(std::string &name_, int count_);

  int get(int a) override;
};

class GV : public Item {
 private:

 public:
  GV();
  GV(std::string &name_);
  GV(std::string &name_, int count_);
  ~GV();
  void set(std::string &name_, int count_);

  int get(int a) override;
};

/*class  : public Item {
 private:

 public:
  Magic_Items();
  Magic_Items(std::string &name_);
  Magic_Items(std::string &name_, int count_);
  ~Magic_Items();
  void set(std::string &name_, int count_);

  int show() override;

  int get(int a) override;
};*/

#endif //ANOTHER_DND_SIMULATOR_ITEM_H
