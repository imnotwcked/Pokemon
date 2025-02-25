#ifndef POKEMON_H
#define POKEMON_H

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <climits>
#include "globalVariable.h"

using namespace std;

int intro_page1();

string width(int num);

void pressToContinue();

void
printFile(const string &fileName, const string &errorMessage = ":( Unable to display image", bool rightIndent = false,
          string color = RESET);

int getInt(int min, int max);

string getYN(const string &prompt = "");

int randGen(int min, int max);

void clearConsole();

class Type;

class Attacks;

class Pokemon;

class Attacks;


class Type {
private:
    basic_string<char> type1;
    string type2;
public:
    Type() {}

    explicit Type(const string &t1, const string &t2 = "") : type1(t1), type2(t2) {}

    void changeType2(const string &tp2) {
        type2 = tp2;
    }

    string getType1() {
        return type1;
    }

    string getType2() {
        return type2;
    }

};


class Attacks {
protected:
    const string name;
    const int attackPower, maxPP, accuracy;
    const string attackType;
    const bool isAttack;
    vector<string> weakAgainst, strongAgainst, immuneAgainst;
    int currentPP;
public:
    explicit Attacks(const string &name = "NULL", string at = NORMAL, bool isAttack = true, int ap = 0, int acc = 100,
                     int pp = 10);

    vector<string> getWeakAgainstTypes() {
        return weakAgainst;
    }

    vector<string> getStrongAgainstTypes() {
        return strongAgainst;
    }

    vector<string> getImmuneAgainstTypes() {
        return immuneAgainst;
    }

    string getAttackType() {
        return attackType;
    }

    int getAttackPower() const {
        return attackPower;
    }

    bool getIsAttack() const {
        return isAttack;
    }

    string getName() const {
        if (name != "NULL") {
            return name;
        } else {
            return "";
        }
    }

    int getAccuracy() {
        return accuracy;
    }

    Attacks &operator=(const Attacks &other);


    void displayAttackStats();

    void healCurrentPP() {
        currentPP = maxPP;
    }

    int getCurrentPP() {
        return currentPP;
    }


    int getMaxPP() {
        return maxPP;
    }

    void decrementCurrentPP() {
        --currentPP;
    }

};


class EmptyAttack : public Attacks {
public:
    EmptyAttack() : Attacks() {}
};

//https://bulbapedia.bulbagarden.net/wiki/Damage
class Pokemon {
protected:
    string name, asciiFileName;
    int IV1, IV2, IV3, IV4, IV5, IV6, baseHP, baseAttack, baseDefense, baseSpAttack, baseSPDefense, baseSpeed;
    Type tp;
    int level, EV, maxHP, attack, defense, catchRate, specialAttack, specialDefense, speed, xp, currentHP;
    Attacks abilities[4];
    bool fainted;
public:
    explicit Pokemon(const string &name, const string &filename, const Attacks &a1, const Attacks &a2,
                     const Attacks &a3,
                     const Attacks &a4, int base1, int base2,
                     int base3, int base4, int base5, int base6, const string &type1, const string &type2 = "",
                     int lvl = 1);


    explicit Pokemon(const string &filename, const string &name, const int &currentHP, const string &type1,
                     const string &type2,
                     int IV1, int IV2, int IV3, int IV4, int IV5, int IV6, int lvl, int EV, int XP, const Attacks &a1,
                     const Attacks &a2, const Attacks &a3, const Attacks &a4, int base1, int base2,
                     int base3, int base4, int base5, int base6);

    void swapAttack(const Attacks &a);

    void display();

    friend void update(Pokemon &p) {
        p.increaseLevel();
        p.increaseEV();
        p.updateStats();
    }

    void updateStats();

    void healPokemon() {
        currentHP = maxHP;
        for (Attacks &pokemonAttacks: abilities) {
            pokemonAttacks.healCurrentPP();
        }
        fainted = false;
    }

    int getCatchRate() const {
        return catchRate;
    }

    string getName() const {
        return name;
    }

    int getLevel() const {
        return level;
    }

    int getAttack() const {
        return attack;
    }

    int getSpecialAttack() const {
        return specialAttack;
    }

    int getDefense() const {
        return defense;
    }

    int getSpecialDefense() const {
        return specialDefense;
    }

    int getSpeed() const {
        return speed;
    }

