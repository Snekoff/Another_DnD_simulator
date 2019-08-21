
#ifndef ANOTHER_DND_SIMULATOR_BATTLEGROUND_TEST_H
#define ANOTHER_DND_SIMULATOR_BATTLEGROUND_TEST_H

#include "../gtest/googletest/include/gtest/gtest.h"
#include "../gtest/googlemock/include/gmock/gmock.h"
#include "../FieldOfHonor/Battleground.h"

class Battleground_TEST : public ::testing::Test {
 public:
  Battleground * Test_Subject;
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  Battleground_TEST(){
    Test_Subject = new Battleground();
  }
  // You can do set-up work for each test here.

  ~Battleground_TEST() override {
    delete Test_Subject;
  }
};

#endif //ANOTHER_DND_SIMULATOR_BATTLEGROUND_TEST_H
