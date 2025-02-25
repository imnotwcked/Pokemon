/****************************************************************************
* File:   pokemon.cpp pokemon.h
* Author:   Wonjoon Jun and Bonggyu Seo
* Purpose: This stores information about the pokemon class and functions required to
           run the functions within pokemon class.
* Version: Final Version Nov 19, 2023
* Resources: line 405 const_cast<string &> Received aid from chat.open.ai on Nov 01
*           line 23 and 24, values needed for creating pokemon came from:
*           //https://pokemondb.net/pokedex/all and
*           //https://www.eurogamer.net/pokemon-sun-and-moon-competitive-training-guide-how-to-raise-the-best-strongest-pokemon-for-competitive-play-4925?page=3#:~:text=IVs%20(Individual%20Values)%20%2D%20the,dictate's%20a%20Pok%C3%A9mon's%20final%20stats.
*           line 148: the information was obtaine from:
*           //calculation obtained from https://bulbapedia.bulbagarden.net/wiki/Stat
*           line 253: the information was obtained from
*           https://www.ign.com/wikis/pokemon-gold-silver-crystal-version/Pokemon_Types
*******************************************************************************/
#include "pokemon.h"
#include "globalVariable.h"
#include <sstream>
#include <fstream>

using namespace std;

//https://pokemondb.net/pokedex/all
//https://www.eurogamer.net/pokemon-sun-and-moon-competitive-training-guide-how-to-raise-the-best-strongest-pokemon-for-competitive-play-4925?page=3#:~:text=IVs%20(Individual%20Values)%20%2D%20the,dictate's%20a%20Pok%C3%A9mon's%20final%20stats.
Pokemon::Pokemon(const string &name, const string &filename, const Attacks &a1, const Attacks &a2, const Attacks &a3,
                 const Attacks &a4, int base1, int base2, int base3, int base4, int base5, int base6,
                 const string &type1, const string &type2, int lvl)
        : name(name), asciiFileName(filename), tp(type1, type2),
          IV1(randGen(1, 31)), IV2(randGen(1, 31)),
          IV3(randGen(1, 31)), IV4(randGen(1, 31)),
          IV5(randGen(1, 31)), IV6(randGen(1, 31)),
          baseHP(base1), baseAttack(base2), baseDefense(base3),
          baseSpAttack(base4),
          baseSPDefense(base5),
          baseSpeed(base6), level(lvl), EV(0), xp(0) {
    level > 100 ? level = 100 : level;
    abilities[0] = a1;
    abilities[1] = a2;
    abilities[2] = a3;
    abilities[3] = a4;
    maxHP = (((2 * base1 + IV1 + EV / 4 + 100) * level) / 100 + 10);
    attack = (((((2 * base2 + IV2 + EV / 4 + 100) * level) / 100 + 10) > 252) ? 252 : (
            ((2 * base2 + IV2 + EV / 4 + 100) * level) / 100 + 10));
    defense = (((((2 * base3 + IV3 + EV / 4 + 100) * level) / 100 + 10) > 252) ? 252 : (
            ((2 * base3 + IV3 + EV / 4 + 100) * level) / 100 + 10));
    specialAttack = (((((2 * base4 + IV4 + EV / 4 + 100) * level) / 100 + 10) > 252) ? 252 : (
            ((2 * base4 + IV4 + EV / 4 + 100) * level) / 100 + 10));
    specialDefense = (((((2 * base5 + IV5 + EV / 4 + 100) * level) / 100 + 10) > 252) ? 252 : (
            ((2 * base5 + IV5 + EV / 4 + 100) * level) / 100 + 10));
    speed = (((((2 * base6 + IV6 + EV / 4 + 100) * level) / 100 + 10) > 252) ? 252 : (
            ((2 * base6 + IV6 + EV / 4 + 100) * level) / 100 + 10));
    currentHP = maxHP;
    fainted = false;
    catchRate = 50;
}


