

#include "Classes.h"

Class::Class() {
  type = 0;
  hit_dice = 0;
  for (int i = 0; i < 6; i++) {
    primary_ability[i] = false;
    saving_throw_proficiencies[i] = false;
    armor_and_weapon_proficiencies[i] = false;
    s[i] = 0;
    s[i + 6] = 0;
    s[i + 12] = 0;
  }
  architype = 0;
}

Class::Class(int type_, bool *s_b[]) {
  set(type_, s_b);
}
Class::~Class() = default;

void Class::set(int type_, bool *s_b[]) {
  Existing_classes E;
  type = type_;
  hit_dice = E.Class_atribute[type][0];
  for (int i = 0; i < 7; i++) {
    if (i < 6) {
      if (E.Class_atribute[type][i + 1] > 0) primary_ability[i] = true;
      if (E.Class_atribute[type][i + 7] > 0) saving_throw_proficiencies[i] = true;
    }
    if (E.Class_atribute[type][i + 12] > 0) armor_and_weapon_proficiencies[i] = true;
  }
  architype = 0;
  set_skills(s_b);
  set_architype();
}

void Class::set_architype() {
  if (type == -1) {
    std::cout << "Choose your way:\n";
  }
}

bool Class::Load(int a,bool b[], int a14){
  Existing_classes E;
  type = a;
  architype = a14;
  for (int i = 0; i < 7; i++) {
    armor_and_weapon_proficiencies[i] = b[29 + i];
  }
  hit_dice = E.Class_atribute[type][0];
  for(int i = 0; i < 6;i++){
    primary_ability[i] = false;
    s[i] = 0;
    s[6+i] = 0;
    s[12+i] = 0;
  }
  for (int i = 0; i < 6; i++) {
    if (E.Class_atribute[type][i + 1] > 0) primary_ability[i] = true;
    saving_throw_proficiencies[i] = b[23 + i];
  }
  return true;
}

