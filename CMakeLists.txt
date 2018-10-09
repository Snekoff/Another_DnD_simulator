cmake_minimum_required(VERSION 3.12)
project(Another_DnD_simulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(Another_DnD_simulator main.cpp Character/character.cpp Character/Race.cpp Skills_Spells_and_Feats_/Skills_and_Spells.cpp Character/UsefulFunctions.cpp "Inventory(Item)/Item.cpp" "Inventory(Item)/Item.h" "Inventory(Item)/Items_Factory.h" Character/UsefulFunctions.h Skills_Spells_and_Feats_/Skills_and_Spells.h Character/Race.h Character/character.h Character/Classes.cpp Character/Classes.h GameOfImagination.cpp GameOfImagination.h "json_nlohmann/single_include/nlohmann/json.hpp" FieldOfHonor/Battleground.cpp FieldOfHonor/Battleground.h Monsters/Monster.cpp Monsters/Monster.h Monsters/Creature.h gtest/googletest/src/gtest-all.cc gtest/googlemock/src/gmock-all.cc)