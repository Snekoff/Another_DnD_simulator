#pragma once
#ifndef ANOTHER_DND_SIMULATOR_ALLOWANCE_TEST_H
#define ANOTHER_DND_SIMULATOR_ALLOWANCE_TEST_H
#include "../gtest/googletest/include/gtest/gtest.h"
#include "../gtest/googlemock/include/gmock/gmock.h"
#include "../AditionalTools/Allowance.h"
class Allowance_TEST : public ::testing::Test {
 public:
  Allowance * Test_Subject;
 protected:

  Allowance_TEST(){
    Test_Subject = new Allowance();
  }

  ~Allowance_TEST() override {
    delete Test_Subject;
  }
};

#endif //ANOTHER_DND_SIMULATOR_ALLOWANCE_TEST_H
