
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
  Shape();
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
    cout << "insert limits for X, Y, Z\n";
    X_Limit = IsNumber<int>(X_Limit,1,X);
    Y_Limit = IsNumber<int>(Y_Limit,1,Y);
    Z_Limit = IsNumber<int>(Z_Limit,1,Z);
    Rectangle_Shape();
  } else if (shape == 2) {
    int radius_limit = 0;
    if(min(X,Y)%2 == 0) radius_limit = min(X,Y)/2 - 1;
    else radius_limit = min(X,Y)/2;
    cout << "Insert Radius equal or lower than " << radius_limit << endl;
    radius = IsNumber<int>(radius,1,radius_limit);
    Round_Shape();
  }
  return shape;
}

void Battleground::Rectangle_Shape() {
for(int i = X; i != X_Limit; i--){
  for(int j = 0; j < Y ;j++){
    square[i][j] = 1;
  }
}
  for(int i = Y; i != Y_Limit; i--){
    for(int j = 0; j < X;j++){
      square[j][i] = 1;
    }
  }
}

void Battleground::Round_Shape() {
  int x_center = Round_Shape_Center(0), y_center = Round_Shape_Center(1);
  square[x_center][y_center] = 2;
  for (int i = 0; i < X; i++) {
    for(int j = 0; j < Y; j++){
      if(Distance_between(x_center,y_center,i,j) > radius) square[i][j] = 1;
      else square[i][j] = 2;// high obstacle
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
  /*double distance_d = sqrt(pow(abs(form_X - to_X),2) + pow(abs(from_Y - to_Y),2));*/ //Euclid metrics
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
}

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