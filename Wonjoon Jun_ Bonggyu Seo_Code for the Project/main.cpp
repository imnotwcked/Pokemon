/****************************************************************************
* File:   main.cpp
* Author:   Wonjoon Jun and Bonggyu Seo
* Purpose: main of the project. Stores everything needed to successfully run
           the program
* Version: Final Version Nov 19, 2023
* Resources: line 1327 vector swap "swap(list[userInput1 - 1], list[userInput2 - 1])"
*            Received aid from chat.open.ai on Nov 15
*            line 167 and beyond stoi keyword Received aid from chat.open.ai on Nov 05
*           line 78 and beyond function this_thread::sleep_for(chrono::seconds())
*           Received aid from chat.open.ai on Nov 05
*******************************************************************************/
#include"pokemon.h"
#include "globalVariable.h"
#include <vector>
#include <string>
#include <thread>
#include <ctime>
#include <fstream>
#include <climits>


using namespace std;


inline void makeNickname(Pokemon &a);

Attacks attackConstructor(const string &name);

inline void play_page1I(vector<Pokemon> &listOfPokemon, Player &player1);

inline void createPlayer_page1I(Player &p);

inline void displayEnemyHealthAndMyPokemonHealth(Pokemon &mine, Pokemon &enemy, bool withDelay = false);

vector<Pokemon> loadSaveFileForPokemon_page1I();

Pokemon chooseStarting_page1I();

Player loadSaveFileForPlayer_page1I();

int mainPage_page2(vector<Pokemon> &list);

void inToTheWild_page3I(vector<Pokemon> &list);

void inToTheGym_page3I(vector<Pokemon> &list);

void ManagePokemon_page3(vector<Pokemon> &list);

void PokemonBattleMainPage_page3(Pokemon enemy, vector<Pokemon> &list);

inline void visitStore_page3(vector<Pokemon> &list);

void fightGymLeader_page3(vector<Pokemon> &list, vector<Pokemon> &enemyList, const string &nameOfGymLeader);

void fight_page4(Pokemon &myPokemon, Pokemon &enemy);

bool throwMonsterBall_page4(Pokemon p, vector<Pokemon> &list);

int damageStep_page4I(Pokemon &attacker, Attacks attack, Pokemon &defender, bool isAttackerEnemy = false);

int damageCalculationAuto_page4I(Pokemon &attacker, Attacks attack, Pokemon &defender);

inline void showCollection_page4(vector<Pokemon> &list);

inline void healPokemon_page4(vector<Pokemon> &list);

void buyMonsterBalls_page4();

void buyTM_page4(vector<Pokemon> &list);

void sortPokemon_page4(vector<Pokemon> &list);

int main() {
    srand(time(NULL));
    clearConsole();
    printFile("pokemonLogo.txt", "Unable to print logo");
    this_thread::sleep_for(chrono::seconds(1));
    vector<Pokemon> listOfPokemon;
    Player player1;
    switch (intro_page1()) {
        case 1:
            clearConsole();
            createPlayer_page1I(player1);
            printFile("player.txt", "Unable to print player image");
            player1.displayGreeting();
            listOfPokemon.push_back(chooseStarting_page1I());
            play_page1I(listOfPokemon, player1);
            cout << "Saving and Quiting the Game! Thank you" << endl;
            break;
        case 2:
            clearConsole();
            try {
                listOfPokemon = loadSaveFileForPokemon_page1I();
                player1 = loadSaveFileForPlayer_page1I();
            } catch (...) {
                cout << "Corrupted save file!" << endl;
                cout << "Unreasonable player or pokemon stats" << endl;
                cout << "Critical error have occurred in the loading process.\nPlease start a new game!" << endl;
                exit(0);
            }
            cout << "Welcome Back!! " << player1.getName() << "!!!" << endl;
            cout << "All pokemons restored their PP after good resting!" << endl;
            pressToContinue();
            play_page1I(listOfPokemon, player1);
            cout << "Saving and Quiting the Game! Thank you" << endl;
            break;
        default:
            clearConsole();
            cout << "Thank you" << endl;
            break;
    }
    return 0;
}

int intro_page1() {
    cout << "Welcome to Pokemon Game!!" << endl;
    cout << "1. Play New Game" << endl;
    cout << "2. Load Save File" << endl;
    cout << "3. Exit" << endl;
    cout << "What do you want to do? (1/2/3)";
    return getInt(1, 3);
}

void play_page1I(vector<Pokemon> &listOfPokemon, Player &player1) {
    int quit(1);
    while (quit) {
        quit = mainPage_page2(listOfPokemon);
    }
    ofstream FILE1("PokemonSave.txt");

    for (Pokemon i: listOfPokemon) {
        FILE1 << i;
        FILE1 << ENDOFONEPOKEMON << endl;
    }
    ofstream FILE2("PlayerSave.txt");
    FILE2 << player1;
}

