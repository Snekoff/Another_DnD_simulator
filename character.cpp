#pragma once

#include <iostream>
#include <string>
#include "interface_races_classes_background.h"
#include "Race_Class_Background.cpp"
#include "UsefulFunctions.cpp"

using namespace std;

struct skills {
  int s[18] = {0};/* acrobatics 0,animalHandling 1,arcana 2,athletics 3,deception 4,
history 5,insight 6,intimidation 7,investigation 8,medicine 9,
nature 10,perception 11,performance 12,persuasion 13,religion 14,
sleightOfHand 15,stealth 16,survival 17*/
};
class Item { //all items have got damage,
 protected:
  int damage;
};

class Character {
 private:
  Race race;
  Class classType;
  string storyline;
  int experience, level;
  int health, maxhealth;
  int health_dice;
  int Str, Dex, Con, Int, Wis, Cha;
  int StrModifier, DexModifier, ConModifier, IntModifier, WisModifier, ChaModifier;
  int AC;
  int deathsaves_s, deathsaves_f;//success/failure
  int passive_perception, proficiency;
  bool advantage = false, disadvantage = false;
  skills skill;
  Item w;
  string inventory;
 public:
  Character() {}

  ~Character() {}

  void SetF(string a, string b, string story, int l, int h, int s, int d, int c, int i, int w, int cha) {
    if (a == "") { a = "human"; }
    if (b == "") { b = "barbarian"; }
    if (story == "") { story = "Acolyte"; }
    if (l < 0) l = 0;
    if (h < 0) h = 0;
    if (s < 0) s = 0;
    if (d < 0) d = 0;
    if (c < 0) c = 0;
    if (i < 0) i = 0;
    if (w < 0) w = 0;
    if (cha < 0) cha = 0;
    //race = a;classType = b;
    level = l;
    health = h;
    maxhealth = h;
    Str = s;
    Dex = d;
    Con = c;
    Int = i;
    Wis = w;
    Cha = cha;
    StrModifier = (Str - 10) / 2;
    DexModifier = (DexModifier - 10) / 2;
    ConModifier = (ConModifier - 10) / 2;
    IntModifier = (IntModifier - 10) / 2;
    WisModifier = (WisModifier - 10) / 2;
    ChaModifier = (ChaModifier - 10) / 2;
    SetSkill(skill);
    if (level < 4)proficiency = 2;
    else if (level > 3 && level < 8)proficiency = 3;
    else proficiency = 4;
    passive_perception = 10 + WisModifier; // if creature have advantage +5 if disadvantage -5
    printf("%s \n",
           "Your class allows you to Get a proficiencyiciency skills, your proficiencyiciency bonus will be added to them that will made you stronger or smarter, depends what you choose.");
    /*if(classType == "Barbarian"){health_dice = 12;
    printf("%s \n", "Choose two from Animal Handling, Athletic, Intimidation, Nature, Perception and Survival");
    }// save throws, skills,
    else if(classType == "Bard"){health_dice = 8;
        printf("%s \n", "Choose any three ");
    }
    else if(classType == "Cleric"){health_dice = 8;
        printf("%s \n", "Choose two from History, .s[6], Medicine, Persuasion and Religion");
    }
    else if(classType == "Druid"){health_dice = 8;
        printf("%s \n", "Choose two from Arcana, Animal Handling, .s[6], Medicine, Nature, Perception, Religion and Survival");
    }
    else if(classType == "Fighter"){health_dice = 10;
        printf("%s \n", "Choose two from Acrobatics, AnimalHandling, Athletics, History, .s[6], Intimidation, Perception and Survival");
    }
    else if(classType == "Monk"){health_dice = 8;
        printf("%s \n", "Choose two from Acrobatics, Athletics, History, .s[6], Religion, and Stealth");
    }
    else if(classType == "Paladin"){health_dice = 10;
        printf("%s \n", "Choose two from Athletics, .s[6], Intimidation, Medicine, Persuasion, and Religion");
    }
    else if(classType == "Ranger"){health_dice = 10;
        printf("%s \n", "Choose two from Animal Handling, Athletics, .s[6], Investigation, Nature, Perception, Stealth and Survival");
    }
    else if(classType == "Rouge"){health_dice = 8;
        printf("%s \n", "Choose four from Acrobatics, Athletics, Deception, .s[6], Intimidation, Investigation, Perception, Performance, Persuasion, Sleight of Hand and Stealth");
    }
    else if(classType == "Sorcerer"){health_dice = 6;
        printf("%s \n", "Choose two from Arcana, Deception, .s[6], Intimidation, Persuasion, and Religion");
    }
    else if(classType == "Warlock"){health_dice = 8;
        printf("%s \n", "Choose two from Arcana, Deception, History, Intimidation, Investigation, Nature, and Religion");
    }
    else if(classType == "Wizard"){health_dice = 6;
        printf("%s \n", "Choose two from Arcana, History, .s[6], Investigation, Medicine, and Religion");
    }*/
    if (story == "Acolyte") {
      if (skill.s[6] == WisModifier)skill.s[6] += proficiency;
      if (skill.s[14] == IntModifier)skill.s[14] += proficiency;
    } else if (story == "Charlatan") {
      if (skill.s[4] == ChaModifier)skill.s[4] += proficiency;
      if (skill.s[15] == DexModifier)skill.s[15] += proficiency;
    } else if (story == "Criminal") {
      if (skill.s[4] == ChaModifier)skill.s[4] += proficiency;
      if (skill.s[16] == DexModifier)skill.s[16] += proficiency;
    } else if (story == "Entertainer") {
      if (skill.s[0] == IntModifier)skill.s[0] += proficiency;
      if (skill.s[12] == ChaModifier)skill.s[12] += proficiency;
    } else if (story == "FolkHero") {
      if (skill.s[1] == WisModifier)skill.s[1] += proficiency;
      if (skill.s[17] == WisModifier)skill.s[17] += proficiency;
    } else if (story == "GuildArtisan") {
      if (skill.s[6] == WisModifier)skill.s[6] += proficiency;
      if (skill.s[13] == ChaModifier)skill.s[13] += proficiency;
    } else if (story == "Hermit") {
      if (skill.s[9] == WisModifier)skill.s[9] += proficiency;
      if (skill.s[14] == IntModifier)skill.s[14] += proficiency;
    } else if (story == "Noble") {
      if (skill.s[5] == IntModifier)skill.s[5] += proficiency;
      if (skill.s[13] == ChaModifier)skill.s[13] += proficiency;
    } else if (story == "Outlander") {
      if (skill.s[3] == StrModifier)skill.s[3] += proficiency;
      if (skill.s[17] == WisModifier)skill.s[17] += proficiency;
    } else if (story == "Sage") {
      if (skill.s[2] == IntModifier)skill.s[2] += proficiency;
      if (skill.s[5] == IntModifier)skill.s[5] += proficiency;
    } else if (story == "Sailor") {
      if (skill.s[3] == StrModifier)skill.s[3] += proficiency;
      if (skill.s[11] == WisModifier)skill.s[11] += proficiency;
    } else if (story == "Soldier") {
      if (skill.s[3] == StrModifier)skill.s[3] += proficiency;
      if (skill.s[7] == ChaModifier)skill.s[7] += proficiency;
    } else if (story == "Urchin") {
      if (skill.s[15] == DexModifier)skill.s[15] += proficiency;
      if (skill.s[16] == DexModifier)skill.s[16] += proficiency;
    }
  }

