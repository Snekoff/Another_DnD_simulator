#pragma once
#include <iostream>
#include <string>
#include "interface_races_classes_background.h"
#include "Race_Class_Background.cpp"
using namespace std;

struct skills{
    int s[18] = {0};/* acrobatics 0,animalHandling 1,arcana 2,athletics 3,deception 4,
history 5,insight 6,intimidation 7,investigation 8,medicine 9,
nature 10,perception 11,performance 12,persuasion 13,religion 14,
sleightOfHand 15,stealth 16,survival 17*/
};
struct weapon{ //I`m going to add here something like interface or database

};

class character{
private:
    race Race;
    Class classType;
    string storyline;
    int level;
    int experience;
    int Health;
    int maxHealth;
    int diceOfHealth;
    int Str,Dex,Con,Int,Wis,Cha;
    int StrM,DexM,ConM,IntM,WisM,ChaM;
    int AC;
    int deathSavesS,deathSavesF;//success/failure
    int prof;
    int passivePerception;
    skills skill;
    weapon w;
    string inventory;
public:
    character(){}
    ~character(){}
    void setF(string a, string b, string story, int l, int h, int s,int d, int c,int i, int w, int cha){
        if(a == ""){a = "human";}
        if(b == ""){b = "barbarian";}
        if(story == ""){story = "Acolyte";}
        if(l < 0) l = 0; if(h < 0) h = 0; if(s < 0) s = 0;if(d < 0) d = 0;if(c < 0) c = 0;if(i < 0) i = 0;if(w < 0) w = 0;if(cha < 0) cha = 0;
        //race = a;classType = b;
        level = l;Health = h;maxHealth = h;
        Str = s;Dex = d;Con = c;Int = i;Wis = w;Cha = cha;
        StrM = (Str - 10)/2;DexM = (DexM-10)/2;ConM = (ConM-10)/2;IntM = (IntM-10)/2;WisM = (WisM-10)/2;ChaM = (ChaM-10)/2;
        setSkill(skill);
        if(level < 4)prof = 2;
        else if(level > 3 && level < 8)prof = 3;
        else prof = 4;
        passivePerception = 10 + WisM; // if creature have advantage +5 if disadvantage -5
        printf("%s \n", "Your class allows you to get a proficiency skills, your proficiency bonus will be added to them that will made you stronger or smarter, depends what you choose.");
        /*if(classType == "Barbarian"){diceOfHealth = 12;
        printf("%s \n", "Choose two from Animal Handling, Athletic, Intimidation, Nature, Perception and Survival");
        }// save throws, skills,
        else if(classType == "Bard"){diceOfHealth = 8;
            printf("%s \n", "Choose any three ");
        }
        else if(classType == "Cleric"){diceOfHealth = 8;
            printf("%s \n", "Choose two from History, .s[6], Medicine, Persuasion and Religion");
        }
        else if(classType == "Druid"){diceOfHealth = 8;
            printf("%s \n", "Choose two from Arcana, Animal Handling, .s[6], Medicine, Nature, Perception, Religion and Survival");
        }
        else if(classType == "Fighter"){diceOfHealth = 10;
            printf("%s \n", "Choose two from Acrobatics, AnimalHandling, Athletics, History, .s[6], Intimidation, Perception and Survival");
        }
        else if(classType == "Monk"){diceOfHealth = 8;
            printf("%s \n", "Choose two from Acrobatics, Athletics, History, .s[6], Religion, and Stealth");
        }
        else if(classType == "Paladin"){diceOfHealth = 10;
            printf("%s \n", "Choose two from Athletics, .s[6], Intimidation, Medicine, Persuasion, and Religion");
        }
        else if(classType == "Ranger"){diceOfHealth = 10;
            printf("%s \n", "Choose two from Animal Handling, Athletics, .s[6], Investigation, Nature, Perception, Stealth and Survival");
        }
        else if(classType == "Rouge"){diceOfHealth = 8;
            printf("%s \n", "Choose four from Acrobatics, Athletics, Deception, .s[6], Intimidation, Investigation, Perception, Performance, Persuasion, Sleight of Hand and Stealth");
        }
        else if(classType == "Sorcerer"){diceOfHealth = 6;
            printf("%s \n", "Choose two from Arcana, Deception, .s[6], Intimidation, Persuasion, and Religion");
        }
        else if(classType == "Warlock"){diceOfHealth = 8;
            printf("%s \n", "Choose two from Arcana, Deception, History, Intimidation, Investigation, Nature, and Religion");
        }
        else if(classType == "Wizard"){diceOfHealth = 6;
            printf("%s \n", "Choose two from Arcana, History, .s[6], Investigation, Medicine, and Religion");
        }*/
        if(story == "Acolyte"){if(skill.s[6] == WisM)skill.s[6]+=prof; if(skill.s[14] == IntM)skill.s[14]+=prof; }
        else if(story == "Charlatan"){if(skill.s[4] == ChaM)skill.s[4]+=prof; if(skill.s[15] == DexM)skill.s[15]+=prof;}
        else if(story == "Criminal"){if(skill.s[4] == ChaM)skill.s[4]+=prof; if(skill.s[16] == DexM)skill.s[16]+=prof;}
        else if(story == "Entertainer"){if(skill.s[0] == IntM)skill.s[0]+=prof; if(skill.s[12] == ChaM)skill.s[12]+=prof;}
        else if(story == "FolkHero"){if(skill.s[1] == WisM)skill.s[1]+=prof; if(skill.s[17] == WisM)skill.s[17]+=prof;}
        else if(story == "GuildArtisan"){if(skill.s[6] == WisM)skill.s[6]+=prof; if(skill.s[13] == ChaM)skill.s[13]+=prof;}
        else if(story == "Hermit"){if(skill.s[9] == WisM)skill.s[9]+=prof; if(skill.s[14] == IntM)skill.s[14]+=prof;}
        else if(story == "Noble"){if(skill.s[5] == IntM)skill.s[5]+=prof; if(skill.s[13] == ChaM)skill.s[13]+=prof;}
        else if(story == "Outlander"){if(skill.s[3] == StrM)skill.s[3]+=prof; if(skill.s[17] == WisM)skill.s[17]+=prof;}
        else if(story == "Sage"){if(skill.s[2] == IntM)skill.s[2]+=prof; if(skill.s[5] == IntM)skill.s[5]+=prof;}
        else if(story == "Sailor"){if(skill.s[3] == StrM)skill.s[3]+=prof; if(skill.s[11] == WisM)skill.s[11]+=prof;}
        else if(story == "Soldier"){if(skill.s[3] == StrM)skill.s[3]+=prof; if(skill.s[7] == ChaM)skill.s[7]+=prof;}
        else if(story == "Urchin"){if(skill.s[15] == DexM)skill.s[15]+=prof; if(skill.s[16] == DexM)skill.s[16]+=prof;}
    }
    void set(int a, int b){// a - what parameter will be changed, b - modifier(can be negative)
        if(a <0){
            printf("%s \n","some error occur, parameter < 0 to be changed. Try another value.");
            int ca = 0;
            cin >> ca;
            while(ca < 0 || ca > 0){
                printf("%s \n", "some error occur, parameter has to be changed. Try again");
                cin >> ca;
            }
            set(ca,b);
        }
        if(a == 1){experience+=b;}
        else if(a == 2){Health+=b;}
        else if(a == 3){Str+=b;}
        else if(a == 4){Dex+=b;}
        else if(a == 5){Con+=b;}
        else if(a == 6){Int+=b;}
        else if(a == 7){Wis+=b;}
        else if(a == 8){Cha+=b;}
        else if(a == 9){AC+=b;}
        else if(a == 10){if(b < 0)deathSavesF++;else deathSavesS++;}
        else if(a == 11){printf("%s \n","reserved for skills");}
        else if(a == 12){printf("%s \n","reserved for weapon");}
        else if(a == 13){printf("%s \n","reserved for inventory");}
        else if(a == 14){printf("%s \n","reserved for story/background");}
        else {
            printf("%s \n", "some error occur, parameter > 14 to be changed. Try again");
            int ca = 0;
            cin >> ca;
            while(ca < 0 || ca > 0){
                printf("%s \n", "some error occur, parameter has to be changed. Try again");
                cin >> ca;
            }
            set(ca,b);
        }

    }
    int get(int a){
        if(a <0){
            printf("%s \n","Some error occur, parameter < 0 to be changed. Try another value.");
            int ca = 0;
            cin >> ca;
            while(ca < 0 || ca > 0){
                printf("%s \n", "Some error occur, parameter has to be changed. Try again");
                cin >> ca;
            }
            get(ca);
        }
        if(a == 1){return experience;}
        else if(a == 2){return Health;}
        else if(a == 3){return Str;}
        else if(a == 4){return Dex;}
        else if(a == 5){return Con;}
        else if(a == 6){return Int;}
        else if(a == 7){return Wis;}
        else if(a == 8){return Cha;}
        else if(a == 9){return AC;}
        else if(a == 10){string message = "Failures: " + to_string(deathSavesF) + " Successes: " + to_string(deathSavesS);}
        else if(a == 11){printf("%s \n","reserved for skills");return 0;}
        else if(a == 12){printf("%s \n","reserved for weapon");return 0;}
        else if(a == 13){printf("%s \n","reserved for inventory");return 0;}
        else if(a == 14){printf("%s \n","reserved for story/background");return 0;}
        else if(a == 15){return passivePerception;}
        else {
            printf("%s \n", "Some error occur, parameter > 15 to be changed. Try once again");
            int ca = 0;
            cin >> ca;
            while(ca < 0 || ca > 0){
                printf("%s \n", "Some error occur, parameter has to be changed. Try again");
                cin >> ca;
            }
            get(ca);
        }
        return -1;
    }
    void levelUp(){
        if(level < 4 && experience > 300*pow(3,level - 1)){level++;
            prof++;
            printf("%s \n", "Character leveled up, your health increased, choose the way: roll dices(1) or take a middle(2)?");
            int lv = 0; while(lv < 1 || lv > 2){cin >> lv;}
            if(lv == 1){int tHP = rand() %diceOfHealth-1 +1;printf("%s %d \n", "Rolled Health + Constitution modifier:", tHP + ConM);maxHealth += tHP + ConM;Health = maxHealth;}//role dices
            else{maxHealth += diceOfHealth/2 + 1;Health = maxHealth;}//take middle
            printf("%s %d %s \n", "You reached", level, " level, that means that you have to choose whether improve one ability +2(type 1) or two abilities +1(type 2)");
            int ablv = -1;//abilityLevelUp
            cin >> ablv;
            while(ablv < 0 && ablv > 2){
                printf("%s \n","You choose inappropriate value. Try 1 or 2.");
                cin >> ablv;
            }
            if(ablv == 1){
                printf("%s \n", "What ability do you want to improve +2 ? Str(1),Dex(2),Con(3),Int(4),Wis(5),Cha(6)");
                cin >> ablv;
                while(ablv < 0 && ablv > 6){
                    printf("%s \n","You choose inappropriate value. Try from 1 to 6.");
                    cin >> ablv;
                }
                set(ablv+2,2);
            }
            else{
                printf("%s \n", "What abilityes do you want to improve +1 ? Str(1),Dex(2),Con(3),Int(4),Wis(5),Cha(6) *Type 2 spaced numbers*");
                int ablv1 = 0;
                cin >> ablv >> ablv1;
                while((ablv < 0 && ablv > 6) ||(ablv1 < 0 && ablv1 > 6)){
                    printf("%s \n","One or both values incorrect. Try from 1 to 6.");
                    cin >> ablv >> ablv1;
                }
                set(ablv+2,1);
                set(ablv1+2,1);
            }
            levelUp();
            /*printf("%s \n", "reserved for skill levelUp");*/}
        else if(level == 4 && experience > 6499){
            level++;
            printf("%s \n", "Character leveled up, your health increased, choose the way: roll dices(1) or take a middle(2)?");
            int lv = 0; while(lv < 1 || lv > 2){cin >> lv;}
            if(lv == 1){int tHP = rand() %diceOfHealth-1 +1;printf("%s %d \n", "Rolled Health + Constitution modifier:", tHP + ConM );maxHealth += tHP + ConM;Health = maxHealth;}//role dices
            else{maxHealth += diceOfHealth/2 + 1;Health = maxHealth;}//take middle
            levelUp();
            /*printf("%s \n", "reserved for skill levelUp");*/}//prof+1, skills(2 points to one or 1 point to two)
        else if(level == 5 && experience > 13999){
            level++;
            printf("%s \n", "Character leveled up, your health increased, choose the way: roll dices(1) or take a middle(2)?");
            int lv = 0; while(lv < 1 || lv > 2){cin >> lv;}
            if(lv == 1){int tHP = rand() %diceOfHealth-1 +1;printf("%s %d \n", "Rolled Health + Constitution modifier:", tHP + ConM );maxHealth += tHP + ConM;Health = maxHealth;}//role dices
            else{maxHealth += diceOfHealth/2 + 1;Health = maxHealth;}//take middle
            levelUp();
            /*printf("%s \n", "reserved for skill levelUp");*/}
        else if(level == 6 && experience > 22999){level++;
            printf("%s \n", "Character leveled up, your health increased, choose the way: roll dices(1) or take a middle(2)?");
            int lv = 0; while(lv < 1 || lv > 2){cin >> lv;}
            if(lv == 1){int tHP = rand() %diceOfHealth-1 +1;printf("%s %d \n", "Rolled Health + Constitution modifier:", tHP + ConM );maxHealth += tHP + ConM;Health = maxHealth;}//role dices
            else{maxHealth += diceOfHealth/2 + 1;Health = maxHealth;}//take middle
            levelUp();
            /*printf("%s \n", "reserved for skill levelUp");*/}
        else if(level == 7 && experience > 33999){level++;prof++;
            printf("%s \n", "Character leveled up, your health increased, choose the way: roll dices(1) or take a middle(2)?");
            int lv = 0; while(lv < 1 || lv > 2){cin >> lv;}
            if(lv == 1){int tHP = rand() %diceOfHealth-1 +1;printf("%s %d \n", "Rolled Health + Constitution modifier:", tHP + ConM );maxHealth += tHP + ConM;Health = maxHealth;}//role dices
            else{maxHealth += diceOfHealth/2 + 1;Health = maxHealth;}//take middle
            printf("%s %d %s \n", "You reached", level, " level, that means that you have to choose whether improve one ability +2(type 1) or two abilities +1(type 2)");
            int ablv = -1;//abilityLevelUp
            cin >> ablv;
            while(ablv < 0 && ablv > 2){
                printf("%s \n","You choose inappropriate value. Try 1 or 2.");
                cin >> ablv;
            }
            if(ablv == 1){
                printf("%s \n", "What ability do you want to improve +2 ? Str(1),Dex(2),Con(3),Int(4),Wis(5),Cha(6)");
                cin >> ablv;
                while(ablv < 0 && ablv > 6){
                    printf("%s \n","You choose inappropriate value. Try from 1 to 6.");
                    cin >> ablv;
                }
                set(ablv+2,2);
            }
            else{
                printf("%s \n", "What abilityes do you want to improve +1 ? Str(1),Dex(2),Con(3),Int(4),Wis(5),Cha(6) *Type 2 spaced numbers*");
                int ablv1 = 0;
                cin >> ablv >> ablv1;
                while((ablv < 0 && ablv > 6) ||(ablv1 < 0 && ablv1 > 6)){
                    printf("%s \n","One or both values incorrect. Try from 1 to 6.");
                    cin >> ablv >> ablv1;
                }
                set(ablv+2,1);
                set(ablv1+2,1);
            }
            levelUp();
            /*printf("%s \n", "reserved for skill levelUp");*/}
        else if(level == 8 && experience > 47999){level++;
            printf("%s \n", "Character leveled up, your health increased, choose the way: roll dices(1) or take a middle(2)?");
            int lv = 0; while(lv < 1 || lv > 2){cin >> lv;}
            if(lv == 1){int tHP = rand() %diceOfHealth-1 +1;printf("%s %d \n", "Rolled Health + Constitution modifier:", tHP + ConM );maxHealth += tHP + ConM;Health = maxHealth;}//role dices
            else{maxHealth += diceOfHealth/2 + 1;Health = maxHealth;}//take middle
            levelUp();
            /*printf("%s \n", "reserved for skill levelUp");*/}//prof+1, skills2 points to one or 1 point to two)
        else if(level == 9 && experience > 64999){level++;
            printf("%s \n", "Character leveled up, your health increased, choose the way: roll dices(1) or take a middle(2)?");
            int lv = 0; while(lv < 1 || lv > 2){cin >> lv;}
            if(lv == 1){int tHP = rand() %diceOfHealth-1 +1;printf("%s %d \n", "Rolled Health + Constitution modifier:", tHP + ConM );maxHealth += tHP + ConM;Health = maxHealth;}//role dices
            else{maxHealth += diceOfHealth/2 + 1;Health = maxHealth;}//take middle
            levelUp();
            /*printf("%s \n", "reserved for skill levelUp");*/}
        printf("%s %d \n", "Your level:", level );
        printf("%s %d \n", "Your Health:", Health );
    }
    void setSkill(skills c){
        for(int j = 0;j<18;j++){
            if(j == 0 || j == 2|| j == 5|| j == 8|| j == 10|| j == 14){ c.s[j]+=IntM; }//acrobatics,arcana,history,investigation,nature,religion
            else if(j == 1|| j == 6|| j == 9|| j == 11|| j == 17){ c.s[j]+=WisM; }//animalHandling,.s[6],medicine,perception,survival
            else if(j == 3){ c.s[j]+=StrM; }//athletics
            else if(j == 4|| j == 7|| j == 12|| j == 13){ c.s[j]+=ChaM; }//deception,intimidation,performance,persuasion
            else if(j == 15|| j == 16){ c.s[j]+=DexM; }//sleightOfHand,stealth
        }
    }
    void getSkill(skills c){
        string a = "acrobatics" + to_string(c.s[0]) + " animalHandling " +to_string(c.s[1]) + " arcana " + to_string(c.s[2]) + " athletics "+ to_string(c.s[3])+" deception "+to_string(c.s[4])+ " history " +to_string(c.s[5])+ " insight " +to_string(c.s[6])+ " intimidation " +to_string(c.s[7])+ " investigation " +to_string(c.s[8])+ " medicine " +to_string(c.s[9])+ " nature " +to_string(c.s[10])+ " perception " +to_string(c.s[11])+ " performance " +to_string(c.s[12])+ " persuasion " +to_string(c.s[13])+ " religion " +to_string(c.s[14])+ " sleightOfHand " +to_string(c.s[15])+ " stealth " +to_string(c.s[16])+ " survival " +to_string(c.s[17]);
        cout << a;
    }
};




