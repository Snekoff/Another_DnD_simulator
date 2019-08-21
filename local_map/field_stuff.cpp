#include "field_stuff.h"

int FieldStuff::GetInt(int what) {
    if (what == 0) return id;
}

string FieldStuff::GetString(int what) {
    if (what == 0) return name;
}

bool FieldStuff::GetBool(int what) {
    if (what == 0) return isactive;
}

vector<Item> FieldStuff::GetInventory() {
    return inventory_;
}

void FieldStuff::SetInt(int what, int value) {
    if (what == 0) id = value;
}

void FieldStuff::SetString(int what, string &value) {
    if (what == 0) name = value;
}

void FieldStuff::SetBool(int what, bool value) {
    if (what == 0) isactive = value;
}

void FieldStuff::SetInventory(vector<Item> &items_) {
    inventory_ = items_;
}

void FieldStuff::RemoveFromInventory(vector<Item> &items_) {
    for (auto j:items_) {
        for (auto i = inventory_.begin(); i < inventory_.end(); i++) {
            if (i->get_name() == j.get_name() && i->What_class() == j.What_class()) {
                // if there are more than one item reduce its num
                if (i->get(2) > 1) i->set_count(i->get(2) - 1);
                else inventory_.erase(i);
                break;
            }
        }
    }
}

Furniture::Furniture(int id_, string name_, bool isactive_, int hp_, int type_, int lock_id_, int lock_hp_,
                     bool islocked_) {
    id = id_;
    name = name_;
    isactive = isactive_;
    hp = hp_;
    type = type_;
    lock_id = lock_id_;
    lock_hp = lock_hp_;
    islocked = islocked_;
    islocked = IsLockLocked(islocked, lock_hp);
}

bool Furniture::IsLockLocked(bool islocked_, int lock_hp_) {
    if(!islocked_) return false;
    if(lock_hp_ <= 0) return false;
    return true;
}

int Furniture::GetInt(int what) {
    if (what == 0) return id;
    if (what == 1) return hp;
    if (what == 2) return type;
    if (what == 3) return lock_id;
    if (what == 4) return lock_hp;
}

bool Furniture::GetBool(int what) {
    if (what == 0) return isactive;
    if (what == 1) return islocked;
}


void Furniture::SetInt(int what, int value) {
    if (what == 0) id = value;
    if (what == 1) hp = value;
    if (what == 2) type = value;
    if (what == 3) lock_id = value;
    if (what == 4) lock_hp = value;
}

void Furniture::SetBool(int what, bool value) {
    if (what == 0) isactive = value;
    if (what == 1) islocked = value;
}

