#pragma once
#ifndef ANOTHER_DND_SIMULATOR_ITEM_TEST_H
#define ANOTHER_DND_SIMULATOR_ITEM_TEST_H
#include "../gtest/googletest/include/gtest/gtest.h"
#include "../gtest/googlemock/include/gmock/gmock.h"
#include "../Inventory(Item)/Item.h"
#include "../Inventory(Item)/Items_Factory.h"
#include "../AditionalTools/allowance.h"
class Item_TEST : public ::testing::Test {
 public:
  Item * Test_Subject;
  Allowance * allowance;
 protected:

  Item_TEST(){
    Complex_Factory complex_factory;
    std::string a = "Longsword";//Initializing Item by unique name
    Test_Subject = complex_factory.Factory_Complex(a, 1);
  }

  ~Item_TEST() override {
    delete Test_Subject;
  }
};

#endif //ANOTHER_DND_SIMULATOR_ITEM_TEST_H
