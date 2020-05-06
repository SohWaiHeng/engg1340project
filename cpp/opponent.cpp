#include<iostream>
#include<fstream>
#include<sstream>
#include<stdlib.h>
#include<time.h>
#include<dos.h>
#include "../hfiles/battle.h"
using namespace std;

void opponentdeploy (int &currentElixir, creature deck[], deployed * &head, int creatureidx, int position) {
    if (numberOfCreatures(head) == 4) {
        return;
    }
    
    if (deck[creatureidx].getdeployed() == true) {
        return;
    }
    
    currentElixir--;
    cout << "Opponent deployed " << deck[creatureidx].getname() << "." << endl;
    cout << endl;

    deployed * newdeployed = new deployed;
    newdeployed->deployedCreature = deck[creatureidx];
    deck[creatureidx].setdeployed(true);
    
    int i = 1;
    deployed * currentnode = head;
    deployed * previousnode = NULL;
    while (i < position && currentnode != NULL) {
        previousnode = currentnode;
        currentnode = currentnode->next;
        i++;
    }
    newdeployed->next = currentnode;
    if (previousnode == NULL) {
        head = newdeployed;
    }
    else {
        previousnode->next = newdeployed;
    }
    return;
}

void opponentattack (deployed * &player, deployed * &opponent, cardOnHand * &playerscard, int &currentElixir, deployed * &attackernode, deployed * &targetnode) {
    if (attackernode->deployedCreature.getcost() > currentElixir) {
        return;
    }
    
    currentElixir = currentElixir - attackernode->deployedCreature.getcost();
    cout << "Opponent attacked your " << targetnode->deployedCreature.getname() << " with his " << attackernode->deployedCreature.getname() << "!" << endl;

    if (targetnode->deployedCreature.getstatus("blind") > 0) {
        cout << "MISSED!" << endl;
        cout << endl;
        targetnode->deployedCreature.setstatus("blind", -1);
    }
    else {
        bool critical = false;
        int byHowMuch = attackernode->deployedCreature.getatk(critical);
        targetnode->deployedCreature.decreasehp(byHowMuch);
        if (critical == true) {
            cout << "CRITICAL ATTACK !!!" << endl;
        }
        cout << targetnode->deployedCreature.getname() << " damaged by " << byHowMuch << " hp." << endl;
        cout << endl;
        attackernode->deployedCreature.thorns(byHowMuch, targetnode->deployedCreature);
    }

    if (attackernode->deployedCreature.getstatus("blockcard") > 0) {
        attackernode->deployedCreature.setstatus("blockcard", -1);
    }
    else if (numberOfCards(playerscard) < 10) {
        int idxOfCardDrawn = drawCard(attackernode->deployedCreature);
        addCardToHand(playerscard, attackernode->deployedCreature.cardpool[idxOfCardDrawn]);
        attackernode->deployedCreature.cardpool[idxOfCardDrawn].cardDrawn();
    }

    if (attackernode->deployedCreature.getstatus("atk") != 0) {
        attackernode->deployedCreature.atk(0);
    }

    attackernode->deployedCreature.elixirsap(targetnode->deployedCreature, currentElixir, true);

    if (targetnode->deployedCreature.gethp() <= 0) {
        death(targetnode, player);
    }
    if (attackernode->deployedCreature.gethp() <= 0) {
        death(attackernode, opponent);

        targetnode->deployedCreature.counteratk(opponent->deployedCreature);

        targetnode->deployedCreature.elixirsap(opponent->deployedCreature, currentElixir, true);

        if (player->deployedCreature.gethp() <= 0) {
            death (attackernode, opponent);
        }
        if (targetnode->deployedCreature.gethp() <= 0) {
            death(targetnode, player);
        }
    }
    if (targetnode->deployedCreature.gethp() >= 0 && attackernode->deployedCreature.gethp() >= 0) {
        targetnode->deployedCreature.counteratk(attackernode->deployedCreature);
        
        if (attackernode->deployedCreature.gethp() <= 0) {
            death (attackernode, opponent);
        }
        if (targetnode->deployedCreature.gethp() <= 0) {
            death(targetnode, player);
        }
    }
    return;
}

