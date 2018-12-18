
#include "Item.h"
using json = nlohmann::json;

Item::Item() : name(" ") { // : name(name) first initialise with reference
  equipped = false;
  count = 0;
  num_equipped = 0;
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
int Item::Price_Parse(const nlohmann::basic_json<> &j, int i) {
  int cost_i = 0;
  auto find_value = j["item"][i].find("value");
  if (find_value != j["item"][i].end()) { /* */
    std::__cxx11::string value_ = j["item"][i]["value"];
    std::__cxx11::string cost_;
    int multiplier = 1;
    int s = 0;
    while (((int) value_[s] < (int) 'A' || (int) value_[s] > (int) 'z') && s < value_.length()) {
      cost_ += value_[s];
      s++;
    }
    while (true) {
      if (value_[s] == 's') {
        multiplier = 10;
        break;
      } else if (value_[s] == 'g') {
        multiplier = 100;
        break;
      } else if (value_[s] == 'p') {
        multiplier = 1000;
        break;
      } else if (s < value_.length() - 1) s++;
      else break;
    }
    i = stoi(cost_); //cost_
    i *= multiplier;
    std::cout << "price = " << i << "\n";
    return i;
  }
  return i;
}
void Item::equip(int a) {
  if (abs(a) > count) {
    if (a > 0) a = count;
    else a = (-1) * count;
  }
  num_equipped += a;
  equipped = (num_equipped == count);
}
void Item::Attune() {
  Attuned = !Attuned;
}
bool Item::Is_Attuned() {
  return Attuned;
}
bool Item::is_equipped() { return equipped; }
std::string Item::What_class() {
  return what_class_is_it;
}
std::vector<std::string> Item::Entries_Parse(const nlohmann::basic_json<> &j) {
  std::cout << "Control reach Item::Entries_Parse 0\n";
  try {
    if (j.find("entries") != j.end()) {
      //std::cout << "Control reach Item::Entries_Parse 1\n";
      //std::cout << "j[\"item\"][i][\"entries\"].size() =" << j["entries"].size() <<"\n";
      for (int k = 0; k < j["entries"].size(); k++) {
        if (j["entries"][k].size() == 1) {
          //std::cout << "Control reach Item::Entries_Parse /string.\n";
          auto entries_ = j["entries"][k];
          entries.push_back(entries_);
        } else if (!j["entries"][k].empty()) {
          Entries_Parse_second_level(j["entries"][k]);
        } else {
          //std::cout << "Control reach Item::Entries_Parse 11\n";
        }
      }
    }
  }
  catch (json::type_error &e) {
    // output exception information
    std::cout << "message: " << e.what() << '\n'
              << "exception id: " << e.id << std::endl;
  }
  return entries;
}
void Item::Entries_Parse_second_level(const nlohmann::basic_json<> &j) {
  if (j.find("name") != j.end()) {
    std::string nameAddOn = j["name"];
    entries.push_back(nameAddOn);
  }
  std::cout << j.size() << std::endl;
  Entries_Parse_second_level_entries_entries(j);
  std::cout << "Control reachItem::Entries_Parse_ 5\n";
  Entries_Parse_second_level_entries_items(j);
}
int Item::Entries_Parse_second_level_entries_entries(const nlohmann::basic_json<> &j) {
  if (j.find("entries") == j.end()) { return 0; }
  for (int f = 0; f < j["entries"].size(); f++) {
    std::cout << "Control reach Item::Entries_Parse 3_0\n";
    if (j["entries"][f].size() == 1) {
      std::cout << "Control reach Item::Entries_Parse 3_0/string.\n";
      auto entries_ = j["entries"][f];
      entries.push_back(entries_);
    } else if (!j["entries"][f].empty()) {//type
      Entries_Parse_third_level(j["entries"][f]);
    }
  }
  return 0;
}
int Item::Entries_Parse_second_level_entries_items(const nlohmann::basic_json<> &j) {
  if (j.find("items") == j.end()) { return 0; }
  for (int f = 0; f < j["items"].size(); f++) {
    if (j["items"][f].size() == 1) {
      std::cout << "Control reach Item::Entries_Parse 3_0/string.\n";
      auto entries_ = j["items"][f];
      entries.push_back(entries_);
    } else if (!j["items"][f].empty()) {//type
      Entries_Parse_forth_level(j["items"][f]);
    }
  }
  return 0;
}
int Item::Entries_Parse_third_level(const nlohmann::basic_json<> &j) {
  std::cout << "Control reach Item::Entries_Parse 3_1\n";
  if (j.find("entries") == j.end()) { return 0; }
  if (j.find("name") != j.end()) {
    //std::cout << "Control reach Item::Entries_Parse 4\n";
    std::string nameAddOn = j["name"];
    entries.push_back(nameAddOn);
  }
  for (int a = 0; a < j["entries"].size(); a++) {
    auto entries_ = j["entries"][a].get<std::string>();
    entries.push_back(entries_);
  }
  if (j.find("items") == j.end()) { return 0; }
  for (int a = 0; a < j["items"].size(); a++) {
    auto entries_ = j["items"][a].get<std::string>();
    entries.push_back(entries_);
  }
  return 0;
}
int Item::Entries_Parse_forth_level(const nlohmann::basic_json<> &j) {
  std::cout << "Control reach Item::Entries_Parse 7\n";
  if (j.size() == 1) {
    auto entries_ = j;
    entries.push_back(entries_);
  }
  if (j.find("name") != j.end()) {
    std::string nameAddOn = j["name"];
    entries.push_back(nameAddOn);
  }
  if (j.find("entries") != j.end()) {
    for (int a = 0; a < j["entries"].size(); a++) {
      auto entries_ = j["entries"][a].get<std::string>();
      entries.push_back(entries_);
    }
  }
  if (j.find("items") != j.end()) {
    for (int a = 0; a < j["items"].size(); a++) {
      auto entries_ = j["items"][a].get<std::string>();
      entries.push_back(entries_);
    }
  }
  return 0;
}
void Item::Show_Entries() {
  for (int IndexOutput = 0; IndexOutput < entries.size(); IndexOutput++) {
    std::cout << entries[IndexOutput] << "\n";
  }
}
std::vector<std::string> Item::Get_Entries() {
  return entries;
}
std::vector<std::string> Item::AttachedSpells_Parse(const nlohmann::basic_json<> &j) {
  try {
    if (!j["attachedSpells"].empty()) {
      for (int k = 0; j["attachedSpells"][k].empty(); k++) {
        attachedSpells.push_back(j["attachedSpells"][k]);
      }
    }
  }
  catch (json::type_error &e) {
    // output exception information
    std::cout << "message: " << e.what() << '\n'
              << "exception id: " << e.id << std::endl;
  }
  return attachedSpells;
}

Melee_Weapon::Melee_Weapon() = default;
Melee_Weapon::Melee_Weapon(std::string &name_) {
  set(name_, 1);
}
Melee_Weapon::Melee_Weapon(std::string &name_, int count_) {
  num_of_dices1 = 0;
  damage_dice1 = 0;
  num_of_dices2 = 0;
  damage_dice2 = 0;
  type_of_elemental_damage = 0;
  set(name_, count_);
}
/*Weapon::Weapon(std::string &name_, int count_, int num_of_dices_, int damage_dice_, int type_of_elemental_damage_) {
  set(name_, count_, num_of_dices_, damage_dice_, type_of_elemental_damage_);
}*/
Melee_Weapon::~Melee_Weapon() = default;
void Melee_Weapon::set(std::string &name_, int count_) {
  std::cout << "Item::Melee_Weapon set 0\n";
  Existing_Items E_I;
  name = " ";
  equipped = false;
  for (int i = 0; i < kWeapon_NUM; i++) {
    if (E_I.Weapon_s[i] == name_) {
      name = name_;
      cost = E_I.Weapon_i[i][0];
      num_of_dices1 = E_I.Weapon_i[i][1];
      damage_dice1 = E_I.Weapon_i[i][2];
      weight = E_I.Weapon_i[i][3];
      type_of_elemental_damage = E_I.Weapon_i[i][4];
      stackable = false;
      break;
    }
  }
  std::cout << "Item::Melee_Weapon set 1\n";
  count = count_;
  if (name == " ") {
    source = "Default";
    std::ifstream inputJson;
    inputJson
        .open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
    json j = json::parse(inputJson);
    try {
      std::cout << "Item::Melee_Weapon set 10\n";
      for (int i = 0; !j["item"][i]["name"].empty(); i++) {
        if (!j["item"][i]["type"].empty()) {//if(..) to be deleted
          if (name_ == j["item"][i]["name"]) {
            name = name_;
            auto jsonEndPointer = j["item"][i].end();
            if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
            if (j["item"][i].find("weight") != jsonEndPointer) {
              std::string weight_ = j["item"][i]["weight"];
              weight = std::stoi(weight_);
            }
            source = j["item"][i]["source"];
            if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
            entries = Entries_Parse(j["item"][i]);
            if (j["item"][i].find("reqAttune") != jsonEndPointer) {
              if (j["item"][i]["reqAttune"] != true) {

              } else reqAttune = j["item"][i]["reqAttune"];
            }
            cost = Price_Parse(j, i);
            break;
          }
        }
      }
    }
    catch (json::type_error &e) {
      std::cout << "messege: " << e.what() << '\n'
                << "exception id: " << e.id << std::endl;
    }
  }
  what_class_is_it = "Weapon";
}
int Melee_Weapon::show() {
  Existing_Items E_I;
  std::cout << name << std::endl;
  std::cout << "Damage " << num_of_dices1 << "d" << damage_dice1 <<
            " element: " << E_I.elements[type_of_elemental_damage] << std::endl;
  return damage_dice1;
}
int Melee_Weapon::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  else if (a == 3) { return num_of_dices1; }
  else if (a == 4) { return damage_dice1; }
  else if (a == 5) { return num_of_dices2; }
  else if (a == 6) { return damage_dice2; }
  else if (a == 7) { return type_of_elemental_damage; }
  else if (a == 8) { return num_equipped; }
  return -1;
}

