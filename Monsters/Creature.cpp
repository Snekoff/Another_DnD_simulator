#include "Creature.h"

int Creature::Hp_Formula_Parse(string hpFormula_, int returnHitDiceOrNumOfDices) {
  if(hpFormula_.empty()) return -1;
  string hpFormula_Parsing;
  int health_dice_num_ = 0;
  int health_dice_ = 0;
  int health_modifier_ = 0;
  for(int j = 0; j < hpFormula_.length(); j++){
    if((int)hpFormula_[j] >= (int)'0' && (int)hpFormula_[j] <= (int)'9'){
      hpFormula_Parsing += hpFormula_[j];
    } else if(hpFormula_[j] == 'd'){
      health_dice_num_ = stoi(hpFormula_Parsing);
      hpFormula_Parsing.clear();
    } else if(hpFormula_[j] == ' '){
      health_dice_ = stoi(hpFormula_Parsing);
      hpFormula_Parsing.clear();
    } else if(hpFormula_[j] == '+'){
      for(int i = j + 2; i < hpFormula_.length(); i++){
        hpFormula_Parsing += hpFormula_[i];
      }
      health_modifier_ = stoi(hpFormula_Parsing);
    }
  }
  if(returnHitDiceOrNumOfDices == 0) return health_dice_;
  else if(returnHitDiceOrNumOfDices == 1) return health_dice_num_;
  else return health_modifier_;
}
