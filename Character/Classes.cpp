

#include "Classes.h"

Class::Class() {
  type = 0;
  hit_dice = 0;
  for (int i = 0; i < 6; i++) {
    primary_ability[i] = false;
    saving_throw_proficiencies[i] = false;
    armor_and_weapon_proficiencies[i] = false;
    skills[i] = 0;
    skills[i + 6] = 0;
    skills[i + 12] = 0;
  }
  archetype = 0;
}

Class::Class(int type_, bool *skills_b[]) {
  set(type_, skills_b);
}
Class::~Class() = default;

void Class::set(int type_, bool *skills_b[]) {
  std::cout << "skills_b[1] = " << skills_b[1] << "\n";
  Existing_classes E;
  type = type_;
  hit_dice = E.Class_atribute[type][0];
  for (int i = 0; i < 7; i++) {
    if (i < 6) {
      if (E.Class_atribute[type][i + 1] > 0) primary_ability[i] = true;
      if (E.Class_atribute[type][i + 7] > 0) saving_throw_proficiencies[i] = true;
    }
    if (E.Class_atribute[type][i + 13] > 0) armor_and_weapon_proficiencies[i] = true;
  }
  for(int j = 0; j < kSkills_Num ; j++){
    skills[j] = 0;
  }
  if (type == 4) {
    std::cout << "Fighter class allows you to choose one of primary abilities. Type 1.Str or 2.Dex\n";
    int str_or_dex_ = 0;
    str_or_dex_ = IsNumber(str_or_dex_, 1, 2);
    if (str_or_dex_ == 1) primary_ability[0] = true;
    else primary_ability[1] = true;
  }
  archetype = 0;
  set_skills(skills_b);
  set_archetype();
}

void Class::set_archetype() {
  if (type == -1) {
    std::cout << "Choose your way:\n";
  }
}

bool Class::Load(int type_, bool b[], int archetype_) {
  Existing_classes E;
  type = type_;
  archetype = archetype_;
  for (int i = 0; i < 7; i++) {
    armor_and_weapon_proficiencies[i] = b[kArmor_Weapon_shift + i];
  }
  hit_dice = E.Class_atribute[type][0];
  for (int i = 0; i < kAbilities_Num; i++) {
    primary_ability[i] = false;
    skills[i] = 0;
    skills[kAbilities_Num + i] = 0;
    skills[kAbilities_Num * 2 + i] = 0;
  }
  for (int i = 0; i < kAbilities_Num; i++) {
    if (E.Class_atribute[type][i + 1] > 0) primary_ability[i] = true;
    saving_throw_proficiencies[i] = b[kSaving_Throw_shift + i];
  }
  if (type == 4) {
    std::cout << "Fighter class asks you again to choose one of primary abilities. Type 1.Str or 2.Dex. "
                 "Because programmer is too lazy to save it.\n";
    int str_or_dex_ = 0;
    str_or_dex_ = IsNumber(str_or_dex_, 1, 2);
    if (str_or_dex_ == 1) primary_ability[0] = true;
    else primary_ability[1] = true;
  }
  return true;
}

