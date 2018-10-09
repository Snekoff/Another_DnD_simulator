

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
        Character_Show_Parameters(player_to_be_checked - 1);
      }
    }
  } else Character_create(Rand_gen);
  //auto FieldOfHonor = new Battleground(X,Y,Z);
}

Game::~Game() {
  characters.clear();
  delete Rand_gen;
};

void Game::Character_create(Random_Generator_ *Rand_gen) {
  cout << "Hello, adventurer. We start with character creation, shouldn't we?\n";
  cout << "Lets start with a number of current players except master. Type it.\n";
  cout << "( You will be able to add or delete character during your game )\n";
  int number_of_characters = 0;
  number_of_characters = IsNumber(number_of_characters, 0, -1);
  characters.resize((unsigned) number_of_characters);
  for (int i = 0; i < number_of_characters; i++) {
    cout << "For player " << i + 1 << " type: experience, level\n";
    int exp_ = 0, level_ = 0, sex_ = 0;
    exp_ = IsNumber(exp_, kExperience_Min, kExperience_Max);
    level_ = IsNumber(level_, kLevel_Minimum, kLevels_Num);
    vector<int> abilities;
    abilities.resize(kAbilities_Num);
    abilities = Set_Character_Abilities(abilities);
    cout << "Choose sex of your character. Female(1), Male(2), Futanari(3), Creature(4)\n";
    sex_ = IsNumber(sex_, 1, kGenders_Num);
    cout << "Choose background. Acolyte(1), Charlatan(2), Criminal(3), Entertainer(4), FolkHero(5), GuildArtisan(6), "
            "Hermit(7), Noble(8), Outlander(9), Sage(10), Sailor(11), Soldier(12), Urchin(13)\n";
    int story_choosal = 0;
    story_choosal = IsNumber(story_choosal, 1, kStory_Num);
    int rand_seed_change = abilities[sex_] * sex_ + story_choosal;
    cout << abilities[0] << endl;
    characters[i] = new Character(Rand_gen, story_choosal - 1, exp_, level_, abilities[0], abilities[1],
                                  abilities[2], abilities[3], abilities[4], abilities[5], sex_ - 1, rand_seed_change);
    Character_Show_Parameters(i);
  }
  cout << "Do you want to save your party ?\n //Yes: 1//,// No: 2//\n";
  int save_or_not = 0;
  save_or_not = IsNumber(save_or_not, 1, 2);
  if (save_or_not == 1) Party_Save();
}

vector<int> Game::Set_Character_Abilities(vector<int> abilities) {
  cout << "If you are building new character, you can use random stats generation.\n";
  cout << "It means that your stats will be randomised from 10 to 16 each, two sets of values will be given to you, "
          "and you must take one of them. To do so you just need to //type 1// now, //type 2// to set it your way\n";
  int first_choosal = 0;
  first_choosal = IsNumber(first_choosal, 1, 2);
  if (first_choosal != 1) {
    cout << "Type six numbers, for each stats. Str, Dex, Con, Int, Wis, Cha. From 0 to 20\n";
    for (int j : {1, 2, 3, 4, 5, 6}) {
      abilities[j] = IsNumber(abilities[j], 0, kAbility_Maximum_Score);
    }
  }
  return abilities;
}

bool Game::is_Created() {
  return characters.empty();
}

void Game::Character_Show_Parameters(int who) {
  Existing_Types E;
  cout << "Now showing params: \n";
  for (int j = 0; j < kOutput_Num; j++) {
    cout << j << " " << E.params_i[j] << " : ";
    cout << characters[who]->Get(j) << endl;
  }
  for (int j = 0; j < kOutput_Num; j++) {
    cout << j << " " << E.params_b[j] << " : ";
    cout << characters[who]->Get_bool(j) << endl;
  }

}

bool Game::Party_Save() {
  nlohmann::json party;
  party["Size"] = characters.size();
  vector<vector<int>> params;
  vector<vector<bool>> bool_params;
  params.resize(characters.size());
  bool_params.resize(characters.size());
  //cout << "Control reach Party Save 2\n";
  for (int i = 0; i < characters.size(); i++) {
    vector<int> inventory = characters[i]->Get_inventory();
    for (int p = 0; p < kData_size; p++) {
      bool_params[i].push_back(characters[i]->Get_bool(p));
      params[i].push_back(characters[i]->Get(p));
    }
    party["Character"][i] = params[i];
    party["Character_bool"][i] = bool_params[i];
    party["InventorySize"][i] = characters[i]->Get(99);//inventory size
    party["Inventory"][i] = inventory;
  }
  std::ofstream outp;
  outp.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/MyParty.json", std::ofstream::out);
  if (!outp.is_open()) return false;
  outp << std::setw(4) << party << endl;
  outp.close();
  return true;
}

bool Game::Party_Load() {
  ifstream party_save_file;
  party_save_file.open("E:/Den`s/programming/Git_c++/Another_DnD_simulator/MyParty.json");
  if (!party_save_file.is_open()) {
    cout << "Error in loading file\n";
    return false;
  }
  json party = json::parse(party_save_file);
  cout << "Control reach method Party Load 0\n";
  int *p = new int[kData_size];
  bool *bool_p = new bool[kData_size];
  int Size = party["Size"].get<int>();
  characters.resize((unsigned) Size);
  cout << "Control reach method Party Load 1\n";
  for (int i = 0; i < Size; i++) {
    vector<int> inventory_;
    unsigned inventory_Size = party["InventorySize"][i].get<int>();
    for (int j = 0; j < kData_size; j++) {
      p[j] = party["Character"][i][j].get<int>();
      bool_p[j - kParameter_b_shift] = party["Character_bool"][i][j].get<bool>();//Exists
    }
    cout << "Control reach method Party Load 3\n";
    inventory_.resize(inventory_Size);
    //cout << inventory_Size << endl;
    for (int j = 0; j < inventory_Size; j++) { //FIXME: party["Inventory"][i][j] not exists
      cout << "Control reach method Party Load _4\n";
      cout << "inventory[" << i << "][" << j << "] = " << party["Inventory"][i][j].get<int>() << endl;
      inventory_[j] = party["Inventory"][i][j].get<int>();
    }
    cout << "Control reach method Party Load 4_1\n";
    characters[i] = new Character();
    characters[i]->Load(p, bool_p, inventory_);
  }
  delete[] p;
  delete[] bool_p;
  return true;
}
