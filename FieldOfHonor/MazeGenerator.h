#pragma once
#ifndef ANOTHER_DND_SIMULATOR_MAZEGENERATOR_H
#define ANOTHER_DND_SIMULATOR_MAZEGENERATOR_H
#include "../Character/UsefulFunctions.h"
#include "../Character/character.h"

const int kDifficulty_Max = 10;
const int kDifficulty_Min = 0;


struct Entrances_info{
    int ID;
    int order;
    string name;
    // If Entrance is not blockable than it is possible that few corridors will lead to this entrance
    // else only one corridor could reach
    bool is_blockable;
    // is reached already?
    bool blocked;
    // I'm going to add some triggers, may be like text appearing, and may be all dungeon changes... who knows :3
    string trigger_name;
};

// id descriptions:
// 0 - wall
// 1 - corridor/empty
// 2 - room wall
// 3 - Exit/Entrance
// 4 - Nonbreakable wall
// 5
// 6
// 7
class MazeGenerator {
 private:
  int difficulty;
  int roomProbability;
  // entrances and exits are just places which algorithm will cross only once
  // odd pair is begin of a region and next one is the end of the region
  vector<vector<int>> entrances;
  vector<vector<int>> deadend;
  vector<Entrances_info> entrances_info;
 public:
  MazeGenerator();

 ~MazeGenerator();
 //How it works:
 //Suppose that our field contain only walls, entrances, exits and preplaced rooms(if they are supposed to be visited
 // then they must have at least one entrance)
 //"Mole" starts digging from entrance 1 and moving all around until there wont be any blank(massive wall regions) space
 // with few rules: The most important is that it couldn't cross exidting corridors, and "impassable" walls
 // if mole crosses the Entrance #2 then all region(Entrance #2) is blocked(marked as corridor) and cant be passed again
 // minimum mole pace is 2 (thick* wall) *5-ft
 MazeGenerator(Random_Generator_ *Rand_gen, vector<vector<int>> square_);
 // room region is two points (start end edge)
 vector<vector<int>> RoomsPlacement(vector<pair<int, int>> roomsRegions, vector<pair<int, int>> roomsEntrances, vector<vector<int>> square_);

  vector<pair<int, int>> RoomsPlacement_BuildingWalls(pair<int, int> start_of_the_region,
                                                  pair<int, int> end_of_the_region,
                                                  vector<vector<int>> &square_
                                                  );

    vector<pair<int, int>> RoomsPlacement_CheckEdgeReach(pair<int, int> start_of_the_region,
                                                        pair<int, int> end_of_the_region,
                                                         unsigned long x_max,
                                                         unsigned long y_max);


 vector<vector<int>> RoomsPlacement_MakingRoomInside(pair<int, int> start_of_the_region,
                                                     pair<int, int> end_of_the_region,
                                                     vector<vector<int>> square_);

  // if you have some rooms, but it doesn`t matter where are they in labirinth and where are their entrances
 vector<vector<int>> RoomRandomPlacement(vector<int> roomSizeAndShape, vector<int> numOfEntrances, vector<int> entransesLength, vector<vector<int>> square_);
 // true if in current position there is no wall that can be passed through without crossing other corridors
 bool Deadend(int x, int y, vector<vector<int>> square_);
 // check negative coordinates
 bool IsNegative(int x, int y, int index);
 // returns new position
 pair<int, int> Move(Random_Generator_ *Rand_gen, int x, int y, vector<vector<int>> square_);
 //if room can be made than make it and return random room space to continue digging
 //else return current position
 pair<int, int> MakeRoom(int x, int y, char whichWay, vector<vector<int>> square_);

 bool CouldMakeCorridor(int from_x, int from_y, int to_x, int to_y, vector<vector<int>> square_);

 int Direction(Random_Generator_ *Rand_gen);

 int RightDirection(Random_Generator_ *Rand_gen, int x, int y, int direction, vector<vector<int>> square_);

 bool IsRightDirection(int x, int y, int direction_, vector<vector<int>> square_);

 int PaceLength(Random_Generator_ *Rand_gen, int difficulty_);

 int Dig(Random_Generator_ *Rand_gen);

 vector<vector<int>> GetField();

 void Set();
 // wall, empty, room wall etc.
 vector<vector<int>> Set_FieldType(pair<int, int> start_of_the_region,
                    pair<int, int> end_of_the_region);

 int Set_Difficulty();
 // later
 /// what to return?
 vector<vector<int>> Set_Trap(pair<int, int> start_of_the_region,
                pair<int, int> end_of_the_region);
 //Entrance or Exit, it does not matter
 vector<vector<int>> Set_Entrance(pair<int, int> start_of_the_region,
                   pair<int, int> end_of_the_region);
 // later
 void Set_Trigger(pair<int, int> start_of_the_region,
                  pair<int, int> end_of_the_region);

};

#endif //ANOTHER_DND_SIMULATOR_MAZEGENERATOR_H
//mazeGenerator