// indicator true: used on opponent (ai) creature
void opponentuse (deployed *&player, deployed * &opponent, int &currentElixir, cardOnHand * &playerscard, bool indicator, cardOnHand * &cardnode, deployed * &creaturenode1, deployed * &targetnode) {
    if (cardnode->theCard.getcost() > currentElixir) {
        return;
    }
    
    if (creaturenode1->deployedCreature.getstatus("silence") > 0) {
        return;
    }
    
    deployed * previousnode = NULL;
    if (indicator) {
        previousnode = opponent;
        if (previousnode == creaturenode1) {
            previousnode = NULL;
        }
        else {
            while (previousnode->next != creaturenode1) {
                previousnode = previousnode->next;
            }
        }
    }
    else {
        previousnode = player;
        if (previousnode == creaturenode1) {
            previousnode = NULL;
        }
        else {
            while (previousnode->next != creaturenode1) {
                previousnode = previousnode->next;
            }
        }
    }
    
    currentElixir = currentElixir - cardnode->theCard.getcost();
    cout << "Opponent used \"" << cardnode->theCard.getname() << "\" on " << creaturenode1->deployedCreature.getname() << " -> ";

    string trash;
    string cardFunction = cardnode->theCard.getfunction(trash);
    cout << trash << endl;
    istringstream iss2 (cardFunction);

    string condition;
    bool area = false;
    string own;
    string enemy;
    string card;
    int number;

    while (iss2 >> condition) {
        iss2 >> trash;
        iss2 >> number;

        if (condition == own) {
            number = number * numberOfCreatures(opponent);
        }
        else if (condition == enemy) {
            number = number * numberOfCreatures(player);
        }
        else if (condition == card) {
            number = number * numberOfCards(playerscard);
        }

        if (condition == "area") {
            area = true;
        }
        else if (condition == "remove") {
            string statusname[] = {"counteratk", "haste", "atk", 
                            "magic", "shield", "elixirsap", "addelixir", "drawcard", 
                            "heal", "directdmg", "niceland", 
                            "thorns", "heroic", "revenge", "defenseup", 
                            "poison", "blind", "silence", "blockcard"};
            creaturenode1->deployedCreature.setstatus(statusname[number], 0);
        }
        else if (condition == "own") {
            string statusname[] = {"counteratk", "haste", "atk", 
                            "magic", "shield", "elixirsap", "addelixir", "drawcard", 
                            "heal", "directdmg", "niceland", 
                            "thorns", "heroic", "revenge", "defenseup", 
                            "poison", "blind", "silence", "blockcard"};
            own = statusname[number-1];
        }
        else if (condition == "enemy") {
            string statusname[] = {"counteratk", "haste", "atk", 
                            "magic", "shield", "elixirsap", "addelixir", "drawcard", 
                            "heal", "directdmg", "niceland", 
                            "thorns", "heroic", "revenge", "defenseup", 
                            "poison", "blind", "silence", "blockcard"};
            enemy = statusname[number-1];
        }
        else if (condition == "card") {
            string statusname[] = {"counteratk", "haste", "atk", 
                            "magic", "shield", "elixirsap", "addelixir", "drawcard", 
                            "heal", "directdmg", "niceland", 
                            "thorns", "heroic", "revenge", "defenseup", 
                            "poison", "blind", "silence", "blockcard"};
            card = statusname[number-1];
        }
        else if (condition == "magic") {
            if (indicator) {
                creaturenode1->deployedCreature.magic(targetnode->deployedCreature);

                if (area) {
                    if (previousnode != NULL) {
                        previousnode->deployedCreature.magic(targetnode->deployedCreature);
                    }
                    if (creaturenode1->next != NULL) {
                        creaturenode1->next->deployedCreature.magic(targetnode->deployedCreature);
                    }
                }

                if (targetnode->deployedCreature.gethp() <= 0) {
                    death(targetnode, player);
                }
            }
            else {
                return;
            }
        }
        else if (condition == "addelixir") {
            if (indicator) {
                creaturenode1->deployedCreature.addelixir(currentElixir, number);
            }
            else {
                return;
            }
        }
        else if (condition == "drawcard") {
            for (int i = 0; i < number; i++) {
                if (numberOfCards(playerscard) < 10) {
                    int idxOfCardDrawn = drawCard(creaturenode1->deployedCreature);
                    addCardToHand(playerscard, creaturenode1->deployedCreature.cardpool[idxOfCardDrawn]);
                    creaturenode1->deployedCreature.cardpool[idxOfCardDrawn].cardDrawn();
                    if (area) {
                        if (previousnode != NULL) {
                            idxOfCardDrawn = drawCard(previousnode->deployedCreature);
                            addCardToHand(playerscard, previousnode->deployedCreature.cardpool[idxOfCardDrawn]);
                            previousnode->deployedCreature.cardpool[idxOfCardDrawn].cardDrawn();
                        }
                        if (creaturenode1->next != NULL) {
                            idxOfCardDrawn = drawCard(creaturenode1->next->deployedCreature);
                            addCardToHand(playerscard, creaturenode1->next->deployedCreature.cardpool[idxOfCardDrawn]);
                            creaturenode1->next->deployedCreature.cardpool[idxOfCardDrawn].cardDrawn();
                        }
                    }
                } 
                else {
                    i = number;
                }
            }
            cout << number << " card drawn from " << creaturenode1->deployedCreature.getname() << endl;
            if (area) {
                if (previousnode != NULL) {
                    cout << number << " card drawn from " << previousnode->deployedCreature.getname() << endl;
                }
                if (creaturenode1->next != NULL) {
                    cout << number << " card drawn from " << creaturenode1->next->deployedCreature.getname() << endl;
                }
            }
        }
        else if (condition == "atk") {
            creaturenode1->deployedCreature.atk(number);
            if (area) {
                if (previousnode != NULL) {
                    previousnode->deployedCreature.atk(number);
                }
                if (creaturenode1->next != NULL) {
                    creaturenode1->next->deployedCreature.atk(number);
                }
            }
        } 
        else if (condition == "heal") {
            creaturenode1->deployedCreature.heal(number);
            if (area) {
                if (previousnode != NULL) {
                    previousnode->deployedCreature.heal(number);
                }
                if (creaturenode1->next != NULL) {
                    creaturenode1->next->deployedCreature.heal(number);
                }
            }
        }
        else if (condition == "directdmg") {
            creaturenode1->deployedCreature.directdmg(number);
            if (area) {
                if (previousnode != NULL) {
                    previousnode->deployedCreature.directdmg(number);
                }
                if (creaturenode1->next != NULL) {
                    creaturenode1->next->deployedCreature.directdmg(number);
                }
            }
        }
        else {
            creaturenode1->deployedCreature.setstatus(condition, number);
            if (area) {
                if (previousnode != NULL) {
                    previousnode->deployedCreature.setstatus(condition, number);
                }
                if (creaturenode1->next != NULL) {
                    creaturenode1->next->deployedCreature.setstatus(condition, number);
                }
            }
        }

        creaturenode1->deployedCreature.haste(false);
        if (area) {
            if (previousnode != NULL) {
                previousnode->deployedCreature.haste(false);
            }
            if (creaturenode1->next != NULL) {
                creaturenode1->next->deployedCreature.haste(false);
            }
        }

        iss2 >> trash;
    }
    cout << endl;

    cardOnHand * deleteafter = playerscard;
    if (deleteafter == cardnode) {
        playerscard = cardnode->next;
        delete cardnode;
    }
    else {
        while (deleteafter->next != cardnode) {
            deleteafter = deleteafter->next;
        }
        deleteafter->next = cardnode->next;
        delete cardnode;
    }

    if (creaturenode1->deployedCreature.gethp() <= 0) {
        if (indicator) {
            death(creaturenode1, opponent);
        }
        else {
            death(creaturenode1, player);
        }
    }
    return;
}