void Attacks::displayAttackStats() {
    if (name != "NULL") {
        cout << name << endl;
        cout << "Type: " << attackType << endl;
        cout << (isAttack ? "Attack" : "Special Attack") << endl;
        cout << "Power: " << attackPower << endl;
        cout << "Accuracy: " << accuracy << endl;
        cout << "Max maxPP: " << maxPP << endl;
        if (!(weakAgainst.empty())) {
            cout << "1/2 damage against: ";
            for (string i: weakAgainst) {
                cout << i << " ";
            }
            cout << endl;
        }
        if (!(strongAgainst.empty())) {
            cout << "2x damage against: ";
            for (string i: strongAgainst) {
                cout << i << " ";
            }
            cout << endl;
        }
        if (!(immuneAgainst.empty())) {
            cout << "Immune against: ";
            for (string i: immuneAgainst) {
                cout << i << " ";
            }
            cout << endl;
        }
        pressToContinue();
        cout << endl;
    }
}

Pokemon::Pokemon(const string &filename, const string &name, const int &currentHP, const string &type1,
                 const string &type2, int IVHP, int IVATK, int IVDEF, int IVSPATK, int IVSPDEF, int IVSPE, int lvl, int EV, int XP,
                 const Attacks &a1, const Attacks &a2, const Attacks &a3, const Attacks &a4, int base1, int base2,
                 int base3, int base4, int base5,
                 int base6)
        : name(name), asciiFileName(filename), currentHP(currentHP), tp(type1, type2),
          IV1(IVHP), IV2(IVATK),
          IV3(IVDEF), IV4(IVSPATK),
          IV5(IVSPDEF), IV6(IVSPE),
          level(lvl),
          EV(EV),
          xp(XP),
          baseHP(base1), baseAttack(base2), baseDefense(base3),
          baseSpAttack(base4),
          baseSPDefense(base5),
          baseSpeed(base6) {
    abilities[0] = a1;
    abilities[1] = a2;
    abilities[2] = a3;
    abilities[3] = a4;
    maxHP = (((2 * base1 + IV1 + EV / 4 + 100) * level) / 100 + 10);
    attack = (((((2 * base2 + IV2 + EV / 4 + 100) * level) / 100 + 10) > 252) ? 252 : (
            ((2 * base2 + IV2 + EV / 4 + 100) * level) / 100 + 10));
    defense = (((((2 * base3 + IV3 + EV / 4 + 100) * level) / 100 + 10) > 252) ? 252 : (
            ((2 * base3 + IV3 + EV / 4 + 100) * level) / 100 + 10));
    specialAttack = (((((2 * base4 + IV4 + EV / 4 + 100) * level) / 100 + 10) > 252) ? 252 : (
            ((2 * base4 + IV4 + EV / 4 + 100) * level) / 100 + 10));
    specialDefense = (((((2 * base5 + IV5 + EV / 4 + 100) * level) / 100 + 10) > 252) ? 252 : (
            ((2 * base5 + IV5 + EV / 4 + 100) * level) / 100 + 10));
    speed = (((((2 * base6 + IV6 + EV / 4 + 100) * level) / 100 + 10) > 252) ? 252 : (
            ((2 * base6 + IV6 + EV / 4 + 100) * level) / 100 + 10));
    (currentHP > 0) ? (fainted = false) : (fainted = true);
    catchRate = 50;
}


void Pokemon::display() {
    printFile(asciiFileName, "Unable to print " + name);
    cout << "Name: " << name << endl;
    cout << "Level: " << level << endl;
    cout << "Type: " << tp.getType1() << ((!tp.getType2().empty()) ? " " + tp.getType2() : "") << endl;
    cout << "Max HP: " << maxHP << endl;
    cout << "Attack: " << attack << endl;
    cout << "Defense: " << defense << endl;
    cout << "Special Attack: " << specialAttack << endl;
    cout << "Special Defense: " << specialDefense << endl;
    cout << "Speed: " << speed << endl;
    string input = getYN("Do you want to display information about abilities? (y/n): ");
    if (input == "y") {
        for (Attacks i: abilities) {
            i.displayAttackStats();
            cout << endl;
        }
    }
}

