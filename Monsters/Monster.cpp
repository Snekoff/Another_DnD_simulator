//
#include "Monster.h"
using json = nlohmann::json;
Monster::Monster(int name_, int challenge_rating_) {
  ifstream MonJson;
  Exsisting_Monsters E_M;
  MonJson
      .open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/monsters/bestiary-all.json");
  if (MonJson.is_open()) {
    json MonsterJson = json::parse(MonJson);
    saving_throws.resize(kAbilities_Num);
    skillString.resize(kSkills_Num);
    Str = 0; Dex = 0; Con = 0; Int = 0; Wis = 0; Cha = 0;
    for (int i = 0; !MonsterJson["monster"][i]["name"].empty(); i++) {
      // if Challenge raiting unknown - challenge raiting = 30
      if (MonsterJson["monster"][i]["name"] == E_M.Challenge_rating[challenge_rating_][name_]) {
        monster_name = name_;
        auto endPointer = MonsterJson["monster"][i].end();

        size = commonStringParse(MonsterJson["monster"][i], "size");
        challenge_rating = commonStringParse(MonsterJson["monster"][i], "cr");
        // health && formula
        if (MonsterJson["monster"][i].find("hp") != endPointer) {
          health = commonIntParse(MonsterJson["monster"][i]["hp"], "average");
          if(health == 0) cout << "Monster::hp_average not found!\n";
          if (MonsterJson["monster"][i]["hp"].find("formula") != MonsterJson["monster"][i]["hp"].end()) {
            hpFormula = MonsterJson["monster"][i]["hp"]["formula"];
            health_dice = Hp_Formula_Parse(hpFormula, 0);
            health_dice_num = Hp_Formula_Parse(hpFormula, 1);
            health_modifier = Hp_Formula_Parse(hpFormula, 2);
          } else cout << "Monster::hp_formula not found!\n";
        }
        //type
        if (MonsterJson["monster"][i].find("type") != endPointer) {
          type_s = commonStringParse(MonsterJson["monster"][i]["type"], "type");
          if (!type_s.empty()) {
            type_tags = commonVectorStringParse(MonsterJson["monster"][i]["type"], "tags");
          } else type_s = MonsterJson["monster"][i]["type"];
        }

        alignment = commonVectorStringParse(MonsterJson["monster"][i], "alignment");
        //ac
        if (MonsterJson["monster"][i].find("ac") != endPointer) {
          armor_class = commonIntParse(MonsterJson["monster"][i]["ac"], "ac");
          if (armor_class == 0) { armor_class = MonsterJson["monster"][i]["ac"]; }
          else acFrom = commonVectorStringParse(MonsterJson["monster"][i]["ac"], "from");
        }
        // movement speed
        // walk, swim, climb, fly
        if (MonsterJson["monster"][i].find("speed") != endPointer) {
            speed[0] = commonIntParse(MonsterJson["monster"][i]["speed"], "walk");
            speed[1] = commonIntParse(MonsterJson["monster"][i]["speed"], "swim");;
            speed[2] = commonIntParse(MonsterJson["monster"][i]["speed"], "climb");;
          if (MonsterJson["monster"][i]["speed"].find("fly") != MonsterJson["monster"][i]["speed"].end()) {
            speed[3] = commonIntParse(MonsterJson["monster"][i]["speed"]["fly"], "fly");
            if (speed[3] == 0) { speed[3] = MonsterJson["monster"][i]["speed"]["fly"]; }
            fly_condition = commonStringParse(MonsterJson["monster"][i]["speed"]["fly"], "condition");
            canHover = commonBoolParse(MonsterJson["monster"][i]["speed"], "canHover");
          }
        }
        //abilities
        // TODO: check whether it enough to say that all abilities are present
        if (MonsterJson["monster"][i].find("str") != endPointer) {
          Str = MonsterJson["monster"][i]["str"];
          Dex = MonsterJson["monster"][i]["dex"];
          Con = MonsterJson["monster"][i]["con"];
          Int = MonsterJson["monster"][i]["int"];
          Wis = MonsterJson["monster"][i]["wis"];
          Cha = MonsterJson["monster"][i]["cha"];
        }
        //saving throws
        if(MonsterJson["monster"][i].find("save") != endPointer){
          saving_throws[0] = commonStringParse(MonsterJson["monster"][i]["save"], "str");
          saving_throws[1] = commonStringParse(MonsterJson["monster"][i]["save"], "dex");
          saving_throws[2] = commonStringParse(MonsterJson["monster"][i]["save"], "con");
          saving_throws[3] = commonStringParse(MonsterJson["monster"][i]["save"], "int");
          saving_throws[4] = commonStringParse(MonsterJson["monster"][i]["save"], "wis");
          saving_throws[5] = commonStringParse(MonsterJson["monster"][i]["save"], "cha");
        }
        //skill
        if(MonsterJson["monster"][i].find("skill") != endPointer){
          Existing_classes E_C;
          for (int l = 0; l < kSkills_Num; l++) {
            //skill_s = skill name
            skillString[l] = commonStringParse(MonsterJson["monster"][i]["skill"], E_C.skills_s[l]);
          }
        }
        //resistances
        if (MonsterJson["monster"][i].find("resist") != endPointer) {
          for (int j = 0; j < MonsterJson["monster"][i]["resist"].size(); j++) {
            if (MonsterJson["monster"][i]["resist"][j].size() == 1) {
              resistance.push_back(MonsterJson["monster"][i]["resist"][j]);
            } else if (MonsterJson["monster"][i]["resist"][j].find("resist")
                != MonsterJson["monster"][i]["resist"][j].end()) {
              for (int m = 0; m < MonsterJson["monster"][i]["resist"][j].size(); m++) {
                resistance.push_back(MonsterJson["monster"][i]["resist"][j][m]);
              }
              if (MonsterJson["monster"][i]["resist"][j].find("note") != MonsterJson["monster"][i]["resist"][j].end()) {
                for (int m = 0; m < MonsterJson["monster"][i]["resist"][j]["note"].size(); m++) {
                  resistance_note.push_back(MonsterJson["monster"][i]["resist"][j]["note"][m]);
                }
              }
            }
          }
        }
        //others
        passive_perception = commonIntParse(MonsterJson["monster"][i], "passive");
        immune = commonForImmuneAndConditionImmuneAndSensesAndLanguageParse(MonsterJson["monster"][i], "immune");
        conditionImune = commonForImmuneAndConditionImmuneAndSensesAndLanguageParse(MonsterJson["monster"][i], "conditionImmune");
        senses = commonForImmuneAndConditionImmuneAndSensesAndLanguageParse(MonsterJson["monster"][i], "senses");
        languages = commonForImmuneAndConditionImmuneAndSensesAndLanguageParse(MonsterJson["monster"][i], "language");
        trait = commonForTraitAndActionAndSpellNameAndSpellHeaderEntriesAndLegendaryParse(MonsterJson["monster"][i]["trait"],"entries");
        action = commonForTraitAndActionAndSpellNameAndSpellHeaderEntriesAndLegendaryParse(MonsterJson["monster"][i]["action"],"entries");
        legendary = commonForTraitAndActionAndSpellNameAndSpellHeaderEntriesAndLegendaryParse(MonsterJson["monster"][i]["legendary"],"entries");
        spellcastingNameAndEntries = commonForTraitAndActionAndSpellNameAndSpellHeaderEntriesAndLegendaryParse(MonsterJson["monster"][i]["spellcasting"],"headerEntries");
        spellcasting_will = spellcastingWillParse(MonsterJson["monster"][i]["spellcasting"]);
        spellcastDaily = spellcastingDailyParse(MonsterJson["monster"][i]["spellcasting"]);
        isNamedCreature = commonBoolParse(MonsterJson["monster"][i], "isNamedCreature");
        traitTags = commonForImmuneAndConditionImmuneAndSensesAndLanguageParse(MonsterJson["monster"][i], "traitTags");
        actionTags = commonForImmuneAndConditionImmuneAndSensesAndLanguageParse(MonsterJson["monster"][i], "actionTags");
        languageTags = commonForImmuneAndConditionImmuneAndSensesAndLanguageParse(MonsterJson["monster"][i], "languageTags");
        senseTags = commonForImmuneAndConditionImmuneAndSensesAndLanguageParse(MonsterJson["monster"][i], "senseTags");
        legendaryGroup = commonStringParse(MonsterJson["monster"][i], "legendaryGroup");
        legendaryActions = commonIntParse(MonsterJson["monster"][i], "legendaryActions");
        // "" - not needed
        variant = commonVariantParse(MonsterJson["monster"][i], "");
        break;
      }
    }
  } else cout << "error in load MonJson" << endl;
}


