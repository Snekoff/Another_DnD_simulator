//
// MIT License
// Copyright (c) 2019 Snekoff. All rights reserved.
//
#pragma once

#include <fstream>
#include <set>

#include "../character/common_functions.h"
#include "../character/character.h"
#include "unicode_console_output.h"

#ifndef ANOTHER_DND_SIMULATOR_MAZE_GENERATOR_H
#define ANOTHER_DND_SIMULATOR_MAZE_GENERATOR_H

/*
 * Bit harsh labyrinth algorithm.
 * Input: Empty field (n * m)
 * You can set field properties before algorithm will start.
 * Like making indestructible walls, place rooms, place entrances.
 * Then in walls mole will dig corridors.
 * Output: Labyrinth with rooms(even if you didn't place them), traps and so on.
 * */

// Adds a modifier to coordinate to get to another point
struct DirectionModifiers{
    const int eight_direction_modifier[8][2] = {{0,  -1},
                                          {1,  -1},
                                          {1,  0},
                                          {1,  1},
                                          {0,  1},
                                          {-1, 1},
                                          {-1, 0},
                                          {-1, -1},
    };
};

struct RoomGenerationVars {
    int room_width;
    int room_length;
    int room_height;
    int room_space;
    pair<int, int> region_from;
    pair<int, int> region_to;
};

struct EntranceInfo {
    int id;
    int order;
    string name;
    // If Entrance is not blockable than it is possible that few corridors will lead to this entrance
    // else only one corridor could reach
    bool is_blockable;
    // is reached already?
    bool blocked;
    // I'm going to add some triggers, may be like text appearing, and may be all dungeon changes... who knows :3
    string trigger_name;
    vector<pair<int, int>> linked_squares;
};

//  Neither id neither order must be equivalent
struct compare_by_id_or_order {
    bool operator() (EntranceInfo &a, EntranceInfo &b) const {
        return (a.id < b.id) && (a.order < b.order);
    }
};

struct find_by_id {
    find_by_id(const int & id) : id(id) {}
    bool operator()( EntranceInfo & entrance_info_) const {
        return entrance_info_.id == id;
    }
private:
    int id;
};

/*auto cmp = [](int a, int b) { return ... };
std::set<int, decltype(cmp)> s(cmp);*/

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
    vector<vector<int>> square;
    int difficulty;
    int room_probability;
    int num_of_free_fields;
    int num_of_deadends;
    // entrances and exits are just places which algorithm will cross only once
    // odd pair is begin of a region and next one is the end of the region
    vector<vector<int>> entrances;
    set<pair<int, int>> FreeSquaresSet;
    vector<vector<bool>> deadend;
    vector<vector<vector<bool>>> square_possible_to_move_from_dirrections;
    bool was_room_built_on_this_turn = false;
    set<EntranceInfo, compare_by_id_or_order> entrance_info_set;
    int room_length_max = 6;
    int room_width_max = 6;
    int room_height_max = 3;
    const int kDifficulty_Max = 10;
    const int kDifficulty_Min = 0;
    const int kRoomProbabilityMax = 9;
    const int kRoomProbabilityMin = 0;
    const int kRoomLengthMin = 1;
    const int kRoomHeightMin = 1;
    const int kRoomWidthMin = 1;
