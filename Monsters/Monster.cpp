//
#include "Monster.h"
using json = nlohmann::json;
Monster::Monster(Random_Generator_ *Rand_gen, int name_index, int challenge_rating_index) {
  ifstream MonJson;
  Existing_Monsters E_M;
  E_M.fakeParameter = 1;
  cout << "Control reach Monster::Constructor 0\n";
  //MonJson.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/AditionalTools/5etools json/monsters/bestiary-all.json");
  MonJson.open("../AditionalTools/5etools json/monsters/bestiary-all.json");
  if (MonJson.is_open()) {
    cout << "Control reach Monster::Constructor 1\n";
    json MonsterJson = json::parse(MonJson);
    saving_throws.resize(kAbilities_Num);
    skillString.resize(kSkills_Num);
    Str = 0;
    Dex = 0;
    Con = 0;
    Int = 0;
    Wis = 0;
    Cha = 0;
    armor_class = 0;

    //!MonsterJson["monster"][i]["name"].empty()

    for (int i = 0; MonsterJson["monster"][i].find("name") != MonsterJson["monster"][i].end(); i++) {
      //Challenge rating unknown is challenge rating = 30
      if(challenge_rating_index < 0 || challenge_rating_index > E_M.Challenge_rating.size() ||
          name_index < 0 || name_index > E_M.Challenge_rating[challenge_rating_index].size()){
        cout << "wrong challenge_rating_index or name_index in Monster.cpp Monster::Constructor\n";
        break;
      }
      if (MonsterJson["monster"][i]["name"] == E_M.Challenge_rating[challenge_rating_index][name_index]) {
        cout << "Control reach Monster::Constructor 2\n";
        monster_name = commonStringParse(MonsterJson["monster"][i], "name");
        auto endPointer = MonsterJson["monster"][i].end();
        size = commonStringParse(MonsterJson["monster"][i], "size");
        challenge_rating = commonStringParse(MonsterJson["monster"][i], "cr");
        cout << "Control reach Monster::Constructor 3\n";
        // maxhealth && formula
        if (MonsterJson["monster"][i].find("hp") != endPointer) {
          maxhealth = commonIntParse(MonsterJson["monster"][i]["hp"], "average");
          if (maxhealth == 0) cout << "----->Monster::hp_average not found!\n";
          if (MonsterJson["monster"][i]["hp"].find("formula") != MonsterJson["monster"][i]["hp"].end()) {
            hpFormula = MonsterJson["monster"][i]["hp"]["formula"];
            health_dice = Hp_Formula_Parse(hpFormula, 0);
            health_dice_num = Hp_Formula_Parse(hpFormula, 1);
            health_modifier = Hp_Formula_Parse(hpFormula, 2);
          } else cout << "Monster hp_formula not found!\n";
        }
        cout << "Control reach Monster::Constructor 4\n";
        //type
        if (MonsterJson["monster"][i].find("type") != endPointer) {
          type_s = commonStringParse(MonsterJson["monster"][i]["type"], "type");
          if (!type_s.empty()) {
            type_tags = commonVectorStringParse(MonsterJson["monster"][i]["type"], "tags");
          } else type_s = commonStringParse(MonsterJson["monster"][i], "type");
        }
        cout << "Control reach Monster::Constructor 5\n";
        alignment = commonVectorStringParse(MonsterJson["monster"][i], "alignment");
        //ac
        if (MonsterJson["monster"][i].find("ac") != endPointer) {
          armor_class = commonIntParse(MonsterJson["monster"][i]["ac"][0], "ac");
          if (armor_class < 0 || armor_class > 100) { armor_class = MonsterJson["monster"][i]["ac"]; }
          else acFrom = commonVectorStringParse(MonsterJson["monster"][i]["ac"][0], "from");
        }
        cout << "Control reach Monster::Constructor 6\n";
        // movement speed
        // walk, swim, climb, fly
        if (MonsterJson["monster"][i].find("speed") != endPointer) {
          speed[3] = 0;
          speed[0] = commonIntParse(MonsterJson["monster"][i]["speed"], "walk");
          speed[1] = commonIntParse(MonsterJson["monster"][i]["speed"], "swim");;
          speed[2] = commonIntParse(MonsterJson["monster"][i]["speed"], "climb");;
          if (MonsterJson["monster"][i]["speed"].find("fly") != MonsterJson["monster"][i]["speed"].end()) {
            speed[3] = commonIntParse(MonsterJson["monster"][i]["speed"]["fly"], "fly");
            if (speed[3] == 0) { speed[3] = commonIntParse(MonsterJson["monster"][i]["speed"], "fly"); }
            fly_condition = commonStringParse(MonsterJson["monster"][i]["speed"]["fly"], "condition");
            canHover = commonBoolParse(MonsterJson["monster"][i]["speed"], "canHover");
          }
        }
        cout << "Control reach Monster::Constructor 7\n";
        //abilities
        Str = commonIntParse(MonsterJson["monster"][i], "str");
        Dex = commonIntParse(MonsterJson["monster"][i], "dex");
        Con = commonIntParse(MonsterJson["monster"][i], "con");
        Int = commonIntParse(MonsterJson["monster"][i], "int");
        Wis = commonIntParse(MonsterJson["monster"][i], "wis");
        Cha = commonIntParse(MonsterJson["monster"][i], "cha");
        cout << "Control reach Monster::Constructor 7\n";
        //saving throws
        if (MonsterJson["monster"][i].find("save") != endPointer) {
          saving_throws[0] = commonStringParse(MonsterJson["monster"][i]["save"], "str");
          saving_throws[1] = commonStringParse(MonsterJson["monster"][i]["save"], "dex");
          saving_throws[2] = commonStringParse(MonsterJson["monster"][i]["save"], "con");
          saving_throws[3] = commonStringParse(MonsterJson["monster"][i]["save"], "int");
          saving_throws[4] = commonStringParse(MonsterJson["monster"][i]["save"], "wis");
          saving_throws[5] = commonStringParse(MonsterJson["monster"][i]["save"], "cha");
        }
        cout << "Control reach Monster::Constructor 8\n";
        //skill
        if (MonsterJson["monster"][i].find("skill") != endPointer) {
          Existing_classes E_C;
          for (int l = 0; l < kSkills_Num; l++) {
            //skill_s = skill name
            skillString[l] = commonStringParse(MonsterJson["monster"][i]["skill"], E_C.skills_s[l]);
          }
        }
        cout << "Control reach Monster::Constructor 9\n";
        //resistances
        if (MonsterJson["monster"][i].find("resist") != endPointer) {
          for (int j = 0; j < MonsterJson["monster"][i]["resist"].size(); j++) {
            if (MonsterJson["monster"][i]["resist"][j].size() == 1) {
              resistance.push_back(MonsterJson["monster"][i]["resist"][j]);
            } else if (MonsterJson["monster"][i]["resist"][j].find("resist") != MonsterJson["monster"][i]["resist"][j].end()) {
              for (int m = 0; m < MonsterJson["monster"][i]["resist"][j]["resist"].size(); m++) {
                resistance.push_back(MonsterJson["monster"][i]["resist"][j]["resist"][m]);
              }
              if (MonsterJson["monster"][i]["resist"][j].find("note") != MonsterJson["monster"][i]["resist"][j].end()) {
                if(MonsterJson["monster"][i]["resist"][j]["note"].is_string()) resistance_note.push_back(MonsterJson["monster"][i]["resist"][j]["note"]);
                else for (int m = 0; m < MonsterJson["monster"][i]["resist"][j]["note"].size(); m++) {
                  resistance_note.push_back(MonsterJson["monster"][i]["resist"][j]["note"][m]);
                }
              }
            }
          }
        }
        cout << "Control reach Monster::Constructor 11\n";
        //others
        passive_perception = commonIntParse(MonsterJson["monster"][i], "passive");
        cout << "Control reach Monster::Constructor 11_1\n";
        immune = ImmuneParse(MonsterJson["monster"][i], "immune");
        cout << "Control reach Monster::Constructor 11_1_1\n";
        conditionImune =
            commonForImmuneAndConditionImmuneAndSensesAndLanguageParse(MonsterJson["monster"][i], "conditionImmune");
        cout << "Control reach Monster::Constructor 11_1_2\n";
        senses = commonForImmuneAndConditionImmuneAndSensesAndLanguageParse(MonsterJson["monster"][i], "senses");
        cout << "Control reach Monster::Constructor 11_2\n";
        languages = commonForImmuneAndConditionImmuneAndSensesAndLanguageParse(MonsterJson["monster"][i], "languages");
        trait =
            commonForTraitAndActionAndSpellNameAndSpellHeaderEntriesAndLegendaryParse(MonsterJson["monster"][i]["trait"],
                                                                                      "entries");
        cout << "Control reach Monster::Constructor 11_3\n";
        action =
            commonForTraitAndActionAndSpellNameAndSpellHeaderEntriesAndLegendaryParse(MonsterJson["monster"][i]["action"],
                                                                                      "entries");
        cout << "Control reach Monster::Constructor 11_4\n";
        legendary =
            commonForTraitAndActionAndSpellNameAndSpellHeaderEntriesAndLegendaryParse(MonsterJson["monster"][i]["legendary"],
                                                                                      "entries");
        cout << "Control reach Monster::Constructor 11_5\n";
        spellcastingNameAndEntries = commonForTraitAndActionAndSpellNameAndSpellHeaderEntriesAndLegendaryParse(
            MonsterJson["monster"][i]["spellcasting"], "headerEntries");
        cout << "Control reach Monster::Constructor 12\n";
        spellcasting_will = commonVectorStringParse(MonsterJson["monster"][i]["spellcasting"], "will");
        spellcastDaily = spellcastingDailyParse(MonsterJson["monster"][i]["spellcasting"]);
        spells = spellsParse(MonsterJson["monster"][i], "spells");
        spellSlots = spellSlotsParse(MonsterJson["monster"][i], "spells");  //TEST
        isNamedCreature = commonBoolParse(MonsterJson["monster"][i], "isNamedCreature");
        cout << "Control reach Monster::Constructor b_13\n";
        traitTags = commonVectorStringParse(MonsterJson["monster"][i], "traitTags");
        cout << "Control reach Monster::Constructor 13\n";
        actionTags = commonVectorStringParse(MonsterJson["monster"][i], "actionTags");
        cout << "Control reach Monster::Constructor 14\n";
        languageTags = commonVectorStringParse(MonsterJson["monster"][i], "languageTags");
        cout << "Control reach Monster::Constructor 15\n";
        senseTags = commonVectorStringParse(MonsterJson["monster"][i], "senseTags");
        cout << "Control reach Monster::Constructor 16\n";
        legendaryGroup = commonStringParse(MonsterJson["monster"][i], "legendaryGroup");
        legendaryActions = commonIntParse(MonsterJson["monster"][i], "legendaryActions");
        // "" - not needed
        variant = commonVariantParse(MonsterJson["monster"][i], "variant");
        maxhealth = health_modifier + HealthRoll(Rand_gen, health_dice, health_dice_num);
        health = maxhealth;
        StrModifier = AbilityModifier(Str);
        DexModifier = AbilityModifier(Dex);
        ConModifier = AbilityModifier(Con);
        IntModifier = AbilityModifier(Int);
        WisModifier = AbilityModifier(Wis);
        ChaModifier = AbilityModifier(Cha);
        break;
      } /*else cout << "monster not found in json\n";*/
    }
  } else cout << "error loading MonJson" << endl;
  cout << "Control reach Monster::Constructor 9\n";
}

