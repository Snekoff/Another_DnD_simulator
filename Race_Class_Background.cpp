
#include "interface_races_classes_background.h"
#include <iostream>
#include "Skills_and_Spells.cpp"
#include "UsefulFunctions.cpp"

class Race {
 private:
  int type;
 protected:
  int height, weight, age;
  int minHeight[39] = {6, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 3, 3, 3, 3, 5, 5, 5, 5, 5, 5, 3, 3, 3, 5, 5, 5, 6, 5, 5, 5, 5,
                       5, 5, 5, 5, 5, 5, 5};
  int maxHeight[39] = {6, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4, 4, 6, 6, 6, 6, 6, 6, 3, 3, 3, 6, 6, 6, 6, 6, 6, 6, 6,
                       6, 6, 6, 6, 6, 6, 6};
  int minWeight[39] = {10};
  int maxWeight[39] = {140};
  int minAge[39] = {3};
  int maxAge[39] = {120};
  int Str, Dex, Con, Int, Wis, Cha;
  Spell spell;
  std::string raceFeatures;
  // Abilities0-5,Movement,Size,Darkvision,skill like firebreath,fits,type of damage resistance,Languages//
 public:
  Race() {
    type = 0;
    height = 0;
    weight = 0;
    age = 0;
  }

  ~Race() {}

  virtual void set(int a) {
    type = a;
  }

  virtual void set(int a, int b, int c, int d) {}

  virtual int get() {}

  void raceFeature() {}
};

class SubRace : public Race {
 private:
  int subtype;
 public:
  void subRaceFeatures() {}
};

class Class {
 private:
  int type;
 protected:
  std::string features = "";
 public:
  Class() {}

  ~Class() {}

  virtual void set(int a) {}

  virtual void set(int a, int b, int c, int d) {}

  virtual int get() {}

  void ClassFeatures() {}
};

class SubClass : public Class {
 private:
  int subtype;
 public:
  void subClassFeatures() {}
};

/*printf("%s \n",
           "Your class allows you to Get a proficiency skills, your proficiency bonus will be added to them that will made you stronger or smarter, depends what you choose.");

 *
 * if(classType == "Barbarian"){health_dice = 12;
    printf("%s \n", "Choose two from Animal Handling, Athletic, Intimidation, Nature, Perception and Survival");
    }// save throws, skills,
    else if(classType == "Bard"){health_dice = 8;
        printf("%s \n", "Choose any three ");
    }
    else if(classType == "Cleric"){health_dice = 8;
        printf("%s \n", "Choose two from History, .s[6], Medicine, Persuasion and Religion");
    }
    else if(classType == "Druid"){health_dice = 8;
        printf("%s \n", "Choose two from Arcana, Animal Handling, .s[6], Medicine, Nature, Perception, Religion and Survival");
    }
    else if(classType == "Fighter"){health_dice = 10;
        printf("%s \n", "Choose two from Acrobatics, AnimalHandling, Athletics, History, .s[6], Intimidation, Perception and Survival");
    }
    else if(classType == "Monk"){health_dice = 8;
        printf("%s \n", "Choose two from Acrobatics, Athletics, History, .s[6], Religion, and Stealth");
    }
    else if(classType == "Paladin"){health_dice = 10;
        printf("%s \n", "Choose two from Athletics, .s[6], Intimidation, Medicine, Persuasion, and Religion");
    }
    else if(classType == "Ranger"){health_dice = 10;
        printf("%s \n", "Choose two from Animal Handling, Athletics, .s[6], Investigation, Nature, Perception, Stealth and Survival");
    }
    else if(classType == "Rouge"){health_dice = 8;
        printf("%s \n", "Choose four from Acrobatics, Athletics, Deception, .s[6], Intimidation, Investigation, Perception, Performance, Persuasion, Sleight of Hand and Stealth");
    }
    else if(classType == "Sorcerer"){health_dice = 6;
        printf("%s \n", "Choose two from Arcana, Deception, .s[6], Intimidation, Persuasion, and Religion");
    }
    else if(classType == "Warlock"){health_dice = 8;
        printf("%s \n", "Choose two from Arcana, Deception, History, Intimidation, Investigation, Nature, and Religion");
    }
    else if(classType == "Wizard"){health_dice = 6;
        printf("%s \n", "Choose two from Arcana, History, .s[6], Investigation, Medicine, and Religion");
    }*/


/* I need to do list of names, also in method Features i must make choice of abilities, if race allows
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