vector<Pokemon> loadSaveFileForPokemon_page1I() {
    vector<string> saveFileInfo;
    vector<Pokemon> loadFromSave;
    ifstream FILE2("PokemonSave.txt");
    int i(0);
    int validity(0);
    string tempInfo;

    if (!FILE2.good()) {
        Pokemon p = chooseStarting_page1I();
        loadFromSave.push_back(p);
        return loadFromSave;
    }

    while (getline(FILE2, tempInfo)) {
        saveFileInfo.push_back(tempInfo);
        ++validity;
        char CriticalError = 0;
        if (validity != 25 && tempInfo == ENDOFONEPOKEMON) {
            cout << "Error have occurred in the loading process!" << endl;
            Pokemon p = chooseStarting_page1I();
            loadFromSave.push_back(p);
            return loadFromSave;
        }
        if (saveFileInfo.size() == 25) {
            string filename = (saveFileInfo[0]);
            string name = (saveFileInfo[1]);
            int currentHP = stoi(saveFileInfo[2]);
            string type1 = saveFileInfo[3];
            string type2 = saveFileInfo[4];
            int IV1 = stoi(saveFileInfo[5]);
            int IV2 = stoi(saveFileInfo[6]);
            int IV3 = stoi((saveFileInfo[7]));
            int IV4 = stoi((saveFileInfo[8]));
            int IV5 = stoi((saveFileInfo[9]));
            int IV6 = stoi((saveFileInfo[10]));
            int lvl = stoi((saveFileInfo[11]));
            int EV = stoi((saveFileInfo[12]));
            int XP = stoi((saveFileInfo[13]));
            Attacks a1 = attackConstructor((saveFileInfo[14]));
            Attacks a2 = attackConstructor((saveFileInfo[15]));
            Attacks a3 = attackConstructor((saveFileInfo[16]));
            Attacks a4 = attackConstructor((saveFileInfo[17]));
            int base1 = stoi(saveFileInfo[18]);
            int base2 = stoi(saveFileInfo[19]);
            int base3 = stoi(saveFileInfo[20]);
            int base4 = stoi(saveFileInfo[21]);
            int base5 = stoi(saveFileInfo[22]);
            int base6 = stoi(saveFileInfo[23]);
            if (base1 == 0 || base2 == 0 || base3 == 0 || base4 == 0 || base5 == 0 || base6 == 0 ||
                (base1 + base2 + base3 + base4 + base5 + base6 > 720) || lvl > 100 || IV1 > 31 || IV2 > 31 ||
                IV3 > 31 || IV4 > 31 || IV5 > 31 || IV6 > 31 || (IV1 + IV2 + IV3 + IV4 + IV5 + IV6) < 6) {
                throw CriticalError;
            }
            loadFromSave.push_back(
                    Pokemon(filename, name, currentHP, type1, type2, IV1, IV2, IV3, IV4, IV5, IV6, lvl, EV, XP,
                            a1,
                            a2, a3, a4, base1, base2, base3, base4, base5, base6));
            ++i;
            validity = 0;
            saveFileInfo.clear();
        }
    }
    if (loadFromSave.empty()) {
        cout << "The save file had no Pokemon!" << endl;
        Pokemon p = chooseStarting_page1I();
        loadFromSave.push_back(p);
        return loadFromSave;
    }
    return loadFromSave;
}

Player loadSaveFileForPlayer_page1I() {
    vector<string> playerInfo;
    ifstream FILE2("PlayerSave.txt");
    string tempInfo;
    char criticalError = 0;
    if (!FILE2.good()) {
        Player p;
        cout << "The loading for player information failed" << endl;
        createPlayer_page1I(p);
        return p;
    }

    while (getline(FILE2, tempInfo)) {
        playerInfo.push_back(tempInfo);
    }


    if (playerInfo.size() == 8) {
        for (int i = 1; i < 7; ++i) {
            if (stoi(playerInfo[i]) > INT_MAX) {
                throw (criticalError);
            }
        }
        Player p(playerInfo[0], stoi(playerInfo[1]), stoi(playerInfo[2]), stoi(playerInfo[3]), stoi(playerInfo[4]),
                 stoi(playerInfo[5]), stoi(playerInfo[6]), stoi(playerInfo[7]));
        return p;
    } else {
        Player p;
        cout << "The loading for player information failed" << endl;
        createPlayer_page1I(p);
        return p;
    }
}

Attacks attackConstructor(const string &name) {
    if (name == BITE)
        return Bite();
    else if (name == TACKLE)
        return Tackle();
    else if (name == AQUATAIL)
        return AquaTail();
    else if (name == EARTHQUAKE)
        return Earthquake();
    else if (name == THUNDERBOLT)
        return Thunderbolt();
    else if (name == FIREBLAST)
        return FireBlast();
    else if (name == DRAGONPULSE)
        return DragonPulse();
    else if (name == STONEEDGE)
        return StoneEdge();
    else if (name == ACROBATICS)
        return Acrobatics();
    else if (name == AEROBLAST)
        return AeroBlast();
    else if (name == STONEEDGE)
        return AirCutter();
    else if (name == AIRSLASH)
        return AirSlash();
    else if (name == ANCHORSHOT)
        return AnchorShot();
    else if (name == ANCIENTPOWER)
        return AncientPower();
    else if (name == APPLEACID)
        return AppleAcid();
    else if (name == AQUACUTTER)
        return AquaCutter();
    else if (name == AQUAJET)
        return AquaJet();
    else if (name == STONEEDGE)
        return AquaStep();
    else if (name == ARMTHRUST)
        return ArmThrust();
    else if (name == STONEEDGE)
        return ArmorCannon();
    else if (name == ASSURANCE)
        return Assurance();
    else if (name == ASTONISH)
        return Astonish();
    else if (name == ASTRALBARRAGE)
        return AstralBarrage();
    else if (name == ATTACKORDER)
        return AttackOrder();
    else if (name == AURASPHERE)
        return AuraSphere();
    else if (name == RAZORLEAF)
        return Razorleaf();
    else if (name == GIGADRAIN)
        return Gigadrain();
    else if (name == VINEWHIP)
        return Vinewhip();
    else if (name == GRASSKNOT)
        return Grassknot();
    else if (name == LEAFBLADE)
        return Leafblade();
    else if (name == BLIZZARD)
        return Blizzard();
    else if (name == ICEBEAM)
        return Icebeam();
    else if (name == SURF)
        return Surf();
    else if (name == TAKEDOWN)
        return Takedown();
    else if (name == FURYSWIPES)
        return FurySwipes();
    else if (name == FLAMETHROWER)
        return Flamethrower();
    else if (name == CRUNCH)
        return Crunch();
    else if (name == RAGINGFURY)
        return Ragingfury();
    else if (name == FIREFANG)
        return Firefang();
    else if (name == FLAREBLITZ)
        return Flareblitz();
    else if (name == HIGHJUMPKICK)
        return Highjumpkick();
    else if (name == FIRESPIN)
        return Firespin();
    else if (name == LOWKICK)
        return Lowkick();
    else if (name == HIGHHORSEPOWER)
        return Highhorsepower();
    else if (name == ACIDSPRAY)
        return Acidspray();
    else
        return EmptyAttack();
}


void createPlayer_page1I(Player &p) {
    clearConsole();
    string pName;
    cout << "Let's create a character!" << endl;
    cout << "What is your name? ";
    getline(cin, pName);
    p.setName(pName);
}


