#pragma once
#ifndef ANOTHER_DND_SIMULATOR_CLASSES_TEST_H
#define ANOTHER_DND_SIMULATOR_CLASSES_TEST_H

#include "../gtest/googletest/include/gtest/gtest.h"
#include "../gtest/googlemock/include/gmock/gmock.h"
#include "../Character/Classes.h"
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
    allowance->Tested();
    for(int i = 0; i < kSkills_Num; i++){
      skills_b.push_back(false);
    }
    allowance->Character_Set();
    Test_Subject = new Class();
  }
  // You can do set-up work for each test here.

  ~Classes_TEST() override {
    delete Test_Subject;
  }
};


#endif //ANOTHER_DND_SIMULATOR_CLASSES_TEST_H
