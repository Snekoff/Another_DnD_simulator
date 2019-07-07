#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <malloc.h>
#include <queue>
#include <locale>

#include "GameOfImagination.h"
//#include "Tests/TEST.h"

/*Monsters/Creature.h gtest/googletest/src/gtest-all.cc gtest/googlemock/src/gmock-all.cc
        Tests/Character_Test.cpp Tests/Character_Test.h Tests/Battleground_TEST.cpp Tests/Battleground_TEST.h
         Tests/TEST.h Tests/Classes_TEST.h Tests/Classes_TEST.cpp Tests/Race_TEST.h Tests/Race_TEST.cpp
        Tests/Allowance_TEST.h Tests/Allowance_TEST.cpp Tests/Item_TEST.h Tests/Item_TEST.cpp*/

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
    //&&&&&&&& Lines below used for testing stuff #########
    //&&&&&&&& Uncomment any one section to try it yourself #########
    //&&&&&&&& Enjoy^^ #########

    /*&&&&&&&& how Inventory (on phase of char creation) works #########
     * auto Char = new Character();
    Char->Add_Money(3,9000);
    Char->Add_To_Inventory();
     */

/* &&&&&&&& how parsing items works #########
 * vector<Item *> itemsForCheckIn;//name
  int quantity = 1;
  itemsForCheckIn.push_back(Char->Factory_Complex(name_, quantity));
  */

    /*&&&&&&&& how Battleground shaping works #########
     * auto FieldOfHonor = new Battleground(17,10,5);// X,Y,Z
    FieldOfHonor->Shape();
     */

    /*&&&&&&&& how action/trait/spell casting parse works #########
    vector <string> trait_parse, trait_optimizedParse;
    auto monster = new Monster();
    string name = "Juiblex";
    ifstream MonJson;
    Existing_Monsters E_M;
    MonJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/monsters/bestiary-all.json");
    if (!MonJson.is_open()) return -2;
    json MonsterJson = json::parse(MonJson);
    for(int i = 0; MonsterJson["monster"][i].find("name") != MonsterJson["monster"][i].end(); i++){
      if(MonsterJson["monster"][i]["name"] == name){
        trait_parse = monster->commonForTraitAndActionAndSpellNameAndSpellHeaderEntriesAndLegendaryParse(MonsterJson["monster"][i]["trait"], "entries");
        cout << "%name% found\n";
        break;
      }
    }
    for(int i = 0; i < trait_parse.size(); i++){
      cout << trait_parse[i] << endl;
    }*/

    //&&&&&&&& how monster parse works #########
    /*auto Rand_gen = new Random_Generator_();
    Existing_Monsters E_M;
    string monster_name = "Tarul Var";
    int name_index = -1, cr_index = 0;
    for(int i = 0; i < E_M.Challenge_rating.size(); i++){
      for(int j = 0; j < E_M.Challenge_rating[i].size(); j++){
        if(monster_name == E_M.Challenge_rating[i][j]){
          cout << "challenge rating = " << i - 3 << endl;
          if(name_index == -1){
            name_index = j;
            cr_index = i;
          }
        }
      }
    }
    auto monster = new Monster(Rand_gen, name_index, cr_index);
    json j;
    j = monster->Save();
    std::cout << std::setw(4) << j << '\n';*/

    //&&&&&&&& how graphics drawing works #########
    /*Random_Generator_ * randomGenerator;
    setlocale(LC_ALL, "");
    // vector<vector<int>> square_(4, vector<int> (5, 0));
    // an example of maze
    vector<vector<int>> square_(10, vector<int> (20, 0));
    // 0 - wall
    // 1 - corridor
    // 4 - unbreakable wall (just in case)

    square_[2][1] = 1;
    square_[2][2] = 1;
    square_[2][3] = 1;
    square_[3][3] = 1;
    square_[4][3] = 1;
    square_[5][3] = 1;
    square_[5][4] = 1;
    square_[6][4] = 1;
    square_[7][4] = 1;
    square_[7][3] = 1;
    square_[7][2] = 1;
    square_[5][5] = 1;
    square_[4][5] = 1;
    square_[4][4] = 4;
    square_[4][5] = 4;
    square_[9][9] = 1;
    square_[9][8] = 1;
    square_[8][9] = 1;
    square_[8][8] = 1;
    // correct output
    // much better to look at
    // in that order:
    for (int j = 0; j < square_[0].size(); ++j) {
        for (int i = 0; i < square_.size(); ++i) {
            cout << square_[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
    MazeGenerator mazeGenerator(randomGenerator, square_);
    // I use wide chars to extend possible output symbols dictionary
    vector<vector<wchar_t>> buf;
    buf = mazeGenerator.VisualizerTakeBattlefieldReturnGraphics(square_);
    // function to print wide chars
    // void printwc(wchar_t wc)
    // try this
    //printwc(0x02500 + 20);
    //printwc(0x1f790);
    cout << "\n";
    for (int j = 0; j < square_[0].size(); ++j) {
        for (int i = 0; i < square_.size(); ++i) {
           printwc(buf[i][j]);
        }
        cout << "\n";
    }*/

    //&&&&&&&& how maze algorithm works #########
    Random_Generator_ * randomGenerator;
    setlocale(LC_ALL, "");
    // an example of maze
    vector<vector<int>> square_(10, vector<int> (20, 0));
    cout << "\n";
    MazeGenerator mazeGenerator(randomGenerator, square_);
    pair<int, int> entrance_0 = make_pair(1, 1);
    pair<int, int> entrance_1 = make_pair(square_.size() - 2, square_[0].size() - 5);
    //First entrance with coords (1, 1)
    //Set(int valuetobechanged, int value1, int value2, int value3, int value4, bool boolvalue1, bool boolvalue2)
    //value1 = id, value2 = order, value3 = x, value4 = y, boolvalue1 = is_blockable, boolvalue2 = blocked
    //zeroid already has id = 0 so start with id = 1
    mazeGenerator.Set(1, 1, 1, entrance_0.first, entrance_0.second, false, false);
    //Second(exit) coords (square_.size() - 2, square_[0].size() - 5)
    mazeGenerator.Set(1, 2, 2, entrance_1.first, entrance_1.second, true, false);
    //Before alg starts you can
    //Set difficulty and others params
    //After it ends you can decide whether it has appropriate form
    mazeGenerator.Build_Labirinth(randomGenerator, square_, mazeGenerator.Get(3), mazeGenerator.Get(2), mazeGenerator.GetVectorVectorInt(1));
    // I use wide chars to extend possible output symbols dictionary
    vector<vector<wchar_t>> buf;
    buf = mazeGenerator.VisualizerTakeBattlefieldReturnGraphics(square_);
    // function to print wide chars
    //printwc(0x1f790);
    cout << "Final form:\n";
    for (int j = 0; j < square_[0].size(); ++j) {
        for (int i = 0; i < square_.size(); ++i) {
            printwc(buf[i][j]);
        }
        cout << "\n";
    }
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
