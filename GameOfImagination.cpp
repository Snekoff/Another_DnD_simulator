

#include "Character/character.h"
#include "GameOfImagination.h"
//#include "WorkWithJson.h"

using namespace std;

Game::Game(int start, int journey) {
  auto Rand_gen = new Random_Generator_();
  /*auto Json1 = new WorkWithJson();
  //Json1->Write_(10);
  cout << "wow\n";*/
  Character_create(Rand_gen);

  delete Rand_gen;
}

Game::~Game() {
  characters.clear();
};

void Game::Character_create(Random_Generator_ * Rand_gen) {
  cout << "Hello, adventurer. We start with character creation, shouldn't we?\n";
  cout << "Lets start with a number of current players except master. Type it.\n";
  cout << "( You will be able to add or delete character during your game )\n";
  int number_of_characters = 0;
  //cin >> number_of_characters;
  number_of_characters = IsNumber(number_of_characters, 0, -1);
  for (int i = 0; i < number_of_characters; i++) {
    printf("%s %d %s", "For player", i + 1, "Type: experience, level\n");
    int exp_ = 0, level_ = 0, sex_ = 0;
    //cin >> exp_ >> level_;
    exp_ = IsNumber(exp_, 0, 355000);
    level_ = IsNumber(level_, 0, 20);
    cout << "If you are building new character, you can use random stats generation.\n";
    cout << "It means that your stats will be randomised from 10 to 16 each, two sets of values will be given to you, "
            "and you must take one of them. To do so you just need to type 0 now, type any number to set it your way\n";
    int first_choosal = 0;
    //cin >> first_choosal;
    first_choosal = IsNumber(first_choosal, 0, 100);
    int abilities[6] = {0};
    if (first_choosal != 0) {
      printf("Type six numbers, for each stats. Str, Dex, Con, Int, Wis, Cha. From 0 to 20\n");
      for (int j = 0; j < 6; j++) {
        //cin >> abilities[j];
        abilities[j] = IsNumber(abilities[j], 0, 20);
      }
    }
    cout << "Choose sex of your character.Female(1), Male(2), Futa(3), Creature(4)\n";
    //cin >> sex_;
    sex_ = IsNumber(sex_, 1, 4);
    cout << "Choose background. Acolyte(1), Charlatan(2), Criminal(3), Entertainer(4), FolkHero(5), GuildArtisan(6), "
            "Hermit(7), Noble(8), Outlander(9), Sage(10), Sailor(11), Soldier(12), Urchin(13)\n";
    //cin >> first_choosal;
    first_choosal = IsNumber(first_choosal, 1, 13);
    string stories[13] = {"Acolyte", "Charlatan", "Criminal", "Entertainer", "FolkHero", "GuildArtisan",
                          "Hermit", "Noble", "Outlander", "Sage", "Sailor", "Soldier", "Urchin"};
    first_choosal = IsNumber(first_choosal, 1, 13);

    auto a = new Character(Rand_gen,stories[first_choosal - 1], exp_, level_, abilities[0], abilities[1],
                           abilities[2], abilities[3], abilities[4], abilities[5], sex_ - 1);
    characters.push_back(a);
    delete a;
    bool testing_method_Get = true;
    int what = 1;
    while (testing_method_Get) {
      cout << characters[characters.size() - 1]->Get(what) << endl;
      printf("type what to test or 0 to stop\n");
      //cin >> what;
      what = IsNumber(what, 0, 90);
      if (what == 0) { testing_method_Get = false; }

    }
  }
}

bool Game::is_Created() {
  return characters.empty() ;
}