  void Set(int a, int b) {// a - what parameter will be changed, b - modifier(can be negative)
    if (a < 0) {
      printf("%s \n", "some error occur, parameter < 0 to be changed. Try another value.");
      int ca = 0;
      cin >> ca;
      while (ca < 0 || ca > 0) {
        printf("%s \n", "some error occur, parameter has to be changed. Try again");
        cin >> ca;
      }
      Set(ca, b);
    }
    if (a == 1) { experience += b; }
    else if (a == 2) { health += b; }
    else if (a == 3) { Str += b; }
    else if (a == 4) { Dex += b; }
    else if (a == 5) { Con += b; }
    else if (a == 6) { Int += b; }
    else if (a == 7) { Wis += b; }
    else if (a == 8) { Cha += b; }
    else if (a == 9) { AC += b; }
    else if (a == 10) { if (b < 0)deathsaves_f++; else deathsaves_s++; }
    else if (a == 11) { printf("%s \n", "reserved for skills"); }
    else if (a == 12) { printf("%s \n", "reserved for weapon"); }
    else if (a == 13) { printf("%s \n", "reserved for inventory"); }
    else if (a == 14) { printf("%s \n", "reserved for story/background"); }
    else {
      printf("%s \n", "some error occur, parameter > 14 to be changed. Try again");
      int ca = 0;
      cin >> ca;
      while (ca < 0 || ca > 0) {
        printf("%s \n", "some error occur, parameter has to be changed. Try again");
        cin >> ca;
      }
      Set(ca, b);
    }

  }