Pokemon chooseStarting_page1I() {
    int i;
    clearConsole();
    cout << "Let's pick your starting pokemon! " << endl;
    cout << "1. Bulbasaur " << endl;
    printFile("bulbasaur.txt");
    pressToContinue();
    cout << "2. Charmander " << endl;
    printFile("charmander.txt");
    pressToContinue();
    cout << "3. Squirtle " << endl;
    printFile("squirtle.txt");
    cout << "What pokemon would you like to choose? (1,2,3): ";
    i = getInt(1, 3);
    if (i == 1) {
        Pokemon pokemon1 = Bulbasaur(10);
        makeNickname(pokemon1);
        clearConsole();
        return pokemon1;
    } else if (i == 2) {
        Pokemon pokemon1 = Charmander(10);
        makeNickname(pokemon1);
        clearConsole();
        return pokemon1;
    } else {
        Pokemon pokemon1 = Squirtle(10);
        makeNickname(pokemon1);
        clearConsole();
        return pokemon1;
    }
}


void makeNickname(Pokemon &a) {
    string input;
    input = getYN("Would you like to name your pokemon? (y/n): ");
    if (input == "y") {
        string name;
        cout << "What would you like to name " << a.getName() << " to? ";
        getline(cin, name);
        a.createNickname(name);
    }
}

void showCollection_page4(vector<Pokemon> &list) {
    for (Pokemon &i: list) {
        i.display();
    }
    pressToContinue();
    clearConsole();
}

int mainPage_page2(vector<Pokemon> &list) {
    clearConsole();
    string gymLeader = ((Player::getBlueBadge() + Player::getRedBadge() + Player::getGreenBadge()) >= 3) ? MASTERNAME
                                                                                                         : "Gym Leader";
    cout << "1. Catch other Pokemon" << endl;
    cout << "2. Challenge " << gymLeader << endl;
    cout << "3. Manage your Pokemon" << endl;
    cout << "4. Go to Store" << endl;
    cout << "5. Save and Quit Game" << endl;
    int HealthyPokemon(0);
    int userInput = getInt(1, 5);
    while (userInput != 5) {
        clearConsole();
        gymLeader = ((Player::getBlueBadge() + Player::getRedBadge() + Player::getGreenBadge()) >= 3) ? MASTERNAME
                                                                                                      : "Gym Leader";
        if (userInput == 1 || userInput == 2) {
            HealthyPokemon = 0;
            for (Pokemon &i: list) {
                if (!i.isFainted()) {
                    ++HealthyPokemon;
                }
            }
            if (HealthyPokemon <= 0 && userInput == 1) {
                cout << "You cannot enter into wild. You have no healthy pokemon!" << endl;
                cout << "Please go and heal your pokemon! Press 2!" << endl;
            } else if (HealthyPokemon <= 0 && userInput == 2) {
                cout << "You cannot challenge " << gymLeader << ". You have no healthy pokemon!" << endl;
                cout << "Please go and heal your pokemon! Press 2!" << endl;
            } else if (userInput == 1) {
                inToTheWild_page3I(list);
            } else {
                inToTheGym_page3I(list);
            }
        } else if (userInput == 3) {
            ManagePokemon_page3(list);
        } else if (userInput == 4) {
            visitStore_page3(list);
        }
        cout << "1. Catch other Pokemon" << endl;
        cout << "2. Challenge " << gymLeader << endl;
        cout << "3. Manage your Pokemon" << endl;
        cout << "4. Go to Store" << endl;
        cout << "5. Save and Quit Game" << endl;
        userInput = getInt(1, 5);
    }
    return 0;
}

void inToTheWild_page3I(vector<Pokemon> &list) {
    vector<Pokemon> inhabitedPokemon;
    if (Player::getLoadingTheGameInAWhile()) {
        clearConsole();
        cout << "Which wild area do you want to go to?" << endl;
        cout << "1. Novice Haven - Beginner's area" << endl;
        printFile("NoviceHaven.txt");
        pressToContinue();
        clearConsole();
        cout << "Which wild area do you want to go to?" << endl;
        cout << "2. Apprentice Outskirts - Slightly more challenging than Novice Haven" << endl;
        printFile("ApprenticeOutskirts.txt");
        pressToContinue();
        clearConsole();
        cout << "Which wild area do you want to go to?" << endl;
        cout << "3. Amateur Enclave - A step up in difficulty for those gaining experience" << endl;
        printFile("AmateurEnclave.txt");
        pressToContinue();
        clearConsole();
        cout << "Which wild area do you want to go to?" << endl;
        cout << "4. Veteran Valley - A challenging area for seasoned Pokémon trainers" << endl;
        printFile("VeteranValley.txt");
        pressToContinue();
        clearConsole();
        cout << "Which wild area do you want to go to?" << endl;
        cout << "5. Shadow Veil Sanctuary - The dark side of universe" << endl;
        printFile("ShadowVeilSanctuary.txt");
        pressToContinue();
        clearConsole();
        cout << "Which wild area do you want to go to?" << endl;
        cout << "6. Celestial Cosmos - Where the creator of the universe lives";
        printFile("CelestialCosmos.txt");
        pressToContinue();
        Player::setLoadingTheGameInAWhile(false);
    }

    clearConsole();
    cout << "Which wild area do you want to go to?" << endl;
    cout << "1. Novice Haven - Beginner's area" << endl;
    cout << "2. Apprentice Outskirts - Slightly more challenging than Novice Haven" << endl;
    cout << "3. Amateur Enclave - A step up in difficulty for those gaining experience" << endl;
    cout << "4. Veteran Valley - A challenging area for seasoned Pokémon trainers" << endl;
    cout << "5. Shadow Veil Sanctuary - The dark side of universe" << endl;
    cout << "6. Celestial Cosmos - Where the creator of the universe lives";
    switch (getInt(1, 6)) {
        case 1:
            inhabitedPokemon.push_back(Porygon(randGen(3, 7)));
            inhabitedPokemon.push_back(Caterpie(randGen(3, 7)));
            inhabitedPokemon.push_back(Magikarp(randGen(3, 7)));
            inhabitedPokemon.push_back(Psyduck(randGen(3, 5)));
            break;
        case 2:
            inhabitedPokemon.push_back(Bulbasaur(randGen(8, 13)));
            inhabitedPokemon.push_back(Squirtle(randGen(8, 13)));
            inhabitedPokemon.push_back(Charmander(randGen(8, 15)));
            break;
        case 3:
            inhabitedPokemon.push_back(Pikachu(randGen(15, 25)));
            inhabitedPokemon.push_back(Eevee(randGen(15, 25)));
            inhabitedPokemon.push_back(Seel(randGen(15, 25)));
            inhabitedPokemon.push_back(Victreebel(randGen(20, 30)));
            inhabitedPokemon.push_back(Arcanine(randGen(20, 25)));
            inhabitedPokemon.push_back(Vileplume(randGen(20, 30)));
            break;
        case 4:
            inhabitedPokemon.push_back(Lapras(randGen(25, 40)));
            inhabitedPokemon.push_back(Tangela(randGen(30, 45)));
            inhabitedPokemon.push_back(Gyarados(randGen(40, 45)));
            inhabitedPokemon.push_back(Lucario(randGen(30, 45)));
            inhabitedPokemon.push_back(Charizard(randGen(30, 45)));
            inhabitedPokemon.push_back(Arcanine(randGen(30, 45)));
            inhabitedPokemon.push_back(Blaziken(randGen(30, 45)));
            inhabitedPokemon.push_back(Rapiddash(randGen(30, 45)));
            if (randGen(1, 10) == 1) {
                inhabitedPokemon.push_back(Rayquaza(50));
            }
            break;
        case 5:
            inhabitedPokemon.push_back(Mew(50));
            inhabitedPokemon.push_back(Giratina(50));
            break;
        case 6:
            inhabitedPokemon.push_back(Dialga(100));
            inhabitedPokemon.push_back(Palkia(100));
            break;
        default:
            inhabitedPokemon.push_back(Pikachu(1));
            break;
    }
    int index = randGen(0, int(inhabitedPokemon.size() - 1));
    Pokemon enemy = inhabitedPokemon[index];
    inhabitedPokemon.clear();
    PokemonBattleMainPage_page3(enemy, list);
}

