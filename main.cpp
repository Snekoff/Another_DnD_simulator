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

using namespace std;

int main() {
  printf("%s \n", "Dungeons and Dragons game (PC) starts here");
  //Game * starts = new Game(1,1);
  //cout << starts->is_Created() << endl;
  auto Mobs = new Monster(1,0,0,1);
  //auto FieldOfHonor = new Battleground(17,10,5);// X,Y,Z
  //FieldOfHonor->Shape();
  return 0;
}
/*
 * 1. characters, weapons, spells etc.
 * 2. mobs, animals , all races.
 * 3. world ( and its randomness )
 * 4. std::map can return pointer of function
 * 5. batle field, turn,
 * 6. map
 * 7. clever enemies
 * 8. coming
 * 9. coming...
 */