//calculation obtained from https://bulbapedia.bulbagarden.net/wiki/Stat
void Pokemon::updateStats() {
    maxHP = (((2 * baseHP + IV1 + EV / 4 + 100) * level) / 100 + 10);
    attack = (((((2 * baseAttack + IV2 + EV / 4 + 100) * level) / 100 + 10)> 252) ? 252 : (
            ((2 * baseAttack + IV2 + EV / 4 + 100) * level) / 100 + 10));
    defense = (((((2 * baseDefense + IV3 + EV / 4 + 100) * level) / 100 + 10) > 252) ? 252 : (
            ((2 * baseDefense + IV3 + EV / 4 + 100) * level) / 100 + 10));
    specialAttack = (((((2 * baseSpAttack + IV4 + EV / 4 + 100) * level) / 100 + 10) > 252) ? 252 : (
            ((2 * baseSpAttack + IV4 + EV / 4 + 100) * level) / 100 + 10));
    specialDefense = (((((2 * baseSPDefense + IV5 + EV / 4 + 100) * level) / 100 + 10) > 252) ? 252 : (
            ((2 * baseSPDefense + IV5 + EV / 4 + 100) * level) / 100 + 10));
    speed = (((((2 * baseSpeed + IV6 + EV / 4 + 100) * level) / 100 + 10) > 252) ? 252 : (
            ((2 * baseSpeed + IV6 + EV / 4 + 100) * level) / 100 + 10));
    (currentHP > 0) ? (fainted = false) : (fainted = true);
}


Attacks Pokemon::selectAttack() {
    int index(0);
    vector<Attacks> attacks;
    int remainingTotalPP(0);
    for (Attacks i: abilities) {
        remainingTotalPP += i.getCurrentPP();
    }
    if (remainingTotalPP <= 0) {
        cout << "You have no remaining PP!" << endl;
        return EmptyAttack();
    }
    for (Attacks &i: abilities) {
        if (i.getName() != "" && i.getCurrentPP() > 0) {
            ++index;
            cout << index << ". " << i.getName() << " [" << i.getCurrentPP() << '/' << i.getMaxPP() << "] "
                 << endl;
            attacks.push_back(i);
        }
    }
    cout << "Choose your move! ";
    Attacks userChoice = attacks[getInt(1, attacks.size()) - 1];
    cout << endl;
    for (Attacks &i: abilities) {
        if (i.getName() == userChoice.getName()) {
            i.decrementCurrentPP();
        }
    }
    return userChoice;
}

void Pokemon::swapAttack(const Attacks &a) {
    int order(1);
    int userInput;
    cout << "What abilities do you want to swap with " << a.getName() << endl;
    for (Attacks &i: abilities) {
        cout << order << ". " << i.getName() << endl;
        ++order;
    }
    userInput = getInt(1, 4);
    if (!abilities[userInput - 1].getName().empty()) {
        cout << "Successfully swapped " << abilities[userInput - 1].getName() << " with " << a.getName() << "!"
             << endl;
        abilities[userInput - 1] = a;
    } else {
        cout << "Successfully added " << a.getName() << " to list of abilities!" << endl;
        abilities[userInput - 1] = a;
    }
}

void Pokemon::displayCurrentHPandLevel(bool isEnemy) const {
    float healthPercentage = float(currentHP) / float(maxHP) * 100;
    if (isEnemy) {
        cout << width(72) << currentHP << " / " << maxHP << "            Level: " << level << endl;
    } else {
        cout << currentHP << " / " << maxHP << "            Level: " << level << endl;
    }
    cout << "[";
    for (int i = 0; i < 100; ++i) {
        if (int(healthPercentage) > i) {
            cout << "|";
        } else {
            cout << " ";
        }
    }
    cout << "]" << endl << endl;
}

int Player::monsterBall = 10;
int Player::superBall = 5;
int Player::money = 5000;
int Player::masterBall = 3;
bool Player::greenBadge = false;
bool Player::blueBadge = false;
bool Player::redBadge = false;
bool Player::loadingTheGameInAWhile = true;

Player::Player(string name, int money, int mb, int sb, int master, bool RB, bool GB, bool BB) : name(name) {
    Player::setMoney(money);
    Player::setMonsterBall(mb);
    Player::setMasterBall
            (master);
    Player::setSuperBall(sb);
    Player::setRedBadge(RB);
    Player::setGreenBadge(GB);
    Player::setBlueBadge(BB);
}

