#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <fstream>
#include <string>
#include <vector>
#include "../gtest/googletest/include/gtest/gtest.h"
#include "../gtest/googlemock/include/gmock/gmock.h"
#include "../json_parse_by_nlohmann/json.hpp"
#include "../Skills_Spells_and_Feats_/Skills_and_Spells.h"
#ifndef ANOTHER_DND_SIMULATOR_ITEM_H
#define ANOTHER_DND_SIMULATOR_ITEM_H

const int kElements_Num = 6;
const int kWeapon_NUM = 29;
const int kWeapon_Parameters_Num = 5;
const int kRanged_Weapon_NUM = 9;
const int kRanged_Weapon_Parameters_Num = 7;
const int kAmmo_NUM = 4;
const int kAmmo_Parameters_Num = 4;
const int kArmor_NUM = 12;
const int kArmor_Parameters_Num = 5;
const int kGoods_NUM = 80;
const int kGoods_Parameters_Num = 3;
const int kSpellCastingFocus_NUM = 12;
const int kSpellCastingFocus_Parameters_NUM = 2;
const int kFocus_Types_NUM = 3;
const int kShield_NUM = 1;
const int kShield_Parameters_NUM = 3;
const int kRing_NUM = 1;
const int kRing_Parameters_NUM = 2;
const int kPotion_NUM = 1;
const int kPotion_Parameters_NUM = 5;
const int kItems_Without_JSON_NUM = kWeapon_NUM + kRanged_Weapon_NUM + kAmmo_NUM + kArmor_NUM + kGoods_NUM
    + kSpellCastingFocus_NUM + kShield_NUM + kRing_NUM + kPotion_NUM;
const int kG_NUM = 125;
const int kM_NUM = 52;
const int kSHP_NUM = 7;
const int kAT_NUM = 17;
const int k$_NUM = 111;
const int kSCF_NUM = 7;
const int kS_NUM = 8;
const int kHA_NUM = 9;
const int kINS_NUM = 33;
const int kRG_NUM = 39;
const int kTAH_NUM = 9;
const int kMA_NUM = 13;
const int kEXP_NUM = 7;
const int kP_NUM = 47;
const int kMNT_NUM = 9;
const int kVEH_NUM = 6;
const int kTG_NUM = 23;
const int kGS_NUM = 4;
const int kEM_NUM = 5;
const int kT_NUM = 7;
const int kLA_NUM = 1;
const int kOTH_NUM = 2;
const int kRD_NUM = 12;
const int kR_NUM = 4;
const int kSC_NUM = 18;
const int kA_NUM = 1;
const int kWD_NUM = 23;
const int kGV_NUM = 0;
const int kAll_Num = kWeapon_NUM + kRanged_Weapon_NUM + kAmmo_NUM + kArmor_NUM + kGoods_NUM
    + kSpellCastingFocus_NUM + kShield_NUM + kRing_NUM + kPotion_NUM + kG_NUM
    + kM_NUM + kSHP_NUM + kAT_NUM + k$_NUM + kSCF_NUM + kS_NUM + kHA_NUM + kINS_NUM + kRG_NUM + kTAH_NUM
    + kMA_NUM + kEXP_NUM + kP_NUM + kMNT_NUM + kVEH_NUM + kTG_NUM + kGS_NUM + kEM_NUM + kT_NUM + kLA_NUM
    + kOTH_NUM + kRD_NUM + kR_NUM + kSC_NUM + kA_NUM + kWD_NUM + kGV_NUM;
const int kItem_For_Sale_Types = 23;
const int kDamage_Types = 6;// bludgeoning not included and so on
const int kArmor_types = 3;
const int kClass_NuM = 12;
const int kSpellCastingFocus_Types = 3;

struct Existing_Items {
  std::string elements[kElements_Num] = {"no", "acid", "lightning", "fire", "cold", "poison"};
  std::string Weapon_s[kWeapon_NUM] = {"Club", "Dagger", "Greatclub", "Handaxe", "Javelin", "Light_hammer",
                                       "Mace", "Quarterstaff", "Sickle", "Spear", "Unarmed_strike", "Battleaxe",
                                       "Flail", "Glaive",
                                       "Greataxe", "Greatsword", "Halberd", "Lance", "Longsword", "Maul",
                                       "Morningstar", "Pike", "Rapier", "Scimitar", "Shortsword", "Trident",
                                       "War_pick", "Warhammer", "Whip"};
  //cost(copper), num_of_dices, damage_dice, weight, type_of_elemental_damage
  int Weapon_i[kWeapon_NUM][kWeapon_Parameters_Num] =
      {{10, 1, 4, 2, 0}, {200, 1, 4, 2, 0}, {20, 1, 8, 10, 0}, {500, 1, 6, 2, 0}, {50, 1, 6, 2, 0},
       {200, 1, 4, 2, 0}, {500, 1, 6, 4, 0}, {20, 1, 6, 4, 0}, {100, 1, 4, 2, 0}, {100, 1, 6, 3, 0},
       {0, 1, 1, 0, 0}, {1000, 1, 8, 4, 0}, {1000, 1, 8, 2, 0}, {2000, 1, 10, 6, 0},
       {3000, 1, 12, 7, 0}, {5000, 2, 6, 6, 0}, {2000, 1, 10, 6, 0}, {1000, 1, 12, 6, 0},
       {1500, 1, 8, 3, 0}, {1000, 2, 6, 10, 0}, {1500, 1, 8, 4, 0}, {500, 1, 10, 18, 0},
       {2500, 1, 8, 2, 0}, {2500, 1, 6, 3, 0}, {1000, 1, 6, 2, 0}, {500, 1, 6, 4, 0},
       {500, 1, 8, 2, 0}, {1500, 1, 8, 2, 0}, {200, 1, 4, 3, 0}};
  std::string Ranged_Weapon_s[kRanged_Weapon_NUM] = {"Crossbow_light", "Dart", "Shortbow", "Sling", "Blowgun",
                                                     "Crossbow_hand", "Crossbow_heavy", "Longbow", "Net"};
  //cost(copper), num_of_dices, damage_dice, weight, type_of_elemental_damage , aiming_range, max_range
  int Ranged_Weapon_i[kRanged_Weapon_NUM][kRanged_Weapon_Parameters_Num] =
      {{2500, 1, 8, 5, 0, 80, 320}, {5, 1, 4, 0, 0, 20, 60}, {2500, 1, 6, 2, 0, 80, 320}, {10, 1, 4, 0, 0, 30, 120},
       {1000, 1, 1, 1, 0, 25, 100}, {7500, 1, 6, 3, 0, 30, 120}, {5000, 1, 10, 18, 0, 100, 400},
       {5000, 1, 8, 2, 0, 150, 600},
       {100, 0, 0, 3, 0, 5, 15}};
  std::string Ammo_s[kAmmo_NUM] = {"Arrows", "Blowgun_needles", "Crossbow_bolts", "Sling_bullets"};
  //cost, weight, ammo damage, element
  int Ammo_i[kAmmo_NUM][kAmmo_Parameters_Num] =
      {{1 * 100, 1, 0, 0}, {1 * 100, 1, 0, 0}, {1 * 100, 1, 0, 0}, {4, 1, 0, 0}};
  std::string Armor_s[kArmor_NUM] = {"Padded", "Leather", "Studded_leather",
                                     "Hide", "Chain_shirt", "Scale_mail", "Breastplate", "Half_plate",
                                     "Ring_mail", "Chain_mail", "Splint", "Plate"};
  //Cost , Type , Armor_Class , Strength_needed , weight
  int Armor_i[kArmor_NUM][kArmor_Parameters_Num] = {{500, 0, 11, 0, 8}, {1000, 0, 11, 0, 10}, {4500, 0, 12, 0, 13},
                                                    {1000, 1, 12, 0, 12}, {5000, 1, 13, 0, 20}, {5000, 1, 14, 0, 45},
                                                    {40000, 1, 14, 0, 20}, {75000, 1, 15, 0, 40},
                                                    {3000, 2, 14, 0, 40}, {7500, 2, 16, 13, 55}, {20000, 2, 17, 15, 60},
                                                    {150000, 2, 18, 15, 65}};
  // stealth_disadvantage
  bool Armor_b[kArmor_NUM] = {true, false, false,
                              false, false, true,
                              false, true,
                              true, true, true,
                              true};
  std::string Goods_s[kGoods_NUM] = {"Abacus",
                                     "Acid_vial", "Alchemists_fire_flask",
                                     "Antitoxin", "Backpack", "Ball_bearings", "Barrel", "Basket", "Bedroll", "Bell",
                                     "Blanket", "Block_and_tackle", "Book", "Bottle_glass", "Bucket", "Caltrops",
                                     "Candle", "Case_crossbow_bolt", "Case_map_or_scroll", "Chain", "Chalk", "Chest",
                                     "Climber`s_kit", "Clothes_common", "Clothes_costume", "Clothes_fine",
                                     "Clothes_traveler`s", "Component_pounch", "Crowbar", "Fishing_tackle",
                                     "Flask_or_tankard", "Grappling_hook", "Hammer", "Hammer_sledge", "Healer`s kit",
                                     "Holy_water", "Hourglass", "Hunting_trap", "Ink", "Ink_pen", "Jug_or_pitcher",
                                     "Ladder", "Lamp", "Lantern_bullseye", "Lantern_hooded", "Lock",
                                     "Magnifying_glass", "Manacles", "Mess_kit", "Oil", "Paper", "Parchment",
                                     "Perfume",
                                     "Pick_miner`s", "Piton", "Poison_basic", "Pole", "Pot_iron", "Pouch", "Quiver",
                                     "Ram_portable", "Rations", "Robes", "Rope_hempen", "Rope_silk", "Sack",
                                     "Scale_merchant`s", "Sealing_wax", "Shovel", "Signal_whistle",
                                     "Soap", "Spellbook", "Spikes_iron", "Spyglass", "Tent_two_person", "Tinderbox",
                                     "Torch", "Vial", "Waterskin", "Whetstone"};
  //cost, weight, is_obstacle,
  int Goods_i[kGoods_NUM][kGoods_Parameters_Num] = {{200, 2, 0},
                                                    {25 * 100, 1, 0}, {50 * 100, 1, 0},
                                                    {50 * 100, 0, 0}, {2 * 100, 5, 0}, {1 * 100, 2, 1},
                                                    {2 * 100, 70, 0}, {4 * 10, 2, 0},
                                                    {1 * 100, 7, 0}, {1 * 100, 0, 0},
                                                    {5 * 10, 3, 0}, {1 * 100, 5, 0}, {25 * 100, 5, 0},
                                                    {2 * 100, 2, 0}, {5 * 10, 2, 0},
                                                    {1 * 100, 2, 0},
                                                    {1 * 10, 0, 0}, {1 * 100, 1, 0}, {1 * 100, 1, 0},
                                                    {5 * 100, 10, 0}, {1 * 10, 0, 0},
                                                    {5 * 100, 25, 0},
                                                    {25 * 100, 12, 0}, {5 * 10, 3, 0}, {5 * 100, 4, 0},
                                                    {15 * 100, 6, 0},
                                                    {2 * 100, 4, 0}, {25 * 100, 2, 0}, {2 * 100, 4, 0},
                                                    {1 * 100, 4, 0},
                                                    {2, 1, 0}, {2 * 100, 4, 0}, {1 * 100, 3, 0}, {2 * 100, 10, 0},
                                                    {5 * 100, 3, 0},
                                                    {25 * 100, 1, 0}, {25 * 100, 1, 0}, {5 * 100, 25, 0},
                                                    {10 * 100, 0, 0}, {2, 0, 0},
                                                    {2, 4, 0},
                                                    {1 * 10, 25, 0}, {5 * 10, 1, 0}, {10 * 100, 2, 0},
                                                    {5 * 100, 2, 0}, {10 * 100, 1, 0},
                                                    {100 * 100, 0, 0}, {2 * 100, 6, 0}, {2 * 10, 1, 0},
                                                    {1 * 10, 1, 0}, {2 * 10, 0, 0},
                                                    {1 * 10, 0, 0}, {5 * 100, 0, 0},
                                                    {2 * 100, 10, 0}, {5, 1, 0}, {100 * 100, 0, 0}, {5, 7, 0},
                                                    {2 * 100, 10, 0},
                                                    {5 * 10, 1, 0}, {1 * 100, 1, 0},
                                                    {4 * 100, 35, 0}, {5 * 10, 2, 0}, {1 * 100, 4, 0},
                                                    {1 * 100, 10, 0}, {10 * 100, 5, 0},
                                                    {1, 1, 0},
                                                    {5 * 100, 3, 0}, {5 * 10, 0, 0}, {2 * 100, 5, 0}, {5, 0, 0},
                                                    {2, 0, 0}, {50 * 100, 3, 0}, {1 * 100, 5, 0}, {1000 * 100, 1, 0},
                                                    {2 * 100, 20, 0},
                                                    {5 * 10, 1, 0},
                                                    {1, 1, 0}, {1 * 100, 0, 0}, {2 * 10, 5, 0}, {1, 1, 0}};

