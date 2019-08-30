//
// MIT License
// Copyright (c) 2019 Snekoff. All rights reserved.
//
#pragma once
#include "../character/common_functions.h"
#include "../items/item.h"
#include "../items/items_factory.h"

#ifndef ANOTHER_DND_SIMULATOR_FIELDSTUFF_H
#define ANOTHER_DND_SIMULATOR_FIELDSTUFF_H

/*
 * Here are classes that are stored in each field/square.
 * Like what is in that position torch, trap, furniture.
 * Example: wooden shelf with books.(Books could be taken.)
 * */
using namespace std;

class FieldStuff {
protected:
    // fast search
    int id;
    string name;
    // exists/active
    bool isactive;
    vector<Item> inventory_;
public:
    FieldStuff() = default;
    ~FieldStuff() = default;

    virtual int GetInt(int what);

    virtual string GetString(int what);

    virtual bool GetBool(int what);

    virtual vector<Item> GetInventory();

    virtual void SetInt(int what, int value);

    virtual void SetString(int what, string &value);

    virtual void SetBool(int what, bool value);

    virtual void SetInventory(vector<Item> &items_);

    virtual void RemoveFromInventory(vector<Item> &items_);
};

class Furniture : public FieldStuff{
private:
    int hp;
    int type;  // High, medium or low
    int lock_id; // Each lock got its key only key with same id will fit
    int lock_hp;
    bool islocked;
public:
    Furniture();
    Furniture(int id_, string name_, bool isactive_, int hp_, int type_, int lock_id_, int lock_hp_, bool islocked_);
    ~Furniture();

    bool IsLockLocked(bool islocked_, int lock_hp_);

    int GetInt(int what) override;

    bool GetBool(int what) override;

    void SetInt(int what, int value) override;

    void SetBool(int what, bool value) override;

};


#endif //ANOTHER_DND_SIMULATOR_FIELDSTUFF_H
