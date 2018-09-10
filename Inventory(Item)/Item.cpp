
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

const int kWeapon_NUM = 29;
const int kR_Weapon_NUM = 9;
const int kFood_NUM = 9;
const int kArmor_NUM = 13;
const int kUsable_NUM = 29;

struct Existing_Items{
  std::string Weapon_s[kWeapon_NUM] = {"Club","Dagger","Greatclub","Handaxe","Javelin","Light_hammer",
                                       "Mace","Quarterstaff","Sickle","Spear","Unarmed_strike","Battleaxe","Flail","Glaive",
                                       "Greataxe","Greatsword","Halberd","Lance","Longsword","Maul",
                                       "Morningstar","Pike","Rapier","Scimitar","Shortsword","Trident",
                                       "War_pick","Warhammer","Whip"};
  int Weapon_i[kWeapon_NUM][5] = {{10, 1, 4, 2, 0}, {200, 1, 4, 2, 0}, {20, 1, 8, 10, 0}, {500, 1, 6, 2, 0}, {50, 1, 6, 2, 0},
                                  {200, 1, 4, 2, 0}, {500, 1, 6, 4, 0}, {20, 1, 6, 4, 0}, {100, 1, 4, 2, 0}, {100, 1, 6, 3, 0},
                                  {0, 1, 1, 0, 0}, {1000, 1, 8, 4, 0}, {1000, 1, 8, 2, 0}, {2000, 1, 10, 6, 0},
                                  {3000, 1, 12, 7, 0}, {5000, 2, 6, 6, 0}, {2000, 1, 10, 6, 0}, {1000, 1, 12, 6, 0},
                                  {1500, 1, 8, 3, 0}, {1000, 2, 6, 10, 0}, {1500, 1, 8, 4, 0}, {500, 1, 10, 18, 0},
                                  {2500, 1, 8, 2, 0}, {2500, 1, 6, 3, 0}, {1000, 1, 6, 2, 0}, {500, 1, 6, 4, 0},
                                  {500, 1, 8, 2, 0}, {1500, 1, 8, 2, 0}, {200, 1, 4, 3, 0}};
  //cost(copper), num_of_dices, damage_dice, weight, type_of_elemental_damage
  std::string Ranged_Weapon_s[kR_Weapon_NUM] = {"Crossbow_light","Dart","Shortbow","Sling","Blowgun",
                                                "Crossbow_hand","Crossbow_heavy","Longbow","Net"};
  int Ranged_Weapon_i[kR_Weapon_NUM][7] = {{2500,1,8,5,0,80,320},{5,1,4,0,0,20,60},{2500,1,6,2,0,80,320},{10,1,4,0,0,30,120},
                                           {1000,1,1,1,0,25,100},{7500,1,6,3,0,30,120},{5000,1,10,18,0,100,400},{5000,1,8,2,0,150,600},
                                           {100,0,0,3,0,5,15}};
  //cost(copper), num_of_dices, damage_dice, weight, type_of_elemental_damage , aiming_range, max_range
  std::string Food_s[kFood_NUM] = {};
  int Food_i[kFood_NUM] = {};
  std::string Armor_s[kArmor_NUM] = {"Padded","Leather","Studded_leather",
                                     "Hide","Chain_shirt","Scale_mail","Breastplate","Half_plate",
                                     "Ring_mail","Chain_mail","Splint","Plate",
                                     "Shield"};
  int Armor_i[kArmor_NUM][6] = {{500,0,11,0,1,8},{1000,0,11,0,0,10},{4500,0,12,0,0,13},
                                {1000,1,12,0,0,12},{5000,1,13,0,0,20},{5000,1,14,0,1,45},{40000,1,14,0,0,20},{75000,1,15,0,1,40},
                                {3000,2,14,0,1,40},{7500,2,16,13,1,55},{20000,2,17,15,1,60},{150000,2,18,15,1,65},
                                {1000,3,2,0,0,6}};
  //Cost , Type , Armor_Class , Strength_needed , stealth_disadvantage, weight
  std::string Usable_s[kUsable_NUM] = {};
  int Usable_i[kUsable_NUM] = {};
};

class Item {
 protected:
  std::string *name;
  int count;
  bool stackable;
  int cost;
  int weight;
 public:
  Item() : name(name) {
    //name = nullptr;
    count = 0;
    stackable = false;
    cost = 0;
    weight = 0;
  }
  ~Item() = default;

  virtual std::string get_name() {
    return *name;
  };
  virtual int show() { return count; };
  virtual int get_count() { return count; };
  virtual void set_count(int a) { count +=a;};
};

