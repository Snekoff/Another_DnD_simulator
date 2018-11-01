
#include "Item.h"
using json = nlohmann::json;

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

Melee_Weapon::Melee_Weapon() = default;
Melee_Weapon::Melee_Weapon(std::string &name_) {
  set(name_, 1);
}
Melee_Weapon::Melee_Weapon(std::string &name_, int count_) {
  num_of_dices = 0;
  damage_dice = 0;
  type_of_elemental_damage = 0;
  set(name_, count_);
}
/*Weapon::Weapon(std::string &name_, int count_, int num_of_dices_, int damage_dice_, int type_of_elemental_damage_) {
  set(name_, count_, num_of_dices_, damage_dice_, type_of_elemental_damage_);
}*/
Melee_Weapon::~Melee_Weapon() = default;
void Melee_Weapon::set(std::string &name_, int count_) {
  Existing_Items E_I;
  name = " ";
  equiped = false;
  for (int i = 0; i < kWeapon_NUM; i++) {
    if (E_I.Weapon_s[i] == name_) {
      name = name_;
      cost = E_I.Weapon_i[i][0];
      num_of_dices = E_I.Weapon_i[i][1];
      damage_dice = E_I.Weapon_i[i][2];
      weight = E_I.Weapon_i[i][3];
      type_of_elemental_damage = E_I.Weapon_i[i][4];
      stackable = false;
      break;
    }
  }
  count = count_;
  if(name == " "){
    source = "Default";
    std::ifstream inputJson;
    inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.jsonjson ");
    json j = json::parse(inputJson);
    for(auto i : j["name"]){
      if(j["item"]["type"] != NULL){
        if(name_ == i["name"]){
          name = name_;
          rarity = i["rarity"];
          weight = i["weight"];
          source = i["source"];
          if(i["tier"] != NULL) tier = i["tier"];

          break;
        }
      }
    }
  }
  what_class_is_it = "Weapon";
}
int Melee_Weapon::show() {
  Existing_Items E_I;
  std::cout << name << std::endl;
  std::cout << "Damage " << num_of_dices << "d" << damage_dice <<
            " element: " << E_I.elements[type_of_elemental_damage] << std::endl;
  return damage_dice;
}
int Melee_Weapon::get(int a) {
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
  name = " ";
  equiped = false;
  for (int i = 0; i < kRanged_Weapon_NUM; i++) {
    if (E_I.Ranged_Weapon_s[i] == name_) {
      name = name_;
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
  count = count_;
  if(name == " "){
    source = "Default";
    std::ifstream inputJson;
    inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.jsonjson ");
    json j = json::parse(inputJson);
    for(auto i : j["name"]){
      if(j["item"]["type"] != NULL){
        if(name_ == i["name"]){
          name = name_;
          rarity = i["rarity"];
          weight = i["weight"];
          source = i["source"];
          if(i["tier"] != NULL) tier = i["tier"];

          break;
        }
      }
    }
  }
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
  Existing_Items E_I;
  name = " ";
  equiped = false;
  for (int i = 0; i < kArmor_NUM; i++) {
    if (E_I.Armor_s[i] == name_) {
      name = name_;
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
  count = count_;
  if(name == " "){
    source = "Default";
    std::ifstream inputJson;
    inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.jsonjson ");
    json j = json::parse(inputJson);
    for(auto i : j["name"]){
      if(j["item"]["type"] != NULL){
        if(name_ == i["name"]){
          name = name_;
          rarity = i["rarity"];
          weight = i["weight"];
          source = i["source"];
          if(i["tier"] != NULL) tier = i["tier"];

          break;
        }
      }
    }
  }
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

Goods::Goods() {
  stackable = false;
  is_obstacle = false;
};
Goods::Goods(std::string &name_, int count_) {
  stackable = false;
  is_obstacle = false;
  set(name_, count_);
}
Goods::Goods(std::string &name_) {
  stackable = false;
  is_obstacle = false;
  set(name_, 1);
}
Goods::~Goods() = default;
void Goods::set(std::string &name_, int count_) {
  Existing_Items E_I;
  name = " ";
  equiped = false;
  for (int i = 0; i < kGoods_NUM; i++) {
    if (E_I.Goods_s[i] == name_) {
      name = name_;
      cost = E_I.Goods_i[i][0];
      weight = E_I.Goods_i[i][1];
      if (E_I.Goods_i[i][2] != 0) is_obstacle = true;
      break;
    }
  }
  count = count_;
  if(name == " "){
    source = "Default";
    std::ifstream inputJson;
    inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
    json j = json::parse(inputJson);
    for(auto i : j["name"]){
      if(j["item"]["type"] != NULL){
        if(name_ == i["name"]){
          name = name_;
          rarity = i["rarity"];
          weight = i["weight"];
          source = i["source"];
          if(i["tier"] != NULL) tier = i["tier"];

          break;
        }
      }
    }
  }
  stackable = false;
  what_class_is_it = "Goods";
}
int Goods::show() {
  printf("%s", "Goods: ");
  std::cout << name << std::endl;
  return count;
}
int Goods::get(int a) {
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
  name = " ";
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
  count = count_;
  if(name == " "){
    source = "Default";
    std::ifstream inputJson;
    inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
    json j = json::parse(inputJson);
    for(auto i : j["name"]){
      if(j["item"]["type"] != NULL){
        if(name_ == i["name"]){
          name = name_;
          rarity = i["rarity"];
          weight = i["weight"];
          source = i["source"];
          if(i["tier"] != NULL) tier = i["tier"];

          break;
        }
      }
    }
  }
  stackable = true;
  what_class_is_it = "Ammo";
}
int Ammo::show() {
  printf("%s", "Goods:");
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
  name = " ";
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
  if(name == " "){
    source = "Default";
    std::ifstream inputJson;
    inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
    json j = json::parse(inputJson);
    for(auto i : j["name"]){
      if(j["item"]["type"] != NULL){
        if(name_ == i["name"]){
          name = name_;
          rarity = i["rarity"];
          weight = i["weight"];
          source = i["source"];
          if(i["tier"] != NULL) tier = i["tier"];

          break;
        }
      }
    }
  }
  stackable = false;
  what_class_is_it = "Magic_Items";
}
int Magic_Items::show() {
  printf("%s", "Goods:");
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

//012030122222222222222224295392485709485739084593847529384705234509823745983475029834579238547093845720398457

ArtisanTools::ArtisanTools() = default;
ArtisanTools::ArtisanTools(std::string &name_) {
  set(name_, 1);
}
ArtisanTools::ArtisanTools(std::string &name_, int count_) {
  set(name_, count_);
}
ArtisanTools::~ArtisanTools() = default;
void ArtisanTools::set(std::string &name_, int count_) {
  weight = 0;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  for(auto i : j["name"]){
    if(j["item"]["type"] != NULL){
      if(name_ == i["name"]){
        name = name_;
        rarity = i["rarity"];
        weight = i["weight"];
        source = i["source"];
        if(i["tier"] != NULL) tier = i["tier"];
        
        break;
      }
    }
  }
  what_class_is_it = "ArtisanTools";
}
int ArtisanTools::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  return -1;
}

Ship::Ship() = default;
Ship::Ship(std::string &name_) {
  set(name_, 1);
}
Ship::Ship(std::string &name_, int count_) {
  set(name_, count_);
}
Ship::~Ship() = default;
void Ship::set(std::string &name_, int count_) {
  weight = 0;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  for(auto i : j["name"]){
    if(j["item"]["type"] != NULL){
      if(name_ == i["name"]){
        name = name_;
        rarity = i["rarity"];
        weight = i["weight"];
        source = i["source"];
        if(i["tier"] != NULL) tier = i["tier"];
        
        break;
      }
    }
  }
  what_class_is_it = "Ship";
}
int Ship::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  return -1;
}

Valuables::Valuables() = default;
Valuables::Valuables(std::string &name_) {
  set(name_, 1);
}
Valuables::Valuables(std::string &name_, int count_) {
  set(name_, count_);
}
Valuables::~Valuables() = default;
void Valuables::set(std::string &name_, int count_) {
  weight = 0;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  for(auto i : j["name"]){
    if(j["item"]["type"] != NULL){
      if(name_ == i["name"]){
        name = name_;
        rarity = i["rarity"];
        weight = i["weight"];
        source = i["source"];
        if(i["tier"] != NULL) tier = i["tier"];
        
        break;
      }
    }
  }
  what_class_is_it = "Valuables";
}
int Valuables::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  return -1;
}

SpellCastingFocus::SpellCastingFocus() = default;
SpellCastingFocus::SpellCastingFocus(std::string &name_) {
  set(name_, 1);
}
SpellCastingFocus::SpellCastingFocus(std::string &name_, int count_) {
  set(name_, count_);
}
SpellCastingFocus::~SpellCastingFocus() = default;
void SpellCastingFocus::set(std::string &name_, int count_) {
  weight = 0;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  for(auto i : j["name"]){
    if(j["item"]["type"] != NULL){
      if(name_ == i["name"]){
        name = name_;
        rarity = i["rarity"];
        weight = i["weight"];
        source = i["source"];
        if(i["tier"] != NULL) tier = i["tier"];
        
        break;
      }
    }
  }
  if(source == "Default"){
    Existing_Items E_I;
    for(int i = 0; i < ; i++){

    }
  }
  what_class_is_it = "SpellCastingFocus";
}
int SpellCastingFocus::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  return -1;
}

Shield::Shield() = default;
Shield::Shield(std::string &name_) {
  set(name_, 1);
}
Shield::Shield(std::string &name_, int count_) {
  set(name_, count_);
}
Shield::~Shield() = default;
void Shield::set(std::string &name_, int count_) {
  weight = 0;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  for(auto i : j["name"]){
    if(j["item"]["type"] != NULL){
      if(name_ == i["name"]){
        name = name_;
        rarity = i["rarity"];
        weight = i["weight"];
        source = i["source"];
        if(i["tier"] != NULL) tier = i["tier"];
        
        break;
      }
    }
  }
  if(source == "Default"){
    Existing_Items E_I;
    for(int i = 0; i < ; i++){

    }
  }
  what_class_is_it = "Shield";
}
int Shield::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  return -1;
}

Instrument::Instrument() = default;
Instrument::Instrument(std::string &name_) {
  set(name_, 1);
}
Instrument::Instrument(std::string &name_, int count_) {
  set(name_, count_);
}
Instrument::~Instrument() = default;
void Instrument::set(std::string &name_, int count_) {
  weight = 0;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  for(auto i : j["name"]){
    if(j["item"]["type"] != NULL){
      if(name_ == i["name"]){
        name = name_;
        rarity = i["rarity"];
        weight = i["weight"];
        source = i["source"];
        if(i["tier"] != NULL) tier = i["tier"];
        
        break;
      }
    }
  }
  what_class_is_it = "Instrument";
}
int Instrument::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  return -1;
}

