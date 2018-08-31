
#include "interface_races_classes_background.h"
#include <iostream>
#include "Skills_and_Spells.cpp"

class race{
private:
    int type;
protected:
    int height,weight,age;
    int minHeight[39]= {6,4,4,5,5,5,5,5,5,5,5,3,3,3,3,5,5,5,5,5,5,3,3,3,5,5,5,6,5,5,5,5,5,5,5,5,5,5,5};
    int maxHeight[39]= {6,5,5,6,6,6,6,6,6,6,6,4,4,4,4,6,6,6,6,6,6,3,3,3,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6};
    int minWeight[39]={10};
    int maxWeight[39]={140};
    int minAge[39] = {3};
    int maxAge[39] = {120};
    int Str,Dex,Con,Int,Wis,Cha;
    Spell spell;
    std::string raceFeatures;// Abilities0-5,Movement,Size,Darkvision,skill like firebreath,type of damage resistance,Languages//
public:
    race(){
        type = 0;
        height = 0;
        weight = 0;
        age = 0;
    }
    ~race(){}
    virtual void set(int a){
        type = a;
    }
    virtual void set(int a,int b,int c, int d){}
    virtual int get(){}
    void raceFeature(){}
};
class subRace : public race{
private:
    int subtype;
public:
    void subRaceFeatures(){}
};

class Class{
private:
    int type;
protected:
    std::string Features = "";
public:
    Class(){}
    ~Class(){}
    virtual void set(int a){}
    virtual void set(int a,int b,int c, int d){}
    virtual int get(){}
    void ClassFeatures(){}
};
class subClass : public Class{
private:
    int subtype;
public:
    void subClassFeatures(){}
};
/*
Dragonborn 0
Str +2; Cha +1
6+

Dwarf (Duergar) 1
Str +1; Con +2
4-5

Dwarf (Hill) 2
Con +2; Wis +1
4-5

Dwarf (Mountain) 3
Str +2; Con +2
4-5

Elf (Drow)4
Dex +2; Cha +1
5-6

Elf (Eladrin)5
Dex +2; Int +1
5-6

Elf (Eladrin)6
Dex +2; Cha +1
5-6

Elf (High)7
Dex +2; Int +1
5-6

Elf (Sea)8
Dex +2; Con +1
5-6

Elf (Shadar-kai)9
Dex +2; Con +1
5-6

Elf (Wood)10
Dex +2; Wis +1
5-6

Gnome (Deep/Svirfneblin)11
Dex +1; Int +2
3-3.5 Small

Gnome (Forest)12
Dex +1; Int +2
3-4 Small

Gnome (Rock)13
Con +1; Int +2
3-4 Small

Goblin 14
Dex +2; Con +1
3-4 Small

Half-Elf 15
Cha +2; Any other two +1
5-6

Half-Elf (Aquatic Elf Descent)16
Cha +2; Any other two +1
5-6

Half-Elf (Drow Descent)17
Cha +2; Any other two +1
5-6

Half-Elf (Moon Elf or Sun Elf Descent)18
Cha +2; Any other two +1
5-6

Half-Elf (Wood Elf Descent)19
Cha +2; Any other two +1
5-6

Half-Orc 20
Str +2; Con +1
5-6

Halfling (Ghostwise) 21
Dex +2; Wis +1
3 Small

Halfling (Lightfoot) 22
Dex +2; Cha +1
3 Small

Halfling (Stout) 23
Dex +2; Con +1
3 Small

Human 24
Str +1; Dex +1; Con +1; Int +1; Wis +1; Cha +1
5-6

Human (Variant) 25
Any two +1
5-6

Lizardfolk 26
Con +2; Wis +1
5-6

Orc 27
Str +2; Con +1; Int -2
6

Tiefling 28
Int +1; Cha +2
5-6

Tiefling (Asmodeus) 29
Int +1; Cha +2
5-6

Tiefling (Baalzebul) 30
Int +1; Cha +2
5-6

Tiefling (Dispater) 31
Dex +1; Cha +2
5-6

Tiefling (Fierna) 32
Wis +1; Cha +2
5-6

Tiefling (Glasya) 33
Dex +1; Cha +2
5-6

Tiefling (Levistus) 34
Con +1; Cha +2
5-6

Tiefling (Mammon) 35
Int +1; Cha +2
5-6

Tiefling (Mephistopheles) 36
Int +1; Cha +2
5-6

Tiefling (Variant) 37
Int +1; Dex or Cha +2
5-6

Tiefling (Zariel) 38
Str +1; Cha +2
5-6

};*/
