//
// MIT License
// Copyright (c) 2019 Snekoff. All rights reserved.
//


#ifndef ANOTHER_DND_SIMULATOR_CHARACTER_TEST_H
#define ANOTHER_DND_SIMULATOR_CHARACTER_TEST_H
#pragma once
#include "../gtest/googletest/include/gtest/gtest.h"
#include "../gtest/googlemock/include/gmock/gmock.h"
#include "../Character/character.h"

class CharacterTest : public ::testing::Test {
 public:
  Character * Test_Subject;
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  CharacterTest(){
    Test_Subject = new Character();
  }
    // You can do set-up work for each test here.

  ~CharacterTest() override {
    delete Test_Subject;
  }
    // You can do clean-up work that doesn't throw exceptions here.

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  //void SetUp() override;
  //void TearDown() override;

  // Objects declared here can be used by all tests in the test case for Foo.
};


//TEST(CharacterTestFunction, ChecksAllparameters);
#endif //ANOTHER_DND_SIMULATOR_CHARACTER_TEST_H
/* int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}*/
