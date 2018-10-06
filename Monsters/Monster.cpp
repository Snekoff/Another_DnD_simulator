//
#include "Monster.h"
using json = nlohmann::json;
Monster::Monster(int type_, int level_) {

}

Monster::Monster(int type_, int level_, int hp, int armor_class_) {
  ifstream inputJson;
  vector<vector<string>> names_by_Challenge_rating;
  names_by_Challenge_rating.resize(34);
  inputJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/Monsters/5e-SRD-Monsters.json");
  if (!inputJson.is_open()) {
    cout << "Error in loading file\n";
  }
  else {
    json j = json::parse(inputJson);
    inputJson.close();
    for(int i = 0;i < 325;i++){
      if(i > 300) cout << i << endl;
      if(j[i]["challenge_rating"] == "0"){
        names_by_Challenge_rating[0].push_back(j[i]["name"]);
      }
      else if(j[i]["challenge_rating"] == "1/8"){
        names_by_Challenge_rating[1].push_back(j[i]["name"]);
      }
      else if(j[i]["challenge_rating"] == "1/4"){
        names_by_Challenge_rating[2].push_back(j[i]["name"]);
      }
      else if(j[i]["challenge_rating"] == "1/2"){
        names_by_Challenge_rating[3].push_back(j[i]["name"]);
      }
      else{
        int challenge_rating_i = stoi(j[i]["challenge_rating"].get<std::string>());
        names_by_Challenge_rating[challenge_rating_i + 3].push_back(j[i]["name"]);
      }
    }
    cout << "Challenge_rating["<< 34 << "] = {";
    for(int n = 0 ;n < 34; n++){
      cout << " {";
      for(int i = 0; i < names_by_Challenge_rating[n].size(); i++){
        cout <<"\"" << names_by_Challenge_rating[n][i] << "\", ";
      }
      cout << "},";
    }
  }

}
//challenge_rating
//name
/*0
1/8
1/4
 1/2
 1
 .
 .
 ...
 30*/

Monster::~Monster() = default;

int Monster::Get(int w) {
  return -1;
}

bool Monster::Load(int *a) {
  return false;
}