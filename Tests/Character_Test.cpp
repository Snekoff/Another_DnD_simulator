#include "Character_Test.h"

Character_Test::Character_Test() {
  Test_All_Params();
}
Character_Test::~Character_Test() = default;
void Character_Test::Test_All_Params() {
  auto Test_Subject = new Character();
  EXPECT_EQ(Test_Subject->Get(0), 0);//party
  EXPECT_EQ(Test_Subject->Get(1), 0);//storyline
  Test_Subject->Set(19,1);//party = 1
  EXPECT_EQ(Test_Subject->Get(0), 1);
  Test_Subject->Set(20,20);// storyline = 20
  EXPECT_EQ(Test_Subject->Get(1), 12);// storyline max = 12
  Test_Subject->Set(4,10);//Dexterity = 10
  EXPECT_EQ(Test_Subject->Get(9), 10);//Dex
  EXPECT_EQ(Test_Subject->Get(102), -5);//Strength Modifier
  EXPECT_EQ(Test_Subject->Get(103),0);//Dex Modifier (Dex - 10)/2
  Test_Subject->Set(7,15);//Wis
  EXPECT_EQ(Test_Subject->Get(100),12);// passive_perception = 10 + Wis Mod
  Test_Subject->Set(10,1);//deathsave_s++
  EXPECT_EQ(Test_Subject->Get(15),1);//deathsave_s
  EXPECT_EQ(Test_Subject->Get(16),0);//deathsave_f
  Test_Subject->Set(11,1);// advantage
  EXPECT_EQ(Test_Subject->Get_bool(0),true);//advantage = true
  Test_Subject->Set(11,-1);//disadvantage
  EXPECT_EQ(Test_Subject->Get(1),false);// advantage + disadvantage = no effect
  Test_Subject->Set(12,-1);//perception disadvantage
  EXPECT_EQ(Test_Subject->Get(100),7);// pas.perc. 12 - 5(perc_disadvantage)
  EXPECT_EQ(Test_Subject->Get(109),0);// skill[1]
  EXPECT_EQ(Test_Subject->Get(111),0);// skill[2]
  EXPECT_EQ(Test_Subject->Get(135),0);// skill[17]
  Test_Subject->Set(13,1);//skill_b[1] = true
  EXPECT_EQ(Test_Subject->Get(109),4);//skill[1] = Wis Mod(2) + proficiency(2)
  Test_Subject->Set(13,2);//skill_b[2] = true
  EXPECT_EQ(Test_Subject->Get(111),-3);//skill[2] = Int Mod(-5) + proficiency(2)
  EXPECT_EQ(Test_Subject->Get(135),-5);//skill[17] = Wis Mod(2)  (without proficiency because skill_b[17] = false)
  EXPECT_EQ(Test_Subject->Get(134),-5);// skill[16] = Cha Mod(-5)
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
  EXPECT_EQ(Test_Subject->Get(21),211);//1cop. + 1sil. + 2gold = 1 + 10 + 200
  Test_Subject->Paying_Money(190);// pay 190 copper (in optimized way) Let us suppose that everyone got change
  EXPECT_EQ(Test_Subject->Get(17),1);// copper = 1
  EXPECT_EQ(Test_Subject->Get(18),2);// silver = 2
  EXPECT_EQ(Test_Subject->Get(19),0);//  Gold = 0
  EXPECT_EQ(Test_Subject->Get(20),0);//plat = 0
  EXPECT_EQ(Test_Subject->Get(21),21);// 211-190 = 21
  /*Race*/
  Test_Subject->Set(17,0);//Race Dragonborn(subtype unknown)
  EXPECT_EQ(Test_Subject->Get(26),0);//type
  int * params = new int[kData_size];
  //params[26] = 1;//type
  params[27] = 1;//height
  params[28] = 1;//weight
  params[29] = 1;//age
  params[30] = 5;//Movement
  params[31] = 2;//Size
  params[32] = -1;//Darkvision
  params[33] = 1;//damage_resistance (element)
  params[34] = 1;// subtype (not all races got subtypes)
  Test_Subject->Race_Call_Load(params);
  EXPECT_EQ(Test_Subject->Get(26),0);//type = 0
  EXPECT_EQ(Test_Subject->Get(3),1);//age = 1
  EXPECT_EQ(Test_Subject->Get(12),-1);//Darkvision
  Test_Subject->Race_Call_race_features();// sets standard parameters for that type
  EXPECT_EQ(Test_Subject->Get(10),30);//Movement = 30 feet
  EXPECT_EQ(Test_Subject->Get(11),2);//Size = medium(2)
  EXPECT_EQ(Test_Subject->Get(12),0);//Darkvison = 0 feet
  EXPECT_EQ(Test_Subject->Get(13),2);// damage resistance = lightning(2)
  /*Class*/
  Test_Subject->Set(18,19);//Class = Ranger ( 12 + 7 to avoid skill choose )
                           // health_dice = 10,
  EXPECT_EQ(Test_Subject->Get(7),10);//Health Dice
  EXPECT_EQ(Test_Subject->Get_bool(22),false);// primary ability (Str) = 0
  EXPECT_EQ(Test_Subject->Get_bool(23),true);// primary ability (Dex) = 1
  EXPECT_EQ(Test_Subject->Get_bool(29),true);//saving_throw_proficiencies[0] (Dex) = true
  /*Test_Subject->Set(,);
  EXPECT_EQ(Test_Subject->Get(),);*/
  cout << "Character Test_All_Params_Passed\n";
  delete Test_Subject;
}