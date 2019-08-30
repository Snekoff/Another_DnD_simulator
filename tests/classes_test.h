//
// MIT License
// Copyright (c) 2019 Snekoff. All rights reserved.
//

#pragma once
#ifndef ANOTHER_DND_SIMULATOR_CLASSES_TEST_H
#define ANOTHER_DND_SIMULATOR_CLASSES_TEST_H

#include "../gtest/googletest/include/gtest/gtest.h"
#include "../gtest/googlemock/include/gmock/gmock.h"
#include "../Character/class.h"
class Classes_TEST : public ::testing::Test {
 public:
  Class * Test_Subject;
  Allowance * allowance;
  std::vector<bool> skills_b;
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  Classes_TEST(){
    allowance = new Allowance();
    if(!allowance->Is_Tested()) allowance->Tested();
    for(int i = 0; i < kSkills_Num; i++){
      skills_b.push_back(false);
    }
    if(!allowance->Is_Character_Set()) allowance->Character_Set();
    Test_Subject = new Class();
    Test_Subject->Create(allowance, 0, skills_b);
  }
  // You can do set-up work for each test here.

  ~Classes_TEST() override {
    delete Test_Subject;
  }
};


#endif //ANOTHER_DND_SIMULATOR_CLASSES_TEST_H