//obtained from: https://www.ign.com/wikis/pokemon-gold-silver-crystal-version/Pokemon_Types
Attacks::Attacks(const string &name, string at, bool isAttack, int ap, int acc, int pp) : name(name), attackPower(ap),
                                                                                          accuracy(acc),
                                                                                          maxPP(pp),
                                                                                          attackType(at),
                                                                                          isAttack(isAttack) {
    currentPP = maxPP;
    //source https://pokemondb.net/type
    if (attackType == NORMAL) {
        weakAgainst.push_back(ROCK);
        weakAgainst.push_back(STEEL);
        immuneAgainst.push_back(GHOST);
    } else if (attackType == FIRE) {
        weakAgainst.push_back(FIRE);
        weakAgainst.push_back(WATER);
        weakAgainst.push_back(ROCK);
        weakAgainst.push_back(DRAGON);
        strongAgainst.push_back(GRASS);
        strongAgainst.push_back(ICE);
        strongAgainst.push_back(BUG);
        strongAgainst.push_back(STEEL);
    } else if (attackType == WATER) {
        weakAgainst.push_back(WATER);
        weakAgainst.push_back(GRASS);
        weakAgainst.push_back(DRAGON);
        strongAgainst.push_back(FIRE);
        strongAgainst.push_back(GRASS);
        strongAgainst.push_back(ROCK);
    } else if (attackType == GRASS) {
        weakAgainst.push_back(FIRE);
        weakAgainst.push_back(GRASS);
        weakAgainst.push_back(POISON);
        weakAgainst.push_back(FLYING);
        weakAgainst.push_back(BUG);
        weakAgainst.push_back(DRAGON);
        weakAgainst.push_back(STEEL);
        strongAgainst.push_back(WATER);
        strongAgainst.push_back(GROUND);
        strongAgainst.push_back(ROCK);
    } else if (attackType == ELECTRIC) {
        weakAgainst.push_back(ELECTRIC);
        weakAgainst.push_back(GRASS);
        weakAgainst.push_back(DRAGON);
        strongAgainst.push_back(WATER);
        strongAgainst.push_back(FLYING);
        immuneAgainst.push_back(GROUND);
    } else if (attackType == ICE) {
        weakAgainst.push_back(FIRE);
        weakAgainst.push_back(WATER);
        weakAgainst.push_back(ICE);
        weakAgainst.push_back(STEEL);
        strongAgainst.push_back(GRASS);
        strongAgainst.push_back(GROUND);
        strongAgainst.push_back(FLYING);
        strongAgainst.push_back(DRAGON);
    } else if (attackType == FIGHTING) {
        weakAgainst.push_back(POISON);
        weakAgainst.push_back(FLYING);
        weakAgainst.push_back(PSYCHIC);
        weakAgainst.push_back(BUG);
        weakAgainst.push_back(FAIRY);
        strongAgainst.push_back(NORMAL);
        strongAgainst.push_back(ICE);
        strongAgainst.push_back(ROCK);
        strongAgainst.push_back(DARK);
        strongAgainst.push_back(STEEL);
        immuneAgainst.push_back(GHOST);
    } else if (attackType == POISON) {
        weakAgainst.push_back(POISON);
        weakAgainst.push_back(GROUND);
        weakAgainst.push_back(ROCK);
        weakAgainst.push_back(GHOST);
        strongAgainst.push_back(GRASS);
        strongAgainst.push_back(FAIRY);
        immuneAgainst.push_back(STEEL);
    } else if (attackType == GROUND) {
        weakAgainst.push_back(BUG);
        weakAgainst.push_back(GRASS);
        strongAgainst.push_back(POISON);
        strongAgainst.push_back(ROCK);
        strongAgainst.push_back(STEEL);
        strongAgainst.push_back(FIRE);
        strongAgainst.push_back(ELECTRIC);
        immuneAgainst.push_back(FLYING);
    } else if (attackType == FLYING) {
        weakAgainst.push_back(ELECTRIC);
        weakAgainst.push_back(ROCK);
        weakAgainst.push_back(STEEL);
        strongAgainst.push_back(GRASS);
        strongAgainst.push_back(FIGHTING);
        strongAgainst.push_back(BUG);
    } else if (attackType == PSYCHIC) {
        weakAgainst.push_back(BUG);
        weakAgainst.push_back(PSYCHIC);
        strongAgainst.push_back(FIGHTING);
        strongAgainst.push_back(POISON);
        immuneAgainst.push_back(DARK);
    } else if (attackType == BUG) {
        weakAgainst.push_back(FIRE);
        weakAgainst.push_back(FIGHTING);
        weakAgainst.push_back(POISON);
        weakAgainst.push_back(FLYING);
        weakAgainst.push_back(GHOST);
        weakAgainst.push_back(STEEL);
        weakAgainst.push_back(FAIRY);
        strongAgainst.push_back(GRASS);
        strongAgainst.push_back(PSYCHIC);
        strongAgainst.push_back(DARK);
    } else if (attackType == ROCK) {
        weakAgainst.push_back(FIGHTING);
        weakAgainst.push_back(GROUND);
        weakAgainst.push_back(STEEL);
        strongAgainst.push_back(FIRE);
        strongAgainst.push_back(ICE);
        strongAgainst.push_back(FLYING);
        strongAgainst.push_back(BUG);
    } else if (attackType == GHOST) {
        weakAgainst.push_back(DARK);
        strongAgainst.push_back(PSYCHIC);
        strongAgainst.push_back(GHOST);
        immuneAgainst.push_back(NORMAL);
    } else if (attackType == DRAGON) {
        weakAgainst.push_back(STEEL);
        strongAgainst.push_back(DRAGON);
        immuneAgainst.push_back(FAIRY);
    } else if (attackType == DARK) {
        weakAgainst.push_back(FIGHTING);
        weakAgainst.push_back(DARK);
        weakAgainst.push_back(FAIRY);
        strongAgainst.push_back(PSYCHIC);
        strongAgainst.push_back(GHOST);
    } else if (attackType == STEEL) {
        weakAgainst.push_back(FIRE);
        weakAgainst.push_back(WATER);
        weakAgainst.push_back(ELECTRIC);
        weakAgainst.push_back(STEEL);
        strongAgainst.push_back(ICE);
        strongAgainst.push_back(ROCK);
        strongAgainst.push_back(FAIRY);
    } else if (attackType == FAIRY) {
        weakAgainst.push_back(FIRE);
        weakAgainst.push_back(GROUND);
        weakAgainst.push_back(STEEL);
        strongAgainst.push_back(FIGHTING);
        strongAgainst.push_back(DRAGON);
        strongAgainst.push_back(DARK);
    }
}

