#pragma once
//#include <iostream>

#ifndef ANOTHER_DND_SIMULATOR_ITEMS_FACTORY_H
#define ANOTHER_DND_SIMULATOR_ITEMS_FACTORY_H


#include "Item.cpp"

template<class C>
class Items_Factory {
 public:
   virtual Item * create(std::string &name_);
};

template<class C>
Item * Items_Factory<C>::create(std::string &name_) {
  return new C(name_);
}

#endif //A// NOTHER_DND_SIMULATOR_ITEMS_FACTORY_H


