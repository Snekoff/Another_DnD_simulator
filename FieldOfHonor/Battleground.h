#pragma once
#ifndef ANOTHER_DND_SIMULATOR_BATTLEGROUND_H
#define ANOTHER_DND_SIMULATOR_BATTLEGROUND_H
#include <vector>
#include <iostream>
#include "../Character/UsefulFunctions.h"
#include "../Character/character.h"

struct Exsisting_Fields{
  string shape_s[3] = {"rectangle", "circle", "~ None"};
  string state_of_square[18] = {"empty ", "inaccessible ", "with_high_obstacle ", "with_meddium_obstacle ",
                                    "with_short_obstacle ", "hard_terrain ", "occupied ", "occupied_by_body ", "door ",
                                    "window ", "water ", "fire ", "deep_water ", "lava ", "poison ", "hatch ",
                                    "ladder ", "forbidden_area "};
};

class Battleground {
 private:
  short X;
  short Y;
  short Z;
  vector<vector<int>> square;
  vector<vector<vector<Character *>>> occupation;
  int shape;
  int radius;
  int X_Limit;
  int Y_Limit;
  int Z_Limit;
 public:
  Battleground();

  ~Battleground();

  Battleground(short x, short y, short z);

  int Get(int what);

  void Set();

  void square_Resize();

  int Shape();

  void Rectangle_Shape();

  void Round_Shape();

  void Load();
};

#endif //ANOTHER_DND_SIMULATOR_BATTLEGROUND_H
