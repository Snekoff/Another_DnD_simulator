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

vector <string> Creature::spellcastingWillParse(const nlohmann::basic_json<> &j) {
  vector <string> Spellcastings;
  if(j.find("will") == j.end()) return Spellcastings;
  for(int k = 0; k < j["will"].size(); k++){
    Spellcastings.push_back(j["will"][k]);
  }
  return Spellcastings;
}

vector <SpellAndUsageTimes> Creature::spellcastingDailyParse(const nlohmann::basic_json<> &j) {
  vector <SpellAndUsageTimes> Spellcastings;
  if(j.find("daily") == j.end()) return Spellcastings;
  auto endPointer = j["daily"].end();
  vector <string> TimesPerDay = {"1", "1e", "2", "2e", "3", "3e"};
  for(int l = 0; l < TimesPerDay.size();l++){
    if(j["daily"].find(TimesPerDay[l]) != endPointer){
      for(int k = 0; k < j["daily"][TimesPerDay[l]].size(); k++){
        SpellAndUsageTimes spellAndUsageTimes;
        spellAndUsageTimes.spellName = j["daily"][TimesPerDay[l]][k];
        spellAndUsageTimes.maxCharges = 1;
        spellAndUsageTimes.Charges = spellAndUsageTimes.maxCharges;
        Spellcastings.push_back(spellAndUsageTimes);
      }
    }
  }
  return Spellcastings;
}

vector <string> Creature::commonForTraitAndActionAndSpellNameAndSpellHeaderEntriesAndLegendaryParse(const nlohmann::basic_json<> &j, string howEntriesNamed) {
  vector <string> outVectorString;
  for(int m = 0; m < j.size(); m++){
    if(j[m].find("name") != j[m].end()) {
      string actionName = "name: ";
      actionName += j[m]["name"];
      outVectorString.push_back(actionName);
    }
    if(j[m].find(howEntriesNamed) != j[m].end()){
      for(int r = 0; r < j[m][howEntriesNamed].size(); r++){
        outVectorString.push_back(j[m][howEntriesNamed][r]);
      }
    }
  }
  return outVectorString;
}

vector<string> Creature::commonForImmuneAndConditionImmuneAndSensesAndLanguageParse(const nlohmann::basic_json<> &MonsterJson, string whatAreLookedFor) {
  vector<string> whatAreLookedForOutput;
  if (MonsterJson.find(whatAreLookedFor) != MonsterJson.end()) {
    for (int j = 0; j < MonsterJson[whatAreLookedFor].size(); j++) {
      whatAreLookedForOutput.push_back(MonsterJson[whatAreLookedFor][j]);
    }
  }
  return whatAreLookedForOutput;
}

vector<string> Creature::commonVariantParse(const nlohmann::basic_json<> &MonsterJson, string whatAreLookedFor) {
  vector <string> outVector;
  if(MonsterJson.find("variant") == MonsterJson.end()) return outVector;
  for(int i = 0; i < MonsterJson["variant"].size(); i++){
    if(MonsterJson["variant"].find("type") != MonsterJson["variant"].end()){
      string outType = "type: ";
      outType += MonsterJson["variant"]["type"];
      outVector.push_back(outType);
    }
    if(MonsterJson["variant"].find("name") != MonsterJson["variant"].end()){
      string outType = "name: ";
      outType += MonsterJson["variant"]["name"];
      outVector.push_back(outType);
    }
    if(MonsterJson["variant"].find("entries") != MonsterJson["variant"].end()){
      vector <string> entries;
      auto fakeItem = new Item();
      entries = fakeItem->Entries_Parse(MonsterJson["variant"]);
      for(int j = 0; j < entries.size(); j++){
        outVector.push_back(entries[j]);
      }
      delete fakeItem;
    }
  }
  return outVector;
}

vector<string> Creature::commonVectorStringParse(const nlohmann::basic_json<> &MonsterJson, string whatAreLookedFor) {
  vector<string> Output;
  if(MonsterJson.find(whatAreLookedFor) == MonsterJson.end()) return Output;
  for(int i = 0; i < MonsterJson[whatAreLookedFor].size(); i++){
    Output.push_back(MonsterJson[whatAreLookedFor][i]);
  }
  return Output;
}

string Creature::commonStringParse(const nlohmann::basic_json<> &MonsterJson, string whatAreLookedFor) {
  string Output;
  if(MonsterJson.find(whatAreLookedFor) == MonsterJson.end()) return Output;
  Output = MonsterJson[whatAreLookedFor];
  return Output;
}

int Creature::commonIntParse(const nlohmann::basic_json<> &MonsterJson, string whatAreLookedFor) {
  int Output;
  if(MonsterJson.find(whatAreLookedFor) == MonsterJson.end()) return Output;
  Output = MonsterJson[whatAreLookedFor];
  return Output;
}

bool Creature::commonBoolParse(const nlohmann::basic_json<> &MonsterJson, string whatAreLookedFor) {
  bool Output;
  if(MonsterJson.find(whatAreLookedFor) == MonsterJson.end()) return Output;
  Output = MonsterJson[whatAreLookedFor];
  return Output;
}