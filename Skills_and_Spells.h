#pragma once

#ifndef ANOTHER_DND_SIMULATOR_SKILLS_AND_SPELLS_H
#define ANOTHER_DND_SIMULATOR_SKILLS_AND_SPELLS_H

#endif //ANOTHER_DND_SIMULATOR_SKILLS_AND_SPELLS_H

class Spell {
 private:
  bool knowledge[50] ;
  int skillSlots[4] ; // up to 10th level
  int maxskillSlots[4] ; // rages
  int spellSlots[5] ;
  int maxspellSlots[5] ;// 10 KI for monk
  int knownSpells, maxknownSpells;
  int knownkantrips, maxknownkantrips;

 public:
  Spell() {}

  ~Spell() {}

  bool doYouKnowIt(int a);

  int get(int a, int b);

  void set(int a, int b, int value);

  void set(int a);

  void cast(int a);
};