void PokemonBattleMainPage_page3(Pokemon enemy, vector<Pokemon> &list) {
    clearConsole();
    cout << "The wild " << enemy.getName() << " appeared" << endl;
    int numberOfFaintedPokemon(0);
    bool firstInBattle(true);
    int vectorIndex(0);
    for (Pokemon &myPoke: list) {
        if (myPoke.isFainted()) {
            ++vectorIndex;
        }
    }
    int vectorIndexTemp = vectorIndex;
    while (!enemy.isFainted()) {
        clearConsole();
        if (list[vectorIndex].isFainted()) {
            ++vectorIndex;
        }
        if (firstInBattle) {
            displayEnemyHealthAndMyPokemonHealth(list[vectorIndex], enemy, true);
            firstInBattle = false;
        } else if (vectorIndex != vectorIndexTemp) {
            displayEnemyHealthAndMyPokemonHealth(list[vectorIndex], enemy, true);
            vectorIndexTemp = vectorIndex;
        } else {
            displayEnemyHealthAndMyPokemonHealth(list[vectorIndex], enemy, false);
        }
        cout << "What will you do?" << endl;
        cout << "1. Fight" << endl;
        cout << "2. Run" << endl;
        cout << "3. Catch" << endl;
        cout << "What will you do? ";
        switch (getInt(1, 3)) {
            case 1:
                fight_page4(list[vectorIndex], enemy);
                break;
            case 2:
                cout << "You have successfully made your way out!!" << endl;
                goto End;
            case 3:
                if (throwMonsterBall_page4(enemy, list)) {
                    goto End;
                }
        }
        numberOfFaintedPokemon = 0;
        for (Pokemon &i: list) {
            if (i.isFainted()) {
                ++numberOfFaintedPokemon;
            }
        }
        if (numberOfFaintedPokemon == list.size()) {
            int moneyLost = randGen(100, 250);
            cout << "Your pokemon all have fainted!" << endl;
            cout << "You lost " << moneyLost << " coins while running away" << endl;
            Player::decrementMoney(moneyLost);
            clearConsole();
            break;
        }
    }
    End:
    pressToContinue();
    clearConsole();
}

//https://bulbapedia.bulbagarden.net/wiki/Gym_Leader
void inToTheGym_page3I(vector<Pokemon> &list) {
    vector<Pokemon> gymLeaderList;
    int numOfBadges = int(Player::getBlueBadge()) + int(Player::getGreenBadge()) + int(Player::getRedBadge());

    int gymLeaderFirstPokemon = (numOfBadges + 1) * 15;
    int gymLeaderSecondPokemon = (numOfBadges + 1) * 16;
    int gymLeaderThirdPokemon = (numOfBadges + 1) * 17;
    string endingMessage;
    if (numOfBadges >= 3) {
        gymLeaderList.push_back(Arceus(100));
        gymLeaderList.push_back(Palkia(100));
        gymLeaderList.push_back(Dialga(100));
        gymLeaderList.push_back(Giratina(100));
        gymLeaderList.push_back(Mew(100));
        gymLeaderList.push_back(Rayquaza(100));
        fightGymLeader_page3(list, gymLeaderList, MASTERNAME);
        clearConsole();
        printFile("EndingCredit2.txt", endingMessage);
        pressToContinue();
        goto Finish;
    }
    cout << "Who do you want to fight?" << endl;
    cout << "1. " << AQUA << endl;
    cout << "2. " << BLAZE << endl;
    cout << "3. " << BLOSSOM << endl;
    cout << "4. I am ready to fight" << endl;
    switch (getInt(1, 4)) {
        case 1:
            gymLeaderList.push_back(Seel(gymLeaderFirstPokemon));
            gymLeaderList.push_back(Psyduck(gymLeaderSecondPokemon));
            gymLeaderList.push_back(Lapras(gymLeaderThirdPokemon));
            fightGymLeader_page3(list, gymLeaderList, AQUA);
            break;
        case 2:
            gymLeaderList.push_back(Rapiddash(gymLeaderFirstPokemon));
            gymLeaderList.push_back(Blaziken(gymLeaderSecondPokemon));
            gymLeaderList.push_back(Arcanine(gymLeaderThirdPokemon));
            fightGymLeader_page3(list, gymLeaderList, BLAZE);
            break;
        case 3:
            gymLeaderList.push_back(Vileplume(gymLeaderFirstPokemon));
            gymLeaderList.push_back(Victreebel(gymLeaderSecondPokemon));
            gymLeaderList.push_back(Tangela(gymLeaderThirdPokemon));
            fightGymLeader_page3(list, gymLeaderList, BLOSSOM);
            break;
        default:
            cout << "Exiting the Gym" << endl;
            pressToContinue();
            goto Finish;
            break;
    }
    gymLeaderList.clear();
    numOfBadges = int(Player::getBlueBadge()) + int(Player::getGreenBadge()) + int(Player::getRedBadge());
    endingMessage = "Congratulations!\nYou have defeated all of the gym leaders!\n Thank you for Playing!"
                    "\nCreated By:\nWonjoon Jun\nBonggyu Seo\nKangmuk Jang";
    if (numOfBadges >= 3) {
        printFile("EndingCredit1.txt", endingMessage);
        this_thread::sleep_for(chrono::seconds(8));
        clearConsole();
        printFile("EndingCredit2.txt", endingMessage);
        pressToContinue();
    }
    Finish:
    clearConsole();
}

