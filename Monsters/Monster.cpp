//
#include "Monster.h"
using json = nlohmann::json;
Monster::Monster(int name_, int challenge_rating_) {
  ifstream MonJson;
  Exsisting_Monsters E_M;
  MonJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/monsters/bestiary-all.json");
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
          if (MonsterJson["monster"][i]["hp"].find("average") != endPointer) health = MonsterJson["monster"][i]["hp"]["average"];
          else cout << "Monster::hp_average not found!\n";
          if (MonsterJson["monster"][i]["hp"].find("formula") != endPointer){
            hpFormula = MonsterJson["monster"][i]["hp"]["formula"];
            health_dice = Hp_Formula_Parse(hpFormula, 0);
            health_dice_num = Hp_Formula_Parse(hpFormula, 1);
            health_modifier = Hp_Formula_Parse(hpFormula, 2);
          }
          else cout << "Monster::hp_formula not found!\n";
        }
        //health_dice = it[""];
        //health_dice = it["hit_dice"];
        //Health_dice_num = it[""];//
        //type_s = it["type"];
        //subtype = it["subtype"];
        //alignment = it["alignment"];
        //armor_class = it["armor_class"];
        //
        //
        //speed[0] = it["speed"];// check this
        /*Str = it["strength"];
        Dex = it["dexterity"];
        Con = it["constitution"];
        Int = it["intelligence"];
        Wis = it["wisdom"];
        Cha = it["charisma"];*/
        for (int o = 0; o < kAbilities_Num; o++) {
          /*= it["constitution_save"];
         = it["intelligence_save"];
         = it["wisdom_save"];*/
        }
        for (int l = 0; l < kSkills_Num; l++) {
          /* = it["history"];
        = it["perception"];*/
        }

        //= it["damage_vulnerabilities"];
        //= it["damage_resistances"];
        //= it["damage_immunities"];
        //= it["condition_immunities"];
        //= it["senses"];
        //= it["languages"];
        /*= it["challenge_rating"];*/

        break;
      }
    }
  } else cout << "error in load MonJson" << endl;
}

Monster::Monster(const Monster &another) {
  monster_name = another.monster_name;
  //experience_if_killed = another.experience_if_killed;
  size = another.size;
  challenge_rating = another.challenge_rating;
  health_dice = another.health_dice;
  Health_dice_num = another.Health_dice_num;
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