    string getType1() {
        return tp.getType1();
    };

    string getType2() {
        return tp.getType2();
    };

    bool isFainted() const {
        return fainted;
    }

    void createNickname(const string &input) {
        name = input;
    }

    int getMaxHp() const {
        return maxHP;
    }

    int getCurrentHP() const {
        return currentHP;
    }


    int getBase1() const {
        return baseHP;
    }

    int getBase2() const {
        return baseAttack;
    }

    int getBase3() const {
        return baseDefense;
    }

    int getBase4() const {
        return baseSpAttack;
    }

    int getBase5() const {
        return baseSPDefense;
    }

    int getBase6() const {
        return baseSpeed;
    }

    void increaseEV() {
        if (EV < 510) {
            EV += 10;
            cout << name << " got a little stronger by this battle (" << (EV / 10) << "/51)" << endl;
            cout << "There was a slight gain in the strength and the HP" << endl;
        }
    }

    void increaseLevel(int exp = randGen(30, 50)) {
        xp += exp;
        cout << "Your " << name << " gained " << exp << " xp!" << endl;
        while (xp >= 100 && level < 100) {
            cout << "Your " << name << " LEVELED UP!!" << endl;
            ++level;
            xp %= 100;
        }
    }

    Attacks selectAttack();

    void decrementCurrentHP(const int &damage) {
        currentHP -= damage;
        if (currentHP > 0) {
            fainted = false;
        } else {
            currentHP = 0;
            fainted = true;
        }
    }

    void displayCurrentHPandLevel(bool isEnemy = false) const;

    void displayCurrentHPLevelAndName(const string &n = "", bool isEnemy = false) const {
        if (!n.empty() && isEnemy) {
            cout << width(72) << name << endl;
            this->displayCurrentHPandLevel(true);
        } else if (!n.empty()) {
            cout << n << endl;
            this->displayCurrentHPandLevel(false);
        } else {
            cout << name << endl;
            this->displayCurrentHPandLevel(false);
        }
    }

    void printFilePokemon(bool isEnemy = false) {
        if (isEnemy) {
            printFile(asciiFileName, "Unable to display " + name, true);
        } else {
            printFile(asciiFileName, "Unable to display " + name);
        }
    }

    bool operator<(const Pokemon &other) const {
        int Strength = maxHP + attack + defense + specialAttack + specialDefense + speed;
        int otherStrength =
                other.maxHP + other.attack + other.defense + other.specialAttack + other.specialDefense + other.speed;
        return Strength > otherStrength;
    }

    friend Attacks autoAttack(Pokemon &attacker, Pokemon &defender);

    friend ostream &operator<<(ostream &os, Pokemon &p) {
        os << p.asciiFileName << endl << p.name << endl << p.currentHP << endl << p.tp.getType1() << endl <<
           p.tp.getType2() << endl << p.IV1 << endl << p.IV2 << endl << p.IV3 << endl <<
           p.IV4 << endl << p.IV5 << endl << p.IV6 << endl << p.level << endl << p.EV << endl << p.xp << endl <<
           p.abilities[0].getName() << endl << p.abilities[1].getName() << endl << p.abilities[2].getName() << endl
           << p.abilities[3].getName() << endl << p.baseHP << endl << p.baseAttack << endl << p.baseDefense << endl
           << p.baseSpAttack << endl << p.baseSPDefense << endl << p.baseSpeed << endl;
        return os;
    }
};

class Player {
protected:
    static int monsterBall;
    static int superBall;
    static int masterBall;
    static int money;
    string name;
    static bool redBadge;
    static bool greenBadge;
    static bool blueBadge;
    static bool loadingTheGameInAWhile;
public:
    Player() {}

    explicit Player(string name, int money = 5000, int mb = 10, int sb = 5, int master = 3, bool RB = false,
                    bool GB = false,
                    bool BB = false);

    void setName(const string &n) {
        name = n;
    }

    string getName() {
        return name;
    }

    void display() {
        cout << "Your name is " << name << endl;
    }

    void displayGreeting() {
        cout << "Welcome to pokemon world!! " << name << "!!!" << endl;
        pressToContinue();
    }

    static int getMoney() {
        return money;
    }

    static void setMonsterBall(int amount = 5) {
        monsterBall = amount;
    }

    static void setSuperBall(int amount = 5) {
        superBall = amount;
    }

