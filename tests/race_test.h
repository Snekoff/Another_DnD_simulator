#pragma once
#ifndef ANOTHER_DND_SIMULATOR_RACE_TEST_H
#define ANOTHER_DND_SIMULATOR_RACE_TEST_H
#include "../gtest/googletest/include/gtest/gtest.h"
#include "../gtest/googlemock/include/gmock/gmock.h"
#include "../Character/race.h"
class Race_TEST : public ::testing::Test {
 public:
  Race * Test_Subject;
  Allowance * allowance;
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  Race_TEST(){
    allowance = new Allowance();
    if(!allowance->Is_Tested())allowance->Tested();
    if(allowance->Is_Character_Set())allowance->Character_Set();
    Test_Subject = new Elf(0,1,1,1,allowance);
  }
  // You can do set-up work for each test here.

  ~Race_TEST() override {
    delete Test_Subject;
  }
};

#endif //ANOTHER_DND_SIMULATOR_RACE_TEST_H