void ManagePokemon_page3(vector<Pokemon> &list) {
    cout << "1. Heal your Pokemon" << endl;
    cout << "2. Sort your Pokemon" << endl;
    cout << "3. Show your Collection" << endl;
    cout << "4. return to main page" << endl;
    int userInput = getInt(1, 4);
    switch (userInput) {
        case 1:
            healPokemon_page4(list);
            cout << "Your Pokemons are healed!!" << endl;
            pressToContinue();
            clearConsole();
            break;
        case 2:
            sortPokemon_page4(list);
            break;
        case 3:
            showCollection_page4(list);
            break;
        default:
            clearConsole();
            break;
    }
}

void fightGymLeader_page3(vector<Pokemon> &list, vector<Pokemon> &enemyList, const string &nameOfGymLeader) {
    int numberOfFaintedGymPokemon(0);
    int vectorIndexEnemy(0);
    bool firstInBattle(true);
    int myVectorIndex(0);
    int myVectorIndexTemp = myVectorIndex;
    int vectorIndexEnemyPrevious = vectorIndexEnemy;
    Pokemon enemy = enemyList[vectorIndexEnemy];
    string gymLeader;
    if (nameOfGymLeader == AQUA || nameOfGymLeader == BLAZE || nameOfGymLeader == BLOSSOM) {
        gymLeader = "gym leader ";
    } else {
        gymLeader = "POKEMON MASTER ";
    }
    if (nameOfGymLeader == MASTERNAME) {
        cout << "You challenged the " << gymLeader << MASTERNAME << "!" << endl;
        //We have gotten Kangmuk's permission to use this ASCII art.
        printFile("MasterKangmuk.txt");
        pressToContinue();
    }
    cout << "The " << gymLeader << nameOfGymLeader << " sent out " << enemyList[vectorIndexEnemy].getName()
         << endl;
    while (true) {
        clearConsole();
        if (vectorIndexEnemy != vectorIndexEnemyPrevious) {
            cout << "The " << gymLeader << nameOfGymLeader << " sent out " << enemyList[vectorIndexEnemy].getName()
                 << endl;
            vectorIndexEnemyPrevious = vectorIndexEnemy;
        }
        myVectorIndex = 0;
        for (Pokemon &myPoke: list) {
            if (myPoke.isFainted() && myVectorIndex < list.size() - 1) {
                ++myVectorIndex;
            }
        }
        while (!enemyList[vectorIndexEnemy].isFainted() && !list[myVectorIndex].isFainted()) {
            if (list[myVectorIndex].isFainted() && myVectorIndex < list.size() - 1) {
                ++myVectorIndex;
            }
            if (firstInBattle) {
                displayEnemyHealthAndMyPokemonHealth(list[myVectorIndex], enemyList[vectorIndexEnemy], true);
                firstInBattle = false;
            } else if (myVectorIndex != myVectorIndexTemp) {
                displayEnemyHealthAndMyPokemonHealth(list[myVectorIndex], enemyList[vectorIndexEnemy], true);
                myVectorIndexTemp = myVectorIndex;
            } else {
                displayEnemyHealthAndMyPokemonHealth(list[myVectorIndex], enemyList[vectorIndexEnemy], false);
            }
            fight_page4(list[myVectorIndex], enemyList[vectorIndexEnemy]);
            clearConsole();
        }
        if (vectorIndexEnemy < enemyList.size() - 1 && enemyList[vectorIndexEnemy].isFainted()) {
            ++vectorIndexEnemy;
        }

        if (vectorIndexEnemy == enemyList.size() - 1 && enemyList[vectorIndexEnemy].isFainted()) {
            break;
        }

        if (myVectorIndex == list.size() - 1 && list[myVectorIndex].isFainted()) {
            cout << "Your pokemon all have fainted!" << endl;
            cout << "You lost to " << nameOfGymLeader << "!" << endl;
            pressToContinue();
            goto End;
        }
    }
    cout << "Congratulation! You defeated " << nameOfGymLeader << "!" << endl;
    if (nameOfGymLeader == AQUA && !Player::getBlueBadge()) {
        Player::earnBlueBadge();
    } else if (nameOfGymLeader == BLAZE && !Player::getRedBadge()) {
        Player::earnRedBadge();
    } else if (nameOfGymLeader == BLOSSOM && !Player::getGreenBadge()) {
        Player::earnGreenBadge();
    }
    pressToContinue();
    End:
    clearConsole();
}


void healPokemon_page4(vector<Pokemon> &list) {
    for (Pokemon &i: list) {
        i.healPokemon();
    }
}

