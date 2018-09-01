#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "UsefulFunctions.cpp"

class Spell {
 private:
  bool knowledge[50] = {false};
  int skillSlots[4] = {-1}; // up to 10th level
  int maxskillSlots[4] = {-1}; // rages
  int spellSlots[5] = {-1};
  int maxspellSlots[5] = {-1};// 10 KI for monk
  int knownSpells, maxknownSpells;
  int knownkantrips, maxknownkantrips;

 public:
  Spell() {
    knownSpells = 0;
    maxknownSpells = 0;
    knownkantrips = 0;
    maxknownkantrips = 0;
  }

  ~Spell() {}

  bool doYouKnowIt(int a) {
    if (a < 0 || a > 50) return -1;
    if (knowledge[a]) return true;
    else return false;
  }

  int get(int a, int b) {
    if (a < 0 || a > 8 || b > 3 || b < 0) {
      printf("%s \n", "Wrong parameter in class Spell method get");
      while (a < 0 || a > 8 || b > 3 || b < 0) {
        printf("%s \n", "Wrong parameter in class Spell method get");
        std::cin >> a;
        std::cin >> b;
        get(a, b);
      }
    } else if (a < 4) {
      if (b == 0) {
        return maxspellSlots[a];
      } else if (b == 1) {
        return maxskillSlots[a];
      } else if (b == 2) {
        return spellSlots[a];
      } else if (b == 3) {
        return skillSlots[a];
      }
    } else if (a == 4) {
      if (b == 0) {
        return maxspellSlots[a];
      } else if (b == 2) {
        return spellSlots[a];
      }

    } else if (a == 5) { return maxknownkantrips; }
    else if (a == 6) { return maxknownSpells; }
    else if (a == 7) { return knownkantrips; }
    else if (a == 8) { return knownSpells; }
    return -1;
  }

  void set(int a, int b, int value) {
    if (a < 0 || a > 8 || b > 3 || b < 0) {
      printf("%s \n", "Wrong parameter in class Spell method set(int,int,int)");
      while (a < 0 || a > 8 || b > 3 || b < 0) {
        printf("%s \n", "Wrong parameter in class Spell method set");
        std::cin >> a;
        std::cin >> b;
        set(a, b, value);
      }
    } else if (a < 4) {
      if (b == 0) {
        maxspellSlots[a] += value;
      } else if (b == 1) {
        maxskillSlots[a] += value;
      } else if (b == 2) {
        spellSlots[a] += value;
      } else if (b == 3) {
        skillSlots[a] += value;
      }
    } else if (a == 4) {
      if (b == 0) {
        maxspellSlots[a] += value;
      } else if (b == 2) {
        spellSlots[a] += value;
      }
    } else if (a == 5) { maxknownkantrips += value; }
    else if (a == 6) { maxknownSpells += value; }
    else if (a == 7) { knownkantrips += value; }
    else if (a == 8) { knownSpells += value; }
  }

  void set(int a) {
    if (a < 0 || a > 50) {
      printf("%s \n", "Wrong parameter in class Spell method set(int)");
      while (a < 0 || a > 50) {
        printf("%s \n", "Wrong parameter in class Spell method set");
        std::cin >> a;
        set(a);
      }
    } else if (!knowledge[a]) { knowledge[a] = true; }
    else printf("%s \n", "You already know that spell.");
  }

  void cast(int a) {
    while (a < 0 || a > 50) {
      printf("%s \n", "Incorrect parameter in class Spell method void cast");
      std::cin >> a;
    }
    //idk how to simplify all spells features
  }
};