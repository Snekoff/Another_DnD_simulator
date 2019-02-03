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
// 6
// 7
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
    for (int j = begSt; j <= begEn; j++) {
      for (int p = endSt; j <= endEn; j++) {
        square_[j][p] = 1;
      }
    }
  }
  for (int i = 0; i < roomsEntrances.size(); i++) {
    if (!IsNegative(roomsEntrances[i].first, roomsEntrances[i].second, i + 1)
        && square_[roomsEntrances[i].first][roomsEntrances[i].second] == 2) {
      square_[roomsEntrances[i].first][roomsEntrances[i].second] = 3;
    } else std::cout << "Entrance #" << i + 1 << " is placed not on room wall\n";
  }
}

bool MazeGenerator::CouldMakeCorridor(int x, int y, vector<vector<int>> square_) {

}

int MazeGenerator::Direction(Random_Generator_ *Rand_gen) {

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

}

pair<int, int> MazeGenerator::Move(Random_Generator_ *Rand_gen, int x, int y, vector<vector<int>> square_) {
  pair<int, int> pos = make_pair(x, y);
  if (IsNegative(x, y, -1)) return pos;
  int direction = Direction(Rand_gen);
  int minPaceLength = 2;
  char dirDescription[4] = {'u', 'r', 'd', 'l'};
  bool deadend = false;
  int dirMod[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
  direction = RightDirection(Rand_gen, x, y, direction, square_);
  if (direction == -1) return pos;
  int x_mod = x + minPaceLength * dirMod[direction][0];
  int y_mod = y + minPaceLength * dirMod[direction][1];
  if (square_[x_mod][y_mod] == 0) {
    int paceLength = PaceLength(difficulty, Rand_gen);
    x_mod = x + paceLength * dirMod[direction][0];
    y_mod = y + paceLength * dirMod[direction][1];
    while (!(square_[x_mod][y_mod] == 0 && CouldMakeCorridor(x_mod, y_mod, square_))) {
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