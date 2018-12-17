//
#include "Monster.h"
using json = nlohmann::json;
Monster::Monster(int name_, int challenge_rating_) {
  ifstream MonJson;
  Exsisting_Monsters E_M;
  MonJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/monsters/bestiary-all.json");
  if (MonJson.is_open()) {
    json MonsterJson = json::parse(MonJson);
    for (int i = 0; !MonsterJson["monster"][i]["name"].empty(); i++) {
      // if Challenge raiting unknown - challenge raiting = 30
      if (MonsterJson["monster"][i]["name"] == E_M.Challenge_rating[challenge_rating_][name_]) {
        monster_name = name_;
        //experience_if_killed = it[""];
        auto endPointer = MonsterJson["monster"][i].end();
        if (MonsterJson["monster"][i].find("size") != endPointer) size = MonsterJson["monster"][i]["size"];
        challenge_rating = challenge_rating_;
        if (MonsterJson["monster"][i].find("hp") != endPointer){
          if (MonsterJson["monster"][i]["hp"].find("average") != MonsterJson["monster"][i]["hp"].end()) health = MonsterJson["monster"][i]["hp"]["average"];
          else cout << "Monster::hp_average not found!\n";
          if (MonsterJson["monster"][i]["hp"].find("formula") != MonsterJson["monster"][i]["hp"].end()){
            hpFormula = MonsterJson["monster"][i]["hp"]["formula"];
            health_dice = Hp_Formula_Parse(hpFormula, 0);
            health_dice_num = Hp_Formula_Parse(hpFormula, 1);
            health_modifier = Hp_Formula_Parse(hpFormula, 2);
          }
          else cout << "Monster::hp_formula not found!\n";
        }
        if (MonsterJson["monster"][i].find("type") != endPointer){
          if(MonsterJson["monster"][i]["type"].find("type") != MonsterJson["monster"][i]["type"].end()){
            type_s = MonsterJson["monster"][i]["type"]["type"];
            if(MonsterJson["monster"][i]["type"].find("tags") != MonsterJson["monster"][i]["type"].end()){
              for(int j = 0; j < MonsterJson["monster"][i]["type"]["tags"].size(); j++){
                type_tags.push_back(MonsterJson["monster"][i]["type"]["tags"][j]);
              }
            }
          } else type_s = MonsterJson["monster"][i]["type"];
        }
        if(MonsterJson["monster"][i].find("alignment") != endPointer){
          for(int j = 0; j < MonsterJson["monster"][i]["alignment"].size(); j++){
            alignment.push_back(MonsterJson["monster"][i]["alignment"][j]);
          }
        }
        if(MonsterJson["monster"][i].find("ac") != endPointer){
          if(MonsterJson["monster"][i]["ac"].find("ac") != MonsterJson["monster"][i]["ac"].end()){
            armor_class = MonsterJson["monster"][i]["ac"]["ac"];
          } else armor_class = MonsterJson["monster"][i]["ac"];
          if(MonsterJson["monster"][i]["ac"].find("from") != MonsterJson["monster"][i]["ac"].end()){
            for(int j = 0; j < MonsterJson["monster"][i]["type"]["tags"].size(); j++){
              acFrom.push_back(MonsterJson["monster"][i]["ac"]["from"][j]);
            }
          }
        }
        // walk, swim, climb, fly
        if(MonsterJson["monster"][i].find("speed") != endPointer){
          if(MonsterJson["monster"][i]["speed"].find("walk") != MonsterJson["monster"][i]["speed"].end()){
            speed[0] = MonsterJson["monster"][i]["speed"]["walk"];
          }
          if(MonsterJson["monster"][i]["speed"].find("swim") != MonsterJson["monster"][i]["speed"].end()){
            speed[1] = MonsterJson["monster"][i]["speed"]["swim"];
          }
          if(MonsterJson["monster"][i]["speed"].find("climb") != MonsterJson["monster"][i]["speed"].end()){
            speed[2] = MonsterJson["monster"][i]["speed"]["climb"];
          }
          if(MonsterJson["monster"][i]["speed"].find("fly") != MonsterJson["monster"][i]["speed"].end()){
            if(MonsterJson["monster"][i]["speed"]["fly"].find("fly") != MonsterJson["monster"][i]["speed"]["fly"].end()){
              speed[3] = MonsterJson["monster"][i]["speed"]["fly"]["fly"];
            } else speed[3] = MonsterJson["monster"][i]["speed"]["fly"];
            if(MonsterJson["monster"][i]["speed"]["fly"].find("condition") != MonsterJson["monster"][i]["speed"]["fly"].end()){
              fly_condition = MonsterJson["monster"][i]["speed"]["fly"]["condition"];
            }
            if(MonsterJson["monster"][i]["speed"].find("canHover") != MonsterJson["monster"][i]["speed"].end()){
              canHover = MonsterJson["monster"][i]["speed"]["canHover"];
            }
          }
        }
        if(MonsterJson["monster"][i].find("str") != endPointer){ // TODO: check whether it enough to say that all abilities are present
          Str = MonsterJson["monster"][i]["str"];
          Dex = MonsterJson["monster"][i]["dex"];
          Con = MonsterJson["monster"][i]["con"];
          Int = MonsterJson["monster"][i]["int"];
          Wis = MonsterJson["monster"][i]["wis"];
          Cha = MonsterJson["monster"][i]["cha"];
        }
        /*
         "save": {
				"wis": "+8"
        }
         */
        for (int o = 0; o < kAbilities_Num; o++) {
          /*= it["constitution_save"];
         = it["intelligence_save"];
         = it["wisdom_save"];*/
        }
        for (int l = 0; l < kSkills_Num; l++) {
          /* = it["history"];
        = it["perception"];*/
        }
        if(MonsterJson["monster"][i].find("resist") != endPointer){
          for(int j = 0; j < MonsterJson["monster"][i]["resist"].size(); j++){
            if(MonsterJson["monster"][i]["resist"][j].size() == 1){
              resistance.push_back(MonsterJson["monster"][i]["resist"][j]);
            } else if(MonsterJson["monster"][i]["resist"][j].find("resist") != MonsterJson["monster"][i]["resist"][j].end()){
              for(int m = 0; m < MonsterJson["monster"][i]["resist"][j].size(); m++){
                resistance.push_back(MonsterJson["monster"][i]["resist"][j][m]);
              }
              if(MonsterJson["monster"][i]["resist"][j].find("note") != MonsterJson["monster"][i]["resist"][j].end()){
                for(int m = 0; m < MonsterJson["monster"][i]["resist"][j]["note"].size(); m++){
                  resistance_note.push_back(MonsterJson["monster"][i]["resist"][j]["note"][m]);
                }
              }
            }
          }
        }
        if(MonsterJson["monster"][i].find("immune") != endPointer){
          for(int j = 0; j < MonsterJson["monster"][i]["immune"].size(); j++){
            immune.push_back(MonsterJson["monster"][i]["immune"][j]);
          }
        }
        if(MonsterJson["monster"][i].find("conditionImmune") != endPointer){
          for(int j = 0; j < MonsterJson["monster"][i]["conditionImmune"].size(); j++){
            conditionImune.push_back(MonsterJson["monster"][i]["conditionImmune"][j]);
          }
        }
        if(MonsterJson["monster"][i].find("senses") != endPointer){
          for(int j = 0; j < MonsterJson["monster"][i]["senses"].size(); j++){
            senses.push_back(MonsterJson["monster"][i]["senses"][j]);
          }
        }
        if(MonsterJson["monster"][i].find("passive") != endPointer){
          passive_perception = MonsterJson["monster"][i]["passive"];
        }
        if(MonsterJson["monster"][i].find("languages") != endPointer){
          for(int j = 0; j < MonsterJson["monster"][i]["languages"].size(); j++){
            languages.push_back(MonsterJson["monster"][i]["languages"][j]);
          }
        }
        trait = commonForTraitAndActionAndSpellNameAndSpellHeaderEntriesAndLegendaryParse(MonsterJson["monster"][i]["trait"], "entries");
        action = commonForTraitAndActionAndSpellNameAndSpellHeaderEntriesAndLegendaryParse(MonsterJson["monster"][i]["action"], "entries");
        legendary = commonForTraitAndActionAndSpellNameAndSpellHeaderEntriesAndLegendaryParse(MonsterJson["monster"][i]["legendary"], "entries");
        spellcastingNameAndEntries = commonForTraitAndActionAndSpellNameAndSpellHeaderEntriesAndLegendaryParse(MonsterJson["monster"][i]["spellcasting"], "headerEntries");
        spellcasting_will = spellcastingWillParse();
        spellcastDaily = spellcastingDailyParse();
        break;
      }
    }
  } else cout << "error in load MonJson" << endl;
}

Monster::Monster() = default;

Monster::Monster(const Monster &another) {
  monster_name = another.monster_name;
  //experience_if_killed = another.experience_if_killed;
  size = another.size;
  challenge_rating = another.challenge_rating;
  health_dice = another.health_dice;
  health_dice_num = another.health_dice_num;
}

Monster::Monster(int type_, int level_, int hp, int armor_class_) {

}

Monster::~Monster() = default;

int Monster::Get(int w) {
  return -1;
}

bool Monster::Load(int *a) {
  return false;
}