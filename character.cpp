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

    }
};




