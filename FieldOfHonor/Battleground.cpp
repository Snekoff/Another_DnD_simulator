
#include "Battleground.h"

Battleground::Battleground() {
  X = 10;
  Y = 10;
  Z = 4;
  square_Resize();
  shape = 0;
}

Battleground::Battleground(int x_, int y_, int z_) {
  x_ = Correctness_of_input<int>(x_, 0, -1);
  y_ = Correctness_of_input<int>(y_, 0, -1);
  z_ = Correctness_of_input<int>(z_, 0, -1);
  X = x_;
  Y = y_;
  Z = z_;
  square_Resize();
  shape = 0;
  radius = 0;
  X_Limit = X;
  Y_Limit = Y;
  Z_Limit = Z;
  shape = Shape();
}

Battleground::~Battleground() = default;

int Battleground::GetInt(int what) {
  if (what == 0) return X;
  else if (what == 1) return Y;
  else if (what == 2) return Z;
  return -1;
}

vector<vector<int>> Battleground::GetField() {
  return square;
}

int Battleground::Shape() {
  cout << "Choose shape of the room\n";
  Exsisting_Fields E_F;
  for(int i = 0; i < kShapes_NUM;i++){
    cout << i+1 << ". " << E_F.shape_s[i] << endl;
  }
  shape = IsNumber<int>(shape, 1, kShapes_NUM);
  if (shape == 1) {
    //cout << "Control reach 0\n";
    cout << "insert limits for X, Y, Z\n";
    cout << "Up to values: " << X << ", " << Y << ", " << Z << endl;
    X_Limit = IsNumber<int>(X_Limit,1,X);
    Y_Limit = IsNumber<int>(Y_Limit,1,Y);
    Z_Limit = IsNumber<int>(Z_Limit,1,Z);
    cout << endl;
    Rectangle_Shape();
  } else if (shape == 2) {
    //cout << "Control reach 1\n";
    int radius_limit = 0;
    if(min(X,Y)%2 == 0) radius_limit = min(X,Y)/2 - 1;
    else radius_limit = min(X,Y)/2;
    cout << "Insert Radius equal or lower than " << radius_limit << endl;
    radius = IsNumber<int>(radius,1,radius_limit);
    Round_Shape();
  }
  Show_Shape();
  return shape;
}

void Battleground::Rectangle_Shape() {
  //cout << "Control reach Rectangle Shape 0\n";
for(int i = X-1; i != X_Limit - 1; i--){
  for(int j = 0; j < Y ;j++){
    square[i][j] = 1;
  }
}
  //cout << "Control reach Rectangle Shape 1\n";
  for(int i = Y-1; i != Y_Limit - 1; i--){
    for(int j = 0; j < X;j++){
      square[j][i] = 1;
    }
  }
}

void Battleground::Round_Shape() { ;
  int x_center = Round_Shape_Center(0), y_center = Round_Shape_Center(1);
  square[x_center][y_center] = 0;
  for (int i = 0; i < X; i++) {
    for(int j = 0; j < Y; j++){
      if(Distance_In_Moves(x_center,y_center,i,j) > radius) {
        square[i][j] = 1;
        //cout << "i = " << i << " j = " << j << endl;
      }
      else square[i][j] = 0;// high obstacle
    }
  }
}

