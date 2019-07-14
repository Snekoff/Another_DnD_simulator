#include "MazeGenerator.h"

static const double Kpercentage_of_filled_space_in_the_end = 1.3;
using namespace std;

MazeGenerator::MazeGenerator(Random_Generator_ *Rand_gen, vector<vector<int>> square_) {
    num_of_deadends = 0;
    num_of_free_fields = 0;
    difficulty = 0;
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
    roomProbability = 1;
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
    if (to_x < 1 || to_x > square_.size() - 2) return false;
    if (to_y < 1 || to_y > square_[to_x].size() - 2) return false;

    // Check whole way whether it passable
    int dif_x = abs(to_x - from_x), dif_y = abs(to_y - from_y);
    cout << "Reach MazeGenerator::CouldMakeCorridor 1\n";
    for (int i = 1; i < max(dif_x, dif_y); i++) {
        if (dif_x > dif_y) {
            // here from_y = to_y
            int one_square = square_[from_x + i * (dif_x / (to_x - from_x))][to_y];
            // wall or entrance
            if (one_square != 0 && one_square != 3) return false;
        } else {
            // here from_x = to_x
            int one_square = square_[to_x][from_y + i * (dif_y / (to_y - from_y))];
            if (one_square != 0 && one_square != 3) return false;
        }
    }
    cout << "Reach MazeGenerator::CouldMakeCorridor 2\n";
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
    int x_t = from_x, y_t = from_y;
    for (int j = 0; j < max(dif_x, dif_y); j++) {
        for (int i = 0; i < 8; i++) {
            if (direction == 0) { if (i == 3 || i == 4 || i == 5) continue; }
            else if (direction == 1) { if (i == 5 || i == 6 || i == 7) continue; }
            else if (direction == 2) { if (i == 0 || i == 1 || i == 7) continue; }
            else { if (i == 1 || i == 2 || i == 3) continue; }
            int one_square = square_[x_t + dirMod[i][0]][y_t + dirMod[i][1]];
            if (one_square == 1 || one_square == 5) return false;
        }
        if (x_t != to_x) x_t += (to_x - from_x) / dif_x;
        if (y_t != to_y) y_t += (to_y - from_y) / dif_y;
    }
    cout << "Reach MazeGenerator::CouldMakeCorridor 3\n";
    return true;
}

int MazeGenerator::Direction(Random_Generator_ *Rand_gen) {
    return Rand_gen->Rand(0, 3);
}

//??
bool MazeGenerator::IsRightDirection(int x, int y, int direction_, vector<vector<int>> square_) {
    if (IsNegative(x, y, -1)) return false;
    if (y > square_[x].size() - 1 || x > square_.size() - 1) return false;
    if (y < 2 && direction_ == 0) return false;
    if (x < 2 && direction_ == 3) return false;
    if (x > square_.size() - 3 && direction_ == 1) return false;
    if (y > square_[x].size() - 3 && direction_ == 2) return false;
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

pair<int, int> MazeGenerator::Move(Random_Generator_ *Rand_gen, int x, int y, vector<vector<int>> square_) {
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
        cout
                << "1 - Set labyrinth difficulty. The higher difficulty means higher chance to get another turn/fork on next field.\n";
        cout << "2 - Set rooms(If you need regular door or hole in it you will have to place entrance later).\n";
        cout << "3 - Set field type. (To delete any complex object like entrance or trap just place '0' on it)\n";

        option_ = IsNumber(option_, 0, 3);
        if (option_ == 1) difficulty = Set_Difficulty();
        else if (option_ == 2) {
            Visualizer(square_);
            square_ = RoomsPlacement(square_);
        } else if (option_ == 3) {
            Visualizer(square_);
            pair<pair<int, int>, pair<int, int>> input = RegionSelect(square_);
            square_ = Set_FieldType(input.first, input.second, square_);
        }
    }
    cout << "Reach MazeGenerator::LabyrinthMenu 1\n";
    return square_;
}

