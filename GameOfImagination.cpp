

#include "Character/character.h"
#include "GameOfImagination.h"

using namespace std;

Game::Game(int start, int journey) {
  auto Rand_gen = new Random_Generator_();
  /*auto Json1 = new WorkWithJson();
  //Json1->Write_(10);
  cout << "wow\n";*/
  printf("Start new game: 1\nLoad saved game: 2\n");
  int new_or_load = 0;
  new_or_load = IsNumber(new_or_load, 1, 2);
  if (new_or_load == 2) {
    Party_Load();
    // to be deleted
    if (!characters.empty()) {
      bool repeat = true;
      int player_to_be_checked = 0;
      while (repeat) {
        Existing_Types E;
        cout << "Who to check? //0 to exit// Size of the party: " << characters.size() << endl;
        player_to_be_checked = IsNumber(player_to_be_checked, 0, characters.size());
        printf("Now showing params: \n");
        for (int j = 1; j < 90; j++) {
          cout << j << " " << E.params[j - 1] << " : " << characters[player_to_be_checked - 1]->Get(j) << endl;
        }
        if (player_to_be_checked == 0) repeat = false;
      }
    }
  } else Character_create(Rand_gen);

  delete Rand_gen;
}

Game::~Game() {
  characters.clear();
};

void Game::Character_create(Random_Generator_ *Rand_gen) {
  Existing_Types E;
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
    cout << "Choose sex of your character. Female(1), Male(2), Futa(3), Creature(4)\n";
    sex_ = IsNumber(sex_, 1, 4);
    cout << "Choose background. Acolyte(1), Charlatan(2), Criminal(3), Entertainer(4), FolkHero(5), GuildArtisan(6), "
            "Hermit(7), Noble(8), Outlander(9), Sage(10), Sailor(11), Soldier(12), Urchin(13)\n";
    first_choosal = IsNumber(first_choosal, 1, 13);
    auto a = new Character(Rand_gen, first_choosal - 1, exp_, level_, abilities[0], abilities[1],
                           abilities[2], abilities[3], abilities[4], abilities[5], sex_ - 1);
    characters.push_back(a);
    delete a;
    //bool testing_method_Get = true;
    // int what = 1;
    //while (testing_method_Get) {
    //  cout << characters[characters.size() - 1]->Get(what) << endl;
    printf("Now showing params: \n");
    for (int j = 1; j < 90; j++) {
      cout << j << " " << E.params[j - 1] << " : " << characters[characters.size() - 1]->Get(j) << endl;
    }
  }
  cout << "Do you want to save your party ?\n Yes - 1 , No - 2\n";
  int save_or_not = 0;
  save_or_not = IsNumber(save_or_not, 1, 2);
  if (save_or_not == 1) Party_Save();
}

bool Game::is_Created() {
  return characters.empty();
}

bool Game::Party_Save() {
  nlohmann::json party;
  party["Size"] = characters.size();
  vector<vector<int>> params;
  params.resize(characters.size());
  for (int i = 0; i < characters.size(); i++) {
    for (int p = 0; p < 69; p++) {
      params[i].push_back(characters[i]->Get(p));
    }
    party["Character"][i] = params[i];
  }
  std::ofstream outp;
  outp.open("E:\\Den`s\\programming\\Git_c++\\Another_DnD_simulator\\MyJson.json", std::ofstream::out);
  if (!outp.is_open()) return false;
  outp << std::setw(4) << party << endl;
  outp.close();
  return true;
}

bool Game::Party_Load() {
  ifstream party_save_file;
  party_save_file.open("E:\\Den`s\\programming\\Git_c++\\Another_DnD_simulator\\MyJson.json");
  if (!party_save_file.is_open()) {
    cout << "Error in loading file\n";
    return false;
  }
  json party = json::parse(party_save_file);
  printf("Control reach method Party Load 0\n");
  int *p = new int[69];
  int Size = party["Size"];
  vector<vector<int>> l_params;
  l_params.resize((unsigned) Size);
  printf("Control reach method Party Load 1\n");
  for (int n = 0; n < Size; n++) {
    for (int i = 0; i < 69; i++) {
      p[i] = party["Character"][n][i];
    } // l_params[n] = party["Character"][n];
    auto a = new Character();
    printf("Control reach method Party Load 4\n");
    a->Load(p);
    printf("Control reach method Party Load 5\n");
    characters.push_back(a);
    delete a;
  }
  delete[] p;
  return true;
}
