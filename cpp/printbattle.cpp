#include<iostream>
#include<sstream>
#include<iomanip>
#include<algorithm>

#include "../hfiles/colours.h"
#include "../hfiles/battle.h"

using namespace std;

// count number of cards on player's hand
// parameter: head of linked list of card on hand
int numberOfCards (cardOnHand * cardhead) {
    int count = 0;
    cardOnHand *currentnode =  cardhead;
    while (currentnode != NULL) {
        count ++;
        currentnode = currentnode->next;
    }
    return count;
}

// count number of player's creatures deployed on field
// parameter : head of linked list of deployed creatures
int numberOfCreatures (deployed * head) {
    int count = 0;
    deployed *currentnode = head;
    while (currentnode != NULL) {
        count ++;
        currentnode = currentnode->next;
    }
    return count;
}

// for printing repeated char
// parameters: starting of the line, the char to be repeatedly printed, times to be printed, end of the line
void repeatedPrinting (char start, char toBePrinted, int times, char end) {
    if (times > 1) {
        cout << start;
        for (int i = 0; i < times-2; i++) {
            cout << toBePrinted;
        }
        cout << end;
    }
    else if (times == 1) {
        cout << toBePrinted;
    }
}

// printing creature section in battle screen
// parameters: total width of battle screen, width to display one creature, head of linked list of player's deployed creature, indicator determines what feature of a creature is to be printed
// indicator: a = print atk, m = print mgc, h = print hp, s = print symbol, n = print name, c = print cost
void printingCreature (int totalSpace, int creatureSpace, deployed * player, char indicator) {
    int blankspace = (totalSpace - 22 - (creatureSpace * numberOfCreatures(player)));
    repeatedPrinting(' ', ' ', blankspace / 2 + blankspace % 2, ' ');
    deployed * creaturenode = player;
    cout << left;
    switch (indicator) {
        case 'a': {
            for (int i = 0; i < numberOfCreatures(player); i++) {
                cout << " atk: " << setw(creatureSpace-6) << creaturenode->deployedCreature.getoriginalatk();
                creaturenode = creaturenode->next;
            }
            break;
        }
        case 'm': {
            for (int i = 0; i < numberOfCreatures(player); i++) {
                cout << " mgc: " << setw(creatureSpace-6) << creaturenode->deployedCreature.getoriginalmgc();
                creaturenode = creaturenode->next;
            }
            break;
        }
        case 'h': {
            for (int i = 0; i < numberOfCreatures(player); i++) {
                cout << " hp:";
                repeatedPrinting(' ', '-', creaturenode->deployedCreature.gethpratio() + 2, ' ');
                cout << setw(creatureSpace - 4 - 2 - creaturenode->deployedCreature.gethpratio()) << creaturenode->deployedCreature.gethp();
                creaturenode = creaturenode->next;
            }
            break;
        }
        case 's': {
            for (int i = 0; i < numberOfCreatures(player); i++) {
                cout << "    " << creaturenode->deployedCreature.getsymbol() << "          ";
                creaturenode = creaturenode->next;
            }
            break;
        }
        case 'n': {
            for (int i = 0; i < numberOfCreatures(player); i++) {
                cout << " ";
                int length = creaturenode->deployedCreature.getname().length();
                if (length <= 13) {
                    repeatedPrinting(' ', ' ', ((13 - length) / 2), ' ');
                    cout << creaturenode->deployedCreature.getname();
                    repeatedPrinting(' ', ' ', ((13 - length) / 2)  + ((13 - length) % 2), ' ');
                    cout << "    ";
                }
                else {
                    cout << setw(17) << creaturenode->deployedCreature.getname();
                }
                cout << "   ";
                creaturenode = creaturenode->next;
            }
            break;
        }
        case 'c': {
            for (int i = 0; i < numberOfCreatures(player); i++) {
                cout << " cost: " << setw(creatureSpace-7) << creaturenode->deployedCreature.getcost();
                creaturenode = creaturenode->next;
            }
            break;
        }
    }
    repeatedPrinting(' ', ' ', blankspace / 2, ' ');
}

// get nth word in a string
// parameter : a sentence of words, value of n (nth word in the sentence)
string getword (string wordlist, int index) {
    string targetword;
    istringstream iss (wordlist);
    for (int i = 0; i <= index; i++) {
        iss >> targetword;
    }
    return targetword;
}

