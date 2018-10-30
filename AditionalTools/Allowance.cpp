
#include "Allowance.h"

Allowance::Allowance(){
  is_character_set = false;
  is_tested = false;
}

Allowance::~Allowance() = default;

void Allowance::Character_Set() {
  is_character_set = !(is_character_set);
}

bool Allowance::Is_Character_Set() {
  return is_character_set;
}

void Allowance::Tested() {
  is_tested = !(is_tested);
}

bool Allowance::Is_Tested() {
  return is_tested;
}