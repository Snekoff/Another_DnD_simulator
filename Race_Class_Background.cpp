
#include "interface_races_classes_background.h"
#include <iostream>

class race{
private:
    int type;
public:
    virtual void set(){}
    virtual int get(){}
};

class Class{
private:
    int type;
public:
    virtual void set(){}
    virtual int get(){}
};
class Background{
private:
    int story;
public:
    virtual void set(){}
    virtual int get(){}
};
