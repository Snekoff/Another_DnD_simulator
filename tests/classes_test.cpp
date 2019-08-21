
#include "classes_test.h"

TEST_F(Classes_TEST, HitDiceParameterTest){
  //Test_Subject->Create(Allowance, 0, skills_b);
  EXPECT_EQ(Test_Subject->get(20),12);//hit dice
}

TEST_F(Classes_TEST, PrimaryAbilityTest){
  EXPECT_EQ(Test_Subject->get_bool(0),true);//primary ability STR
  EXPECT_EQ(Test_Subject->get_bool(1),false);//primary ability Dex
  EXPECT_EQ(Test_Subject->get_bool(5),false);//primary ability Wis
}

TEST_F(Classes_TEST, SavingThrowTest){
  EXPECT_EQ(Test_Subject->get_bool(6),true);//saving throw STR
  EXPECT_EQ(Test_Subject->get_bool(7),false);//saving throw Dex
  EXPECT_EQ(Test_Subject->get_bool(11),false);//saving throw Wis
}

TEST_F(Classes_TEST, ArmorAndWeaponProfTest){
// type = 0 (Barbarian)
  EXPECT_EQ(Test_Subject->get_bool(12),true);//simple weapon
  EXPECT_EQ(Test_Subject->get_bool(15),true);// weapon
  EXPECT_EQ(Test_Subject->get_bool(18),false);// ... weapon
}

TEST_F(Classes_TEST, HadSkillBeenChosenTest){
  Existing_classes E_Cl;
  EXPECT_EQ(Test_Subject->Had_Skill_Been_Chosen(skills_b,E_Cl.skills_per_class_i[Test_Subject->get(0)],1), 1);// if skill wasn't chosen it can be chosen
}

//TODO: Use googlemock to test hadskillbeenchosen

/*TEST_F(Classes_TEST, ){
EXPECT_EQ(Test_Subject->get(),);
}*/