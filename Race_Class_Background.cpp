
#include "interface_races_classes_background.h"
#include <iostream>
#include "Skills_and_Spells.cpp"

class race{
private:
    int type;
    int height,weight,age;
    int minHeight[61];
    int maxHeight[61];
    int minWeight[61];
    int maxWeight[61];
    int minAge[61];
    int maxAge[61];
protected:
    Spell spell;
    std::string raceFeatures;// Movement,Size,Height,Weight,Darkvision,skill like firebreath,type of damage resistance,Languages//
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
Dragonborn
Str +2; Cha +1
6+

Dwarf (Duergar)
Str +1; Con +2
4-5

Dwarf (Hill)
Con +2; Wis +1
4-5

Dwarf (Mountain)
Str +2; Con +2
4-5

Elf (Drow)
Dex +2; Cha +1
5-6

Elf (Eladrin)
Dex +2; Int +1
5-6

Elf (Eladrin)
Dex +2; Cha +1
5-6

Elf (High)
Dex +2; Int +1
5-6

Elf (Sea)
Dex +2; Con +1
5-6

Elf (Shadar-kai)
Dex +2; Con +1
5-6

Elf (Wood)
Dex +2; Wis +1
5-6

Gnome (Deep/Svirfneblin)
Dex +1; Int +2
3-3.5 Small

Gnome (Forest)
Dex +1; Int +2
3-4 Small

Gnome (Rock)
Con +1; Int +2
3-4 Small

Goblin
Dex +2; Con +1
3-4 Small

Half-Elf
Cha +2; Any other two +1
5-6

Half-Elf (Aquatic Elf Descent)
Cha +2; Any other two +1
5-6

Half-Elf (Drow Descent)
Cha +2; Any other two +1
5-6

Half-Elf (Moon Elf or Sun Elf Descent)
Cha +2; Any other two +1
5-6

Half-Elf (Wood Elf Descent)
Cha +2; Any other two +1
5-6

Half-Orc
Str +2; Con +1
5-6

Halfling (Ghostwise)
Dex +2; Wis +1
3 Small

Halfling (Lightfoot)
Dex +2; Cha +1
3 Small

Halfling (Stout)
Dex +2; Con +1
3 Small

Human
Str +1; Dex +1; Con +1; Int +1; Wis +1; Cha +1
5-6

Human (Variant)
Any two +1
5-6

Lizardfolk
Con +2; Wis +1
5-6

Orc
Str +2; Con +1; Int -2
6

Tiefling
Int +1; Cha +2
5-6

Tiefling (Asmodeus)
Int +1; Cha +2
5-6

Tiefling (Baalzebul)
Int +1; Cha +2
5-6

Tiefling (Dispater)
Dex +1; Cha +2
5-6

Tiefling (Fierna)
Wis +1; Cha +2
5-6

Tiefling (Glasya)
Dex +1; Cha +2
5-6

Tiefling (Levistus)
Con +1; Cha +2
5-6

Tiefling (Mammon)
Int +1; Cha +2
5-6

Tiefling (Mephistopheles)
Int +1; Cha +2
5-6

Tiefling (Variant)
Int +1; Dex or Cha +2
5-6

Tiefling (Zariel)
Str +1; Cha +2
5-6

};*/