  int Get(int a) {
    if (a < 0) {
      printf("%s \n", "Some error occur, parameter < 0 to be changed. Try another value.");
      int ca = 0;
      cin >> ca;
      while (ca < 0 || ca > 0) {
        printf("%s \n", "Some error occur, parameter has to be changed. Try again");
        cin >> ca;
      }
      Get(ca);
    }
    if (a == 1) { return experience; }
    else if (a == 2) { return health; }
    else if (a == 3) { return Str; }
    else if (a == 4) { return Dex; }
    else if (a == 5) { return Con; }
    else if (a == 6) { return Int; }
    else if (a == 7) { return Wis; }
    else if (a == 8) { return Cha; }
    else if (a == 9) { return AC; }
    else if (a == 10) {
      string message = "Failures: " + to_string(deathsaves_f) + " Successes: " + to_string(deathsaves_s);
    } else if (a == 11) {
      printf("%s \n", "reserved for skills");
      return 0;
    } else if (a == 12) {
      printf("%s \n", "reserved for weapon");
      return 0;
    } else if (a == 13) {
      printf("%s \n", "reserved for inventory");
      return 0;
    } else if (a == 14) {
      printf("%s \n", "reserved for story/background");
      return 0;
    } else if (a == 15) { return passive_perception; }
    else {
      printf("%s \n", "Some error occur, parameter > 15 to be changed. Try once again");
      int ca = 0;
      cin >> ca;
      while (ca < 0 || ca > 0) {
        printf("%s \n", "Some error occur, parameter has to be changed. Try again");
        cin >> ca;
      }
      Get(ca);
    }
    return -1;
  }

