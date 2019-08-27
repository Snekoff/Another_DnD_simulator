#pragma once
#ifndef ANOTHER_DND_SIMULATOR_BATTLEGROUND_H
#define ANOTHER_DND_SIMULATOR_BATTLEGROUND_H

#include <vector>
#include <iostream>

//#include "../character/common_functions.h"
//#include "../character/character.h"
#include "field_stuff.h"
#include "effect.h"
#include "maze_generator.h"

const int kShapes_NUM = 2;
const int kState_of_Field_NUM = 18;
const int kShow_Shape_String_spread_Multiplayer_x = 2;
const int kShow_Shape_String_spread_Multiplayer_y = 4;

struct Exsisting_Fields{
  string shape_s[kShapes_NUM] = {"rectangle", "circle"};
  string state_of_square[kState_of_Field_NUM] = {"empty", "inaccessible", "with_high_obstacle", "with_medium_obstacle",
                                   "with_low_obstacle", "hard_terrain", "occupied", "occupied_by_body", "door",
                                   "window", "water", "fire", "deep_water", "lava", "poison", "hatch",
                                   "ladder", "forbidden_area"};
};

class Battleground {
 private:
  int X;
  int Y;
  int Z;
  vector<vector<int>> square;
  vector<vector<Character *>> in_square;
  //vector<Effect *> effects;
  // What things/stuff are in this square.
  vector<vector<vector<FieldStuff *>>> fieldstuff;
  int shape;
  int radius;
  int X_Limit;
  int Y_Limit;
  int Z_Limit;
 public:
  Battleground();

  ~Battleground();

  Battleground(int x, int y, int z);

  int GetInt(int what);

  vector<vector<int>> GetField();

  int Shape();

  void Rectangle_Shape();

  void Round_Shape();

  int Round_Shape_Center(int what_to_show_X_or_Y);

  int Distance_In_Moves(int from_X, int from_Y, int to_X, int to_Y);
  // some geometry here
  double Distance(int from_X, int from_Y, int to_X, int to_Y);

  int Distance_Rounded(int from_X, int from_Y, int to_X, int to_Y);

  int IfHardTerrain(int X, int Y);

  double Angle_Between(int from_X, int from_Y, int to_X, int to_Y);

  void Set(int what, int value);

  void square_Resize();

  void Load();

  void Show_Shape();
};

#endif //ANOTHER_DND_SIMULATOR_BATTLEGROUND_H