Monster::Monster() = default;

Monster::Monster(const Monster &another) {
  saving_throws.resize(kAbilities_Num);
  skillString.resize(kSkills_Num);
  monster_name = another.monster_name;
  size = another.size;
  challenge_rating = another.challenge_rating;
  health = another.health;
  hpFormula = another.hpFormula;
  health_dice = another.health_dice;
  health_dice_num = another.health_dice_num;
  health_modifier = another.health_modifier;
  type_s = another.type_s;
  type_tags = another.type_tags;
  alignment = another.alignment;
  armor_class = another.armor_class;
  acFrom = another.acFrom;
  for(int i = 0; i < kSpeed_types_NUM; i++){
    speed[i] = another.speed[i];
  }
  fly_condition = another.fly_condition;
  canHover = another.canHover;
  Str = another.Str;
  Dex = another.Dex;
  Con = another.Con;
  Int = another.Int;
  Wis = another.Wis;
  Cha = another.Cha;
  for(int i = 0; i < kAbilities_Num; i++){
    saving_throws[i] = another.saving_throws[i];
  }
  for (int i = 0; i < kSkills_Num; i++) {
    skillString[i] = another.skillString[i];
  }
  resistance = another.resistance;
  resistance_note = another.resistance_note;
  passive_perception = another.passive_perception;
  immune = another.immune;
  conditionImune = another.conditionImune;
  senses = another.senses;
  languages = another.languages;
  trait = another.trait;
  action = another.action;
  legendary = another.legendary;
  spellcastingNameAndEntries = another.spellcastingNameAndEntries;
  spellcasting_will = another.spellcasting_will;
  spellcastDaily = another.spellcastDaily;
  isNamedCreature = another.isNamedCreature;
  traitTags = another.traitTags;
  actionTags = another.actionTags;
  languageTags = another.languageTags;
  senseTags = another.senseTags;
  legendaryGroup = another.legendaryGroup;
  legendaryActions = another.legendaryActions;
  variant = another.variant;
}

/*Monster::Monster(int type_, int level_, int hp, int armor_class_) {

}*/

Monster::~Monster() = default;

int Monster::Get(int w) {
  return -1;
}

bool Monster::Load(int *a) {
  return false;
}