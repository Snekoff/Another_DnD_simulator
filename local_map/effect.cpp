#include "effect.h"

using json = nlohmann::json;

Effect::Effect(int X, int Y, int Z, int type_, int center_X, int center_Y, int center_Z, int name_i_) {
  center[0] = center_X;
  center[1] = center_Y;
  center[2] = center_Z;
  type = type_;
  name_i = -1;
  Existing_Spells E_Spells;
  for(int i = 0; i < kSpell_Num; i++){
    if(name_i_ < kSpell_Num) {
      name_i = name_i_;
      break;
    }
    if(i == kSpell_Num - 1) cout << "Effect name incorrect\n";
  }
  if(name_i != -1){
    ifstream inpJson;
    inpJson.open("../aditional_tools/5etools json/spells/spells-all.json");
    if(!inpJson.is_open()) {cout << "Error in opening file\n";}
    else{
      json j;
      j.parse(inpJson);
      for(int i = 0; i < kSpell_Num; i++){
        if(j["spell"]["name"] == E_Spells.name_s[name_i]){
          shape = 0;
          radius[0] = -1;
          radius[1] = -1;
          radius[2] = -1;
          limit[0] = -1;
          limit[1] = -1;
          limit[2] = -1;
          break;
        }
      }
    }
  }
}

Effect::~Effect() = default;

int Effect::Distance_In_Moves(int from_X, int from_Y, int to_X, int to_Y) {
  int distance_i = 0;
  return distance_i;
}