  std::string SpellCastingFocus_types[kSpellCastingFocus_Types] = {"holy", "druid", "arcane"};
  std::string SpellCastingFocus_s[kSpellCastingFocus_NUM] =
      {"Crystal", "Orb", "Rod", "Staff", "Wand", "Spring_of_mistletoe", "Totem",
       "Wooden_staff", "Yew_wand", "Amulet", "Emblem", "Reliquary",
      };
  //cost, weight
  int SpellCastingFocus_i[kSpellCastingFocus_NUM][kSpellCastingFocus_Parameters_NUM] = {{1000, 1}, {2000, 3}, {1000, 2},
                                                                                        {500, 4}, {1000, 1}, {100},
                                                                                        {100, 0},
                                                                                        {500, 4}, {1000, 1}, {500, 1},
                                                                                        {500, 0},
                                                                                        {500, 2},
  };
  //arcane_focus, druidic_focus, holy_symbol;
  bool SpellCastingFocus_b[kSpellCastingFocus_NUM][kFocus_Types_NUM] =
      {{true, false, false}, {true, false, false}, {true, false, false},
       {true, false, false}, {true, false, false}, {false, true, false},
       {false, true, false},
       {false, true, false}, {false, true, false}, {false, false, true},
       {false, false, true},
       {false, false, true},
      };
  std::string Shield_s[kShield_NUM] = {"Shield"};
  //Cost , weight , Armor_Class
  int Shield_i[kShield_NUM][kShield_Parameters_NUM] = {{1000, 6, 2}};
  std::string Ring_s[kRing_NUM] = {"Signet_ring"};
  //cost, weight,
  int Ring_i[kRing_NUM][kRing_Parameters_NUM] = {{5 * 100, 0}};
  std::string Potion_s[kPotion_NUM] = {"Potion_of_healing"};
  //cost, weight, const healing, num of healing dices, healing dice
  int Potion_i[kPotion_NUM][kPotion_Parameters_NUM] = {{5000, 1, 2, 2, 4}};// 2d4+2

  std::string G_s[kG_NUM] =
      {"Abacus", "Acid (vial)", "Alchemist's Fire (flask)", "Antitoxin", "Assassin's Blood (Ingested)", "Backpack",
       "Ball Bearing", "Ball Bearings (Bag of 1,000)", "Barrel", "Basic Poison (vial)", "Basket", "Bedroll", "Bell",
       "Blanket", "Block and Tackle", "Book", "Bucket", "Bullseye Lantern", "Burglar's Pack",
       "Burnt Othur Fumes (Inhaled)", "Caltrops", "Caltrops (20)", "Candle", "Carrion Crawler Mucus (Contact)",
       "Chain (10 feet)", "Chalk (1 piece)", "Chest", "Climber's Kit", "Common Clothes", "Component Pouch",
       "Costume Clothes", "Crossbow Bolt Case", "Crowbar", "Dancing Monkey Fruit", "Diplomat's Pack",
       "Drow Poison (Injury)", "Dungeoneer's Pack", "Entertainer's Pack", "Essence of Ether (Inhaled)",
       "Explorer's Pack", "Fine Clothes", "Fishing Tackle", "Flask", "Glass Bottle", "Grappling Hook", "Hammer",
       "Healer's Kit", "Hempen Rope (50 feet)", "Holy Water (flask)", "Hooded Lantern", "Hourglass", "Hunting Trap",
       "Ink (1-ounce bottle)", "Ink Pen", "Insect Repellent (block of incense)",
       "Insect Repellent (greasy salve)", "Iron Pot", "Iron Spikes", "Iron Spikes (10)", "Jug", "Ladder (10-foot)",
       "Lamp", "Lock", "Magnifying Glass", "Malice (Inhaled)", "Manacles", "Map or Scroll Case",
       "Menga leaves (1 ounce)", "Merchant's Scale", "Mess Kit", "Midnight Tears (Ingested)", "Miner's Pick",
       "Monster Hunter's Pack", "Oil (flask)", "Oil of Taggit (Contact)", "Pale Tincture (Ingested)",
       "Paper (one sheet)", "Parchment (one sheet)", "Perfume (vial)", "Pitcher", "Piton", "Pole (10-foot)",
       "Portable Ram", "Pouch", "Priest's Pack", "Purple Worm Poison (Injury)", "Quiver", "Rain Catcher",
       "Rations (1 day)", "Robes", "Ryath Root", "Sack", "Scholar's Pack", "Sealing Wax", "Serpent Venom (Injury)",
       "Shovel", "Signal Whistle", "Signet Ring", "Silk Rope (50 feet)", "Sinda berries (10)", "Sledgehammer", "Soap",
       "Spellbook", "Spyglass", "Steel Mirror", "Tankard", "Tej", "Tinderbox", "Tome of Strahd", "Torch",
       "Torpor (Ingested)", "Traveler's Clothes", "Trinket (CoS)", "Trinket (EET)", "Trinket (PHB)",
       "Truth Serum (Ingested)", "Two-Person Tent", "Vial", "Waterskin", "Whetstone", "Wildroot", "Wukka Nut",
       "Wyvern Poison (Injury)", "Yahcha", "Zabou",};
  std::string M_s[kM_NUM] =
      {"Adventurer's Battleaxe", "Axe of the Dwarvish Lords", "Blackrazor", "Blood Spear", "Bookmark",
       "Dagger of Venom", "Dawnbringer", "Dragontooth Dagger", "Drown", "Dwarven Thrower", "Greater Silver Sword",
       "Gulthias Staff", "Gurt's Greataxe", "Hammer of Thunderbolts", "Hazirawn", "Ironfang", "Javelin of Backbiting",
       "Javelin of Lightning", "Korolnor Scepter", "Lightbringer", "Lost Sword", "Mace of Disruption",
       "Mace of Smiting", "Mace of Terror", "Mind Lash", "Moonblade", "Orcsplitter", "Reszur",
       "Saint Markovia's Thighbone", "Scimitar of Speed", "Shatterspike", "Spear of Backbiting",
       "Staff of the Forgotten One", "Sun Blade", "Sunsword", "Sword of Answering (Answerer)",
       "Sword of Answering (Back Talker)", "Sword of Answering (Concluder)", "Sword of Answering (Last Quip)",
       "Sword of Answering (Rebutter)", "Sword of Answering (Replier)", "Sword of Answering (Retorter)",
       "Sword of Answering (Scather)", "Sword of Answering (Squelcher)", "Sword of Kas", "Tinderstrike",
       "Trident of Fish Command", "Wave", "Waythe", "Whelm", "Windvane", "Azuredge",};
  std::string SHP_s[kSHP_NUM] = {"Airship", "Galley", "Keelboat", "Longship", "Rowboat", "Sailing Ship", "Warship",};
  std::string AT_s[kAT_NUM] =
      {"Alchemist's Supplies", "Brewer's Supplies", "Calligrapher's Supplies", "Carpenter's Tools",
       "Cartographer's Tools", "Cobbler's Tools", "Cook's Utensils", "Glassblower's Tools", "Jeweler's Tools",
       "Leatherworker's Tools", "Mason's Tools", "Painter's Supplies", "Potter's Tools", "Smith's Tools",
       "Tinker's Tools", "Weaver's Tools", "Woodcarver's Tools",};
  std::string $_s[k$_NUM] = {"Alexandrite", "Amber", "Amethyst", "Aquamarine", "Azurite", "Banded Agate",
                             "Bejeweled ivory drinking horn with gold filigree", "Black Opal", "Black Pearl",
                             "Black Sapphire", "Black velvet mask stitched with silver thread", "Bloodstone",
                             "Blue Quartz", "Blue Sapphire", "Blue Spinel",
                             "Bottle stopper cork embossed with gold leaf and set with amethysts",
                             "Box of turquoise animal figurines", "Brass mug with jade inlay", "Bronze crown",
                             "Carnelian", "Carved bone statuette",
                             "Carved harp of exotic wood with ivory inlay and zircon gems", "Carved ivory statuette",
                             "Ceremonial electrum dagger with a black pearl in the pommel", "Chalcedony", "Chrysoberyl",
                             "Chrysoprase", "Citrine", "Cloth-of-gold vestments", "Copper (cp)",
                             "Copper chalice with silver filigree", "Coral", "Diamond", "Electrum (ep)",
                             "Embroidered glove set with jewel chips",
                             "Embroidered silk and velvet mantle set with numerous moonstones",
                             "Embroidered silk handkerchief", "Emerald", "Eye Agate",
                             "Eye patch with a mock eye set in blue sapphire and moonstone",
                             "Fine gold chain set with a fire opal", "Fire Opal", "Garnet", "Gold (gp)",
                             "Gold bird cage with electrum filigree", "Gold circlet set with four aquamarines",
                             "Gold cup set with emeralds", "Gold dragon comb set with red garnets as eyes",
                             "Gold jewelry box with platinum filigree", "Gold locket with a painted portrait inside",
                             "Gold music box", "Gold ring set with bloodstones", "Hematite", "Jacinth", "Jade",
                             "Jade game board with solid gold playing pieces", "Jasper", "Jet", "Jeweled anklet",
                             "Jeweled gold crown", "Jeweled platinum ring", "Lapis Lazuli", "Large gold bracelet",
                             "Large well-made tapestry", "Malachite", "Moonstone", "Moss Agate",
                             "Necklace string of small pink pearls", "Obsidian",
                             "Obsidian statuette with gold fittings and inlay", "Old masterpiece painting", "Onyx",
                             "Opal", "Painted gold child's sarcophagus", "Painted gold war mask",
                             "Pair of engraved bone dice", "Pearl", "Peridot", "Platinum (pp)",
                             "Platinum bracelet set with a sapphire", "Quartz", "Rhodochrosite", "Ruby", "Sardonyx",
                             "Silk robe with gold embroidery", "Silver (sp)", "Silver and gold brooch",
                             "Silver chalice set with moonstones", "Silver ewer",
                             "Silver necklace with a gemstone pendant",
                             "Silver-plated steel longsword with jet set in hilt", "Small gold bracelet",
                             "Small gold idol", "Small gold statuette set with rubies",
                             "Small mirror set in a painted wooden frame", "Spinel", "Star rose quartz", "Star Ruby",
                             "Star Sapphire", "Tiger Eye", "Topaz", "Tourmaline", "Turquoise", "Yellow Sapphire",
                             "Zircon", "Nib", "Shard", "Toal", "Dragon", "Sun", "Harbor Moon",};
  std::string
      SCF_s[kSCF_NUM] = {"Amulet", "Emblem", "Reliquary", "Sprig of Mistletoe", "Totem", "Wooden Staff", "Yew Wand",};
  std::string S_s[kS_NUM] =
      {"Animated Shield", "Arrow-Catching Shield", "Sentinel Shield", "Shield of Expression", "Shield of Far Sight",
       "Shield of Missile Attraction", "Silver Dragon Shield +2", "Spellguard Shield",};
  std::string HA_s[kHA_NUM] =
      {"Armor of Invulnerability", "Armor of Vulnerability (Bludgeoning)", "Armor of Vulnerability (Piercing)",
       "Armor of Vulnerability (Slashing)", "Demon Armor", "Dwarven Plate", "Efreeti Chain",
       "Plate Armor of Etherealness", "Scorpion Armor",};
  std::string INS_s[kINS_NUM] =
      {"Bagpipes", "Birdpipes", "Drum", "Dulcimer", "Flute", "Glaur", "Hand Drum", "Horn", "Instrument of Illusions",
       "Instrument of Scribing", "Instrument of the Bards, Anstruth Harp", "Instrument of the Bards, Canaith Mandolin",
       "Instrument of the Bards, Cli Lyre", "Instrument of the Bards, Doss Lute",
       "Instrument of the Bards, Fochlucan Bandore", "Instrument of the Bards, Mac-Fuirmidh Cittern",
       "Instrument of the Bards, Ollamh Harp", "Longhorn", "Lute", "Lyre", "Pan Flute", "Pipes of Haunting",
       "Pipes of the Sewers", "Shawm", "Shawm", "Songhorn", "Tantan", "Thelarr", "Tocken", "Viol", "Wargong", "Yarting",
       "Zulkoon",};
  std::string RG_s[kRG_NUM] =
      {"Band of Loyalty", "Ring of Acid Resistance", "Ring of Air Elemental Command", "Ring of Animal Influence",
       "Ring of Cold Resistance", "Ring of Djinni Summoning", "Ring of Earth Elemental Command", "Ring of Evasion",
       "Ring of Feather Falling", "Ring of Fire Elemental Command", "Ring of Fire Resistance",
       "Ring of Force Resistance", "Ring of Free Action", "Ring of Invisibility", "Ring of Jumping",
       "Ring of Lightning Resistance", "Ring of Mind Shielding", "Ring of Necrotic Resistance",
       "Ring of Poison Resistance", "Ring of Protection", "Ring of Psychic Resistance", "Ring of Radiant Resistance",
       "Ring of Regeneration", "Ring of Shooting Stars", "Ring of Spell Storing", "Ring of Spell Turning",
       "Ring of Swimming", "Ring of Telekinesis", "Ring of the Ram", "Ring of Three Wishes",
       "Ring of Thunder Resistance", "Ring of Warmth", "Ring of Water Elemental Command", "Ring of Water Walking",
       "Ring of Winter", "Ring of X-ray Vision", "Rings of Shared Suffering", "Ring of Truth Telling",
       "Teleporter Ring",};
  std::string TAH_s[kTAH_NUM] =
      {"Barding", "Bit and bridle", "Exotic Saddle", "Feed (per day)", "Military Saddle", "Pack Saddle",
       "Riding Saddle", "Saddlebags", "Stabling (per day)",};
  std::string MA_s[kMA_NUM] =
      {"Black Dragon Scale Mail", "Blue Dragon Scale Mail", "Brass Dragon Scale Mail", "Bronze Dragon Scale Mail",
       "Copper Dragon Scale Mail", "Dragonguard", "Elven Chain", "Gold Dragon Scale Mail", "Green Dragon Scale Mail",
       "Red Dragon Scale Mail", "Silver Dragon Scale Mail", "Survival Mantle", "White Dragon Scale Mail",};
  std::string EXP_s[kEXP_NUM] =
      {"Bomb", "Dynamite (Stick)", "Fragmentation Grenade", "Grenade Launcher", "Gunpowder Horn", "Gunpowder Keg",
       "Smoke Grenade",};
  std::string P_s[kP_NUM] =
      {"Bottled Breath", "Elixir of Health", "Oil of Etherealness", "Oil of Sharpness", "Oil of Slipperiness",
       "Philter of Love", "Potion of Acid Resistance", "Potion of Animal Friendship", "Potion of Clairvoyance",
       "Potion of Climbing", "Potion of Cloud Giant Strength", "Potion of Cold Resistance", "Potion of Diminution",
       "Potion of Fire Breath", "Potion of Fire Giant Strength", "Potion of Fire Resistance", "Potion of Flying",
       "Potion of Force Resistance", "Potion of Frost Giant Strength", "Potion of Gaseous Form", "Potion of Giant Size",
       "Potion of Greater Healing", "Potion of Growth", "Potion of Healing", "Potion of Heroism",
       "Potion of Hill Giant Strength", "Potion of Invisibility", "Potion of Invulnerability",
       "Potion of Lightning Resistance", "Potion of Longevity", "Potion of Mind Control (beast)",
       "Potion of Mind Control (humanoid)", "Potion of Mind Control (monster)", "Potion of Mind Reading",
       "Potion of Necrotic Resistance", "Potion of Poison", "Potion of Poison Resistance",
       "Potion of Psychic Resistance", "Potion of Radiant Resistance", "Potion of Speed",
       "Potion of Stone Giant Strength", "Potion of Storm Giant Strength", "Potion of Superior Healing",
       "Potion of Supreme Healing", "Potion of Thunder Resistance", "Potion of Vitality", "Potion of Water Breathing",};
  std::string MNT_s[kMNT_NUM] =
      {"Camel", "Donkey", "Draft Horse", "Elephant", "Mastiff", "Mule", "Pony", "Riding Horse", "Warhorse",};
  std::string VEH_s[kVEH_NUM] = {"Canoe", "Carriage", "Cart", "Chariot", "Sled", "Wagon",};
  std::string TG_s[kTG_NUM] =
      {"Canvas (1 sq. yd.)", "Chicken", "Cinnamon", "Cloves", "Copper", "Cotton Cloth (1 sq. yd.)", "Cow", "Flour",
       "Ginger", "Goat", "Gold", "Iron", "Linen (1 sq. yd.)", "Ox", "Pepper", "Pig", "Platinum", "Saffron", "Salt",
       "Sheep", "Silk (1 sq. yd.)", "Silver", "Wheat",};
  std::string GS_s[kGS_NUM] = {"Dice Set", "Dragonchess Set", "Playing Card Set", "Three-Dragon Ante Set",};
  std::string EM_s[kEM_NUM] = {"Dimensional Seal", "Mabaran Resonator", "Master's Call", "Spell Sink", "Storm Sphere",};
  std::string T_s[kT_NUM] =
      {"Disguise Kit", "Forgery Kit", "Hacking Tools", "Herbalism Kit", "Navigator's Tools", "Poisoner's Kit",
       "Thieves' Tools",};
  std::string LA_s[kLA_NUM] = {"Glamoured Studded Leather",};
  std::string OTH_s[kOTH_NUM] = {"Green Copper Ewer", "Statuette of Saint Markovia",};
  std::string RD_s[kRD_NUM] =
      {"Immovable Rod", "Rod of Absorption", "Rod of Alertness", "Rod of Lordly Might", "Rod of Resurrection",
       "Rod of Rulership", "Rod of Security", "Rod of the Pact Keeper, (+1)", "Rod of the Pact Keeper (+2)",
       "Rod of the Pact Keeper (+3)", "Rod of the Vonindod", "Tentacle Rod",};
  std::string R_s[kR_NUM] = {"Oathbow", "Seeker Dart", "Storm Boomerang", "Oversized Longbow",};
  std::string SC_s[kSC_NUM] = {"Scroll of Protection from Aberrations", "Scroll of Protection from Beasts",
                               "Scroll of Protection from Celestials", "Scroll of Protection from Elementals",
                               "Scroll of Protection from Fey", "Scroll of Protection from Fiends",
                               "Scroll of Protection from Plants", "Scroll of Protection from Undead",
                               "Spell Scroll (1st Level)", "Spell Scroll (2nd Level)", "Spell Scroll (3rd Level)",
                               "Spell Scroll (4th Level)", "Spell Scroll (5th Level)", "Spell Scroll (6th Level)",
                               "Spell Scroll (7th Level)", "Spell Scroll (8th Level)", "Spell Scroll (9th Level)",
                               "Spell Scroll (Cantrip)",};
  std::string A_s[kA_NUM] = {"Unbreakable Arrow",};
  std::string WD_s[kWD_NUM] =
      {"Wand of Binding", "Wand of Conducting", "Wand of Enemy Detection", "Wand of Entangle", "Wand of Fear",
       "Wand of Fireballs", "Wand of Lightning Bolts", "Wand of Magic Detection", "Wand of Magic Missiles",
       "Wand of Orcus", "Wand of Paralysis", "Wand of Polymorph", "Wand of Pyrotechnics", "Wand of Scowls",
       "Wand of Secrets", "Wand of Smiles", "Wand of the War Mage (+1)", "Wand of the War Mage (+2)",
       "Wand of the War Mage (+3)", "Wand of Viscid Globs", "Wand of Web", "Wand of Winter", "Wand of Wonder",};
  //std::string GV_s[kGV_NUM] = {};

