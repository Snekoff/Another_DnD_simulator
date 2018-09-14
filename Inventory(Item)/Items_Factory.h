#pragma once
//#include <iostream>

#ifndef ANOTHER_DND_SIMULATOR_ITEMS_FACTORY_H
#define ANOTHER_DND_SIMULATOR_ITEMS_FACTORY_H


#include "Item.cpp"

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

#endif //ANOTHER_DND_SIMULATOR_ITEMS_FACTORY_H