Monster::Monster() = default;

Monster::Monster(Random_Generator_ *Rand_gen, const Monster &another) {
  saving_throws.resize(kAbilities_Num);
  skillString.resize(kSkills_Num);
  monster_name = another.monster_name;
  size = another.size;
  challenge_rating = another.challenge_rating;
  maxhealth = another.maxhealth;
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
  for (int i = 0; i < kSpeed_types_NUM; i++) {
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
  for (int i = 0; i < kAbilities_Num; i++) {
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
  maxhealth = health_modifier + HealthRoll(Rand_gen, health_dice, health_dice_num);
  health = maxhealth;
  StrModifier = AbilityModifier(Str);
  DexModifier = AbilityModifier(Dex);
  ConModifier = AbilityModifier(Con);
  IntModifier = AbilityModifier(Int);
  WisModifier = AbilityModifier(Wis);
  ChaModifier = AbilityModifier(Cha);
}

/*Monster::Monster(int type_, int level_, int hp, int armor_class_) {

}*/

Monster::~Monster() = default;

int Monster::GetInt(int whatToShow) {
  if (whatToShow == 0) return maxhealth;
  else if (whatToShow == 1) return health;
  else if (whatToShow == 2) return health_dice;
  else if (whatToShow == 3) return health_dice_num;
  else if (whatToShow == 4) return health_modifier;
  else if (whatToShow == 5) return armor_class;
  else if (whatToShow == 6) return speed[kSpeed_types_NUM - 4]; // walk
  else if (whatToShow == 7) return speed[kSpeed_types_NUM - 3];
  else if (whatToShow == 8) return speed[kSpeed_types_NUM - 2];
  else if (whatToShow == 9) return speed[kSpeed_types_NUM - 1]; // fly
  else if (whatToShow == 10) return Str;
  else if (whatToShow == 11) return Dex;
  else if (whatToShow == 12) return Con;
  else if (whatToShow == 13) return Int;
  else if (whatToShow == 14) return Wis;
  else if (whatToShow == 15) return Cha;
  else if (whatToShow == 16) return passive_perception;
  else if (whatToShow == 17) return legendaryActions;
  return -1;
}

string Monster::GetString(int whatToShow) {
  if (whatToShow == 0) return monster_name;
  else if (whatToShow == 1) return size;
  else if (whatToShow == 2) return challenge_rating;
  else if (whatToShow == 3) return hpFormula;
  else if (whatToShow == 4) return type_s;
  else if (whatToShow == 5) return fly_condition;
  else if (whatToShow >= 6 && whatToShow < 6 + kAbilities_Num) return saving_throws[whatToShow - 6];
  else if (whatToShow >= 12 && whatToShow < 12 + kSkills_Num) return skillString[whatToShow - 12];
  else if (whatToShow == 30) return legendaryGroup;
  return "";
}

vector<string> Monster::GetVectorString(int whatToShow) {
  vector<string> Output;
  if (whatToShow == 0) return type_tags;
  else if (whatToShow == 1) return alignment;
  else if (whatToShow == 2) return acFrom;
  else if (whatToShow == 3) return resistance;
  else if (whatToShow == 4) return resistance_note;
  else if (whatToShow == 5) return immune;
  else if (whatToShow == 6) return conditionImune;
  else if (whatToShow == 7) return senses;
  else if (whatToShow == 8) return languages;
  else if (whatToShow == 9) return trait;
  else if (whatToShow == 10) return action;
  else if (whatToShow == 11) return legendary;
  else if (whatToShow == 12) return spellcastingNameAndEntries;
  else if (whatToShow == 13) return spellcasting_will;
  else if (whatToShow == 14) return traitTags;
  else if (whatToShow == 15) return actionTags;
  else if (whatToShow == 16) return languageTags;
  else if (whatToShow == 17) return senseTags;
  else if (whatToShow == 18) return variant;
  return Output;
}

bool Monster::GetBool(int whatToShow) {
  if (whatToShow == 0) return canHover;
  else if (whatToShow == 1) return isNamedCreature;
  /*else if (whatToShow == 2) return;
  else if (whatToShow == 3) return;
  else if (whatToShow == 4) return;
  else if (whatToShow == 5) return;
  else if (whatToShow == 6) return;
  else if (whatToShow == 7) return;
  else if (whatToShow == 8) return;
  else if (whatToShow == 9) return;*/
  return false;
}

vector<SpellAndUsageTimes> Monster::GetSpellAndUsageTimes(int whatToShow) {
  vector<SpellAndUsageTimes> Output;
  if (whatToShow == 0) return spellcastDaily;
  return Output;
}

void Monster::SetInt(int whatToSet, int value) {
  if (whatToSet == 0) maxhealth = value;
  else if (whatToSet == 1) health = value;
  else if (whatToSet == 2) health_dice = value;
  else if (whatToSet == 3) health_dice_num = value;
  else if (whatToSet == 4) health_modifier = value;
  else if (whatToSet == 5) armor_class = value;
  else if (whatToSet == 6) speed[kSpeed_types_NUM - 4] = value; // walk
  else if (whatToSet == 7) speed[kSpeed_types_NUM - 3] = value;
  else if (whatToSet == 8) speed[kSpeed_types_NUM - 2] = value;
  else if (whatToSet == 9) speed[kSpeed_types_NUM - 1] = value; // fly
  else if (whatToSet == 10) Str = value;
  else if (whatToSet == 11) Dex = value;
  else if (whatToSet == 12) Con = value;
  else if (whatToSet == 13) Int = value;
  else if (whatToSet == 14) Wis = value;
  else if (whatToSet == 15) Cha = value;
  else if (whatToSet == 16) passive_perception = value;
  else if (whatToSet == 17) legendaryActions = value;
}

void Monster::SetString(int whatToSet, string value) {
  if (whatToSet == 0) monster_name = value;
  else if (whatToSet == 1) size = value;
  else if (whatToSet == 2) challenge_rating = value;
  else if (whatToSet == 3) hpFormula = value;
  else if (whatToSet == 4) type_s = value;
  else if (whatToSet == 5) fly_condition = value;
  else if (whatToSet >= 6 && whatToSet < 6 + kAbilities_Num) saving_throws[whatToSet - 6] = value;
  else if (whatToSet >= 12 && whatToSet < 12 + kSkills_Num) skillString[whatToSet - 12] = value;
  else if (whatToSet == 30) legendaryGroup = value;
}

void Monster::SetVectorString(int whatToSet, vector<string> value) {
  if (whatToSet == 0) type_tags = value;
  else if (whatToSet == 1) alignment = value;
  else if (whatToSet == 2) acFrom = value;
  else if (whatToSet == 3) resistance = value;
  else if (whatToSet == 4) resistance_note = value;
  else if (whatToSet == 5) immune = value;
  else if (whatToSet == 6) conditionImune = value;
  else if (whatToSet == 7) senses = value;
  else if (whatToSet == 8) languages = value;
  else if (whatToSet == 9) trait = value;
  else if (whatToSet == 10) action = value;
  else if (whatToSet == 11) legendary = value;
  else if (whatToSet == 12) spellcastingNameAndEntries = value;
  else if (whatToSet == 13) spellcasting_will = value;
  else if (whatToSet == 14) traitTags = value;
  else if (whatToSet == 15) actionTags = value;
  else if (whatToSet == 16) languageTags = value;
  else if (whatToSet == 17) senseTags = value;
  else if (whatToSet == 18) variant = value;
}

void Monster::SetBool(int whatToSet, bool value) {
  if (whatToSet == 0) canHover = value;
  else if (whatToSet == 1) isNamedCreature = value;
}

void Monster::SetSpellAndUsageTimes(int whatToSet, vector<SpellAndUsageTimes> &value) {
  if (whatToSet == 0) spellcastDaily = value;
}

const nlohmann::basic_json<> Monster::Save() {
  json Output;
  Monster_Parameters_Names M_P;
  M_P.fakeParameter = 1;
  cout << "Control reach Monster::Save 1\n";
  for (int i = 0; i < M_P.intVar.size(); i++) {
    Output["monster"] += json::object_t::value_type(M_P.intVar[i], this->GetInt(i));
  }
  for (int i = 0; i < M_P.boolVar.size(); i++) {
    Output["monster"] += json::object_t::value_type(M_P.boolVar[i], this->GetBool(i));
  }
  cout << "Control reach Monster::Save 3\n";
  for (int i = 0; i < M_P.stringVar.size(); i++) {
    Output["monster"] += json::object_t::value_type(M_P.stringVar[i], this->GetString(i));
  }
  cout << "Control reach Monster::Save 4\n";
  for (int i = 0; i < M_P.vectorStringVar.size(); i++) {
    Output["monster"] += json::object_t::value_type(M_P.vectorStringVar[i], this->GetVectorString(i));
  }
  cout << "Control reach Monster::Save 5\n";
  Output["monster"]  += json::object_t::value_type("dailySpells", NULL);
  for (int i = 0; i < spellcastDaily.size(); i++) {
    //Output["monster"]["dailySpells"]  += json::object_t::value_type(i, NULL);
    Output["monster"]["dailySpells"][i] += json::object_t::value_type("name" ,spellcastDaily[i].spellName);
    Output["monster"]["dailySpells"][i] +=
        json::object_t::value_type("maxCharges", to_string(spellcastDaily[i].maxCharges));
    Output["monster"]["dailySpells"][i] += json::object_t::value_type("Charges", to_string(spellcastDaily[i].Charges));
  }
  cout << "Control reach Monster::Save 10\n";
  return Output;
}
//j["monster"] must be given as a parameter
bool Monster::Load(const nlohmann::basic_json<> &j) {
  Monster_Parameters_Names M_P;
  if(j.find("monster_name") == j.end()) return false;
  for (int i = 0; i < M_P.intVar.size(); i++) {
    SetInt(i, j[M_P.intVar[i]]);
  }
  for (int i = 0; i < M_P.boolVar.size(); i++) {
    SetInt(i, j[M_P.boolVar[i]]);
  }
  for (int i = 0; i < M_P.stringVar.size(); i++) {
    SetInt(i, j[M_P.stringVar[i]]);
  }
  for (int i = 0; i < M_P.vectorStringVar.size(); i++) {
    SetInt(i, j[M_P.vectorStringVar[i]]);
  }
  if(j.find("dailySpells") == j.end()) return true;
  vector <SpellAndUsageTimes> spellAndUsage_;
  for(int i = 0; i < j["dailySpells"].size(); i++){
    SpellAndUsageTimes daily;
    daily.spellName = j["dailySpells"]["name"];
    daily.maxCharges = j["dailySpells"]["maxCharges"];
    daily.Charges = j["dailySpells"]["Charges"];
    spellAndUsage_.push_back(daily);
  }
  SetSpellAndUsageTimes(0, spellAndUsage_);
  return true;
}