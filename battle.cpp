#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<stdlib.h>
#include<time.h>
#include<limits>
#include<algorithm>
#include<iomanip>
#include "battle.h"
using namespace std;

// count number of cards on player's hand
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

// printing creature section
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
string getword (string wordlist, int index) {
    string targetword;
    istringstream iss (wordlist);
    for (int i = 0; i <= index; i++) {
        iss >> targetword;
    }
    return targetword;
}

// printing card on hand section
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
    cout << endl;
    
    repeatedPrinting(' ', '_', totalSpace, ' ');
    line++;
    cout << endl;
    
    repeatedPrinting('|', ' ', totalSpace, '|');
    line++;
    cout << endl;

    char toPrintOpponent[5] = {'a', 'm', 'h', 's', 'n'};
    for (int i = 0; i < 5; i++) {
        printUndeployed(deck, line);
        printingCreature(totalSpace, creatureSpace, opponent, toPrintOpponent[i]);
        repeatedPrinting(' ', ' ', 10, '|');
        line++;
        cout << endl;
    }

    for (int i = 0; i < 6; i++) {
        printUndeployed(deck, line);
        repeatedPrinting(' ', ' ', totalSpace-12, '|');
        line++;
        cout << endl;
    }

    char toPrintPlayer[6] = {'n', 's', 'c', 'h', 'a', 'm'};
    for (int i = 0; i < 6; i++) {
        printUndeployed(deck, line);
        printingCreature(totalSpace, creatureSpace, player, toPrintPlayer[i]);
        repeatedPrinting(' ', ' ', 10, '|');
        line++;
        cout << endl;
    }

    printUndeployed(deck, line);
    repeatedPrinting(' ', ' ', totalSpace-12, '|');
    line++;
    cout << endl;

    char toPrintCard[5] = {'\0', '1', 'c', 'n', '\n'};
    for (int i = 0; i < 5; i++) {
        printUndeployed(deck, line);
        printingCard(totalSpace, cardSpace, cardhead, toPrintCard[i], currentElixir);
        repeatedPrinting(' ', ' ', 10, '|');
        line++;
        cout << endl;
    }

    repeatedPrinting('|', '_', totalSpace, '|');
    cout << endl;

    cout << endl;
}

// to deploy a creature on battle field
// format : deploy <creature number> <creature position>
// negates all invalid input
void deploy (int &currentElixir, creature deck[], deployed * &head) {
    int creatureidx;
    cin >> creatureidx;
    string *trash = new string;
    while ( cin.fail() ) {
        cin.clear(); 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "To deploy a creature, please type the <creature number>, followed by the <position> that you wish to deploy the creature at." << endl;
        cout << "Please enter the creature number properly" << endl;
        cout << "Deploy ";
        return;
    }
    if ( creatureidx < 1 || creatureidx > 5) {
        cin.clear(); 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Please enter a valid creature number." << endl;
        return;
    }
    else if ( deck[creatureidx-1].getdeployed() == true ) {
        cin.clear(); 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Creature already deployed!" << endl;
        return;
    }

    int position;
    cin >> position;
    while ( cin.fail() ) {
        cin.clear(); 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Please enter the position of the creature as a valid number" << endl;
        cout << "deploy " << creatureidx << " ";
        return;
    }

    if (currentElixir > 0) {
        currentElixir--;
    }
    else {
        cout << "Not enough elixir!" << endl;
        return;
    }

    deployed * newdeployed = new deployed;
    newdeployed->deployedCreature = deck[creatureidx-1];
    deck[creatureidx-1].setdeployed(true);
    
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
}

// randomly draw a card from a creature
int drawCard(creature &toBeDrawnFrom) {
    int cards[25] = {0};
    int count = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < toBeDrawnFrom.cardpool[i].getrarity(); j++) {
            cards[count] = i;
            count++;
        }
    }
    if (count == 0) {
        for (int i = 0; i < 5; i++) {
            toBeDrawnFrom.cardpool[i].setcard(toBeDrawnFrom.cardpool[i].getcardnumber());
        }
        for (int i = 1; i < 6; i++) {
            for (int j = 0; j < toBeDrawnFrom.cardpool[i-1].getrarity(); j++) {
                cards[count] = i;
                count++;
            }
        }
    }
    
    srand(time(NULL));
    return cards[(rand() % count)];
}

// add a card to player's hand (after drawn)
void addCardToHand (cardOnHand * &cardhead, card toBeAdded) {
    cardOnHand * newnode = new cardOnHand;
    newnode->theCard = toBeAdded;
    newnode->next = cardhead;
    cardhead = newnode;
}

// randomly draw 5 cards from all creatures' card at start of battle
void initialiseCard (cardOnHand * &cardhead, creature deck[], int push) {
    for (int i = 0; i < 5; i++) {
        srand(time(NULL)+push);
        addCardToHand(cardhead, deck[( rand() % 24 ) / 5].cardpool[( rand() % 24 ) % 5]);
        push++;
    }
}

