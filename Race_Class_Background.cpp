
#include "interface_races_classes_background.h"
#include <iostream>

class race{
private:
    int type;
protected:
    int height;
    int weight;
    int age;
    // spell Spell;
public:
    race(){}
    ~race(){}
    virtual void set(){}
    virtual int get(){}
};
class subRace : public race{
public:
    void subRaceFeatures(){}
};

class Class{
private:
    int type;
protected:
    //skill Skill;
    //spell Spell;

public:
    Class(){}
    ~Class(){}
    virtual void set(){}
    virtual int get(){}
};
class subClass : public Class{
public:
    void subClassFeatures(){}
};

/*class Background{
private:
    int story;
public:
    virtual void set(){}
    virtual int get(){}
};
class subBackground : public Background{
public:
    void subBackgroundFeatures(){}
};*/
