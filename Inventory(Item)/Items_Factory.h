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
    Items_Factory<Melee_Weapon> Weapon_Factory;
    Items_Factory<Ranged_Weapon> Ranged_Weapon_Factory;
    Items_Factory<Armor> Armor_Factory;
    Items_Factory<Goods> Goods_Factory;
    Items_Factory<Ammo> Ammo_Factory;
    Items_Factory<SpellCastingFocus> SpellCastingFocus_Factory;
    Items_Factory<Shield> Shield_Factory;
    Items_Factory<Ring> Ring_Factory;
    Items_Factory<Potion> Potion_Factory;
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
    for (int i = 0; i < kGoods_NUM; i++) {
      if (i < kGoods_NUM && name_ == E_I.Goods_s[i]) {
        return Goods_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kSpellCastingFocus_NUM; i++) {
      if (i < kSpellCastingFocus_NUM && name_ == E_I.SpellCastingFocus_s[i]) {
        return SpellCastingFocus_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kShield_NUM; i++) {
      if (i < kShield_NUM && name_ == E_I.Shield_s[i]) {
        return Shield_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kRing_NUM; i++) {
      if (i < kRing_NUM && name_ == E_I.Ring_s[i]) {
        return Ring_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kPotion_NUM; i++) {
      if (i < kPotion_NUM && name_ == E_I.Potion_s[i]) {
        return Potion_Factory.create(name_, quantity);
      }
    }
    return nullptr;
  }
};

#endif //ANOTHER_DND_SIMULATOR_ITEMS_FACTORY_H


