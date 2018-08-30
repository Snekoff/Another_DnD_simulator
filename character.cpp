#pragma once

#include <string>
using namespace std;

struct skills{

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
        race = a;classType = b;level = l;Health = h;
        Str = s;Dex = d;Con = c;Int = i;Wis = w;Cha = cha;
    }
    void set(int a, int b){// a - what parameter will be changed, b - modifier(can be negative)
        if(a <0){printf("%s \n","some error occur, parameter < 0 to be changed, parameter = 1");a = 1;}
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


    }
};