    static void setMasterBall(int amount = 3) {
        masterBall = amount;
    }

    static void setMoney(int amount = 5000) {
        money = amount;
    }

    static void setRedBadge(bool RB = false) {
        redBadge = RB;
    }

    static void setGreenBadge(bool GB = false) {
        greenBadge = GB;
    }

    static void setBlueBadge(bool BB = false) {
        blueBadge = BB;
    }

    static int getNumOfMonsterBall() {
        return monsterBall;
    }

    static int getNumOfSuperBall() {
        return superBall;
    }

    static int getNumOfMasterBall() {
        return masterBall;
    }

    static void decrementMonsterBall(int numberOfTimes = 1) {
        if (monsterBall > 0)
            monsterBall -= numberOfTimes;
    }

    static void decrementSuperBall(int numberOfTimes = 1) {
        if (superBall > 0)
            superBall -= numberOfTimes;
    }

    static void decrementMasterBall(int numberOfTimes = 1) {
        if (masterBall > 0)
            masterBall -= numberOfTimes;
    }

    static void incrementMonsterBall(int numberOfTimes = 1) {
        if (numberOfTimes + monsterBall < INT_MAX)
            monsterBall += numberOfTimes;
    }

    static void incrementSuperBall(int numberOfTimes = 1) {
        if (numberOfTimes + superBall < INT_MAX)
            superBall += numberOfTimes;
    }

    static void incrementMasterBall(int numberOfTimes = 1) {
        if (numberOfTimes + masterBall < INT_MAX)
            masterBall += numberOfTimes;
    }

    static void incrementMoney(int amount = 100) {
        if (amount + money < INT_MAX) {
            money += amount;
            cout << "You earned " << amount << " coins !!" << endl;
        }
    }

    static void decrementMoney(int amount = 100) {
        money -= amount;
    }

    static void earnGreenBadge() {
        cout << "You earned a Green Badge" << endl;
        printFile("GreenBadge.txt", "Here is your green badge!\n", false, GREEN);
        greenBadge = true;
    }

    static void earnBlueBadge() {
        cout << "You earned a Blue Badge" << endl;
        printFile("BlueBadge.txt", "Here is your blue badge!\n", false, BLUE);
        blueBadge = true;
    }

    static void earnRedBadge() {
        cout << "You earned a Red Badge" << endl;
        printFile("RedBadge.txt", "Here is your red badge!\n", false, RED);
        redBadge = true;
    }

    static void setLoadingTheGameInAWhile(bool boolean = false) {
        loadingTheGameInAWhile = boolean;
    }

    static bool getLoadingTheGameInAWhile() {
        return loadingTheGameInAWhile;
    }


    static bool getGreenBadge() {
        return greenBadge;
    }

    static bool getBlueBadge() {
        return blueBadge;
    }

    static bool getRedBadge() {
        return redBadge;
    }


    friend ostream &operator<<(ostream &os, Player &p) {
        os << p.name << endl << Player::money << endl << Player::monsterBall << endl << Player::superBall << endl
           << Player::masterBall << endl
           << Player::redBadge << endl << Player::greenBadge << endl << Player::blueBadge << endl;
        return os;
    }
};

//Source: https://pokemondb.net/move/all
class Bite : public Attacks {
public:
    Bite() : Attacks(BITE, DARK, true, 60, 100, 25) {}
};

class Tackle : public Attacks {
public:
    Tackle() : Attacks(TACKLE, NORMAL, true, 40, 100, 35) {}
};

class AquaTail : public Attacks {
public:
    AquaTail() : Attacks(AQUATAIL, WATER, true, 90, 90, 10) {}
};

class Earthquake : public Attacks {
public:
    Earthquake() : Attacks(EARTHQUAKE, GROUND, true, 100, 100, 10) {}
};


class Thunderbolt : public Attacks {
public:
    Thunderbolt() : Attacks(THUNDERBOLT, ELECTRIC, false, 90, 100, 15) {}
};


class FireBlast : public Attacks {
public:
    FireBlast() : Attacks(FIREBLAST, FIRE, false, 110, 85, 10) {}
};


class DragonPulse : public Attacks {
public:
    DragonPulse() : Attacks(DRAGONPULSE, DRAGON, false, 85, 90, 10) {}
};