Attacks &Attacks::operator=(const Attacks &other) {
    if (this->getName() == other.getName()) {
        this->currentPP = other.currentPP;
    } else if (this != &other) {
        const_cast<string &>(this->name) = other.name;
        const_cast<int &>(this->attackPower) = other.attackPower;
        const_cast<int &>(this->maxPP) = other.maxPP;
        const_cast<int &>(this->accuracy) = other.accuracy;
        const_cast<string &>(this->attackType) = other.attackType;
        const_cast<bool &>(this->isAttack) = other.isAttack;
        this->weakAgainst = other.weakAgainst;
        this->strongAgainst = other.strongAgainst;
        this->immuneAgainst = other.immuneAgainst;
        this->currentPP = other.currentPP;
    }
    return *this;
}


string width(int num = 10) {
    string width = "";
    for (int i = 0; i < num; ++i) {
        width += " ";
    }
    return width;
}


void printFile(const string &fileName, const string &errorMessage, bool rightIndent,
               string color) {
    if (color != RED && color != GREEN && color != BLUE) {
        color = RESET;
    }
    ifstream file(fileName);
    if (file.good()) {
        if (rightIndent) {
            string line;
            while (getline(file, line)) {
                int numSpaces = int(190 - line.size());
                cout << color << width(numSpaces) << line << RESET << endl;
            }
            file.close();
        } else {
            string line;
            while (getline(file, line)) {
                cout << color << line << RESET << endl;
            }
            file.close();
        }
    } else {
        cout << errorMessage << endl;
    }
}

int getInt(int min, int max) {
    string input;
    int number;
    cout << endl;
    cout << "Select: ";
    while (true) {
        getline(cin, input);
        istringstream iss(input);
        if (iss >> number && !(min > number || number > max)) {
            return number;
        } else {
            cout << "Invalid input. Please enter a valid integer: ";
        }
    }
}

string getYN(const string &prompt) {
    string input;
    do {
        cout << prompt;
        getline(cin, input);
    } while (input != "y" && input != "n");
    return input;
}


int randGen(int min, int max) {
    return rand() % (max - min + 1) + min;
}


void clearConsole() {
    cout << "\033[2J\033[1;1H";
}

void pressToContinue() {
    string i;
    cout << "Press Enter to continue...";
    while (getline(cin, i) && !i.empty());
}