#include <vector>
#include "character.h"

vector<Character*> characters;

void Character_create(){
  cout << "Hello, adventurer. We start with character creation, scholdn`t we?\n";
  cout << "Lets start with a number of current players except master. Type it.\n";
  cout << "( You will be able to add or delete character during your game )\n";
  int number_of_characters = 0;
  cin >> number_of_characters;
  number_of_characters = Correctness_of_input(number_of_characters,0,-1);
  for(int i = 0; i < number_of_characters; i++){
    printf("%s %d %s","For player", i, "Type: experience, level\n");
    int exp_,level_,sex_;
    cin >> exp_ >> level_;
    exp_ = Correctness_of_input(exp_,0,355000);
    level_ = Correctness_of_input(level_,0,20);
    cout << "If you are building new character, you can use random stats generation.\n";
    cout << "It means that your stats will be randomed from 10 to 16 each, two sets of values will be given to you, "
            "and you must take one of them. To do so you just need to type 0 now, type any number to set it your way\n";
    int first_choosal;
    cin >> first_choosal;
    int abilities[6] = {0};
    if(first_choosal != 0){
      printf("Type six numbers, for each stats. Str, Dex, Con, Int, Wis, Cha. From 0 to 38\n");
      for(int j = 0;j < 6;j++){
        cin >> abilities[j];
        abilities[j] = Correctness_of_input(abilities[j],0,38);
      }
    }
    cout << "Choose sex of your character.Female(1), Male(2), Futa(3), Creature(4)\n";
    cin >> sex_;
    sex_ = Correctness_of_input(sex_,1,4);
    cout << "Choose background. Acolyte(1), Charlatan(2), Criminal(3), Entertainer(4), FolkHero(5), GuildArtisan(6), "
            "Hermit(7), Noble(8), Outlander(9), Sage(10), Sailor(11), Soldier(12), Urchin(13)\n";
    cin >> first_choosal;
    string stories[13] = {"Acolyte", "Charlatan", "Criminal", "Entertainer", "FolkHero", "GuildArtisan",
                          "Hermit", "Noble", "Outlander", "Sage", "Sailor", "Soldier", "Urchin"};
    first_choosal = Correctness_of_input(first_choosal,1,13);
    characters.push_back(new Character(stories[first_choosal - 1], exp_, level_, abilities[0], abilities[1],
                            abilities[2], abilities[3], abilities[4], abilities[5], sex_ - 1));
    bool testing_method_Get = true;
    int what = 1;
    while(testing_method_Get){
      characters[characters.size() - 1]->Get(what);
      printf("Continue ? Yes(1), No(2)\n");
      cin >> what;
      if(what != 1){ testing_method_Get = false; }
      printf("type what to test.\n");
      cin >> what;
      what = Correctness_of_input(what,0,90);
    }
  }
}