  void Level_Up() {
    if (level < 4 && experience > 300 * pow(3, level - 1)) {
      level++;
      proficiency++;
      printf("%s \n",
             "Character leveled up, your health increased, choose the way: roll dices(1) or take a middle(2)?");
      int lv = 0;
      while (lv < 1 || lv > 2) { cin >> lv; }
      if (lv == 1) {
        int tHP = rand() % health_dice - 1 + 1;
        printf("%s %d \n", "Rolled health + Constitution modifier:", tHP + ConModifier);
        maxhealth += tHP + ConModifier;
        health = maxhealth;
      }//role dices
      else {
        maxhealth += health_dice / 2 + 1;
        health = maxhealth;
      }//take middle
      printf("%s %d %s \n",
             "You reached",
             level,
             " level, that means that you have to choose whether improve one ability +2(type 1) or two abilities +1(type 2)");
      int ablv = -1;//abilityLevel_Up
      cin >> ablv;
      while (ablv < 0 || ablv > 2) {
        printf("%s \n", "You choose inappropriate value. Try 1 or 2.");
        cin >> ablv;
      }
      if (ablv == 1) {
        printf("%s \n", "What ability do you want to improve +2 ? Str(1),Dex(2),Con(3),Int(4),Wis(5),Cha(6)");
        cin >> ablv;
        while (ablv < 0 || ablv > 6) {
          printf("%s \n", "You choose inappropriate value. Try from 1 to 6.");
          cin >> ablv;
        }
        Set(ablv + 2, 2);
      } else {
        printf("%s \n",
               "What abilityes do you want to improve +1 ? Str(1),Dex(2),Con(3),Int(4),Wis(5),Cha(6) *Type 2 spaced numbers*");
        int ablv1 = 0;
        cin >> ablv >> ablv1;
        while ((ablv < 0 | ablv > 6) || (ablv1 < 0 || ablv1 > 6)) {
          printf("%s \n", "One or both values incorrect. Try from 1 to 6.");
          cin >> ablv >> ablv1;
        }
        Set(ablv + 2, 1);
        Set(ablv1 + 2, 1);
      }
      Level_Up();
      /*printf("%s \n", "reserved for skill Level_Up");*/} else if (level == 4 && experience > 6499) {
      level++;
      printf("%s \n",
             "Character leveled up, your health increased, choose the way: roll dices(1) or take a middle(2)?");
      int lv = 0;
      while (lv < 1 || lv > 2) { cin >> lv; }
      if (lv == 1) {
        int tHP = rand() % health_dice - 1 + 1;
        printf("%s %d \n", "Rolled health + Constitution modifier:", tHP + ConModifier);
        maxhealth += tHP + ConModifier;
        health = maxhealth;
      }//role dices
      else {
        maxhealth += health_dice / 2 + 1;
        health = maxhealth;
      }//take middle
      Level_Up();
      /*printf("%s \n", "reserved for skill Level_Up");*/}//proficiency+1, skills(2 points to one or 1 point to two)
    else if (level == 5 && experience > 13999) {
      level++;
      printf("%s \n",
             "Character leveled up, your health increased, choose the way: roll dices(1) or take a middle(2)?");
      int lv = 0;
      while (lv < 1 || lv > 2) { cin >> lv; }
      if (lv == 1) {
        int tHP = rand() % health_dice - 1 + 1;
        printf("%s %d \n", "Rolled health + Constitution modifier:", tHP + ConModifier);
        maxhealth += tHP + ConModifier;
        health = maxhealth;
      }//role dices
      else {
        maxhealth += health_dice / 2 + 1;
        health = maxhealth;
      }//take middle
      Level_Up();
      /*printf("%s \n", "reserved for skill Level_Up");*/} else if (level == 6 && experience > 22999) {
      level++;
      printf("%s \n",
             "Character leveled up, your health increased, choose the way: roll dices(1) or take a middle(2)?");
      int lv = 0;
      while (lv < 1 || lv > 2) { cin >> lv; }
      if (lv == 1) {
        int tHP = rand() % health_dice - 1 + 1;
        printf("%s %d \n", "Rolled health + Constitution modifier:", tHP + ConModifier);
        maxhealth += tHP + ConModifier;
        health = maxhealth;
      }//role dices
      else {
        maxhealth += health_dice / 2 + 1;
        health = maxhealth;
      }//take middle
      Level_Up();
      /*printf("%s \n", "reserved for skill Level_Up");*/} else if (level == 7 && experience > 33999) {
      level++;
      proficiency++;
      printf("%s \n",
             "Character leveled up, your health increased, choose the way: roll dices(1) or take a middle(2)?");
      int lv = 0;
      while (lv < 1 || lv > 2) { cin >> lv; }
      if (lv == 1) {
        int tHP = rand() % health_dice - 1 + 1;
        printf("%s %d \n", "Rolled health + Constitution modifier:", tHP + ConModifier);
        maxhealth += tHP + ConModifier;
        health = maxhealth;
      }//role dices
      else {
        maxhealth += health_dice / 2 + 1;
        health = maxhealth;
      }//take middle
      printf("%s %d %s \n",
             "You reached",
             level,
             " level, that means that you have to choose whether improve one ability +2(type 1) or two abilities +1(type 2)");
      int ablv = -1;//abilityLevel_Up
      cin >> ablv;
      while (ablv < 0 || ablv > 2) {
        printf("%s \n", "You choose inappropriate value. Try 1 or 2.");
        cin >> ablv;
      }
      if (ablv == 1) {
        printf("%s \n", "What ability do you want to improve +2 ? Str(1),Dex(2),Con(3),Int(4),Wis(5),Cha(6)");
        cin >> ablv;
        while (ablv < 0 || ablv > 6) {
          printf("%s \n", "You choose inappropriate value. Try from 1 to 6.");
          cin >> ablv;
        }
        Set(ablv + 2, 2);
      } else {
        printf("%s \n",
               "What abilityes do you want to improve +1 ? Str(1),Dex(2),Con(3),Int(4),Wis(5),Cha(6) *Type 2 spaced numbers*");
        int ablv1 = 0;
        cin >> ablv >> ablv1;
        while ((ablv < 0 || ablv > 6) || (ablv1 < 0 || ablv1 > 6)) {
          printf("%s \n", "One or both values incorrect. Try from 1 to 6.");
          cin >> ablv >> ablv1;
        }
        Set(ablv + 2, 1);
        Set(ablv1 + 2, 1);
      }
      Level_Up();
      /*printf("%s \n", "reserved for skill Level_Up");*/} else if (level == 8 && experience > 47999) {
      level++;
      printf("%s \n",
             "Character leveled up, your health increased, choose the way: roll dices(1) or take a middle(2)?");
      int lv = 0;
      while (lv < 1 || lv > 2) { cin >> lv; }
      if (lv == 1) {
        int tHP = rand() % health_dice - 1 + 1;
        printf("%s %d \n", "Rolled health + Constitution modifier:", tHP + ConModifier);
        maxhealth += tHP + ConModifier;
        health = maxhealth;
      }//role dices
      else {
        maxhealth += health_dice / 2 + 1;
        health = maxhealth;
      }//take middle
      Level_Up();
      /*printf("%s \n", "reserved for skill Level_Up");*/}//proficiency+1, skills2 points to one or 1 point to two)
    else if (level == 9 && experience > 64999) {
      level++;
      printf("%s \n",
             "Character leveled up, your health increased, choose the way: roll dices(1) or take a middle(2)?");
      int lv = 0;
      while (lv < 1 || lv > 2) { cin >> lv; }
      if (lv == 1) {
        int tHP = rand() % health_dice - 1 + 1;
        printf("%s %d \n", "Rolled health + Constitution modifier:", tHP + ConModifier);
        maxhealth += tHP + ConModifier;
        health = maxhealth;
      }//role dices
      else {
        maxhealth += health_dice / 2 + 1;
        health = maxhealth;
      }//take middle
      Level_Up();
      /*printf("%s \n", "reserved for skill Level_Up");*/}
    printf("%s %d \n", "Your level:", level);
    printf("%s %d \n", "Your health:", health);
  }