void MazeGenerator::Set(int valuetobechanged, int value1, int value2, int value3, int value4, bool boolvalue1,
                        bool boolvalue2) {
    if (valuetobechanged == 0) {
        difficulty = value1;
        roomProbability = value2;
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
    difficulty = IsNumber(difficulty, kDifficulty_Min, kDifficulty_Max);
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
    map<int, wchar_t> uni_sym;
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
    uni_sym.insert(make_pair(1111, 0x02500 + 146));// 0x02500 + 60
    uni_sym.insert(make_pair(4000, 0x02500 + 120));   // left bold half-edge
    uni_sym.insert(make_pair(4004, 0x02500 + 27));
    uni_sym.insert(make_pair(4040, 0x02500 + 1));
    uni_sym.insert(make_pair(4044, 0x02500 + 59));
    uni_sym.insert(make_pair(4400, 0x02500 + 19));
    uni_sym.insert(make_pair(4404, 0x02500 + 43));
    uni_sym.insert(make_pair(4440, 0x02500 + 51));
    uni_sym.insert(make_pair(4444, 0x02500 + 136));// 0x02500 + 75
    uni_sym.insert(make_pair(-1, 0x02500 + 146));  // wall block
    uni_sym.insert(make_pair(-4, 0x02500 + 136));  // filled square
    uni_sym.insert(make_pair(-2, 0x02000));
    uni_sym.insert(make_pair(3, 0x02000 + 200)); // entrance

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
            } else {
                buf[i][j] = uni_sym.at(3);
            }
            //printwc(buf[i][j]);
        }
    }
    //cout << "MazeGenerator::VisualizerTakeBattlefieldReturnGraphics reach 3\n";
    return buf;
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
    cout << "Reach MazeGenerator::GetZeroOrderEntrancePos 0\n";
    for (int i = 0; i < entrance_info_.size(); i++) {
        if (entrance_info_[i].order > 0 && entrance_info_[i].order < minorder) {
            zeroorderid = entrance_info_[i].id;
            savedpos = i;
            minorder = entrance_info_[i].order;
        }
    }
    cout << "Reach MazeGenerator::GetZeroOrderEntrancePos 1\n";
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

    cout << "Reach MazeGenerator::GetZeroOrderEntrancePos 1_2\n";
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
                                                         pair<int, int> to) {
    bool did_x_changed;
    if (from.first != to.first) did_x_changed = true;
    else if (from.second != to.second) did_x_changed = false;
    else return square_;
    int range_end = max(abs(from.first - to.first), abs(from.second - to.second));
    int mod;
    if (did_x_changed) mod = (to.first - from.first) / abs(to.first - from.first);
    else mod = (to.second - from.second) / abs(to.second - from.second);
    for (int i = 1; i < range_end; ++i) {
        if (did_x_changed) {
            // -1 / +1
            if (from.first + (i * mod) < 0 || from.first + (i * mod) > square_.size() - 1) {
                cout << "Error in MazeGenerator::FreeSpaceAfterDigging X is out of range\n";
                cout << "X = " << from.first << "";
                cout << "X + i * mod = " << from.first + (i * mod) << "\n";
            }
            if(square_[from.first + (i * mod)][from.second] != 3 && square_[from.first + (i * mod)][from.second] != 4) square_[from.first + (i * mod)][from.second] = 1;
        } else {
            // -1 / +1
            if (from.second + (i * mod) < 0 || from.second + (i * mod) > square_[0].size() - 1) {
                cout << "Error in MazeGenerator::FreeSpaceAfterDigging Y is out of range\n";
                cout << "Y = " << from.second << "";
                cout << "Y + i * mod = " << from.second + (i * mod) << "\n";
            }
            if(square_[from.first][from.second + (i * mod)] != 3 && square_[from.first][from.second + (i * mod)] != 4) square_[from.first][from.second + (i * mod)] = 1;
        }
    }
    return square_;
}

/*Method which uses all the others and return field filled with corridors and walls :D*/
vector<vector<int>>
MazeGenerator::Build_Labirinth(Random_Generator_ *Rand_gen, vector<vector<int>> &square_, int num_of_deadends_,
                               int num_of_free_fields_, vector<vector<int>> deadend_) {
    square_ = LabyrinthMenu(square_);
    cout << "Reach MazeGenerator::Build_Labirinth 0\n";
    square = square_;
    bool issatisfying = false;
    cout << "Reach MazeGenerator::Build_Labirinth 1\n";
    while (!issatisfying) {
        cout << "Reach MazeGenerator::Build_Labirinth 1_2\n";
        cout << "entrance_info[0].id = " << entrance_info[0].id << "\n";
        cout << "entrance_info[1].id = " << entrance_info[1].id << "\n";
        cout << "entrance_info[2].id = " << entrance_info[2].id << "\n";
        cout << "entrances[1][1] = " << entrances[1][1] << "\n";
        cout << "entrances[8][15] = " << entrances[8][15] << "\n";
        cout << "entrance_info[1].order = " << entrance_info[1].order << "\n";
        cout << "entrance_info[2].order = " << entrance_info[2].order << "\n";
        pair<int, int> pos = GetZeroOrderEntrancePos(Rand_gen, entrance_info);
        cout << "starting pos = (" << pos.first << ", " << pos.second << ")\n";
        pair<int, int> prev_pos;
        cout << "Reach MazeGenerator::Build_Labirinth 2\n";
        double num_of_deadends_d = num_of_deadends_, num_of_free_fields_d = num_of_free_fields_;
        while (true) {
            cout << "Reach MazeGenerator::Build_Labirinth 3\n";
            prev_pos = pos;
            cout << "prev pos = (" << pos.first << ", " << pos.second << ")\n";
            pos = Move(Rand_gen, pos.first, pos.second, square_);
            cout << "new pos = (" << pos.first << ", " << pos.second << ")\n";
            num_of_free_fields_ += max(abs(prev_pos.first - pos.first), abs(prev_pos.second - pos.second));
            square_ = FreeSpaceAfterDigging(square_, prev_pos, pos);
            if (pos == prev_pos) {
                cout << "Reach MazeGenerator::Build_Labirinth 4\n";
                num_of_deadends_++;
                deadend_[pos.first][pos.second] = 1;
                num_of_deadends_d = num_of_deadends_;
                num_of_free_fields_d = num_of_free_fields_d;
                if (num_of_deadends_ == num_of_free_fields_ ||
                    num_of_free_fields_d / num_of_deadends_d > Kpercentage_of_filled_space_in_the_end)
                    break;
                pos = GetNewRandPos(Rand_gen, pos, square_, deadend_);
                if (pos == prev_pos) {
                    //Just to be sure that nearly all free fields are deadends
                    pos = GetNewRandPos(Rand_gen, pos, square_, deadend_);
                    if (pos == prev_pos) break;
                }
            }
            if ((num_of_deadends_ == num_of_free_fields_ && num_of_free_fields_ != 0) || num_of_deadends_ < 0 ||
                num_of_free_fields_ < 0)
                break;
        }
        cout << "Reach MazeGenerator::Build_Labirinth 5\n";
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
    return square_;
}

