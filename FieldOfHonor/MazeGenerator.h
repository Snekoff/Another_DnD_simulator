#pragma once
#ifndef ANOTHER_DND_SIMULATOR_MAZEGENERATOR_H
#define ANOTHER_DND_SIMULATOR_MAZEGENERATOR_H
#include "../Character/UsefulFunctions.h"
#include "../Character/character.h"



class MazeGenerator {
 private:
  int difficulty;
  int roomProbability;
  // entrances and exits are just places which algorithm will cross only once
  // odd pair is start of a region and next one is the end of the region
  vector<vector<pair<int, int>>> entrances;
 public:
  MazeGenerator();

 ~MazeGenerator();
 //How it works:
 //Suppose that our field contain only walls, entrances, exits and preplaced rooms(if they are supposed to be visited
 // then they must have at least one entrance)
 //"Mole" starts digging from entrance 1 and moving all around until there wont be any blank(massive wall regions) space
 // with few rules: The most important is that it couldn't cross exidting corridors, and "impassable" walls
 // if mole crosses the Entrance #2 then all region(Entrance #2) is blocked(marked as corridor) and cant be passed again
 MazeGenerator(Random_Generator_ *Rand_gen, vector<vector<int>> square_);
 // true if in current position there is no wall that can be passed through without crossing other corridors
 bool Deadend(int x, int y, vector<vector<int>> square_);
 // returns new position
 pair<int, int> Move(int x, int y, char whichWay, int howFar, vector<vector<int>> square_);
 //if room can be made than make it and return random room space to continue digging
 //else return current position
 pair<int, int> MakeRoom(int x, int y, char whichWay, vector<vector<int>> square_);

 vector<vector<int>> GetField();

};

#endif //ANOTHER_DND_SIMULATOR_MAZEGENERATOR_H
//mazeGenerator
