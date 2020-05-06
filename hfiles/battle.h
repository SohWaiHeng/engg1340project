#ifndef BATTLE_H
#define BATTLE_H
#include "../classes/creature.h"
#include <string>

struct rewardstruct {
    int gold;
    int food;
    int creatureidx;
};

struct opponent {
    creature opponentCreature[5];
    rewardstruct rewards;
};

struct deployed {
    creature deployedCreature;
    deployed * next;
};

struct cardOnHand {
    card theCard;
    cardOnHand * next;
};

int numberOfCards (cardOnHand * cardhead);
int numberOfCreatures (deployed * head);
void printBattleScreen(deployed * player, cardOnHand * cardhead, deployed * opponent, int currentElixir, creature deck[]);

//void deploy (int &currentElixir, creature deck[], deployed * &head);
//void initialiseCard (cardOnHand * &cardhead, creature deck[], int push);
int drawCard (creature &toBeDrawnFrom);
void addCardToHand (cardOnHand * &cardhead, card toBeAdded);
void death (deployed * &creaturenode, deployed * &head);
//void attack (deployed * &player, deployed * &opponent, cardOnHand * &playerscard, int &currentElixir);
//void playersMove (deployed * &player, deployed * &opponent, int &currentElixir, creature deck[], cardOnHand * &playerscard);
//void setopponent(opponent &currentOpponent);
//void repeatedPrinting (char start, char toBePrinted, int times, char end);
//void printingCreature (int totalSpace, int creatureSpace, deployed * player, char indicator);\
//void printingCard (int totalSpace, int cardSpace, cardOnHand * playerscard, char indicator, int currentElixir);
//void printBattleScreen(deployed * player, cardOnHand * cardhead, deployed * opponent, int currentElixir);
void opponentsResponse (creature deck[], int &elixir, deployed * &head, cardOnHand * &cardhead, deployed * &playerhead);
//void battleResults();
//void use (deployed *&player, deployed * &opponent, int &currentElixir, cardOnHand playerscard);
//void removeCardFromHand();
void tutorialmode (creature deck[], opponent currentOpponent);
void battle (creature deck[], opponent currentOpponent);
void delay(double number_of_seconds);

#endif