// attack the opponent creature
// format: attack <opponent creature name> with <own creature name>
// negates all invalid input
void attack (deployed * &player, deployed * &opponent, cardOnHand * &playerscard, int &currentElixir) {
    string fullsentence;
    getline(cin, fullsentence);

    istringstream iss (fullsentence);
    string word;
    string name = "";
    while (iss >> word && word != "with") {
        if (name == "") {
            name += word;
        }
        else {
            name = name + " " + word;
        }
    }
    if (word != "with") {
        cout << "To attack an opponent's creature using your creature, please type \"attack <target creature's name> with <your creature's name>\"" << endl;
        cout << "You did not type the word \"with\"" << endl;
        return;
    }
    if (name == "") {
        cout << "No target name inserted." << endl;
        return;
    }
    
    deployed * targetnode = opponent;
    bool flag = false;
    while (flag == false && targetnode != NULL) {
        if (targetnode->deployedCreature.getname() == name) {
            flag = true;
        }
        else {
            targetnode = targetnode->next;
        }
    }
    if (flag == false) {
        cout << "Invalid target name inserted. Please check your spelling." << endl;
        return;
    }

    name = "";
    while (iss >> word) {
        if (name == "") {
            name += word;
        }
        else {
            name = name + " " + word;
        }
    }
    if (name == "") {
        cout << "No attacker name inserted." << endl;
        return;
    }

    deployed * attackernode = player;
    flag = false;
    while (flag == false && attackernode != NULL) {
        if (attackernode->deployedCreature.getname() == name) {
            flag = true;
        }
        else {
            attackernode = attackernode->next;
        }
    }
    if (flag == false) {
        cout << "Invalid attacker name inserted. Please check your spelling." << endl;
        return;
    }

    if (attackernode->deployedCreature.getcost() > currentElixir) {
        cout << "Not enough elixir" << endl;
        return;
    }
    else {
        currentElixir = currentElixir - attackernode->deployedCreature.getcost();
    }
    
    bool critical = false;
    targetnode->deployedCreature.decreasehp(attackernode->deployedCreature.getatk(critical));
    if (critical == true) {
        cout << "CRITICAL ATTACK !!!" << endl;
    }

    if (targetnode->deployedCreature.gethp() <= 0) {
        deployed * deleteafter = opponent;
        if (deleteafter == targetnode) {
            opponent = targetnode->next;
            delete targetnode;
        }
        else {
            while (deleteafter->next != targetnode) {
                deleteafter = deleteafter->next;
            }
            deleteafter->next = targetnode->next;
            delete targetnode;
        } 
    }

    if (numberOfCards(playerscard) < 10) {
        int idxOfCardDrawn = drawCard(attackernode->deployedCreature);
        addCardToHand(playerscard, attackernode->deployedCreature.cardpool[idxOfCardDrawn]);
        attackernode->deployedCreature.cardpool[idxOfCardDrawn].cardDrawn();
    } else {
        cout << "Hand full." << endl;
    }
    return;
}

// a centre switch to take in player's input and calls different functions based on user's input
void playersMove (deployed * &player, deployed * &opponent, int &currentElixir, creature deck[], cardOnHand * &playerscard) {
    string action;
    while (player != NULL && opponent != NULL) {
        printBattleScreen(player, playerscard, opponent, currentElixir, deck);
        cout << "Your move: ";
        cin >> action;
        if (action == "deploy") {
            deploy(currentElixir, deck, player);
        }
        else if (action == "attack") {
            attack(player, opponent, playerscard, currentElixir);
        }
        /*else if (action == "use") {
            use();
        }*/
        else if (action == "next") {
            cout << "------------------------------------------------------------------------------" << endl;
            return;
        }
        else {
            cout << "Invalid response. Please check your spelling." << endl;
        }
    }
}

// overall battle function 
// call this function to start the battle
void battle(creature deck[], opponent currentOpponent) {
    deployed * head1 = NULL;
    deployed * head2 = NULL;
    cardOnHand * cardhead1 = NULL;
    cardOnHand * cardhead2 = NULL;

    initialiseCard(cardhead1, deck, 0);
    initialiseCard(cardhead2, currentOpponent.opponentCreature, 5);

    int totalElixir = 1;
    int currentElixir = totalElixir;
    
    printBattleScreen(head1, cardhead1, head2, currentElixir, deck);

    while (currentElixir == 1) { 
        cout << "Please deploy a creature: deploy ";
        deploy(currentElixir, deck, head1);
    }
    currentElixir = totalElixir;
    //opponentsResponse();
    printBattleScreen(head2, cardhead2, head1, currentElixir, currentOpponent.opponentCreature);
    while (currentElixir == 1) { 
        cout << "Please deploy a creature: deploy ";
        deploy(currentElixir, currentOpponent.opponentCreature, head2);
    }

    while (head1 != NULL && head2 != NULL) {
        totalElixir++;
        currentElixir = totalElixir;
        playersMove(head1, head2, currentElixir, deck, cardhead1);
        currentElixir = totalElixir;
        playersMove(head2, head1, currentElixir, currentOpponent.opponentCreature, cardhead2);
        //opponentsResponse();
    }
    printBattleScreen(head1, cardhead1, head2, currentElixir, deck);
    //battleResults();
}