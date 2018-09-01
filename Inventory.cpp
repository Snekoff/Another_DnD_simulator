#include <iostream>

class Item { //all items have got damage
 protected:
  std::string name;
  std::string type;
  int amount;
  int weight;
  int damage;
  bool isweapon;
 public:
  Item() {
    name = "clothes";
    type = "equipment";
    amount = 1;
    weight = 1;
    damage = 0;
    isweapon = false;
  }
  ~Item() {}

  void Set(){

  }
};

class Weapon : public Item {
 private:
  int skill_required;
  int weapon_type; // slashing/piercing etc.
 public:
  Weapon() {}
  ~Weapon() {}

  void SetWeapon(){

  }
};