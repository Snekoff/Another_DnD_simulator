
#include "UsefulFunctions.h"
template<typename T>
T Correctness_of_input(T a, T lower_limit, T higher_limit) {
  if (higher_limit == lower_limit - 1) {
    while (a < lower_limit) {
      std::cout << "Incorrect input." << std::endl;
      std::cout << "value must be equal or higher than " << lower_limit << std::endl;
      a = IsNumber<T>(a, lower_limit, higher_limit);
    }
  } else if (higher_limit < lower_limit) {
    while (a > lower_limit) {
      std::cout << "Incorrect input." << std::endl;
      std::cout << "value must be equal or lower than " << lower_limit << std::endl;
      a = IsNumber<T>(a, lower_limit, higher_limit);
    }
  } else {
    while (a < lower_limit || a > higher_limit) {
      std::cout << "Incorrect input." << std::endl;
      std::cout << "value must be between " << lower_limit << " and " << higher_limit << std::endl;
      a = IsNumber<T>(a, lower_limit, higher_limit);
    }
  }
  return a;
}

Random_Generator_::Random_Generator_() = default;
Random_Generator_::~Random_Generator_() = default;
int Random_Generator_::Rand(int lower_limit, int higher_limit) {
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> dist(lower_limit, higher_limit);
  return dist(mt);
}

int Health_Level_Up(Random_Generator_ *Rand_gen, int health_dice, int ConModifier, int maxHealth) {
  std::cout <<
            "Character leveled up, your health increased, choose the way: roll dices(1) or take a middle(2)?"
            << std::endl;
  int roll_or_middle = 0;
  std::cin >> roll_or_middle;
  roll_or_middle = Correctness_of_input(roll_or_middle, 1, 2);
  if (roll_or_middle == 1) {
    int tHP = Rand_gen->Rand(1, health_dice);
    std::cout << "Rolled health + Constitution modifier = " << tHP + ConModifier << std::endl;
    maxHealth += tHP + ConModifier;
  }
  else {
    maxHealth += health_dice / 2 + 1;
    std::cout << "Middle health = " << health_dice / 2 + 1 << std::endl;
  }
  return maxHealth;
}

template<typename T>
T IsNumber(T a, T lower_limit, T higher_limit) {
  for (;;) {
    std::cout << "Input: ";
    if (std::cin >> a) {
      a = Correctness_of_input<T>(a, lower_limit, higher_limit);
      break;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  return a;
}

