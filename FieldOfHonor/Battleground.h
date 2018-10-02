
#ifndef ANOTHER_DND_SIMULATOR_BATTLEGROUND_H
#define ANOTHER_DND_SIMULATOR_BATTLEGROUND_H
#include <vector>
#include <iostream>
#include "../Character/UsefulFunctions.h"

struct Exsisting_Fields{
  std::string state_of_square[18] = {"empty ", "inaccessible ", "with_high_obstacle ", "with_meddium_obstacle ",
                                    "with_short_obstacle ", "hard_terrain ", "occupied ", "occupied_by_body ", "door ",
                                    "window ", "water ", "fire ", "deep_water ", "lava ", "poison ", "hatch ",
                                    "ladder ", "forbidden_area "};
};

class Battleground {
 private:
  short X;
  short Y;
  short Z;
  std::vector<std::vector<int>> square;
 public:
  Battleground();

  ~Battleground();

  Battleground(short x, short y, short z);

  int Get(int what);

  void Set();

  void square_Resize();

  int Shape();

  void Load();
};

#endif //ANOTHER_DND_SIMULATOR_BATTLEGROUND_H
