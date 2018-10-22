
#include "Race_TEST.h"
/*Movement = 30;
  Size = 2;
  Darkvision = 120;
  damage_resistance = 0;
  Dex += 2;
  Cha += 1;
  raceFeatures = "fits,Languages";*/

TEST_F(Race_TEST, TypeTest){
  EXPECT_EQ(Test_Subject->get(0),2);//type
}

TEST_F(Race_TEST, MovementTest){
  EXPECT_EQ(Test_Subject->get(10),30);//Movement
}

TEST_F(Race_TEST, SizeTest){
  EXPECT_EQ(Test_Subject->get(11),2);//Size
}

TEST_F(Race_TEST, DamageResTest){
  EXPECT_EQ(Test_Subject->get(13),0);//DamageResistance
}

TEST_F(Race_TEST, StrengthTest){
  EXPECT_EQ(Test_Subject->get(4),0);// Str
}

TEST_F(Race_TEST, CharismaTest){
  EXPECT_EQ(Test_Subject->get(9),1);//Charisma = 1
}

/*TEST_F(Race_TEST, ){
EXPECT_EQ(Test_Subject->get(),);
}*/