void Class::set_skills(bool *skills_b[]) {
  Existing_classes E_C;
  E_C.fake_parameter = 1;
  int skill_1 = 0, skill_2 = 0, skill_3 = 0, skill_4 = 0; //tmp
  if (type == 0) {
    //int skills_identifier[6] = {1, 3, 7, 10, 11, 17};
    std::cout << "Choose two from:\n";
    /*Animal Handling(0), Athletic(1), Intimidation(2), Nature(3), "
                                                                 "Perception(4) and Survival(5)*/
    for(int i = 0; i < E_C.skills_per_class_i[type].size();i++){
      std::cout << i + 1 << ". " << E_C.skills_per_class_i[type][i] << " ";
    }
    std::cout << std::endl;
    skill_1 = IsNumber(skill_1, 1, (int)E_C.skills_per_class_i[type].size());
    skill_1 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1);
    skill_2 = IsNumber(skill_2, 1, (int)E_C.skills_per_class_i[type].size());
    skill_2 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1, skill_2);
    skills[E_C.skills_per_class_i[type][skill_1 - 1]] = 1;
    skills[E_C.skills_per_class_i[type][skill_2 - 1]] = 1;
  } else if (type == 1) {
    std::cout << "Choose any three \n";
    for(int i = 0; i < E_C.skills_per_class_i[type].size();i++){
      std::cout << i + 1 << ". " << E_C.skills_per_class_i[type][i] << " ";
    }
    std::cout << std::endl;
    skill_1 = IsNumber(skill_1, 1, (int)E_C.skills_per_class_i[type].size());
    skill_1 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1);
    skill_2 = IsNumber(skill_2, 1, (int)E_C.skills_per_class_i[type].size());
    skill_2 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1, skill_2);
    skill_3 = IsNumber(skill_3, 1, (int)E_C.skills_per_class_i[type].size());
    skill_3 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1, skill_2, skill_3);
    skills[E_C.skills_per_class_i[type][skill_1 - 1]] = 1;
    skills[E_C.skills_per_class_i[type][skill_2 - 1]] = 1;
    skills[E_C.skills_per_class_i[type][skill_3 - 1]] = 1;
  } else if (type == 2) {
    //int skills_identifier[5] = {5, 6, 9, 13, 14};
    std::cout << "Choose two from:\n";
    /*History(0), Insight(1), Medicine(2), Persuasion(3) and Religion(4)*/
    for(int i = 0; i < E_C.skills_per_class_i[type].size();i++){
      std::cout << i + 1 << ". " << E_C.skills_per_class_i[type][i] << " ";
    }
    std::cout << std::endl;
    skill_1 = IsNumber(skill_1, 1, (int)E_C.skills_per_class_i[type].size());
    skill_1 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1);
    skill_2 = IsNumber(skill_2, 1, (int)E_C.skills_per_class_i[type].size());
    skill_2 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1, skill_2);
    skills[E_C.skills_per_class_i[type][skill_1 - 1]] = 1;
    skills[E_C.skills_per_class_i[type][skill_2 - 1]] = 1;
  } else if (type == 3) {
    std::cout << "Choose two from:\n";
    /* Arcana(0), Animal Handling(1), Insight(2), Medicine(3), Nature(4), "
                    "Perception(5), Religion(6) and Survival(7)*/
    for(int i = 0; i < E_C.skills_per_class_i[type].size();i++){
      std::cout << i + 1 << ". " << E_C.skills_per_class_i[type][i] << " ";
    }
    std::cout << std::endl;
    skill_1 = IsNumber(skill_1, 1, (int)E_C.skills_per_class_i[type].size());
    skill_1 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1);
    skill_2 = IsNumber(skill_2, 1, (int)E_C.skills_per_class_i[type].size());
    skill_2 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1, skill_2);
    skills[E_C.skills_per_class_i[type][skill_1 - 1]] = 1;
    skills[E_C.skills_per_class_i[type][skill_2 - 1]] = 1;
  } else if (type == 4) {
    std::cout << "Choose two from:\n";
    /* Acrobatics(0), AnimalHandling(1), Athletics(2), History(3), Insight(4), "
                    "Intimidation(5), Perception(6) and Survival(7)*/
    for(int i = 0; i < E_C.skills_per_class_i[type].size();i++){
      std::cout << i + 1 << ". " << E_C.skills_per_class_i[type][i] << " ";
    }
    std::cout << std::endl;
    skill_1 = IsNumber(skill_1, 1, (int)E_C.skills_per_class_i[type].size());
    skill_1 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1);
    skill_2 = IsNumber(skill_2, 1, (int)E_C.skills_per_class_i[type].size());
    skill_2 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1, skill_2);
    skills[E_C.skills_per_class_i[type][skill_1 - 1]] = 1;
    skills[E_C.skills_per_class_i[type][skill_2 - 1]] = 1;
  } else if (type == 5) {
    //int skills_identifier[6] = {0, 3, 5, 6, 14, 17};
    std::cout << "Choose two from:\n";
    /* Acrobatics(0), Athletics(1), History(2), Insight(3), Religion(4), "
                    "and Stealth(5)*/
    for(int i = 0; i < E_C.skills_per_class_i[type].size();i++){
      std::cout << i + 1 << ". " << E_C.skills_per_class_i[type][i] << " ";
    }
    std::cout << std::endl;
    skill_1 = IsNumber(skill_1, 1, (int)E_C.skills_per_class_i[type].size());
    skill_1 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1);
    skill_2 = IsNumber(skill_2, 1, (int)E_C.skills_per_class_i[type].size());
    skill_2 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1, skill_2);
    skills[E_C.skills_per_class_i[type][skill_1 - 1]] = 1;
    skills[E_C.skills_per_class_i[type][skill_2 - 1]] = 1;
  } else if (type == 6) {
    std::cout << "Choose two from:\n";
    /* Athletics(0), Insight(1), Intimidation(2), Medicine(3), Persuasion(4), "
                    "and Religion(5)*/
    for(int i = 0; i < E_C.skills_per_class_i[type].size();i++){
      std::cout << i + 1 << ". " << E_C.skills_per_class_i[type][i] << " ";
    }
    std::cout << std::endl;
    skill_1 = IsNumber(skill_1, 1, (int)E_C.skills_per_class_i[type].size());
    skill_1 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1);
    skill_2 = IsNumber(skill_2, 1, (int)E_C.skills_per_class_i[type].size());
    skill_2 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1, skill_2);
    skills[E_C.skills_per_class_i[type][skill_1 - 1]] = 1;
    skills[E_C.skills_per_class_i[type][skill_2 - 1]] = 1;
  } else if (type == 7) {
    std::cout << "Choose two from:\n";
    /* Animal Handling(0), Athletics(1), Insight(2), Investigation(3), Nature(4), "
                    "Perception(5), Stealth(6) and Survival(7)*/
    for(int i = 0; i < E_C.skills_per_class_i[type].size();i++){
      std::cout << i + 1 << ". " << E_C.skills_per_class_i[type][i] << " ";
    }
    std::cout << std::endl;
    skill_1 = IsNumber(skill_1, 1, (int)E_C.skills_per_class_i[type].size());
    skill_1 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1);
    skill_2 = IsNumber(skill_2, 1, (int)E_C.skills_per_class_i[type].size());
    skill_2 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1, skill_2);
    skills[E_C.skills_per_class_i[type][skill_1 - 1]] = 1;
    skills[E_C.skills_per_class_i[type][skill_2 - 1]] = 1;
  } else if (type == 8) {
    std::cout << "Choose four from :\n";
    /*Acrobatics(0), Athletics(1), Deception(2), Insight(3), Intimidation(4), "
                    "Investigation(5), Perception(6), Performance(7), Persuasion(8), Sleight of Hand(9) "
                    "and Stealth(10)*/
    for(int i = 0; i < E_C.skills_per_class_i[type].size();i++){
      std::cout << i + 1 << ". " << E_C.skills_per_class_i[type][i] << " ";
    }
    std::cout << std::endl;
    skill_1 = IsNumber(skill_1, 1, (int)E_C.skills_per_class_i[type].size());
    skill_1 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1);
    skill_2 = IsNumber(skill_2, 1, (int)E_C.skills_per_class_i[type].size());
    skill_2 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1, skill_2);
    skill_3 = IsNumber(skill_3, 1, (int)E_C.skills_per_class_i[type].size());
    skill_3 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1, skill_2, skill_3);
    skill_4 = IsNumber(skill_4, 1, (int)E_C.skills_per_class_i[type].size());
    skill_4 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1, skill_2, skill_3, skill_4);
    skills[E_C.skills_per_class_i[type][skill_1 - 1]] = 1;
    skills[E_C.skills_per_class_i[type][skill_2 - 1]] = 1;
    skills[E_C.skills_per_class_i[type][skill_3 - 1]] = 1;
    skills[E_C.skills_per_class_i[type][skill_4 - 1]] = 1;
  } else if (type == 9) {
    //int skills_identifier[6] = {2, 4, 6, 7, 13, 4};
    std::cout << "Choose two from:\n";
    /* Arcana(0), Deception(1), Insight(2), Intimidation(3), Persuasion(4), "
                    "and Religion(5)*/
    for(int i = 0; i < E_C.skills_per_class_i[type].size();i++){
      std::cout << i + 1 << ". " << E_C.skills_per_class_i[type][i] << " ";
    }
    std::cout << std::endl;
    skill_1 = IsNumber(skill_1, 1, (int)E_C.skills_per_class_i[type].size());
    skill_1 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1);
    skill_2 = IsNumber(skill_2, 1, (int)E_C.skills_per_class_i[type].size());
    skill_2 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1, skill_2);
    skills[E_C.skills_per_class_i[type][skill_1 - 1]] = 1;
    skills[E_C.skills_per_class_i[type][skill_2 - 1]] = 1;
  } else if (type == 10) {
    //int skills_identifier[7] = {2, 4, 5, 7, 8, 10, 14};

    std::cout << "Choose two from:\n";
    /* Arcana(0), Deception(1), History(2), Intimidation(3), Investigation(4), "
                    "Nature(5), and Religion(6)*/
    for(int i = 0; i < E_C.skills_per_class_i[type].size();i++){
      std::cout << i + 1 << ". " << E_C.skills_per_class_i[type][i] << " ";
    }
    std::cout << std::endl;
    skill_1 = IsNumber(skill_1, 1, (int)E_C.skills_per_class_i[type].size());
    skill_1 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1);
    skill_2 = IsNumber(skill_2, 1, (int)E_C.skills_per_class_i[type].size());
    skill_2 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1, skill_2);
    skills[E_C.skills_per_class_i[type][skill_1 - 1]] = 1;
    skills[E_C.skills_per_class_i[type][skill_2 - 1]] = 1;
  } else if (type == 11) {
    std::cout << "Choose two from:\n";
    /*from Arcana(0), History(1), Insight(2), Investigation(3), Medicine(4) "
                    "and Religion(5)*/
    for(int i = 0; i < E_C.skills_per_class_i[type].size();i++){
      std::cout << i + 1 << ". " << E_C.skills_per_class_i[type][i] << " ";
    }
    std::cout << std::endl;
    skill_1 = IsNumber(skill_1, 1, (int)E_C.skills_per_class_i[type].size());
    skill_1 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1);
    skill_2 = IsNumber(skill_2, 1, (int)E_C.skills_per_class_i[type].size());
    skill_2 = Had_Skill_Been_Chosen(*skills_b, E_C.skills_per_class_i[type], skill_1, skill_2);
    skills[E_C.skills_per_class_i[type][skill_1 - 1]] = 1;
    skills[E_C.skills_per_class_i[type][skill_2 - 1]] = 1;
  }
}

