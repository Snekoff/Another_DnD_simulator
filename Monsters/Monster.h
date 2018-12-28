#pragma once
#ifndef ANOTHER_DND_SIMULATOR_MONSTER_H
#define ANOTHER_DND_SIMULATOR_MONSTER_H
#include <fstream>
#include "../Character/character.h"
#include "../json_parse_by_nlohmann/json.hpp"

const int kMonster_NUM = 1104;
const int kMonster_Parameter_NUM = 6;

struct Exsisting_Monsters {
  //in challenge_rating groups order. (0, 1/8, 1/4, 1/2, 1, 2...., 30, Unknown)
  vector<vector<string>> Challenge_rating =
      {{"Giant Fly", "Larva", "Awakened Shrub", "Baboon", "Badger", "Bat", "Cat", "Commoner", "Crab", "Crawling Claw",
        "Deer", "Eagle", "Frog", "Giant Fire Beetle", "Goat", "Hawk", "Homunculus", "Hyena", "Jackal", "Lemure",
        "Lizard", "Myconid Sprout", "Octopus", "Owl", "Quipper", "Rat", "Raven", "Scorpion", "Sea Horse", "Shrieker",
        "Spider", "Vulture", "Weasel", "Servo", "Augrek Brighthelm", "Beldora", "Darathra Shendrel", "Darz Helgar",
        "Duvessa Shane", "Ghelryn Foehammer", "Lifferlas", "Markham Southwell", "Miros Xelbrin", "Narth Tezrin",
        "Naxene Drathkala", "Oren Yogilvy", "Othovir", "Shalvus Martholio", "Sir Baric Nylef", "Sirac of Suzail",
        "Tressym", "Urgala Meltimer", "Zi Liang", "Almiraj", "Chwinga", "Flying Monkey", "Cranium Rat",
        "Magister Umbero Zastro", "Sylgar", "Awakened Rat", "Bepis Honeymaker", "Thorvin Twinbeard",
        "Talisolvanar \"Tally\" Fellbranch",},
       {"Young Kruthik", "Bandit", "Blood Hawk", "Camel", "Cultist", "Flumph", "Flying Snake", "Giant Crab",
        "Giant Rat", "Giant Rat (Diseased)", "Giant Weasel", "Guard", "Kobold", "Manes", "Mastiff", "Merfolk",
        "Monodrone", "Mule", "Noble", "Poisonous Snake", "Pony", "Slaad Tadpole", "Stirge", "Tribal Warrior",
        "Twig Blight", "Bridesmaid of Zuggtmoy", "Drow Spore Servant", "Howling Hatred Initiate", "Aarakocra Simulacra",
        "Mwaxanare", "Boggle", "Dolphin", "Neogi Hatchling", "Xvart", "Xvart Speaker", "Yalah Gralhund",
        "Orond Gralhund", "Ott Steeltoes",},
       {"Abyssal Wretch", "Derro", "Male Steeder", "Oblex Spawn", "Star Spawn Grue", "The Wretched", "Tortle",
        "Broom of Animated Attack", "Mongrelfolk", "Pidlwick II", "Ash Zombie", "Aarakocra", "Acolyte", "Axe Beak",
        "Blink Dog", "Boar", "Bullywug", "Constrictor Snake", "Draft Horse", "Dretch", "Drow", "Duodrone", "Elk",
        "Flying Sword", "Giant Badger", "Giant Bat", "Giant Centipede", "Giant Frog", "Giant Lizard", "Giant Owl",
        "Giant Poisonous Snake", "Giant Wolf Spider", "Goblin", "Grimlock", "Kenku", "Kuo-toa", "Mud Mephit",
        "Needle Blight", "Panther", "Pixie", "Pseudodragon", "Pteranodon", "Riding Horse", "Skeleton", "Smoke Mephit",
        "Sprite", "Steam Mephit", "Swarm of Bats", "Swarm of Rats", "Swarm of Ravens", "Troglodyte", "Violet Fungus",
        "Winged Kobold", "Wolf", "Zombie", "Derro", "Giant Riding Lizard", "Ixitxachitl", "Ixitxachitl Cleric",
        "Lords' Alliance Guard", "Male Steeder", "Erky Timbers", "Grenl", "Guthash", "Albino Dwarf Warrior",
        "Tabaxi Minstrel", "Volothamp \"Volo\" Geddarm", "Yellow Musk Zombie", "Geonid", "Tortle", "Apprentice Wizard",
        "Cow", "Deep Rothé", "Dimetrodon", "Gnoll Witherling", "Grung", "Hadrosaurus", "Kobold Inventor", "Ox", "Rothé",
        "Stench Kow", "Vegepygmy", "Velociraptor", "Flying Staff", "Swarm of Books", "Panopticus Wizard", "Engineer",
        "Maxeene", "Grum'shar",},
       {"Nupperibo", "Skulk", "Barovian Witch", "Ambush Drake", "Redbrand Ruffian", "Ape", "Black Bear", "Cockatrice",
        "Crocodile", "Darkmantle", "Deep Gnome (Svirfneblin)", "Dust Mephit", "Gas Spore", "Giant Goat",
        "Giant Sea Horse", "Giant Wasp", "Gnoll", "Gray Ooze", "Gray Ooze (Psychic)", "Hobgoblin", "Ice Mephit",
        "Jackalwere", "Lizardfolk", "Magma Mephit", "Magmin", "Myconid Adult", "Orc", "Piercer", "Reef Shark",
        "Rust Monster", "Sahuagin", "Satyr", "Scout", "Shadow", "Swarm of Beetles", "Swarm of Centipedes",
        "Swarm of Insects", "Swarm of Spiders", "Swarm of Wasps", "Thug", "Tridrone", "Vine Blight", "Warhorse",
        "Warhorse Skeleton", "Worg", "Duergar Spore Servant", "Emerald Enclave Scout", "Zhentarim Thug",
        "Crushing Wave Reaver", "Sacred Stone Monk", "Gremlin", "Frilled Deathspitter", "Sharwyn Hucrele",
        "Sir Braford", "Thorn Slinger", "Jaculi", "Tri-Flower Frond", "Zorbo", "Topi", "Clawfoot Raptor", "Chitine",
        "Darkling", "Firenewt Warrior", "Gazer", "Gnoll Hunter", "Orc Nurtured One of Yurtrus", "Swarm of Rot Grubs",
        "Swarm of Mechanical Spiders", "Noska Ur'gray", "Yagra Stonefist", "Yorn",},
       {"Bronze Scout", "Choker", "Duergar Soulblade", "Female Steeder", "Meazel", "Stone Cursed", "Guardian Portrait",
        "Strahd Zombie", "Jamna Gleamsilver", "Evil Mage", "Sildar Hallwinter", "Animated Armor",
        "Brass Dragon Wyrmling", "Brown Bear", "Bugbear", "Copper Dragon Wyrmling", "Death Dog", "Dire Wolf", "Dryad",
        "Duergar", "Faerie Dragon (Orange)", "Faerie Dragon (Red)", "Faerie Dragon (Yellow)", "Fire Snake", "Ghoul",
        "Giant Eagle", "Giant Hyena", "Giant Octopus", "Giant Spider", "Giant Toad", "Giant Vulture", "Goblin Boss",
        "Half-Ogre (Ogrillon)", "Harpy", "Hippogriff", "Imp", "Kuo-toa Whip", "Lion", "Quadrone",
        "Quaggoth Spore Servant", "Quasit", "Scarecrow", "Specter", "Spy", "Swarm of Quippers", "Thri-kreen",
        "Thri-kreen (Psionic)", "Tiger", "Yuan-ti Pureblood", "Duergar Soulblade", "Female Steeder",
        "Lords' Alliance Spy", "Spider King", "Feathergale Knight", "Homarid", "Dragonclaw", "Ice Toad", "Crag Cat",
        "Zaltember", "Blazing Skeleton", "Choker", "Dread Warrior", "Durnn", "Yusdrayl", "Albino Dwarf Spirit Warrior",
        "Aldani (Lobsterfolk)", "Eblis", "Mantrap", "Pterafolk", "Su-Monster", "Tabaxi Hunter", "Deinonychus",
        "Firenewt Warlock of Imix", "Giant Strider", "Gnoll Flesh Gnawer", "Grung Wildling", "Kobold Dragonshield",
        "Kobold Scale Sorcerer", "Maw Demon", "Nilbog", "Quickling", "Sea Spawn", "Thorny", "Vargouille",
        "Xvart Warlock of Raxivort",},
       {"Adult Kruthik", "Berbalang", "Duergar Hammerer", "Duergar Kavalrachni", "Duergar Mind Master",
        "Duergar Stone Guard", "Duergar Xarrorn", "Ogre Bolt Launcher", "Ogre Howdah", "Rutterkin", "Tortle Druid",
        "Wereraven", "Frulam Mondath", "Nezznar the Black Spider", "Allosaurus", "Ankheg", "Awakened Tree", "Azer",
        "Bandit Captain", "Berserker", "Black Dragon Wyrmling", "Bronze Dragon Wyrmling", "Carrion Crawler",
        "Cave Bear", "Centaur", "Cult Fanatic", "Druid", "Ettercap", "Faerie Dragon (Blue)", "Faerie Dragon (Green)",
        "Faerie Dragon (Indigo)", "Faerie Dragon (Violet)", "Gargoyle", "Gelatinous Cube", "Ghast", "Giant Boar",
        "Giant Constrictor Snake", "Giant Elk", "Gibbering Mouther", "Githzerai Monk", "Gnoll Pack Lord",
        "Green Dragon Wyrmling", "Grick", "Griffon", "Hunter Shark", "Intellect Devourer", "Lizardfolk Shaman",
        "Merrow", "Mimic", "Minotaur Skeleton", "Myconid Sovereign", "Nothic", "Ochre Jelly", "Ogre", "Ogre Zombie",
        "Orc Eye of Gruumsh", "Orog", "Pegasus", "Pentadrone", "Peryton", "Plesiosaurus", "Polar Bear", "Poltergeist",
        "Priest", "Quaggoth", "Rhinoceros", "Rug of Smothering", "Saber-Toothed Tiger", "Sahuagin Priestess", "Sea Hag",
        "Silver Dragon Wyrmling", "Spined Devil", "Swarm of Poisonous Snakes", "Wererat", "White Dragon Wyrmling",
        "Will-o'-Wisp", "Awakened Zurkhwood", "Chamberlain of Zuggtmoy", "Droki", "Duergar Darkhaft",
        "Duergar Kavalrachni", "Duergar Keeper of the Flame", "Duergar Stone Guard", "Duergar Xarrorn", "Grisha",
        "Narrak", "Vampiric Ixitxachitl", "Vampiric Ixitxachitl Cleric", "Black Earth Guard", "Crushing Wave Priest",
        "Eternal Flame Guardian", "Fathomer", "Howling Hatred Priest", "Hurricane", "Oreioth", "Wiggan Nettlebee",
        "Kavu Predator", "Creepy Doll", "Dragonwing", "Guard Drake", "Purple Wormling", "Uthgardt Shaman",
        "Animated Table", "Belak the Outcast", "Calcryx", "Duergar Spy", "Four-Armed Gargoyle", "Giant Crayfish",
        "Kaarghaz", "Nereid", "Snurrevin", "Thayan Apprentice", "Thayan Warrior", "Asharra", "Hew Hackinstone",
        "Yellow Musk Creeper", "Tortle Druid", "Aurochs", "Bard", "Black Guard Drake", "Blue Guard Drake",
        "Darkling Elder", "Green Guard Drake", "Grung Elite Warrior", "Hobgoblin Iron Shadow", "Meenlock",
        "Orc Claw of Luthic", "Orc Hand of Yurtrus", "Quetzalcoatlus", "Red Guard Drake", "Shadow Mastiff",
        "Vegepygmy Chief", "White Guard Drake", "Yuan-ti Broodguard", "Tissina Khyret", "Laiba \"Nana\" Rosse",
        "Jandar Chergoba", "Kalain", "Lady Gondafrey", "Melannor Fellbranch", "Thrakkus", "Valetta", "Shard Shunner",
        "Fala Lefaliir", "Barnibus Blastwind", "Griffon Cavalry Rider",},
       {"Bulezau", "Deathlock Wight", "Derro Savant", "Duergar Screamer", "Giff", "Merrenoloth", "Ogre Chain Brute",
        "Sword Wraith Warrior", "Vampiric Mist", "Phantom Warrior", "Dralmorrer Borngray", "Pharblex Spattergoo",
        "Mormesk the Wraith", "Ankylosaurus", "Basilisk", "Bearded Devil", "Blue Dragon Wyrmling", "Bugbear Chief",
        "Displacer Beast", "Doppelganger", "Giant Scorpion", "Githyanki Warrior", "Gold Dragon Wyrmling", "Green Hag",
        "Grell", "Hell Hound", "Hobgoblin Captain", "Hook Horror", "Killer Whale", "Knight", "Kuo-toa Monitor",
        "Manticore", "Minotaur", "Mummy", "Nightmare", "Owlbear", "Phase Spider", "Quaggoth Thonot", "Spectator",
        "Veteran", "Water Weird", "Werewolf", "Wight", "Winter Wolf", "Yeti", "Yuan-ti Malison (Type 1)",
        "Yuan-ti Malison (Type 2)", "Yuan-ti Malison (Type 3)", "Deepking Horgar Steelshadow V", "Derro Savant",
        "Hook Horror Spore Servant", "Troglodyte Champion of Laogzed", "Veteran Of The Gauntlet", "Black Earth Priest",
        "Dark Tide Knight", "Eternal Flame Priest", "One-Eyed Shiver", "Skyweaver", "Thurl Merosska", "Windharrow",
        "Serpopard", "Werewolf (Krallenhorde)", "Chupacabra", "Thunderbeast Skeleton", "Yakfolk Warrior",
        "Deathlock Wight", "Giant Ice Toad", "Giant Lightning Eel", "Kalka-Kylla", "Nahual", "Nimira", "Siren",
        "Vampiric Mist", "Ankylosaurus Zombie", "Assassin Vine", "Giant Snapping Turtle", "Girallon Zombie",
        "Tomb Dwarf", "Giant Slug", "Archer", "Cave Fisher", "Choldrith", "Deep Scion", "Flail Snail", "Illusionist",
        "Leucrotta", "Martial Arts Adept", "Neogi", "Orc Red Fang of Shargaas", "Redcap", "Slithering Tracker",
        "Swashbuckler", "Trapper", "Yuan-ti Malison (Type 4)", "Yuan-ti Malison (Type 5)", "Dining Table",
        "Renaer Neverember", "Saeth Cromley", "Zhent Martial Arts Adept",},
       {"Deathlock", "Dybbuk", "Iron Cobra", "Merregon", "Ogre Battering Ram", "Stone Defender", "Azbara Jos",
        "Langdedrosa Cyanwrath", "Banshee", "Black Pudding", "Bone Naga (Guardian)", "Bone Naga (Spirit)", "Chuul",
        "Couatl", "Elephant", "Ettin", "Flameskull", "Ghost", "Gnoll Fang of Yeenoghu", "Helmed Horror", "Incubus",
        "Lamia", "Lizard King", "Lizard Queen", "Orc War Chief", "Red Dragon Wyrmling", "Shadow Demon", "Succubus",
        "Wereboar", "Weretiger", "Chuul Spore Servant", "The Pudding King", "Yestabrod", "Burrowshark",
        "Shoalar Quanderil", "Stonemelder", "Steel Leaf Kavu", "Geist", "Yakfolk Priest", "Giant Subterranean Lizard",
        "Kelpie", "Tecuziztecatl", "Kamadan", "Liara Portyr", "Withers", "Decapus", "Babau", "Barghest", "Girallon",
        "Hobgoblin Devastator", "Neogi Master", "Orc Blade of Ilneval", "Stegosaurus", "Warlock of the Archfey",
        "Yeth Hound", "Yuan-ti Mind Whisperer", "Yuan-ti Nightmare Speaker", "Soluun Xibrindas", "Drow Gunslinger",
        "Jalester Silvermane", "Nimblewright",},
       {"Adult Oblex", "Allip", "Kruthik Hive Lord", "Oaken Bolter", "Star Spawn Mangler", "Izek Strazni", "Rictavio",
        "Captain Othelstan", "Talis the White", "Air Elemental", "Barbed Devil", "Barlgura", "Beholder Zombie",
        "Bulette", "Cambion", "Drow Elite Warrior", "Earth Elemental", "Fire Elemental", "Flesh Golem",
        "Giant Crocodile", "Giant Shark", "Gladiator", "Gorgon", "Half-Red Dragon Veteran", "Hill Giant", "Mezzoloth",
        "Night Hag", "Otyugh", "Red Slaad", "Revenant", "Roper", "Sahuagin Baron", "Salamander", "Shambling Mound",
        "Triceratops", "Troll", "Umber Hulk", "Unicorn", "Vampire Spawn", "Water Elemental", "Werebear", "Wraith",
        "Xorn", "Young Remorhaz", "Elizar Dryflagon", "Hellenrae", "Razerblast", "Manticore, Heart-Piercer", "Skaab",
        "Vampire Neonate", "Felidar", "Dragonfang", "Chief Guh", "Hulking Crab", "Greater Zombie", "Sea Lion", "Snarla",
        "Tloques-Popolocas", "Clay Gladiator", "Dragonbait", "Tomb Guardian", "Banderhobb", "Brontosaurus",
        "Catoblepas", "Enchanter", "Kraken Priest", "Master Thief", "Mindwitness", "Spawn of Kyuss",
        "Swarm of Cranium Rats", "Tanarukk", "Tlincalli", "Transmuter", "Wood Woad", "Yuan-ti Pit Master", "Obliteros",
        "Ammalia Cassalanter", "Black Viper", "Hrabbaz",},
       {"Duergar Warlord", "White Abishai", "Strahd's Animated Armor", "Trepsin", "Chasme", "Chimera", "Cyclops",
        "Drider", "Galeb Duhr", "Githzerai Zerth", "Hobgoblin Warlord", "Invisible Stalker", "Kuo-toa Archpriest",
        "Mage", "Mammoth", "Medusa", "Vrock", "Wyvern", "Young Brass Dragon", "Young White Dragon", "Flamewrath",
        "Miraj Vizann", "Rath Modar", "Centaur Mummy", "Spiked Tomb Guardian", "Annis Hag", "Bodak", "Conjurer",
        "Gauth", "Mouth of Grolantor", "Warlock of the Great Old One", "Kaevja Cynavern", "Manafret Cherryport",
        "Losser Mirklav", "Rishaal", "Davil Starsong", "Skeemo Weirdbottle",},
       {"Air Elemental Myrmidon", "Armanite", "Black Abishai", "Dhergoloth", "Earth Elemental Myrmidon",
        "Fire Elemental Myrmidon", "Maurezhi", "Shadow Dancer", "The Lost", "Venom Troll", "Water Elemental Myrmidon",
        "Tree Blight", "Vladimir Horngaard", "Rezmir", "Blue Slaad", "Drow Mage", "Giant Ape", "Grick Alpha",
        "Mind Flayer", "Oni", "Shield Guardian", "Stone Giant", "Young Black Dragon", "Young Copper Dragon",
        "Yuan-ti Abomination", "Aerisi Kalinoth", "Air Elemental Myrmidon", "Drannin Splithelm",
        "Earth Elemental Myrmidon", "Fire Elemental Myrmidon", "Ghald", "Water Elemental Myrmidon", "Dragonsoul",
        "Thane Kayalithica", "Giant Skeleton", "Artus Cimber", "Ras Nsi", "Xandala", "Bheur Hag", "Draegloth", "Korred",
        "Warlock of the Fiend", "Nar'l Xibrindas",},
       {"Canoloth", "Corpse Flower", "Deathlock Mastermind", "Howler", "Sword Wraith Commander", "Ezmerelda d'Avenir",
        "Assassin", "Chain Devil", "Cloaker", "Drow Priestess of Lolth", "Fomorian", "Frost Giant", "Githyanki Knight",
        "Green Slaad", "Hezrou", "Hydra", "Mind Flayer Arcanist", "Spirit Naga", "Tyrannosaurus Rex",
        "Young Bronze Dragon", "Young Green Dragon", "Bastian Thermandar", "Marlos Urnrayle", "Jarl Storvald",
        "Huge Giant Crab", "Bag of Nails", "King of Feathers", "Tyrannosaurus Zombie", "Zindar", "Blackguard",
        "Diviner", "Mind Flayer Psion", "Shoosuva", "Manshoon Simulacrum", "Urstul Floxin", "Istrid Horn",
        "Ziraj the Hunter",},
       {"Drow House Captain", "Frost Salamander", "Gloom Weaver", "Hydroloth", "Rot Troll", "The Lonely", "Blagothkus",
        "Spider Shark", "Abominable Yeti", "Bone Devil", "Clay Golem", "Cloud Giant", "Fire Giant", "Glabrezu",
        "Gray Slaad", "Nycaloth", "Treant", "Young Blue Dragon", "Young Silver Dragon", "Gar Shatterkeel", "Vanifer",
        "Neronvain", "Duke Zalto", "Harshnag", "Abjurer", "Champion", "Evoker", "Flind", "Necromancer", "Ulitharid",
        "War Priest", "Ahmaergo", "Durnan", "Meloon Wardragon", "Mirt", "Remallia Haventree", "Tashlyn Yafeera",},
       {"Autumn Eladrin", "Elder Oblex", "Githyanki Gish", "Githzerai Enlightened", "Orthon", "Spring Eladrin",
        "Star Spawn Hulk", "Summer Eladrin", "Winter Eladrin", "Madam Eva", "Rahadin", "Aboleth", "Death Slaad", "Deva",
        "Guardian Naga", "Stone Golem", "Yochlol", "Young Gold Dragon", "Young Red Dragon", "Sky Leviathan",
        "Gishath, Sun's Avatar", "Archon Of Redemption", "Malformed Kraken", "Ooze Master", "White Maw",
        "Giant Four-Armed Gargoyle", "Alhoon", "Death Kiss", "Froghemoth", "Stone Giant Dreamwalker",
        "Victoro Cassalanter",},
       {"Alkilith", "Balhannoth", "Drow Shadowblade", "Soul Monger", "Spirit Troll", "The Hungry", "Yagnoloth",
        "Baba Lysaga", "Baba Lysaga's Creeping Hut", "Behir", "Dao", "Djinni", "Efreeti", "Gynosphinx", "Horned Devil",
        "Marid", "Remorhaz", "Roc", "Naergoth Bladelord", "Severin", "Countess Sansuri", "Cloud Giant Smiling One",
        "Morkoth",},
       {"Boneclaw", "Duergar Despot", "Eidolon", "Githyanki Kith'rak", "Gray Render", "Oinoloth", "Arcanaloth",
        "Archmage", "Erinyes", "Stone Juggernaut", "Archdruid", "Frost Giant Everlasting One", "Ki-rin", "Warlord",
        "Yuan-ti Anathema",},
       {"Dire Troll", "Drow Arachnomancer", "Narzugon", "Star Spawn Seer", "The Angry", "Wastrilith",
        "Adult Brass Dragon", "Adult White Dragon", "Beholder", "Nalfeshnee", "Rakshasa", "Storm Giant", "Ultroloth",
        "Vampire", "Young Red Shadow Dragon", "Criosphinx", "Sunbird", "Kraken", "King Hekaton", "Zephyros",
        "Tarul Var", "Atropal", "Devourer", "Neothelid", "Manshoon", "Vajra Safahr",},
       {"Cadaver Collector", "Drow Inquisitor", "Githyanki Supreme Commander", "Retriever", "Adult Black Dragon",
        "Adult Copper Dragon", "Death Tyrant", "Ice Devil", "Ice Devil Spear", "Elder Brain",
        "Fire Giant Dreadnought",},
       {"Green Abishai", "Nabassu", "Skull Lord", "Strahd von Zarovich", "Adult Bronze Dragon", "Adult Green Dragon",
        "Mummy Lord", "Purple Worm", "Vampire Spellcaster", "Vampire Warrior", "Jarlaxle Baenre",},
       {"Githzerai Anarch", "Hellfire Engine", "Phoenix", "Star Spawn Larva Mage", "Steel Predator", "Titivilus",
        "Adult Blue Dragon", "Adult Silver Dragon", "Iron Golem", "Marilith", "Planetar", "Storm Giant Quintessent",
        "Hlam",},
       {"Blue Abishai", "Nagpa", "Adult Blue Dracolich", "Adult Gold Dragon", "Adult Red Dragon", "Androsphinx",
        "Death Knight", "Dragon Turtle", "Goristro", "Laeral Silverhand",},
       {"Amnizu", "Drow Favored Consort", "Sibriex", "Demilich", "Olhydra", "Yan-C-Bin",
        "Walking Statue of Waterdeep",}, {"Bael", "Red Abishai", "Balor", "Imix",},
       {"Drow Matron Mother", "Leviathan", "Nightwalker", "Ancient Brass Dragon", "Ancient White Dragon", "Pit Fiend",
        "Ogrémoch",},
       {"Astral Dreadnought", "Hutijin", "Moloch", "Molydeus", "Acererak Demilich", "Ancient Black Dragon",
        "Ancient Copper Dragon", "Lich", "Solar", "Valindra Shadowmantle",},
       {"Geryon", "Zaratan", "Ancient Bronze Dragon", "Ancient Green Dragon", "Illithilich",},
       {"Baphomet", "Elder Tempest", "Fraz-Urb'luu", "Juiblex", "Zuggtmoy", "Ancient Blue Dragon",
        "Ancient Silver Dragon", "Empyrean", "Kraken", "Baphomet", "Fraz-Urb'luu", "Juiblex", "Zuggtmoy",
        "Iymrith, Ancient Blue Dragon", "Maegera the Dawn Titan", "Acererak",},
       {"Graz'zt", "Yeenoghu", "Ancient Gold Dragon", "Ancient Red Dragon", "Graz'zt", "Yeenoghu",},
       {"Marut", "Klauth", "Slarkrethel",}, {"Demogorgon", "Orcus", "Zariel", "Demogorgon", "Orcus",}, {}, {}, {},
       {"Tarrasque", "Elder Dinosaur", "Elder Dinosaur (Etali, Primal Storm)", "Elder Dinosaur (Ghalta, Primal Hunger)",
        "Elder Dinosaur (Nezahal, Primal Tide)", "Elder Dinosaur (Tetzimoc, Primal Death)",
        "Elder Dinosaur (Zacama, Primal Calamity)", "Elder Dinosaur (Zetalpa, Primal Dawn)", "Tiamat",},
       {"Sacred Statue", "Avatar of Death", "Animated Object (Huge)", "Animated Object (Large)",
        "Animated Object (Medium)", "Animated Object (Small)", "Animated Object (Tiny)", "Tiny Servant",}};
  vector<vector<string>> Source = {
      {"DMG", "DMG", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM",
       "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "PSK", "SKT", "SKT",
       "SKT", "SKT", "SKT", "SKT", "SKT", "SKT", "SKT", "SKT", "SKT", "SKT", "SKT", "SKT", "SKT", "SKT", "SKT", "SKT",
       "SKT", "ToA", "ToA", "ToA", "VGM", "WDH", "WDH", "WDH", "WDH", "WDH", "WDH",},
      {"MTF", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM",
       "MM", "MM", "MM", "MM", "MM", "MM", "MM", "OotA", "OotA", "PotA", "SKT", "ToA", "VGM", "VGM", "VGM", "VGM",
       "VGM", "WDH", "WDH", "WDH",},
      {"MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "CoS", "CoS", "CoS", "LMoP", "MM", "MM", "MM", "MM", "MM", "MM",
       "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM",
       "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM",
       "OotA", "OotA", "OotA", "OotA", "OotA", "OotA", "TftYP", "TftYP", "TftYP", "ToA", "ToA", "ToA", "ToA", "TTP",
       "TTP", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "WDH", "WDH",
       "WDH", "WDH", "WDH", "WDH",},
      {"MTF", "MTF", "CoS", "HotDQ", "LMoP", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM",
       "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM",
       "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "OotA", "OotA", "OotA", "PotA", "PotA", "PSK", "PSX",
       "TftYP", "TftYP", "TftYP", "ToA", "ToA", "ToA", "TTP", "UAWGE", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM",
       "WDH", "WDH", "WDH", "WDH",},
      {"MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "CoS", "CoS", "HotDQ", "LMoP", "LMoP", "MM", "MM", "MM", "MM", "MM",
       "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM",
       "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "OotA", "OotA", "OotA",
       "OotA", "PotA", "PSD", "RoT", "RoT", "SKT", "SKT", "Stream", "TftYP", "TftYP", "TftYP", "TftYP", "ToA", "ToA",
       "ToA", "ToA", "ToA", "ToA", "ToA", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM",
       "VGM", "VGM", "VGM",},
      {"MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "CoS", "HotDQ", "LMoP", "MM", "MM",
       "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM",
       "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM",
       "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM",
       "MM", "MM", "MM", "OotA", "OotA", "OotA", "OotA", "OotA", "OotA", "OotA", "OotA", "OotA", "OotA", "OotA", "OotA",
       "PotA", "PotA", "PotA", "PotA", "PotA", "PotA", "PotA", "PotA", "PSD", "PSI", "RoT", "RoT", "SKT", "SKT",
       "TftYP", "TftYP", "TftYP", "TftYP", "TftYP", "TftYP", "TftYP", "TftYP", "TftYP", "TftYP", "TftYP", "ToA", "ToA",
       "ToA", "TTP", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM",
       "VGM", "VGM", "VGM", "WDH", "WDH", "WDH", "WDH", "WDH", "WDH", "WDH", "WDH", "WDH", "WDH", "WDH", "WDH",},
      {"MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "CoS", "HotDQ", "HotDQ", "LMoP", "MM", "MM", "MM",
       "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM",
       "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "OotA", "OotA", "OotA", "OotA",
       "OotA", "PotA", "PotA", "PotA", "PotA", "PotA", "PotA", "PotA", "PSA", "PSI", "PSX", "SKT", "SKT", "TftYP",
       "TftYP", "TftYP", "TftYP", "TftYP", "TftYP", "TftYP", "TftYP", "ToA", "ToA", "ToA", "ToA", "ToA", "TTP", "VGM",
       "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "WDH",
       "WDH", "WDH", "WDH",},
      {"MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "HotDQ", "HotDQ", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM",
       "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "OotA", "OotA", "OotA", "PotA",
       "PotA", "PotA", "PSD", "PSI", "SKT", "TftYP", "TftYP", "TftYP", "ToA", "ToA", "ToA", "TTP", "VGM", "VGM", "VGM",
       "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "WDH", "WDH", "WDH", "WDH",},
      {"MTF", "MTF", "MTF", "MTF", "MTF", "CoS", "CoS", "HotDQ", "HotDQ", "MM", "MM", "MM", "MM", "MM", "MM", "MM",
       "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM",
       "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "PotA", "PotA", "PotA", "PSA", "PSI", "PSI", "PSZ", "RoT",
       "SKT", "SKT", "TftYP", "TftYP", "TftYP", "TftYP", "ToA", "ToA", "ToA", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM",
       "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "WDH", "WDH", "WDH", "WDH",},
      {"MTF", "MTF", "CoS", "HotDQ", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM",
       "MM", "MM", "PotA", "PotA", "RoT", "TftYP", "ToA", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "WDH", "WDH", "WDH",
       "WDH", "WDH", "WDH",},
      {"MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "CoS", "CoS", "HotDQ", "MM", "MM",
       "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "PotA", "PotA", "PotA", "PotA", "PotA", "PotA", "PotA",
       "RoT", "SKT", "TftYP", "ToA", "ToA", "ToA", "VGM", "VGM", "VGM", "VGM", "WDH",},
      {"MTF", "MTF", "MTF", "MTF", "MTF", "CoS", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM",
       "MM", "MM", "MM", "PotA", "PotA", "SKT", "TftYP", "ToA", "ToA", "ToA", "ToA", "VGM", "VGM", "VGM", "VGM", "WDH",
       "WDH", "WDH", "WDH",},
      {"MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "HotDQ", "Mag", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM",
       "MM", "MM", "PotA", "PotA", "RoT", "SKT", "SKT", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "VGM", "WDH", "WDH",
       "WDH", "WDH", "WDH", "WDH",},
      {"MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "CoS", "CoS", "MM", "MM", "MM", "MM", "MM", "MM",
       "MM", "MM", "PSK", "PSX", "PSZ", "TftYP", "TftYP", "TftYP", "ToA", "VGM", "VGM", "VGM", "VGM", "WDH",},
      {"MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "CoS", "CoS", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM",
       "MM", "RoT", "RoT", "SKT", "VGM", "VGM",},
      {"MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "MM", "MM", "MM", "ToA", "VGM", "VGM", "VGM", "VGM", "VGM",},
      {"MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "PSA", "PSX",
       "PSZ", "SKT", "SKT", "TftYP", "ToA", "VGM", "VGM", "WDH", "WDH",},
      {"MTF", "MTF", "MTF", "MTF", "MM", "MM", "MM", "MM", "MM", "VGM", "VGM",},
      {"MTF", "MTF", "MTF", "CoS", "MM", "MM", "MM", "MM", "MM", "MM", "WDH",},
      {"MTF", "MTF", "MTF", "MTF", "MTF", "MTF", "MM", "MM", "MM", "MM", "MM", "VGM", "WDH",},
      {"MTF", "MTF", "MM", "MM", "MM", "MM", "MM", "MM", "MM", "WDH",},
      {"MTF", "MTF", "MTF", "MM", "PotA", "PotA", "WDH",}, {"MTF", "MTF", "MM", "PotA",},
      {"MTF", "MTF", "MTF", "MM", "MM", "MM", "PotA",},
      {"MTF", "MTF", "MTF", "MTF", "MM", "MM", "MM", "MM", "MM", "ToA",}, {"MTF", "MTF", "MM", "MM", "VGM",},
      {"MTF", "MTF", "MTF", "MTF", "MTF", "MM", "MM", "MM", "MM", "OotA", "OotA", "OotA", "OotA", "SKT", "SKT", "ToA",},
      {"MTF", "MTF", "MM", "MM", "OotA", "OotA",}, {"MTF", "SKT", "SKT",}, {"MTF", "MTF", "MTF", "OotA", "OotA",}, {},
      {}, {}, {"MM", "PSX", "PSX", "PSX", "PSX", "PSX", "PSX", "PSX", "RoT",},
      {"MTF", "DMG", "PHB", "PHB", "PHB", "PHB", "PHB", "XGE",}};
};

struct Monster_Parameters_Names{
  vector <string> intVar = {"maxhealth", "health", "health_dice", "health_dice_num", "health_modifier", "armor_class", "speed[0]", "speed[1]", "speed[2]", "speed[3]", "Str", "Dex", "Con", "Int", "Wis", "Cha", "passive_perception", "legendaryActions"};
  vector <string> boolVar = {"canHover", "isNamedCreature"};
  vector <string> stringVar = {"monster_name", "size", "challenge_rating", "hpFormula", "type_s", "fly_condition", "saving_throws[0]", "saving_throws[1]", "saving_throws[2]", "saving_throws[3]", "saving_throws[4]", "saving_throws[5]", "skillString[0]", "skillString[1]", "skillString[2]", "skillString[3]", "skillString[4]", "skillString[5]", "skillString[6]", "skillString[7]", "skillString[8]", "skillString[9]", "skillString[10]", "skillString[11]", "skillString[12]", "skillString[13]", "skillString[14]", "skillString[15]", "skillString[16]", "skillString[17]", "legendaryGroup"};
  vector <string> vectorStringVar = {"type_tags", "alignment", "acFrom", "resistance", "resistance_note", "immune", "conditionImune", "senses", "languages", "trait", "action", "legendary", "spellcastingNameAndEntries", "spellcasting_will", "traitTags", "actionTags", "languageTags", "senseTags", "variant"};
};

class Monster : public Creature {
 private:
  string monster_name;
  //int experience_if_killed;
  string size;
  string challenge_rating;
  string type_s;
  string subtype;
  vector <string> type_tags;
  string source;
  vector <string> alignment;
  vector <string> skillString;
  vector <string> saving_throws;
  vector <string> acFrom;
  int Ability_Save[kAbilities_Num];
  bool damage_vulnerabilities[kDamage_Types];
  //vector<string> entries;

 public:

  Monster();

  Monster(Random_Generator_ *Rand_gen, int name_index, int challenge_rating_index);

  Monster(Random_Generator_ *Rand_gen, const Monster &another);

  Monster(int type_, int level_, int hp, int armor_class_);

  int GetInt(int whatToShow);

  string GetString(int whatToShow);

  vector<string> GetVectorString(int whatToShow);

  vector<SpellAndUsageTimes> GetSpellAndUsageTimes(int whatToShow);

  bool GetBool(int whatToShow);

  void SetInt(int whatToSet, int value);

  void SetString(int whatToSet, string value);

  void SetVectorString(int whatToSet, vector<string> value);

  void SetSpellAndUsageTimes(int whatToSet, vector<SpellAndUsageTimes> &value);

  void SetBool(int whatToSet, bool value);

  const nlohmann::basic_json<> Save();

  ~Monster();

  bool Load(const nlohmann::basic_json<> &j);
};

#endif //ANOTHER_DND_SIMULATOR_MONSTER_H
