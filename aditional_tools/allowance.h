//
// MIT License
// Copyright (c) 2019 Snekoff. All rights reserved.
//
#ifndef ANOTHER_DND_SIMULATOR_ALLOWANCE_H
#define ANOTHER_DND_SIMULATOR_ALLOWANCE_H

class Allowance {
 private:
  bool is_character_set;
  bool is_tested;
 public:
  Allowance();

  ~Allowance();

  void Character_Set();

  bool Is_Character_Set();

  void Tested();

  bool Is_Tested();
};

#endif //ANOTHER_DND_SIMULATOR_ALLOWANCE_H