  std::string All_s[kAll_Num] = {
      "Club", "Dagger", "Greatclub", "Handaxe", "Javelin", "Light_hammer",
      "Mace", "Quarterstaff", "Sickle", "Spear", "Unarmed_strike", "Battleaxe",
      "Flail",
      "Glaive",
      "Greataxe", "Greatsword", "Halberd", "Lance", "Longsword", "Maul",
      "Morningstar", "Pike", "Rapier", "Scimitar", "Shortsword", "Trident",
      "War_pick", "Warhammer", "Whip",
      "Crossbow_light", "Dart", "Shortbow", "Sling", "Blowgun",
      "Crossbow_hand", "Crossbow_heavy", "Longbow", "Net",
      "Arrows", "Blowgun_needles", "Crossbow_bolts", "Sling_bullets",
      "Padded", "Leather", "Studded_leather",
      "Hide", "Chain_shirt", "Scale_mail", "Breastplate", "Half_plate",
      "Ring_mail", "Chain_mail", "Splint", "Plate",
      "Abacus",
      "Acid_vial", "Alchemists_fire_flask",
      "Antitoxin", "Backpack", "Ball_bearings", "Barrel", "Basket", "Bedroll",
      "Bell",
      "Blanket", "Block_and_tackle", "Book", "Bottle_glass", "Bucket",
      "Caltrops",
      "Candle", "Case_crossbow_bolt", "Case_map_or_scroll", "Chain", "Chalk",
      "Chest",
      "Climber`s_kit", "Clothes_common", "Clothes_costume", "Clothes_fine",
      "Clothes_traveler`s", "Component_pounch", "Crowbar", "Fishing_tackle",
      "Flask_or_tankard", "Grappling_hook", "Hammer", "Hammer_sledge",
      "Healer`s kit",
      "Holy_water", "Hourglass", "Hunting_trap", "Ink", "Ink_pen",
      "Jug_or_pitcher",
      "Ladder", "Lamp", "Lantern_bullseye", "Lantern_hooded", "Lock",
      "Magnifying_glass", "Manacles", "Mess_kit", "Oil", "Paper", "Parchment",
      "Perfume",
      "Pick_miner`s", "Piton", "Poison_basic", "Pole", "Pot_iron", "Pouch",
      "Quiver",
      "Ram_portable", "Rations", "Robes", "Rope_hempen", "Rope_silk", "Sack",
      "Scale_merchant`s", "Sealing_wax", "Shovel", "Signal_whistle",
      "Soap", "Spellbook", "Spikes_iron", "Spyglass", "Tent_two_person",
      "Tinderbox",
      "Torch", "Vial", "Waterskin", "Whetstone",
      "Crystal", "Orb", "Rod", "Staff", "Wand", "Spring_of_mistletoe", "Totem",
      "Wooden_staff", "Yew_wand", "Amulet", "Emblem", "Reliquary",
      "Shield", "Signet_ring", "Potion_of_healing",
      "Abacus", "Acid (vial)", "Alchemist's Fire (flask)", "Antitoxin", "Assassin's Blood (Ingested)", "Backpack",
      "Ball Bearing", "Ball Bearings (Bag of 1,000)", "Barrel", "Basic Poison (vial)", "Basket", "Bedroll", "Bell",
      "Blanket", "Block and Tackle", "Book", "Bucket", "Bullseye Lantern", "Burglar's Pack",
      "Burnt Othur Fumes (Inhaled)", "Caltrops", "Caltrops (20)", "Candle", "Carrion Crawler Mucus (Contact)",
      "Chain (10 feet)", "Chalk (1 piece)", "Chest", "Climber's Kit", "Common Clothes", "Component Pouch",
      "Costume Clothes", "Crossbow Bolt Case", "Crowbar", "Dancing Monkey Fruit", "Diplomat's Pack",
      "Drow Poison (Injury)", "Dungeoneer's Pack", "Entertainer's Pack", "Essence of Ether (Inhaled)",
      "Explorer's Pack", "Fine Clothes", "Fishing Tackle", "Flask", "Glass Bottle", "Grappling Hook", "Hammer",
      "Healer's Kit", "Hempen Rope (50 feet)", "Holy Water (flask)", "Hooded Lantern", "Hourglass", "Hunting Trap",
      "Ink (1-ounce bottle)", "Ink Pen", "Insect Repellent (block of incense)",
      "Insect Repellent (greasy salve)", "Iron Pot", "Iron Spikes", "Iron Spikes (10)", "Jug", "Ladder (10-foot)",
      "Lamp", "Lock", "Magnifying Glass", "Malice (Inhaled)", "Manacles", "Map or Scroll Case",
      "Menga leaves (1 ounce)", "Merchant's Scale", "Mess Kit", "Midnight Tears (Ingested)", "Miner's Pick",
      "Monster Hunter's Pack", "Oil (flask)", "Oil of Taggit (Contact)", "Pale Tincture (Ingested)",
      "Paper (one sheet)", "Parchment (one sheet)", "Perfume (vial)", "Pitcher", "Piton", "Pole (10-foot)",
      "Portable Ram", "Pouch", "Priest's Pack", "Purple Worm Poison (Injury)", "Quiver", "Rain Catcher",
      "Rations (1 day)", "Robes", "Ryath Root", "Sack", "Scholar's Pack", "Sealing Wax", "Serpent Venom (Injury)",
      "Shovel", "Signal Whistle", "Signet Ring", "Silk Rope (50 feet)", "Sinda berries (10)", "Sledgehammer", "Soap",
      "Spellbook", "Spyglass", "Steel Mirror", "Tankard", "Tej", "Tinderbox", "Tome of Strahd", "Torch",
      "Torpor (Ingested)", "Traveler's Clothes", "Trinket (CoS)", "Trinket (EET)", "Trinket (PHB)",
      "Truth Serum (Ingested)", "Two-Person Tent", "Vial", "Waterskin", "Whetstone", "Wildroot", "Wukka Nut",
      "Wyvern Poison (Injury)", "Yahcha", "Zabou",
      "Adventurer's Battleaxe", "Axe of the Dwarvish Lords", "Blackrazor", "Blood Spear", "Bookmark", "Dagger of Venom",
      "Dawnbringer", "Dragontooth Dagger", "Drown", "Dwarven Thrower", "Greater Silver Sword", "Gulthias Staff",
      "Gurt's Greataxe", "Hammer of Thunderbolts", "Hazirawn", "Ironfang", "Javelin of Backbiting",
      "Javelin of Lightning", "Korolnor Scepter", "Lightbringer", "Lost Sword", "Mace of Disruption", "Mace of Smiting",
      "Mace of Terror", "Mind Lash", "Moonblade", "Orcsplitter", "Reszur", "Saint Markovia's Thighbone",
      "Scimitar of Speed", "Shatterspike", "Spear of Backbiting", "Staff of the Forgotten One", "Sun Blade", "Sunsword",
      "Sword of Answering (Answerer)", "Sword of Answering (Back Talker)", "Sword of Answering (Concluder)",
      "Sword of Answering (Last Quip)", "Sword of Answering (Rebutter)", "Sword of Answering (Replier)",
      "Sword of Answering (Retorter)", "Sword of Answering (Scather)", "Sword of Answering (Squelcher)", "Sword of Kas",
      "Tinderstrike",
      "Trident of Fish Command", "Wave", "Waythe", "Whelm", "Windvane", "Azuredge",
      "Airship", "Galley", "Keelboat", "Longship", "Rowboat", "Sailing Ship", "Warship",
      "Alchemist's Supplies", "Brewer's Supplies", "Calligrapher's Supplies", "Carpenter's Tools",
      "Cartographer's Tools", "Cobbler's Tools", "Cook's Utensils", "Glassblower's Tools", "Jeweler's Tools",
      "Leatherworker's Tools", "Mason's Tools", "Painter's Supplies", "Potter's Tools", "Smith's Tools",
      "Tinker's Tools", "Weaver's Tools", "Woodcarver's Tools",
      "Alexandrite", "Amber", "Amethyst", "Aquamarine", "Azurite", "Banded Agate",
      "Bejeweled ivory drinking horn with gold filigree", "Black Opal", "Black Pearl", "Black Sapphire",
      "Black velvet mask stitched with silver thread", "Bloodstone", "Blue Quartz", "Blue Sapphire", "Blue Spinel",
      "Bottle stopper cork embossed with gold leaf and set with amethysts", "Box of turquoise animal figurines",
      "Brass mug with jade inlay", "Bronze crown", "Carnelian", "Carved bone statuette",
      "Carved harp of exotic wood with ivory inlay and zircon gems", "Carved ivory statuette",
      "Ceremonial electrum dagger with a black pearl in the pommel", "Chalcedony", "Chrysoberyl", "Chrysoprase",
      "Citrine", "Cloth-of-gold vestments", "Copper (cp)", "Copper chalice with silver filigree", "Coral", "Diamond",
      "Electrum (ep)", "Embroidered glove set with jewel chips",
      "Embroidered silk and velvet mantle set with numerous moonstones", "Embroidered silk handkerchief", "Emerald",
      "Eye Agate",
      "Eye patch with a mock eye set in blue sapphire and moonstone", "Fine gold chain set with a fire opal",
      "Fire Opal", "Garnet", "Gold (gp)", "Gold bird cage with electrum filigree",
      "Gold circlet set with four aquamarines", "Gold cup set with emeralds",
      "Gold dragon comb set with red garnets as eyes", "Gold jewelry box with platinum filigree",
      "Gold locket with a painted portrait inside", "Gold music box", "Gold ring set with bloodstones", "Hematite",
      "Jacinth", "Jade", "Jade game board with solid gold playing pieces", "Jasper", "Jet", "Jeweled anklet",
      "Jeweled gold crown", "Jeweled platinum ring", "Lapis Lazuli", "Large gold bracelet", "Large well-made tapestry",
      "Malachite", "Moonstone", "Moss Agate", "Necklace string of small pink pearls", "Obsidian",
      "Obsidian statuette with gold fittings and inlay", "Old masterpiece painting", "Onyx", "Opal",
      "Painted gold child's sarcophagus", "Painted gold war mask", "Pair of engraved bone dice", "Pearl", "Peridot",
      "Platinum (pp)",
      "Platinum bracelet set with a sapphire", "Quartz", "Rhodochrosite", "Ruby", "Sardonyx",
      "Silk robe with gold embroidery", "Silver (sp)", "Silver and gold brooch", "Silver chalice set with moonstones",
      "Silver ewer", "Silver necklace with a gemstone pendant", "Silver-plated steel longsword with jet set in hilt",
      "Small gold bracelet", "Small gold idol", "Small gold statuette set with rubies",
      "Small mirror set in a painted wooden frame", "Spinel", "Star rose quartz", "Star Ruby", "Star Sapphire",
      "Tiger Eye", "Topaz", "Tourmaline", "Turquoise", "Yellow Sapphire", "Zircon", "Nib", "Shard", "Toal", "Dragon",
      "Sun", "Harbor Moon",
      "Amulet", "Emblem", "Reliquary", "Sprig of Mistletoe", "Totem", "Wooden Staff", "Yew Wand",
      "Animated Shield", "Arrow-Catching Shield", "Sentinel Shield", "Shield of Expression", "Shield of Far Sight",
      "Shield of Missile Attraction", "Silver Dragon Shield +2", "Spellguard Shield",
      "Armor of Invulnerability", "Armor of Vulnerability (Bludgeoning)", "Armor of Vulnerability (Piercing)",
      "Armor of Vulnerability (Slashing)", "Demon Armor", "Dwarven Plate", "Efreeti Chain",
      "Plate Armor of Etherealness", "Scorpion Armor",
      "Bagpipes", "Birdpipes", "Drum", "Dulcimer", "Flute", "Glaur", "Hand Drum", "Horn", "Instrument of Illusions",
      "Instrument of Scribing", "Instrument of the Bards, Anstruth Harp", "Instrument of the Bards, Canaith Mandolin",
      "Instrument of the Bards, Cli Lyre", "Instrument of the Bards, Doss Lute",
      "Instrument of the Bards, Fochlucan Bandore", "Instrument of the Bards, Mac-Fuirmidh Cittern",
      "Instrument of the Bards, Ollamh Harp", "Longhorn", "Lute", "Lyre", "Pan Flute", "Pipes of Haunting",
      "Pipes of the Sewers", "Shawm", "Shawm", "Songhorn", "Tantan", "Thelarr", "Tocken", "Viol", "Wargong", "Yarting",
      "Zulkoon",
      "Band of Loyalty", "Ring of Acid Resistance", "Ring of Air Elemental Command", "Ring of Animal Influence",
      "Ring of Cold Resistance", "Ring of Djinni Summoning", "Ring of Earth Elemental Command", "Ring of Evasion",
      "Ring of Feather Falling", "Ring of Fire Elemental Command", "Ring of Fire Resistance",
      "Ring of Force Resistance", "Ring of Free Action", "Ring of Invisibility", "Ring of Jumping",
      "Ring of Lightning Resistance", "Ring of Mind Shielding", "Ring of Necrotic Resistance",
      "Ring of Poison Resistance", "Ring of Protection", "Ring of Psychic Resistance", "Ring of Radiant Resistance",
      "Ring of Regeneration", "Ring of Shooting Stars", "Ring of Spell Storing", "Ring of Spell Turning",
      "Ring of Swimming", "Ring of Telekinesis", "Ring of the Ram", "Ring of Three Wishes",
      "Ring of Thunder Resistance", "Ring of Warmth", "Ring of Water Elemental Command", "Ring of Water Walking",
      "Ring of Winter", "Ring of X-ray Vision", "Rings of Shared Suffering", "Ring of Truth Telling",
      "Teleporter Ring",
      "Barding", "Bit and bridle", "Exotic Saddle", "Feed (per day)", "Military Saddle", "Pack Saddle", "Riding Saddle",
      "Saddlebags", "Stabling (per day)",
      "Black Dragon Scale Mail", "Blue Dragon Scale Mail", "Brass Dragon Scale Mail", "Bronze Dragon Scale Mail",
      "Copper Dragon Scale Mail", "Dragonguard", "Elven Chain", "Gold Dragon Scale Mail", "Green Dragon Scale Mail",
      "Red Dragon Scale Mail", "Silver Dragon Scale Mail", "Survival Mantle", "White Dragon Scale Mail",
      "Bomb", "Dynamite (Stick)", "Fragmentation Grenade", "Grenade Launcher", "Gunpowder Horn", "Gunpowder Keg",
      "Smoke Grenade",
      "Bottled Breath", "Elixir of Health", "Oil of Etherealness", "Oil of Sharpness", "Oil of Slipperiness",
      "Philter of Love", "Potion of Acid Resistance", "Potion of Animal Friendship", "Potion of Clairvoyance",
      "Potion of Climbing", "Potion of Cloud Giant Strength", "Potion of Cold Resistance", "Potion of Diminution",
      "Potion of Fire Breath", "Potion of Fire Giant Strength", "Potion of Fire Resistance", "Potion of Flying",
      "Potion of Force Resistance", "Potion of Frost Giant Strength", "Potion of Gaseous Form", "Potion of Giant Size",
      "Potion of Greater Healing", "Potion of Growth", "Potion of Healing", "Potion of Heroism",
      "Potion of Hill Giant Strength", "Potion of Invisibility", "Potion of Invulnerability",
      "Potion of Lightning Resistance", "Potion of Longevity", "Potion of Mind Control (beast)",
      "Potion of Mind Control (humanoid)", "Potion of Mind Control (monster)", "Potion of Mind Reading",
      "Potion of Necrotic Resistance", "Potion of Poison", "Potion of Poison Resistance",
      "Potion of Psychic Resistance", "Potion of Radiant Resistance", "Potion of Speed",
      "Potion of Stone Giant Strength", "Potion of Storm Giant Strength", "Potion of Superior Healing",
      "Potion of Supreme Healing", "Potion of Thunder Resistance", "Potion of Vitality", "Potion of Water Breathing",
      "Camel", "Donkey", "Draft Horse", "Elephant", "Mastiff", "Mule", "Pony", "Riding Horse", "Warhorse",
      "Canoe", "Carriage", "Cart", "Chariot", "Sled", "Wagon",
      "Canvas (1 sq. yd.)", "Chicken", "Cinnamon", "Cloves", "Copper", "Cotton Cloth (1 sq. yd.)", "Cow", "Flour",
      "Ginger", "Goat", "Gold", "Iron", "Linen (1 sq. yd.)", "Ox", "Pepper", "Pig", "Platinum", "Saffron", "Salt",
      "Sheep", "Silk (1 sq. yd.)", "Silver", "Wheat",
      "Dice Set", "Dragonchess Set", "Playing Card Set", "Three-Dragon Ante Set",
      "Dimensional Seal", "Mabaran Resonator", "Master's Call", "Spell Sink", "Storm Sphere",
      "Disguise Kit", "Forgery Kit", "Hacking Tools", "Herbalism Kit", "Navigator's Tools", "Poisoner's Kit",
      "Thieves' Tools",
      "Glamoured Studded Leather",
      "Green Copper Ewer", "Statuette of Saint Markovia",
      "Immovable Rod", "Rod of Absorption", "Rod of Alertness", "Rod of Lordly Might", "Rod of Resurrection",
      "Rod of Rulership", "Rod of Security", "Rod of the Pact Keeper, (+1)", "Rod of the Pact Keeper (+2)",
      "Rod of the Pact Keeper (+3)", "Rod of the Vonindod", "Tentacle Rod",
      "Oathbow", "Seeker Dart", "Storm Boomerang", "Oversized Longbow",
      "Scroll of Protection from Aberrations", "Scroll of Protection from Beasts",
      "Scroll of Protection from Celestials", "Scroll of Protection from Elementals", "Scroll of Protection from Fey",
      "Scroll of Protection from Fiends", "Scroll of Protection from Plants", "Scroll of Protection from Undead",
      "Spell Scroll (1st Level)", "Spell Scroll (2nd Level)", "Spell Scroll (3rd Level)", "Spell Scroll (4th Level)",
      "Spell Scroll (5th Level)", "Spell Scroll (6th Level)", "Spell Scroll (7th Level)", "Spell Scroll (8th Level)",
      "Spell Scroll (9th Level)", "Spell Scroll (Cantrip)",
      "Unbreakable Arrow",
      "Wand of Binding", "Wand of Conducting", "Wand of Enemy Detection", "Wand of Entangle", "Wand of Fear",
      "Wand of Fireballs", "Wand of Lightning Bolts", "Wand of Magic Detection", "Wand of Magic Missiles",
      "Wand of Orcus", "Wand of Paralysis", "Wand of Polymorph", "Wand of Pyrotechnics", "Wand of Scowls",
      "Wand of Secrets", "Wand of Smiles", "Wand of the War Mage (+1)", "Wand of the War Mage (+2)",
      "Wand of the War Mage (+3)", "Wand of Viscid Globs", "Wand of Web", "Wand of Winter", "Wand of Wonder"

  };
  std::vector<std::string> names_of_sellable_itemsG =
      {"Abacus", "Acid (vial)", "Alchemist's Fire (flask)", "Antitoxin", "Assassin's Blood (Ingested)", "Backpack",
       "Ball Bearing", "Ball Bearings (Bag of 1,000)", "Barrel", "Basic Poison (vial)", "Basket", "Bedroll", "Bell",
       "Blanket", "Block and Tackle", "Book", "Bucket", "Bullseye Lantern", "Burglar's Pack",
       "Burnt Othur Fumes (Inhaled)", "Caltrops", "Caltrops (20)", "Candle", "Carrion Crawler Mucus (Contact)",
       "Chain (10 feet)", "Chalk (1 piece)", "Chest", "Climber's Kit", "Common Clothes", "Component Pouch",
       "Costume Clothes", "Crossbow Bolt Case", "Crowbar", "Dancing Monkey Fruit", "Diplomat's Pack",
       "Drow Poison (Injury)", "Dungeoneer's Pack", "Entertainer's Pack", "Essence of Ether (Inhaled)",
       "Explorer's Pack", "Fine Clothes", "Fishing Tackle", "Flask", "Glass Bottle", "Grappling Hook", "Hammer",
       "Healer's Kit", "Hempen Rope (50 feet)", "Holy Water (flask)", "Hooded Lantern", "Hourglass", "Hunting Trap",
       "Ink (1-ounce bottle)", "Ink Pen",
       "Insect Repellent (block of incense)", "Insect Repellent (greasy salve)", "Iron Pot", "Iron Spikes",
       "Iron Spikes (10)", "Jug", "Ladder (10-foot)", "Lamp", "Lock", "Magnifying Glass", "Malice (Inhaled)",
       "Manacles", "Map or Scroll Case", "Menga leaves (1 ounce)", "Merchant's Scale", "Mess Kit",
       "Midnight Tears (Ingested)", "Miner's Pick", "Monster Hunter's Pack", "Oil (flask)", "Oil of Taggit (Contact)",
       "Pale Tincture (Ingested)", "Paper (one sheet)", "Parchment (one sheet)", "Perfume (vial)", "Pitcher", "Piton",
       "Pole (10-foot)", "Portable Ram", "Pouch", "Priest's Pack", "Purple Worm Poison (Injury)", "Quiver",
       "Rain Catcher", "Rations (1 day)", "Robes", "Ryath Root", "Sack", "Scholar's Pack", "Sealing Wax",
       "Serpent Venom (Injury)", "Shovel", "Signal Whistle", "Signet Ring", "Silk Rope (50 feet)", "Sinda berries (10)",
       "Sledgehammer", "Soap", "Spellbook", "Spyglass", "Steel Mirror", "Tankard", "Tej", "Tinderbox", "Torch",
       "Torpor (Ingested)", "Traveler's Clothes", "Truth Serum (Ingested)",
       "Two-Person Tent", "Vial", "Waterskin", "Whetstone", "Wildroot", "Wukka Nut", "Wyvern Poison (Injury)", "Yahcha",
       "Zabou",};
  std::vector<std::string> names_of_sellable_itemsM = {"Reszur",};
  std::vector<std::string>
      names_of_sellable_itemsSHP = {"Airship", "Galley", "Keelboat", "Longship", "Rowboat", "Sailing Ship", "Warship",};
  std::vector<std::string> names_of_sellable_itemsAT =
      {"Alchemist's Supplies", "Brewer's Supplies", "Calligrapher's Supplies", "Carpenter's Tools",
       "Cartographer's Tools", "Cobbler's Tools", "Cook's Utensils", "Glassblower's Tools", "Jeweler's Tools",
       "Leatherworker's Tools", "Mason's Tools", "Painter's Supplies", "Potter's Tools", "Smith's Tools",
       "Tinker's Tools", "Weaver's Tools", "Woodcarver's Tools",};
  std::vector<std::string> names_of_sellable_items$ =
      {"Alexandrite", "Amber", "Amethyst", "Aquamarine", "Azurite", "Banded Agate",
       "Bejeweled ivory drinking horn with gold filigree", "Black Opal", "Black Pearl", "Black Sapphire",
       "Black velvet mask stitched with silver thread", "Bloodstone", "Blue Quartz", "Blue Sapphire", "Blue Spinel",
       "Bottle stopper cork embossed with gold leaf and set with amethysts", "Box of turquoise animal figurines",
       "Brass mug with jade inlay", "Bronze crown", "Carnelian", "Carved bone statuette",
       "Carved harp of exotic wood with ivory inlay and zircon gems", "Carved ivory statuette",
       "Ceremonial electrum dagger with a black pearl in the pommel", "Chalcedony", "Chrysoberyl", "Chrysoprase",
       "Citrine", "Cloth-of-gold vestments", "Copper (cp)", "Copper chalice with silver filigree", "Coral", "Diamond",
       "Electrum (ep)", "Embroidered glove set with jewel chips",
       "Embroidered silk and velvet mantle set with numerous moonstones", "Embroidered silk handkerchief", "Emerald",
       "Eye Agate",
       "Eye patch with a mock eye set in blue sapphire and moonstone", "Fine gold chain set with a fire opal",
       "Fire Opal", "Garnet", "Gold (gp)", "Gold bird cage with electrum filigree",
       "Gold circlet set with four aquamarines", "Gold cup set with emeralds",
       "Gold dragon comb set with red garnets as eyes", "Gold jewelry box with platinum filigree",
       "Gold locket with a painted portrait inside", "Gold music box", "Gold ring set with bloodstones", "Hematite",
       "Jacinth", "Jade", "Jade game board with solid gold playing pieces", "Jasper", "Jet", "Jeweled anklet",
       "Jeweled gold crown", "Jeweled platinum ring", "Lapis Lazuli", "Large gold bracelet", "Large well-made tapestry",
       "Malachite", "Moonstone", "Moss Agate", "Necklace string of small pink pearls", "Obsidian",
       "Obsidian statuette with gold fittings and inlay", "Old masterpiece painting", "Onyx", "Opal",
       "Painted gold child's sarcophagus", "Painted gold war mask", "Pair of engraved bone dice", "Pearl", "Peridot",
       "Platinum (pp)",
       "Platinum bracelet set with a sapphire", "Quartz", "Rhodochrosite", "Ruby", "Sardonyx",
       "Silk robe with gold embroidery", "Silver (sp)", "Silver and gold brooch", "Silver chalice set with moonstones",
       "Silver ewer", "Silver necklace with a gemstone pendant", "Silver-plated steel longsword with jet set in hilt",
       "Small gold bracelet", "Small gold idol", "Small gold statuette set with rubies",
       "Small mirror set in a painted wooden frame", "Spinel", "Star rose quartz", "Star Ruby", "Star Sapphire",
       "Tiger Eye", "Topaz", "Tourmaline", "Turquoise", "Yellow Sapphire", "Zircon", "Nib", "Shard", "Toal", "Dragon",
       "Sun", "Harbor Moon",};
  std::vector<std::string> names_of_sellable_itemsSCF =
      {"Amulet", "Emblem", "Reliquary", "Sprig of Mistletoe", "Totem", "Wooden Staff", "Yew Wand",};
  std::vector<std::string> names_of_sellable_itemsS = {};
  std::vector<std::string> names_of_sellable_itemsHA = {};
  std::vector<std::string> names_of_sellable_itemsINS =
      {"Bagpipes", "Drum", "Dulcimer", "Flute", "Horn", "Lute", "Lyre", "Pan Flute", "Shawm", "Viol",};
  std::vector<std::string> names_of_sellable_itemsRG = {};
  std::vector<std::string> names_of_sellable_itemsTAH =
      {"Barding", "Bit and bridle", "Exotic Saddle", "Feed (per day)", "Military Saddle", "Pack Saddle",
       "Riding Saddle", "Saddlebags", "Stabling (per day)",};
  std::vector<std::string> names_of_sellable_itemsMA = {};
  std::vector<std::string> names_of_sellable_itemsEXP = {"Bomb", "Gunpowder Horn", "Gunpowder Keg",};
  std::vector<std::string> names_of_sellable_itemsP = {"Potion of Healing",};
  std::vector<std::string> names_of_sellable_itemsMNT =
      {"Camel", "Donkey", "Draft Horse", "Elephant", "Mastiff", "Mule", "Pony", "Riding Horse", "Warhorse",};
  std::vector<std::string> names_of_sellable_itemsVEH = {"Canoe", "Carriage", "Cart", "Chariot", "Sled", "Wagon",};
  std::vector<std::string> names_of_sellable_itemsTG =
      {"Canvas (1 sq. yd.)", "Chicken", "Cinnamon", "Cloves", "Copper", "Cotton Cloth (1 sq. yd.)", "Cow", "Flour",
       "Ginger", "Goat", "Gold", "Iron", "Linen (1 sq. yd.)", "Ox", "Pepper", "Pig", "Platinum", "Saffron", "Salt",
       "Sheep", "Silk (1 sq. yd.)", "Silver", "Wheat",};
  std::vector<std::string>
      names_of_sellable_itemsGS = {"Dice Set", "Dragonchess Set", "Playing Card Set", "Three-Dragon Ante Set",};
  std::vector<std::string> names_of_sellable_itemsEM = {};
  std::vector<std::string> names_of_sellable_itemsT =
      {"Disguise Kit", "Forgery Kit", "Herbalism Kit", "Navigator's Tools", "Poisoner's Kit", "Thieves' Tools",};
  std::vector<std::string> names_of_sellable_itemsLA = {};
  std::vector<std::string> names_of_sellable_itemsOTH = {"Statuette of Saint Markovia",};
  std::vector<std::string> names_of_sellable_itemsRD = {};
  std::vector<std::string> names_of_sellable_itemsR = {};
  std::vector<std::string> names_of_sellable_itemsSC = {};
  std::vector<std::string> names_of_sellable_itemsA = {};
  std::vector<std::string> names_of_sellable_itemsWD = {};
  std::vector<std::string> names_of_sellable_itemsGV = {};
  std::vector<std::string> prices_G =
      {"2 gp", "25 gp", "50 gp", "50 gp", "150 gp", "2 gp", "0.1 cp", "1 gp", "2 gp", "100 gp", "4 sp", "1 gp", "1 gp",
       "5 sp", "1 gp", "25 gp", "5 cp", "10 gp", "16 gp", "500 gp", "5 cp", "1 gp", "1 cp", "200 gp", "5 gp", "1 cp",
       "5 gp", "25 gp", "5 sp", "25 gp", "5 gp", "1 gp", "2 gp", "5 gp", "39 gp", "200 gp", "12 gp", "40 gp", "300 gp",
       "10 gp", "15 gp", "1 gp", "1 cp", "2 gp", "2 gp", "1 gp", "5 gp", "1 gp", "25 gp", "5 gp", "25 gp", "5 gp",
       "10 gp", "2 cp", "1 sp", "1 gp", "2 gp", "1 sp", "1 gp", "2 cp", "1 sp", "5 sp", "10 gp", "100 gp", "250 gp",
       "2 gp", "1 gp", "2 gp", "5 gp", "2 sp", "1500 gp", "2 gp", "33 gp", "1 sp", "400 gp", "250 gp", "2 sp", "1 sp",
       "5 gp", "2 cp", "5 cp", "5 cp", "4 gp", "5 sp", "19 gp", "2000 gp", "1 gp", "1 gp", "5 sp", "1 gp", "50 gp",
       "1 cp", "40 gp", "5 sp", "200 gp", "2 gp", "5 cp", "5 gp", "10 gp", "5 gp", "2 gp", "2 cp", "50 gp", "1000 gp",
       "5 gp", "1 cp", "Varies", "5 sp", "1 cp", "600 gp", "2 gp", "150 gp", "2 gp", "1 gp", "2 sp", "1 cp",
       "25 gp", "1 gp", "1200 gp", "1 gp", "10 gp",};
  std::vector<std::string> prices_M = {"2 gp",};
  std::vector<std::string>
      prices_SHP = {"20000 gp", "30000 gp", "3000 gp", "10000 gp", "50 gp", "10000 gp", "25000 gp",};
  std::vector<std::string> prices_AT =
      {"50 gp", "20 gp", "10 gp", "8 gp", "15 gp", "5 gp", "1 gp", "30 gp", "25 gp", "5 gp", "10 gp", "10 gp", "10 gp",
       "20 gp", "50 gp", "1 gp", "1 gp",};
  std::vector<std::string> prices_$ =
      {"500 gp", "100 gp", "100 gp", "500 gp", "10 gp", "10 gp", "7500 gp", "1000 gp", "500 gp", "5000 gp", "25 gp",
       "50 gp", "10 gp", "1000 gp", "500 gp", "750 gp", "250 gp", "250 gp", "250 gp", "50 gp", "25 gp", "750 gp",
       "250 gp", "750 gp", "50 gp", "100 gp", "50 gp", "50 gp", "25 gp", "1 cp", "25 gp", "100 gp", "5000 gp", "1ep",
       "2500 gp", "2500 gp", "25 gp", "1000 gp", "10 gp", "2500 gp", "2500 gp", "1000 gp", "100 gp", "1 gp", "250 gp",
       "2500 gp", "7500 gp", "750 gp", "7500 gp", "25 gp", "2500 gp", "250 gp", "10 gp", "5000 gp", "100 gp", "7500 gp",
       "50 gp", "100 gp", "2500 gp", "7500 gp", "7500 gp", "10 gp", "250 gp", "250 gp", "10 gp", "50 gp", "10 gp",
       "2500 gp", "10 gp", "750 gp", "2500 gp", "50 gp", "1000 gp", "7500 gp", "750 gp", "25 gp", "100 gp", "500 gp",
       "1 pp", "2500 gp", "50 gp", "10 gp", "5000 gp", "50 gp", "250 gp", "1 sp", "750 gp", "750 gp", "25 gp", "250 gp",
       "750 gp", "25 gp", "750 gp", "7500 gp", "25 gp", "100 gp", "50 gp", "1000 gp", "1000 gp", "10 gp", "500 gp",
       "100 gp", "10 gp", "1000 gp", "50 gp", "1cp", "1sp", "2gp", "1gp", "1pp", "5pp",};
  std::vector<std::string> prices_SCF = {"5 gp", "5 gp", "5 gp", "1 gp", "1 gp", "5 gp", "10 gp",};
  std::vector<std::string> prices_S = {};
  std::vector<std::string> prices_HA = {};
  std::vector<std::string>
      prices_INS = {"30 gp", "6 gp", "25 gp", "2 gp", "3 gp", "35 gp", "30 gp", "12 gp", "2 gp", "30 gp",};
  std::vector<std::string> prices_RG = {};
  std::vector<std::string> prices_TAH = {"x4", "2 gp", "60 gp", "5 cp", "20 gp", "5 gp", "10 gp", "4 gp", "5 sp",};
  std::vector<std::string> prices_MA = {};
  std::vector<std::string> prices_EXP = {"150 gp", "35 gp", "250 gp",};
  std::vector<std::string> prices_P = {"50 gp",};
  std::vector<std::string>
      prices_MNT = {"50 gp", "8 gp", "50 gp", "200 gp", "25 gp", "8 gp", "30 gp", "75 gp", "400 gp",};
  std::vector<std::string> prices_VEH = {"50 gp", "100 gp", "15 gp", "250 gp", "20 gp", "35 gp",};
  std::vector<std::string> prices_TG =
      {"1 sp", "2 cp", "2 gp", "3 gp", "5 sp", "5 sp", "10 gp", "2 cp", "1 gp", "1 gp", "50 gp", "1 sp", "5 gp",
       "15 gp", "2 gp", "3 gp", "500 gp", "15 gp", "5 cp", "2 gp", "10 gp", "5 gp", "1 cp",};
  std::vector<std::string> prices_GS = {"1 sp", "1 gp", "5 sp", "1 gp",};
  std::vector<std::string> prices_EM = {};
  std::vector<std::string> prices_T = {"25 gp", "15 gp", "5 gp", "25 gp", "50 gp", "25 gp",};
  std::vector<std::string> prices_LA = {};
  std::vector<std::string> prices_OTH = {"250 gp",};
  std::vector<std::string> prices_RD = {};
  std::vector<std::string> prices_R = {};
  std::vector<std::string> prices_SC = {};
  std::vector<std::string> prices_A = {};
  std::vector<std::string> prices_WD = {};
  std::vector<std::string> prices_GV = {};
  std::vector<std::string> names_of_sellable_items =
      {"Abacus", "Acid (vial)", "Alchemist's Fire (flask)", "Antitoxin", "Assassin's Blood (Ingested)", "Backpack",
       "Ball Bearing", "Ball Bearings (Bag of 1,000)", "Barrel", "Basic Poison (vial)", "Basket", "Bedroll", "Bell",
       "Blanket", "Block and Tackle", "Book", "Bucket", "Bullseye Lantern", "Burglar's Pack",
       "Burnt Othur Fumes (Inhaled)", "Caltrops", "Caltrops (20)", "Candle", "Carrion Crawler Mucus (Contact)",
       "Chain (10 feet)", "Chalk (1 piece)", "Chest", "Climber's Kit", "Common Clothes", "Component Pouch",
       "Costume Clothes", "Crossbow Bolt Case", "Crowbar", "Dancing Monkey Fruit", "Diplomat's Pack",
       "Drow Poison (Injury)", "Dungeoneer's Pack", "Entertainer's Pack", "Essence of Ether (Inhaled)",
       "Explorer's Pack", "Fine Clothes", "Fishing Tackle", "Flask", "Glass Bottle", "Grappling Hook", "Hammer",
       "Healer's Kit", "Hempen Rope (50 feet)", "Holy Water (flask)", "Hooded Lantern", "Hourglass", "Hunting Trap",
       "Ink (1-ounce bottle)", "Ink Pen",
       "Insect Repellent (block of incense)", "Insect Repellent (greasy salve)", "Iron Pot", "Iron Spikes",
       "Iron Spikes (10)", "Jug", "Ladder (10-foot)", "Lamp", "Lock", "Magnifying Glass", "Malice (Inhaled)",
       "Manacles", "Map or Scroll Case", "Menga leaves (1 ounce)", "Merchant's Scale", "Mess Kit",
       "Midnight Tears (Ingested)", "Miner's Pick", "Monster Hunter's Pack", "Oil (flask)", "Oil of Taggit (Contact)",
       "Pale Tincture (Ingested)", "Paper (one sheet)", "Parchment (one sheet)", "Perfume (vial)", "Pitcher", "Piton",
       "Pole (10-foot)", "Portable Ram", "Pouch", "Priest's Pack", "Purple Worm Poison (Injury)", "Quiver",
       "Rain Catcher", "Rations (1 day)", "Robes", "Ryath Root", "Sack", "Scholar's Pack", "Sealing Wax",
       "Serpent Venom (Injury)", "Shovel", "Signal Whistle", "Signet Ring", "Silk Rope (50 feet)", "Sinda berries (10)",
       "Sledgehammer", "Soap", "Spellbook", "Spyglass", "Steel Mirror", "Tankard", "Tej", "Tinderbox", "Torch",
       "Torpor (Ingested)", "Traveler's Clothes", "Truth Serum (Ingested)",
       "Two-Person Tent", "Vial", "Waterskin", "Whetstone", "Wildroot", "Wukka Nut", "Wyvern Poison (Injury)", "Yahcha",
       "Zabou", "Reszur", "Airship", "Galley", "Keelboat", "Longship", "Rowboat", "Sailing Ship", "Warship",
       "Alchemist's Supplies", "Brewer's Supplies", "Calligrapher's Supplies", "Carpenter's Tools",
       "Cartographer's Tools", "Cobbler's Tools", "Cook's Utensils", "Glassblower's Tools", "Jeweler's Tools",
       "Leatherworker's Tools", "Mason's Tools", "Painter's Supplies", "Potter's Tools", "Smith's Tools",
       "Tinker's Tools", "Weaver's Tools", "Woodcarver's Tools", "Alexandrite", "Amber", "Amethyst", "Aquamarine",
       "Azurite", "Banded Agate", "Bejeweled ivory drinking horn with gold filigree", "Black Opal", "Black Pearl",
       "Black Sapphire", "Black velvet mask stitched with silver thread", "Bloodstone", "Blue Quartz", "Blue Sapphire",
       "Blue Spinel", "Bottle stopper cork embossed with gold leaf and set with amethysts",
       "Box of turquoise animal figurines", "Brass mug with jade inlay", "Bronze crown", "Carnelian",
       "Carved bone statuette", "Carved harp of exotic wood with ivory inlay and zircon gems", "Carved ivory statuette",
       "Ceremonial electrum dagger with a black pearl in the pommel", "Chalcedony", "Chrysoberyl", "Chrysoprase",
       "Citrine", "Cloth-of-gold vestments", "Copper (cp)", "Copper chalice with silver filigree", "Coral", "Diamond",
       "Electrum (ep)", "Embroidered glove set with jewel chips",
       "Embroidered silk and velvet mantle set with numerous moonstones", "Embroidered silk handkerchief", "Emerald",
       "Eye Agate", "Eye patch with a mock eye set in blue sapphire and moonstone",
       "Fine gold chain set with a fire opal", "Fire Opal", "Garnet", "Gold (gp)",
       "Gold bird cage with electrum filigree", "Gold circlet set with four aquamarines", "Gold cup set with emeralds",
       "Gold dragon comb set with red garnets as eyes", "Gold jewelry box with platinum filigree",
       "Gold locket with a painted portrait inside", "Gold music box", "Gold ring set with bloodstones", "Hematite",
       "Jacinth", "Jade",
       "Jade game board with solid gold playing pieces", "Jasper", "Jet", "Jeweled anklet", "Jeweled gold crown",
       "Jeweled platinum ring", "Lapis Lazuli", "Large gold bracelet", "Large well-made tapestry", "Malachite",
       "Moonstone", "Moss Agate", "Necklace string of small pink pearls", "Obsidian",
       "Obsidian statuette with gold fittings and inlay", "Old masterpiece painting", "Onyx", "Opal",
       "Painted gold child's sarcophagus", "Painted gold war mask", "Pair of engraved bone dice", "Pearl", "Peridot",
       "Platinum (pp)", "Platinum bracelet set with a sapphire", "Quartz", "Rhodochrosite", "Ruby", "Sardonyx",
       "Silk robe with gold embroidery", "Silver (sp)", "Silver and gold brooch", "Silver chalice set with moonstones",
       "Silver ewer", "Silver necklace with a gemstone pendant", "Silver-plated steel longsword with jet set in hilt",
       "Small gold bracelet", "Small gold idol", "Small gold statuette set with rubies",
       "Small mirror set in a painted wooden frame", "Spinel", "Star rose quartz", "Star Ruby", "Star Sapphire",
       "Tiger Eye", "Topaz", "Tourmaline", "Turquoise", "Yellow Sapphire", "Zircon", "Nib", "Shard", "Toal", "Dragon",
       "Sun", "Harbor Moon", "Amulet", "Emblem", "Reliquary", "Sprig of Mistletoe", "Totem", "Wooden Staff", "Yew Wand",
       "Bagpipes", "Drum", "Dulcimer", "Flute", "Horn", "Lute", "Lyre", "Pan Flute", "Shawm", "Viol", "Barding",
       "Bit and bridle", "Exotic Saddle", "Feed (per day)", "Military Saddle", "Pack Saddle", "Riding Saddle",
       "Saddlebags", "Stabling (per day)", "Bomb", "Gunpowder Horn", "Gunpowder Keg", "Potion of Healing", "Camel",
       "Donkey", "Draft Horse", "Elephant", "Mastiff", "Mule", "Pony", "Riding Horse", "Warhorse", "Canoe", "Carriage",
       "Cart", "Chariot", "Sled", "Wagon", "Canvas (1 sq. yd.)", "Chicken", "Cinnamon", "Cloves", "Copper",
       "Cotton Cloth (1 sq. yd.)", "Cow", "Flour", "Ginger", "Goat", "Gold", "Iron", "Linen (1 sq. yd.)", "Ox",
       "Pepper", "Pig", "Platinum", "Saffron", "Salt", "Sheep", "Silk (1 sq. yd.)", "Silver", "Wheat", "Dice Set",
       "Dragonchess Set", "Playing Card Set",
       "Three-Dragon Ante Set", "Disguise Kit", "Forgery Kit", "Herbalism Kit", "Navigator's Tools", "Poisoner's Kit",
       "Thieves' Tools", "Statuette of Saint Markovia"};
  std::vector<std::string> prices_of_sellable_items =
      {"2 gp", "25 gp", "50 gp", "50 gp", "150 gp", "2 gp", "0.1 cp", "1 gp", "2 gp", "100 gp", "4 sp", "1 gp", "1 gp",
       "5 sp", "1 gp", "25 gp", "5 cp", "10 gp", "16 gp", "500 gp", "5 cp", "1 gp", "1 cp", "200 gp", "5 gp", "1 cp",
       "5 gp", "25 gp", "5 sp", "25 gp", "5 gp", "1 gp", "2 gp", "5 gp", "39 gp", "200 gp", "12 gp", "40 gp", "300 gp",
       "10 gp", "15 gp", "1 gp", "1 cp", "2 gp", "2 gp", "1 gp", "5 gp", "1 gp", "25 gp", "5 gp", "25 gp", "5 gp",
       "10 gp", "2 cp", "1 sp", "1 gp", "2 gp", "1 sp", "1 gp", "2 cp", "1 sp", "5 sp", "10 gp", "100 gp", "250 gp",
       "2 gp", "1 gp", "2 gp", "5 gp", "2 sp", "1500 gp", "2 gp", "33 gp", "1 sp", "400 gp", "250 gp", "2 sp", "1 sp",
       "5 gp", "2 cp", "5 cp", "5 cp", "4 gp", "5 sp", "19 gp", "2000 gp", "1 gp", "1 gp", "5 sp", "1 gp", "50 gp",
       "1 cp", "40 gp", "5 sp", "200 gp", "2 gp", "5 cp", "5 gp", "10 gp", "5 gp", "2 gp", "2 cp", "50 gp", "1000 gp",
       "5 gp", "1 cp", "Varies", "5 sp", "1 cp", "600 gp", "2 gp", "150 gp", "2 gp", "1 gp", "2 sp",
       "1 cp", "25 gp", "1 gp", "1200 gp", "1 gp", "10 gp", "2 gp", "20000 gp", "30000 gp", "3000 gp", "10000 gp",
       "50 gp", "10000 gp", "25000 gp", "50 gp", "20 gp", "10 gp", "8 gp", "15 gp", "5 gp", "1 gp", "30 gp", "25 gp",
       "5 gp", "10 gp", "10 gp", "10 gp", "20 gp", "50 gp", "1 gp", "1 gp", "500 gp", "100 gp", "100 gp", "500 gp",
       "10 gp", "10 gp", "7500 gp", "1000 gp", "500 gp", "5000 gp", "25 gp", "50 gp", "10 gp", "1000 gp", "500 gp",
       "750 gp", "250 gp", "250 gp", "250 gp", "50 gp", "25 gp", "750 gp", "250 gp", "750 gp", "50 gp", "100 gp",
       "50 gp", "50 gp", "25 gp", "1 cp", "25 gp", "100 gp", "5000 gp", "1ep", "2500 gp", "2500 gp", "25 gp", "1000 gp",
       "10 gp", "2500 gp", "2500 gp", "1000 gp", "100 gp", "1 gp", "250 gp", "2500 gp", "7500 gp", "750 gp", "7500 gp",
       "25 gp", "2500 gp", "250 gp", "10 gp", "5000 gp", "100 gp", "7500 gp", "50 gp", "100 gp", "2500 gp", "7500 gp",
       "7500 gp", "10 gp", "250 gp", "250 gp", "10 gp", "50 gp", "10 gp", "2500 gp", "10 gp", "750 gp", "2500 gp",
       "50 gp", "1000 gp", "7500 gp",
       "750 gp", "25 gp", "100 gp", "500 gp", "1 pp", "2500 gp", "50 gp", "10 gp", "5000 gp", "50 gp", "250 gp", "1 sp",
       "750 gp", "750 gp", "25 gp", "250 gp", "750 gp", "25 gp", "750 gp", "7500 gp", "25 gp", "100 gp", "50 gp",
       "1000 gp", "1000 gp", "10 gp", "500 gp", "100 gp", "10 gp", "1000 gp", "50 gp", "1cp", "1sp", "2gp", "1gp",
       "1pp", "5pp", "5 gp", "5 gp", "5 gp", "1 gp", "1 gp", "5 gp", "10 gp", "30 gp", "6 gp", "25 gp", "2 gp", "3 gp",
       "35 gp", "30 gp", "12 gp", "2 gp", "30 gp", "x4", "2 gp", "60 gp", "5 cp", "20 gp", "5 gp", "10 gp", "4 gp",
       "5 sp", "150 gp", "35 gp", "250 gp", "50 gp", "50 gp", "8 gp", "50 gp", "200 gp", "25 gp", "8 gp", "30 gp",
       "75 gp", "400 gp", "50 gp", "100 gp", "15 gp", "250 gp", "20 gp", "35 gp", "1 sp", "2 cp", "2 gp", "3 gp",
       "5 sp", "5 sp", "10 gp", "2 cp", "1 gp", "1 gp", "50 gp", "1 sp", "5 gp", "15 gp", "2 gp", "3 gp", "500 gp",
       "15 gp", "5 cp", "2 gp", "10 gp", "5 gp", "1 cp", "1 sp", "1 gp", "5 sp", "1 gp", "25 gp", "15 gp", "5 gp",
       "25 gp", "50 gp", "25 gp", "250 gp"};
  std::vector<std::string> names_of_merchants_items =
      {"Abacus", "Acid (vial)", "Alchemist's Fire (flask)", "Antitoxin", "Assassin's Blood (Ingested)", "Backpack",
       "Ball Bearing", "Ball Bearings (Bag of 1,000)", "Barrel", "Basic Poison (vial)", "Basket", "Bedroll", "Bell",
       "Blanket", "Block and Tackle", "Book", "Bucket", "Bullseye Lantern", "Burglar's Pack",
       "Burnt Othur Fumes (Inhaled)", "Caltrops", "Caltrops (20)", "Candle", "Carrion Crawler Mucus (Contact)",
       "Chain (10 feet)", "Chalk (1 piece)", "Chest", "Climber's Kit", "Common Clothes", "Component Pouch",
       "Costume Clothes", "Crossbow Bolt Case", "Crowbar", "Diplomat's Pack", "Drow Poison (Injury)",
       "Dungeoneer's Pack", "Entertainer's Pack", "Essence of Ether (Inhaled)", "Explorer's Pack", "Fine Clothes",
       "Fishing Tackle", "Flask", "Glass Bottle", "Grappling Hook", "Hammer", "Healer's Kit", "Hempen Rope (50 feet)",
       "Holy Water (flask)", "Hooded Lantern", "Hourglass", "Hunting Trap", "Ink (1-ounce bottle)", "Ink Pen",
       "Insect Repellent (block of incense)",
       "Insect Repellent (greasy salve)", "Iron Pot", "Iron Spikes", "Iron Spikes (10)", "Jug", "Ladder (10-foot)",
       "Lamp", "Lock", "Magnifying Glass", "Malice (Inhaled)", "Manacles", "Map or Scroll Case", "Merchant's Scale",
       "Mess Kit", "Midnight Tears (Ingested)", "Miner's Pick", "Monster Hunter's Pack", "Oil (flask)",
       "Oil of Taggit (Contact)", "Pale Tincture (Ingested)", "Paper (one sheet)", "Parchment (one sheet)",
       "Perfume (vial)", "Pitcher", "Piton", "Pole (10-foot)", "Portable Ram", "Pouch", "Priest's Pack",
       "Purple Worm Poison (Injury)", "Quiver", "Rain Catcher", "Rations (1 day)", "Robes", "Sack", "Scholar's Pack",
       "Sealing Wax", "Serpent Venom (Injury)", "Shovel", "Signal Whistle", "Signet Ring", "Silk Rope (50 feet)",
       "Sledgehammer", "Soap", "Spellbook", "Spyglass", "Steel Mirror", "Tankard", "Tej", "Tinderbox", "Torch",
       "Torpor (Ingested)", "Traveler's Clothes", "Truth Serum (Ingested)", "Two-Person Tent", "Vial", "Waterskin",
       "Whetstone", "Wyvern Poison (Injury)", "Yahcha", "Zabou", "Airship",
       "Galley", "Keelboat", "Longship", "Rowboat", "Sailing Ship", "Warship", "Alchemist's Supplies",
       "Brewer's Supplies", "Calligrapher's Supplies", "Carpenter's Tools", "Cartographer's Tools", "Cobbler's Tools",
       "Cook's Utensils", "Glassblower's Tools", "Jeweler's Tools", "Leatherworker's Tools", "Mason's Tools",
       "Painter's Supplies", "Potter's Tools", "Smith's Tools", "Tinker's Tools", "Weaver's Tools",
       "Woodcarver's Tools", "Alexandrite", "Amber", "Amethyst", "Aquamarine", "Azurite", "Banded Agate",
       "Bejeweled ivory drinking horn with gold filigree", "Black Opal", "Black Pearl", "Black Sapphire",
       "Black velvet mask stitched with silver thread", "Bloodstone", "Blue Quartz", "Blue Sapphire", "Blue Spinel",
       "Bottle stopper cork embossed with gold leaf and set with amethysts", "Box of turquoise animal figurines",
       "Brass mug with jade inlay", "Bronze crown", "Carnelian", "Carved bone statuette",
       "Carved harp of exotic wood with ivory inlay and zircon gems", "Carved ivory statuette",
       "Ceremonial electrum dagger with a black pearl in the pommel", "Chalcedony", "Chrysoberyl", "Chrysoprase",
       "Citrine", "Cloth-of-gold vestments", "Copper (cp)", "Copper chalice with silver filigree", "Coral", "Diamond",
       "Electrum (ep)", "Embroidered glove set with jewel chips",
       "Embroidered silk and velvet mantle set with numerous moonstones", "Embroidered silk handkerchief", "Emerald",
       "Eye Agate", "Eye patch with a mock eye set in blue sapphire and moonstone",
       "Fine gold chain set with a fire opal", "Fire Opal", "Garnet", "Gold (gp)",
       "Gold bird cage with electrum filigree", "Gold circlet set with four aquamarines", "Gold cup set with emeralds",
       "Gold dragon comb set with red garnets as eyes", "Gold jewelry box with platinum filigree",
       "Gold locket with a painted portrait inside", "Gold music box", "Gold ring set with bloodstones", "Hematite",
       "Jacinth", "Jade", "Jade game board with solid gold playing pieces", "Jasper", "Jet", "Jeweled anklet",
       "Jeweled gold crown", "Jeweled platinum ring", "Lapis Lazuli",
       "Large gold bracelet", "Large well-made tapestry", "Malachite", "Moonstone", "Moss Agate",
       "Necklace string of small pink pearls", "Obsidian", "Obsidian statuette with gold fittings and inlay",
       "Old masterpiece painting", "Onyx", "Opal", "Painted gold child's sarcophagus", "Painted gold war mask",
       "Pair of engraved bone dice", "Pearl", "Peridot", "Platinum (pp)", "Platinum bracelet set with a sapphire",
       "Quartz", "Rhodochrosite", "Ruby", "Sardonyx", "Silk robe with gold embroidery", "Silver (sp)",
       "Silver and gold brooch", "Silver chalice set with moonstones", "Silver ewer",
       "Silver necklace with a gemstone pendant", "Silver-plated steel longsword with jet set in hilt",
       "Small gold bracelet", "Small gold idol", "Small gold statuette set with rubies",
       "Small mirror set in a painted wooden frame", "Spinel", "Star rose quartz", "Star Ruby", "Star Sapphire",
       "Tiger Eye", "Topaz", "Tourmaline", "Turquoise", "Yellow Sapphire", "Zircon", "Nib", "Shard", "Toal", "Dragon",
       "Sun", "Harbor Moon", "Amulet", "Emblem",
       "Reliquary", "Sprig of Mistletoe", "Totem", "Wooden Staff", "Yew Wand", "Bagpipes", "Drum", "Dulcimer", "Flute",
       "Horn", "Lute", "Lyre", "Pan Flute", "Shawm", "Viol", "Barding", "Bit and bridle", "Exotic Saddle",
       "Feed (per day)", "Military Saddle", "Pack Saddle", "Riding Saddle", "Saddlebags", "Stabling (per day)", "Bomb",
       "Gunpowder Horn", "Gunpowder Keg", "Camel", "Donkey", "Draft Horse", "Elephant", "Mastiff", "Mule", "Pony",
       "Riding Horse", "Warhorse", "Canoe", "Carriage", "Cart", "Chariot", "Sled", "Wagon", "Canvas (1 sq. yd.)",
       "Chicken", "Cinnamon", "Cloves", "Copper", "Cotton Cloth (1 sq. yd.)", "Cow", "Flour", "Ginger", "Goat", "Gold",
       "Iron", "Linen (1 sq. yd.)", "Ox", "Pepper", "Pig", "Platinum", "Saffron", "Salt", "Sheep", "Silk (1 sq. yd.)",
       "Silver", "Wheat", "Dice Set", "Dragonchess Set", "Playing Card Set", "Three-Dragon Ante Set", "Disguise Kit",
       "Forgery Kit", "Herbalism Kit", "Navigator's Tools", "Poisoner's Kit", "Thieves' Tools",};
  std::vector<std::string> prices_of_merchants_items =
      {"2 gp", "25 gp", "50 gp", "50 gp", "150 gp", "2 gp", "0.1 cp", "1 gp", "2 gp", "100 gp", "4 sp", "1 gp", "1 gp",
       "5 sp", "1 gp", "25 gp", "5 cp", "10 gp", "16 gp", "500 gp", "5 cp", "1 gp", "1 cp", "200 gp", "5 gp", "1 cp",
       "5 gp", "25 gp", "5 sp", "25 gp", "5 gp", "1 gp", "2 gp", "39 gp", "200 gp", "12 gp", "40 gp", "300 gp", "10 gp",
       "15 gp", "1 gp", "1 cp", "2 gp", "2 gp", "1 gp", "5 gp", "1 gp", "25 gp", "5 gp", "25 gp", "5 gp", "10 gp",
       "2 cp", "1 sp", "1 gp", "2 gp", "1 sp", "1 gp", "2 cp", "1 sp", "5 sp", "10 gp", "100 gp", "250 gp", "2 gp",
       "1 gp", "5 gp", "2 sp", "1500 gp", "2 gp", "33 gp", "1 sp", "400 gp", "250 gp", "2 sp", "1 sp", "5 gp", "2 cp",
       "5 cp", "5 cp", "4 gp", "5 sp", "19 gp", "2000 gp", "1 gp", "1 gp", "5 sp", "1 gp", "1 cp", "40 gp", "5 sp",
       "200 gp", "2 gp", "5 cp", "5 gp", "10 gp", "2 gp", "2 cp", "50 gp", "1000 gp", "5 gp", "1 cp", "Varies", "5 sp",
       "1 cp", "600 gp", "2 gp", "150 gp", "2 gp", "1 gp", "2 sp", "1 cp", "1200 gp", "1 gp", "10 gp",
       "20000 gp", "30000 gp", "3000 gp", "10000 gp", "50 gp", "10000 gp", "25000 gp", "50 gp", "20 gp", "10 gp",
       "8 gp", "15 gp", "5 gp", "1 gp", "30 gp", "25 gp", "5 gp", "10 gp", "10 gp", "10 gp", "20 gp", "50 gp", "1 gp",
       "1 gp", "500 gp", "100 gp", "100 gp", "500 gp", "10 gp", "10 gp", "7500 gp", "1000 gp", "500 gp", "5000 gp",
       "25 gp", "50 gp", "10 gp", "1000 gp", "500 gp", "750 gp", "250 gp", "250 gp", "250 gp", "50 gp", "25 gp",
       "750 gp", "250 gp", "750 gp", "50 gp", "100 gp", "50 gp", "50 gp", "25 gp", "1 cp", "25 gp", "100 gp", "5000 gp",
       "1ep", "2500 gp", "2500 gp", "25 gp", "1000 gp", "10 gp", "2500 gp", "2500 gp", "1000 gp", "100 gp", "1 gp",
       "250 gp", "2500 gp", "7500 gp", "750 gp", "7500 gp", "25 gp", "2500 gp", "250 gp", "10 gp", "5000 gp", "100 gp",
       "7500 gp", "50 gp", "100 gp", "2500 gp", "7500 gp", "7500 gp", "10 gp", "250 gp", "250 gp", "10 gp", "50 gp",
       "10 gp", "2500 gp", "10 gp", "750 gp", "2500 gp", "50 gp", "1000 gp", "7500 gp", "750 gp", "25 gp", "100 gp",
       "500 gp", "1 pp", "2500 gp",
       "50 gp", "10 gp", "5000 gp", "50 gp", "250 gp", "1 sp", "750 gp", "750 gp", "25 gp", "250 gp", "750 gp", "25 gp",
       "750 gp", "7500 gp", "25 gp", "100 gp", "50 gp", "1000 gp", "1000 gp", "10 gp", "500 gp", "100 gp", "10 gp",
       "1000 gp", "50 gp", "1cp", "1sp", "2gp", "1gp", "1pp", "5pp", "5 gp", "5 gp", "5 gp", "1 gp", "1 gp", "5 gp",
       "10 gp", "30 gp", "6 gp", "25 gp", "2 gp", "3 gp", "35 gp", "30 gp", "12 gp", "2 gp", "30 gp", "x4", "2 gp",
       "60 gp", "5 cp", "20 gp", "5 gp", "10 gp", "4 gp", "5 sp", "150 gp", "35 gp", "250 gp", "50 gp", "8 gp", "50 gp",
       "200 gp", "25 gp", "8 gp", "30 gp", "75 gp", "400 gp", "50 gp", "100 gp", "15 gp", "250 gp", "20 gp", "35 gp",
       "1 sp", "2 cp", "2 gp", "3 gp", "5 sp", "5 sp", "10 gp", "2 cp", "1 gp", "1 gp", "50 gp", "1 sp", "5 gp",
       "15 gp", "2 gp", "3 gp", "500 gp", "15 gp", "5 cp", "2 gp", "10 gp", "5 gp", "1 cp", "1 sp", "1 gp", "5 sp",
       "1 gp", "25 gp", "15 gp", "5 gp", "25 gp", "50 gp", "25 gp",};

};
//types = {"G", "M", "SHP", "AT", "$", "SCF", "S",
// "HA", "INS", "RG", "TAH", "MA", "EXP", "P", "MNT",
// "VEH", "TG", "GS", "EM", "T", "LA", "OTH", "RD", "R"
// "SC", "A", "WD", "GV", "", "", "", "", "", "", "", "", }
// Goods, Melee, Ship, Artisan Tools, Valuables, Spell Casting Focus, Shield,
// Heavy Armor, Instrument (music)?, Ring, To Animal Handle?, MediumArmor, Explosive, Potions, Mounties
// Vehicle, Trade Goods, Gaming Set, ElectronicMachines???, Tools, Light Armor, OTH, Rod, Ranged
// Scroll, Ammo?, Wand, GV?
// No DMG, TftYP, ToA because of (no type)
class Item {
 protected:
  bool equipped;
  int num_equipped;
  std::string name;
  int count;
  bool stackable;
  int cost;
  int weight;
  std::string what_class_is_it;
  std::string source;
  bool attune_requirement;
  std::vector<bool> who_can_attune;
  bool Attuned;
  std::string rarity;
  std::string tier;
  std::vector<std::string> entries;
  std::vector<std::string> attachedSpells;
 public:
  Item();
  ~Item();

