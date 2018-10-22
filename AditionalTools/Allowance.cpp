
#include "Allowance.h"

Allowance::Allowance() = default;

Allowance::~Allowance() = default;

void Allowance::Character_Set() {
  if (is_character_set) is_character_set = false;
  else is_character_set = true;
}

bool Allowance::Is_Character_Set() {
  return is_character_set;
}

void Allowance::Tested() {
  if (is_tested) is_tested = false;
  else is_tested = true;
}

bool Allowance::Is_Tested() {
  return is_tested;
}