int Class::Had_Skill_Been_Chosen(bool skills_b[], std::vector<int> skills_access, int skill_1) {
  while (skills_b[skills_access[skill_1 - 1]]) {
    std::cout <<"you already got proficiency in this skill 1\n";
    skill_1 = -1;
    skill_1 = IsNumber(skill_1, 1, (int)skills_access.size());
  }
  return skill_1;
}

int Class::Had_Skill_Been_Chosen(bool skills_b[], std::vector<int> skills_access, int skill_1, int skill_2) {
  while (skill_2 == skill_1 || skills_b[skills_access[skill_2 - 1]]) {
    std::cout <<"you already got proficiency in this skill 2\n";
    skill_2 = -1;
    skill_2 = IsNumber(skill_2, 1, (int)skills_access.size());
  }
  return skill_2;
}

int Class::Had_Skill_Been_Chosen(bool skills_b[], std::vector<int> skills_access, int skill_1, int skill_2, int skill_3) {
  while (skill_2 == skill_3 || skill_1 == skill_3 || skills_b[skills_access[skill_3 - 1]]) {
    std::cout <<"you already got proficiency in this skill 3\n";
    skill_3 = -1;
    skill_3 = IsNumber(skill_3, 1, (int)skills_access.size());
  }
  return skill_3;
}

int Class::Had_Skill_Been_Chosen(bool *skills_b, std::vector<int> skills_access,
    int skill_1, int skill_2, int skill_3, int skill_4) {
  while (skill_2 == skill_4 || skill_1 == skill_4 || skill_3 == skill_4 || skills_b[skills_access[skill_4 - 1]]) {
    std::cout <<"you already got proficiency in this skill 4\n";
    skill_4 = -1;
    skill_4 = IsNumber(skill_4, 1, (int)skills_access.size());
  }
  return skill_4;
}

int Class::get(int what) {
  if (what == 0) { return type; }
  else if (what == 20) return hit_dice;
  else if (20 < what && what < 39) return skills[what - kClassType_get_shift];
  else if (what == 39) return archetype;
  return -1;
}

bool Class::get_bool(int what) {
  if (0 < what && what < 7) return primary_ability[what - 1];
  else if (6 < what && what < 13) return saving_throw_proficiencies[what - 7];
  else if (12 < what && what < 20) return armor_and_weapon_proficiencies[what - 13];
  return false;
}

MultiClass::MultiClass() : Class() {
  multitype = 0;
}
MultiClass::~MultiClass() = default;
void MultiClass::subClassFeatures() {}