  virtual std::string get_name();
  virtual int show();
  virtual void set_count(int a);
  virtual int get(int a);
  virtual void equip(int a);
  void Attune();
  bool Is_Attuned();
  virtual bool is_equipped();
  int Price_Parse(const nlohmann::basic_json<> &j, int i);
  std::vector<std::string> Entries_Parse(const nlohmann::basic_json<> &j, int i);
  std::vector<std::string> AttachedSpells_Parse(const nlohmann::basic_json<> &j, int i);

  //TODO: Who can Attune
  virtual std::string What_class();
};

class Melee_Weapon :
    public Item {
 protected:
  bool reqAttune;
  bool reqAttuneByWho[kClass_NuM + kRace_Num + kRace_Num];
  int num_of_dices1;
  int damage_dice1;
  int num_of_dices2;
  int damage_dice2;
  int type_of_elemental_damage;
  int weapon_category;
  int aiming_range;
  int max_range;
  std::string damage_type;
  std::vector<std::string> property;
 public:
  Melee_Weapon();
  Melee_Weapon(std::string &name_);
  Melee_Weapon(std::string &name_, int
  count_);
  ~Melee_Weapon();
  virtual void set(std::string &name_, int count_);
  int show()
  override;
  virtual int get(int a);
};

class Ranged_Weapon :
    public Melee_Weapon {
 protected:
 public:
  Ranged_Weapon();
  Ranged_Weapon(std::string &name_);
  Ranged_Weapon(std::string &name_, int
  count_);
  ~Ranged_Weapon();
  void set(std::string &name_, int count_)
  override;

  int show()
  override;

  int get(int a)
  override;
};