// printing card on hand section in battle screen
// parameters: total width of battle screen, width to display one card, head of linked list of player's cards on hand, indicator determines what feature of a card is to be printed
// indicator: \0 = prints top of card, 1 = prints card index number, c = prints card cost, 0 = prints empty part of a card, \n = prints bottom of card, n = prints name of card
void printingCard (int totalSpace, int cardSpace, cardOnHand * playerscard, char indicator, int currentElixir) {
    int blankspace = (totalSpace - 22 - (cardSpace * numberOfCards(playerscard)));
    repeatedPrinting(' ', ' ', blankspace / 2, ' ');
    cardOnHand * cardnode = playerscard;
    switch (indicator) {
        case '\0': {
            for (int i = 0; i < numberOfCards(playerscard); i++) {
                repeatedPrinting(' ', '_', cardSpace, ' ');
            }
            break;
        }
        case '1': {
            for (int i = 0; i < numberOfCards(playerscard); i++) {
                cout << "|  (" << i+1 << ")   |";  
            }
            break;
        }
        case 'c': {
            for (int i = 0; i < numberOfCards(playerscard); i++) {
                cout << '|' << cardnode->theCard.getcost() << " elixir|";
                cardnode = cardnode->next;
            }
            break;
        }
        case '0': {
            for (int i = 0; i < numberOfCards(playerscard); i++) {
                repeatedPrinting('|', ' ', cardSpace, '|');
            }
            break;
        }
        case '\n': {
            for (int i = 0; i < numberOfCards(playerscard); i++) {
                repeatedPrinting('|', '_', cardSpace, '|');
            }
            break;
        }
        case 'n': {
            for (int i = 0; i < 4; i++) {
                if (i != 0) {
                    repeatedPrinting('|', ' ', 12, ' ');
                    repeatedPrinting(' ', ' ', blankspace / 2, ' ');
                }

                for (int j = 0; j < numberOfCards(playerscard); j++) {
                    int length = cardnode->theCard.getnamelength();
                    if (i != 0) {
                        if (i == 1) {
                            if (length <= 2) {
                                cout << '|' << setw(8) << getword(cardnode->theCard.getname(), 0) << '|';
                            }
                            else {
                                cout << '|' << setw(8) << getword(cardnode->theCard.getname(), 1) << '|';
                            }
                        }
                        else if (i == 2) {
                            if (length == 2) {
                                cout << '|' << setw(8) << getword(cardnode->theCard.getname(), 1) << '|';
                            }
                            else if (length == 3 || length == 4) {
                                cout << '|' << setw(8) << getword(cardnode->theCard.getname(), 2) << '|';
                            }
                            else {
                                repeatedPrinting('|', ' ', cardSpace, '|');
                            }
                        }
                        else {
                            if (length == 4) {
                                cout << '|' << setw(8) << getword(cardnode->theCard.getname(), 3) << '|';
                            }
                            else {
                                repeatedPrinting('|', ' ', cardSpace, '|');
                            }
                        }
                    }
                    else {
                        if (length == 3 || length == 4) {
                            cout << '|' << setw(8) << getword(cardnode->theCard.getname(), 0) << '|';
                        }
                        else {
                            repeatedPrinting('|', ' ', cardSpace, '|');
                        }
                    }
                    cardnode = cardnode->next;
                }

                cardnode = playerscard;
                int totalblankspace = blankspace / 2 + blankspace % 2 + 9;
                if (i != 3) {
                    if (i == 1) {
                        repeatedPrinting(' ', ' ', (totalblankspace-7) / 2, ' ');
                        cout << "Elixir:";
                        repeatedPrinting(' ', ' ', (totalblankspace-7) / 2 + (totalblankspace-7) % 2 + 1, '|');
                        cout << endl;
                    }
                    else if (i == 2) {
                        if (currentElixir == 10) {
                            repeatedPrinting(' ', ' ', (totalblankspace-2) / 2, ' ');
                            cout << currentElixir;
                            repeatedPrinting(' ', ' ', (totalblankspace-2) / 2 + (totalblankspace-2) % 2 + 1, '|');
                            cout << endl;
                        }
                        else {
                            repeatedPrinting(' ', ' ', (totalblankspace-1) / 2, ' ');
                            cout << currentElixir;
                            repeatedPrinting(' ', ' ', (totalblankspace-1) / 2 + (totalblankspace-1) % 2 + 1, '|');
                            cout << endl;
                        }
                    }
                    else {
                        repeatedPrinting(' ', ' ', blankspace / 2 + blankspace % 2, ' ');
                        repeatedPrinting(' ', ' ', 10, '|');
                        cout << endl;
                    }
                }
            }
        }
    }
    repeatedPrinting(' ', ' ', blankspace / 2 + blankspace % 2, ' ');
}

