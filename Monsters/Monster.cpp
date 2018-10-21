//
#include "Monster.h"
using json = nlohmann::json;
Monster::Monster(int name_, int challenge_rating_) {
  ifstream MonJson;
  Exsisting_Monsters E_M;
  MonJson.open("../AditionalTools/bestiary-all.json");//TODO: check
  if (MonJson.is_open()) {
    json MonsterJson = json::parse(MonJson);
    for (auto it : MonsterJson) {
      if (it["name"] == E_M.Challenge_rating[challenge_rating_][name_]) {
        monster_name = name_;
        experience_if_killed = it[""];
        size = it[""];
        challenge_rating = challenge_rating_;
        health_dice = it[""];//
        Health_dice_num = it[""];//
        type_s = it["type"];
        subtype = it["subtype"];
        alignment = it["alignment"];
          armor_class = it["armor_class"];
          health = it["hit_points"];
          health_dice = it["hit_dice"];
          Monster_Movement[0] = it["speed"];// check this
          Str = it["strength"];
          Dex = it["dexterity"];
          Con = it["constitution"];
          Int = it["intelligence"];
          Wis = it["wisdom"];
          Cha = it["charisma"];
          for(int o = 0; o < kAbilities_Num; o++){
            /*= it["constitution_save"];
           = it["intelligence_save"];
           = it["wisdom_save"];*/
          }
           for(int l = 0; l < kSkills_Num; l++){
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
  experience_if_killed = another.experience_if_killed;
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