/*class Food : public Item {
 public:
  Food(std::string &name_, int count_) {
    set(name_, count_);
  }
  ~Food() = default;
  void set(std::string &name_, int count_) {
    name = name_;
    count = count_;
    stackable = true;
  }
  int show() {
    printf("%s", "Goods:");
    std::cout << name << std::endl;
    return count;
  }
};*/

class Armor :
    public Item {
 protected:
  bool reqAttune;
  bool reqAttuneByWho[kClass_NuM + kRace_Num];
  int type_of_armor;
  int armor_class;
  int strength_needed;
  bool stealth_disadvantage;
 public:
  Armor(std::string &name_);
  Armor(std::string &name_, int
  count_);
  //Armor(std::string &name_, int type_, int count_, int armor_class_, int strength_needed_, bool stealth_disadvantage_);
  ~Armor();
  void set(std::string &name_, int count_);
  int show()
  override;

  int get(int a)
  override;
};

class Goods :
    public Item {
 private:
  bool is_obstacle;
 public:
  Goods();
  Goods(std::string &name_, int
  count_);
  Goods(std::string &name_);
  ~Goods();
  virtual void set(std::string &name_, int count_);
  int show()
  override;

  virtual int get(int a);
};

class Ammo :
    public Goods {
 protected:
  bool reqAttune;
  bool reqAttuneByWho[kClass_NuM + kRace_Num];
  int ammo_damage;
  int element;
 public:
  Ammo();
  Ammo(std::string &name_, int
  count_);
  Ammo(std::string &name_);
  //Ammo(std::string &name_, int count_, int ammo_damage_, int element_);
  void set(std::string &name_, int count_)
  override;
  int show()
  override;

  int get(int a)
  override;

};

