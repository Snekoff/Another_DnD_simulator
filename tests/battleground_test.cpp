
#include "battleground_test.h"

TEST_F(Battleground_TEST, RoundShapeCenterOddOddTest) {
  Test_Subject->Set(0, 5);//X = 5
  Test_Subject->Set(1, 5);//Y = 5
  EXPECT_EQ(Test_Subject->Round_Shape_Center(0),2);//X
  EXPECT_EQ(Test_Subject->Round_Shape_Center(1),2);//Y
}

TEST_F(Battleground_TEST, RoundShapeCenterOddPairTest) {
  Test_Subject->Set(0, 5);//X = 5
  Test_Subject->Set(1, 4);//Y = 5
  EXPECT_EQ(Test_Subject->Round_Shape_Center(0),2);//X
  EXPECT_EQ(Test_Subject->Round_Shape_Center(1),1);//Y
}

TEST_F(Battleground_TEST, RoundShapeCenterPairPairTest) {
  Test_Subject->Set(0, 4);//X = 4
  Test_Subject->Set(1, 4);//Y = 4
  EXPECT_EQ(Test_Subject->Round_Shape_Center(0),1);//X
  EXPECT_EQ(Test_Subject->Round_Shape_Center(1),1);//Y
}

TEST_F(Battleground_TEST, DistanceInMovesSameXSameYTest){
  EXPECT_EQ(Test_Subject->Distance_In_Moves(1,1,1,1),0);// A(1,1), B(1,1), dist = 0
}

TEST_F(Battleground_TEST, DistanceInMovesSameXTest){
  EXPECT_EQ(Test_Subject->Distance_In_Moves(1,1,1,2),1);//A(1,1), B(1,2), dist =  1
}

TEST_F(Battleground_TEST, DistanceInMovesOddDiagonalMoveTest){
  //diagonal consumes 1 per each odd move and 2 for pairs
  EXPECT_EQ(Test_Subject->Distance_In_Moves(1,1,2,2),1);//A(1,1), B(2,2), dist = 1
}

TEST_F(Battleground_TEST, DistanceInMovesPairDiagonalMoveTest){
  EXPECT_EQ(Test_Subject->Distance_In_Moves(1,1,3,3),3); //A(1,1), B(3,3), dist = 1 + 2(pair diagonal move)
}

TEST_F(Battleground_TEST, DistanceInMovesDiagonalTest){
  EXPECT_EQ(Test_Subject->Distance_In_Moves(1,1,5,8),9);
}

TEST_F(Battleground_TEST, DistanceInMovesOneNegativeDiagonalTest){
  EXPECT_EQ(Test_Subject->Distance_In_Moves(5,8,9,1),9);//check
}

TEST_F(Battleground_TEST, DistanceInMovesTwoNegativeDiagonalTest){
  EXPECT_EQ(Test_Subject->Distance_In_Moves(5,8,1,1),9);
}

TEST_F(Battleground_TEST, DistanceSqrtSameXSameYTest){
  EXPECT_EQ(Test_Subject->Distance(1,1,1,1),0);
}

TEST_F(Battleground_TEST, DistanceSqrtSameXTest){
  EXPECT_EQ(Test_Subject->Distance(1,1,1,2),1);// dist = sqrt(0*0 + 1*1) = sqrt(1) = 1
}

TEST_F(Battleground_TEST, DistanceSqrtOddDiagonalDiffTest){
  EXPECT_EQ(Test_Subject->Distance(1,1,2,2),sqrt(2));// dist = sqrt(1*1 + 1*1)
}

TEST_F(Battleground_TEST, DistanceSqrtPairDiagonalTest){
  EXPECT_EQ(Test_Subject->Distance(1,1,3,3),sqrt(8));
}

TEST_F(Battleground_TEST, DistanceSqrtFarPointTest){
  EXPECT_EQ(Test_Subject->Distance(1,1,7,6),sqrt(6*6+5*5));
}

TEST_F(Battleground_TEST, DistanceSqrtNegativeFarTest){
  EXPECT_EQ(Test_Subject->Distance(7,6,1,1),sqrt(6*6 + 5*5));
}

TEST_F(Battleground_TEST, DistanceRoundedSameXSameYTest){
  EXPECT_EQ(Test_Subject->Distance_Rounded(1,1,1,1),0);
}

TEST_F(Battleground_TEST, DistanceRoundedSameXTest){
  EXPECT_EQ(Test_Subject->Distance_Rounded(1,1,1,2),1);
}

TEST_F(Battleground_TEST, DistanceRoundedFarTest){
  EXPECT_EQ(Test_Subject->Distance_Rounded(1,1,4,6),6);// dist_double = 5.83 > 5.5, dist_int = 6;
}

TEST_F(Battleground_TEST, DistanceRoundedNegativeFarTest){
  EXPECT_EQ(Test_Subject->Distance_Rounded(4,6,1,1),6);
}

TEST_F(Battleground_TEST, AngleTest1){
  EXPECT_EQ(Test_Subject->Angle_Between(1,1,1,1),0);
}

TEST_F(Battleground_TEST, AngleFortyFiveTest){
  EXPECT_LE(Test_Subject->Angle_Between(1,1,2,2) - asin(sqrt(2)/2), kEpsilon);
}

TEST_F(Battleground_TEST, AngleTest2){
  EXPECT_LE(Test_Subject->Angle_Between(1,1,2,3) - asin(1/sqrt(2*2+1)), kEpsilon);
}

TEST_F(Battleground_TEST, AngleTest3){
  EXPECT_LE(Test_Subject->Angle_Between(1,1,2,1), kEpsilon);
}



/*TEST_F(Battleground_TEST, ){
EXPECT_EQ(,);
}*/

/*TEST(Battleground, ){
EXPECT_EQ(,);
}*/