void fight_page4(Pokemon &myPokemon, Pokemon &enemy) {
    Attacks userAttack;
    Attacks enemyAttack;
    string myPokemonName = myPokemon.getName();
    string enemyPokemonName = enemy.getName();
    bool isMyPokemonFaster = (myPokemon.getSpeed() > enemy.getSpeed());
    //If the pokemons are same speed who goes first is randomly selected with 50% chance.
    bool isMyPokemonSameSpeed = (myPokemon.getSpeed() == enemy.getSpeed()) && bool(randGen(0, 1));
    int moneyEarned = randGen(enemy.getLevel() * 10, enemy.getLevel() * 15);
    if (myPokemonName == enemy.getName()) {
        myPokemonName += " (mine)";
        enemyPokemonName += " (opponent)";
    }
    if (!myPokemon.isFainted() && !enemy.isFainted()) {
        userAttack = myPokemon.selectAttack();
        enemyAttack = autoAttack(enemy, myPokemon);
        if (isMyPokemonFaster || isMyPokemonSameSpeed) {
            clearConsole();
            damageStep_page4I(myPokemon, userAttack, enemy, false);
            this_thread::sleep_for(chrono::seconds(3));
            if (!enemy.isFainted()) {
                clearConsole();
                damageStep_page4I(enemy, enemyAttack, myPokemon, true);
                this_thread::sleep_for(chrono::seconds(3));
                if (myPokemon.isFainted()) {
                    cout << myPokemonName << " fainted!" << endl;
                    pressToContinue();
                    clearConsole();
                }
            } else {
                cout << enemyPokemonName << " fainted!" << endl;
                cout << "Your pokemon get xp and you get coins!" << endl;
                update(myPokemon);
                Player::incrementMoney(moneyEarned);
                pressToContinue();
                clearConsole();
            }
        } else {
            clearConsole();
            damageStep_page4I(enemy, enemyAttack, myPokemon, true);
            this_thread::sleep_for(chrono::seconds(3));
            if (!myPokemon.isFainted()) {
                clearConsole();
                damageStep_page4I(myPokemon, userAttack, enemy, false);
                this_thread::sleep_for(chrono::seconds(3));
                if (enemy.isFainted()) {
                    cout << enemyPokemonName << " fainted!" << endl;
                    cout << "Your pokemon get xp and you get coins!" << endl;
                    update(myPokemon);
                    Player::incrementMoney(moneyEarned);
                    pressToContinue();
                    clearConsole();
                }
            } else {
                cout << myPokemonName << " fainted!" << endl;
                pressToContinue();
                clearConsole();
            }
        }
    }
}

Attacks autoAttack(Pokemon &attacker, Pokemon &defender) {
    int maxDamage(INT_MIN);
    int vectorIndex(0);
    vector<Attacks> attacks;
    for (Attacks i: attacker.abilities) {
        if (!i.getName().empty() && i.getCurrentPP() > 0) {
            attacks.push_back(i);
        }
    }
    int currentAttack(-1);
    for (int index = 0; index < attacks.size(); ++index) {
        currentAttack = damageCalculationAuto_page4I(attacker, attacks[index], defender);
        if (currentAttack > maxDamage) {
            vectorIndex = index;
            maxDamage = currentAttack;
        }
    }
    Attacks attackToReturn;
    attackToReturn = attacks[vectorIndex];
    return attackToReturn;
}

int damageStep_page4I(Pokemon &attacker, Attacks attack, Pokemon &defender, bool isAttackerEnemy) {
    float stab(1);
    float effectivity(1);
    string printAtEnd;
    if (!attack.getImmuneAgainstTypes().empty()) {
        for (string i: attack.getImmuneAgainstTypes()) {
            if (i == defender.getType1() || i == defender.getType2()) {
                if (isAttackerEnemy) {
                    displayEnemyHealthAndMyPokemonHealth(defender, attacker);
                } else {
                    displayEnemyHealthAndMyPokemonHealth(attacker, defender);
                }
                cout << "The " << attacker.getName() << " used " << attack.getName() << "!" << endl;
                cout << "The " << defender.getName() << " was immune to " << attack.getName() << "!" << endl;
                return 0;
            }
        }
    }
    if (attack.getAccuracy() >= randGen(1, 100)) {
        int criticalHit = randGen(1, 100);
        if (attack.getAttackType() == attacker.getType1() || attack.getAttackType() == attacker.getType2()) {
            stab = 1.5;
        }
        for (string i: attack.getWeakAgainstTypes()) {
            if (i == defender.getType1()) {
                effectivity /= 2;
            }
            if (i == defender.getType2()) {
                effectivity /= 2;
            }
        }


        if (criticalHit > 90) {
            printAtEnd += "Critical Hit!!\n";
            effectivity = 1;
        }

        for (string i: attack.getStrongAgainstTypes()) {
            if (i == defender.getType1()) {
                effectivity *= 2;
            }
            if (i == defender.getType2()) {
                effectivity *= 2;
            }
        }

        if (effectivity > 1) {
            printAtEnd += "It was super effective!\n";
        }
        if (effectivity < 1) {
            printAtEnd += "It was not effective!\n";
        }
        float damage;
        float attackOverDefense;
        if (attack.getIsAttack()) {
            attackOverDefense = float(attacker.getAttack()) / float(defender.getDefense());
        } else {
            attackOverDefense = float(attacker.getSpecialAttack()) / float(defender.getSpecialDefense());
        }

        damage = (((((float(attacker.getLevel()) * 2) / 5 + 2) *
                    float(float(attack.getAttackPower()) * attackOverDefense)) /
                   50 + 2) * (float(randGen(100, 110)) / 100 + 1) * stab *
                  effectivity);

        defender.decrementCurrentHP(int(damage));
        if (isAttackerEnemy) {
            displayEnemyHealthAndMyPokemonHealth(defender, attacker);
        } else {
            displayEnemyHealthAndMyPokemonHealth(attacker, defender);
        }
        cout << "The " << attacker.getName() << " used " << attack.getName() << "!" << endl;
        cout << printAtEnd;
    } else {
        if (isAttackerEnemy) {
            displayEnemyHealthAndMyPokemonHealth(defender, attacker);
        } else {
            displayEnemyHealthAndMyPokemonHealth(attacker, defender);
        }
        cout << "The " << attacker.getName() << " used " << attack.getName() << "!" << endl;
        cout << "It didn't hit!" << endl;
        return 0;
    }
    return 0;
}

