
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

int Health_Level_Up(int health_dice, int ConModifier){
  printf("%s \n",
         "Character leveled up, your health increased, choose the way: roll dices(1) or take a middle(2)?");
  int roll_or_middle = 0;
  roll_or_middle = Correctness(roll_or_middle,1,2);
  if (roll_or_middle == 1) {
    int tHP = Random_Generator(1,health_dice);
    printf("%s %d \n", "Rolled health + Constitution modifier:", tHP + ConModifier);
    maxhealth += tHP + ConModifier;
    health = maxhealth;
  }//roll dices f
  else {
    maxhealth += health_dice / 2 + 1;
    health = maxhealth;
  }//take middle
}