void random(int &elixir, creature deck[], deployed * &head, int push, deployed * &playerhead, cardOnHand * &cardhead) {
    srand(time(NULL) + push);
    int firstword = (rand() % 3);

    srand(time(NULL) + push + 1);
    if (firstword == 0) {
        int creatureidx = (rand() % 5);
        int position = (rand() % (numberOfCreatures(head)+1)) + 1;
        opponentdeploy(elixir, deck, head, creatureidx, position);
    }
    else if (firstword == 1) {
        int attacker = (rand() % (numberOfCreatures(head)));
        deployed * attackernode = head;
        for (int i = 0; i < attacker; i++) {
            attackernode = attackernode->next;
        }

        srand(time(NULL) + push + 2);
        int target = (rand() % (numberOfCreatures(playerhead)));
        deployed * targetnode = playerhead;
        for (int i = 0; i < target; i++) {
            targetnode = targetnode->next;
        }

        opponentattack(playerhead, head, cardhead, elixir, attackernode, targetnode);
    }
    else {
        int card = (rand() % numberOfCards(cardhead));
        cardOnHand * cardnode = cardhead;
        for (int i = 0; i < card; i++) {
            cardnode = cardnode->next;
        }

        bool indicator = true;
        string trash;
        istringstream iss (cardnode->theCard.getfunction(trash));
        string function;
        iss >> function;
        while (function == "area" || (function == "remove" || (function == "own" || (function == "enemy" || function == "card")))) {
            iss >> trash;
            iss >> trash;
            iss >> function;
        }
        if (function == "poison" || (function == "blockcard" || (function == "silence" || (function == "blind" || function == "directdmg")))) {
            indicator = false;
        }
    
        deployed * creaturenode1;
        if (indicator) {
            creaturenode1 = head;
        }
        else {
            creaturenode1 = playerhead;
        }

        srand(time(NULL) + push + 2);
        int creatureno = (rand() % numberOfCreatures(creaturenode1));
        for (int i = 0; i < creatureno; i++) {
            creaturenode1 = creaturenode1->next;
        }

        deployed * targetnode = playerhead;
        srand(time(NULL) + push + 3);
        int target = (rand() % numberOfCreatures(playerhead));
        for (int i = 0; i < target; i++) {
            targetnode = targetnode->next;
        }

        opponentuse(playerhead, head, elixir, cardhead, indicator, cardnode, creaturenode1, targetnode);
    }
}

