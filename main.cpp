#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <malloc.h>
#include <queue>
#include <locale>
#include "Interface_races_classes_background.h"
#include "character.cpp"
#include "Race_Class_Background.cpp"
#include "Item_usage.cpp"

using namespace std;

int main() {
  Item_usage();
  //setlocale(LC_ALL, "rus");
  printf("%s", "Dungeons and Dragons game (PC) starts here");

  return 0;
}
/*
 * 1. персонажи (characters, weapons, spells etc.)
 * 2. mobs, animals , all races.
 * 3. world ( and its randomness )
 * 4. std::map can return pointer of function
 * 5. batle field, turn,
 * 6. map
 * 7. clever enemies
 * 8. coming
 * 9. coming...
 */