void Class::set_skills(bool *s_b[]) {
  int skill_1 = 0, skill_2 = 0, skill_3 = 0, skill_4 = 0; //tmp
  if (type == 0) {
    int skills_identifier[6] = {1, 3, 7, 10, 11, 17};
    printf("%s \n", "Choose two from Animal Handling(0), Athletic(1), Intimidation(2), Nature(3), "
                    "Perception(4) and Survival(5)");
    //std::cin >> skill_1 >> skill_2;
    skill_1 = IsNumber(skill_1, 0, 5);
    skill_2 = IsNumber(skill_2, 0, 5);
    while (s_b[skills_identifier[skill_1]]) {
      printf("you already got proficiency in this skill\n");
      skill_1 = -1;
      skill_1 = IsNumber(skill_1, 0, 5);
    }
    while (skill_2 == skill_1 || s_b[skills_identifier[skill_2]]) {
      skill_2 = -1;
      printf("you already got proficiency in this skill\n");
      skill_2 = IsNumber(skill_2, 0, 5);
    }
    s[skills_identifier[skill_1]] = 1;
    s[skills_identifier[skill_2]] = 1;
  } else if (type == 1) {
    printf("%s \n", "Choose any three (0-17)");
    //std::cin >> skill_1 >> skill_2 >> skill_3;
    skill_1 = IsNumber(skill_1, 0, 17);
    skill_2 = IsNumber(skill_2, 0, 17);
    skill_3 = IsNumber(skill_3, 0, 17);
    while (s_b[skill_1]) {
      printf("you already got proficiency in this skill 1\n");
      skill_1 = -1;
      skill_1 = IsNumber(skill_1, 0, 17);
    }
    while (skill_2 == skill_1 || s_b[skill_2]) {
      printf("you already got proficiency in this skill 2\n");
      skill_2 = -1;
      skill_2 = IsNumber(skill_2, 0, 17);
    }
    //skill_3 = IsNumber(skill_3, 0, 17);
    while (skill_2 == skill_3 || skill_1 == skill_3 || s_b[skill_3]) {
      printf("you already got proficiency in this skill 3\n");
      skill_3 = -1;
      skill_3 = IsNumber(skill_3, 0, 17);
    }
    s[skill_1] = 1;
    s[skill_2] = 1;
    s[skill_3] = 1;
  } else if (type == 2) {
    int skills_identifier[5] = {5, 6, 9, 13, 14};
    printf("%s \n", "Choose two from History(0), Insight(1), Medicine(2), Persuasion(3) and Religion(4)");
    //std::cin >> skill_1 >> skill_2;
    skill_1 = IsNumber(skill_1, 0, 4);
    skill_2 = IsNumber(skill_2, 0, 4);
    while (s_b[skills_identifier[skill_1]]) {
      printf("you already got proficiency in this skill\n");
      skill_1 = -1;
      skill_1 = IsNumber(skill_1, 0, 4);
    }
    while (skill_2 == skill_1 || s_b[skills_identifier[skill_2]]) {
      skill_2 = -1;
      skill_2 = IsNumber(skill_2, 0, 4);
    }

    s[skills_identifier[skill_1]] = 1;
    s[skills_identifier[skill_2]] = 1;
  } else if (type == 3) {
    int skills_identifier[8] = {3, 1, 6, 9, 10, 11, 14, 17};
    printf("%s \n", "Choose two from Arcana(0), Animal Handling(1), Insight(2), Medicine(3), Nature(4), "
                    "Perception(5), Religion(6) and Survival(7)");
    //std::cin >> skill_1 >> skill_2;
    skill_1 = IsNumber(skill_1, 0, 7);
    skill_2 = IsNumber(skill_2, 0, 7);
    while (s_b[skills_identifier[skill_1]]) {
      printf("you already got proficiency in this skill\n");
      skill_1 = -1;
      skill_1 = IsNumber(skill_1, 0, 7);
    }
    while (skill_2 == skill_1 || s_b[skills_identifier[skill_2]]) {
      skill_2 = -1;
      skill_2 = IsNumber(skill_2, 0, 7);
    }
    s[skills_identifier[skill_1]] = 1;
    s[skills_identifier[skill_2]] = 1;
  } else if (type == 4) {
    int skills_identifier[8] = {0, 1, 3, 5, 6, 7, 11, 17};
    printf("%s \n", "Choose two from Acrobatics(0), AnimalHandling(1), Athletics(2), History(3), Insight(4), "
                    "Intimidation(5), Perception(6) and Survival(7)");
    //std::cin >> skill_1 >> skill_2;
    skill_1 = IsNumber(skill_1, 0, 7);
    skill_2 = IsNumber(skill_2, 0, 7);
    while (s_b[skills_identifier[skill_1]]) {
      printf("you already got proficiency in this skill\n");
      skill_1 = -1;
      skill_1 = IsNumber(skill_1, 0, 7);
    }
    while (skill_2 == skill_1 || s_b[skills_identifier[skill_2]]) {
      skill_2 = -1;
      skill_2 = IsNumber(skill_2, 0, 7);
    }

    s[skills_identifier[skill_1]] = 1;
    s[skills_identifier[skill_2]] = 1;
  } else if (type == 5) {
    int skills_identifier[6] = {0, 3, 5, 6, 14, 17};
    printf("%s \n", "Choose two from Acrobatics(0), Athletics(1), History(2), Insight(3), Religion(4), "
                    "and Stealth(5)");
    //std::cin >> skill_1 >> skill_2;
    skill_1 = IsNumber(skill_1, 0, 5);
    skill_2 = IsNumber(skill_2, 0, 5);
    while (s_b[skills_identifier[skill_1]]) {
      printf("you already got proficiency in this skill\n");
      skill_1 = -1;
      skill_1 = IsNumber(skill_1, 0, 5);
    }
    //skill_1 = IsNumber(skill_1, 0, 5);
    //skill_2 = IsNumber(skill_2, 0, 5);
    while (skill_2 == skill_1 || s_b[skills_identifier[skill_2]]) {
      printf("you already got proficiency in this skill\n");
      skill_2 = -1;
      skill_2 = IsNumber(skill_2, 0, 5);
    }

    s[skills_identifier[skill_1]] = 1;
    s[skills_identifier[skill_2]] = 1;
  } else if (type == 6) {
    int skills_identifier[6] = {3, 6, 7, 9, 14};
    printf("%s \n", "Choose two from Athletics(0), Insight(1), Intimidation(2), Medicine(3), Persuasion(4), "
                    "and Religion(5)");
    //std::cin >> skill_1 >> skill_2;
    skill_1 = IsNumber(skill_1, 0, 5);
    skill_2 = IsNumber(skill_2, 0, 5);
    while (s_b[skills_identifier[skill_1]]) {
      printf("you already got proficiency in this skill\n");
      skill_1 = -1;
      skill_1 = IsNumber(skill_1, 0, 5);
    }
    while (skill_2 == skill_1 || s_b[skills_identifier[skill_2]]) {
      printf("you already got proficiency in this skill\n");
      skill_2 = -1;
      skill_2 = IsNumber(skill_2, 0, 5);
    }

    s[skills_identifier[skill_1]] = 1;
    s[skills_identifier[skill_2]] = 1;
  } else if (type == 7) {
    int skills_identifier[8] = {1, 3, 6, 8, 10, 11, 16, 17};
    while (s_b[skills_identifier[skill_1]]) {
      printf("you already got proficiency in this skill\n");
      skill_1 = -1;
      skill_1 = IsNumber(skill_1, 0, 5);
    }
    printf("%s \n", "Choose two from Animal Handling(0), Athletics(1), Insight(2), Investigation(3), Nature(4), "
                    "Perception(5), Stealth(6) and Survival(7)");
    //std::cin >> skill_1 >> skill_2;
    skill_1 = IsNumber(skill_1, 0, 7);
    skill_2 = IsNumber(skill_2, 0, 7);
    while (skill_2 == skill_1 || s_b[skills_identifier[skill_2]]) {
      printf("you already got proficiency in this skill\n");
      skill_2 = -1;
      skill_2 = IsNumber(skill_2, 0, 7);
    }
    s[skills_identifier[skill_1]] = 1;
    s[skills_identifier[skill_2]] = 1;
  } else if (type == 8) {
    int skills_identifier[11] = {0, 3, 4, 6, 7, 8, 11, 12, 13, 15, 16};
    /*while (s_b[skills_identifier[skill_1]]) {
      printf("you already got proficiency in this skill\n");
      skill_1 = -1;
      skill_1 = IsNumber(skill_1, 0, 5);
    }*/
    printf("%s \n", "Choose four from Acrobatics(0), Athletics(1), Deception(2), Insight(3), Intimidation(4), "
                    "Investigation(5), Perception(6), Performance(7), Persuasion(8), Sleight of Hand(9) "
                    "and Stealth(10)");
    //std::cin >> skill_1 >> skill_2 >> skill_3 >> skill_4;
    skill_1 = IsNumber(skill_1, 0, 10);
    skill_2 = IsNumber(skill_2, 0, 10);
    skill_3 = IsNumber(skill_3, 0, 10);
    skill_4 = IsNumber(skill_4, 0, 10);
    while (skill_2 == skill_1 || s_b[skills_identifier[skill_2]]) {
      printf("you already got proficiency in this skill\n");
      skill_2 = -1;
      skill_2 = IsNumber(skill_2, 0, 10);
    }
    skill_3 = IsNumber(skill_3, 0, 10);
    while (skill_2 == skill_3 || skill_1 == skill_3 || s_b[skills_identifier[skill_3]]) {
      printf("you already got proficiency in this skill\n");
      skill_3 = -1;
      skill_3 = IsNumber(skill_3, 0, 10);
    }
    skill_4 = IsNumber(skill_4, 0, 10);
    while (skill_2 == skill_4 || skill_1 == skill_4 || skill_3 == skill_4 || s_b[skills_identifier[skill_4]]) {
      printf("you already got proficiency in this skill\n");
      skill_4 = -1;
      skill_4 = IsNumber(skill_4, 0, 10);
    }
    s[skills_identifier[skill_1]] = 1;
    s[skills_identifier[skill_2]] = 1;
    s[skills_identifier[skill_3]] = 1;
    s[skills_identifier[skill_4]] = 1;
  } else if (type == 9) {
    int skills_identifier[6] = {2, 4, 6, 7, 13, 4};
    /*while (s_b[skills_identifier[skill_1]]) {
      printf("you already got proficiency in this skill\n");
      skill_1 = -1;
      skill_1 = IsNumber(skill_1, 0, 5);
    }*/
    printf("%s \n", "Choose two from Arcana(0), Deception(1), Insight(2), Intimidation(3), Persuasion(4), "
                    "and Religion(5)");
    //std::cin >> skill_1 >> skill_2;
    skill_1 = IsNumber(skill_1, 0, 5);
    skill_2 = IsNumber(skill_2, 0, 5);
    while (skill_2 == skill_1 || s_b[skills_identifier[skill_2]]) {
      printf("you already got proficiency in this skill\n");
      skill_2 = -1;
      skill_2 = IsNumber(skill_2, 0, 5);
    }

    s[skills_identifier[skill_1]] = 1;
    s[skills_identifier[skill_2]] = 1;
  } else if (type == 10) {
    int skills_identifier[7] = {2, 4, 5, 7, 8, 10, 14};
    /*while (s_b[skills_identifier[skill_1]]) {
      printf("you already got proficiency in this skill\n");
      skill_1 = -1;
      skill_1 = IsNumber(skill_1, 0, 5);
    }*/
    printf("%s \n", "Choose two from Arcana(0), Deception(1), History(2), Intimidation(3), Investigation(4), "
                    "Nature(5), and Religion(6)");
    //std::cin >> skill_1 >> skill_2;
    skill_1 = IsNumber(skill_1, 0, 6);
    skill_2 = IsNumber(skill_2, 0, 6);
    while (skill_2 == skill_1 || s_b[skills_identifier[skill_2]]) {
      printf("you already got proficiency in this skill\n");
      skill_2 = -1;
      skill_2 = IsNumber(skill_2, 0, 6);
    }

    s[skills_identifier[skill_1]] = 1;
    s[skills_identifier[skill_2]] = 1;
  } else if (type == 11) {
    int skills_identifier[6] = {2, 5, 6, 8, 9, 14};
    /*while (s_b[skills_identifier[skill_1]]) {
      printf("you already got proficiency in this skill\n");
      skill_1 = -1;
      skill_1 = IsNumber(skill_1, 0, 5);
    }*/
    printf("%s \n", "Choose two from Arcana(0), History(1), Insight(2), Investigation(3), Medicine(4) "
                    "and Religion(5)");
    //std::cin >> skill_1 >> skill_2;
    skill_1 = IsNumber(skill_1, 0, 5);
    skill_2 = IsNumber(skill_2, 0, 5);
    while (skill_2 == skill_1 || s_b[skills_identifier[skill_2]]) {
      printf("you already got proficiency in this skill\n");
      skill_2 = -1;
      skill_2 = IsNumber(skill_2, 0, 5);
    }

    s[skills_identifier[skill_1]] = 1;
    s[skills_identifier[skill_2]] = 1;
  }
}

int Class::get(int what) {
  if (what == 0) { return type; }
  else if (what == 20) return hit_dice;
  else if (20 < what && what < 39) return s[what - 21];
  else if(what == 39) return architype;
  return -1;
}

bool Class::get_bool(int what){
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
