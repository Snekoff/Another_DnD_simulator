#pragma once
#ifndef ANOTHER_DND_SIMULATOR_EFFECT_H
#define ANOTHER_DND_SIMULATOR_EFFECT_H
#include <fstream>
#include "../Monsters/Creature.h"
#include "../Skills_Spells_and_Feats_/Skills_and_Spells.h"
#include "../Character/character.h"
class Effect {
 private:
  int type;
  int name_i;
  int shape;//circle, rectangular
  int limit[kCoordinates_NUM];
  int center[kCoordinates_NUM];
  int radius[kCoordinates_NUM];
 public:
  Effect(int X, int Y, int Z, int type, int center_X, int center_Y, int center_Z, int name_i);

  ~Effect();
  //while (from_Z > to_Z) { radius--; from_Z--; }
  int Distance_In_Moves(int from_X, int from_Y, int to_X, int to_Y);
};


/* foot radius
 * foot cube
 * foot deep
 * foot cone
 * feet length
 * feet high
 * foot thick
 * foot square
 * feet long
 * feet thick
 * feet tall
 * speed increaces by ** feet*/
#endif //ANOTHER_DND_SIMULATOR_EFFECT_H
