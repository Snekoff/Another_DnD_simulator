#include "MazeGenerator.h"

using namespace std;

MazeGenerator::MazeGenerator(Random_Generator_ *Rand_gen, vector <vector<int>> square_) {
// smth here
    deadend.resize(square_.size());
    for (int i = 0; i < deadend.size(); i++) {
        deadend[i].resize(square_[i].size());
    }
    entrances.resize(square_.size());
    for (int i = 0; i < entrances.size(); i++) {
        entrances[i].resize(square_[i].size());
    }
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
vector <vector<int>> MazeGenerator::RoomsPlacement(vector <pair<int, int>> roomsRegions,
                                                   vector <pair<int, int>> roomsEntrances,
                                                   vector <vector<int>> square_) {
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
        // square_ here is an address
        /// TEST
        vector <pair<int, int>> new_room_region = RoomsPlacement_BuildingWalls(begin, ending, square_);
        square = RoomsPlacement_MakingRoomInside(new_room_region[0], new_room_region[1], square_);

    }
    //
    /*Написать структуру для входов, (дверь есть/нет, какая, прочность(урон для разрушения),
     * замок(сложность, 0 - нет замка))*/
    for (int i = 0; i < roomsEntrances.size(); i++) {
        if (!IsNegative(roomsEntrances[i].first, roomsEntrances[i].second, i + 1)
            && square_[roomsEntrances[i].first][roomsEntrances[i].second] == 2) {
            square_[roomsEntrances[i].first][roomsEntrances[i].second] = 3;
        } else std::cout << "Entrance #" << i + 1 << " is placed not on room wall\n";
    }
}

vector <pair<int, int>> MazeGenerator::RoomsPlacement_BuildingWalls(pair<int, int> start_of_the_region,
                                                                    pair<int, int> end_of_the_region,
                                                                    vector <vector<int>> &square_
) {
    vector <pair<int, int>> output;
    pair<int, int> st_new_region, end_new_region;
    pair<int, int> st_new_room_region = start_of_the_region, end_new_room_region = end_of_the_region;
    //User choose size and placement, but if it is too close to the edge of the world
    //walls will be automaticaly builded to prevent reach nonexisting array member
    // if it is possible region expands by 1 in all directions
    // and build there walls
    output = RoomsPlacement_CheckEdgeReach(start_of_the_region, end_of_the_region, square_[0].size(), square_.size());
    if(output.empty()) return output;
    for (int i = min(output[0].first, output[1].first);
         i < max(output[0].first, output[1].first); i++) {
        for (int j = min(output[0].second, output[1].second);
             j < max(output[0].second, output[1].second); j++) {
            if(square_[i][j] > 0) continue;
            square_[i][j] = 2;
        }
    }
    return output;
}

vector<pair<int, int>> MazeGenerator::RoomsPlacement_CheckEdgeReach(pair<int, int> start_of_the_region,
                                                                    pair<int, int> end_of_the_region, unsigned long x_max,
                                                                    unsigned long y_max) {
    pair<int, int> st_new_region, end_new_region;
    pair<int, int> st_new_room_region = start_of_the_region, end_new_room_region = end_of_the_region;
    vector<pair<int, int>> output;
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
    output.push_back(st_new_room_region);
    output.push_back(end_new_room_region);
    return output;

}
vector <vector<int>> MazeGenerator::RoomsPlacement_MakingRoomInside(pair<int, int> start_of_the_region,
                                                                    pair<int, int> end_of_the_region,
                                                                    vector <vector<int>> square_) {
    for (int i = min(start_of_the_region.first, end_of_the_region.first);
         i < max(start_of_the_region.first, end_of_the_region.first); i++) {
        for (int j = min(start_of_the_region.second, end_of_the_region.second);
             j < max(start_of_the_region.second, end_of_the_region.second); j++) {
            square_[i][j] = 1;
        }
    }
}