class StoneEdge : public Attacks {
public:
    StoneEdge() : Attacks(STONEEDGE, ROCK, true, 100, 80, 5) {}
};

class Acrobatics : public Attacks {
public:
    Acrobatics() : Attacks(ACROBATICS, FLYING, true, 55, 100, 15) {}
};

class AeroBlast : public Attacks {
public:
    AeroBlast() : Attacks(AEROBLAST, FLYING, false, 100, 95, 5) {}
};

class AirCutter : public Attacks {
public:
    AirCutter() : Attacks(AIRCUTTER, FLYING, false, 60, 95, 25) {}
};

class AirSlash : public Attacks {
public:
    AirSlash() : Attacks(AIRSLASH, FLYING, false, 75, 95, 15) {}
};

class AnchorShot : public Attacks {
public:
    AnchorShot() : Attacks(ANCHORSHOT, STEEL, true, 80, 100, 20) {}
};

class AncientPower : public Attacks {
public:
    AncientPower() : Attacks(ANCIENTPOWER, ROCK, false, 60, 100, 5) {}
};

class AppleAcid : public Attacks {
public:
    AppleAcid() : Attacks(APPLEACID, GRASS, false, 80, 100, 20) {}
};

class Acidspray : public Attacks {
public:
    Acidspray() : Attacks(ACIDSPRAY, POISON, false, 40, 100, 20) {}
};

class Razorleaf : public Attacks {
public:
    Razorleaf() : Attacks(RAZORLEAF, GRASS, true, 105, 100, 25) {}
};

class AquaCutter : public Attacks {
public:
    AquaCutter() : Attacks(AQUACUTTER, WATER, true, 70, 100, 20) {}
};

class AquaJet : public Attacks {
public:
    AquaJet() : Attacks(AQUAJET, WATER, true, 40, 100, 20) {}
};

class AquaStep : public Attacks {
public:
    AquaStep() : Attacks(AQUASTEP, WATER, true, 80, 100, 10) {}
};

class Vinewhip : public Attacks {
public:
    Vinewhip() : Attacks(VINEWHIP, GRASS, true, 45, 100, 25) {}
};

class ArmThrust : public Attacks {
public:
    ArmThrust() : Attacks(ARMTHRUST, FIGHTING, true, 15, 100, 20) {}
};

class ArmorCannon : public Attacks {
public:
    ArmorCannon() : Attacks(ARMORCANNON, FIRE, false, 120, 100, 5) {}
};

class Assurance : public Attacks {
public:
    Assurance() : Attacks(ASSURANCE, DARK, true, 60, 100, 10) {}
};

class Astonish : public Attacks {
public:
    Astonish() : Attacks(ASTONISH, GHOST, true, 30, 100, 15) {}
};

class Gigadrain : public Attacks {
public:
    Gigadrain() : Attacks(GIGADRAIN, GRASS, false, 75, 100, 10) {}
};

class AstralBarrage : public Attacks {
public:
    AstralBarrage() : Attacks(ASTRALBARRAGE, GHOST, false, 120, 100, 5) {}
};

class Takedown : public Attacks {
public:
    Takedown() : Attacks(TAKEDOWN, FIGHTING, true, 90, 85, 20) {}
};

class Highjumpkick : public Attacks {
public:
    Highjumpkick() : Attacks(HIGHJUMPKICK, FIGHTING, true, 130, 90, 10) {}
};

class Ragingfury : public Attacks {
public:
    Ragingfury() : Attacks(RAGINGFURY, FIRE, true, 120, 100, 10) {}
};

class Grassknot : public Attacks {
public:
    Grassknot() : Attacks(GRASSKNOT, GRASS, true, 50, 100, 20) {}
};

class Leafblade : public Attacks {
public:
    Leafblade() : Attacks(LEAFBLADE, GRASS, true, 60, 100, 10) {}
};

class Surf : public Attacks {
public:
    Surf() : Attacks(SURF, WATER, false, 80, 100, 20) {}
};

class Icebeam : public Attacks {
public:
    Icebeam() : Attacks(ICEBEAM, ICE, false, 85, 100, 15) {}
};

class Flareblitz : public Attacks {
public:
    Flareblitz() : Attacks(FLAREBLITZ, FIRE, true, 120, 100, 10) {}
};

