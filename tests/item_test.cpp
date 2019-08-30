//
// MIT License
// Copyright (c) 2019 Snekoff. All rights reserved.
//


#include "item_test.h"

TEST_F(Item_TEST, ItemGetNameShouldReturnLongswordTest){
  EXPECT_EQ(Test_Subject->get_name(), "Longsword");
}

TEST_F(Item_TEST, ItemGetClassShouldReturnWeaponTest){
  EXPECT_EQ(Test_Subject->get_name(), "Longsword");
}

TEST_F(Item_TEST, ItemShowShouldReturnEightTest){
  EXPECT_EQ(Test_Subject->show(), 8);//damage dice
}

TEST_F(Item_TEST, ItemGetZeroShouldReturnCostTest){
  EXPECT_EQ(Test_Subject->get(0), 15*100);//cost
}

TEST_F(Item_TEST, ItemGetWeightShouldReturnThreeTest){
  EXPECT_EQ(Test_Subject->get(1), 3);//weight
}

TEST_F(Item_TEST, ItemGetCountShouldReturnOneTest){
  EXPECT_EQ(Test_Subject->get(2), 1);//count
}

TEST_F(Item_TEST, ItemGetNumOfDicesShouldReturnOneTest){
  EXPECT_EQ(Test_Subject->get(3), 1);//num_of_dices
}

TEST_F(Item_TEST, ItemGetDamageShouldReturnEightTest){
  EXPECT_EQ(Test_Subject->get(4), 8);//damage_dice
}

TEST_F(Item_TEST, ItemGetElementShouldReturnZeroTest){
  EXPECT_EQ(Test_Subject->get(5), 0);// type_of_elemental_damage
}

TEST_F(Item_TEST, ItemIsEquipedShouldReturnFalseTest){
  EXPECT_EQ(Test_Subject->is_equipped(), false);
}

TEST_F(Item_TEST, ItemIsEquipedShouldReturnTrueIfWasEquippedTest){
  Test_Subject->equip(1);//equip 1 Longsword
  EXPECT_EQ(Test_Subject->is_equipped(), true);
}

TEST_F(Item_TEST, ItemIsEquipedShouldReturnFalseIfNumOfEquipedIsLessThanTotalTest){
  Test_Subject->set_count(2);// add 2 Longswords to existing one
  Test_Subject->equip(2);//equip 2 of 3 Longswords means that we still can equip at least one.
  EXPECT_EQ(Test_Subject->is_equipped(), false);
}

TEST_F(Item_TEST, ItemIsEquipedShouldReturnTrueIfNumOfEquipedIsEqualThanTotalTest){
  Test_Subject->equip(1);//equip 1 of 1 Longswords
  EXPECT_EQ(Test_Subject->is_equipped(), true);
}

TEST_F(Item_TEST, ItemIsEquipedShouldReturnTrueIfNumOfEquipedIsGreaterThanTotalTest){
  Test_Subject->equip(2);//equip 2 of 1 Longswords means that we equip one(maximum).
  EXPECT_EQ(Test_Subject->is_equipped(), true);
}

TEST_F(Item_TEST, ItemIsEquipedShouldReturnFalseIfNumOfEquipedIsNegativeTest){
  Test_Subject->equip(-10);//unequip 10 of 1 Longswords means that we unequip one(maximum).
  EXPECT_EQ(Test_Subject->is_equipped(), false);
}

/*TEST_F(Item_TEST, ItemGetShouldReturnTest){
  EXPECT_EQ(Test_Subject->get(),);
}*/