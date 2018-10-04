#pragma once
#ifndef ANOTHER_DND_SIMULATOR_BATTLEGROUND_H
#define ANOTHER_DND_SIMULATOR_BATTLEGROUND_H
#include <vector>
#include <iostream>
#include "../Character/UsefulFunctions.h"
#include "../Character/character.h"

const int kShapes_NUM = 3;
const int kState_NUM = 18;

struct Exsisting_Fields{
  string shape_s[kShapes_NUM] = {"rectangle", "circle", "~None"};
  string state_of_square[kState_NUM] = {"empty ", "inaccessible ", "with_high_obstacle ", "with_meddium_obstacle ",
                                    "with_int_obstacle ", "hard_terrain ", "occupied ", "occupied_by_body ", "door ",
                                    "window ", "water ", "fire ", "deep_water ", "lava ", "poison ", "hatch ",
                                    "ladder ", "forbidden_area "};
};

class Battleground {
 private:
  int X;
  int Y;
  int Z;
  vector<vector<int>> square;
  //vector<vector<vector<Character *>>> occupation;
  int shape;
  int radius;
  int X_Limit;
  int Y_Limit;
  int Z_Limit;
 public:
  Battleground();

  ~Battleground();

  Battleground(int x, int y, int z);

  int Get(int what);

  void Set();

  void square_Resize();

  int Shape();

  void Rectangle_Shape();

  void Round_Shape();

  int Round_Shape_Center(int what_to_show_X_or_Y);

  int Distance_between(int form_X, int from_Y, int to_X, int to_Y);

  void Load();
};

#endif //ANOTHER_DND_SIMULATOR_BATTLEGROUND_H