// printing undeployed creatures on the left side of battle screen
// parameters: player's deck, line number (nth line)
void printUndeployed (creature deck[], int line) {
    string leftarray[3] = {"|_______    ", "||  ", "|_______|   "};
    if (line > 6 && line < 22) {
        int index = (line - 7) % 3;
        int i = (line - 7) / 3;
        if (deck[i].getdeployed() == true) {
            repeatedPrinting('|', ' ', 12, ' ');
        }
        else {
            if (index == 1) {
                leftarray[index] = leftarray[index].insert(3, to_string(i+1));
                leftarray[index] = leftarray[index].insert(1, deck[i].getsymbol());
                cout << leftarray[index];
            }
            else {
                cout << leftarray[index];
            }
        }
    }
    else {
        repeatedPrinting('|', ' ', 12, ' ');
    }
}

// prints creatures status below/above the creature in battle screen
// parameters: total width of battle screen, width to display one creature, head of player's deployed creatures, nth line, full deck of the player (array of creatures)
void printStatus (int totalSpace, int creatureSpace, deployed * player, int &line, creature deck[]) {
    struct statuslinked {
        string statusname;
        int number;
        statuslinked * next;
    };

    struct statusptrlinked {
        statuslinked * linked;
        statusptrlinked * next;
    };

    statusptrlinked * linkedarrayhead = NULL;
    statusptrlinked * currentptrptr = linkedarrayhead;
    statuslinked * currentptr;
    deployed * currentcreaturenode = player;
    for (int i = 0; i < numberOfCreatures(player); i++) {
        statusptrlinked * newptr = new statusptrlinked;
        newptr->linked = NULL;
        newptr->next = NULL;
        
        if (currentptrptr == NULL) {
            linkedarrayhead = newptr;
            currentptrptr = newptr;
        }
        else {
            currentptrptr->next = newptr;
            currentptrptr = newptr;
        }

        currentptr = newptr->linked;
        string statusname[] = {"counteratk", "haste", "atk", 
                        "magic", "shield", "elixirsap", "addelixir", "drawcard", 
                        "heal", "directdmg", "niceland", 
                        "thorns", "heroic", "revenge", "defenseup", 
                        "poison", "blind", "silence", "blockcard"};

        for (int j = 0; j < currentcreaturenode->deployedCreature.getnumberofstatus()-5; j++) {
            if (currentcreaturenode->deployedCreature.getstatus(statusname[j]) != 0) {
                statuslinked * newstatus = new statuslinked;
                newstatus->statusname = statusname[j];
                newstatus->number = currentcreaturenode->deployedCreature.getstatus(statusname[j]);
                newstatus->next = NULL;

                if (currentptr == NULL) {
                    newptr->linked = newstatus;
                    currentptr = newstatus;
                }
                else {
                    currentptr->next = newstatus;
                    currentptr = newstatus;
                }
            }
        }
        currentcreaturenode = currentcreaturenode->next;
    }

    bool flag = true;
    int i = 0;
    while (flag) {
        flag = false;
        currentptrptr = linkedarrayhead;

        while (currentptrptr != NULL) {
            currentptr = currentptrptr->linked;
            for (int j = 0; j < i; j++) {
                if (currentptr != NULL) {
                    currentptr = currentptr->next;
                }
                else {
                    j = i;
                }
            }
            if (currentptr != NULL) {
                flag = true;
                currentptrptr = NULL;
            }
            else {
                currentptrptr = currentptrptr->next;
            }
        }

        if (flag) {
            printUndeployed(deck, line);
            int blankspace = (totalSpace - 22 - (creatureSpace * numberOfCreatures(player)));
            repeatedPrinting(' ', ' ', blankspace / 2 + blankspace % 2, ' ');
            currentptrptr = linkedarrayhead;

            while (currentptrptr != NULL) {

                currentptr = currentptrptr->linked;
                for (int j = 0; j < i; j++) {
                    if (currentptr != NULL) {
                        currentptr = currentptr->next;
                    }
                    else {
                        j = i;
                    }
                }
                if (currentptr != NULL) {
                    if (currentptr->statusname == "area" || currentptr->statusname == "remove") {
                        cout << left;
                        cout << setw(creatureSpace) << " (" + currentptr->statusname + ")";
                    }
                    else if (currentptr->statusname == "atk") {
                        cout << left;
                        if (currentptr->number > 0) {
                            cout << setw(creatureSpace) << " (" + currentptr->statusname + " up " + to_string(currentptr->number) + "%)";
                        }
                        else {
                            cout << setw(creatureSpace) << " (" + currentptr->statusname + " down " + to_string(-currentptr->number) + "%)";
                        }
                    }
                    else if (currentptr->statusname == "heroic") {
                        cout << left;
                        cout << RED << setw(creatureSpace) << " !! HEROIC !! x " + to_string(currentptr->number) << WHITE;
                    }
                    else if (currentptr->statusname == "revenge") {
                        cout << left;
                        cout << setw(creatureSpace) << " (" + currentptr->statusname + " -> " + to_string(currentptr->number) + ")";
                    }
                    else if (currentptr->statusname == "poison") {
                        cout << left;
                        cout << setw(creatureSpace) << " (" + currentptr->statusname + " x " + to_string(currentptr->number) + "%)";
                    }
                    else {
                        cout << left;
                        cout << setw(creatureSpace) << " (" + currentptr->statusname + " x " + to_string(currentptr->number) + ")";
                    }
                }
                else {
                    cout << setw(creatureSpace) << " ";
                }

                currentptrptr = currentptrptr->next;
            }
            repeatedPrinting(' ', ' ', blankspace / 2, ' ');
            repeatedPrinting(' ', ' ', 10, '|');
            cout << endl;
            line++;
        }
        i++;
    }
}