Ring::Ring() = default;
Ring::Ring(std::string &name_) {
  set(name_, 1);
}
Ring::Ring(std::string &name_, int count_) {
  set(name_, count_);
}
Ring::~Ring() = default;
void Ring::set(std::string &name_, int count_) {
  weight = 0;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  for(auto i : j["name"]){
    if(j["item"]["type"] != NULL){
      if(name_ == i["name"]){
        name = name_;
        rarity = i["rarity"];
        weight = i["weight"];
        source = i["source"];
        if(i["tier"] != NULL) tier = i["tier"];
        
        break;
      }
    }
  }
  if(source == "Default"){
    Existing_Items E_I;
    for(int i = 0; i < kGoods_NUM; i++){
      if(name_ == E_I.Goods_s[i]){
        name = name_;
        cost =
        break;
      }
    }
  }
  what_class_is_it = "Ring";
}
int Ring::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  return -1;
}

AnimalGear::AnimalGear() = default;
AnimalGear::AnimalGear(std::string &name_) {
  set(name_, 1);
}
AnimalGear::AnimalGear(std::string &name_, int count_) {
  set(name_, count_);
}
AnimalGear::~AnimalGear() = default;
void AnimalGear::set(std::string &name_, int count_) {
  weight = 0;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  for(auto i : j["name"]){
    if(j["item"]["type"] != NULL){
      if(name_ == i["name"]){
        name = name_;
        rarity = i["rarity"];
        weight = i["weight"];
        source = i["source"];
        if(i["tier"] != NULL) tier = i["tier"];
        
        break;
      }
    }
  }
  what_class_is_it = "AnimalGear";
}
int AnimalGear::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  return -1;
}