class ArtisanTools :
    public Item {
 private:
 public:
  ArtisanTools();
  ArtisanTools(std::string &name_);
  ArtisanTools(std::string &name_, int
  count_);
  ~ArtisanTools();
  void set(std::string &name_, int count_);

  int get(int a)
  override;
};

class Ship :
    public Item {
 private:
  std::string speed;
  std::string carryingcapacity;
  int crew;
  int vehAc;
  int vehHp;
  int vehDmgThresh;
  /*Damage Threshold. If a ship has a Damage Threshold, it has immunity to all damage unless it takes an
   * amount of damage equal to or greater than its damage threshold, in which case it takes damage as normal.*/
 public:
  Ship();
  Ship(std::string &name_);
  Ship(std::string &name_, int
  count_);
  ~Ship();
  void set(std::string &name_, int count_);

  int get(int a)
  override;
};

class Valuables :
    public Item {
 private:
 public:
  Valuables();
  Valuables(std::string &name_);
  Valuables(std::string &name_, int
  count_);
  ~Valuables();
  void set(std::string &name_, int count_);

  int get(int a)
  override;
};

class SpellCastingFocus :
    public Item {
 private:
  bool reqAttune;
  bool reqAttuneByWho[kClass_NuM + kRace_Num];
  bool arcane_focus;
  bool druidic_focus;
  bool holy_symbol;
  int scfType;//holy, druid, arcane
 public:
  SpellCastingFocus();
  SpellCastingFocus(std::string &name_);
  SpellCastingFocus(std::string &name_, int
  count_);
  ~SpellCastingFocus();
  void set(std::string &name_, int count_);

  int get(int a)
  override;
};