void delay(double number_of_seconds) { 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds); 
} 

void opponentsResponse (creature deck[], int &elixir, deployed * &head, cardOnHand * &cardhead, deployed * &playerhead) {
    if (head == NULL && elixir == 1) {
        srand(time(NULL));
        opponentdeploy(elixir, deck, head, rand() % 5, 1);
        cout << "------------------------------------------------------------------------------" << endl;
        return;
    }
    else if (head == NULL || playerhead == NULL) {
        return;
    }

    int currentElixir = elixir;
    bool actionAvailable = true;
    int push = 0;

    while (elixir > 0 && actionAvailable) {
        // make sure there is some moves left
        delay(1);
        if (head == NULL || playerhead == NULL) {
            return;
        }
        if (numberOfCreatures(head) == 4) {
            actionAvailable = false;
            deployed * currentnode = head;
            while (currentnode != NULL && !actionAvailable) {
                if (currentnode->deployedCreature.getcost() <= elixir) {
                    actionAvailable = true;
                } 
                currentnode = currentnode->next;
            }
            if (!actionAvailable) {
                if (numberOfCards(cardhead) != 0) {
                    cardOnHand * cardnode = cardhead;
                    while (cardnode != NULL && !actionAvailable) {
                        if (cardnode->theCard.getcost() <= elixir) {
                            actionAvailable = true;
                        }
                        cardnode = cardnode->next;
                    }
                    if (!actionAvailable) {
                        break;
                    }
                    else {
                        actionAvailable = false;
                        currentnode = head;
                        while (currentnode != NULL && !actionAvailable) {
                            if (currentnode->deployedCreature.getstatus("silence") <= 0) {
                                actionAvailable = true;
                            }
                            currentnode = currentnode->next;
                        }
                        if (!actionAvailable) {
                            currentnode = playerhead;
                            while (currentnode != NULL && !actionAvailable) {
                                if (currentnode->deployedCreature.getstatus("silence") <= 0) {
                                    actionAvailable = true;
                                }
                                currentnode = currentnode->next;
                            }
                            if (!actionAvailable) {
                                break;
                            }
                        }
                    }
                }
                else {
                    break;
                }
            }
        }

        while (currentElixir == elixir) {
            random(elixir, deck, head, push, playerhead, cardhead);
            push++;
        }

        currentElixir = elixir;
    }

    cout << "------------------------------------------------------------------------------" << endl;
    delay(3);
    return;
}