public:
    MazeGenerator();

    ~MazeGenerator();

    //How it works:
    //Suppose that our field contain only walls, entrances, exits and preplaced rooms(if they are supposed to be visited
    // then they must have at least one entrance)
    //"Mole" starts digging from entrance 1 and moving all around until there wont be any blank(massive wall regions) space
    // with few rules: The most important is that it couldn't cross existing corridors, and "impassable" walls
    // if mole crosses the Entrance #2 then all region(Entrance #2) is blocked(marked as reached entrance) and cant be passed again
    // minimum mole pace is 2 (thick* wall) *5-ft
    MazeGenerator(Random_Generator_ *Rand_gen, vector<vector<int>> square_);

    // room region is two points (start end end)
    vector<vector<int>> RoomsPlacement(vector<vector<int>> &square_);

    bool Room_BuildingWalls(pair<int, int> start_of_the_region,
                            pair<int, int> end_of_the_region,
                            vector<vector<int>> &square_, pair<int, int> entrance
    );



    bool Room_MakingSpaceInsideWalls(pair<int, int> start_of_the_region,
                                         pair<int, int> end_of_the_region,
                                         vector<vector<int>> &square_,
                                         int &num_of_free_fields_);

    // if you have some rooms, but it doesn`t matter where are they in labyrinth and where are their entrances
    vector<vector<int>>
    RoomRandomPlacement(vector<int> roomSizeAndShape, vector<int> numOfEntrances, vector<int> entransesLength,
                        vector<vector<int>> &square_);

    // check negative coordinates
    bool IsNegative(int x, int y, int index);

    // returns new position
    pair<int, int>
    Move(Random_Generator_ *Rand_gen, int x, int y, vector<vector<int>> &square_, int &num_of_free_fields_,
         vector<vector<bool>> &deadends, vector<vector<vector<bool>>> & squarepossibletomovedirrections);

    bool CouldMakeCorridor(Random_Generator_ *Rand_gen, int direction, int from_x, int from_y, int to_x, int to_y, vector<vector<int>> square_);

    int GetRandomDirection(Random_Generator_ *Rand_gen);

    int ReturnPossibleDirectionOrNegativeIfAny(Random_Generator_ *Rand_gen, int x, int y, int direction, vector<vector<int>> square_, vector<vector<bool>> &deadends, vector<vector<vector<bool>>> & squarepossibletomovedirrections_);

    bool IsRightDirection(int x, int y, int direction_, vector<vector<int>> square_);

    int ReturnPaceLength(Random_Generator_ *Rand_gen, int difficulty_);

    vector<vector<int>> Build_Labyrinth(Random_Generator_ *Rand_gen, vector<vector<int>> &square_, int num_of_deadends_, int num_of_free_fields_, vector<vector<bool>> deadend_);

    vector<vector<int>> GetField();

    void Set(int valuetobechanged, int value1, int value2, int value3, int value4, bool boolvalue1, bool boolvalue2);

    // wall, empty, room wall etc.
    vector<vector<int>> Set_FieldType(pair<int, int> start_of_the_region,
                                      pair<int, int> end_of_the_region, vector<vector<int>> &square_);

    vector<vector<int>>  LabyrinthMenu(vector<vector<int>> &square_);

    int Set_Difficulty();

    pair<pair<int, int>, pair<int, int>> RegionSelect(vector<vector<int>> square_);

    // later
    // what to return?
    vector <pair<int, int>> Set_Trap(pair<int, int> start_of_the_region,
                                     pair<int, int> end_of_the_region);

    //Entrance or Exit, it does not matter
    EntranceInfo Set_Entrance();

    // later
    void Set_Trigger(pair<int, int> start_of_the_region,
                     pair<int, int> end_of_the_region);

    void Visualizer(vector<vector<int>> square_);
    
    vector<vector<wchar_t>> VisualizerTakeBattlefieldReturnGraphics(vector<vector<int>> square_);

    vector<vector<int>> GetLabirinth();

    int Get(int what);

    vector<vector<int>> GetVectorVectorInt(int what);

    vector<vector<bool>> GetVectorVectorBool(int what);

    pair<int, int> GetZeroOrderEntrancePos(Random_Generator_ * Rand_gen, set<EntranceInfo, compare_by_id_or_order> entrance_info_);

    EntranceInfo GetEntranceInfo(int id);

    vector<vector<int>> GetEntrances();

    EntranceInfo ZeroIdEntranceInfo() const;

    pair<int, int> GetNewRandPos(Random_Generator_ *Rand_gen, pair<int, int> starting_pos, vector<vector<int>> square_, vector<vector<bool>> deadend_);

    void DeleteOldInfoInSquare(const vector<vector<int>> &square_, int j, int i);

    bool FreeSpaceAfterDigging(vector<vector<int>> &square_, pair<int, int> from, pair<int, int> to, int &num_of_free_fields_);

    void ShowField(vector<vector<int>> &square_);

    pair<int, int> RoomGenerator(Random_Generator_ *Rand_gen, vector<vector<int>> &square_, pair<int, int> from, int direction_, int &num_of_free_fields_);

    int Set_RoomProbability();

    pair<int, int>
    RoomGenerator_RoomStartingPoint(Random_Generator_ *Rand_gen, vector<vector<int>> &square_, pair<int, int> from,
                                    int direction_, int &linelength, vector<bool> &usedpos, vector<int> searchedforfieldtypes, vector<pair<int, int>> excludepoints);

    bool
    RoomGenerator_RoomRegionCheckIfEmpty(Random_Generator_ *Rand_gen, vector<vector<int>> &square_, pair<int, int> from,
                                         pair<int, int> to, vector<pair<int, int>> excludepoints);

    pair<int, int> RoomGenerator_FreeSpaceAndReturnNewPos(Random_Generator_ *Rand_gen, vector<vector<int>> &square_,
                                                          pair<int, int> from, pair<int, int> to,
                                                          pair<int, int> entrance_, int direction_,
                                                          int &num_of_free_fields_);

    int Set_RoomSize();

    bool CheckFieldSurroundingsReturnFalseIfFoundSearched_v2(pair<int, int> from, pair<int, int> to,
                                                             vector<vector<int>> square_,
                                                             vector<int> searchedforfieldtypes,
                                                             vector<pair<int, int>> excludepoints);

    map<int, wchar_t> GetMapIntWchar_t() const;

    RoomGenerationVars
    DP_RoomSearchForBiggestRoomStartingFromGivenSizesAndDecreaseIfDontFitIn(Random_Generator_ *Rand_gen, vector<vector<int>> square_, int direction,
                                                                           pair<int, int> entrance, int width,
                                                                           int length, int height);

    bool IsOutOfVectorVectorSize(vector<vector<int>> square_, int x, int y);

    bool IsDirectionCorrect(int direction, pair<int, int> from, pair<int, int> to);

    void AddToFreeSquaresSet(vector<vector<int>> square_, pair<int, int> freesquare);

    void DeleteFromFreeSquaresSet(pair<int, int> freesquare);

    void ShowFreeSquaresSet();

    pair<int, int>
    IfMovingByXReturnChangedXElseReturnChangedY(int from_x, int from_y, int to_x, int to_y, int dif_x, int dif_y, int i) const;

    bool CheckForRoomWallOrFreeFieldWhichCouldBeIgnoredWhileBuildingCorridor(Random_Generator_ *Rand_gen,
                                pair<int, int> point_for_checking,
                                int direction,
                                vector<vector<int>> square_,
                                int &count_room_walls_if_more_than_two_stop,
                                bool &is_first_field_after_passing_through_room_wall,
                                vector<pair<int, int>> &excludepoints_);

    pair<int, int> ReturnNewPosIfInFieldElseReturnOldPos(Random_Generator_ *Rand_gen, int x, int y,
                                                         const vector<vector<int>> &square_,
                                                         vector<vector<bool>> &deadends,
                                                         vector<vector<vector<bool>>> &squarepossibletomovedirrections_,
                                                         int min_pace_length, const DirectionModifiers &dir_mod,
                                                         int direction);

    pair<int, int>
    IfPossibleToMakeCorridorReturnEndOfItPositionElseOldPosition(Random_Generator_ *Rand_gen, int x, int y,
                                                                 const vector<vector<int>> &square_, pair<int, int> pos,
                                                                 int direction, const DirectionModifiers &dir_mod);

    pair<int, int>
    IfRndLessThanRoomProbabilityTryToBuildRoomAndReturnExitOfIt(Random_Generator_ *Rand_gen, int &num_of_free_fields_,
                                                                int direction, const DirectionModifiers &dir_mod,
                                                                int &x,
                                                                int &y, vector<vector<int>> &square_,
                                                                pair<int, int> pos);
};

#endif //ANOTHER_DND_SIMULATOR_MAZE_GENERATOR_H
//mazeGenerator
