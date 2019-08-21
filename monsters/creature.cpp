#include "creature.h"

int Creature::Hp_Formula_Parse(string hpFormula_, int returnHitDiceOrNumOfDicesOrHealthModifier) {
  if(hpFormula_.empty()) return -1;
  string hpFormula_Parsing;
  int health_dice_num_ = 0;
  int health_dice_ = 0;
  int health_modifier_ = 0;
  for(int j = 0; j < hpFormula_.length(); j++){
    if((int)hpFormula_[j] >= (int)'0' && (int)hpFormula_[j] <= (int)'9'){
      hpFormula_Parsing += hpFormula_[j];
      if(j == hpFormula_.length() - 1) health_dice_ = stoi(hpFormula_Parsing);
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
      break;
    }
  }
  if(returnHitDiceOrNumOfDicesOrHealthModifier == 0) return health_dice_;
  else if(returnHitDiceOrNumOfDicesOrHealthModifier == 1) return health_dice_num_;
  else return health_modifier_;
}

int Creature::HealthRoll(Random_Generator_ *Rand_gen, int hitDice, int numOfDices) {
  int health_ = 0;
  for(int i = 0; i < numOfDices; i++){
    health_ += Rand_gen->Rand(1, hitDice);
  }
  return health_;
}

int Creature::AbilityModifier(int ability_) {
  return (ability_ - 10) / 2;
}

vector <vector <string>> Creature::spellsParse(const nlohmann::basic_json<> &j, string whatAreLookedFor) {
  vector <vector <string>> Spellcasting;
  // Maximum spell level is 10
  Spellcasting.resize(kSpellMaxLevel);
  if(j.find(whatAreLookedFor) == j.end()) return Spellcasting;
  auto endPointer = j[whatAreLookedFor].end();
  //Kantrip is zero level spell
  vector <string> SpellLevel = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
  for(int l = 0; l < SpellLevel.size();l++){
    if(j[whatAreLookedFor].find(SpellLevel[l]) != endPointer){
      for(int k = 0; k < j[whatAreLookedFor][SpellLevel[l]][whatAreLookedFor].size(); k++){
        Spellcasting[l].push_back(j[whatAreLookedFor][SpellLevel[l]][whatAreLookedFor][k]);
      }
    }
  }
  return Spellcasting;
}

vector <int> Creature::spellSlotsParse(const nlohmann::basic_json<> &j, string whatAreLookedFor) {
  vector <int> SpellSlots;
  // Maximum spell level is 10
  SpellSlots.resize(kSpellMaxLevel);
  if(j.find(whatAreLookedFor) == j.end()) return SpellSlots;
  auto endPointer = j[whatAreLookedFor].end();
  //Kantrip is zero level spell
  vector <string> SpellLevel = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
  for(int l = 0; l < SpellLevel.size();l++){
    if (j[whatAreLookedFor].find(SpellLevel[l]) != endPointer) {
      SpellSlots[l] = j[whatAreLookedFor][SpellLevel[l]]["slots"];
    }
  }
  return SpellSlots;
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
        spellAndUsageTimes.spell_name = j["daily"][TimesPerDay[l]][k];
        spellAndUsageTimes.max_charges = 1;
        spellAndUsageTimes.charges = spellAndUsageTimes.max_charges;
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
  vector<string> Output;
  vector<string> Output_Second_Level;
  if (MonsterJson.find(whatAreLookedFor) != MonsterJson.end()) {
    //cout << "MonsterJson[whatAreLookedFor].size() = " << MonsterJson[whatAreLookedFor].size() << endl;
    if(MonsterJson[whatAreLookedFor].size() == 1){
      Output.push_back(MonsterJson[whatAreLookedFor]);
      return Output;
    }
    for (int j = 0; j < MonsterJson[whatAreLookedFor].size(); j++) {
       if(MonsterJson[whatAreLookedFor][j].size() == 1){
        Output.push_back(MonsterJson[whatAreLookedFor][j]);
        //cout << "MonsterJson[whatAreLookedFor][j] " << MonsterJson[whatAreLookedFor][j] << endl;
      } else {
        Output_Second_Level = commonForImmuneAndConditionImmuneAndSensesAndLanguageParse(MonsterJson[j], whatAreLookedFor);
        if(MonsterJson[whatAreLookedFor][j].find("note") != MonsterJson[whatAreLookedFor][j].end()) Output_Second_Level.push_back(MonsterJson[whatAreLookedFor][j]["note"]);
        for(int l = 0; l < Output_Second_Level.size(); l++){
          //cout << "Output_Second_Level[l] pushed_back" << Output_Second_Level[l] << endl;
          Output.push_back(Output_Second_Level[l]);
        }
      }
      //Output.push_back(MonsterJson[whatAreLookedFor][j]);
    }
  }
  return Output;
}

vector<string> Creature::ImmuneParse(const nlohmann::basic_json<> &MonsterJson, string whatAreLookedFor) {
  vector<string> Output;
  if (MonsterJson.find(whatAreLookedFor) != MonsterJson.end()) {
    for (int j = 0; j < MonsterJson[whatAreLookedFor].size(); j++) {
      if(MonsterJson[whatAreLookedFor][j].size() == 1) Output.push_back(MonsterJson[whatAreLookedFor][j]);
      else {
        if(MonsterJson[whatAreLookedFor][j].find(whatAreLookedFor) != MonsterJson[whatAreLookedFor][j].end()){
          for(int l = 0; l < MonsterJson[whatAreLookedFor][j][whatAreLookedFor].size(); l++){
            if(MonsterJson[whatAreLookedFor][j][whatAreLookedFor].size() == 1) Output.push_back(MonsterJson[whatAreLookedFor][j][whatAreLookedFor]);
            else Output.push_back(MonsterJson[whatAreLookedFor][j][whatAreLookedFor][l]);
          }
        }
      }
    }
  }
  return Output;
}

vector<string> Creature::commonForAllTagsParse(const nlohmann::basic_json<> &MonsterJson, string whatAreLookedFor) {
  vector<string> Output;
  if(MonsterJson.find(whatAreLookedFor) != MonsterJson.end()) return Output;
  for(int i = 0; !MonsterJson[whatAreLookedFor][i].empty();i++){
    Output.push_back(MonsterJson[whatAreLookedFor][i]);
  }
  return Output;
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
  int Output = 0;
  if(MonsterJson.find(whatAreLookedFor) == MonsterJson.end() || !MonsterJson[whatAreLookedFor].is_number()) return Output;
  Output = MonsterJson[whatAreLookedFor];
  return Output;
}

bool Creature::commonBoolParse(const nlohmann::basic_json<> &MonsterJson, string whatAreLookedFor) {
  bool Output = false;
  if(MonsterJson.find(whatAreLookedFor) == MonsterJson.end()) return Output;
  Output = MonsterJson[whatAreLookedFor];
  return Output;
}