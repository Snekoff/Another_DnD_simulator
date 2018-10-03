
#include "UsefulFunctions.h"
template<typename T>
T Correctness_of_input(T a, T lowerlimit, T higherlimit) {
  if (higherlimit == lowerlimit - 2) {
    while (a > lowerlimit) {
      std::cout << "Incorrect input." << std::endl;
      std::cout << "value must be equal or lower than " << lowerlimit << std::endl;
      a = IsNumber<T>(a, lowerlimit, higherlimit);
    }
  } else if (higherlimit == lowerlimit - 1) {
    while (a < lowerlimit) {
      std::cout << "Incorrect input." << std::endl;
      std::cout << "value must be equal or lower higher than " << higherlimit << std::endl;
      a = IsNumber<T>(a, lowerlimit, higherlimit);
    }
  } else {
    while (a < lowerlimit || a > higherlimit) {
      std::cout << "Incorrect input." << std::endl;
      std::cout << "value must be between " << lowerlimit << " and " << higherlimit << std::endl;
      a = IsNumber<T>(a, lowerlimit, higherlimit);
    }
  }
  return a;
}

Random_Generator_::Random_Generator_() = default;
Random_Generator_::~Random_Generator_() = default;
int Random_Generator_::Rand(int lowerlimit, int higherlimit) {
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> dist(lowerlimit, higherlimit);
  return dist(mt);
}

int Health_Level_Up(Random_Generator_ *Rand_gen, int health_dice, int ConModifier, int maxhealth) {
  std::cout <<
            "Character leveled up, your health increased, choose the way: roll dices(1) or take a middle(2)?"
            << std::endl;
  int roll_or_middle = 0;
  std::cin >> roll_or_middle;
  roll_or_middle = Correctness_of_input(roll_or_middle, 1, 2);
  if (roll_or_middle == 1) {
    int tHP = Rand_gen->Rand(1, health_dice);
    std::cout << "Rolled health + Constitution modifier:" << tHP + ConModifier << std::endl;
    maxhealth += tHP + ConModifier;
  }//roll dices f
  else {
    maxhealth += health_dice / 2 + 1;
    std::cout << "middle health = " << health_dice / 2 + 1 << std::endl;
  }//take middle
  return maxhealth;
}

template<typename T>
T IsNumber(T a, T lowerlimit, T higherlimit) {
  for (;;) {
    std::cout << "Input: ";
    if (std::cin >> a) {
      a = Correctness_of_input<T>(a, lowerlimit, higherlimit);
      break;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  return a;
}

