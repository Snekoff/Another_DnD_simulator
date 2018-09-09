//
// Created by Oleg on 09.09.2018.
//

#ifndef ANOTHER_DND_SIMULATOR_ITEMS_FACTORY_H
#define ANOTHER_DND_SIMULATOR_ITEMS_FACTORY_H

#include <iostream>

template<class Item, class C>
class Items_Factory {
 public:
  virtual Item create(std::string *name_){
    return new C(name_);
  }
};

template<class Item, class C>
class Concrete_Items_Factory {
 public:
  virtual Item create(std::string *name){
    return new C(name);
  }
};

#endif //A// NOTHER_DND_SIMULATOR_ITEMS_FACTORY_H
