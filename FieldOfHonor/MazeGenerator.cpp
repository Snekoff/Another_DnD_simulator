#include "MazeGenerator.h"
using namespace std;

MazeGenerator::MazeGenerator(Random_Generator_ *Rand_gen, vector<vector<int>> square_) {
// smth here
  deadend.resize(square_.size());
  for (int i = 0; i < deadend.size(); i++) {
    deadend[i].resize(square_[i].size());
  }
}

MazeGenerator::~MazeGenerator() {
  for (int i = 0; i < deadend.size(); i++) {
    deadend[i].clear();
  }
  deadend.clear();
  for (int i = 0; i < entrances.size(); i++) {
    entrances[i].clear();
  }
  entrances.clear();
}

bool MazeGenerator::IsNegative(int x, int y, int index) {
  if (x < 0 || y < 0) {
    cout << "Negative" << index << " coordinates\n";
    return true;
  }
  return false;
}

// id descriptions:
// 0 - wall
// 1 - corridor/empty
// 2 - room wall
// 3 - Exit/Entrance
// 4 - Nonbreakable wall
// 5 - Reached Entrance
vector<vector<int>> MazeGenerator::RoomsPlacement(vector<pair<int, int>> roomsRegions,
                                                  vector<pair<int, int>> roomsEntrances,
                                                  vector<vector<int>> square_) {
  for (int i = 0; i < roomsRegions.size(); i += 2) {
    pair<int, int> begin, ending;
    begin = roomsRegions[i];
    ending = roomsRegions[i + 1];
    if (IsNegative(begin.first, begin.second, i / 2 + 1) || IsNegative(ending.first, ending.second, i / 2 + 1)) {
      continue;
    }
    int begSt = min(begin.first, begin.second), begEn = max(begin.first, begin.second);
    int endSt = min(ending.first, ending.second), endEn = max(ending.first, ending.second);
    /*bool upper_room_wall_reached_end_of_the_region, right_room_wall_reached_end_of_the_region;
    bool bottom_room_wall_reached_end_of_the_region, left_room_wall_reached_end_of_the_region;*/
    // square_ here is an adress
    /// TEST
    RoomsPlacement_BuidingWalls(begin, ending, square_);
    RoomsPlacement_MakingRoomInside();
    /// ???
    /*for (int j = begSt; j <= begEn; j++) {
      for (int p = endSt; j <= endEn; j++) {
        square_[j][p] = 1;
      }
    }*/
    /// ???
  }
  for (int i = 0; i < roomsEntrances.size(); i++) {
    if (!IsNegative(roomsEntrances[i].first, roomsEntrances[i].second, i + 1)
        && square_[roomsEntrances[i].first][roomsEntrances[i].second] == 2) {
      square_[roomsEntrances[i].first][roomsEntrances[i].second] = 3;
    } else std::cout << "Entrance #" << i + 1 << " is placed not on room wall\n";
  }
}

vector<pair<int, int>> MazeGenerator::RoomsPlacement_BuidingWalls(pair<int, int> start_of_the_region,
                                                               pair<int, int> end_of_the_region,
                                                               vector<vector<int>> &square_
                                                               ) {
  vector<pair<int, int>> output;
  pair<int, int> st_new_region, end_new_region;
  pair<int, int> st_new_room_region = start_of_the_region, end_new_room_region = end_of_the_region;
  if(start_of_the_region.first >= end_of_the_region.first){
    if(start_of_the_region.second >= end_of_the_region.second){
      if(start_of_the_region.second > 0 && start_of_the_region.first < square_.size()){
        st_new_region.first = start_of_the_region.first + 1;
        st_new_region.second = start_of_the_region.second + 1;
      } else if(start_of_the_region.second > 0){
        st_new_region.first = start_of_the_region.first;
        st_new_region.second = start_of_the_region.second + 1;
        st_new_region.first--;
      }
    }
  }
  //....
  output.push_back(st_new_room_region);
  output.push_back(end_new_room_region);
  return output;
}

vector<vector<int>> MazeGenerator::RoomsPlacement_MakingRoomInside(pair<int, int> start_of_the_region,
                                                                   pair<int, int> end_of_the_region,
                                                                   vector<vector<int>> square_,
                                                                   bool up,
                                                                   bool right,
                                                                   bool bottom,
                                                                   bool left) {

}

