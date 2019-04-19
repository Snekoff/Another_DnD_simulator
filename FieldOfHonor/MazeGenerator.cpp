#include "MazeGenerator.h"

using namespace std;

MazeGenerator::MazeGenerator(Random_Generator_ *Rand_gen, vector <vector<int>> square_) {
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
vector<vector<int>> MazeGenerator::RoomsPlacement(vector <vector<int>> square_) {
    pair<pair<int, int>, pair<int, int>> region;
    region = RegionSelect(square_);
    region = RoomsPlacement_BuildingWalls(region.first, region.second, square_);
    square = RoomsPlacement_MakingRoomInside(region.first, region.second, square_);
    return square;
}

pair<pair<int, int>, pair<int, int>> MazeGenerator::RoomsPlacement_BuildingWalls(pair<int, int> start_of_the_region,
                                                                    pair<int, int> end_of_the_region,
                                                                    vector <vector<int>> &square_
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
            if(square_[i][j] > 0) continue;
            square_[i][j] = 2;
        }
    }
    return output;
}

pair<pair<int, int>, pair<int, int>> MazeGenerator::RoomsPlacement_CheckEdgeReach(pair<int, int> start_of_the_region,
                                                                    pair<int, int> end_of_the_region, unsigned long x_max,
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
vector <vector<int>> MazeGenerator::RoomsPlacement_MakingRoomInside(pair<int, int> start_of_the_region,
                                                                    pair<int, int> end_of_the_region,
                                                                    vector <vector<int>> square_) {
    for (int i = min(start_of_the_region.first, end_of_the_region.first);
         i < max(start_of_the_region.first, end_of_the_region.first); i++) {
        for (int j = min(start_of_the_region.second, end_of_the_region.second);
             j < max(start_of_the_region.second, end_of_the_region.second); j++) {
            square_[i][j] = 1;
            num_of_free_fields++;
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
        cout << "2 - Set rooms(If you need regular door or hole in it you will have to place entrance later).\n";
        cout << "3 - Set field type. (To delete any complex object like entrance or trap just place '0' on it)\n";

        option_ = IsNumber(option_, 0, 3);
        if (option_ == 1) difficulty = Set_Difficulty();
        else if (option_ == 2){
            square_ = RoomsPlacement(square_);
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

Entrance_info MazeGenerator::Set_Entrance() {
    Entrance_info output;
    //Default Entrance info
    if (entrance_info.empty()) {
        entrance_info.push_back(ZeroIdEntranceInfo());
    }
    //Default id
    output.id = entrance_info.size();
    cout << "(Your ID now is " << output.id << ".)\n";
    //Entrance struct
    output.order = output.id;
    cout << "For entrance with ID " << output.id << " set settings. :P\n";
    cout << "Set order. Entrance with order 0 will be starting point of the labyrinth. Or you can set it same as ID.\n";
    output.order = IsNumber(output.order, 0, INT_MAX - 1);
    cout
    << "Set whether this entrance is blockable. Blockable Entrance could be reached once and only once. 0/1 (Yes/No)\n";
    output.is_blockable = IsNumber(output.is_blockable, false, true);  // Check
    cout << "Is it blocked now?\n";
    output.blocked = IsNumber(output.blocked, false, true);  // Check
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
}

vector<vector<int>> MazeGenerator::Set_FieldType(pair<int, int> start_of_the_region, pair<int, int> end_of_the_region,
                                                 vector<vector<int>> square_) {
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
    if (field_type == 3) entrance_info.push_back(Set_Entrance());

    int max_d = max(abs(start_of_the_region.first - end_of_the_region.first),
                    abs(start_of_the_region.second - end_of_the_region.second));
    int min_d = min(abs(start_of_the_region.first - end_of_the_region.first),
                    abs(start_of_the_region.second - end_of_the_region.second));

    for (int i = 0; i < max_d; i++) {
        for (int j = 0; j < min_d; j++) {
            if (min_d == abs(start_of_the_region.second - end_of_the_region.second)) {
                square_[min(start_of_the_region.first, start_of_the_region.first) + i][min(start_of_the_region.second, start_of_the_region.second) + j] = field_type;
                if(field_type == 3) entrances[min(start_of_the_region.first, start_of_the_region.first) + i][min(start_of_the_region.second, start_of_the_region.second) + j] = entrance_info[entrance_info.size() - 1].id;
            } else {
                square_[min(start_of_the_region.first, start_of_the_region.first) + j][min(start_of_the_region.second, start_of_the_region.second) + i] = field_type;
                if(field_type == 3) entrances[min(start_of_the_region.first, start_of_the_region.first) + j][min(start_of_the_region.second, start_of_the_region.second) + i] = entrance_info[entrance_info.size() - 1].id;
            }
        }
    }
    return square_;
}

void MazeGenerator::Visualizer(vector<vector<int>> square_) {
    // I found stuff that looks fine to my opinion
    // 0x02500 +=
    // 2, 3, 5, 7, 15, 19, 23, 27, 32, 40, 48, 56, 66, 81  - 108, 136, 137, 167, 169, 178, 179
    // Example:
    // printwc(0x02502);
    vector<wchar_t> uni_symbols = VisualizerGetReadySymbols(VisualizerGetReadyIds());
    /*read square and print stuff*/
}

vector <wchar_t > MazeGenerator::VisualizerGetReadySymbols(vector<int> ids_) {
    vector<wchar_t> uni_symbols;
    //starting point of interesting stuff
    wchar_t uni_symbol = 0x02500;
    for (int j = 0; j < ids_.size(); ++j) {
        uni_symbols.push_back(uni_symbol + j);
    }
    return  uni_symbols;
}

vector<vector<char>> MazeGenerator::VisualizerTakeIndexesReturnGraphics(vector<vector<int>> square_){
    vector<vector<char>> buf;

    map<int, wchar_t > uni_sym;
    /*
     * 1 = ─  5 = │  25 = ┌   33 = ┐  41 = └   49 = ┘
57 = ├ 73 = ┤ 89 = ┬  105 = ┴  121 = ┼
161 = ═ 163 = ║
165 = ╒ 167 = ╓
169 = ╔ 171 = ╕ 173 = ╖ 175 = ╗ 177 = ╘
179 = ╙ 181 = ╚ 183 = ╛ 185 = ╜ 187 = ╝
189 = ╞ 191 = ╟ 193 = ╠ 195 = ╡ 197 = ╢
199 = ╣ 201 = ╤ 203 = ╥ 205 = ╦ 207 = ╧
209 = ╨ 211 = ╩ 213 = ╪ 215 = ╫ 217 = ╬
     *
     * uni_sym.insert(0, 0x02500 + );
    uni_sym.insert(1, 0x02500 + );
    uni_sym.insert(4, 0x02500 + );
    uni_sym.insert(10, 0x02500 + );
    uni_sym.insert(11, 0x02500 + );
    uni_sym.insert(14, 0x02500 + );
    uni_sym.insert(40, 0x02500 + );
    uni_sym.insert(41, 0x02500 + );
    uni_sym.insert(44, 0x02500 + );
    uni_sym.insert(100, 0x02500 + );
    uni_sym.insert(101, 0x02500 + );
    uni_sym.insert(104, 0x02500 + );
    uni_sym.insert(110, 0x02500 + );
    uni_sym.insert(111, 0x02500 + );
    uni_sym.insert(114, 0x02500 + );
    uni_sym.insert(140, 0x02500 + );
    uni_sym.insert(141, 0x02500 + );
    uni_sym.insert(144, 0x02500 + );
    uni_sym.insert(400, 0x02500 + );
    uni_sym.insert(401, 0x02500 + );
    uni_sym.insert(404, 0x02500 + );
    uni_sym.insert(410, 0x02500 + );
    uni_sym.insert(411, 0x02500 + );
    uni_sym.insert(414, 0x02500 + );
    uni_sym.insert(440, 0x02500 + );
    uni_sym.insert(441, 0x02500 + );
    uni_sym.insert(444, 0x02500 + );
    uni_sym.insert(1000, 0x02500 + );
    uni_sym.insert(1001, 0x02500 + );
    uni_sym.insert(1004, 0x02500 + );
    uni_sym.insert(1010, 0x02500 + );
    uni_sym.insert(1011, 0x02500 + );
    uni_sym.insert(1014, 0x02500 + );
    uni_sym.insert(1040, 0x02500 + );
    uni_sym.insert(1041, 0x02500 + );
    uni_sym.insert(1044, 0x02500 + );
    uni_sym.insert(1100, 0x02500 + );
    uni_sym.insert(1101, 0x02500 + );
    uni_sym.insert(1104, 0x02500 + );
    uni_sym.insert(1110, 0x02500 + );
    uni_sym.insert(1111, 0x02500 + );
    uni_sym.insert(1114, 0x02500 + );
    uni_sym.insert(1140, 0x02500 + );
    uni_sym.insert(1141, 0x02500 + );
    uni_sym.insert(1144, 0x02500 + );
    uni_sym.insert(1400, 0x02500 + );
    uni_sym.insert(1401, 0x02500 + );
    uni_sym.insert(1404, 0x02500 + );
    uni_sym.insert(1410, 0x02500 + );
    uni_sym.insert(1411, 0x02500 + );
    uni_sym.insert(1414, 0x02500 + );
    uni_sym.insert(1440, 0x02500 + );
    uni_sym.insert(1441, 0x02500 + );
    uni_sym.insert(1444, 0x02500 + );
    uni_sym.insert(4000, 0x02500 + );
    uni_sym.insert(4001, 0x02500 + );
    uni_sym.insert(4004, 0x02500 + );
    uni_sym.insert(4010, 0x02500 + );
    uni_sym.insert(4011, 0x02500 + );
    uni_sym.insert(4014, 0x02500 + );
    uni_sym.insert(4040, 0x02500 + );
    uni_sym.insert(4041, 0x02500 + );
    uni_sym.insert(4044, 0x02500 + );
    uni_sym.insert(4100, 0x02500 + );
    uni_sym.insert(4101, 0x02500 + );
    uni_sym.insert(4104, 0x02500 + );
    uni_sym.insert(4110, 0x02500 + );
    uni_sym.insert(4111, 0x02500 + );
    uni_sym.insert(4114, 0x02500 + );
    uni_sym.insert(4140, 0x02500 + );
    uni_sym.insert(4141, 0x02500 + );
    uni_sym.insert(4144, 0x02500 + );
    uni_sym.insert(4400, 0x02500 + );
    uni_sym.insert(4401, 0x02500 + );
    uni_sym.insert(4404, 0x02500 + );
    uni_sym.insert(4410, 0x02500 + );
    uni_sym.insert(4411, 0x02500 + );
    uni_sym.insert(4414, 0x02500 + );
    uni_sym.insert(4440, 0x02500 + );
    uni_sym.insert(4441, 0x02500 + );
    uni_sym.insert(4444, 0x02500 + );*/

    for(int i = 0; i < square_[0].size(); i++){
        for(int j = 0; j < square_.size(); j++){
            if(square_[i][j] == 0){  // wall

            } else if(square_[i][j] == 4) {  // unbreakable wall

            } else if(square_[i][j] == 0) {  // empty

            }
        }
    }
}

vector<int> MazeGenerator::VisualizerGetReadyIds() {
    vector<int> uni_symbols_id = {2, 3, 5, 7, 15, 19, 23, 27, 32, 40, 48, 56, 66};// 136, 137, 167, 169, 178, 179};
    for (int i = 81; i < 109; ++i) {
        uni_symbols_id.push_back(i);
    }
    /*sorting vector*/

    uni_symbols_id.push_back(136); // after sorting delete
    uni_symbols_id.push_back(137);
    uni_symbols_id.push_back(167);
    uni_symbols_id.push_back(169);
    uni_symbols_id.push_back(178);
    uni_symbols_id.push_back(179);
    return uni_symbols_id;
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

pair<int, int> MazeGenerator::GetZeroOrderEntrancePos(vector<Entrance_info> entrance_info_, vector<vector<int>> entrances) {
    int zeroorderid;
    pair<int, int> result;
    for(int i = 0; i < entrance_info_.size(); i++){
        if(entrance_info_[i].order == 0) {
            zeroorderid = entrance_info_[i].id;
            break;
        }
    }
    for (int j = 0; j < entrances[0].size(); ++j) {
        for (int i = 0; i < entrances.size(); ++i) {
            if(entrances[j][i] == zeroorderid) {
                result = make_pair(j, i);
                break;
            }
        }
    }
    return result;
}

pair<int, int> MazeGenerator::GetNewRandPos(Random_Generator_ *Rand_gen, pair<int, int> starting_pos, vector<vector<int>> square_,
                                            vector<vector<int>> deadend_) {
    pair<int, int> result = starting_pos;
    int count;
    while(true){
        count++;
        result.first = Rand_gen->Rand(1, square_[0].size() - 2);
        result.second = Rand_gen->Rand(1, square_.size() - 2);
        if(square_[result.first][result.second] == 1 && deadend_[result.first][result.second] != 1) break;
        if(count >= square_[0].size() * square_.size() * 2) break;
    }
    return result;
}

/*Method which uses all the others and return field filled with corridors and walls :D*/
vector<vector<int>> MazeGenerator::Build_Labirinth(Random_Generator_ *Rand_gen, vector<vector<int>> square_) {
    square_ = LabyrinthMenu(square_);
    square = square_;
    bool issatisfying = false;
    while(!issatisfying){
        square_ = square;
        pair<int, int> pos = GetZeroOrderEntrancePos(entrance_info, entrances);
        pair<int, int> prev_pos;
        while(true){
            if(num_of_deadends == num_of_free_fields) break;
            prev_pos = pos;
            pos = Move(Rand_gen, pos.first, pos.second, square_);
            num_of_free_fields += max(abs(prev_pos.first - pos.first), abs(prev_pos.second - pos.second));
            if(pos == prev_pos){
                num_of_deadends++;
                deadend[pos.first][pos.second] = 1;
                if(num_of_deadends == num_of_free_fields) break;
                pos = GetNewRandPos(Rand_gen, pos, square_, deadend);
            }
        }
        /*Output function*/
        //Visualizer(square_);
        cout << "Do you satisfied with labirinth? 0/1 (Yes/No)\n";
        int issatisfying_i = IsNumber(issatisfying_i, 0, 1);
        if(issatisfying_i == 0) issatisfying = true;
    }
    num_of_deadends = 0;
    num_of_free_fields = 0;
    return square_;
}