bool MazeGenerator::CouldMakeCorridor(int from_x, int from_y, int to_x, int to_y, vector <vector<int>> square_) {
    //weakness of algorithm
    //mole moves at least by 2 steps/squares
    //and I protected edges (not in satisfying way, because it ruins a bit great mazes with unpredictable field form)
    if (to_x < 3 || to_x > square_.size() - 3) return false;
    if (to_y < 3 || to_y > square_[to_x].size() - 3) return false;

    // Check whole way whether it passable
    int dif_x = abs(from_x - to_x), dif_y = abs(from_y - to_y);
    for (int i = 0; i < max(dif_x, dif_y); i++) {
        if (dif_x > dif_y) {
            int one_square = square_[from_x + (i + 1) * dif_x / (to_x - from_x)][to_y]; // here from_y = to_y
            // wall or entrance
            if (one_square != 0 && one_square != 3) return false;
        } else {
            int one_square = square_[to_x][from_y + (i + 1) * dif_y / (to_y - from_y)];// here from_x = to_x
            if (one_square != 0 && one_square != 3) return false;
        }
    }
    // Check surrounding
    // There have to be only walls or Entrances
    // (No corridors/Reached entrances)
    // Directions:
    // Up, up-right, rright, down-right, down, down-left, left, up-left
    int dirMod[8][2] = {{-1, 0},
                        {-1, 1},
                        {0,  1},
                        {1,  1},
                        {1,  0},
                        {1,  -1},
                        {0,  -1},
                        {-1, -1}};
    int x_t = from_x, y_t = from_y;
    for (int j = 0; j < max(dif_x, dif_y); j++) {
        for (int i = 0; i < 8; i++) {
            int one_square = square_[x_t + dirMod[i][0]][y_t + dirMod[i][1]];
            if (one_square == 1 || one_square == 5) return false;
        }
        if (x_t != to_x) x_t += (from_x - to_x) / dif_x;
        if (y_t != to_y) y_t += (from_y - to_y) / dif_y;
    }
    return true;
}

int MazeGenerator::Direction(Random_Generator_ *Rand_gen) {
    return Rand_gen->Rand(0, 3);
}

//??
bool MazeGenerator::IsRightDirection(int x, int y, int direction_, vector <vector<int>> square_) {
    if (IsNegative(x, y, -1)) return false;
    if (y > square_[x].size() - 1 || x > square_.size() - 1) return false;
    if (x < 2 && direction_ == 0) return false;
    if (y < 2 && direction_ == 3) return false;
    if (x > square_.size() - 3 && direction_ == 2) return false;
    if (y > square_[x].size() - 3 && direction_ == 1) return false;
    return true;
}

