
#include <iostream>
#include <random>

int Correctness(int a, int lowerlimit, int higherlimit) {
  while (a < lowerlimit || a > higherlimit) {
    printf("%s \n", "Incorrect input.");
    std::cin >> a;
  }
  return a;
}

void LevelUp() {

}

int Random_Generator(int lowerlimit, int higherlimit){
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> dist(lowerlimit,higherlimit);
  return dist(mt);
}