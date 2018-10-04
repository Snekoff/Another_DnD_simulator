
#include "Battleground.h"

Battleground::Battleground() {
  X = 4;
  Y = 4;
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

int Battleground::Get(int what) {
  if (what == 0) return X;
  else if (what == 1) return Y;
  else if (what == 2) return Z;
  return -1;
}

int Battleground::Shape() {
  cout << "Choose shape of the room\n1.Rectangle 2.Circle 3.~None\n";
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

void Battleground::Round_Shape() {
  //cout << "Control reach Round_Shape 0\n";
  int x_center = Round_Shape_Center(0), y_center = Round_Shape_Center(1);
  //cout << " x_center = "<< x_center << " y_center = " << y_center << endl;
  square[x_center][y_center] = 0;
  for (int i = 0; i < X; i++) {
    for(int j = 0; j < Y; j++){
      if(Distance_between(x_center,y_center,i,j) > radius) {
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

int Battleground::Distance_between(int form_X, int from_Y, int to_X, int to_Y) {
  /*double distance_d = sqrt(pow(abs(form_X - to_X),2) + pow(abs(from_Y - to_Y),2));*/ //Euclid's metrics
  int distance_i = 0;
  if(abs(form_X - to_X) != 0 && abs(from_Y - to_Y) != 0){
    for(int i = 0; i < min(abs(form_X - to_X),abs(from_Y - to_Y)); i++){
      if(i%2 == 0) distance_i++;
      else distance_i +=2;
    }
  }
  int difference = max(abs(form_X - to_X),abs(from_Y - to_Y)) - min(abs(form_X - to_X),abs(from_Y - to_Y));
  distance_i += difference;
  return distance_i;
}// D&D metrics is not that simple as Euclid's

void Battleground::square_Resize() {
  square.resize((unsigned) X);
  //occupation.resize((unsigned) X);
  for (int i = 0; i < X; i++) {
    //occupation.resize((unsigned) X);
    square[i].resize((unsigned) Y);
  }
}

void Battleground::Set() {

}

void Battleground::Load() {

}

void Battleground::Show_Shape() {
  //cout << "Control reach Show_Shape 1\n";
  vector<vector<string>> showing_field;
  showing_field.resize((unsigned)1 + X*kShow_Shape_String_spread_Multiplayer_x);
  //cout << "Control reach Show_Shape 2\n";
  for(int k = 0;k <1+X*kShow_Shape_String_spread_Multiplayer_x;k++){
    for(int k1 = 0;k1 <1 + Y*kShow_Shape_String_spread_Multiplayer_y;k1++){
      showing_field[k].push_back("#");
    }
  }
  //cout << "Control reach Show_Shape 3\n";
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
  //cout << "Control reach Show_Shape 4\n";
  string squares[1 + X*kShow_Shape_String_spread_Multiplayer_x];
  for(int k = 0;k <1 + X*kShow_Shape_String_spread_Multiplayer_x;k++){
    for(int k1 = 0;k1 <1 + Y*kShow_Shape_String_spread_Multiplayer_y;k1++){
      squares[k] += showing_field[k][k1];
    }
    cout << squares[k] <<endl;
  }
  //cout << "Control reach Show_Shape 5\n";
}