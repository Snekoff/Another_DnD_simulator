//
// MIT License
// Copyright (c) 2019 Snekoff. All rights reserved.
//
#include "local_map_user_usage.h"

void Maze_generator_usage(){
    Random_Generator_ * randomGenerator;
    setlocale(LC_ALL, "");
// an example of maze
    setlocale(LC_ALL, "ALL");
    vector<vector<int>> square_(50, vector<int> (30, 0));
    cout << "\n";
    MazeGenerator mazeGenerator(randomGenerator, square_);
    pair<int, int> entrance_0 = make_pair(1, 1);
    pair<int, int> entrance_1 = make_pair(square_.size() - 2, square_[0].size() - 5);
//First entrance with coords (1, 1)
//Set(int valuetobechanged, int value1, int value2, int value3, int value4, bool boolvalue1, bool boolvalue2)
//value1 = id, value2 = order, value3 = x, value4 = y, boolvalue1 = is_blockable, boolvalue2 = blocked
//zeroid already is in with id = 0 so start with id = 1

    mazeGenerator.Set(1, 1, 1, entrance_0.first, entrance_0.second, false, false);
//Second(exit) coords (square_.size() - 2, square_[0].size() - 5)
    mazeGenerator.Set(1, 2, 2, entrance_1.first, entrance_1.second, true, false);
    square_ = mazeGenerator.GetVectorVectorInt(2);
    mazeGenerator.Visualizer(square_);
//Before alg starts you can
//Set difficulty and others params
//After it ends you can decide whether it has appropriate form
    mazeGenerator.Build_Labyrinth(randomGenerator, square_, mazeGenerator.Get(3), mazeGenerator.Get(2),
                                  mazeGenerator.GetVectorVectorBool(1));
// I use wide chars to extend possible output symbols dictionary
    vector<vector<wchar_t>> buf;
    buf = mazeGenerator.VisualizerTakeBattlefieldReturnGraphics(square_);
// function to print wide chars
//printwc(0x1f790);
    cout << "Final form:\n";
    mazeGenerator.Visualizer(square_);
}


