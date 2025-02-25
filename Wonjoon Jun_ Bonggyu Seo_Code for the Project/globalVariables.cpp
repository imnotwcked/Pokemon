/****************************************************************************
* File:   globalVariables.cpp globalVariables.h
* Author:   Wonjoon Jun and Bonggyu Seo
* Purpose: To store information about global variables. The global variables are
           used in the situation where the if statements check for the string
           to prevent typos from falsifying the logic we use global variables
* Version: Final Version Nov 19, 2023
* Resources:
*******************************************************************************/
#include <string>
#include "globalVariable.h"

using namespace std;

const string ENDOFONEPOKEMON = "THIS IS THE END OF ONE POKEMON";

//Name of Types:
const string NORMAL = "Normal";
const string FIGHTING = "Fighting";
const string FLYING = "Flying";
const string POISON = "Poison";
const string GROUND = "Ground";
const string ROCK = "Rock";
const string BUG = "Bug";
const string GHOST = "Ghost";
const string STEEL = "Steel";
const string FIRE = "Fire";
const string WATER = "Water";
const string GRASS = "Grass";
const string ELECTRIC = "Electric";
const string PSYCHIC = "Psychic";
const string ICE = "Ice";
const string DRAGON = "Dragon";
const string DARK = "Dark";
const string FAIRY = "Fairy";

//Name of Attacks:
const string BITE = "Bite";
const string TACKLE = "Tackle";
const string AQUATAIL = "Aqua Tail";
const string EARTHQUAKE = "Earthquake";
const string THUNDERBOLT = "Thunderbolt";
const string FIREBLAST = "Fire Blast";
const string DRAGONPULSE = "Dragon Pulse";
const string STONEEDGE = "Stone Edge";
const string ACROBATICS = "Acrobatics";
const string AEROBLAST = "Aero Blast";
const string AIRCUTTER = "Air Cutter";
const string AIRSLASH = "Air Slash";
const string ANCHORSHOT = "Anchor Shot";
const string ANCIENTPOWER = "Ancient Power";
const string APPLEACID = "Apple Acid";
const string AQUACUTTER = "Aqua Cutter";
const string AQUAJET = "Aqua Jet";
const string AQUASTEP = "Aqua Step";
const string ARMTHRUST = "Arm Thrust";
const string ARMORCANNON = "Armor Cannon";
const string ASSURANCE = "Assurance";
const string ASTONISH = "Astonish";
const string ASTRALBARRAGE = "Astral Barrage";
const string ATTACKORDER = "Attack Order";
const string AURASPHERE = "Aura Sphere";
const string RAZORLEAF = "Razor leaf";
const string GIGADRAIN = "Giga drain";
const string VINEWHIP = "Vine whip";
const string GRASSKNOT = "Grass knot";
const string LEAFBLADE = "Leaf Blade";
const string BLIZZARD = "Blizzard";
const string ICEBEAM = "Icebeam";
const string SURF = "Surf";
const string TAKEDOWN = "Takedown";
const string FURYSWIPES = "Fury Swipes";
const string FLAMETHROWER = "Flamethrower";
const string CRUNCH = "Crunch";
const string RAGINGFURY = "Raging Fury";
const string FIREFANG = "Fire Fang";
const string FLAREBLITZ = "Flare Blitz";
const string HIGHJUMPKICK = "High Jump Kick";
const string FIRESPIN = "Fire spin";
const string LOWKICK = "Low Kick";
const string HIGHHORSEPOWER = "High Horsepower";
const string ACIDSPRAY = "Acid Spray";
string ARRAYOFATTACKNAMES[] = {BITE, TACKLE, AQUATAIL, EARTHQUAKE, THUNDERBOLT, FIREBLAST, DRAGONPULSE, STONEEDGE,
                               ACROBATICS, AEROBLAST, AIRCUTTER, AIRSLASH, ANCHORSHOT, ANCIENTPOWER, APPLEACID,
                               AQUACUTTER, AQUAJET, AQUASTEP, ARMTHRUST, ARMORCANNON, ASSURANCE, ASTONISH,
                               ASTRALBARRAGE, ATTACKORDER, AURASPHERE, RAZORLEAF, GIGADRAIN, VINEWHIP, GRASSKNOT,
                               LEAFBLADE,
                               BLIZZARD, ICEBEAM, SURF, TAKEDOWN, FURYSWIPES, FLAMETHROWER, CRUNCH, RAGINGFURY,
                               FIREFANG, FLAREBLITZ, HIGHJUMPKICK, FIRESPIN, LOWKICK, HIGHHORSEPOWER, ACIDSPRAY};
//Names of gymLeader:
const string AQUA = "Aqua";
const string BLAZE = "Blaze";
const string BLOSSOM = "Blossom";

//Name of the pokemon master:
const string MASTERNAME = "M";

//Value of escape character
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string BLUE = "\033[34m";