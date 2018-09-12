

#include "Items_Factory.h"

//typedef std::pair<std::string, Item *> MyPair;
enum Item_name{
  Club, Dagger, Greatclub, Handaxe, Javelin, Light_hammer, Mace, Spear, Unarmed_strike,
  Crossbow_light, Dart, Shortbow, Sling,
  Battleaxe, Flail, Glaive, Greataxe, Greatsword, Halberd, Lance, Longsword, Maul, Morningstar,
  Pike, Rapier, Scimitar, Shortsword, Trident, War_pick, Warhammer, Whip,
  Blowgun, Crossbow_hand, Crossbow_heavy, Longbow, Net,
  Abacus,
  Acid_vial, Alchemists_fire_flask,
  Arrows, Blowgun_needles, Crossbow_bolts, Sling_bullets,
  Antitoxin,
  first_item = Club,
  last_item = Antitoxin,
};

int Item_usage() {
  std::map<std::string, Item *> myMapDude;
  std::vector<Item *> v;
  std::string a = "Leatherarmor";
  Items_Factory<Ranged_Weapon> Item_Factory_Ranged_Weapon;
  Items_Factory<Weapon> Item_Factory_Weapon;
  v.push_back(new Armor(a));
  a = "Arrows";
  v.push_back(new Ammo(a,1,0,0));
  v.push_back(new Ammo(a,11,0,0));
  a = "Longbow";
  v.push_back(new Ranged_Weapon(a));
  a = "Sling";
  v.push_back(Item_Factory_Ranged_Weapon.create(a));
  a = "Club";
  v.push_back(Item_Factory_Weapon.create(a));

  for(int i = 0; i <= v.size();i++){
    printf("%d %s " , i, " name:");
    std::cout << v[i]->show() << std::endl;
    auto iter = myMapDude.find(v[i]->get_name());
    if(iter != myMapDude.end()){
      myMapDude.at(v[i]->get_name())->set_count(v[i]->get_count());
      v.pop_back();
    }
    else{
      myMapDude.insert(std::pair(v[i]->get_name(), v[i]));
    }
  }
  std::cout << "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\n";
  for(auto it = myMapDude.begin();it != myMapDude.end(); it++){
    std::cout << it->second->show() << " count:" << it->second->get_count()<< std::endl;
  }

  return 0;
}