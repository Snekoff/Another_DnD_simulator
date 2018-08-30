#pragma once
#include <iostream>
#include <string>
using namespace std;

struct skills{
    int acrobatics = 0,animalHandling = 0,arcana = 0,athletics = 0,deception = 0,history = 0,
    insight = 0,intimidation = 0,investigation = 0,medicine = 0,nature = 0,perception = 0,
    perfomance = 0,persuasion = 0,religion = 0,sleightOfHand = 0,stealth = 0,survival = 0;
};
struct weapon{

};

class character{
private:
    string race;
    string classType;
    int level;
    int experience;
    int Health;
    int maxHealth;
    int diceOfHealth;
    int Str,Dex,Con,Int,Wis,Cha;
    int AC;
    int deathSavesS,deathSavesF;//sucsess/failure
    int prof;
    int passivePerception;
    skills s;
    weapon w;
    string inventory;
public:
    character(){}
    ~character(){}
    void setF(string a,string b,int l,int h, int s,int d, int c,int i, int w, int cha){
        if(a == ""){a = "human";}
        if(b == ""){b = "barbarian";}
        if(l < 0) l = 0; if(h < 0) h = 0; if(s < 0) s = 0;if(d < 0) d = 0;if(c < 0) c = 0;if(i < 0) i = 0;if(w < 0) w = 0;if(cha < 0) cha = 0;
        race = a;classType = b;level = l;Health = h;maxHealth = h;
        Str = s;Dex = d;Con = c;Int = i;Wis = w;Cha = cha;
        if(level < 4)prof = 2;
        else if(level > 3 && level < 8)prof = 3;
        else prof = 4;
        if(classType == "Barbarian"){diceOfHealth = 12;}// save throws, skills
        else if(classType == "Bard"){diceOfHealth = 8;}
        else if(classType == "Cleric"){diceOfHealth = 8;}
        else if(classType == "Druid"){diceOfHealth = 8;}
        else if(classType == "Fighter"){diceOfHealth = 10;}
        else if(classType == "Monk"){diceOfHealth = 8;}
        else if(classType == "Paladin"){diceOfHealth = 10;}
        else if(classType == "Ranger"){diceOfHealth = 10;}
        else if(classType == "Rouge"){diceOfHealth = 8;}
        else if(classType == "Sorcerer"){diceOfHealth = 6;}
        else if(classType == "Warlock"){diceOfHealth = 8;}
        else if(classType == "Wizard"){diceOfHealth = 6;}
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
        else {
            printf("%s \n", "some error occur, parameter > 13 to be changed. Try again");
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
        else {
            printf("%s \n", "Some error occur, parameter > 13 to be changed. Try once again");
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
            if(lv == 1){int tHP = rand() %diceOfHealth-1 +1;printf("%s %d \n", "Rolled Health + Constitution modifier:", tHP + (Con - 10)/2 );maxHealth += tHP + (Con - 10)/2;Health = maxHealth;}//role dices
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
            if(lv == 1){int tHP = rand() %diceOfHealth-1 +1;printf("%s %d \n", "Rolled Health + Constitution modifier:", tHP + (Con - 10)/2 );maxHealth += tHP + (Con - 10)/2;Health = maxHealth;}//role dices
            else{maxHealth += diceOfHealth/2 + 1;Health = maxHealth;}//take middle
            levelUp();
            /*printf("%s \n", "reserved for skill levelUp");*/}//prof+1, skills(2 points to one or 1 point to two)
        else if(level == 5 && experience > 13999){
            level++;
            printf("%s \n", "Character leveled up, your health increased, choose the way: roll dices(1) or take a middle(2)?");
            int lv = 0; while(lv < 1 || lv > 2){cin >> lv;}
            if(lv == 1){int tHP = rand() %diceOfHealth-1 +1;printf("%s %d \n", "Rolled Health + Constitution modifier:", tHP + (Con - 10)/2 );maxHealth += tHP + (Con - 10)/2;Health = maxHealth;}//role dices
            else{maxHealth += diceOfHealth/2 + 1;Health = maxHealth;}//take middle
            levelUp();
            /*printf("%s \n", "reserved for skill levelUp");*/}
        else if(level == 6 && experience > 22999){level++;
            printf("%s \n", "Character leveled up, your health increased, choose the way: roll dices(1) or take a middle(2)?");
            int lv = 0; while(lv < 1 || lv > 2){cin >> lv;}
            if(lv == 1){int tHP = rand() %diceOfHealth-1 +1;printf("%s %d \n", "Rolled Health + Constitution modifier:", tHP + (Con - 10)/2 );maxHealth += tHP + (Con - 10)/2;Health = maxHealth;}//role dices
            else{maxHealth += diceOfHealth/2 + 1;Health = maxHealth;}//take middle
            levelUp();
            /*printf("%s \n", "reserved for skill levelUp");*/}
        else if(level == 7 && experience > 33999){level++;prof++;
            printf("%s \n", "Character leveled up, your health increased, choose the way: roll dices(1) or take a middle(2)?");
            int lv = 0; while(lv < 1 || lv > 2){cin >> lv;}
            if(lv == 1){int tHP = rand() %diceOfHealth-1 +1;printf("%s %d \n", "Rolled Health + Constitution modifier:", tHP + (Con - 10)/2 );maxHealth += tHP + (Con - 10)/2;Health = maxHealth;}//role dices
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
            if(lv == 1){int tHP = rand() %diceOfHealth-1 +1;printf("%s %d \n", "Rolled Health + Constitution modifier:", tHP + (Con - 10)/2 );maxHealth += tHP + (Con - 10)/2;Health = maxHealth;}//role dices
            else{maxHealth += diceOfHealth/2 + 1;Health = maxHealth;}//take middle
            levelUp();
            /*printf("%s \n", "reserved for skill levelUp");*/}//prof+1, skills2 points to one or 1 point to two)
        else if(level == 9 && experience > 64999){level++;
            printf("%s \n", "Character leveled up, your health increased, choose the way: roll dices(1) or take a middle(2)?");
            int lv = 0; while(lv < 1 || lv > 2){cin >> lv;}
            if(lv == 1){int tHP = rand() %diceOfHealth-1 +1;printf("%s %d \n", "Rolled Health + Constitution modifier:", tHP + (Con - 10)/2 );maxHealth += tHP + (Con - 10)/2;Health = maxHealth;}//role dices
            else{maxHealth += diceOfHealth/2 + 1;Health = maxHealth;}//take middle
            levelUp();
            /*printf("%s \n", "reserved for skill levelUp");*/}
        printf("%s %d \n", "Your level:", level );
        printf("%s %d \n", "Your Health:", Health );
    }
};




