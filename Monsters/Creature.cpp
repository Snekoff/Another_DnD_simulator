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

vector <string> Creature::traitParse(const nlohmann::basic_json<> &j, int i) {
  vector <string> traits;
  if(j["monster"][i].find("trait") == j["monster"][i].end()) return traits;
  for(int m = 0; m < j["monster"][i]["trait"].size(); m++){
    if(j["monster"][i]["trait"][m].find("name") != j["monster"][i]["trait"][m].end()) {
      string traitName = "name";
      traits.push_back(traitName);
      traits.push_back(j["monster"][i]["trait"][m]["name"]);
    }
    if(j["monster"][i]["trait"][m].find("entries") != j["monster"][i]["trait"][m].end()){
      string traitEntries = "entries:";
      traits.push_back(traitEntries);
      for(int r = 0; r < j["monster"][i]["trait"][m]["entries"].size(); r++){
        traits.push_back(j["monster"][i]["trait"][m]["entries"][r]);
      }
    }
  }
  return traits;
}

vector <string> Creature::actionParse(const nlohmann::basic_json<> &j, int i) {
  vector <string> actions;
  if(j["monster"][i].find("action") == j["monster"][i].end()) return actions;
  for(int m = 0; m < j["monster"][i]["action"].size(); m++){
    if(j["monster"][i]["action"][m].find("name") != j["monster"][i]["action"][m].end()) {
      string actionName = "name";
      actions.push_back(actionName);
      actions.push_back(j["monster"][i]["action"][m]["name"]);
    }
    if(j["monster"][i]["action"][m].find("entries") != j["monster"][i]["action"][m].end()){
      string actionEntries = "entries:";
      actions.push_back(actionEntries);
      for(int r = 0; r < j["monster"][i]["action"][m]["entries"].size(); r++){
        actions.push_back(j["monster"][i]["action"][m]["entries"][r]);
      }
    }
  }
  return actions;
}

vector <string> Creature::spellcastingNameAndHeaderEntriesParse(const nlohmann::basic_json<> &j, int i) {
  vector <string> Spellcastings;
  if(j["monster"][i].find("Spellcasting") == j["monster"][i].end()) return Spellcastings;
  for(int m = 0; m < j["monster"][i]["Spellcasting"].size(); m++){
    if(j["monster"][i]["Spellcasting"][m].find("name") != j["monster"][i]["Spellcasting"][m].end()) {
      string SpellcastingName = "name";
      Spellcastings.push_back(SpellcastingName);
      Spellcastings.push_back(j["monster"][i]["Spellcasting"][m]["name"]);
    }
    if(j["monster"][i]["Spellcasting"][m].find("headerEntries") != j["monster"][i]["Spellcasting"][m].end()){
      string SpellcastingEntries = "headerEntries:";
      Spellcastings.push_back(SpellcastingEntries);
      for(int r = 0; r < j["monster"][i]["Spellcasting"][m]["headerEntries"].size(); r++){
        Spellcastings.push_back(j["monster"][i]["Spellcasting"][m]["headerEntries"][r]);
      }
    }
  }
  return Spellcastings;
}

vector <string> Creature::spellcastingWillParse(const nlohmann::basic_json<> &j, int i) {
  vector <string> Spellcastings;
  if(j["monster"][i]["Spellcasting"].find("will") == j["monster"][i]["Spellcasting"].end()) return Spellcastings;
  for(int k = 0; k < j["monster"][i]["Spellcasting"]["will"].size(); k++){
    Spellcastings.push_back(j["monster"][i]["Spellcasting"]["will"][k]);
  }
  return Spellcastings;
}

vector <SpellAndUsageTimes> Creature::spellcastingDailyParse(const nlohmann::basic_json<> &j, int i) {
  vector <SpellAndUsageTimes> Spellcastings;
  if(j["monster"][i]["Spellcasting"].find("daily") == j["monster"][i]["Spellcasting"].end()) return Spellcastings;
  auto endPointer = j["monster"][i]["Spellcasting"]["daily"].end();
  vector <string> TimesPerDay = {"1", "1e", "2", "2e", "3", "3e", ""};
  for(int l = 0; l < TimesPerDay.size();l++){
    if(j["monster"][i]["Spellcasting"]["daily"].find(TimesPerDay[l]) != endPointer){
      for(int k = 0; k < j["monster"][i]["Spellcasting"]["daily"][TimesPerDay[l]].size(); k++){
        SpellAndUsageTimes spellAndUsageTimes;
        spellAndUsageTimes.spellName = j["monster"][i]["Spellcasting"]["daily"][TimesPerDay[l]][k];
        spellAndUsageTimes.maxCharges = 1;
        spellAndUsageTimes.Charges = spellAndUsageTimes.maxCharges;
        Spellcastings.push_back(spellAndUsageTimes);
      }
    }
  }
  /*if(j["monster"][i]["Spellcasting"]["daily"].find("1") != endPointer){
    for(int k = 0; k < j["monster"][i]["Spellcasting"]["daily"]["1"].size(); k++){
      SpellAndUsageTimes spellAndUsageTimes;
      spellAndUsageTimes.spellName = j["monster"][i]["Spellcasting"]["daily"]["1"][k];
      spellAndUsageTimes.maxCharges = 1;
      spellAndUsageTimes.Charges = spellAndUsageTimes.maxCharges;
      Spellcastings.push_back(spellAndUsageTimes);
    }
  }
  if(j["monster"][i]["Spellcasting"]["daily"].find("1e") != endPointer){

  }
  if(j["monster"][i]["Spellcasting"]["daily"].find("2") != endPointer){

  }
  if(j["monster"][i]["Spellcasting"]["daily"].find("2e") != endPointer){

  }
  if(j["monster"][i]["Spellcasting"]["daily"].find("3") != endPointer){

  }
  if(j["monster"][i]["Spellcasting"]["daily"].find("3e") != endPointer){

  }*/

}

vector <string> Creature::legendaryParse(const nlohmann::basic_json<> &j, int i) {
  vector <string> legendarys;
  if(j["monster"][i].find("legendary") == j["monster"][i].end()) return legendarys;
  for(int m = 0; m < j["monster"][i]["legendary"].size(); m++){
    if(j["monster"][i]["legendary"][m].find("name") != j["monster"][i]["legendary"][m].end()) {
      string legendaryName = "name";
      legendarys.push_back(legendaryName);
      legendarys.push_back(j["monster"][i]["legendary"][m]["name"]);
    }
    if(j["monster"][i]["legendary"][m].find("entries") != j["monster"][i]["legendary"][m].end()){
      string legendaryEntries = "entries:";
      legendarys.push_back(legendaryEntries);
      for(int r = 0; r < j["monster"][i]["legendary"][m]["entries"].size(); r++){
        legendarys.push_back(j["monster"][i]["legendary"][m]["entries"][r]);
      }
    }
  }
  return legendarys;
}

vector <string> Creature::commonEverythingParse(const nlohmann::basic_json<> &j) {
  vector <string> TraitActSpell;
  for(int m = 0; m < j.size(); m++){
    if(j[m].find("name") != j[m].end()) {
      string actionName = "name";
      TraitActSpell.push_back(actionName);
      TraitActSpell.push_back(j[m]["name"]);
    }
    if(j[m].find("entries") != j[m].end()){
      string actionEntries = "entries:";
      TraitActSpell.push_back(actionEntries);
      for(int r = 0; r < j[m]["entries"].size(); r++){
        TraitActSpell.push_back(j[m]["entries"][r]);
      }
    }
  }
  return TraitActSpell;
}