Explosive::Explosive() = default;
Explosive::Explosive(std::string &name_) {
  set(name_, 1);
}
Explosive::Explosive(std::string &name_, int count_) {
  set(name_, count_);
}
Explosive::~Explosive() = default;
void Explosive::set(std::string &name_, int count_) {
  weight = 0;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  for(auto i : j["name"]){
    if(j["item"]["type"] != NULL){
      if(name_ == i["name"]){
        name = name_;
        rarity = i["rarity"];
        weight = i["weight"];
        source = i["source"];
        if(i["tier"] != NULL) tier = i["tier"];
        
        break;
      }
    }
  }
  what_class_is_it = "Explosive";
}
int Explosive::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  return -1;
}

Potion::Potion() = default;
Potion::Potion(std::string &name_) {
  set(name_, 1);
}
Potion::Potion(std::string &name_, int count_) {
  set(name_, count_);
}
Potion::~Potion() = default;
void Potion::set(std::string &name_, int count_) {
  weight = 0;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  for(auto i : j["name"]){
    if(j["item"]["type"] != NULL){
      if(name_ == i["name"]){
        name = name_;
        rarity = i["rarity"];
        weight = i["weight"];
        source = i["source"];
        if(i["tier"] != NULL) tier = i["tier"];
        
        break;
      }
    }
  }
  if(source == "Default"){
    Existing_Items E_I;
    for(int i = 0; i < ; i++){

    }
  }
  what_class_is_it = "Potion";
}
int Potion::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  return -1;
}

