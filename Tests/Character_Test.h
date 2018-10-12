
#ifndef ANOTHER_DND_SIMULATOR_CHARACTER_TEST_H
#define ANOTHER_DND_SIMULATOR_CHARACTER_TEST_H
#pragma once
#include "../gtest/googletest/include/gtest/gtest.h"
#include "../gtest/googlemock/include/gmock/gmock.h"
#include "../Character/character.h"

class Character_Test : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  Character_Test();
    // You can do set-up work for each test here.

  ~Character_Test() override;
    // You can do clean-up work that doesn't throw exceptions here.

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  //void SetUp() override;
  //void TearDown() override;

  void Test_All_Params();

  // Objects declared here can be used by all tests in the test case for Foo.
};

#endif //ANOTHER_DND_SIMULATOR_CHARACTER_TEST_H
/* int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}*/