class Shield :
    public Item {
 private:
  int ac;
  bool reqAttune;
  bool reqAttuneByWho[kClass_NuM + kRace_Num];
 public:
  Shield();
  Shield(std::string &name_);
  Shield(std::string &name_, int
  count_);
  ~Shield();
  void set(std::string &name_, int count_);

  int get(int a)
  override;
};

class Instrument :
    public Item {
 private:

 public:
  Instrument();
  Instrument(std::string &name_);
  Instrument(std::string &name_, int
  count_);
  ~Instrument();
  void set(std::string &name_, int count_);

  int get(int a)
  override;
};

class Ring :
    public Item {
 private:
  int charges;
  int resistance_type;
  bool reqAttune;
  bool reqAttuneByWho[kClass_NuM + kRace_Num];
 public:
  Ring();
  Ring(std::string &name_);
  Ring(std::string &name_, int
  count_);
  ~Ring();
  void set(std::string &name_, int count_);

  int get(int a)
  override;
};

class AnimalGear :
    public Item {
 private:

 public:
  AnimalGear();
  AnimalGear(std::string &name_);
  AnimalGear(std::string &name_, int
  count_);
  ~AnimalGear();
  void set(std::string &name_, int count_);

  int get(int a)
  override;
};

class Explosive :
    public Item {
 private:
  std::string age;
 public:
  Explosive();
  Explosive(std::string &name_);
  Explosive(std::string &name_, int
  count_);
  ~Explosive();
  void set(std::string &name_, int count_);

  int get(int a)
  override;
};