class Weapon : public Item {
 protected:
  int num_of_dices;
  int damage_dice;
  int type_of_elemental_damage;
  std::string elements[6] = {"no", "acid", "lightning", "fire", "cold", "poison"};
 public:
  Weapon() = default;
  Weapon(std::string *name_) {
    Existing_Items E;
    int count_ = 1, num_of_dices_ = 0, damage_dice_ = 0, type_of_elemental_damage_ = 0;
    for(int i = 0;i < kWeapon_NUM;i++){
      if(E.Weapon_s[i].compare(*name)){
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
  Weapon(std::string *name_, int count_, int num_of_dices_, int damage_dice_, int type_of_elemental_damage_){
    set(name_, count_, num_of_dices_, damage_dice_, type_of_elemental_damage_);
  }
  ~Weapon() = default;
  void set(std::string *name_, int count_, int num_of_dices_, int damage_dice_, int type_of_elemental_damage_) {
    name = name_;
    count = count_;
    stackable = false;
    num_of_dices = num_of_dices_;
    damage_dice = damage_dice_;
    type_of_elemental_damage = type_of_elemental_damage_;
  }
  int show() {
    std::cout << *name << std::endl;
    std::cout << "Damage "<< num_of_dices << "d"<< damage_dice <<
              " element:"<< elements[type_of_elemental_damage] << std::endl;
    return damage_dice;
  }
};

class Ranged_Weapon : public Weapon {
 protected:
  int aiming_range;
  int max_range;
 public:
  Ranged_Weapon() = default;
  Ranged_Weapon(std::string *name_) {
    Existing_Items E;
    int count_ = 1, num_of_dices_ = 0, damage_dice_ = 0, type_of_elemental_damage_ = 0;
    int aiming_range_ = 0,max_range_ = 0;
    for(int i = 0;i < kWeapon_NUM;i++){
      if(E.Ranged_Weapon_s[i].compare(*name)){
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
  Ranged_Weapon(std::string *name_, int count_, int num_of_dices_, int damage_dice_, int type_of_elemental_damage_,
      int aiming_range_, int max_range_){
    set(name_, count_, num_of_dices_, damage_dice_, type_of_elemental_damage_, aiming_range_, max_range_);
  }
  ~Ranged_Weapon() = default;
  void set(std::string *name_, int count_, int num_of_dices_, int damage_dice_, int type_of_elemental_damage_,
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

  int show(){
    std::cout << *name << std::endl;
    std::cout << "Damage "<< num_of_dices << "d"<< damage_dice <<
              " element:"<< elements[type_of_elemental_damage] << std::endl;
    return damage_dice;
  }
};

class Food : public Item {
 public:
  Food(std::string *name_, int count_) {
    set(name_, count_);
  }
  ~Food() = default;
  void set(std::string *name_, int count_) {
    name = name_;
    count = count_;
    stackable = true;
  }
  int show() {
    printf("%s", "Usable:");
    std::cout << *name << std::endl;
    return -1;
  }
};

class Armor : public Item {
 protected:
  int type;
  int armor_class;
  int strength_needed;
  bool stealth_disadvantage;
 public:
  Armor(std::string *name_) {
    Existing_Items E;
    int count_ = 1, type_ = 0, armor_class_ = 0, strength_needed_ = 0;
    bool stealth_disadvantage_ = 0;
    for(int i = 0;i < kWeapon_NUM;i++){
      if(E.Armor_s[i].compare(*name)){
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
    set(name_, type_, count_,  armor_class_, strength_needed_, stealth_disadvantage_);
  }
  Armor(std::string *name_, int type_, int count_,  int armor_class_,int strength_needed_, bool stealth_disadvantage_){
    set(name_, type_, count_,  armor_class_, strength_needed_, stealth_disadvantage_);
  }
  ~Armor() = default;
  void set(std::string *name_,int type_, int count_, int armor_class_, int strength_needed_, bool stealth_disadvantage_) {
    name = name_;
    type = type_;
    count = count_;
    stackable = false;
    armor_class = armor_class_;
    strength_needed = strength_needed_;
    stealth_disadvantage = stealth_disadvantage_;
  }
  int show() {
    std::cout << *name << std::endl;
    printf("%s %d %s %d \n", "Armor Class:", armor_class, "stealth disadvantage:", stealth_disadvantage);
    return armor_class;
  }
};

class Usables : public Item {
 public:
  Usables() = default;
  Usables(std::string *name_, int count_) {
    set(name_, count_);
  }
  ~Usables() = default;
  void set(std::string *name_, int count_) {
    name = name_;
    count = count_;
    stackable = true;
  }
  int show() {
    printf("%s", "Usable:");
    std::cout << *name << std::endl;
    return -1;
  }
};

class Ammo : public Usables {
 protected:
  int ammo_damage;
  int element;
 public:
  Ammo(std::string *name_, int count_, int ammo_damage_,int element_){
    set(name_, count_,ammo_damage_,element_);
  }
  void set(std::string *name_, int count_, int ammo_damage_, int element_) {
    name = name_;
    count = count_;
    ammo_damage = ammo_damage_;
    stackable = true;
    element = element_;
  }
  int show() {
    printf("%s", "Usable:");
    std::cout << *name << std::endl;
    return -1;
  }

};