class Crunch : public Attacks {
public:
    Crunch() : Attacks(CRUNCH, DARK, true, 80, 100, 15) {}
};

class Firespin : public Attacks {
public:
    Firespin() : Attacks(FIRESPIN, FIRE, true, 75, 85, 15) {}
};

class Lowkick : public Attacks {
public:
    Lowkick() : Attacks(LOWKICK, FIGHTING, true, 55, 100, 25) {}
};

class Highhorsepower : public Attacks {
public:
    Highhorsepower() : Attacks(HIGHHORSEPOWER, GROUND, true, 95, 95, 15) {}
};

class Firefang : public Attacks {
public:
    Firefang() : Attacks(FIREFANG, FIRE, true, 80, 100, 15) {}
};

class Flamethrower : public Attacks {
public:
    Flamethrower() : Attacks(FLAMETHROWER, FIRE, false, 90, 100, 15) {}
};

class Blizzard : public Attacks {
public:
    Blizzard() : Attacks(BLIZZARD, ICE, true, 90, 100, 10) {}
};

class FurySwipes : public Attacks {
public:
    FurySwipes() : Attacks(FURYSWIPES, NORMAL, true, 18, 80, 15) {}
};

class AttackOrder : public Attacks {
public:
    AttackOrder() : Attacks(ATTACKORDER, BUG, true, 90, 100, 15) {}
};

class AuraSphere : public Attacks {
public:
    AuraSphere() : Attacks(AURASPHERE, FIGHTING, false, 80, 10000, 20) {}
};


/*
 * Below are Pokémon From
 * https://marriland.com
 * Please use the generation 4 stats, if applicable.
 */


class Bulbasaur : public Pokemon {
public:
    explicit Bulbasaur(int level = 1, const string &n = "Bulbasaur") : Pokemon(n, "bulbasaur.txt", Tackle(),
                                                                               Vinewhip(),
                                                                               EmptyAttack(), EmptyAttack(), 45, 49,
                                                                               49,
                                                                               65,
                                                                               65, 45,
                                                                               GRASS, "",
                                                                               level) {}
};

class Pikachu : public Pokemon {
public:
    explicit Pikachu(int level = 1, const string &n = "Pikachu") : Pokemon(n, "pikachu.txt", Tackle(),
                                                                           Thunderbolt(),
                                                                           EmptyAttack(), EmptyAttack(), 35, 55, 30,
                                                                           50,
                                                                           40,
                                                                           90, ELECTRIC,
                                                                           "",
                                                                           level) {}
};

class Eevee : public Pokemon {
public:
    explicit Eevee(int level = 1, const string &n = "Eevee") : Pokemon(n, "Eevee.txt", Tackle(), EmptyAttack(),
                                                                       EmptyAttack(), EmptyAttack(), 55, 55, 50, 45,
                                                                       65,
                                                                       55,
                                                                       NORMAL, "",
                                                                       level) {}
};

class Caterpie : public Pokemon {
public:
    explicit Caterpie(int level = 1, const string &n = "caterpie") : Pokemon(n, "caterpie.txt", Tackle(),
                                                                             EmptyAttack(),
                                                                             EmptyAttack(), EmptyAttack(), 45, 30,
                                                                             35,
                                                                             20, 20,
                                                                             45, BUG,
                                                                             "",
                                                                             level) {}
};

class Dialga : public Pokemon {
public:
    explicit Dialga(int level = 1, const string &n = "Dialga") : Pokemon(n, "Dialga.txt", DragonPulse(),
                                                                         FireBlast(),
                                                                         ArmorCannon(), Thunderbolt(), 100, 120, 120,
                                                                         150,
                                                                         100, 90,
                                                                         STEEL,
                                                                         DRAGON,
                                                                         level) {}
};

class Giratina : public Pokemon {
public:
    explicit Giratina(int level = 1, const string &n = "Giratina") : Pokemon(n, "Giratina.txt", DragonPulse(),
                                                                             FireBlast(),
                                                                             Acrobatics(), Thunderbolt(), 150, 100, 120,
                                                                             100, 120,
                                                                             90,
                                                                             DRAGON,
                                                                             GHOST,
                                                                             level) {}
};