class Potion :
    public Item {
 private:
  int healing;
  int num_of_healing_dices;
  int healing_dice;
 public:
  Potion();
  Potion(std::string &name_);
  Potion(std::string &name_, int
  count_);
  ~Potion();
  void set(std::string &name_, int count_);

  int get(int a)
  override;
};

class Mounties :
    public Item {
 private:
  std::string carryingcapacity;
  std::string speed;
 public:
  Mounties();
  Mounties(std::string &name_);
  Mounties(std::string &name_, int
  count_);
  ~Mounties();
  void set(std::string &name_, int count_);

  int get(int a)
  override;
};

class Vehicle :
    public Item {
 private:
  std::string speed;
  std::string carryingcapacity;
 public:
  Vehicle();
  Vehicle(std::string &name_);
  Vehicle(std::string &name_, int
  count_);
  ~Vehicle();
  void set(std::string &name_, int count_);

  int get(int a)
  override;
};

class TradeGoods :
    public Item {
 private:

 public:
  TradeGoods();
  TradeGoods(std::string &name_);
  TradeGoods(std::string &name_, int
  count_);
  ~TradeGoods();
  void set(std::string &name_, int count_);

  int get(int a)
  override;
};

class GamingSet :
    public Item {
 private:

 public:
  GamingSet();
  GamingSet(std::string &name_);
  GamingSet(std::string &name_, int
  count_);
  ~GamingSet();
  void set(std::string &name_, int count_);

  int get(int a)
  override;
};

class Device :
    public Item {
 private:
  bool reqAttune;//?
 public:
  Device();//EM
  Device(std::string &name_);
  Device(std::string &name_, int
  count_);
  ~Device();
  void set(std::string &name_, int count_);

  int get(int a)
  override;
};

class Tools :
    public Item {
 private:

 public:
  Tools();
  Tools(std::string &name_);
  Tools(std::string &name_, int
  count_);
  ~Tools();
  void set(std::string &name_, int count_);

  int get(int a)
  override;
};

class OTH :
    public Item {
 private:

 public:
  OTH();
  OTH(std::string &name_);
  OTH(std::string &name_, int
  count_);
  ~OTH();
  void set(std::string &name_, int count_);

  int get(int a)
  override;
};

class Rod :
    public Item {
 private:
  bool reqAttune;
  bool reqAttuneByWho[kClass_NuM + kRace_Num];//classes
 public:
  Rod();
  Rod(std::string &name_);
  Rod(std::string &name_, int
  count_);
  ~Rod();
  void set(std::string &name_, int count_);

  int get(int a)
  override;
};

class Scroll :
    public Item {
 private:

 public:
  Scroll();
  Scroll(std::string &name_);
  Scroll(std::string &name_, int
  count_);
  ~Scroll();
  void set(std::string &name_, int count_);

  int get(int a)
  override;
};

class Wand :
    public Item {
 private:
  bool reqAttune;
  bool reqAttuneByWho[kClass_NuM + kRace_Num];
  int charges;
 public:
  Wand();
  Wand(std::string &name_);
  Wand(std::string &name_, int
  count_);
  ~Wand();
  void set(std::string &name_, int count_);

  int get(int a)
  override;
};

class GV :
    public Item {
 private:

 public:
  GV();
  GV(std::string &name_);
  GV(std::string &name_, int
  count_);
  ~GV();
  void set(std::string &name_, int count_);

  int get(int a)
  override;
};

/*class  : public Item {
 private:

 public:
  Magic_Items();
  Magic_Items(std::string &name_);
  Magic_Items(std::string &name_, int count_);
  ~Magic_Items();
  void set(std::string &name_, int count_);

  int show() override;

  int get(int a) override;
};*/

#endif //ANOTHER_DND_SIMULATOR_ITEM_H
