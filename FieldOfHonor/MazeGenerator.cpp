#include "MazeGenerator.h"

static const double Kpercentage_of_filled_space_in_the_end = 1.1;
using namespace std;

MazeGenerator::MazeGenerator(Random_Generator_ *Rand_gen, vector<vector<int>> square_) {
    num_of_deadends = 0;
    num_of_free_fields = 0;
    difficulty = kDifficulty_Min;
    roomProbability = kRoomProbabilityMax;
    for (int j = 0; j < square_[0].size(); ++j) {
        for (int i = 0; i < square_.size(); ++i) {
            if (square_[i][j] == 1) num_of_free_fields++;
        }
        cout << "\n";
    }
    deadend.resize(square_.size());
    for (int i = 0; i < deadend.size(); i++) {
        deadend[i].resize(square_[i].size());
    }
    entrances.resize(square_.size());
    for (int i = 0; i < entrances.size(); i++) {
        entrances[i].resize(square_[i].size(), -1);
    }
    entrance_info.push_back(ZeroIdEntranceInfo());
    square = square_;
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
    for (int i = 0; i < square.size(); i++) {
        square[i].clear();
    }
    square.clear();
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
vector<vector<int>> MazeGenerator::RoomsPlacement(vector<vector<int>> &square_) {
    pair<pair<int, int>, pair<int, int>> region;
    region = RegionSelect(square_);
    region = RoomsPlacement_BuildingWalls(region.first, region.second, square_);
    square_ = RoomsPlacement_MakingRoomInside(region.first, region.second, square_);
    return square_;
}

pair<pair<int, int>, pair<int, int>> MazeGenerator::RoomsPlacement_BuildingWalls(pair<int, int> start_of_the_region,
                                                                                 pair<int, int> end_of_the_region,
                                                                                 vector<vector<int>> &square_
) {
    pair<pair<int, int>, pair<int, int>> output;
    pair<int, int> st_new_region, end_new_region;
    pair<int, int> st_new_room_region = start_of_the_region, end_new_room_region = end_of_the_region;
    //User choose size and placement, but if it is too close to the edge of the world
    //walls will be automatically built to prevent reach nonexisting array member
    // if it is possible region expands by 1 in all directions
    // and build there walls
    output = RoomsPlacement_CheckEdgeReach(start_of_the_region, end_of_the_region, square_[0].size(), square_.size());
    for (int i = min(output.first.first, output.second.first);
         i < max(output.first.first, output.second.first); i++) {
        for (int j = min(output.first.second, output.second.second);
             j < max(output.first.second, output.second.second); j++) {
            if (square_[i][j] > 0) continue;
            square_[i][j] = 2;
        }
    }
    return output;
}

pair<pair<int, int>, pair<int, int>> MazeGenerator::RoomsPlacement_CheckEdgeReach(pair<int, int> start_of_the_region,
                                                                                  pair<int, int> end_of_the_region,
                                                                                  unsigned long x_max,
                                                                                  unsigned long y_max) {
    pair<int, int> st_new_region, end_new_region;
    pair<int, int> st_new_room_region = start_of_the_region, end_new_room_region = end_of_the_region;
    pair<pair<int, int>, pair<int, int>> output;
    if (start_of_the_region.first >= end_of_the_region.first) {
        if (start_of_the_region.second >= end_of_the_region.second) { // x++ y++
            // start of the region
            if (start_of_the_region.first < x_max - 1) {
                st_new_region.first = start_of_the_region.first + 1;
            } else st_new_room_region.first--;
            if (start_of_the_region.second < y_max - 1) {
                st_new_region.second = start_of_the_region.second + 1;
            } else st_new_room_region.second--;
            // end
            if (end_of_the_region.first > 0) {
                end_new_region.first = end_of_the_region.first--;
            } else end_new_room_region.first++;
            if (end_of_the_region.second > 0) {
                end_new_region.second = end_of_the_region.second--;
            } else end_new_room_region.second++;
        } else { //x++ y--
            if (start_of_the_region.first < x_max - 1) {
                st_new_region.first = start_of_the_region.first + 1;
            } else st_new_room_region.first--;
            if (start_of_the_region.second > 0) {
                st_new_region.second = start_of_the_region.second - 1;
            } else st_new_room_region.second++;
            if (end_of_the_region.first > 0) {
                end_new_region.first = end_of_the_region.first--;
            } else end_new_room_region.first++;
            if (end_of_the_region.second < y_max - 1) {
                end_new_region.second = end_of_the_region.second++;
            } else end_new_room_region.second--;
        }
    } else {
        if (start_of_the_region.second >= end_of_the_region.second) { // x-- y++
            if (start_of_the_region.first > 0) {
                st_new_region.first = start_of_the_region.first - 1;
            } else st_new_room_region.first++;
            if (start_of_the_region.second < y_max - 1) {
                st_new_region.second = start_of_the_region.second + 1;
            } else st_new_room_region.second--;
            if (end_of_the_region.first < x_max - 1) {
                end_new_region.first = end_of_the_region.first++;
            } else end_new_room_region.first--;
            if (end_of_the_region.second > 0) {
                end_new_region.second = end_of_the_region.second--;
            } else end_new_room_region.second++;
        } else { //x-- y--
            if (start_of_the_region.first > 0) {
                st_new_region.first = start_of_the_region.first - 1;
            } else st_new_room_region.first++;
            if (start_of_the_region.second > 0) {
                st_new_region.second = start_of_the_region.second - 1;
            } else st_new_room_region.second++;
            if (end_of_the_region.first < x_max - 1) {
                end_new_region.first = end_of_the_region.first++;
            } else end_new_room_region.first--;
            if (end_of_the_region.second < y_max - 1) {
                end_new_region.second = end_of_the_region.second++;
            } else end_new_room_region.second--;
        }
    }
    output.first = st_new_room_region;
    output.second = end_new_room_region;
    return output;

}

vector<vector<int>> MazeGenerator::RoomsPlacement_MakingRoomInside(pair<int, int> start_of_the_region,
                                                                   pair<int, int> end_of_the_region,
                                                                   vector<vector<int>> &square_) {
    for (int i = min(start_of_the_region.first, end_of_the_region.first);
         i < max(start_of_the_region.first, end_of_the_region.first); i++) {
        for (int j = min(start_of_the_region.second, end_of_the_region.second);
             j < max(start_of_the_region.second, end_of_the_region.second); j++) {
            square_[i][j] = 1;
            num_of_free_fields++;
        }
    }
}

bool MazeGenerator::CouldMakeCorridor(int direction, int from_x, int from_y, int to_x, int to_y, vector<vector<int>> square_) {
    //weakness of algorithm
    //mole moves at least by 2 steps/squares
    //and I protected edges (not in satisfying way, because it ruins a bit great mazes with unpredictable field form)
    bool result = false;
    if((direction == 0 && from_y <= to_y) || (direction == 1 && from_x >= to_x) || (direction == 2 && from_y >= to_y) || (direction == 3 && from_x <= to_x)){
        cout << "Error in CouldMakeCorridor. Wrong Direction\n";
        cout << "direction = " << direction << "\n";
        cout << "from_x = " << from_x << "\n";
        cout << "from_y = " << from_y << "\n";
        cout << "to_x = " << to_x << "\n";
        cout << "to_y = " << to_y << "\n";
        return false;
    }
    cout << "Reach MazeGenerator::CouldMakeCorridor 0\n";
    if (to_x < 1 || to_x > square_.size() - 2) return result;
    if (to_y < 1 || to_y > square_[to_x].size() - 2) return result;

    // Check whole way whether it passable
    int dif_x = abs(to_x - from_x), dif_y = abs(to_y - from_y);
    cout << "Reach MazeGenerator::CouldMakeCorridor 1\n";
    for (int i = 1; i < max(dif_x, dif_y); i++) {
        if (dif_x > dif_y) {
            cout << "Reach MazeGenerator::CouldMakeCorridor 1_1\n";
            // here from_y = to_y
            int one_square = square_[from_x + i * (dif_x / (to_x - from_x))][to_y];
            cout << "one_square[" << from_x + i * (dif_x / (to_x - from_x)) << "][" << to_y <<"]: " << one_square << "\n";
            // wall or entrance
            if (one_square != 0 && one_square != 3) return result;
        } else {
            cout << "Reach MazeGenerator::CouldMakeCorridor 1_2\n";
            // here from_x = to_x
            int one_square = square_[to_x][from_y + i * (dif_y / (to_y - from_y))];
            cout << "one_square[" << to_x << "][" << from_y + i * (dif_y / (to_y - from_y)) <<"]: " << one_square << "\n";
            if (one_square != 0 && one_square != 3) return result;
        }
    }
    cout << "Reach MazeGenerator::CouldMakeCorridor 2\n";
    vector<int> searchedforfieldtypes = {1, 2, 4, 5};
    vector<pair<int, int>> excludepoints_ = {};
    result = CheckFieldSurroundingsReturnFalseIfFoundSearched(direction, from_x, from_y, to_x, to_y, square_, dif_x, dif_y,
                                                     searchedforfieldtypes, excludepoints_);
    cout << "Reach MazeGenerator::CouldMakeCorridor 3\n";
    return result;
}

bool MazeGenerator::CheckFieldSurroundingsReturnFalseIfFoundSearched(int direction, int from_x, int from_y, int to_x,
                                                                     int to_y, const vector<vector<int>> &square_,
                                                                     int dif_x, int dif_y,
                                                                     vector<int> searchedforfieldtypes,
                                                                     vector<pair<int, int>> excludepoint) {
    cout << "Reach MazeGenerator::CheckFieldSurroundingsReturnFalseIfFoundSearched 1\n";
    if(IsOutofVectorVectorSize(square_, from_x, from_y)) return false;
    if(IsOutofVectorVectorSize(square_, to_x, to_y)) return false;
    if(dif_x < 0 || dif_y < 0) return false;
    if(!IsDirectionCorrect(direction, make_pair(from_x, from_y), make_pair(to_x, to_y))) return  false;
    // Check surrounding
    // There have to be only walls or Entrances
    // (No corridors/Reached entrances that are blockable)
    // Directions:
    // Up, up-right, right, down-right, down, down-left, left, up-left
    int dirMod[8][2] = {{0,  -1},
                        {1,  -1},
                        {1,  0},
                        {1,  1},
                        {0,  1},
                        {-1, 1},
                        {-1, 0},
                        {-1, -1},
    };
    pair<int, int> mod = make_pair(0, 0);
    if (dif_x > dif_y) {
        if (to_x - from_x > 0) mod.first = 1;
        else mod.first = -1;
    } else {
        if (to_y - from_y > 0) mod.second = 1;
        else mod.second = -1;
    }
    cout << "Reach MazeGenerator::CheckFieldSurroundingsReturnFalseIfFoundSearched 2\n";
    int x_t = from_x, y_t = from_y;
    for (int j = 1; j <= max(dif_x, dif_y); j++) {
        from_x += mod.first;
        from_y += mod.second;
        for (int i = 0; i < 8; i++) {
            if(abs(i - ((direction + 2) % 4) * 2) < 3 || (direction == 2 && i == 7) || (direction == 1 && i == 0)) {
                cout << "if(abs(i - ((direction + 2) % 4) * 2) < 3 || (direction == 2 && i == 7))\n";
                cout << "((direction + 2) % 4) * 2) = " << ((direction + 2) % 4) * 2 << "\n";
                cout << "dirrection = " << direction << " i = " << i << "\n";
                continue;
            }
            x_t = from_x + dirMod[i][0];
            y_t = from_y + dirMod[i][1];
            bool isexcluded = false;
            for (int l = 0; l < excludepoint.size(); ++l) {
                if(x_t == excludepoint[l].first && y_t == excludepoint[l].second){
                    isexcluded = true;
                    break;
                }
            }
            if(isexcluded) continue;
            if(IsOutofVectorVectorSize(square_, x_t, y_t)) {
                cout << "Reach MazeGenerator::CheckFieldSurroundingsReturnFalseIfFoundSearched 2_0\n";
                cout << "IsOutofVectorVectorSize\n";
                return false;
            }
            int one_square = square_[x_t][y_t];
            for (int k = 0; k < searchedforfieldtypes.size(); ++k) {
                if (one_square == searchedforfieldtypes[k]) {
                    cout << "Reach MazeGenerator::CheckFieldSurroundingsReturnFalseIfFoundSearched 2_1\n";
                    cout << "i = " << i << "\n";
                    cout << "square_[" << x_t << "][" << y_t << "] = " << square_[x_t][y_t] << "\n";
                    return false;
                }
            }
        }
    }
    cout << "Reach MazeGenerator::CheckFieldSurroundingsReturnFalseIfFoundSearched 3\n";
    return true;
}

bool MazeGenerator::IsDirectionCorrect(int direction, pair<int, int> from, pair<int, int> to) {
    if(direction == 0 && from.second <= to.second) return false;
    if(direction == 1 && from.first >= to.first) return false;
    if(direction == 2 && from.second >= to.second) return false;
    if(direction == 3 && from.first <= to.first) return false;
    return true;
}

int MazeGenerator::Direction(Random_Generator_ *Rand_gen) {
    return Rand_gen->Rand(0, 3);
}

bool MazeGenerator::IsOutofVectorVectorSize(vector<vector<int>> square_, int x, int y) {
    if(x > square_.size() - 1) return true;
    if(x < 0) return true;
    if(y > square_[0].size() - 1) return true;
    if(y < 0) return true;
    return false;
}

//??
bool MazeGenerator::IsRightDirection(int x, int y, int direction_, vector<vector<int>> square_) {
    if (IsNegative(x, y, -1)) return false;
    if (y > square_[x].size() - 1 || x > square_.size() - 1) return false;
    if (y < 2 && direction_ == 0) return false;
    if (x < 2 && direction_ == 3) return false;
    if (x > square_.size() - 3 && direction_ == 1) return false;
    if (y > square_[x].size() - 3 && direction_ == 2) return false;
    if (direction_ == 0 && square_[x][y - 2] == 1) return false;
    if (direction_ == 1 && square_[x + 2][y] == 1) return false;
    if (direction_ == 2 && square_[x][y + 2] == 1) return false;
    if (direction_ == 3 && square_[x - 2][y] == 1) return false;
    return true;
}

int MazeGenerator::RightDirection(Random_Generator_ *Rand_gen, int x, int y, int direction,
                                  vector<vector<int>> square_) {
    bool canMove[4] = {true, true, true, true};
    bool deadend_ = false;
    int dir = -1;  // Means deadend reached
    while (!IsRightDirection(x, y, direction, square_)) {
        canMove[direction] = false;
        for (int j = 0; j < 4; j++) {
            if (canMove[j]) break;
            else if (j == 3) deadend_ = true;
        }
        if (!deadend_) direction = Direction(Rand_gen);
        else return dir;
    }
    dir = direction;
    return dir;
}

int MazeGenerator::PaceLength(Random_Generator_ *Rand_gen, int difficulty_) {
    if (difficulty_ > 10) difficulty_ = 10;
    if (difficulty_ < 0) difficulty_ = 0;
    int maxPace = 12, minPace = 2;
    int pace = Rand_gen->Rand(minPace, maxPace - difficulty_);
    return pace;
}

pair<int, int> MazeGenerator::Move(Random_Generator_ *Rand_gen, int x, int y, vector<vector<int>> &square_, int &num_of_free_fields_) {
    cout << "Reach MazeGenerator::Move 0\n";
    pair<int, int> pos = make_pair(x, y);
    if (IsNegative(x, y, -1)) return pos;
    int direction = Direction(Rand_gen);
    int minPaceLength = 2;
    char dirDescription[4] = {'u', 'r', 'd', 'l'};
    int dirMod[4][2] = {{0,  -1},
                        {1,  0},
                        {0,  1},
                        {-1, 0}};
    cout << "Reach MazeGenerator::Move 1\n";
    direction = RightDirection(Rand_gen, x, y, direction, square_);
    if (direction == -1) return pos;
    int x_mod = x + minPaceLength * dirMod[direction][0];
    int y_mod = y + minPaceLength * dirMod[direction][1];
    cout << "Reach MazeGenerator::Move 1_2\n";
    cout << "direction = " << dirDescription[direction] << "\n";
    if (square_[x_mod][y_mod] == 0) {
        cout << "Reach MazeGenerator::Move 2\n";
        int rnd = Rand_gen->Rand(0, kRoomProbabilityMax);
        if(rnd <= roomProbability){
            // one step forward and generate room
            pos = make_pair(x + dirMod[direction][0], y + dirMod[direction][1]);
            square_[x + dirMod[direction][0]][y + dirMod[direction][1]] = 1;
            num_of_free_fields_++;
            pair<int, int> prev_pos = pos;
            cout << "Reach MazeGenerator::Move 2_1\n";
            cout << "num_of_free_fields: " << num_of_free_fields_ << "\n";
            pos = RoomGenerator(Rand_gen, square_, pos, direction, num_of_free_fields_);
            cout << "num_of_free_fields: " << num_of_free_fields_ << "\n";
            if(prev_pos != pos) return pos;
            else {
                pos = make_pair(x - dirMod[direction][0], y - dirMod[direction][1]);
                square_[x - dirMod[direction][0]][y - dirMod[direction][1]] = 0;
                num_of_free_fields_--;
            }
        }
        int paceLength = PaceLength(Rand_gen, difficulty);
        x_mod = x + paceLength * dirMod[direction][0];
        y_mod = y + paceLength * dirMod[direction][1];
        while (!CouldMakeCorridor(direction, x, y, x_mod, y_mod, square_)) {
            cout << "New paceLength = " << paceLength - 1 << "\n";
            paceLength--;
            cout << "prev. x_mod = " << x_mod << "\n";
            cout << "prev. y_mod = " << y_mod << "\n";
            x_mod = x + paceLength * dirMod[direction][0];
            y_mod = y + paceLength * dirMod[direction][1];
            cout << "new x_mod = " << x_mod << "\n";
            cout << "new y_mod = " << y_mod << "\n";
            if (paceLength == 1) {
                x_mod = x;
                y_mod = y;
                break;
            }
        }
        cout << "Reach MazeGenerator::Move 3\n";
        pos = make_pair(x_mod, y_mod);
        return pos;
    }
    cout << "Reach MazeGenerator::Move 4\n";
    return pos;
}

vector<vector<int>> MazeGenerator::LabyrinthMenu(vector<vector<int>> &square_) {
    int option_ = -1;
    while (option_ != 0) {
        cout << "Before Labyrinth will appear you can change nearly every field.\n";
        cout << "Choose what to do:\n";
        cout << "0 - If you are already satisfied with its form.\n";
        cout << "1 - Set labyrinth difficulty. "
                "The higher difficulty means higher chance to get another turn/fork on next step.\n";
        cout << "2 - Set rooms(If you need regular door or just hole in it you will have to place entrance later). Not implemented yet.\n";
        cout << "3 - Set field type. (To delete any complex object like entrance or trap just place '0' on it)\n";
        cout << "4 - Set room probability (if you want to have randomly generated rooms)\n";
        cout << "5 - Set room sizes (only for randomly generated rooms)\n";


        option_ = IsNumber(option_, 0, 5);
        if (option_ == 1) difficulty = Set_Difficulty();
        else if (option_ == 2) {
            //  Visualizer(square_);
            //  square_ = RoomsPlacement(square_);
        } else if (option_ == 3) {
            Visualizer(square_);
            pair<pair<int, int>, pair<int, int>> input = RegionSelect(square_);
            square_ = Set_FieldType(input.first, input.second, square_);
        } else if (option_ == 4) {
            roomProbability = Set_RoomProbability();
        } else if (option_ == 5) {
            cout << "Choose Length(0) Width(1) Height(2)\n";
            int lengthorwidthorheight = IsNumber(lengthorwidthorheight, 0, 2);
            int * roomsizes[3] = {&RoomLengthMax, &RoomWidthMax, &RoomHeightMax};
            cout << "current number:" << *roomsizes[lengthorwidthorheight] << "\n";
            *roomsizes[lengthorwidthorheight] = Set_RoomSize();
            cout << "Reach MazeGenerator::LabyrinthMenu option 5 *roomsizes[lengthorwidthorheight] ="
            << *roomsizes[lengthorwidthorheight] << "\n";
        }
    }
    cout << "Reach MazeGenerator::LabyrinthMenu 1\n";
    return square_;
}

void MazeGenerator::Set(int valuetobechanged, int value1, int value2, int value3, int value4, bool boolvalue1,
                        bool boolvalue2) {
    if (valuetobechanged == 0) {
        difficulty = value1;
        num_of_free_fields = value3;
        num_of_deadends = value4;
    } else if (valuetobechanged == 1) {
        //add entrance info
        Entrance_info entranceInfo;
        entranceInfo.id = value1;
        entranceInfo.order = value2;
        entranceInfo.is_blockable = boolvalue1;
        entranceInfo.blocked = boolvalue2;
        entranceInfo.name = "";
        entranceInfo.trigger_name = "";
        entranceInfo.linkedsquares.push_back(make_pair(value3, value4));
        entrance_info.push_back(entranceInfo);
        entrances[value3][value4] = value1;
        square[value3][value4] = 3;
        num_of_free_fields++;
    } else if (valuetobechanged == 2) {
        //remove entrance info found by id
        if (!entrance_info.empty()) {
            for (int i = 0; i < entrance_info.size(); ++i) {
                if (entrance_info[i].id == value1) {
                    entrance_info[i] = entrance_info[entrance_info.size() - 1];
                    entrance_info.pop_back();
                    break;
                }
            }
        } else cout << "entrance_info is empty. Nothing to delete.\n";

    } else if (valuetobechanged == 3) {
        //add to existing entrance_info pair(value3, value4)
        if (!entrance_info.empty()) {
            for (int i = 0; i < entrance_info.size(); ++i) {
                if (entrance_info[i].id == value1) {
                    entrance_info[i].linkedsquares.push_back(make_pair(value3, value4));
                    entrances[value3][value4] = entrance_info[i].id;
                    num_of_free_fields++;
                    break;
                } else if (i == entrance_info.size() - 1)
                    cout << "id not found in entrance_info. Unable to add pair.\n";
            }
        } else cout << "entrance_info is empty. Nothing to add to.\n";

    } else if (valuetobechanged == 4) {
        //delete from existing entrance_info pair(value3, value4)
        if (!entrance_info.empty()) {
            for (int i = 0; i < entrance_info.size(); ++i) {
                if (entrance_info[i].id == value1) {
                    for (int j = 0; j < entrance_info[i].linkedsquares.size(); ++j) {
                        if (entrance_info[i].linkedsquares[j].first == value3 &&
                            entrance_info[i].linkedsquares[j].second == value4) {
                            entrance_info[i].linkedsquares[j] = entrance_info[i].linkedsquares[
                                    entrance_info[i].linkedsquares.size() - 1];
                            entrance_info[i].linkedsquares.pop_back();
                            entrances[value3][value4] = -1;
                            num_of_free_fields--;
                            break;
                        } else if (j == entrance_info[i].linkedsquares.size() - 1) cout << "pair not found.\n";
                    }
                    break;
                } else if (i == entrance_info.size() - 1)
                    cout << "id not found in entrance_info. Unable to delete pair.\n";
            }
        } else cout << "entrance_info is empty. Nothing to delete from.\n";
    } else if (valuetobechanged == 5) {
        //change field type in (value3, value4)
        if (square[value1][value2] != 1 && square[value1][value2] != 3 && (value3 == 1 || value3 == 3)) num_of_free_fields++;
        if (square[value1][value2] == 1 && square[value1][value2] == 3 && value3 != 1 && value3 != 3 && num_of_free_fields > 0) num_of_free_fields--;
        square[value1][value2] = value3;
    } else if (valuetobechanged == 6) {
        //add/remove a deadend in (value3, value4)
        if (deadend[value3][value4] == 0) {
            num_of_deadends++;
            deadend[value3][value4] = 1;
        } else {
            if (num_of_deadends > 0) num_of_deadends--;
            deadend[value3][value4] = 0;
        }
    } else if (valuetobechanged == 7) {
        //add entrance id to (value3, value4)
        entrances[value3][value4] = value1;
    } /*else if(valuetobechanged == 8){

} else if(valuetobechanged == 9){

}*/
}

int MazeGenerator::Set_Difficulty() {
    cout << "Set Dungeon(labyrinth) difficulty.\n";
    int difficulty_ = IsNumber(difficulty_, kDifficulty_Min, kDifficulty_Max);
    return difficulty_;
}

Entrance_info MazeGenerator::Set_Entrance() {
    Entrance_info output;
    //Default id
    output.id = entrance_info.size();
    cout << "(Your ID now is " << output.id << ".)\n";
    //Entrance struct
    output.order = output.id;
    cout << "For entrance with ID " << output.id << " set settings. :P\n";
    cout << "Set order. Entrance with order 0 will be starting point of the labyrinth. Or you can set it same as ID.\n";
    output.order = IsNumber(output.order, 0, INT_MAX - 1);
    cout
            << "Set whether this entrance is blockable. Blockable Entrance could be reached once and only once. 1/0 (Yes/No)\n";
    int isblockable_ = IsNumber(isblockable_, 0, 1);
    output.is_blockable = isblockable_ == 1;
    cout << "Is it blocked now? 1/0 (Yes/No)\n";
    int isblocked_ = IsNumber(isblocked_, 0, 1);
    output.blocked = isblocked_ == 1;
    cout << "Set name. (Just for you.)\n";
    cin >> output.name;
    cout << "Set trigger name. (not implemented yet... But you can set it.)\n";
    cin >> output.trigger_name;
    cout << "That's all.\n";
    return output;
}

int MazeGenerator::Set_RoomSize() {
    cout << "new value:" << "\n";
    int result = IsNumber(result, 1, INT32_MAX - 1);
    return result;
}

Entrance_info MazeGenerator::ZeroIdEntranceInfo() const {
    Entrance_info ZeroId;
    ZeroId.trigger_name = "";
    ZeroId.order = -1;
    ZeroId.name = "default";
    ZeroId.is_blockable = false;
    ZeroId.blocked = false;
    ZeroId.id = 0;
    return ZeroId;
}

vector<vector<int>> MazeGenerator::Set_FieldType(pair<int, int> start_of_the_region, pair<int, int> end_of_the_region,
                                                 vector<vector<int>> &square_) {
    // Asking identifiers for each field
    cout << "For the region (" << start_of_the_region.first << ", " << start_of_the_region.second << ") - ("
         << end_of_the_region.first << ", " << end_of_the_region.second << ")\n";
    cout << "Set field type.\n";
    cout << "id descriptions:\n"
         << "0 - wall.\n"
         << "1 - corridor/empty.\n"
         << "2 - room wall.\n"
         << "3 - Entrance/Exit.\n"
         << "4 - Nonbreakable wall.\n"
         << "-1 - Go back.\n";
    int field_type;
    field_type = IsNumber(field_type, -1, 4);
    if (field_type == -1) return square_;
    //TODO: replace entrance_info with set to prevent two values with same order
    if (field_type == 3) entrance_info.push_back(Set_Entrance());

    int min_x = min(start_of_the_region.first, end_of_the_region.first);
    int max_x = max(start_of_the_region.first, end_of_the_region.first);
    int min_y = min(start_of_the_region.second, end_of_the_region.second);
    int max_y = max(start_of_the_region.second, end_of_the_region.second);
    for (int j = min_y; j <= max_y; ++j) {
        for (int i = min_x; i <= max_x; ++i) {
            DeleteOldInfoInSquare(square_, j, i);
            square_[i][j] = field_type;
            if (field_type == 3) {
                num_of_free_fields++;
                entrances[i][j] = entrance_info[entrance_info.size() - 1].id;
                entrance_info[entrance_info.size() - 1].linkedsquares.push_back(make_pair(i, j));
            }
        }
    }

    return square_;
}

void MazeGenerator::DeleteOldInfoInSquare(const vector<vector<int>> &square_, int j, int i) {
    if (square_[i][j] == 3) {
        for (int k = 0; k < entrance_info.size(); ++k) {
            if (entrance_info[k].id == entrances[i][j]) {
                for (int l = 0; l < entrance_info[k].linkedsquares.size(); ++l) {
                    if (entrance_info[k].linkedsquares[l].first == i && entrance_info[k].linkedsquares[l].second == j) {
                        entrance_info[k].linkedsquares[l] = entrance_info[k].linkedsquares[
                                entrance_info[k].linkedsquares.size() - 1];
                        entrance_info[k].linkedsquares.pop_back();
                        break;
                    }
                }
                break;
            }
        }
        entrances[i][j] = -1;
        num_of_free_fields--;
    }
}

void MazeGenerator::Visualizer(vector<vector<int>> square_) {
    // I found stuff that looks fine to my opinion
    // 0x02500 +=
    // 2, 3, 5, 7, 15, 19, 23, 27, 32, 40, 48, 56, 66, 81  - 108, 136, 137, 167, 169, 178, 179
    // Example:
    // printwc(0x02502);
    vector<vector<wchar_t>> uni_symbols = VisualizerTakeBattlefieldReturnGraphics(square_);
    for (int j = 0; j < uni_symbols[0].size(); ++j) {
        for (int i = 0; i < uni_symbols.size(); ++i) {
            printwc(uni_symbols[i][j]);
        }
        cout << "\n";
    }
}

vector<vector<wchar_t>> MazeGenerator::VisualizerTakeBattlefieldReturnGraphics(vector<vector<int>> square_) {
    //cout << "MazeGenerator::VisualizerTakeBattlefieldReturnGraphics reach 0\n";
    //cout << "MazeGenerator::VisualizerTakeBattlefieldReturnGraphics reach \n";
    vector<vector<wchar_t>> buf(square_.size(), vector<wchar_t>(square_[0].size()));

    /*
     * Here I'm using formula to draw an appropriate field.
     * Imagine that we have one square which is not empty space
     * n - will be value of upper square (0 if not exists)
     * m - right value, p - bottom value, q - left
     * then n*1 + m*10 + p*100 + q*1000 will be the id for it
     * to simplify it values can not contain different numbers
     * except 0.
     * Example:
     * Wrong: 401 14 4414 1114
     * Right: 404 44 4444 1111 1110
     *
     * There are most of shown symbols
        0  1  2  3  4  5  6  7  8  9
    0   ─  ━  │  ┃  ┄  ┅  ┆  ┇  ┈  ┉
    1   ┊  ┋  ┌  ┍  ┎  ┏  ┐  ┑  ┒  ┓
    2   └  ┕  ┖  ┗  ┘  ┙  ┚  ┛  ├  ┝
    3   ┞  ┟  ┠  ┡  ┢  ┣  ┤  ┥  ┦  ┧
    4   ┨  ┩  ┪  ┫  ┬  ┭  ┮  ┯  ┰  ┱
    5   ┲  ┳  ┴  ┵  ┶  ┷  ┸  ┹  ┺  ┻
    6   ┼  ┽  ┾  ┿  ╀  ╁  ╂  ╃  ╄  ╅
    7   ╆  ╇  ╈  ╉  ╊  ╋  ╌  ╍  ╎  ╏
    8   ═  ║  ╒  ╓  ╔  ╕  ╖  ╗  ╘  ╙
    9   ╚  ╛  ╜  ╝  ╞  ╟  ╠  ╡  ╢  ╣
    10  ╤  ╥  ╦  ╧  ╨  ╩  ╪  ╫  ╬  ╭
    11  ╮  ╯  ╰  ╱  ╲  ╳  ╴  ╵  ╶  ╷
    12  ╸  ╹  ╺  ╻  ╼  ╽  ╾  ╿  ▀  ▁
    13  ▂  ▃  ▄  ▅  ▆  ▇  █  ▉  ▊  ▋
    14  ▌  ▍  ▎  ▏  ▐  ░  ▒  ▓  ▔  ▕
    15  ▖  ▗  ▘  ▙  ▚  ▛  ▜  ▝  ▞  ▟
    16  ■  □  ▢  ▣  ▤  ▥  ▦  ▧  ▨  ▩
    17  ▪  ▫  ▬  ▭  ▮  ▯  ▰  ▱  ▲  △
    18  ▴  ▵  ▶  ▷  ▸  ▹  ►  ▻  ▼  ▽
    19  ▾  ▿  ◀  ◁  ◂  ◃  ◄  ◅  ◆  ◇
    20  ◈  ◉  ◊  ○  ◌  ◍  ◎  ●  ◐  ◑
    21  ◒  ◓  ◔  ◕  ◖  ◗  ◘  ◙  ◚  ◛
    22  ◜  ◝  ◞  ◟  ◠  ◡  ◢  ◣  ◤  ◥
    23  ◦  ◧  ◨  ◩  ◪  ◫  ◬  ◭  ◮  ◯

     */
    //cout << "MazeGenerator::VisualizerTakeBattlefieldReturnGraphics reach 1\n";
    map<int, wchar_t> uni_sym = GetMapIntWchar_t();

    for (int j = 0; j < square_[0].size(); j++) {
        for (int i = 0; i < square_.size(); i++) {
            if (square_[i][j] == 0) square_[i][j] = -1;
        }
    }

    //cout << "MazeGenerator::VisualizerTakeBattlefieldReturnGraphics reach 2\n";
    for (int j = 0; j < square_[0].size(); j++) {
        //cout << "MazeGenerator::VisualizerTakeBattlefieldReturnGraphics reach 2_1 j =" << j << "\n";
        for (int i = 0; i < square_.size(); i++) {
            //cout << "MazeGenerator::VisualizerTakeBattlefieldReturnGraphics reach 2_2 i =" << i << "\n";
            if (square_[i][j] == -1) {  // wall
                //cout << "MazeGenerator::VisualizerTakeBattlefieldReturnGraphics reach 2_3\n";
                buf[i][j] = uni_sym.at(-1);
                int id_, n = 0, m = 0, p = 0, q = 0;
                if (i != 0) q = square_[i - 1][j];
                if (j != square_[j].size() - 1) p = square_[i][j + 1];
                if (i != square_.size() - 1) m = square_[i + 1][j];
                if (j != 0) n = square_[i][j - 1];
                // simplify
                if (n != 0 && n != -1) n = -1;
                if (m != 0 && m != -1) m = -1;
                if (p != 0 && p != -1) p = -1;
                if (q != 0 && q != -1) q = -1;
                //formula
                // (-1)* because walls are zeros, so I had to replace them with -1
                id_ = (-1) * (n + m * 10 + p * 100 + q * 1000);
                buf[i][j] = uni_sym.at(id_);
                //cout << "MazeGenerator::VisualizerTakeBattlefieldReturnGraphics reach 2_4\n";
            } else if (square_[i][j] == 4) {  // unbreakable wall
                //cout << "MazeGenerator::VisualizerTakeBattlefieldReturnGraphics reach 2_5\n";
                buf[i][j] = uni_sym.at(-4);
                int id_, n = 0, m = 0, p = 0, q = 0;
                if (i != 0) q = square_[i - 1][j];
                if (j != square_[j].size() - 1) p = square_[i][j + 1];
                if (i != square_.size() - 1) m = square_[i + 1][j];
                if (j != 0) n = square_[i][j - 1];
                // simplify
                if (n != 0 && n != 4) n = 4;
                if (m != 0 && m != 4) m = 4;
                if (p != 0 && p != 4) p = 4;
                if (q != 0 && q != 4) q = 4;
                //formula
                id_ = n + m * 10 + p * 100 + q * 1000;
                buf[i][j] = uni_sym.at(id_);
                //cout << "MazeGenerator::VisualizerTakeBattlefieldReturnGraphics reach 2_6\n";
            } else if (square_[i][j] == 1) {  // empty
                //cout << "MazeGenerator::VisualizerTakeBattlefieldReturnGraphics reach 2_7\n";
                buf[i][j] = uni_sym.at(-2);
                //cout << "MazeGenerator::VisualizerTakeBattlefieldReturnGraphics reach 2_8\n";
            } else if (square_[i][j] == 3) {
                buf[i][j] = uni_sym.at(3);
            } else if (square_[i][j] == 2) {
                buf[i][j] = uni_sym.at(2);
            } else {
                buf[i][j] = uni_sym.at(-404);
            }
            //printwc(buf[i][j]);
        }
    }
    //cout << "MazeGenerator::VisualizerTakeBattlefieldReturnGraphics reach 3\n";
    return buf;
}

map<int, wchar_t> MazeGenerator::GetMapIntWchar_t() const {
    map<int, wchar_t> uni_sym;
    uni_sym.insert(make_pair(0, 0x02500 + 146)); // wall block
    uni_sym.insert(make_pair(1, 0x02500 + 117)); // upper half-edge
    uni_sym.insert(make_pair(4, 0x02500 + 121));
    uni_sym.insert(make_pair(10, 0x02500 + 118));
    uni_sym.insert(make_pair(11, 0x02500 + 20));
    uni_sym.insert(make_pair(40, 0x02500 + 122));  // right bold half-edge
    uni_sym.insert(make_pair(44, 0x02500 + 23));
    uni_sym.insert(make_pair(100, 0x02500 + 119));  // bottom half_edge
    uni_sym.insert(make_pair(101, 0x02500 + 2));
    uni_sym.insert(make_pair(110, 0x02500 + 12));
    uni_sym.insert(make_pair(111, 0x02500 + 28));
    uni_sym.insert(make_pair(400, 0x02500 + 123));
    uni_sym.insert(make_pair(404, 0x02500 + 3));
    uni_sym.insert(make_pair(440, 0x02500 + 15));
    uni_sym.insert(make_pair(444, 0x02500 + 35));
    uni_sym.insert(make_pair(1000, 0x02500 + 116));  // left half-edge
    uni_sym.insert(make_pair(1001, 0x02500 + 24));
    uni_sym.insert(make_pair(1010, 0x02500 + 0));
    uni_sym.insert(make_pair(1011, 0x02500 + 52));
    uni_sym.insert(make_pair(1100, 0x02500 + 16));
    uni_sym.insert(make_pair(1101, 0x02500 + 36));
    uni_sym.insert(make_pair(1110, 0x02500 + 44));
    uni_sym.insert(make_pair(1111, 0x02500 + 146));  //
    uni_sym.insert(make_pair(4000, 0x02500 + 120));  // left bold half-edge
    uni_sym.insert(make_pair(4004, 0x02500 + 27));
    uni_sym.insert(make_pair(4040, 0x02500 + 1));
    uni_sym.insert(make_pair(4044, 0x02500 + 59));
    uni_sym.insert(make_pair(4400, 0x02500 + 19));
    uni_sym.insert(make_pair(4404, 0x02500 + 43));
    uni_sym.insert(make_pair(4440, 0x02500 + 51));
    uni_sym.insert(make_pair(4444, 0x02500 + 136));  // 0x02500 + 75
    uni_sym.insert(make_pair(-1, 0x02500 + 146));  // wall block
    uni_sym.insert(make_pair(-4, 0x02500 + 136));  // filled square
    uni_sym.insert(make_pair(-2, 0x02000));
    uni_sym.insert(make_pair(3, 0x0235f));  // entrance
    uni_sym.insert(make_pair(2, 0x02591));  // room wall
    uni_sym.insert(make_pair(-404, 0x02426));
    return uni_sym;

    //  notes
    // Диапазон: 1F300-1F5FF
}


pair<pair<int, int>, pair<int, int>> MazeGenerator::RegionSelect(vector<vector<int>> square_) {
    pair<pair<int, int>, pair<int, int>> output;
    int input;
    cout << "For first point.\n";
    cout << "Type x:\n";
    input = IsNumber(input, 0, (int) square_[0].size() - 1);
    output.first.first = input;
    cout << "Type y:\n";
    input = IsNumber(input, 0, (int) square_.size() - 1);
    output.first.second = input;
    cout << "For second point.\n";
    cout << "Type x:\n";
    input = IsNumber(input, 0, (int) square_[0].size() - 1);
    output.second.first = input;
    cout << "Type y:\n";
    input = IsNumber(input, 0, (int) square_.size() - 1);
    output.second.second = input;
    return output;
}

vector<vector<int>> MazeGenerator::GetLabirinth() {
    return square;
}

int MazeGenerator::Get(int what) {
    if (what == 0) return difficulty;
    if (what == 1) return roomProbability;
    if (what == 2) return num_of_free_fields;
    if (what == 3) return num_of_deadends;
}

vector<vector<int>> MazeGenerator::GetVectorVectorInt(int what) {
    if (what == 0) return entrances;
    if (what == 1) return deadend;
    if (what == 2) return square;
}

void MazeGenerator::ShowField(vector<vector<int>> &square_) {
    for (int j = 0; j < square_[0].size(); ++j) {
        for (int i = 0; i < square_.size(); ++i) {
            cout << square_[i][j];
        }
        cout << "\n";
    }
}

pair<int, int> MazeGenerator::RoomGenerator(Random_Generator_ *Rand_gen, vector<vector<int>> &square_,
                                            pair<int, int> from, int direction_, int &num_of_free_fields_) {
    pair<int, int> result = from;
    cout << "Reach MazeGenerator::RoomGenerator 0\n";
    /*
     * 0. Choose size
     * 1. choose where room starts
     *   1.1 No options? return pos : goto 2
     * 2. check surroundings for region excluding @from point
     * 3. Fine? return pos : goto 1
     * */


    //  linelength is a perpendicular to direction
    //  while there are free space move within line and try to secure place for room
    //  if no options are avalible return result
    //  else give back starting pos and direction
    //  Build room (checking from max size to min)
    //  randomly choose exit on room wall (no less than 1 square from entrance)
    //  random place doors
    //  result is exit
    //  if there are no appropriate place for exit than return rnd room point

    //  length(ordinate)
    //  width(abscissa)
    //
    int roomlength = Rand_gen->Rand(kRoomLengthMin, RoomLengthMax);
    int roomwidth = Rand_gen->Rand(kRoomWidthMin, RoomWidthMax);
    int roomheight = Rand_gen->Rand(kRoomHeightMin, RoomHeightMax);
    int linelength;
    pair<int, int> to;
    int linestartcount = 0;  // when linestartcount == linelength no matching space found
    if(direction_ == 0 || direction_ == 2) linelength = roomwidth;
    else linelength = roomheight;
    cout << "linelength: " << linelength << "\n";
    while(true){
        cout << "Reach MazeGenerator::RoomGenerator 1\n";
        int roomlength_ = roomlength;
        int roomheight_ = roomheight;
        int roomwidth_ = roomwidth;
        bool iswayempty_;
        result = RoomGenerator_RoomStartingPoint(Rand_gen, square_, result, direction_, linelength, linestartcount);
        if(result == from) return result;
        char dirDescription[4] = {'u', 'r', 'd', 'l'};
        int dirMod[4][2] = {{0,  -1},
                            {1,  0},
                            {0,  1},
                            {-1, 0}};
        // linelength must be min for  x or y
        // otherwise room will appear in distance
        // and there will be no possible way to connect it to corridors
        int roomlengthmin = kRoomLengthMin;
        int roomwidthmin = kRoomWidthMin;
        int roomheightmin = kRoomHeightMin;
        vector<pair<int, int>> excludepoints_ = {from};
        if(direction_ == 0 || direction_ == 2) roomwidthmin = max(kRoomWidthMin, roomwidth);
        else roomlengthmin = max(kRoomHeightMin, roomheight);
        to = make_pair(result.first + roomwidthmin * dirMod[direction_][0],
                                      result.second + roomlengthmin * dirMod[direction_][1]);
        cout << "Reach MazeGenerator::RoomGenerator 2\n";
        if(RoomGenerator_RoomRegionCheckIfEmpty(Rand_gen, square_, result, to, excludepoints_, direction_)){
            cout << "Reach MazeGenerator::RoomGenerator 3\n";
            to = make_pair(result.first + roomwidth_ * dirMod[direction_][0],
                           result.second + roomlength_ * dirMod[direction_][1]);
            int count = 0;
            while(!RoomGenerator_RoomRegionCheckIfEmpty(Rand_gen, square_, result, to, excludepoints_, direction_)){
                cout << "Room sizes: width: " << roomwidth_ << " length: " << roomlength_ << ")\n";
                count++;
                if(count % 2 == 1) roomlength_--;
                else roomwidth_--;
                if(roomheight < 2 || roomwidth < 2) break;
                to = make_pair(result.first + roomwidth_ * dirMod[direction_][0],
                               result.second + roomlength_ * dirMod[direction_][1]);
            }
            break;
        } else {
            cout << "Reach MazeGenerator::RoomGenerator 4\n";
            linelength--;
            if(linelength < 1) {
                cout << "Reach MazeGenerator::RoomGenerator 4_1 linelength < 1 \n";
                result = from;
                return result;
            }
        }
        cout << "Reach MazeGenerator::RoomGenerator 5\n";
    }
    result = RoomGenerator_FreeSpaceAndReturnNewPos(Rand_gen, square_, result, to, from, direction_, num_of_free_fields_);
    return result;
}

pair<int, int> MazeGenerator::RoomGenerator_RoomStartingPoint(Random_Generator_ *Rand_gen, vector<vector<int>> &square_,
                                                              pair<int, int> from, int direction_, int &linelength,
                                                              int linestartcount_) {
    cout << "Reach MazeGenerator::RoomGenerator_RoomStartingPoint 0\n";
    pair<int, int> result = from;
    vector<bool> usedpos (linelength, false);
    int count = 0;
    while(true){
        cout << "Reach MazeGenerator::RoomGenerator_RoomStartingPoint 1\n";
        if(count == linelength) {
            if(linelength == 1) break;
            linelength--;
            count = 0;
            while(!usedpos.empty()) usedpos.pop_back();
            usedpos.resize(linelength, false);
        }
        int rndlinestartingpos = Rand_gen->Rand(0, linelength - 1);
        while(usedpos[rndlinestartingpos]) rndlinestartingpos = Rand_gen->Rand(0, linelength - 1);
        usedpos[rndlinestartingpos] = true;
        count++;
        cout << "rndlinestartingpos " << rndlinestartingpos << "\n";
        int dirMod[4][2] = {{-1 * rndlinestartingpos,  -1},
                            {1,  -1 * rndlinestartingpos},
                            {rndlinestartingpos,  1},
                            {-1, rndlinestartingpos}};
        int startingpos_x = from.first + dirMod[direction_][0];
        int startingpos_y = from.second + dirMod[direction_][1];
        cout << " direction_ " << direction_ << "\n";
        cout << "startingpos_x " << startingpos_x;
        cout << " startingpos_y " << startingpos_y << "\n";
        cout << "Reach MazeGenerator::RoomGenerator_RoomStartingPoint 2\n";
        if (startingpos_x > square_.size() - 1 || startingpos_x < 1) continue;
        if (startingpos_y > square_[0].size() - 1 || startingpos_y < 1) continue;
        if(square_[startingpos_x][startingpos_y] == 0 || square_[startingpos_x][startingpos_y] == 3){
            cout << "Reach MazeGenerator::RoomGenerator_RoomStartingPoint 3\n";
            int mod[4][2] = {{1,  0},
                             {0,  1},
                             {-1,  0},
                             {0, -1}};
            bool iswayempty = true;
            for (int i = 1; i <= linelength; ++i) {
                if(square_[startingpos_x + i * mod[direction_][0]][startingpos_y + i * mod[direction_][1]] != 0
                && square_[startingpos_x + i * mod[direction_][0]][startingpos_y + i * mod[direction_][1]] != 3) {
                    iswayempty = false;
                    break;
                }
            }
            if(iswayempty){
                result = make_pair(startingpos_x, startingpos_y);
                break;
            }
        }
        cout << "Reach MazeGenerator::RoomGenerator_RoomStartingPoint 4\n";
    }
    cout << "Reach MazeGenerator::RoomGenerator_RoomStartingPoint 5\n";
    cout << "Room starting point:(" << result.first << " ," << result.second << ")\n";
    return result;
}

bool MazeGenerator::RoomGenerator_RoomRegionCheckIfEmpty(Random_Generator_ *Rand_gen, vector<vector<int>> &square_,
                                                         pair<int, int> from, pair<int, int> to,
                                                         vector<pair<int, int>> excludepoints, int direction_) {
    cout << "Reach MazeGenerator::RoomGenerator_RoomRegionCheckIfEmpty 1\n";
    bool result = true;
    int dirMod[4][2] = {{0,  -1},
                        {1,  0},
                        {0,  1},
                        {-1, 0}};
    //  that has not to be in room
    //  no empty space before, no unbreakable walls, no reached entrances
    vector<int> searchedforfieldtypes = {1, 4, 5};
    //  firstly check orthogonal vector back and forward (not in every single time orthogonal (Y is fixed))
    //  then check all straight vectors (X is fixed value)
    int orthogonaldirection = (direction_ + 1) % 4;  // direction is from 0 to 3
    cout << "orthogonal: " << orthogonaldirection << "\n";
    cout << "from: " << from.first << " " << from.second << "\n";
    cout << "to: " << to.first << " " << from.second << "\n";
    cout << "abs(from.first - to.first): " << abs(from.first - to.first) << "\n";
    result = CheckFieldSurroundingsReturnFalseIfFoundSearched(orthogonaldirection, from.first, from.second, to.first,
                                                              from.second, square_, abs(from.first - to.first), 0,
                                                              searchedforfieldtypes, excludepoints);
    if (!result) return result;
    orthogonaldirection = (orthogonaldirection + 2) % 4;
    cout << "backward orthogonal: " << orthogonaldirection << "\n";
    cout << "from: " << to.first << " " << from.second << "\n";
    cout << "to: " << from.first << " " << from.second << "\n";
    cout << "abs(from.first - to.first): " << abs(from.first - to.first) << "\n";
    result = CheckFieldSurroundingsReturnFalseIfFoundSearched(orthogonaldirection, to.first, from.second, from.first,
                                                              from.second, square_, abs(from.first - to.first), 0,
                                                              searchedforfieldtypes, excludepoints);
    if (!result) return result;
    cout << "Reach MazeGenerator::RoomGenerator_RoomRegionCheckIfEmpty 1_1 from: (" << from.first<< ", " << from.second << ")\n";
    cout << "to: (" << to.first<< ", " << to.second << ")\n";
    for (int i = from.first; i <= to.first; ++i) {
        int dif_x = 0, dif_y = abs(to.second - from.second);
        result = CheckFieldSurroundingsReturnFalseIfFoundSearched(direction_, i, from.second, i, to.second, square_,
                                                                  dif_x, dif_y, searchedforfieldtypes, excludepoints);
        if (!result) return result;
    }
    cout << "Reach MazeGenerator::RoomGenerator_RoomRegionCheckIfEmpty 2\n";
    return result;
}

pair<int, int> MazeGenerator::RoomGenerator_FreeSpaceAndReturnNewPos(Random_Generator_ *Rand_gen,
                                                                     vector<vector<int>> &square_, pair<int, int> from, pair<int, int> to,
                                                                     pair<int, int> entrance_, int direction_, int &num_of_free_fields_) {
    cout << "Reach MazeGenerator::RoomGenerator_FreeSpaceAndReturnNewPos 0\n";
    pair<int, int> result = entrance_;
    int dirMod[4][2] = {{-1,  1},
                        {-1,  -1},
                        {1,  -1},
                        {1, 1}};
    //  expand area by 1 field in all directions
    //  then change whole area to a room walls excluding entrance_ and any fields that weren't walls
    //  then change inner area to empty excluding -//-
    //  find exit on wall no less than 1 field from entrance* if there are such return it else return rnd pos
    //  *otherwise algorithm won't continue moving that way
    pair<int, int> new_from, new_to;
    cout << "Reach MazeGenerator::RoomGenerator_FreeSpaceAndReturnNewPos 0_1\n from: (" << from.first << ", " << from.second << ")\n";
    cout << "to: (" << to.first << ", " << to.second << ")\n";
    new_from.first = from.first + dirMod[direction_][0];
    new_from.second = from.second + dirMod[direction_][1];
    new_to.first = to.first - dirMod[direction_][0];
    new_to.second = to.second - dirMod[direction_][1];
    cout << "new_from: (" << new_from.first << ", " << new_from.second << ")\n";
    cout << "new_to: (" << new_to.first << ", " << new_to.second << ")\n";

    cout << "Room\n";
    cout << "inner space: (" << from.first << ", " << from.second << ") - (" << to.first << ", " << to.second << ")\n";
    cout << "walls: (" << new_from.first << ", " << new_from.second << ") - (" << new_to.first << ", " << new_to.second << ")\n";
    for (int i = min(new_from.first, new_to.first); i <= max(new_from.first, new_to.first); ++i) {
        for (int j = min(new_from.second, new_to.second); j <= max(new_from.second, new_to.second); ++j) {
            if (i == entrance_.first && j == entrance_.second) continue;
            if (IsOutofVectorVectorSize(square_, i, j)) {
                cout << "Error in RoomGenerator_FreeSpaceAndReturnNewPos X or Y is out of bounds.\n";
                cout << "X = " << i << "\n";
                cout << "Y = " << j << "\n";
                return result;
            }
            if(square_[i][j] == 0) square_[i][j] = 2;
            else cout << "RoomGenerator_FreeSpaceAndReturnNewPos 0_2 square_[i][j] = " << square_[i][j] << "\n";
        }
    }
    for (int i = min(from.first, to.first); i <= max(from.first, to.first); ++i) {
        for (int j = min(from.second, to.second); j <= max(from.second, to.second); ++j) {
            if(square_[i][j] == 2) {
                num_of_free_fields_++;
                square_[i][j] = 1;
            } else cout << "RoomGenerator_FreeSpaceAndReturnNewPos 0_3 square_[i][j] = " << square_[i][j] << "\n";
        }
    }
    cout << "Reach MazeGenerator::RoomGenerator_FreeSpaceAndReturnNewPos 1\n";
    //  rnd pos
    pair<int, int> exit;
    //  rnd times try to find exit
    int count = 0;
    int count_max = Rand_gen->Rand(min(max(abs(from.first - to.first), abs(from.second - to.second)), 4), abs(from.first - to.first) + abs(from.second - to.second));
    cout << "count_max: " << count_max << "\n";
    while(true){
        cout << "Reach MazeGenerator::RoomGenerator_FreeSpaceAndReturnNewPos 2\n";
        if(count == count_max) {
            cout << "Reach MazeGenerator::RoomGenerator_FreeSpaceAndReturnNewPos 2_0\n";
            while(true){
                cout << "Reach MazeGenerator::RoomGenerator_FreeSpaceAndReturnNewPos 2_0_1\n";
                result = make_pair(Rand_gen->Rand(from.first, to.first), Rand_gen->Rand(from.second, to.second));
                cout << "square_[result.first][result.second]: " << square_[result.first][result.second] << "\n";
                if(square_[result.first][result.second] == 1 || square_[result.first][result.second] == 2) break;
            }
            square_[result.first][result.second] = 1;
            return result;
        }
        int x_or_y = Rand_gen->Rand(0, 1);
        if(x_or_y) {
            exit.second = Rand_gen->Rand(min(from.second, to.second), max(from.second, to.second));
            x_or_y = Rand_gen->Rand(0, 1);
            if(x_or_y){
                exit.first = new_to.first;
            } else {
                exit.first = new_from.first;
            }
        } else {
            exit.first = Rand_gen->Rand(min(from.first, to.first), max(from.first, to.first));
            x_or_y = Rand_gen->Rand(0, 1);
            if(x_or_y){
                exit.second = new_to.second;
            } else {
                exit.second = new_from.second;
            }
        }
        if(abs(entrance_.first - exit.first) > 1 || abs(entrance_.second - exit.second) > 1) {
            cout << "Reach MazeGenerator::RoomGenerator_FreeSpaceAndReturnNewPos 2_1\n";
            cout << "exit: (" << exit.first << ", " << exit.second << ")\n";
            square_[exit.first][exit.second] = 1;
            num_of_free_fields++;
            result = exit;
            return result;
        }
        count++;
    }
    cout << "Reach MazeGenerator::RoomGenerator_FreeSpaceAndReturnNewPos 3\n";
    return result;
}

int MazeGenerator::Set_RoomProbability() {
    cout << "Set room probability.\n";
    int probability_ = IsNumber(probability_, kRoomProbabilityMin, kRoomProbabilityMax);
    return probability_;
}

Entrance_info MazeGenerator::GetEntranceInfo(int id) {
    if (id < 0 || id > entrance_info.size() - 1) {
        cout << "Incorrect id\n";
        return entrance_info[0];
    }
    return entrance_info[id];
}

pair<int, int> MazeGenerator::GetZeroOrderEntrancePos(Random_Generator_ *Rand_gen, vector<Entrance_info> entrance_info_) {
    int zeroorderid = 0, minorder = INT32_MAX;
    pair<int, int> result = make_pair(1, 1);
    int savedpos = 0;
    //cout << "Reach MazeGenerator::GetZeroOrderEntrancePos 0\n";
    for (int i = 0; i < entrance_info_.size(); i++) {
        if (entrance_info_[i].order > 0 && entrance_info_[i].order < minorder) {
            zeroorderid = entrance_info_[i].id;
            savedpos = i;
            minorder = entrance_info_[i].order;
        }
    }
    //cout << "Reach MazeGenerator::GetZeroOrderEntrancePos 1\n";
    //Random starting point
    //if there are more than one entrance with id = zeroorderid

    if (entrance_info_[savedpos].id == zeroorderid && !entrance_info_[savedpos].linkedsquares.empty()) {
        result = entrance_info_[savedpos].linkedsquares[Rand_gen->Rand(0,
                                                                       entrance_info_[savedpos].linkedsquares.size() -
                                                                       1)];
    } else {
        //if entrance_info with min id got no elements
        result = entrance_info_[Rand_gen->Rand(0, entrance_info_.size() - 1)].linkedsquares[Rand_gen->Rand(0,
                                                                                                           entrance_info_[savedpos].linkedsquares.size() -
                                                                                                           1)];
    }

    //cout << "Reach MazeGenerator::GetZeroOrderEntrancePos 1_2\n";
    return result;
}

pair<int, int>
MazeGenerator::GetNewRandPos(Random_Generator_ *Rand_gen, pair<int, int> starting_pos, vector<vector<int>> square_,
                             vector<vector<int>> deadend_) {
    cout << "Reach MazeGenerator::GetNewRandPos 0\n";
    pair<int, int> result = starting_pos;
    int count = 0;
    while (true) {
        //cout << "Reach MazeGenerator::GetNewRandPos 1\n";
        count++;
        result.first = Rand_gen->Rand(1, square_.size() - 2);// TODO: replace with set of empty squares
        result.second = Rand_gen->Rand(1, square_[0].size() - 2);
        pair<int, int> zeroorderentrancepair = GetZeroOrderEntrancePos(Rand_gen, entrance_info);
        int zeroorderentranceid = entrances[zeroorderentrancepair.first][zeroorderentrancepair.second];
        if ((square_[result.first][result.second] == 1 || entrances[result.first][result.second] == zeroorderentranceid) && deadend_[result.first][result.second] != 1) break;
        if (count >= square_[0].size() * square_.size() * 2) {
            result = starting_pos;
            break;
        }
    }
    cout << "Reach MazeGenerator::GetNewRandPos 3\n";
    cout << "new rand pos = (" << result.first << ", " << result.second << ")\n";
    return result;
}

vector<vector<int>> MazeGenerator::FreeSpaceAfterDigging(vector<vector<int>> &square_, pair<int, int> from,
                                                         pair<int, int> to, int &num_of_free_fields_) {
    bool did_x_changed;
    if (from.first != to.first) did_x_changed = true;
    else if (from.second != to.second) did_x_changed = false;
    else return square_;
    int range_end = max(abs(from.first - to.first), abs(from.second - to.second));
    int mod;
    if (did_x_changed) mod = (to.first - from.first) / abs(to.first - from.first);
    else mod = (to.second - from.second) / abs(to.second - from.second);
    for (int i = 1; i <= range_end; ++i) {
        if (did_x_changed) {
            // -1 / +1
            if (from.first + (i * mod) < 0 || from.first + (i * mod) > square_.size() - 1) {
                cout << "Error in MazeGenerator::FreeSpaceAfterDigging X is out of range\n";
                cout << "X = " << from.first << "";
                cout << "X + i * mod = " << from.first + (i * mod) << "\n";
            }
            if(square_[from.first + (i * mod)][from.second] != 3 && square_[from.first + (i * mod)][from.second] != 4) {
                square_[from.first + (i * mod)][from.second] = 1;
                num_of_free_fields_++;
            }
        } else {
            // -1 / +1
            if (from.second + (i * mod) < 0 || from.second + (i * mod) > square_[0].size() - 1) {
                cout << "Error in MazeGenerator::FreeSpaceAfterDigging Y is out of range\n";
                cout << "Y = " << from.second << "";
                cout << "Y + i * mod = " << from.second + (i * mod) << "\n";
            }
            if(square_[from.first][from.second + (i * mod)] != 3 && square_[from.first][from.second + (i * mod)] != 4){
                square_[from.first][from.second + (i * mod)] = 1;
                num_of_free_fields_++;
            }
        }
    }
    return square_;
}

/*Method which uses all of the others and return field filled with corridors and walls :D*/
vector<vector<int>>
MazeGenerator::Build_Labyrinth(Random_Generator_ *Rand_gen, vector<vector<int>> &square_, int num_of_deadends_,
                               int num_of_free_fields_, vector<vector<int>> deadend_) {
    square_ = LabyrinthMenu(square_);
    cout << "Reach MazeGenerator::Build_Labyrinth 0\n";
    square = square_;
    bool issatisfying = false;
    ofstream output_file;
    output_file.open("maze_in_steps.txt");
    if(!output_file.is_open()) {
        cout << "Error in opening file\n";
        cout <<'\n';
    }
    output_file << "\n\n\n *** \n";
    cout << "Reach MazeGenerator::Build_Labyrinth 1\n";
    while (!issatisfying) {

        cout << "Reach MazeGenerator::Build_Labyrinth 1_2\n";
        cout << "entrance_info[0].id = " << entrance_info[0].id << "\n";
        cout << "entrance_info[1].id = " << entrance_info[1].id << "\n";
        cout << "entrance_info[2].id = " << entrance_info[2].id << "\n";
        cout << "entrances[1][1] = " << entrances[1][1] << "\n";
        cout << "entrances[8][15] = " << entrances[square_.size() - 2][square_[0].size() - 5] << "\n";
        cout << "entrance_info[1].order = " << entrance_info[1].order << "\n";
        cout << "entrance_info[2].order = " << entrance_info[2].order << "\n";
        pair<int, int> pos = GetZeroOrderEntrancePos(Rand_gen, entrance_info);
        cout << "starting pos = (" << pos.first << ", " << pos.second << ")\n";
        pair<int, int> prev_pos;
        cout << "Reach MazeGenerator::Build_Labyrinth 2\n";
        double num_of_deadends_d = num_of_deadends_, num_of_free_fields_d = num_of_free_fields_;
        while (true) {
            cout << "Reach MazeGenerator::Build_Labyrinth 3\n";
            prev_pos = pos;
            cout << "prev pos = (" << pos.first << ", " << pos.second << ")\n";
            pos = Move(Rand_gen, pos.first, pos.second, square_, num_of_free_fields_);
            cout << "new pos = (" << pos.first << ", " << pos.second << ")\n";
            //num_of_free_fields_ += max(abs(prev_pos.first - pos.first), abs(prev_pos.second - pos.second));
            cout << "prev. num_of_free_fields_ = " << num_of_free_fields_ << "\n";
            if(min(abs(pos.first - prev_pos.first), abs(pos.second - prev_pos.second)) == 0){
                square_ = FreeSpaceAfterDigging(square_, prev_pos, pos, num_of_free_fields_);
                for (int j = 0; j < square_[0].size(); ++j) {
                    for (int i = 0; i < square_.size(); ++i) {
                        output_file << square_[i][j];
                    }
                    output_file << "\n";
                }
            }
            cout << "new. num_of_free_fields_ = " << num_of_free_fields_ << "\n";
            if (pos == prev_pos) {
                cout << "Reach MazeGenerator::Build_Labyrinth 4\n";
                num_of_deadends_++;
                deadend_[pos.first][pos.second] = 1;
                num_of_deadends_d = num_of_deadends_;
                num_of_free_fields_d = num_of_free_fields_;
                if (num_of_deadends_ == num_of_free_fields_ ||
                    num_of_free_fields_d / num_of_deadends_d < Kpercentage_of_filled_space_in_the_end){
                    cout << "num_of_free_fields_d / num_of_deadends_d < Kpercentage_of_filled_space_in_the_end\n";
                    cout << num_of_free_fields_d << " / " <<  num_of_deadends_d << " < " << Kpercentage_of_filled_space_in_the_end << "\n";
                    break;
                }

                pos = GetNewRandPos(Rand_gen, pos, square_, deadend_);
                if (pos == prev_pos) {
                    cout << "Reach MazeGenerator::Build_Labyrinth 4_1\n";
                    //Just to be sure that nearly all free fields are deadends
                    pos = GetNewRandPos(Rand_gen, pos, square_, deadend_);
                    if (pos == prev_pos) break;
                    cout << "Reach MazeGenerator::Build_Labyrinth 4_2\n";
                }
            }
            if ((num_of_deadends_ == num_of_free_fields_ && num_of_free_fields_ != 0) || num_of_deadends_ < 0 ||
                num_of_free_fields_ < 0)
            {
                cout << "num_of_deadends_ == num_of_free_fields_\n";
                cout << num_of_deadends_ << " == " <<  num_of_free_fields_ << "\n";
                break;
            }
        }
        cout << "Reach MazeGenerator::Build_Labyrinth 5\n";
        Visualizer(square_);
        ShowField(square_);
        cout << "Are you satisfied with labirinth? 1/0 (Yes/No)\n";
        int issatisfying_i = IsNumber(issatisfying_i, 0, 1);
        if (issatisfying_i == 1) issatisfying = (bool) issatisfying_i;
        else {
            square_ = square;
            deadend_ = deadend;
            num_of_deadends_ = num_of_deadends;
            num_of_free_fields_ = num_of_free_fields;
            //printwc(0x0000c);  // clear console
        }
    }
    num_of_deadends_ = num_of_deadends;
    num_of_free_fields_ = num_of_free_fields;
    output_file.close();
    return square_;
}