// print out full battle screen
void printBattleScreen(deployed * player, cardOnHand * cardhead, deployed * opponent, int currentElixir, creature deck[]) {
    // commented code for debug purpose
    /*cout << endl;
    deployed * creaturenode = player;
    while (creaturenode != NULL) {
        cout << "own" << endl;
        creaturenode->deployedCreature.getcurrentstats();
        creaturenode = creaturenode->next;
        cout << endl;
    }
    cardOnHand * cardnode = cardhead;
    while (cardnode != NULL) {
        cardnode->theCard.getfunction();
        cardnode = cardnode->next;
        cout << endl;
    }
    deployed * opponentcreaturenode = opponent;
    while (opponentcreaturenode != NULL) {
        cout << "enemy" << endl;
        opponentcreaturenode->deployedCreature.getcurrentstats();
        opponentcreaturenode = opponentcreaturenode->next;
        cout << endl;
    }*/

    const int creatureSpace = 21;
    const int cardSpace = 10;
    int totalSpace = max({ (creatureSpace * numberOfCreatures(player)), (cardSpace * numberOfCards(cardhead)), (creatureSpace * numberOfCreatures(opponent))}) + 22;
    int line = 0;
    
    // prints top of battle screen
    repeatedPrinting(' ', '_', totalSpace, ' ');
    line++;
    cout << endl;
    
    // prints an empty line
    repeatedPrinting('|', ' ', totalSpace, '|');
    line++;
    cout << endl;

    // prints opponent's creatures
    char toPrintOpponent[5] = {'a', 'm', 'h', 's', 'n'};
    for (int i = 0; i < 5; i++) {
        printUndeployed(deck, line);
        printingCreature(totalSpace, creatureSpace, opponent, toPrintOpponent[i]);
        repeatedPrinting(' ', ' ', 10, '|');
        line++;
        cout << endl;
    }
    // print opponent's creature's status
    printStatus(totalSpace, creatureSpace, opponent, line, deck);

    // prints 6 empty lines
    for (int i = 0; i < 6; i++) {
        printUndeployed(deck, line);
        repeatedPrinting(' ', ' ', totalSpace-12, '|');
        line++;
        cout << endl;
    }

    // prints player's creatures' status
    printStatus(totalSpace, creatureSpace, player, line, deck);

    // prints player's creatures
    char toPrintPlayer[6] = {'n', 's', 'c', 'h', 'a', 'm'};
    for (int i = 0; i < 6; i++) {
        printUndeployed(deck, line);
        printingCreature(totalSpace, creatureSpace, player, toPrintPlayer[i]);
        repeatedPrinting(' ', ' ', 10, '|');
        line++;
        cout << endl;
    }

    // prints an empty line
    printUndeployed(deck, line);
    repeatedPrinting(' ', ' ', totalSpace-12, '|');
    line++;
    cout << endl;

    // prints player's card on hand
    char toPrintCard[5] = {'\0', '1', 'c', 'n', '\n'};
    for (int i = 0; i < 5; i++) {
        printUndeployed(deck, line);
        printingCard(totalSpace, cardSpace, cardhead, toPrintCard[i], currentElixir);
        repeatedPrinting(' ', ' ', 10, '|');
        line++;
        cout << endl;
    }

    // prints bottom of battle screen
    repeatedPrinting('|', '_', totalSpace, '|');
    cout << endl;

    cout << endl;
}