int Battleground::Round_Shape_Center(int what_to_show_X_or_Y){
  int x_center = 0, y_center = 0;
  if (X % 2 == 0) {
    if (Y % 2 == 0) {
      x_center = X / 2 - 1;
      y_center = Y / 2 - 1;
    } else {
      x_center = X / 2 - 1;
      y_center = Y / 2;
    }
  } else {
    if (Y % 2 == 0) {
      x_center = X / 2;
      y_center = Y / 2 - 1;
    } else {
      x_center = X / 2;
      y_center = Y / 2;
    }
  }
  if(what_to_show_X_or_Y == 0) return x_center;
  else if(what_to_show_X_or_Y == 1) return y_center;
  return -1;
}
// D&D metrics is not that simple as Euclid's
int Battleground::Distance_In_Moves(int from_X, int from_Y, int to_X, int to_Y) {
  /*double distance_d = sqrt(pow(abs(from_X - to_X),2) + pow(abs(from_Y - to_Y),2));*/ //Euclid's metrics
  int distance_i = 0;
  int C_X = from_X,C_Y = from_Y;
  if(abs(from_X - to_X) != 0 && abs(from_Y - to_Y) != 0){
    /*for(int i = 0; i < min(abs(from_X - to_X),abs(from_Y - to_Y)); i++){
      if(i%2 == 0) distance_i++;
      else distance_i +=2;
    }*/
    int iter_A = max(abs(abs(from_X) - abs(to_X)),abs(abs(from_Y) - abs(to_Y)));
    int iter_B = min(abs(abs(from_X) - abs(to_X)),abs(abs(from_Y) - abs(to_Y)));
    int it_B = 1;
    int direction_X = 1,direction_Y = 1;
    if(from_X - to_X > 0) direction_X = -1;
    if(from_Y - to_Y > 0) direction_Y = -1;
    while (iter_A != 0){
      int move_length;
      while(iter_B != 0){
        if(it_B % 2 == 0) move_length = 2;
        else move_length = 1;
        C_X += direction_X;
        C_Y += direction_Y;
        move_length *= IfHardTerrain(C_X,C_Y);
        it_B++;
        distance_i += move_length;
        iter_B--;
        iter_A--;
      }
      if(iter_A == 0) break;
      move_length = 1;
      if(C_X == to_X && C_Y != to_Y) C_Y += direction_Y;
      else if(C_X != to_X && C_Y == to_Y) C_X += direction_X;
      move_length *= IfHardTerrain(C_X,C_Y);
      distance_i += move_length;
      iter_A--;
    }
  }
  int difference = max(abs(C_X - to_X),abs(C_Y - to_Y)) ;
  distance_i += difference;
  return distance_i;
}
// some geometry here
double Battleground::Distance(int from_X, int from_Y, int to_X, int to_Y) {
  double distance_d = sqrt(pow(abs(from_X - to_X),2) + pow(abs(from_Y - to_Y),2));
  return distance_d;
}
// no geometry here
int Battleground::Distance_Rounded(int from_X, int from_Y, int to_X, int to_Y) {
  int distance_i = 0;
  double distance_d = Distance(from_X,from_Y,to_X,to_Y);
  distance_i = (int)distance_d;
  if(distance_d - (double)distance_i > 0.5) distance_i++;
  return distance_i;
}

int Battleground::IfHardTerrain(int X, int Y) {
  if(square[X][Y] == 4 || square[X][Y] == 5 || square[X][Y] == 10) return 2;
  else return 1;
}
// angle [0,90)
double Battleground::Angle_Between(int from_X, int from_Y, int to_X, int to_Y) {
  //lets add point C(from_X,to_Y) to have right triangle
  //A(from_X,from_Y)
  //B(to_X,to_Y)
  //AC is perpendicular to CB
  double angle;
  int C_X = from_X, C_Y = to_Y;
  double DistAB = Distance(from_X, from_Y, to_X, to_Y);
  double DistCB = Distance(C_X, C_Y, to_X, to_Y);
  if (DistAB != DistCB) {
    angle = asin(DistCB / DistAB);
  } else angle = 0;
  return angle;
}

void Battleground::square_Resize() {
  square.resize((unsigned) X);
  in_square.resize((unsigned) X);
  for (int i = 0; i < X; i++) {
    in_square.resize((unsigned) X);
    square[i].resize((unsigned) Y);
  }
}

void Battleground::Set(int what, int value) {
  if (what == 0) X = value;
  else if (what == 1) Y = value;
  else if (what == 2) Z = value;
  else if (what == 3) radius = value;
  else if(what == 4) X_Limit = value;
  else if(what == 5) Y_Limit = value;
  else if(what == 6) Z_Limit = value;
  else if(what == 7) shape = value;
}

void Battleground::Load() {

}

void Battleground::Show_Shape() {
  //cout << "Control reach Show_Shape 1\n";
  vector<vector<string>> showing_field;
  showing_field.resize((unsigned)1 + X*kShow_Shape_String_spread_Multiplayer_x);
  for(int k = 0;k <1+X*kShow_Shape_String_spread_Multiplayer_x;k++){
    for(int k1 = 0;k1 <1 + Y*kShow_Shape_String_spread_Multiplayer_y;k1++){
      showing_field[k].push_back("#");
    }
  }
  for(int i = 0;i < X;i++){
    for(int j = 0;j < Y;j++){
      if(square[i][j] == 0){
        for(int n = i*kShow_Shape_String_spread_Multiplayer_x + 1; n < (i+1)*kShow_Shape_String_spread_Multiplayer_x ;n++){
          for(int m = j*kShow_Shape_String_spread_Multiplayer_y + 1; m < (j+1)*kShow_Shape_String_spread_Multiplayer_y ;m++){
            showing_field[n][m] = " ";
          }
        }
      }
    }
  }
  string squares[1 + X*kShow_Shape_String_spread_Multiplayer_x];
  for(int k = 0;k <1 + X*kShow_Shape_String_spread_Multiplayer_x;k++){
    for(int k1 = 0;k1 <1 + Y*kShow_Shape_String_spread_Multiplayer_y;k1++){
      squares[k] += showing_field[k][k1];
    }
    cout << squares[k] <<endl;
  }
  //cout << "Control reach Show_Shape 5\n";
}