Mounties::Mounties() = default;
Mounties::Mounties(std::string &name_) {
  set(name_, 1);
}
Mounties::Mounties(std::string &name_, int count_) {
  set(name_, count_);
}
Mounties::~Mounties() = default;
void Mounties::set(std::string &name_, int count_) {
  weight = 0;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  for(auto i : j["name"]){
    if(j["item"]["type"] != NULL){
      if(name_ == i["name"]){
        name = name_;
        rarity = i["rarity"];
        weight = i["weight"];
        source = i["source"];
        if(i["tier"] != NULL) tier = i["tier"];
        
        break;
      }
    }
  }
  what_class_is_it = "Mounties";
}
int Mounties::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  return -1;
}

Vehicle::Vehicle() = default;
Vehicle::Vehicle(std::string &name_) {
  set(name_, 1);
}
Vehicle::Vehicle(std::string &name_, int count_) {
  set(name_, count_);
}
Vehicle::~Vehicle() = default;
void Vehicle::set(std::string &name_, int count_) {
  weight = 0;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  for(auto i : j["name"]){
    if(j["item"]["type"] != NULL){
      if(name_ == i["name"]){
        name = name_;
        rarity = i["rarity"];
        weight = i["weight"];
        source = i["source"];
        if(i["tier"] != NULL) tier = i["tier"];
        
        break;
      }
    }
  }
  what_class_is_it = "Vehicle";
}
int Vehicle::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  return -1;
}

TradeGoods::TradeGoods() = default;
TradeGoods::TradeGoods(std::string &name_) {
  set(name_, 1);
}
TradeGoods::TradeGoods(std::string &name_, int count_) {
  set(name_, count_);
}
TradeGoods::~TradeGoods() = default;
void TradeGoods::set(std::string &name_, int count_) {
  weight = 0;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  for(auto i : j["name"]){
    if(j["item"]["type"] != NULL){
      if(name_ == i["name"]){
        name = name_;
        rarity = i["rarity"];
        weight = i["weight"];
        source = i["source"];
        if(i["tier"] != NULL) tier = i["tier"];
        
        break;
      }
    }
  }
  what_class_is_it = "TradeGoods";
}
int TradeGoods::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  return -1;
}

