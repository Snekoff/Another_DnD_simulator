#include "Character_Test.h"


TEST_F(CharacterTest, DeathsaveAndPerceptionTest){
  Test_Subject->Set(10,1);//deathsave_s++
  EXPECT_EQ(Test_Subject->Get(15),1);//deathsave_s
  EXPECT_EQ(Test_Subject->Get(16),0);//deathsave_f
  Test_Subject->Set(11,1);// advantage
  EXPECT_EQ(Test_Subject->Get_bool(0),true);//advantage = true
  Test_Subject->Set(7,15);//Wisd
  EXPECT_EQ(Test_Subject->Get(100),12);// passive_perception
  Test_Subject->Set(11,-1);//disadvantage
  EXPECT_EQ(Test_Subject->Get_bool(1),false);// advantage + disadvantage = no effect
  Test_Subject->Set(12,-1);//perception disadvantage
  EXPECT_EQ(Test_Subject->Get(100),7);// passive_perception = 12 - 5(perception_disadvantage)
  /*Test_Subject->Set(,);
  EXPECT_EQ(Test_Subject->Get(),);*/
}

TEST_F(CharacterTest, EasyParametersMaxValuesTest){
  EXPECT_EQ(Test_Subject->Get(0), 0) ;//party
  EXPECT_EQ(Test_Subject->Get(1), 0);//storyline
  EXPECT_EQ(Test_Subject->Get(2), 0);//sex
  Test_Subject->Set(19,1);//party = 1
  EXPECT_EQ(Test_Subject->Get(0), 1);
  Test_Subject->Set(20,20);// storyline = 20
  EXPECT_EQ(Test_Subject->Get(1), 12);// storyline_max = 12
  Test_Subject->Set(0,20);// sex = 20
  EXPECT_EQ(Test_Subject->Get(2), 3);//sex_max = 3
}

TEST_F(CharacterTest, ExperienceTest){
  EXPECT_EQ(Test_Subject->Get(3), 0);//experience
  EXPECT_EQ(Test_Subject->Get(4), 0);//level
  Test_Subject->Set(1,-100);//experience = -100
  EXPECT_EQ(Test_Subject->Get(3),0);//experience_min = 0
  Test_Subject->Set(1,1000000);//experience = 1000000
  EXPECT_EQ(Test_Subject->Get(3),355000); //experience_max = 355000
}

TEST_F(CharacterTest, HealthTest){
  EXPECT_EQ(Test_Subject->Get(5),0);// health
  EXPECT_EQ(Test_Subject->Get(6),0);// max_health
  EXPECT_EQ(Test_Subject->Get(7),0);// health_dice
  Test_Subject->Set(21,2);// maxhealth now = 2
  EXPECT_EQ(Test_Subject->Get(6),2);//maxhealth
  EXPECT_EQ(Test_Subject->Get(5),0);//health  *not changed*
  EXPECT_EQ(Test_Subject->Get(7),0);//health_dice *not changed*
  Test_Subject->Healing_Injuring(1);//health++
  EXPECT_EQ(Test_Subject->Get(6),2);//maxhealth *not changed*
  EXPECT_EQ(Test_Subject->Get(5),1);// health
  Test_Subject->Healing_Injuring(1);//health++
  EXPECT_EQ(Test_Subject->Get(6),2);//maxhealth *not changed*
  EXPECT_EQ(Test_Subject->Get(5),2);// health
  Test_Subject->Healing_Injuring(-1);//health--
  EXPECT_EQ(Test_Subject->Get(6),2);//maxhealth *not changed*
  EXPECT_EQ(Test_Subject->Get(5),1);// health
  Test_Subject->Healing_Injuring(10);//health += 10
  EXPECT_EQ(Test_Subject->Get(6),2);//maxhealth *not changed*
  EXPECT_EQ(Test_Subject->Get(5),2);// health = maxhealth
  Test_Subject->Healing_Injuring(-2);//health -=2
  EXPECT_EQ(Test_Subject->Get(6),2);//maxhealth *not changed*
  EXPECT_EQ(Test_Subject->Get(5),0);// health
  EXPECT_EQ(Test_Subject->Get_bool(40),true);// incapacitated (health = 0)
  Test_Subject->Healing_Injuring(-2);//health -=2
  EXPECT_EQ(Test_Subject->Get(5),0);// health = 0
  EXPECT_EQ(Test_Subject->Get_bool(48),true);// dead
  // (if damage overcomes health + maxhealth then player/monster/npc is dead without any chance to got back by itself)
  //Test_Subject->Set(,);
}

