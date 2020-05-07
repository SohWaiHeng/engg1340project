#include<iostream>
#include "../hfiles/titleScreen.h"
#include "../hfiles/battle.h"
#include "../hfiles/tutorial.h"
#include "../hfiles/menu.h"
#include "../hfiles/movement.h"
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
    string avatarSymbol = avatar.getfigure();  // avatar figure
    string enemySymbol = "(^<^)";  // enemy figure
    string newBlock = "../txt/out.txt";
    int option;

    // print title screen, take in user's input, get the save file's name
    filename = titleScreen(option);

    // load data from file
    load(filename, ownedhead, avataridx, currentcurrency, currentcoordinate, currentblock, currentavatar, deck);
    
    // start tutorial if new game
    if (option == 1) {
        cout << "STARTING A NEW GAME..." << endl;
        delay(2);
        tutorial();
    }

    int flag = 0;
    while (flag != 3) {
        // quit from menu
        if (flag == 0) {
            opponent newopponent;
            for (int i = 0; i < 5; i++) {
                newopponent.opponentCreature[i].setbasestats(i+1);
                newopponent.opponentCreature[i].setcurrentstats(1);
            }
            battle(deck, newopponent);
        }
        else if (flag == 1) {
            mainMenuPage(currentcurrency, currentavatar, deck, filename, ownedhead, avataridx, currentcoordinate, currentblock, flag);
        }
        else if (flag == 2) {
            moveAroundMap(currentavatar, currentcoordinate, currentblock, flag);
        }
    }

    return 0;
}
