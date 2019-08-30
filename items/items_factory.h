//
// MIT License
// Copyright (c) 2019 Snekoff. All rights reserved.
//

#pragma once
//#include <iostream>
#include "item.h"

#ifndef ANOTHER_DND_SIMULATOR_ITEMS_FACTORY_H
#define ANOTHER_DND_SIMULATOR_ITEMS_FACTORY_H

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

    Items_Factory<ArtisanTools> AT_Factory;
    Items_Factory<Ship> SHP_Factory;
    Items_Factory<Valuables> $_Factory;
    Items_Factory<Instrument> INS_Factory;
    Items_Factory<AnimalGear> TAH_Factory;
    Items_Factory<Explosive> EXP_Factory;
    Items_Factory<Mounties> MNT_Factory;
    Items_Factory<Vehicle> VEH_Factory;
    Items_Factory<TradeGoods> TG_Factory;
    Items_Factory<GamingSet> GS_Factory;
    Items_Factory<Device> EM_Factory;
    Items_Factory<Tools> T_Factory;
    Items_Factory<OTH> OTH_Factory;
    Items_Factory<Rod> RD_Factory;
    Items_Factory<Scroll> SC_Factory;
    Items_Factory<Wand> WD_Factory;
    Existing_Items E_I;
    for (int i = 0; i < kM_NUM; i++) {
      if (i < kWeapon_NUM && name_ == E_I.Weapon_s[i]) {
        return Weapon_Factory.create(name_, quantity);
      }
      if (name_ == E_I.M_s[i]) {
        return Weapon_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kRanged_Weapon_NUM; i++) {
      if (i < kRanged_Weapon_NUM && name_ == E_I.Ranged_Weapon_s[i]) {
        return Ranged_Weapon_Factory.create(name_, quantity);
      }
      if (i < kR_NUM && name_ == E_I.R_s[i]) {
        return Ranged_Weapon_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kAmmo_NUM; i++) {
      if (i < kAmmo_NUM && name_ == E_I.Ammo_s[i]) {
        return Ammo_Factory.create(name_, quantity);
      }
      if (i < kA_NUM && name_ == E_I.A_s[i]) {
        return Ammo_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kArmor_NUM; i++) {
      if (i < kArmor_NUM && name_ == E_I.Armor_s[i]) {
        return Armor_Factory.create(name_, quantity);
      }
      if (i < kHA_NUM && name_ == E_I.HA_s[i]) {
        return Armor_Factory.create(name_, quantity);
      }
      if (i < kMA_NUM && name_ == E_I.MA_s[i]) {
        return Armor_Factory.create(name_, quantity);
      }
      if (i < kLA_NUM && name_ == E_I.LA_s[i]) {
        return Armor_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kG_NUM; i++) {
      if (i < kGoods_NUM && name_ == E_I.Goods_s[i]) {
        return Goods_Factory.create(name_, quantity);
      }
      if (name_ == E_I.G_s[i]) {
        return Goods_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kSpellCastingFocus_NUM; i++) {
      if (i < kSpellCastingFocus_NUM && name_ == E_I.SpellCastingFocus_s[i]) {
        return SpellCastingFocus_Factory.create(name_, quantity);
      }
      if (i < kSCF_NUM && name_ == E_I.SCF_s[i]) {
        return SpellCastingFocus_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kS_NUM; i++) {
      if (i < kShield_NUM && name_ == E_I.Shield_s[i]) {
        return Shield_Factory.create(name_, quantity);
      }
      if (i < kS_NUM && name_ == E_I.S_s[i]) {
        return Shield_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kRG_NUM; i++) {
      if (i < kRing_NUM && name_ == E_I.Ring_s[i]) {
        return Ring_Factory.create(name_, quantity);
      }
      if (name_ == E_I.RG_s[i]) {
        return Ring_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kP_NUM; i++) {
      if (i < kPotion_NUM && name_ == E_I.Potion_s[i]) {
        return Potion_Factory.create(name_, quantity);
      }
      if (i < kP_NUM && name_ == E_I.P_s[i]) {
        return Potion_Factory.create(name_, quantity);
      }
    }
    //------------------------------------------2324423423453564356735673567567
    for (int i = 0; i < kAT_NUM; i++) {
      if (i < kAT_NUM && name_ == E_I.AT_s[i]) {
        return AT_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kSHP_NUM; i++) {
      if (i < kSHP_NUM && name_ == E_I.SHP_s[i]) {
        return SHP_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < k$_NUM; i++) {
      if (i < k$_NUM && name_ == E_I.$_s[i]) {
        return $_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kINS_NUM; i++) {
      if (i < kINS_NUM && name_ == E_I.INS_s[i]) {
        return INS_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kTAH_NUM; i++) {
      if (i < kTAH_NUM && name_ == E_I.TAH_s[i]) {
        return TAH_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kEXP_NUM; i++) {
      if (i < kEXP_NUM && name_ == E_I.EXP_s[i]) {
        return EXP_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kMNT_NUM; i++) {
      if (i < kMNT_NUM && name_ == E_I.MNT_s[i]) {
        return MNT_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kVEH_NUM; i++) {
      if (i < kVEH_NUM && name_ == E_I.VEH_s[i]) {
        return VEH_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kTG_NUM; i++) {
      if (i < kTG_NUM && name_ == E_I.TG_s[i]) {
        return TG_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kGS_NUM; i++) {
      if (i < kGS_NUM && name_ == E_I.GS_s[i]) {
        return GS_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kEM_NUM; i++) {
      if (i < kEM_NUM && name_ == E_I.EM_s[i]) {
        return EM_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kT_NUM; i++) {
      if (i < kT_NUM && name_ == E_I.T_s[i]) {
        return T_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kOTH_NUM; i++) {
      if (i < kOTH_NUM && name_ == E_I.OTH_s[i]) {
        return OTH_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kRD_NUM; i++) {
      if (i < kRD_NUM && name_ == E_I.RD_s[i]) {
        return RD_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kSC_NUM; i++) {
      if (i < kSC_NUM && name_ == E_I.SC_s[i]) {
        return SC_Factory.create(name_, quantity);
      }
    }
    for (int i = 0; i < kWD_NUM; i++) {
      if (i < kWD_NUM && name_ == E_I.WD_s[i]) {
        return WD_Factory.create(name_, quantity);
      }
    }
    return nullptr;
  }
};

#endif //ANOTHER_DND_SIMULATOR_ITEMS_FACTORY_H


