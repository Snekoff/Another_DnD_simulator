#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Spell{
private:
    bool knowledge[50] = {false};
    int skillSlots[4]; // up to 10th level
    int maxskillSlots[4]; // 10 KI for monk
    int spellSlots[5];
    int maxspellSlots[5];
    int knownSpells;
    int knownkantrips;
public:
    Spell(){}
    ~Spell(){}
    bool doYouKnowIt(int a){
        if(knowledge[a]) return true;
        else return false;
    }
    int get(int a){
        if(a < 0){
            printf("%s \n", "Wrong parameter in class Spell method get, a < 0");
            while(a < 0 && a > 10){
                printf("%s \n", "Wrong parameter in class Spell method get");
                scanf("%d", a);
            }
        }
    }
};