int MazeGenerator::RightDirection(Random_Generator_ *Rand_gen, int x, int y, int direction,
                                  vector <vector<int>> square_) {
    bool canMove[4] = {true, true, true, true};
    bool deadend = false;
    int dir = -1;  // Means deadend reached
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

int MazeGenerator::PaceLength(Random_Generator_ *Rand_gen, int difficulty_) {
    if (difficulty_ > 10) difficulty_ = 10;
    if (difficulty_ < 0) difficulty_ = 0;
    int maxPace = 12, minPace = 2;
    int pace = Rand_gen->Rand(minPace, maxPace - difficulty_);
    return pace;
}

pair<int, int> MazeGenerator::Move(Random_Generator_ *Rand_gen, int x, int y, vector <vector<int>> square_) {
    pair<int, int> pos = make_pair(x, y);
    if (IsNegative(x, y, -1)) return pos;
    int direction = Direction(Rand_gen);
    int minPaceLength = 2;
    char dirDescription[4] = {'u', 'r', 'd', 'l'};
    int dirMod[4][2] = {{-1, 0},
                        {0,  1},
                        {1,  0},
                        {0,  -1}};
    direction = RightDirection(Rand_gen, x, y, direction, square_);
    if (direction == -1) return pos;
    int x_mod = x + minPaceLength * dirMod[direction][0];
    int y_mod = y + minPaceLength * dirMod[direction][1];
    if (square_[x_mod][y_mod] == 0) {
        int paceLength = PaceLength(Rand_gen, difficulty);
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

vector<vector<int>> MazeGenerator::LabyrinthMenu(vector<vector<int>> square_) {
    int option_ = -1;
    while (option_ != 0) {
        cout << "Before Labyrinth will appear you can change nearly every field.\n";
        cout << "Choose what to do:\n";
        cout << "0 - If you are already satisfied with its form.\n";
        cout << "1 - Set labyrinth difficulty. The higher difficulty means higher chance to get another turn/fork on next field.\n";
        cout << "2 - Set entrances and exits. Set their options and (in later builds) triggers.\n";
        cout << "3 - Set field type. (to delete any complex object like entrance or trap just place '0' on it)\n";

        option_ = IsNumber(option_, 0, 3);
        if (option_ == 1) difficulty = Set_Difficulty();
        else if (option_ == 2){
            pair<pair<int, int>, pair<int, int>> input = RegionSelect(square_);
            vector<pair<pair<int, int>, int>> entr = Set_Entrance(input.first, input.second);
            for(int i = 0; i < entr.size(); i++){
                entrances[entr[i].first.first][entr[i].first.second] = entr[i].second;
            }
        }
        else if (option_ == 3){
            pair<pair<int, int>, pair<int, int>> input = RegionSelect(square_);
            square_ = Set_FieldType(input.first, input.second, square_);
        }
    }
    return square_;
}

void MazeGenerator::Set() {

}

int MazeGenerator::Set_Difficulty() {
    cout << "Set Dungeon(labyrinth) difficulty.\n";
    difficulty = IsNumber(difficulty, kDifficulty_Min, kDifficulty_Max);
}

vector<pair<pair<int, int>, int>> MazeGenerator::Set_Entrance(pair<int, int> start_of_the_region,
        pair<int, int> end_of_the_region) {
    int space;
    space = abs(start_of_the_region.first - end_of_the_region.first) *
            abs(start_of_the_region.second - end_of_the_region.second);
    vector<pair<pair<int, int>, int>> output;
    output.resize((unsigned)space);
    bool isIdentifierTheSame = true;
    cout << "Is identifier the same for whole region? (it means that whole entrance got same name, settings,"
            " triggers, so on)\n";
    cout << "0/1 (Yes/No)\n";
    string input;
    cin >> input;
    if(input[0] == '1' || input[0] == 'N') isIdentifierTheSame = false;
    pair<int, int> coords;
    coords.first = min(start_of_the_region.first, end_of_the_region.first);
    coords.second = min(start_of_the_region.second, end_of_the_region.second);
    int max_d = max(abs(start_of_the_region.first - end_of_the_region.first), abs(start_of_the_region.second - end_of_the_region.second));
    int min_d = min(abs(start_of_the_region.first - end_of_the_region.first), abs(start_of_the_region.second - end_of_the_region.second));
    //Default Entrance info
    if(entrance_info.empty()) {
        entrance_info.push_back(ZeroIdEntranceInfo());
    }
    //ask identifiers for each field
    for(int i = 0; i < max_d; i++){
        for(int j = 0; j < min_d; j++) {
            if(!isIdentifierTheSame || j == 0){
                //default id
                if(entrance_info.empty()) output[i+j].second = 1;
                else output[i+j].second = entrance_info.size();
                // ask for id
                cout << "for ("<< coords.first  << ", " << coords.second  << ") choose identifier. "
                                                                             "If you use same identifier few times "
                                                                             "regions just will counts as one. \n";
                cout << "(Your ID now is " << output[i+j].second << ".) Print -1 to leave it as is.\n";
                output[i+j].first.first = coords.first;
                output[i+j].first.second = coords.second;
                int inp = IsNumber(output[i+j].second, -1, INT_MAX - 1);
                if(inp != -1)  output[i+j].second = inp;
                /// CHECK whether this ID already exists!!
            } else {
                output[i+j].first.first = coords.first;
                output[i+j].first.second = coords.second;
                output[i+j].second = output[0].second;
            }
            //Entrance struct
            if(!isIdentifierTheSame || j == 0){
                Entrance_info entr_info;
                entr_info.id = output[i+j].second;
                entr_info.order = output[i+j].second;
                cout << "for entrance with ID " << output[i+j].second << " set settings. :P\n";
                cout << "Set order. Entrance with order 0 will be starting point of the labyrinth. Or you can set it same as ID.\n";
                entr_info.order = IsNumber(entr_info.order, 0, INT_MAX - 1);
                cout << "Set whether this entrance is blockable. Blockable Entrance could be reached once and only once. 0/1 (Yes/No)\n";
                entr_info.is_blockable = IsNumber(entr_info.is_blockable, false, true);
                cout << "Set name. (Just for you.)\n";
                cin >> entr_info.name;
                cout << "Set trigger name. (not implemented yet... But you can set it.)\n";
                cin >> entr_info.trigger_name;
                cout << "That's all.\n";
                ///Must first entrance be blocked? I think no.
                entr_info.blocked = false;
                entrance_info.push_back(entr_info);
            }
            //
            if(min_d == abs(start_of_the_region.second - end_of_the_region.second)) {coords.second++; }
            else {coords.first++; }
        }
        if(max_d == abs(start_of_the_region.first - end_of_the_region.first)) {coords.first++; coords.second = min(start_of_the_region.second, end_of_the_region.second);}
        else {coords.second++; coords.first = min(start_of_the_region.first, end_of_the_region.first);}
    }
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
}

vector<vector<int>> MazeGenerator::Set_FieldType(pair<int, int> start_of_the_region, pair<int, int> end_of_the_region, vector<vector<int>> square_) {
    // Asking identifiers for each field
    cout << "For the region (" << start_of_the_region.first << ", " << start_of_the_region.second << ") - (" << end_of_the_region.first << ", " << end_of_the_region.second << ")\n";
    cout << "Set field type.\n";
    cout << "id descriptions:/n"
         << "0 - wall/n"
         << "1 - corridor/empty/n"
         << "2 - room wall/n"
         << "3 - Exit/Entrance/n"
         << "4 - Nonbreakable wall/n"
         << "5 - Reached(Blocked) Entrance/n";
    int field_type;
    field_type = IsNumber(field_type, 0, 5);
    int max_d = max(abs(start_of_the_region.first - end_of_the_region.first), abs(start_of_the_region.second - end_of_the_region.second));
    int min_d = min(abs(start_of_the_region.first - end_of_the_region.first), abs(start_of_the_region.second - end_of_the_region.second));

    for(int i = 0; i < max_d; i++){
        for(int j = 0; j < min_d; j++) {
            if(min_d == abs(start_of_the_region.second - end_of_the_region.second)){
                square_[min(start_of_the_region.first, start_of_the_region.first) + i][min(start_of_the_region.second, start_of_the_region.second) + j] = field_type;
            } else {
                square_[min(start_of_the_region.first, start_of_the_region.first) + j][min(start_of_the_region.second, start_of_the_region.second) + i] = field_type;
            }
        }
    }
    return square_;
}

pair<pair<int, int>, pair<int, int>> MazeGenerator::RegionSelect(vector<vector<int>> square_) {
    pair<pair<int, int>, pair<int, int>> output;
    int input;
    cout << "For first point.\n";
    cout << "Type x:\n";
    input = IsNumber(input, 0, (int)square_[0].size() - 1);
    output.first.first = input;
    cout << "Type y:\n";
    input = IsNumber(input, 0, (int)square_.size() - 1);
    output.first.second = input;
    cout << "For second point.\n";
    cout << "Type x:\n";
    input = IsNumber(input, 0, (int)square_[0].size() - 1);
    output.second.first = input;
    cout << "Type y:\n";
    input = IsNumber(input, 0, (int)square_.size() - 1);
    output.second.second = input;
    return output;
}

vector<vector<int>> MazeGenerator::GetLabirinth() {
    return square;
}

int MazeGenerator::Get(int what) {
    if(what == 0) return difficulty;
    if(what == 1) return roomProbability;
}

Entrance_info MazeGenerator::GetEntranceInfo(int id) {
    if(id < 0 || id > entrance_info.size() - 1) {
        cout << "Incorrect id\n";
        return entrance_info[0];
    }
    return entrance_info[id];
}

int MazeGenerator::Dig(Random_Generator_ *Rand_gen) {
    pair<int, int> pos;
}

