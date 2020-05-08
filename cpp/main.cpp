#include<iostream>
#include "../hfiles/titleScreen.h"
#include "../hfiles/battle.h"
#include "../hfiles/tutorial.h"
#include "../hfiles/menu.h"
#include "../hfiles/movement.h"
#include "../hfiles/colours.h"

#include "../classes/creature.h"
#include "../classes/avatar.h"
#include "../classes/currency.h"

using namespace std;

int main () {
    // all variables necessary to the game
    creature deck[5];           // current deck
    owned * ownedhead = NULL;   // head of linked list of all creatures player owns
    int avataridx[10] = {0};    // array to store the avatar player owned
    avatar currentavatar;       // current avatar 
    currency currentcurrency;   // current currency
    int currentcoordinate[2];   // current avatar coordinate
    int enemyCoordinate[2];     // enemy coordinate
    string currentblock;        // current block file name
    string filename;            // save file location name
    string avatarSymbol = currentavatar.getfigure();  // avatar figure
    opponent currentOpponent;
    string enemySymbol = "(^<^)";  // enemy figure
    string newBlock = "../txt/out.txt";
    int option;

    // print title screen, take in user's input, get the save file's name
    filename = titleScreen(option);

    // load data from file
    load(filename, ownedhead, avataridx, currentcurrency, currentcoordinate, currentblock, currentavatar, deck);
    determineopponent("random", currentOpponent, deck);

    // start tutorial if new game
    if (option == 1) {
        cout << "STARTING A NEW GAME..." << endl;
        delay(2);
        bool winlose = false;
        tutorial(currentcoordinate,enemyCoordinate,avatarSymbol,enemySymbol,currentblock,newBlock, currentOpponent, winlose, deck);
        cout << BLUE << "Now go and defeat more opponent, level up yourself and prepare yourself for the final boss!" << WHITE << endl;
    }

    int flag = 0;
    string battlemode = "random";
    while (flag != 3) {
        if (flag == 0) {
            moveAroundMap(currentcoordinate,enemyCoordinate,avatarSymbol,enemySymbol,currentblock,newBlock, flag, battlemode);
        }
        else if (flag == 1) {
            bool winlose = false;
            determineopponent(battlemode, currentOpponent, deck);
            battle(deck, currentOpponent, winlose);
            for (int i = 0; i < 5; i++) {
                deck[i].setdeployed(false);
            }
            if (winlose) {
                delay(1);
                cout << GREEN << "You gained " << currentOpponent.rewards.coins << " coins!" << endl;
                currentcurrency.coins += currentOpponent.rewards.coins;
                delay(1);
                cout << "You gained " << currentOpponent.rewards.food << " food!" << endl;
                currentcurrency.food += currentOpponent.rewards.food;
                delay(1);
                cout << "You gained " << currentOpponent.rewards.gems << " gems!" << endl;
                currentcurrency.gems += currentOpponent.rewards.gems;
                delay(1);
                cout << "You obtained " << currentOpponent.opponentCreature[currentOpponent.rewards.creatureidx].getname() << "!" << WHITE << endl;
                bool own;
                buildLinkedListOfOwnedCreatures(ownedhead, currentOpponent.rewards.creatureidx, 1, own);
                if (own == true) {
                    cout << RED << "You already had this creature. An extra 5 food is given instead" << WHITE << endl;
                    currentcurrency.food += 5;
                }
            }
            flag = 0;
        }
        else if (flag == 2) {
            mainMenuPage(currentcurrency, currentavatar, deck, filename, ownedhead, avataridx, currentcoordinate, currentblock, flag);
        }
    }

    return 0;
}
