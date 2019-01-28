#include "MazeGenerator.h"

MazeGenerator::MazeGenerator(Random_Generator_ *Rand_gen, vector<vector<int>> square_){
// smth here
}

vector<vector<int>> MazeGenerator::RoomsPlacement(vector<pair<int, int>> roomsRegions, vector<pair<int, int>> roomsEntrances, vector<vector<int>> square_){
  for(int i = 0; i < roomsRegions.size(); i += 2){
    pair<int, int> begining, ending;
    begining = roomsRegions[i];
    ending = roomsRegions[i+1];
    int begSt = min(begining.first, begining.second), begEn = max(begining.first, begining.second);
    int endSt = min(ending.first, ending.second), endEn = max(ending.first, ending.second);
    for(int j = begSt; j <= begEn; j++){
      for(int p = endSt; j <= endEn; j++){
        square_[j][p] = 1;
      }
    }
  }
  for(int i = 0; i < roomsEntrances.size(); i++){
    if(square_[roomsEntrances[i].first][roomsEntrances[i].second] != 1){
      square_[roomsEntrances[i].first][roomsEntrances[i].second] = 3;
    }
    else std::cout << "Entrance #" << i+1 << " is placed not outside of the room\n";
  }
}