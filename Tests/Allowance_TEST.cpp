#include "Allowance_TEST.h"

TEST_F(Allowance_TEST, AllowanceGetIsCharacterSetShouldReturnFalseTest){
  EXPECT_EQ(Test_Subject->Is_Character_Set(), false);
}

TEST_F(Allowance_TEST, AllowanceGetIsCharacterSetShouldReturnTrueIfChangedOnceTest){
  Test_Subject->Character_Set();// Is_Character_Set = true
  EXPECT_EQ(Test_Subject->Is_Character_Set(), true);
}

TEST_F(Allowance_TEST, AllowanceGetIsCharacterSetShouldReturnFalseIfChangedTwiceTest){
  Test_Subject->Character_Set();// Is_Character_Set = true
  Test_Subject->Character_Set();// Is_Character_Set = false
  EXPECT_EQ(Test_Subject->Is_Character_Set(), false);
}

TEST_F(Allowance_TEST, AllowanceGetIsTestedShouldReturnFalseTest){
  EXPECT_EQ(Test_Subject->Is_Tested(), false);
}

TEST_F(Allowance_TEST, AllowanceGetIsTestedShouldReturnTrueIfChangedOnceTest){
  Test_Subject->Tested();// Is_Tested = true
  EXPECT_EQ(Test_Subject->Is_Tested(), true);
}

TEST_F(Allowance_TEST, AllowanceGetIsTestedShouldReturnFalseIfChangedTwiceTest){
  Test_Subject->Tested();// Is_Tested = true
  Test_Subject->Tested();// Is_Tested = false
  EXPECT_EQ(Test_Subject->Is_Tested(), false);
}