
#include <iostream>
#include <random>

struct Existing_Types{
  int minHeight[39] = {6, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 3, 3, 3, 3, 5, 5, 5, 5, 5, 5, 3, 3, 3, 5, 5, 5, 6, 5, 5, 5, 5,
                       5, 5, 5, 5, 5, 5, 5};
  int maxHeight[39] = {6, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4, 4, 6, 6, 6, 6, 6, 6, 3, 3, 3, 6, 6, 6, 6, 6, 6, 6, 6,
                       6, 6, 6, 6, 6, 6, 6};
  int minWeight[39] = {10};
  int maxWeight[39] = {140};
  int minAge[39] = {3};
  int maxAge[39] = {120};//
  std::string item[9] = {"equipment","potions","food","ammo_holder","shield","weapon","armor","ammo","usable"};
  int race_ability_bonus[39][6] =
      {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
};

int Correctness(int a, int lowerlimit, int higherlimit) {
  if(higherlimit == lowerlimit - 2){
    while(a > lowerlimit){
      printf("%s \n", "Incorrect input.");
      std::cin >> a;
    }
  }
  else if(higherlimit == lowerlimit - 1){
    while(a < lowerlimit){
      printf("%s \n", "Incorrect input.");
      std::cin >> a;
    }
  }
  else {
    while (a < lowerlimit || a > higherlimit) {
      printf("%s \n", "Incorrect input.");
      std::cin >> a;
    }
  }
  return a;
}

int Random_Generator(int lowerlimit, int higherlimit){
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> dist(lowerlimit,higherlimit);
  return dist(mt);
}

int Health_Level_Up(int health_dice, int ConModifier, int maxhealth){
  printf("%s \n",
         "Character leveled up, your health increased, choose the way: roll dices(1) or take a middle(2)?");
  int roll_or_middle = 0;
  roll_or_middle = Correctness(roll_or_middle,1,2);
  if (roll_or_middle == 1) {
    int tHP = Random_Generator(1,health_dice);
    printf("%s %d \n", "Rolled health + Constitution modifier:", tHP + ConModifier);
    maxhealth += tHP + ConModifier;
  }//roll dices f
  else {
    maxhealth += health_dice / 2 + 1;
  }//take middle
  return maxhealth;
}