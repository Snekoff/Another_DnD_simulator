#include <iostream>

class Item { //all items have got damage
 protected:
  std::string name;
  std::string type;
  int amount;
  int damage;
  bool isweapon;
 public:
  Item() {
    name = "clothes";
    type = "equipment";
    amount = 1;
    damage = 0;
    isweapon = false;
  }
  ~Item() {}

  void Set(){

  }
};