#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <malloc.h>
#include <queue>
#include <locale>

#include "GameOfImagination.h"
#include "Tests/TEST.h"
#include "Inventory(Item)/TMPIt.h"

using namespace std;

int main(int argc, char **argv) {
  printf("%s \n", "Dungeons and Dragons game (PC) starts here");
  bool Test = false;
  if(Test) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }
  //Game * starts = new Game(1,1);
  Pircse();
  //cout << starts->is_Created() << endl;
  //auto Mobs = new Monster(1,0,0,1);
  //auto FieldOfHonor = new Battleground(17,10,5);// X,Y,Z
  //FieldOfHonor->Shape();
  //return 0;

  return 0;
}
/*
 * 1. characters, weapons, spells etc.
 * 2. mobs, animals , all races.
 * 3. battle field, turn
 * 4. world map
 * 5. NPC
 * 6. World Random generation
 * 7. AI
 * 8. coming
 * 9. coming...
 */