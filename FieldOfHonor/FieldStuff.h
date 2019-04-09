#pragma once
#include "../Character/UsefulFunctions.h"
#include "../Inventory(Item)/Item.h"
#include "../Inventory(Item)/Items_Factory.h"
#ifndef ANOTHER_DND_SIMULATOR_FIELDSTUFF_H
#define ANOTHER_DND_SIMULATOR_FIELDSTUFF_H
using namespace std;

class FieldStuff {
private:
    int id;
    string name;
    bool isActive;
    vector<Item> inventory_;
public:
    FieldStuff() = default;
    ~FieldStuff() = default;

    int GetInt(int what);

    string GetString(int which);

    bool GetBool(bool what);

    Item GetInventory();

    void SetInt(int what, int value);

    void SetString(int what, string value);

    void SetBool(int what, bool value);

    void SetInventory(vector<Item> items_);
};

class Furniture : public FieldStuff{
private:
    int hp;
    int type;
    int lock_id;
    int lock_hp;
    bool islocked;
};


#endif //ANOTHER_DND_SIMULATOR_FIELDSTUFF_H
