#pragma once
//#include <iostream>

#ifndef ANOTHER_DND_SIMULATOR_ITEMS_FACTORY_H
#define ANOTHER_DND_SIMULATOR_ITEMS_FACTORY_H


#include "Item.h"

template<class C>
class Items_Factory {
 public:
   virtual Item * create(std::string &name_){
     return new C(name_);
   };
   virtual Item * create(std::string &name_, int count_){
     return new C(name_, count_);
   };
};

class Complex_Factory {
 public:
  virtual Item * Factory_Complex(std::string &name_, int quantity) {
    Items_Factory<Weapon> Weapon_Factory;
    Items_Factory<Ranged_Weapon> Ranged_Weapon_Factory;
    Items_Factory<Armor> Armor_Factory;
    Items_Factory<Usables> Usables_Factory;
    Items_Factory<Ammo> Ammo_Factory;
    Items_Factory<Magic_Items> Magic_Items_Factory;
    Existing_Items E_I;
    for (int i = 0; i < kWeapon_NUM; i++) {
      if (name_ == E_I.Weapon_s[i]) {
        return Weapon_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kRanged_Weapon_NUM; i++) {
      if (i < kRanged_Weapon_NUM && name_ == E_I.Ranged_Weapon_s[i]) {
        return Ranged_Weapon_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kAmmo_NUM; i++) {
      if (i < kAmmo_NUM && name_ == E_I.Ammo_s[i]) {
        return Ammo_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kArmor_NUM; i++) {
      if (i < kArmor_NUM && name_ == E_I.Armor_s[i]) {
        return Armor_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kUsable_NUM; i++) {
      if (i < kUsable_NUM && name_ == E_I.Usable_s[i]) {
        return Usables_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kMagic_Items_NUM; i++) {
      if (i < kMagic_Items_NUM && name_ == E_I.Magic_Items_s[i]) {
        return Magic_Items_Factory.create(name_, quantity);
      }
    }
    return nullptr;
  }
};

#endif //ANOTHER_DND_SIMULATOR_ITEMS_FACTORY_H


