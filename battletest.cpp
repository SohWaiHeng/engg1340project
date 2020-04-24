#include<iostream>
#include "battle.h"

int main () {
    creature deck[5];
    for (int i = 0; i < 5; i++) {
        deck[i].setbasestats(i+1);
        deck[i].setcurrentstats(1);
    }
    opponent currentOpponent;
    for (int i = 0; i < 5; i++) {
        currentOpponent.opponentCreature[i].setbasestats(i+1);
        currentOpponent.opponentCreature[i].setcurrentstats(1);
    }

    battle(deck, currentOpponent);
    
    return 0;
}