int damageCalculationAuto_page4I(Pokemon &attacker, Attacks attack, Pokemon &defender) {
    float stab(1);
    float effectivity(1);
    float damage = 0;
    if (!attack.getImmuneAgainstTypes().empty()) {
        for (string i: attack.getImmuneAgainstTypes()) {
            if (i == defender.getType1() || i == defender.getType2()) {
                return 0;
            }
        }
    }

    if (attack.getAttackType() == attacker.getType1() || attack.getAttackType() == attacker.getType2()) {
        stab = 1.5;
    }

    for (string weakType: attack.getWeakAgainstTypes()) {
        if (weakType == defender.getType1()) {
            effectivity /= 2;
        }
        if (weakType == defender.getType2()) {
            effectivity /= 2;
        }

        for (string strongType: attack.getStrongAgainstTypes()) {
            if (strongType == defender.getType1()) {
                effectivity *= 2;
            }
            if (strongType == defender.getType2()) {
                effectivity *= 2;
            }
        }


        float attackOverDefense;
        if (attack.getIsAttack()) {
            attackOverDefense = float(attacker.getAttack()) / float(defender.getDefense());
        } else {
            attackOverDefense = float(attacker.getSpecialAttack()) / float(defender.getSpecialDefense());
        }

        damage = (((((float(attacker.getLevel()) * 2) / 5 + 2) *
                    float(float(attack.getAttackPower()) * attackOverDefense)) /
                   50 + 2) * stab * effectivity) * (float(attack.getAccuracy()) / 100);

        return int(damage);
    }
    return int(damage);
}


bool throwMonsterBall_page4(Pokemon p, vector<Pokemon> &list) {
    int input;
    int ballMod;
    int f;
    int d;
    float catchRate = p.getCatchRate(); // Get the catch rate of the Pokémon
    float hpCurrent = p.getCurrentHP();
    float hpMax = p.getMaxHp();
    float hpPercentage = (hpCurrent * 100) / hpMax; // Calculate HP percentage

    Start:
    if ((Player::getNumOfMonsterBall() + Player::getNumOfSuperBall() + Player::getNumOfMasterBall()) == 0) {
        cout << "You have no balls left!!" << endl;
        cout << "You need to buy more balls" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        return false;
    }

    cout << "1. Throw Monster Ball (" << Player::getNumOfMonsterBall() << ")" << endl;
    cout << "2. Throw Super Ball (" << Player::getNumOfSuperBall() << ")" << endl;
    cout << "3. Throw Master Ball (" << Player::getNumOfMasterBall() << ")" << endl;
    input = getInt(1, 3);

    if (input == 1) {
        if (Player::getNumOfMonsterBall() > 0) {
            ballMod = 255; // Ball modifier for Poke Ball
            Player::decrementMonsterBall();
        } else {
            cout << "You have no monster balls left!!" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            goto Start;
        }
    } else if (input == 2) {
        if (Player::getNumOfSuperBall() > 0) {
            ballMod = 200; // Ball modifier for Super Ball
            Player::decrementSuperBall();
        } else {
            cout << "You have no super balls left!!" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            goto Start;
        }
    } else {
        if (Player::getNumOfMasterBall() > 0) {
            clearConsole();
            printFile("openBall.txt");
            this_thread::sleep_for(chrono::seconds(2));
            cout << "The Ball shakes once" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "The Ball shakes twice" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "Ball shakes three times" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            printFile("ball.txt");
            cout << "Congratulations! You caught " << p.getName() << "!!" << endl;
            makeNickname(p);
            list.push_back(p);
            Player::decrementMasterBall();
            return true;
        } else {
            cout << "You have no master balls left!!" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            goto Start;
        }
    }

    d = (catchRate * 100) / ballMod;
    if (d >= 256) {
        // Ball shakes three times before the Pokémon breaks free
        clearConsole();
        printFile("openBall.txt");
        this_thread::sleep_for(chrono::seconds(2));
        cout << "The Pokemon broke free!" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        return false;
    }

    if (hpPercentage < 50) {
        // Modify the capture rate based on HP percentage
        f = max(int(((hpMax) * 255 * 4) / (hpCurrent * ballMod)), 10);
        f = min(f, 255); // f should be between 10 and 255
        // Apply a 20% chance for the Monster Ball
        if (randGen(0, 99) < 20) {
            clearConsole();
            printFile("openBall.txt");
            this_thread::sleep_for(chrono::seconds(2));
            cout << "The Ball shakes once" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "The Ball shakes twice" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "Ball shakes three times" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            printFile("ball.txt");
            cout << "Congratulations! You caught " << p.getName() << "!!" << endl;
            makeNickname(p);
            list.push_back(p);
            return true;
        }
    } else {
        // Higher catch rate for Pokémon with 50% or more HP
        f = 5;
        // Apply a 5% chance for Pokémon with 50% or more HP
        if (randGen(0, 99) < 5) {
            clearConsole();
            printFile("openBall.txt");
            this_thread::sleep_for(chrono::seconds(2));
            cout << "The Ball shakes once" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "The Ball shakes twice" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "Ball shakes three times" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            printFile("ball.txt");
            cout << "Congratulations! You caught " << p.getName() << "!!" << endl;
            makeNickname(p);
            list.push_back(p);
            return true;
        }
    }

    int x = (d * f) / 255 + 10;
    if (x < 10) {
        // Ball misses the Pokémon completely
        cout << "The Ball misses the Pokemon completely!" << endl;
    } else if (x < 30) {
        // Ball shakes once before the Pokémon breaks free
        clearConsole();
        printFile("openBall.txt");
        this_thread::sleep_for(chrono::seconds(2));
        cout << "The Ball shakes once" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        cout << "But the Pokemon broke free!" << endl;
        this_thread::sleep_for(chrono::seconds(2));
    } else if (x < 70) {
        // Ball shakes twice before the Pokémon breaks free
        clearConsole();
        printFile("openBall.txt");
        this_thread::sleep_for(chrono::seconds(2));
        cout << "The Ball shakes once" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        cout << "The Ball shakes twice" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        cout << "But the Pokemon broke free!" << endl;
        this_thread::sleep_for(chrono::seconds(2));
    } else {
        // Ball shakes three times before the Pokémon breaks free
        clearConsole();
        printFile("openBall.txt");
        this_thread::sleep_for(chrono::seconds(2));
        cout << "The Ball shakes once" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        cout << "The Ball shakes twice" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        cout << "Ball shakes three times" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        cout << "But the Pokemon broke free!" << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }
    return false;
}


