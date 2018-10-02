
#include "Battleground.h"

Battleground::Battleground() {
  X = 4;
  Y = 4;
  Z = 4;
  square_Resize();
}

Battleground::Battleground(short x_, short y_, short z_) {
  x_ = Correctness_of_input<short>(x_,0,-1);
  y_ = Correctness_of_input<short>(y_,0,-1);
  z_ = Correctness_of_input<short>(z_,0,-1);
  X = x_;
  Y = y_;
  Z = z_;
  square_Resize();
  Shape();
}

Battleground::~Battleground() = default;

int Battleground::Get(int what) {
if(what == 0) return X;
else if(what == 1) return Y;
else if(what == 2) return Z;
return -52;
}

int Battleground::Shape() {

}

void Battleground::square_Resize() {
  square.resize((unsigned)X);
  for(short i = 0; i < X;i++){
    square[i].resize((unsigned)Y);
  }
}

void Battleground::Set() {

}

void Battleground::Load() {

}