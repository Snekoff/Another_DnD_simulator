//
// MIT License
// Copyright (c) 2019 Snekoff. All rights reserved.
//

#pragma once
#ifndef ANOTHER_DND_SIMULATOR_ALOWANCE_TEST_H
#define ANOTHER_DND_SIMULATOR_ALOWANCE_TEST_H
#include "../gtest/googletest/include/gtest/gtest.h"
#include "../gtest/googlemock/include/gmock/gmock.h"
#include "../aditional_tools/allowance.h"
class Allowance_TEST : public ::testing::Test {
 public:
  Allowance * Test_Subject;
 protected:

  Allowance_TEST(){
    Test_Subject = new Allowance();
    //if(Test_Subject->Is_Character_Set()) Test_Subject->Character_Set();
    //if(Test_Subject->Is_Tested()) Test_Subject->Tested();
  }

  ~Allowance_TEST() override {
    delete Test_Subject;
  }
};

#endif //ANOTHER_DND_SIMULATOR_ALOWANCE_TEST_H