void visitStore_page3(vector<Pokemon> &list) {
    cout << "Welcome to the Store!" << endl;
    cout << "You currently have " << Player::getMoney() << " coins!" << endl;
    cout << "1. Buy Monster Balls" << endl;
    cout << "2. Buy Technical Machines" << endl;
    cout << "3. Exit the store" << endl;
    switch (getInt(1, 3)) {
        case 1:
            buyMonsterBalls_page4();
            break;
        case 2:
            buyTM_page4(list);
            break;
        default:
            cout << "Exiting the store" << endl;
            pressToContinue();
    }
    clearConsole();
}

void buyMonsterBalls_page4() {
    clearConsole();
    cout << "1. Buy Monster Ball (100 coins)" << endl;
    cout << "2. Buy Super Ball (500 coins)" << endl;
    cout << "3. Buy Master Ball (10000 coins)" << endl;
    cout << "4. Exit Store" << endl;
    int amount(0);
    switch (getInt(1, 4)) {
        clearConsole();
        case 1:
            cout << "How many Monster Balls do you want to buy?" << endl;
            amount = getInt(0,INT_MAX);
            if (Player::getMoney() >= 100 * amount) {
                Player::decrementMoney(100 * amount);
                Player::incrementMonsterBall(amount);
                cout << "You bought " << amount << " Monster Ball!" << endl;
            } else {
                cout << "Not enough money to buy"<< amount << "Monster Ball!" << endl;
            }
            break;
        case 2:
            cout << "How many Super Balls do you want to buy?" << endl;
            amount = getInt(0,INT_MAX);
            if (Player::getMoney() >= 500 * amount) {
                Player::decrementMoney(500 * amount);
                Player::incrementSuperBall(amount);
                cout << "You bought " << amount << " Super Ball!" << endl;
            } else {
                cout << "Not enough money to buy"<< amount << "Super Ball!" << endl;
            }
            break;
        case 3:
            cout << "How Many do you want to buy?" << endl;
            amount = getInt(0,INT_MAX);
            if (Player::getMoney() >= 10000 * amount) {
                Player::decrementMoney(10000 * amount);
                Player::incrementMasterBall(amount);
                cout << "You bought " << amount << " Master Ball!" << endl;
            } else {
                cout << "Not enough money to buy"<< amount << "Master Ball!" << endl;
            }
            break;
        default:
            cout << "Exiting Store." << endl;
            break;
    }
    pressToContinue();
}

void buyTM_page4(vector<Pokemon> &list) {
    int count(0);
    Attacks TM;
    clearConsole();
    cout << "Which TM do you want to buy?" << endl;
    for (string nameOfAttack: ARRAYOFATTACKNAMES) {
        ++count;
        cout << count << ". " << nameOfAttack << " TM (2500 coins)" << endl;
    }
    cout << count + 1 << ". Exit the store." << endl;

    int userInputForTM = getInt(1, count + 1) - 1;
    if (userInputForTM == count) {
        goto End;
    }
    clearConsole();
    TM = attackConstructor(ARRAYOFATTACKNAMES[userInputForTM]);
    cout << "\b";
    TM.displayAttackStats();
    cout << "Do you want to purchase " << TM.getName() << " TM? (y/n): ";
    if (getYN() == "n") {
        goto End;
    }
    if (Player::getMoney() >= 2500) {
        Player::decrementMoney(2500);
        cout << "Which pokemon do you want to use TM to? " << endl;
        count = 0;
        for (Pokemon myPokemon: list) {
            ++count;
            cout << count << ". " << myPokemon.getName() << endl;
        }
        Pokemon &pokemon = list[getInt(1, count) - 1];
        pokemon.swapAttack(TM);
    } else {
        cout << "Not enough money to buy a " << ARRAYOFATTACKNAMES[userInputForTM] << " TM!" << endl;
        pressToContinue();
    }
    End:
    clearConsole();
}

void displayEnemyHealthAndMyPokemonHealth(Pokemon &mine, Pokemon &enemy, bool withDelay) {
    enemy.printFilePokemon(true);
    enemy.displayCurrentHPLevelAndName(enemy.getName(), true);
    if (withDelay) {
        cout << "\nGo " << mine.getName() << "!!" << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }
    mine.printFilePokemon();
    mine.displayCurrentHPLevelAndName();
}

void sortPokemon_page4(vector<Pokemon> &list) {
    if (list.size() <= 1) {
        cout << "You need two or more Pokemon to sort!" << endl;
        goto End;
    }
    clearConsole();
    cout << "1. Sort Pokemon Manually" << endl;
    cout << "2. Sort Pokemon Automatically by strength" << endl;
    switch (getInt(1, 2)) {
        case 1:
            while (true) {
                clearConsole();
                int nthPokemon(0);
                cout << "Choose a pokemon to Swap! Press 0 to exit!" << endl;
                for (Pokemon i: list) {
                    ++nthPokemon;
                    cout << nthPokemon << ". " << i.getName() << endl;
                }
                int userInput1 = getInt(0, nthPokemon);
                if (userInput1 == 0) {
                    break;
                }
                cout << "What Pokemon do you want to swap " << list[userInput1 - 1].getName() << " with?" << endl;
                nthPokemon = 0;
                for (Pokemon i: list) {
                    ++nthPokemon;
                    cout << nthPokemon << ". " << i.getName() << endl;
                }
                int userInput2 = getInt(1, nthPokemon);
                if (userInput1 == userInput2) {
                    cout << "You picked the same pokemon!" << endl;
                    pressToContinue();
                    clearConsole();
                    continue;
                }
                swap(list[userInput1 - 1], list[userInput2 - 1]);
                clearConsole();
                cout << "Successfully swapped " << list[userInput1 - 1].getName() << " with "
                     << list[userInput2 - 1].getName() << "!" << endl << endl;
            }
            break;
        case 2:
            clearConsole();
            sort(list.begin(), list.end());
            cout << "Successfully sorted your Pokemons by strength!" << endl;
            break;
        default:
            cout << "Error have occurred" << endl;
            break;
    }
    End:
    pressToContinue();
    clearConsole();
}
