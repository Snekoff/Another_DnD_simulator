//
// Created by Oleg on 09.09.2018.
//
#include <iostream>

#ifndef ANOTHER_DND_SIMULATOR_ITEM_H
#define ANOTHER_DND_SIMULATOR_ITEM_H



class Item {
 protected:
  std::string *name;
  int count;
  bool stackable;
  int cost;
  int weight;
 public:
  Item() {
    name = new std::string("");
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


#endif //ANOTHER_DND_SIMULATOR_ITEM_H
