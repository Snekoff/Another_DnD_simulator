//
// MIT License
// Copyright (c) 2019 Snekoff. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <queue>

#include "game_of_imagination.h"
// #include "tests/TEST.h"
// google test was disabled so I saved Cmake here
/*
 * monsters/Creature.h gtest/googletest/src/gtest-all.cc gtest/googlemock/src/gmock-all.cc
 * tests/Character_Test.cpp tests/Character_Test.h tests/Battleground_TEST.cpp tests/Battleground_TEST.h
 * tests/TEST.h tests/Classes_TEST.h tests/Classes_TEST.cpp tests/Race_TEST.h tests/Race_TEST.cpp
 * tests/Allowance_TEST.h tests/Allowance_TEST.cpp tests/Item_TEST.h tests/Item_TEST.cpp*/

using namespace std;

int main(int argc, char **argv) {
    printf("%s \n", "Dungeons and Dragons game (PC) starts here");
    bool Test = false;// replace with true to see it passing all testcases
    /*if (Test) {
      ::testing::InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
    }*/
    //&&&&&&&& Base game #########
    //Uncomment following three lines and run to start/continue your story
    //Game *starts = new Game(1, 1);
    //cout << starts->is_Created() << endl;
    //delete starts;
    //&&&&&&&& End of Base game #########


    //&&&&&&&& how maze algorithm works #########
    Maze_generator_usage();

    return 0;
}
/*
* 1. characters, weapons, spells etc.
* 2. mobs, animals , all races.
* 3. battle field, turn
* 4. world map
* 5. NPC
* 6. World Random generation
* 7. AI
* 8. coming
* 9. coming...
*/