  void SetSkill(skills c) {
    for (int j = 0; j < 18; j++) {
      if (j == 0 || j == 2 || j == 5 || j == 8 || j == 10 ||
          j == 14) { c.s[j] += IntModifier; }//acrobatics,arcana,history,investigation,nature,religion
      else if (j == 1 || j == 6 || j == 9 || j == 11 ||
          j == 17) { c.s[j] += WisModifier; }//animalHandling,.s[6],medicine,perception,survival
      else if (j == 3) { c.s[j] += StrModifier; }//athletics
      else if (j == 4 || j == 7 || j == 12 ||
          j == 13) { c.s[j] += ChaModifier; }//deception,intimidation,performance,persuasion
      else if (j == 15 || j == 16) { c.s[j] += DexModifier; }//sleightOfHand,stealth
    }
  }

  void GetSkill(skills c) {
    string a = "acrobatics" + to_string(c.s[0]) + " animalHandling " + to_string(c.s[1]) + " arcana " +
        to_string(c.s[2]) + " athletics " + to_string(c.s[3]) + " deception " + to_string(c.s[4]) +
        " history " + to_string(c.s[5]) + " insight " + to_string(c.s[6]) + " intimidation " +
        to_string(c.s[7]) + " investigation " + to_string(c.s[8]) + " medicine " + to_string(c.s[9]) +
        " nature " + to_string(c.s[10]) + " perception " + to_string(c.s[11]) + " performance " +
        to_string(c.s[12]) + " persuasion " + to_string(c.s[13]) + " religion " + to_string(c.s[14]) +
        " sleightOfHand " + to_string(c.s[15]) + " stealth " + to_string(c.s[16]) + " survival " +
        to_string(c.s[17]);
    cout << a;
  }
};




