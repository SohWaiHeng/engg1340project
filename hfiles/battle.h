#ifndef BATTLE_H
#define BATTLE_H

#include "../classes/creature.h"

#include <string>

using namespace std;

// rewards of an opponent if defeated
struct rewardstruct {
    int coins;
    int food;
    int gems;
    int creatureidx;
};

// an struct to store an opponent
struct opponent {
    creature opponentCreature[5]; // opponent's deck
    rewardstruct rewards; // opponents rewards
};

// a struct to store a node in the linked list of deployed creatures in battle
struct deployed {
    creature deployedCreature;
    deployed * next;
};

// a struct to store a node in the linked list of cards on a player's hand in battle
struct cardOnHand {
    card theCard;
    cardOnHand * next;
};

int numberOfCards (cardOnHand * cardhead);
int numberOfCreatures (deployed * head);
void printBattleScreen(deployed * player, cardOnHand * cardhead, deployed * opponent, int currentElixir, creature deck[]);

int drawCard (creature &toBeDrawnFrom);
void addCardToHand (cardOnHand * &cardhead, card toBeAdded);
void death (deployed * &creaturenode, deployed * &head);

void determineopponent(string mode, opponent &currentopponent, creature deck[5]);
void opponentsResponse (creature deck[], int &elixir, deployed * &head, cardOnHand * &cardhead, deployed * &playerhead);

void tutorialmode (creature deck[], opponent currentOpponent, bool &winlose);
void battle (creature deck[], opponent currentOpponent, bool &winlose);
void delay(double number_of_seconds);

#endif