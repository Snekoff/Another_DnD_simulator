cmake_minimum_required(VERSION 3.14)
project(Another_DnD_simulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        Another_DnD_simulator main.cpp character/character.cpp character/race.cpp
        skills_spells_and_feats_/skills_and_spells.cpp character/common_functions.cpp "items/item.cpp"
        "items/item.h" "items/items_factory.h" character/common_functions.h
        skills_spells_and_feats_/skills_and_spells.h character/race.h character/character.h character/class.cpp
        character/class.h game_of_imagination.cpp game_of_imagination.h json_parse_by_nlohmann/json.hpp
        local_map/battleground.cpp local_map/battleground.h monsters/monster.cpp monsters/monster.h
        aditional_tools/allowance.cpp aditional_tools/allowance.h local_map/effect.cpp local_map/effect.h
        monsters/creature.cpp local_map/maze_generator.cpp local_map/maze_generator.h local_map/field_stuff.h local_map/unicode_console_output.cpp local_map/unicode_console_output.h local_map/local_map_user_usage.cpp local_map/local_map_user_usage.h)