GamingSet::GamingSet() = default;
GamingSet::GamingSet(std::string &name_) {
  set(name_, 1);
}
GamingSet::GamingSet(std::string &name_, int count_) {
  set(name_, count_);
}
GamingSet::~GamingSet() = default;
void GamingSet::set(std::string &name_, int count_) {
  weight = 0;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  for(auto i : j["name"]){
    if(j["item"]["type"] != NULL){
      if(name_ == i["name"]){
        name = name_;
        rarity = i["rarity"];
        weight = i["weight"];
        source = i["source"];
        if(i["tier"] != NULL) tier = i["tier"];
        
        break;
      }
    }
  }
  what_class_is_it = "GamingSet";
}
int GamingSet::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  return -1;
}

Device::Device() = default;
Device::Device(std::string &name_) {
  set(name_, 1);
}
Device::Device(std::string &name_, int count_) {
  set(name_, count_);
}
Device::~Device() = default;
void Device::set(std::string &name_, int count_) {
  weight = 0;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  for(auto i : j["name"]){
    if(j["item"]["type"] != NULL){
      if(name_ == i["name"]){
        name = name_;
        rarity = i["rarity"];
        weight = i["weight"];
        source = i["source"];
        if(i["tier"] != NULL) tier = i["tier"];
        
        break;
      }
    }
  }
  what_class_is_it = "Device";
}
int Device::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  return -1;
}

Tools::Tools() = default;
Tools::Tools(std::string &name_) {
  set(name_, 1);
}
Tools::Tools(std::string &name_, int count_) {
  set(name_, count_);
}
Tools::~Tools() = default;
void Tools::set(std::string &name_, int count_) {
  weight = 0;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  for(auto i : j["name"]){
    if(j["item"]["type"] != NULL){
      if(name_ == i["name"]){
        name = name_;
        rarity = i["rarity"];
        weight = i["weight"];
        source = i["source"];
        if(i["tier"] != NULL) tier = i["tier"];
        
        break;
      }
    }
  }
  what_class_is_it = "Tools";
}
int Tools::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  return -1;
}

Rod::Rod() = default;
Rod::Rod(std::string &name_) {
  set(name_, 1);
}
Rod::Rod(std::string &name_, int count_) {
  set(name_, count_);
}
Rod::~Rod() = default;
void Rod::set(std::string &name_, int count_) {
  weight = 0;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  for(auto i : j["name"]){
    if(j["item"]["type"] != NULL){
      if(name_ == i["name"]){
        name = name_;
        rarity = i["rarity"];
        weight = i["weight"];
        source = i["source"];
        if(i["tier"] != NULL) tier = i["tier"];
        
        break;
      }
    }
  }

  what_class_is_it = "Rod";
}
int Rod::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  return -1;
}

Scroll::Scroll() = default;
Scroll::Scroll(std::string &name_) {
  set(name_, 1);
}
Scroll::Scroll(std::string &name_, int count_) {
  set(name_, count_);
}
Scroll::~Scroll() = default;
void Scroll::set(std::string &name_, int count_) {
  weight = 0;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  for(auto i : j["name"]){
    if(j["item"]["type"] != NULL){
      if(name_ == i["name"]){
        name = name_;
        rarity = i["rarity"];
        weight = i["weight"];
        source = i["source"];
        if(i["tier"] != NULL) tier = i["tier"];
        
        break;
      }
    }
  }
  what_class_is_it = "Scroll";
}
int Scroll::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  return -1;
}

Wand::Wand() = default;
Wand::Wand(std::string &name_) {
  set(name_, 1);
}
Wand::Wand(std::string &name_, int count_) {
  set(name_, count_);
}
Wand::~Wand() = default;
void Wand::set(std::string &name_, int count_) {
  weight = 0;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  for(auto i : j["name"]){
    if(i["type"] != NULL){
      if(name_ == i["name"]){
        name = name_;
        rarity = i["rarity"];
        weight = i["weight"];
        source = i["source"];
        if(i["tier"] != NULL) tier = i["tier"];
        
        break;
      }
    }
  }

  what_class_is_it = "Wand";
}
int Wand::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  return -1;
}