Ranged_Weapon::Ranged_Weapon() = default;
Ranged_Weapon::Ranged_Weapon(std::string &name_) {
  set(name_, 1);
}
Ranged_Weapon::Ranged_Weapon(std::string &name_, int count_) {
  num_of_dices1 = 0;
  damage_dice1 = 0;
  num_of_dices2 = 0;
  damage_dice2 = 0;
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
  equipped = false;
  for (int i = 0; i < kRanged_Weapon_NUM; i++) {
    if (E_I.Ranged_Weapon_s[i] == name_) {
      name = name_;
      cost = E_I.Ranged_Weapon_i[i][0];
      num_of_dices1 = E_I.Ranged_Weapon_i[i][1];
      damage_dice1 = E_I.Ranged_Weapon_i[i][2];
      weight = E_I.Ranged_Weapon_i[i][3];
      type_of_elemental_damage = E_I.Ranged_Weapon_i[i][4];
      aiming_range = E_I.Ranged_Weapon_i[i][5];
      max_range = E_I.Ranged_Weapon_i[i][6];
      stackable = false;
      break;
    }
  }
  count = count_;
  if (name == " ") {
    source = "Default";
    std::ifstream inputJson;
    inputJson
        .open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
    json j = json::parse(inputJson);
    try {
      for (int i = 0; !j["item"][i]["name"].empty(); i++) {
        if (!j["item"][i]["type"].empty()) {
          if (name_ == j["item"][i]["name"]) {
            name = name_;
            auto jsonEndPointer = j["item"][i].end();
            if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
            if (j["item"][i].find("weight") != jsonEndPointer) {
              std::string weight_ = j["item"][i]["weight"];
              weight = std::stoi(weight_);
            }
            source = j["item"][i]["source"];
            if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
            entries = Entries_Parse(j["item"][i]);
            if (j["item"][i].find("reqAttune") != jsonEndPointer) {
              if (j["item"][i]["reqAttune"] != true) {

              } else reqAttune = j["item"][i]["reqAttune"];
            }
            cost = Price_Parse(j, i);
            break;
          }
        }
      }
    }
    catch (json::type_error &e) {
      std::cout << "messege: " << e.what() << '\n'
                << "exception id: " << e.id << std::endl;
    }
  }
  what_class_is_it = "Ranged_Weapon";
}
int Ranged_Weapon::show() {
  Existing_Items E_I;
  std::cout << name << std::endl;
  std::cout << "Damage " << num_of_dices1 << "d" << damage_dice1 <<
            " element:" << E_I.elements[type_of_elemental_damage] << std::endl;
  return damage_dice1;
}
int Ranged_Weapon::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  else if (a == 3) { return num_of_dices1; }
  else if (a == 4) { return damage_dice1; }
  else if (a == 5) { return num_of_dices2; }
  else if (a == 6) { return damage_dice2; }
  else if (a == 7) { return type_of_elemental_damage; }
  else if (a == 8) { return aiming_range; }
  else if (a == 9) { return max_range; }
  else if (a == 10) { return num_equipped; }
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
  equipped = false;
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
  if (name == " ") {
    source = "Default";
    std::ifstream inputJson;
    inputJson
        .open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
    json j = json::parse(inputJson);
    try {
      for (int i = 0; !j["item"][i]["name"].empty(); i++) {
        if (!j["item"][i]["type"].empty()) {
          if (name_ == j["item"][i]["name"]) {
            name = name_;
            auto jsonEndPointer = j["item"][i].end();
            if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
            if (j["item"][i].find("weight") != jsonEndPointer) {
              std::string weight_ = j["item"][i]["weight"];
              weight = std::stoi(weight_);
            }
            source = j["item"][i]["source"];
            if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
            entries = Entries_Parse(j["item"][i]);
            if (j["item"][i].find("reqAttune") != jsonEndPointer) {
              if (j["item"][i]["reqAttune"] != true) {

              } else reqAttune = j["item"][i]["reqAttune"];
            }
            cost = Price_Parse(j, i);
            break;
          }
        }
      }
    }
    catch (json::type_error &e) {
      std::cout << "messege: " << e.what() << '\n'
                << "exception id: " << e.id << std::endl;
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
  //std::cout << "Control reach Item::Goods::set 0/0\n";
  name = " ";
  equipped = false;
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
  //std::cout << "Control reach Item::Goods::set 0\n";
  if (name == " ") {
    source = "Default";
    std::ifstream inputJson;
    inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
    json j = json::parse(inputJson);
    try {
      for (int i = 0; !j["item"][i]["name"].empty(); i++) {
        if (!j["item"][i]["type"].empty()) {
          if (name_ == j["item"][i]["name"]) {
            //std::cout << "Control reach Item::Goods::set 2\n";
            name = name_;
            auto jsonEndPointer = j["item"][i].end();
            if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
            if (j["item"][i].find("weight") != jsonEndPointer) {
              std::string weight_ = j["item"][i]["weight"];
              //std::cout << "Control reach I}tem::Goods::set 3\n";
              weight = std::stoi(weight_);
            }
            source = j["item"][i]["source"];
            //std::cout << "Control reach Item::Goods::set 4\n";
            if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
            //std::cout << "Control reach Item::Goods::set 5\n";
            entries = Entries_Parse(j["item"][i]);
            //std::cout << "Control reach Item::Goods::set 6\n";
            cost = Price_Parse(j, i);
            break;
          }
        }
      }
    }
    catch (json::type_error &e) {
      std::cout << "messege: " << e.what() << '\n'
                << "exception id: " << e.id << std::endl;
    }
    //std::cout << "Control reach Item::Goods::set 1\n";

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
  else if (a == 4) { return num_equipped; }
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
  equipped = false;
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
  if (name == " ") {
    source = "Default";
    std::ifstream inputJson;
    inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
    json j = json::parse(inputJson);
    try {
      for (int i = 0; !j["item"][i]["name"].empty(); i++) {
        if (!j["item"][i]["type"].empty()) {
          if (name_ == j["item"][i]["name"]) {
            name = name_;
            auto jsonEndPointer = j["item"][i].end();
            if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
            if (j["item"][i].find("weight") != jsonEndPointer) {
              std::string weight_ = j["item"][i]["weight"];
              weight = std::stoi(weight_);
            }
            source = j["item"][i]["source"];
            if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
            entries = Entries_Parse(j["item"][i]);
            if (j["item"][i].find("reqAttune") != jsonEndPointer) {
              if (j["item"][i]["reqAttune"] != true) {

              } else reqAttune = j["item"][i]["reqAttune"];
            }
            cost = Price_Parse(j, i);
            break;
          }
        }
      }
    }
    catch (json::type_error &e) {
      std::cout << "messege: " << e.what() << '\n'
                << "exception id: " << e.id << std::endl;
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
  else if (a == 5) { return num_equipped; }
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
  count = count_;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  try {
    for (int i = 0; !j["item"][i]["name"].empty(); i++) {
      if (!j["item"][i]["type"].empty()) {
        if (name_ == j["item"][i]["name"]) {
          name = name_;
          auto jsonEndPointer = j["item"][i].end();
          if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
          if (j["item"][i].find("weight") != jsonEndPointer) {
            std::string weight_ = j["item"][i]["weight"];
            weight = std::stoi(weight_);
          }
          source = j["item"][i]["source"];
          if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
          entries = Entries_Parse(j["item"][i]);
          cost = Price_Parse(j, i);
          break;
        }
      }
    }
  }
  catch (json::type_error &e) {
    std::cout << "messege: " << e.what() << '\n'
              << "exception id: " << e.id << std::endl;
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
  count = count_;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  try {
    for (int i = 0; !j["item"][i]["name"].empty(); i++) {
      if (!j["item"][i]["type"].empty()) {
        if (name_ == j["item"][i]["name"]) {
          name = name_;
          auto jsonEndPointer = j["item"][i].end();
          if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
          if (j["item"][i].find("weight") != jsonEndPointer) {
            std::string weight_ = j["item"][i]["weight"];
            weight = std::stoi(weight_);
          }
          source = j["item"][i]["source"];
          if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
          entries = Entries_Parse(j["item"][i]);
          if (!j["item"][i]["speed"].empty()) speed = j["item"][i]["speed"];
          if (!j["item"][i]["carryingcapacity"].empty()) carryingcapacity = j["item"][i]["carryingcapacity"];
          if (!j["item"][i]["crew"].empty()) crew = j["item"][i]["crew"];
          if (!j["item"][i]["vehAc"].empty()) vehAc = j["item"][i]["vehAc"];
          if (!j["item"][i]["vehHp"].empty()) vehHp = j["item"][i]["vehHp"];
          if (!j["item"][i]["vehDmgThresh"].empty()) vehDmgThresh = j["item"][i]["vehDmgThresh"];
          cost = Price_Parse(j, i);
          break;
        }
      }
    }
  }
  catch (json::type_error &e) {
    std::cout << "messege: " << e.what() << '\n'
              << "exception id: " << e.id << std::endl;
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
  count = count_;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  try {
    for (int i = 0; !j["item"][i]["name"].empty(); i++) {
      if (!j["item"][i]["type"].empty()) {
        if (name_ == j["item"][i]["name"]) {
          name = name_;
          auto jsonEndPointer = j["item"][i].end();
          if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
          if (j["item"][i].find("weight") != jsonEndPointer) {
            std::string weight_ = j["item"][i]["weight"];
            weight = std::stoi(weight_);
          }
          source = j["item"][i]["source"];
          if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
          entries = Entries_Parse(j["item"][i]);
          cost = Price_Parse(j, i);
          break;
        }
      }
    }
  }
  catch (json::type_error &e) {
    std::cout << "messege: " << e.what() << '\n'
              << "exception id: " << e.id << std::endl;
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
  count = count_;
  Existing_Items E_I;
  name = " ";
  equipped = false;
  for (int i = 0; i < kSpellCastingFocus_NUM; i++) {
    if (E_I.SpellCastingFocus_s[i] == name_) {
      name = name_;
      cost = E_I.SpellCastingFocus_i[i][0];
      weight = E_I.SpellCastingFocus_i[i][1];
      if (E_I.SpellCastingFocus_b[i][0]) arcane_focus = true;
      if (E_I.SpellCastingFocus_b[i][1]) druidic_focus = true;
      if (E_I.SpellCastingFocus_b[i][2]) holy_symbol = true;
      break;
    }
  }
  count = count_;
  source = "Default";
  if (name == " ") {
    std::ifstream inputJson;
    inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
    json j = json::parse(inputJson);
    try {
      for (int i = 0; !j["item"][i]["name"].empty(); i++) {
        if (!j["item"][i]["technology"].empty()) {
          if (j["item"][i]["technology"] == "Staff") {
            arcane_focus = true;
            druidic_focus = false;
            holy_symbol = false;
            weight = E_I.SpellCastingFocus_i[4][1];// technology @Staff
            auto jsonEndPointer = j["item"][i].end();
            if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
            if (j["item"][i].find("weight") != jsonEndPointer) {
              std::string weight_ = j["item"][i]["weight"];
              weight = std::stoi(weight_);
            }
            if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
            entries = Entries_Parse(j["item"][i]);
            if (j["item"][i].find("reqAttune") != jsonEndPointer) {
              if (j["item"][i]["reqAttune"] != true) {

              } else reqAttune = j["item"][i]["reqAttune"];
            }
            cost = Price_Parse(j, i);
            break;
          }
        } else if (!j["item"][i]["type"].empty()) {
          if (name_ == j["item"][i]["name"]) {
            name = name_;
            auto jsonEndPointer = j["item"][i].end();
            if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
            if (j["item"][i].find("weight") != jsonEndPointer) {
              std::string weight_ = j["item"][i]["weight"];
              weight = std::stoi(weight_);
            }
            source = j["item"][i]["source"];
            if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
            entries = Entries_Parse(j["item"][i]);
            if (!j["item"][i]["scfType"].empty()) {
              for (int m = 0; m < kSpellCastingFocus_Types; m++) {
                if (E_I.SpellCastingFocus_types[m] == j["item"][i]["scfType"]) {
                  scfType = m;
                  break;
                }
              }
            }

            if (j["item"][i].find("reqAttune") != jsonEndPointer) {
              if (j["item"][i]["reqAttune"] != true) {

              } else reqAttune = j["item"][i]["reqAttune"];
            }
            cost = Price_Parse(j, i);
            break;
          }
        }
      }
    }
    catch (json::type_error &e) {
      std::cout << "messege: " << e.what() << '\n'
                << "exception id: " << e.id << std::endl;
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
  count = count_;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  try {
    for (int i = 0; !j["item"][i]["name"].empty(); i++) {
      if (!j["item"][i]["type"].empty()) {
        if (name_ == j["item"][i]["name"]) {
          name = name_;
          auto jsonEndPointer = j["item"][i].end();
          if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
          if (j["item"][i].find("weight") != jsonEndPointer) {
            std::string weight_ = j["item"][i]["weight"];
            weight = std::stoi(weight_);
          }
          source = j["item"][i]["source"];
          if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
          entries = Entries_Parse(j["item"][i]);
          if (!j["item"][i]["ac"].empty()) ac = j["item"][i]["ac"];
          if (j["item"][i].find("reqAttune") != jsonEndPointer) {
            if (j["item"][i]["reqAttune"] != true) {

            } else reqAttune = j["item"][i]["reqAttune"];
          }
          cost = Price_Parse(j, i);
          break;
        }
      }
    }
  }
  catch (json::type_error &e) {
    std::cout << "messege: " << e.what() << '\n'
              << "exception id: " << e.id << std::endl;
  }
  if (source == "Default") {
    Existing_Items E_I;
    for (int i = 0; i < kShield_NUM; i++) {
      if (name_ == E_I.Shield_s[i]) {
        name = name_;
        cost = E_I.Shield_i[i][0];
        weight = E_I.Shield_i[i][1];
        ac = E_I.Shield_i[i][2];
        break;
      }
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
  count = count_;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  try {
    for (int i = 0; !j["item"][i]["name"].empty(); i++) {
      if (!j["item"][i]["type"].empty()) {
        if (name_ == j["item"][i]["name"]) {
          name = name_;
          auto jsonEndPointer = j["item"][i].end();
          if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
          if (j["item"][i].find("weight") != jsonEndPointer) {
            std::string weight_ = j["item"][i]["weight"];
            weight = std::stoi(weight_);
          }
          source = j["item"][i]["source"];
          if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
          entries = Entries_Parse(j["item"][i]);
          cost = Price_Parse(j, i);
          break;
        }
      }
    }
  }
  catch (json::type_error &e) {
    std::cout << "messege: " << e.what() << '\n'
              << "exception id: " << e.id << std::endl;
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
  Existing_Items E_I;
  weight = 0;
  count = count_;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  try {
    for (int i = 0; !j["item"][i]["name"].empty(); i++) {
      if (!j["item"][i]["type"].empty()) {
        if (name_ == j["item"][i]["name"]) {
          name = name_;
          auto jsonEndPointer = j["item"][i].end();
          if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
          if (j["item"][i].find("weight") != jsonEndPointer) {
            std::string weight_ = j["item"][i]["weight"];
            weight = std::stoi(weight_);
          }
          source = j["item"][i]["source"];
          if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
          entries = Entries_Parse(j["item"][i]);
          if (!j["item"][i]["resist"].empty()) {
            for (int k = 1; k < kElements_Num; k++) {
              if (E_I.elements[k] == j["item"][i]["resist"]) {
                resistance_type = k - 1;// because "first" type is non-elemental damage
                break;
              }
            }
          }
          attachedSpells = AttachedSpells_Parse(j["item"][i]);
          if (!j["item"][i]["charges"].empty()) charges = !j["item"][i]["charges"];
          if (j["item"][i].find("reqAttune") != jsonEndPointer) {
            if (j["item"][i]["reqAttune"] != true) {

            } else reqAttune = j["item"][i]["reqAttune"];
          }
          cost = Price_Parse(j, i);
          break;
        }
      }
    }
  }
  catch (json::type_error &e) {
    std::cout << "messege: " << e.what() << '\n'
              << "exception id: " << e.id << std::endl;
  }
  if (source == "Default") {
    Existing_Items E_I;
    for (int i = 0; i < kGoods_NUM; i++) {
      if (name_ == E_I.Ring_s[i]) {
        name = name_;
        cost = E_I.Ring_i[i][0];
        weight = E_I.Ring_i[i][1];
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
  count = count_;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  try {
    for (int i = 0; !j["item"][i]["name"].empty(); i++) {
      if (!j["item"][i]["type"].empty()) {
        if (name_ == j["item"][i]["name"]) {
          name = name_;
          auto jsonEndPointer = j["item"][i].end();
          if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
          if (j["item"][i].find("weight") != jsonEndPointer) {
            std::string weight_ = j["item"][i]["weight"];
            weight = std::stoi(weight_);
          }
          source = j["item"][i]["source"];
          if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
          entries = Entries_Parse(j["item"][i]);
          cost = Price_Parse(j, i);
          break;
        }
      }
    }
  }
  catch (json::type_error &e) {
    std::cout << "messege: " << e.what() << '\n'
              << "exception id: " << e.id << std::endl;
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
  count = count_;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  try {
    for (int i = 0; !j["item"][i]["name"].empty(); i++) {
      if (!j["item"][i]["type"].empty()) {
        if (name_ == j["item"][i]["name"]) {
          name = name_;
          auto jsonEndPointer = j["item"][i].end();
          if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
          if (j["item"][i].find("weight") != jsonEndPointer) {
            std::string weight_ = j["item"][i]["weight"];
            weight = std::stoi(weight_);
          }
          source = j["item"][i]["source"];
          if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
          age = j["item"][i]["age"];
          entries = Entries_Parse(j["item"][i]);
          cost = Price_Parse(j, i);
          break;
        }
      }
    }
  }
  catch (json::type_error &e) {
    std::cout << "messege: " << e.what() << '\n'
              << "exception id: " << e.id << std::endl;
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
  count = count_;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  try {
    for (int i = 0; !j["item"][i]["name"].empty(); i++) {
      if (!j["item"][i]["type"].empty()) {
        if (name_ == j["item"][i]["name"]) {
          name = name_;
          auto jsonEndPointer = j["item"][i].end();
          if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
          if (j["item"][i].find("weight") != jsonEndPointer) {
            std::string weight_ = j["item"][i]["weight"];
            weight = std::stoi(weight_);
          }
          source = j["item"][i]["source"];
          if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
          entries = Entries_Parse(j["item"][i]);
          attachedSpells = AttachedSpells_Parse(j["item"][i]);
          cost = Price_Parse(j, i);
          break;
        }
      }
    }
  }
  catch (json::type_error &e) {
    std::cout << "messege: " << e.what() << '\n'
              << "exception id: " << e.id << std::endl;
  }
  if (source == "Default") {
    Existing_Items E_I;
    for (int i = 0; i < kPotion_NUM; i++) {
      if (name_ == E_I.Potion_s[i]) {
        name = name_;
        cost = E_I.Potion_i[i][0];
        weight = E_I.Potion_i[i][1];
        healing = E_I.Potion_i[i][2];
        num_of_healing_dices = E_I.Potion_i[i][3];
        healing_dice = E_I.Potion_i[i][4];
        break;
      }
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
  count = count_;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  try {
    for (int i = 0; !j["item"][i]["name"].empty(); i++) {
      if (!j["item"][i]["type"].empty()) {
        if (name_ == j["item"][i]["name"]) {
          name = name_;
          auto jsonEndPointer = j["item"][i].end();
          if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
          if (j["item"][i].value("weight", "no") != "no") {
            std::string weight_ = j["item"][i]["weight"];
            weight = std::stoi(weight_);
          }
          source = j["item"][i]["source"];
          if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
          //entries = Entries_Parse(j["item"][i]);
          if (!j["item"][i]["speed"].empty()) speed = j["item"][i]["speed"];
          if (!j["item"][i]["carryingcapacity"].empty()) carryingcapacity = j["item"][i]["carryingcapacity"];
          cost = Price_Parse(j, i);
          break;
        }
      }
    }
  }
  catch (json::type_error &e) {
    std::cout << "messege: " << e.what() << '\n'
              << "exception id: " << e.id << std::endl;
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
  count = count_;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  try {
    for (int i = 0; !j["item"][i]["name"].empty(); i++) {
      if (!j["item"][i]["type"].empty()) {
        if (name_ == j["item"][i]["name"]) {
          name = name_;
          auto jsonEndPointer = j["item"][i].end();
          if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
          if (j["item"][i].find("weight") != jsonEndPointer) {
            std::string weight_ = j["item"][i]["weight"];
            weight = std::stoi(weight_);
          }
          source = j["item"][i]["source"];
          if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
          entries = Entries_Parse(j["item"][i]);
          if (!j["item"][i]["speed"].empty()) speed = j["item"][i]["speed"];
          if (!j["item"][i]["carryingcapacity"].empty()) carryingcapacity = j["item"][i]["carryingcapacity"];
          cost = Price_Parse(j, i);
          break;
        }
      }
    }
  }
  catch (json::type_error &e) {
    std::cout << "messege: " << e.what() << '\n'
              << "exception id: " << e.id << std::endl;
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
  count = count_;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  try {
    for (int i = 0; !j["item"][i]["name"].empty(); i++) {
      if (!j["item"][i]["type"].empty()) {
        if (name_ == j["item"][i]["name"]) {
          name = name_;
          auto jsonEndPointer = j["item"][i].end();
          if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
          if (j["item"][i].find("weight") != jsonEndPointer) {
            std::string weight_ = j["item"][i]["weight"];
            source = std::stoi(weight_);
          }
          if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
          if (!j["item"][i]["entries"].empty()) entries = Entries_Parse(j["item"][i]);
          if (!j["item"][i]["cost"].empty()) cost = Price_Parse(j, i);
          break;
        }
      }
    }
  }
  catch (json::type_error &e) {
    std::cout << "messege: " << e.what() << '\n'
              << "exception id: " << e.id << std::endl;
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
  count = count_;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  try {
    for (int i = 0; !j["item"][i]["name"].empty(); i++) {
      if (!j["item"][i]["type"].empty()) {
        if (name_ == j["item"][i]["name"]) {
          name = name_;
          auto jsonEndPointer = j["item"][i].end();
          if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
          weight = 0;
          source = j["item"][i]["source"];
          if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
          std::cout << "Control Reach Item::Gaming Set::set 0\n";
          //entries = Entries_Parse(j["item"][i]);
          std::cout << "Control Reach Item::Gaming Set::set 1\n";
          cost = Price_Parse(j, i);
          std::cout << "Control Reach Item::Gaming Set::set 2\n";
          break;
        }
      }
    }
  }
  catch (json::type_error &e) {
    std::cout << "messege: " << e.what() << '\n'
              << "exception id: " << e.id << std::endl;
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
  count = count_;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  try {
    for (int i = 0; !j["item"][i]["name"].empty(); i++) {
      if (!j["item"][i]["type"].empty()) {
        if (name_ == j["item"][i]["name"]) {
          name = name_;
          auto jsonEndPointer = j["item"][i].end();
          if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
          if (j["item"][i].find("weight") != jsonEndPointer) {
            std::string weight_ = j["item"][i]["weight"];
            weight = std::stoi(weight_);
          }
          source = j["item"][i]["source"];
          if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
          entries = Entries_Parse(j["item"][i]);
          if (j["item"][i].find("reqAttune") != jsonEndPointer) {
            if (j["item"][i]["reqAttune"] != true) {

            } else reqAttune = j["item"][i]["reqAttune"];
          }
          cost = Price_Parse(j, i);
          break;
        }
      }
    }
  }
  catch (json::type_error &e) {
    std::cout << "messege: " << e.what() << '\n'
              << "exception id: " << e.id << std::endl;
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
Tools::~Tools() = default; //TODO: AditionalEntries
void Tools::set(std::string &name_, int count_) {
  weight = 0;
  count = count_;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  try {
    for (int i = 0; !j["item"][i]["name"].empty(); i++) {
      if (!j["item"][i]["type"].empty()) {
        if (name_ == j["item"][i]["name"]) {
          name = name_;
          auto jsonEndPointer = j["item"][i].end();
          if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
          if (j["item"][i].find("weight") != jsonEndPointer) {
            std::string weight_ = j["item"][i]["weight"];
            weight = std::stoi(weight_);
          }
          source = j["item"][i]["source"];
          if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
          entries = Entries_Parse(j["item"][i]);
          cost = Price_Parse(j, i);
          break;
        }
      }
    }
  }
  catch (json::type_error &e) {
    std::cout << "messege: " << e.what() << '\n'
              << "exception id: " << e.id << std::endl;
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
  count = count_;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  try {
    for (int i = 0; !j["item"][i]["name"].empty(); i++) {
      if (!j["item"][i]["type"].empty()) {
        if (name_ == j["item"][i]["name"]) {
          name = name_;
          auto jsonEndPointer = j["item"][i].end();
          if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
          if (j["item"][i].find("weight") != jsonEndPointer) {
            std::string weight_ = j["item"][i]["weight"];
            weight = std::stoi(weight_);
          }
          source = j["item"][i]["source"];
          if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
          entries = Entries_Parse(j["item"][i]);
          attachedSpells = AttachedSpells_Parse(j["item"][i]);
          if (j["item"][i].find("reqAttune") != jsonEndPointer) {
            if (j["item"][i]["reqAttune"] != true) {

            } else reqAttune = j["item"][i]["reqAttune"];
          }
          cost = Price_Parse(j, i);
          break;
        }
      }
    }

  }
  catch (json::type_error &e) {
    std::cout << "messege: " << e.what() << '\n'
              << "exception id: " << e.id << std::endl;
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
  count = count_;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  try {
    for (int i = 0; !j["item"][i]["name"].empty(); i++) {
      if (!j["item"][i]["type"].empty()) {
        if (name_ == j["item"][i]["name"]) {
          name = name_;
          auto jsonEndPointer = j["item"][i].end();
          if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
          if (j["item"][i].find("weight") != jsonEndPointer) {
            std::string weight_ = j["item"][i]["weight"];
            weight = std::stoi(weight_);
          }
          source = j["item"][i]["source"];
          if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
          entries = Entries_Parse(j["item"][i]);
          attachedSpells = AttachedSpells_Parse(j["item"][i]);
          cost = Price_Parse(j, i);
          break;
        }
      }
    }
  }
  catch (json::type_error &e) {
    std::cout << "messege: " << e.what() << '\n'
              << "exception id: " << e.id << std::endl;
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
  count = count_;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  try {
    for (int i = 0; !j["item"][i]["name"].empty(); i++) {
      if (j["item"][i]["type"] != NULL) {
        if (name_ == j["item"][i]["name"]) {
          name = name_;
          auto jsonEndPointer = j["item"][i].end();
          if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
          if (j["item"][i].find("weight") != jsonEndPointer) {
            std::string weight_ = j["item"][i]["weight"];
            weight = std::stoi(weight_);
          }
          source = j["item"][i]["source"];
          if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
          entries = Entries_Parse(j["item"][i]);
          if (j["item"][i].find("reqAttune") != jsonEndPointer) {
            if (j["item"][i]["reqAttune"] != true) {

            } else reqAttune = j["item"][i]["reqAttune"];
          }
          attachedSpells = AttachedSpells_Parse(j["item"][i]);
          if (!j["item"][i]["charges"].empty()) charges = !j["item"][i]["charges"];
          cost = Price_Parse(j, i);
          break;
        }
      }
    }

  }
  catch (json::type_error &e) {
    std::cout << "messege: " << e.what() << '\n'
              << "exception id: " << e.id << std::endl;
  }

  what_class_is_it = "Wand";
}
int Wand::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  return -1;
}

OTH::OTH() = default;
OTH::OTH(std::string &name_) {
  set(name_, 1);
}
OTH::OTH(std::string &name_, int count_) {
  set(name_, count_);
}
OTH::~OTH() = default;
void OTH::set(std::string &name_, int count_) {
  weight = 0;
  count = count_;
  source = "Default";
  std::ifstream inputJson;
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/items/items.json");
  json j = json::parse(inputJson);
  try {
    for (int i = 0; !j["item"][i]["name"].empty(); i++) {
      if (j["item"][i]["type"] != NULL) {
        if (name_ == j["item"][i]["name"]) {
          name = name_;
          auto jsonEndPointer = j["item"][i].end();
          if (j["item"][i].find("rarity") != jsonEndPointer) rarity = j["item"][i]["rarity"];
          if (j["item"][i].find("weight") != jsonEndPointer) {
            std::string weight_ = j["item"][i]["weight"];
            weight = std::stoi(weight_);
          }
          source = j["item"][i]["source"];
          if (j["item"][i].find("tier") != jsonEndPointer) tier = j["item"][i]["tier"];
          entries = Entries_Parse(j["item"][i]);
          if (j["item"][i].find("reqAttune") != jsonEndPointer) {
            if (j["item"][i]["reqAttune"] != true) {

            } else reqAttune = j["item"][i]["reqAttune"];
          }
          attachedSpells = AttachedSpells_Parse(j["item"][i]);
          if (!j["item"][i]["charges"].empty()) charges = !j["item"][i]["charges"];
          cost = Price_Parse(j, i);
          break;
        }
      }
    }
  }
  catch (json::type_error &e) {
    std::cout << "messege: " << e.what() << '\n'
              << "exception id: " << e.id << std::endl;
  }
  what_class_is_it = "OTH";
}
int OTH::get(int a) {
  if (a == 0) { return cost; }
  else if (a == 1) { return weight; }
  else if (a == 2) { return count; }
  return -1;
}