class Rayquaza : public Pokemon {
public:
    explicit Rayquaza(int level = 1, const string &n = "Rayquaza") : Pokemon(n, "Rayquaza.txt", DragonPulse(),
                                                                             FireBlast(),
                                                                             Acrobatics(), Thunderbolt(), 105, 150, 90,
                                                                             150,
                                                                             90,
                                                                             95,
                                                                             DRAGON,
                                                                             FLYING,
                                                                             level) {}
};

class Lucario : public Pokemon {
public:
    explicit Lucario(int level = 1, const string &n = "Lucario") : Pokemon(n, "lucario.txt", Firefang(),
                                                                           AuraSphere(),
                                                                           Crunch(), FurySwipes(), 70, 110,
                                                                           70,
                                                                           115, 70,
                                                                           90,
                                                                           FIGHTING,
                                                                           STEEL,
                                                                           level) {}
};

class Magikarp : public Pokemon {
public:
    explicit Magikarp(int level = 1, const string &n = "Magikarp") : Pokemon(n, "magikarp.txt", Tackle(),
                                                                             EmptyAttack(),
                                                                             EmptyAttack(), EmptyAttack(), 20, 10,
                                                                             55,
                                                                             15, 20,
                                                                             90, WATER,
                                                                             "",
                                                                             level) {}
};

class Mew : public Pokemon {
public:
    explicit Mew(int level = 1, const string &n = "Mew") : Pokemon(n, "Mew.txt", DragonPulse(), FireBlast(),
                                                                   Crunch(), Thunderbolt(), 100, 100, 100, 100, 100,
                                                                   100,
                                                                   PSYCHIC,
                                                                   "",
                                                                   level) {}
};

class Porygon : public Pokemon {
public:
    explicit Porygon(int level = 1, const string &n = "Porygon") : Pokemon(n, "porygon.txt", Tackle(),
                                                                           Thunderbolt(),
                                                                           EmptyAttack(), EmptyAttack(), 65, 60, 70,
                                                                           85,
                                                                           75,
                                                                           40, NORMAL,
                                                                           "",
                                                                           level) {}
};

class Squirtle : public Pokemon {
public:
    explicit Squirtle(int level = 1, const string &n = "Squirtle") : Pokemon(n, "squirtle.txt", Tackle(),
                                                                             AquaTail(),
                                                                             EmptyAttack(), EmptyAttack(), 44, 48,
                                                                             65,
                                                                             50, 64,
                                                                             43, WATER,
                                                                             "",
                                                                             level) {}
};

class Charmander : public Pokemon {
public:
    explicit Charmander(int level = 1, const string &n = "Charmander") : Pokemon(n, "charmander.txt", Tackle(),
                                                                                 Firefang(),
                                                                                 EmptyAttack(), EmptyAttack(), 39,
                                                                                 52,
                                                                                 43, 60,
                                                                                 50, 65,
                                                                                 FIRE,
                                                                                 "",
                                                                                 level) {}
};

class Charizard : public Pokemon {
public:
    explicit Charizard(int level = 1, const string &n = "Charizard") : Pokemon(n, "charizard.txt", FireBlast(),
                                                                               Crunch(),
                                                                               Firefang(), Acrobatics(), 78, 84,
                                                                               78,
                                                                               109,
                                                                               85, 100,
                                                                               FIRE,
                                                                               FLYING,
                                                                               level) {}
};

class Gyarados : public Pokemon {
public:
    explicit Gyarados(int level = 1, const string &n = "Gyarados") : Pokemon(n, "gyarados.txt", Tackle(),
                                                                             Surf(),
                                                                             Earthquake(), AquaTail(), 95, 125,
                                                                             79,
                                                                             60,
                                                                             100, 81,
                                                                             WATER,
                                                                             FLYING,
                                                                             level) {}
};

class Palkia : public Pokemon {
public:
    explicit Palkia(int level = 1, const string &n = "Palkia") : Pokemon(n, "Palkia.txt", DragonPulse(),
                                                                         FireBlast(),
                                                                         Earthquake(), AquaCutter(), 90, 120,
                                                                         100,
                                                                         150,
                                                                         120, 100,
                                                                         WATER,
                                                                         DRAGON,
                                                                         level) {}
};

class Rapiddash : public Pokemon {
public:
    explicit Rapiddash(int level = 1, const string &n = "Rapiddash") : Pokemon(n, "rapiddash.txt", Firespin(),
                                                                               Lowkick(),
                                                                               Highhorsepower(), Tackle(), 65,
                                                                               100,
                                                                               70,
                                                                               80,
                                                                               80, 105,
                                                                               FIRE,
                                                                               "",
                                                                               level) {}
};

