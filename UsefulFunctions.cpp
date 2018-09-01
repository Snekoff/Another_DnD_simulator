
#include <iostream>

int Correctness(int a, int lowerlimit, int higherlimit) {
  while (a < lowerlimit || a > higherlimit) {
    printf("%s \n", "Incorrect input.");
    std::cin >> a;
  }
  return a;
}

void LevelUp() {

}