bool MazeGenerator::CouldMakeCorridor(int from_x, int from_y, int to_x, int to_y, vector<vector<int>> square_) {
  if(to_x < 1 || to_x > square_.size() - 2) return false;
  if(to_y < 1 || to_y > square_[to_x].size() - 2)  return false;

  // Check whole way whether it passable
  int dif_x = abs(from_x - to_x), dif_y = abs(from_y - to_y);
  for(int i = 0; i < max(dif_x, dif_y); i++){
    if(dif_x > dif_y){
      int one_square = square_[from_x + (i+1) * dif_x/(to_x - from_x)][to_y];
      if(one_square != 0 && one_square != 3) return false;
    } else {
      int one_square = square_[to_x][from_y + (i+1) * dif_y/(to_y - from_y)];
      if(one_square != 0 && one_square != 3) return false;
    }
  }
  // Check surrounding
  // There have to be only walls or Entrances
  //(No corridors/Reached entrances)
  // up, up-right, r, down-right, d, d-left, l, up-left
  int dirMod[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
  int x_t = from_x, y_t = from_y;
  for(int j = 0; j < max(dif_x, dif_y); j++){
    for(int i = 0; i < 8; i++){
      int one_square = square_[x_t + dirMod[i][0]][y_t + dirMod[i][1]];
      if(one_square == 1 || one_square == 5) return false;
    }
    if(x_t != to_x) x_t += (from_x - to_x)/dif_x;
    if(y_t != to_y) y_t += (from_y - to_y)/dif_y;
  }
  return true;
}

int MazeGenerator::Direction(Random_Generator_ *Rand_gen) {
  return Rand_gen->Rand(0,3);
}

bool MazeGenerator::IsRightDirection(int x, int y, int direction_, vector<vector<int>> square_) {
  if (IsNegative(x, y, -1)) return false;
  if (y > square_[x].size() - 1 || x > square_.size() - 1) return false;
  if (x < 2 && direction_ == 0) return false;
  if (y < 2 && direction_ == 3) return false;
  if (x > square_.size() - 3 && direction_ == 2) return false;
  if (y > square_[x].size() - 3 && direction_ == 1) return false;
  return true;
}

int MazeGenerator::RightDirection(Random_Generator_ *Rand_gen, int x, int y, int direction,
                                  vector<vector<int>> square_) {
  bool canMove[4] = {true, true, true, true};
  bool deadend = false;
  int dir = -1;// means deadend reached
  while (!IsRightDirection(x, y, direction, square_)) {
    canMove[direction] = false;
    for (int j = 0; j < 4; j++) {
      if (canMove[j]) break;
      else if (j == 3) deadend = true;
    }
    if (!deadend) direction = Direction(Rand_gen);
    else return dir;
  }
  dir = direction;
  return dir;
}

int MazeGenerator::PaceLength(int difficulty_, Random_Generator_ *Rand_gen) {
  if (difficulty_ > 10) difficulty_ = 10;
  if (difficulty_ < 0) difficulty_ = 0;
  int maxPace = 12, minPace = 2;
  int pace = Rand_gen->Rand(minPace, maxPace - difficulty_);
  return pace;
}

pair<int, int> MazeGenerator::Move(Random_Generator_ *Rand_gen, int x, int y, vector<vector<int>> square_) {
  pair<int, int> pos = make_pair(x, y);
  if (IsNegative(x, y, -1)) return pos;
  int direction = Direction(Rand_gen);
  int minPaceLength = 2;
  char dirDescription[4] = {'u', 'r', 'd', 'l'};
  int dirMod[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
  direction = RightDirection(Rand_gen, x, y, direction, square_);
  if (direction == -1) return pos;
  int x_mod = x + minPaceLength * dirMod[direction][0];
  int y_mod = y + minPaceLength * dirMod[direction][1];
  if (square_[x_mod][y_mod] == 0) {
    int paceLength = PaceLength(difficulty, Rand_gen);
    x_mod = x + paceLength * dirMod[direction][0];
    y_mod = y + paceLength * dirMod[direction][1];
    while (!(square_[x_mod][y_mod] == 0 && CouldMakeCorridor(x, y, x_mod, y_mod, square_))) {
      cout << "New paceLength = " << paceLength - 1 << "\n";
      paceLength--;
      x_mod = x + paceLength * dirMod[direction][0];
      y_mod = y + paceLength * dirMod[direction][1];
    }
    pos = make_pair(x_mod, y_mod);
    return pos;
  }
  return pos;
}