TEST_F(CharacterTest, AbilitiesAndSkillsTest){
  Test_Subject->Set(4,10);//Dexterity = 10
  EXPECT_EQ(Test_Subject->Get(9), 10);//Dex
  EXPECT_EQ(Test_Subject->Get(102), -5);//Strength Modifier = (Str - 10)/2 = -10/2
  EXPECT_EQ(Test_Subject->Get(103),0);//Dex Modifier = (Dex - 10)/2 = 0/2
  Test_Subject->Set(7,15);//Wis
  EXPECT_EQ(Test_Subject->Get(100),12);// passive_perception = 10 + Wis Mod(2)
  EXPECT_EQ(Test_Subject->Get(109),2);// skill[1] = WisMod = 2
  EXPECT_EQ(Test_Subject->Get(110),-5);// skill[2] = IntMod = -5
  EXPECT_EQ(Test_Subject->Get(125),2);// skill[17] = WisMod = 2
  Test_Subject->Set(13,1);//skill_b[1] = true
  EXPECT_EQ(Test_Subject->Get(109),4);//skill[1] = Wis Mod(2) + proficiency(2)
  Test_Subject->Set(13,2);//skill_b[2] = true
  EXPECT_EQ(Test_Subject->Get(110),-3);//skill[2] = Int Mod(-5) + proficiency(2)
  EXPECT_EQ(Test_Subject->Get(125),2);//skill[17] = Wis Mod(2)  (without proficiency because skill_b[17] = false)
  EXPECT_EQ(Test_Subject->Get(124),0);// skill[16] = Dex Mod(0)
  /*Test_Subject->Set(,);
  EXPECT_EQ(Test_Subject->Get(),);*/
}

TEST_F(CharacterTest, MoneyTest){
  Test_Subject->Set(14,1);//money[0] = 1  (copper)
  EXPECT_EQ(Test_Subject->Get(17),1);//money[0]
  EXPECT_EQ(Test_Subject->Get(18),0);//silver (money[1])
  EXPECT_EQ(Test_Subject->Get(19),0);//gold
  EXPECT_EQ(Test_Subject->Get(20),0);//platinum
  EXPECT_EQ(Test_Subject->Get(21),1);//all money in copper (money[4])
  Test_Subject->Set(15,1);// add 1 silver
  EXPECT_EQ(Test_Subject->Get(18),1);// silver
  EXPECT_EQ(Test_Subject->Get(21),11);// 1 copper + 1 silver = 11 copper
  Test_Subject->Set(16,2);// add 2 gold
  EXPECT_EQ(Test_Subject->Get(19),2);//gold
  EXPECT_EQ(Test_Subject->Get(21),211);//1copper + 1silver + 2gold = 1 + 10 + 200 copper
  Test_Subject->Paying_Money(190);// pay 190 copper* (in optimized way)
  //*Let us suppose that everyone got change
  EXPECT_EQ(Test_Subject->Get(17),1);// copper = 1
  EXPECT_EQ(Test_Subject->Get(18),2);// silver = 2
  EXPECT_EQ(Test_Subject->Get(19),0);//  Gold = 0
  EXPECT_EQ(Test_Subject->Get(20),0);//plat = 0
  EXPECT_EQ(Test_Subject->Get(21),21);// 211-190 = 21
  /*Test_Subject->Set(,);
  EXPECT_EQ(Test_Subject->Get(),);*/
}

TEST_F(CharacterTest, CharacterRaceTest){
  Test_Subject->Set(17,0);//Race Dragonborn(subtype unknown)
  EXPECT_EQ(Test_Subject->Get(26),0);//type
  int * params = new int[kData_size];
  params[26] = 0;//type
  params[27] = 1;//height
  params[28] = 1;//weight
  params[29] = 1;//age
  params[30] = 5;//Movement
  params[31] = 2;//Size
  params[32] = -1;//Darkvision in feets
  params[33] = 1;//damage_resistance (element)
  params[34] = 1;// subtype (not all races got subtypes)
  Test_Subject->Race_Call_Load(params);
  EXPECT_EQ(Test_Subject->Get(26),0);//type = 0
  EXPECT_EQ(Test_Subject->Get(29),1);//age = 1
  EXPECT_EQ(Test_Subject->Get(32),-1);//Darkvision
  Test_Subject->Race_Call_race_features();// sets standard parameters for that type
  EXPECT_EQ(Test_Subject->Get(30),30);//Movement = 30 feet
  EXPECT_EQ(Test_Subject->Get(31),2);//Size = medium(2)
  EXPECT_EQ(Test_Subject->Get(32),0);//Darkvison = 0 feet
  EXPECT_EQ(Test_Subject->Get(33),2);// damage resistance = lightning(2)

}

TEST_F(CharacterTest, CharacterClassTest){
  /*Class*/
  Test_Subject->Set(18,19);//Class = Ranger ( 12 + 7 to avoid skill choose )
  // health_dice = 10,
  EXPECT_EQ(Test_Subject->Get(7),10);//Health Dice
  EXPECT_EQ(Test_Subject->Get_bool(51),false);// primary ability (Str) = 0
  EXPECT_EQ(Test_Subject->Get_bool(52),true);// primary ability (Dex) = 1
  EXPECT_EQ(Test_Subject->Get_bool(22),true);//saving_throw_proficiencies[0] (Dex) = true
  EXPECT_EQ(Test_Subject->Get_bool(23),true);//saving_throw_proficiencies[1] (Str) = true
  EXPECT_EQ(Test_Subject->Get_bool(24),false);//saving_throw_proficiencies[2] (Con) = false

/*  Test_Subject->Set(,);
  EXPECT_EQ(Test_Subject->Get(),);*/
}

/*TEST_F(CharacterTest, ){
Test_Subject->Set(,);
  EXPECT_EQ(Test_Subject->Get(),);
}*/