class Blaziken : public Pokemon {
public:
    explicit Blaziken(int level = 1, const string &n = "Blaziken") : Pokemon(n, "blaziken.txt", Flareblitz(),
                                                                             Highjumpkick(),
                                                                             StoneEdge(), EmptyAttack(), 80, 120,
                                                                             70,
                                                                             110,
                                                                             70, 80,
                                                                             FIRE,
                                                                             FIGHTING,
                                                                             level) {}
};

class Arcanine : public Pokemon {
public:
    explicit Arcanine(int level = 1, const string &n = "Arcanine") : Pokemon(n, "arcanine.txt", Flamethrower(),
                                                                             Firefang(),
                                                                             Ragingfury(), Crunch(), 90, 110,
                                                                             80,
                                                                             100,
                                                                             80, 95,
                                                                             FIRE,
                                                                             "",
                                                                             level) {}
};

class Lapras : public Pokemon {
public:
    explicit Lapras(int level = 1, const string &n = "Lapras") : Pokemon(n, "lapras.txt", Surf(),
                                                                         Blizzard(),
                                                                         Icebeam(), Tackle(), 130, 85,
                                                                         80,
                                                                         85,
                                                                         95, 60,
                                                                         WATER,
                                                                         ICE,
                                                                         level) {}
};

class Psyduck : public Pokemon {
public:
    explicit Psyduck(int level = 1, const string &n = "Psyduck") : Pokemon(n, "psyduck.txt", FurySwipes(), Surf(),
                                                                           EmptyAttack(), EmptyAttack(), 50, 52, 48, 65,
                                                                           50, 55, WATER, "", level) {}
};

class Seel : public Pokemon {
public:
    explicit Seel(int level = 1, const string &n = "Seel") : Pokemon(n, "seel.txt", Surf(),
                                                                     Takedown(),
                                                                     Icebeam(), EmptyAttack(), 65, 55,
                                                                     115,
                                                                     100,
                                                                     40, 60,
                                                                     WATER,
                                                                     "",
                                                                     level) {}
};

class Vileplume : public Pokemon {
public:
    explicit Vileplume(int level = 1, const string &n = "Vileplume") : Pokemon(n, "vileplume.txt", Grassknot(),
                                                                               Leafblade(),
                                                                               Tackle(), EmptyAttack(), 75, 80,
                                                                               85,
                                                                               110,
                                                                               90, 50,
                                                                               GRASS,
                                                                               POISON,
                                                                               level) {}
};

class Tangela : public Pokemon {
public:
    explicit Tangela(int level = 1, const string &n = "Tangela") : Pokemon(n, "tangela.txt", Gigadrain(),
                                                                           Vinewhip(),
                                                                           Tackle(), EmptyAttack(), 65, 55,
                                                                           115,
                                                                           100,
                                                                           40, 60,
                                                                           GRASS,
                                                                           "",
                                                                           level) {}
};

class Victreebel : public Pokemon {
public:
    explicit Victreebel(int level = 1, const string &n = "Victreebel") : Pokemon(n, "victreebel.txt",
                                                                                 Razorleaf(),
                                                                                 Acidspray(),
                                                                                 EmptyAttack(), EmptyAttack(),
                                                                                 80, 105,
                                                                                 65,
                                                                                 100,
                                                                                 60, 70,
                                                                                 GRASS,
                                                                                 POISON,
                                                                                 level) {}
};

//Arceus is un-catchable pokemon that only Pokemon master uses. The base stats are impossible natural values.
class Arceus : public Pokemon {
public:
    explicit Arceus(int level = 1, const string &n = "Arceus") : Pokemon(n, "Arceus.txt",
                                                                         Ragingfury(),
                                                                         ArmorCannon(),
                                                                         Earthquake(), DragonPulse(),
                                                                         500, 500,
                                                                         500,
                                                                         500,
                                                                         500, 500,
                                                                         FAIRY,"",
                                                                         level) {
        currentHP = maxHP;
        IV1 = 31;
        IV2 = 31;
        IV3 = 31;
        IV4 = 31;
        IV5 = 31;
        IV6 = 31;
    }
};

#endif