//
// MIT License
// Copyright (c) 2019 Snekoff. All rights reserved.
//
#pragma once
#include "../character/common_functions.h"
#include "../items/item.h"
#include "../items/items_factory.h"
#include "../monsters/creature.h"

#ifndef ANOTHER_DND_SIMULATOR_FIELDSTUFF_H
#define ANOTHER_DND_SIMULATOR_FIELDSTUFF_H

/*
 * Here are classes that are stored in each field/square.
 * Like what is in that position torch, trap, furniture.
 * Example: wooden shelf with books.(Books could be taken.)
 * */
using namespace std;

class Furniture {
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

    int GetInt(int what);

    bool GetBool(int what);

    void SetInt(int what, int value);

    void SetBool(int what, bool value);

};

class FieldStuff {
protected:
    // fast search
    int id;
    string name;
    // exists/active
    bool isactive;
    int local_coordinates[3];  // to avoid huge numbers
    int global_coordinates[3];
    // Inventory
    // 1. Unhold (free to spot and take)
    // 2. Hidden (DC against ability check)
    // 3. Blocked by other means (magicaly)
    // 4. Other planes
    vector<vector<Item>> inventory_;
    vector<Creature> &creatures;
    // furniture got fields:
        // AC, HP, ishold
        // vector<vector<Item>> inventory_inside;
        // vector<Creature> &creatures;
        // Spell spells
        // string text
        // vector<pair<int, int> lockid_and_dc
        // ? trigger
    vector<Furniture> furniture;
    // ? Interactables
        // Other
        // Hidden
        // Locked
    // ? what_is_made_of
    // All fields that share side and got type "air"
    // are as well hard terrain
    // for creatures with flying speed = 0
    bool is_hard_terrain;
    // ? herbs
    // ? sources_of_light
public:
    FieldStuff() = default;
    ~FieldStuff() = default;

    virtual int GetInt(int what);

    virtual string GetString(int what);

    virtual bool GetBool(int what);

    virtual vector<vector<Item>> GetInventory();

    virtual void SetInt(int what, int value);

    virtual void SetString(int what, string &value);

    virtual void SetBool(int what, bool value);

    virtual void SetInventory(vector<vector<Item>> &items_);

    virtual void RemoveFromInventory(vector<vector<Item>> &items_);
};


#endif //ANOTHER_DND_SIMULATOR_FIELDSTUFF_H
