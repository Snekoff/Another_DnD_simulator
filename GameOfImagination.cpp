

#include "Character/character.h"
#include "GameOfImagination.h"

using namespace std;

Game::Game() {
  Rand_gen = new Random_Generator_();
};

Game::Game(int start, int journey) {
  Rand_gen = new Random_Generator_();
  cout << "Start new game: 1\nLoad saved game: 2\n";
  int new_or_load = 0;
  new_or_load = IsNumber(new_or_load, 1, 2);
  if (new_or_load == 2) {
    Party_Load();
    // to be deleted
    if (!characters.empty()) {
      int player_to_be_checked = 0;
      while (true) {
        Existing_Types E;
        cout << "Who to check? //0 to exit// Size of the party: " << characters.size() << endl;
        player_to_be_checked = IsNumber<int>(player_to_be_checked, 0, characters.size());
        if (player_to_be_checked == 0) {
          break;
        }
        cout << "Now showing params: \n";
        for (int j = 1; j < kOutput; j++) {
          if(j > kCharacter_Get_Bool_shift && j < kData_size){
            cout << j << " " << E.params[j - 1] << " : " << characters[player_to_be_checked - 1]->Get_bool(j) << endl;
          }
          else {
            cout << j << " " << E.params[j - 1] << " : " << characters[player_to_be_checked - 1]->Get(j) << endl;
          }
        }
      }
    }
  } else Character_create(Rand_gen);
}

Game::~Game() {
  characters.clear();
  delete Rand_gen;
};

void Game::Character_create(Random_Generator_ *Rand_gen) {
  Existing_Types E;
  cout << "Hello, adventurer. We start with character creation, shouldn't we?\n";
  cout << "Lets start with a number of current players except master. Type it.\n";
  cout << "( You will be able to add or delete character during your game )\n";
  int number_of_characters = 0;
  number_of_characters = IsNumber(number_of_characters, 0, -1);
  characters.resize((unsigned)number_of_characters);
  for (int i = 0; i < number_of_characters; i++) {
    cout << "For player" << i + 1 << "Type: experience, level\n";
    int exp_ = 0, level_ = 0, sex_ = 0;
    exp_ = IsNumber(exp_, kExperience_Min, kExperience_Max);
    level_ = IsNumber(level_, kLevel_Minimum, kLevels_Num);
    cout << "If you are building new character, you can use random stats generation.\n";
    cout << "It means that your stats will be randomised from 10 to 16 each, two sets of values will be given to you, "
            "and you must take one of them. To do so you just need to type 0 now, type any number to set it your way\n";
    int first_choosal = 0;
    first_choosal = IsNumber(first_choosal, 0, INT_MAX);
    int rand_seed_change = 0;
    int abilities[kAbilities_Num] = {0};
    if (first_choosal != 0) {
      cout << "Type six numbers, for each stats. Str, Dex, Con, Int, Wis, Cha. From 0 to 20\n";
      for (int j : {1,2,3,4,5,6}) {
        abilities[j] = IsNumber(abilities[j], 0, kAbility_Maximum_Score);
      }
    }
    cout << "Choose sex of your character. Female(1), Male(2), Futanari(3), Creature(4)\n";
    sex_ = IsNumber(sex_, 1, kGenders_Num);
    cout << "Choose background. Acolyte(1), Charlatan(2), Criminal(3), Entertainer(4), FolkHero(5), GuildArtisan(6), "
            "Hermit(7), Noble(8), Outlander(9), Sage(10), Sailor(11), Soldier(12), Urchin(13)\n";
    first_choosal = IsNumber(first_choosal, 1, 13);
    rand_seed_change = abilities[2]*sex_ + first_choosal;
    characters[i] = new Character(Rand_gen, first_choosal - 1, exp_, level_, abilities[0], abilities[1],
                                  abilities[2], abilities[3], abilities[4], abilities[5], sex_ - 1, rand_seed_change);
    cout << "Now showing params: \n";
    for (int j = 1; j < kOutput; j++) {
      if(j == kCharacter_get_fake_parameter) continue;
      cout << j << " " << E.params[j - 1] << " : " ;
      if(j > kCharacter_Get_Bool_shift && j < kData_size) cout << characters[i]->Get_bool(j) << endl;
      else cout << characters[i]->Get(j) << endl;
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
  cout << "Control reach Party Save 1\n";
  nlohmann::json party;
  party["Size"] = characters.size();
  vector<vector<int>> params;
  vector<vector<bool>> bool_params;
  params.resize(characters.size());
  bool_params.resize(characters.size());
  cout << "Control reach Party Save 2\n";
  for (int i = 0; i < characters.size(); i++) {
    for (int p = 1; p < kData_size; p++) {
      if (p > kCharacter_Get_Bool_shift && p < kData_size) bool_params[i].push_back(characters[i]->Get_bool(p));
      else params[i].push_back(characters[i]->Get(p));
    }
    cout << "Control reach Party Save 3\n";
    party["Character"][i] = params[i];
    cout << "Control reach Party Save 4\n";
    party["Character_bool"][i] = bool_params[i];
    cout << "Control reach Party Save 5\n";
    party["InventorySize"][i] = characters[i]->Get(99);
    cout << "Control reach Party Save 6\n";
    vector<int> inventory;
    inventory = characters[i]->Get_inventory();
    party["Inventory"][i] = inventory;// test
    cout << "Control reach Party Save 7\n";
  }
  cout << "Control reach Party Save 8\n";
  std::ofstream outp;
  outp.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/MyJson.json", std::ofstream::out);
  if (!outp.is_open()) return false;
  outp << std::setw(4) << party << endl;
  outp.close();
  return true;
}

bool Game::Party_Load() {
  ifstream party_save_file;
  party_save_file.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/MyJson.json");
  if (!party_save_file.is_open()) {
    cout << "Error in loading file\n";
    return false;
  }
  json party = json::parse(party_save_file);
  cout << "Control reach method Party Load 0\n";
  int *p = new int[kData_size];
  bool *bool_p = new bool[kData_size];
  int Size = party["Size"];
  vector<int> inventory_;
  cout << "Control reach method Party Load 1\n";
  characters.resize((unsigned)Size);//
  for (int n = 0; n < Size; n++) {
    unsigned inventory_Size = party["InventorySize"][n];
    for (int i = 1; i < kData_size; i++) {
      if(i == kCharacter_get_fake_parameter) continue;
      cout << "i = " << i << endl;
      if(i < kParameter_b_shift) p[i] = party["Character"][n][i-1];
      else bool_p[i-kParameter_b_shift] = party["Character_bool"][n][i-kParameter_b_shift];//
    }
    cout << "Control reach method Party Load 2\n";
    inventory_.resize(inventory_Size);
    for(int i = 0;i < inventory_Size; i++){
      inventory_[i] = party["Inventory"][n][i];
    }
    characters[n] = new Character();
    cout << "Control reach method Party Load 4\n";
    characters[n]->Load(p,bool_p,inventory_);
    cout << "Control reach method Party Load 5\n";
  }
  delete[] p;
  delete[] bool_p;
  return true;
}
