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
#include "Tests/TEST.h"

using namespace std;

int main(int argc, char **argv) {
  printf("%s \n", "Dungeons and Dragons game (PC) starts here");
  bool Test = false;// replace with true to see it passing all testcases
  if (Test) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }
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
  auto Rand_gen = new Random_Generator_();
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
  std::cout << std::setw(4) << j << '\n';
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