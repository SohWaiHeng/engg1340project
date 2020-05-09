#include<iostream>
#include<string>
#include<sstream>
#include<stdlib.h>
#include<time.h>
#include<limits>

#include "../hfiles/battle.h"
#include "../hfiles/colours.h"
#include "../hfiles/menu.h"

using namespace std;

// to deploy a creature on battle field (add a new undeployed creature into the linked list of deployed creatures)
// format : deploy <creature number> <creature position>
// negates all invalid input
// parameters: current elixir count, the deck to deploy creature from, and the head of the linked list of deployed creatures
void deploy (int &currentElixir, creature deck[], deployed * &head) {
    // only allows 4 creatures on the field
    if (numberOfCreatures(head) == 4) {
        cin.clear(); 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << RED << "You can only have a maximum of 4 creatures on the field" << WHITE << endl;
        return;
    }
    
    int creatureidx;
    cin >> creatureidx;
    // terminates function if player enters the input in a wrong format
    while ( cin.fail() ) {
        cin.clear(); 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "To deploy a creature, please type the <creature number>, followed by the <position> that you wish to deploy the creature at." << endl;
        cout << RED << "Please enter the creature number properly" << WHITE << endl;
        return;
    }
    if ( creatureidx < 1 || creatureidx > 5) {
        cin.clear(); 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << RED << "Please enter a valid creature number." << WHITE << endl;
        return;
    }
    // terminates function if creature is already deployed
    else if ( deck[creatureidx-1].getdeployed() == true ) {
        cin.clear(); 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << RED << "Creature already deployed!" << WHITE << endl;
        return;
    }

    // takes in the position to deploy the creature
    int position;
    cin >> position;
    while ( cin.fail() ) {
        cin.clear(); 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << RED << "Please enter the position of the creature as a valid number" << WHITE << endl;
        return;
    }

    // deploy takes 1 elixir, terminate function if not enough elixir.
    if (currentElixir > 0) {
        currentElixir--;
    }
    else {
        cout << RED << "Not enough elixir!" << WHITE << endl;
        return;
    }

    // create a node for the newly deployed creature
    deployed * newdeployed = new deployed;
    newdeployed->deployedCreature = deck[creatureidx-1];
    deck[creatureidx-1].setdeployed(true);
    
    // put the node in specified location
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

// randomly draw a card from a creature
// parameter: the creature from which the card is drawn from (of type creature class)
// output: the card's index number (as stored in the creature) (1~5)
int drawCard(creature &toBeDrawnFrom) {
    // store available cards in an array with size 25
    int cards[25] = {0};
    int count = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < toBeDrawnFrom.cardpool[i].getrarity(); j++) {
            cards[count] = i;
            count++;
        }
    }

    // if all cards were already drawn, initialise cards again 
    if (count == 0) {
        for (int i = 0; i < 5; i++) {
            toBeDrawnFrom.cardpool[i].setcard(toBeDrawnFrom.cardpool[i].getcardnumber());
        }
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < toBeDrawnFrom.cardpool[i].getrarity(); j++) {
                cards[count] = i;
                count++;
            }
        }
    }
    
    // randomly draw a card, return the card's index number
    delay(0.1);
    srand(time(NULL));
    int cardidx = cards[(rand() % count)];
    toBeDrawnFrom.cardpool[cardidx].minusrarity();
    return cardidx;
}

// add a card to player's hand (after drawn) (append to the linked list of the cards on hand)
// parameters: head of the linked list of cards on hand, the card to be added (with type class card)
void addCardToHand (cardOnHand * &cardhead, card toBeAdded) {
    cardOnHand * newnode = new cardOnHand;
    newnode->theCard = toBeAdded;
    newnode->next = cardhead;
    cardhead = newnode;
    return;
}

// randomly draw 5 cards from all creatures' card at start of battle and add to the hand
// parameters: head of linked list of cards on hand, the deck of the player, a 'push' integer to randomise the random seed
void initialiseCard (cardOnHand * &cardhead, creature deck[], int push) {
    for (int i = 0; i < 5; i++) {
        srand(time(NULL)+push);
        addCardToHand(cardhead, deck[( rand() % 24 ) / 5].cardpool[( rand() % 24 ) % 5]);
        push++;
    }
    return;
}

// remove dead creature from the linked list of deployed creatures
// parameters: the node of the dead creature, the head of the linked list of deployed creatures
void death (deployed * &creaturenode, deployed * &head) {
    deployed * deleteafter = head;
    cout << creaturenode->deployedCreature.getname() << " is eliminated from the battlefield." << endl;
    if (deleteafter == creaturenode) {
        head = creaturenode->next;
        if (creaturenode->next != NULL && creaturenode->deployedCreature.getstatus("elixirsap") < 0) {
            creaturenode->next->deployedCreature.setstatus("elixirsap", creaturenode->deployedCreature.getstatus("elixirsap"));
        }
        delete creaturenode;
    }
    else {
        while (deleteafter->next != creaturenode) {
            deleteafter = deleteafter->next;
        }
        if (creaturenode->next != NULL && creaturenode->deployedCreature.getstatus("elixirsap") < 0) {
            deleteafter->deployedCreature.setstatus("elixirsap", creaturenode->deployedCreature.getstatus("elixirsap"));
        }
        deleteafter->next = creaturenode->next;
        delete creaturenode;
    } 
}

// attack the opponent creature
// format: attack <opponent creature name> with <own creature name>
// negates all invalid input
// parameters: the player's and opponent's head of deployed creature linked list, head of the player's cards linked list, current elixir count
void attack (deployed * &player, deployed * &opponent, cardOnHand * &playerscard, int &currentElixir) {
    // get input
    string fullsentence;
    getline(cin, fullsentence);

    // rejects invalid input
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
        cout << RED << "To attack an opponent's creature using your creature, please type \"attack <target creature's name> with <your creature's name>\"" << endl;
        cout << "You did not type the word \"with\"" << WHITE << endl;
        return;
    }
    if (name == "") {
        cout << RED << "No target name inserted." << WHITE << endl;
        return;
    }
    
    // check if the target in valid or if any opponent creature has heroic
    deployed * targetnode = opponent;
    bool flag = false;
    bool heroic = false;
    while (flag == false && targetnode != NULL) {
        if (targetnode->deployedCreature.getstatus("heroic") != 0) {
            heroic = true;
        }
        if (targetnode->deployedCreature.getname() == name) {
            flag = true;
        }
        else {
            targetnode = targetnode->next;
        }
    }

    if (flag == false) {
        cout << RED << "Invalid target name inserted. Please check your spelling." << WHITE << endl;
        return;
    }
    else {
        deployed * continuenode = targetnode->next;
        while (continuenode != NULL) {
            if (continuenode->deployedCreature.getstatus("heroic") != 0) {
                heroic = true;
            }
            continuenode = continuenode->next;
        }
    }
    // the player can only a creature with heroic if heroic is present on the field
    if (heroic == true && targetnode->deployedCreature.getstatus("heroic") == 0) {
        cout << RED << "You can only attack creatures with heroic." << WHITE << endl;
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
        cout << RED << "No attacker name inserted." << WHITE << endl;
        return;
    }
    // checks if attacker is valid
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
        cout << RED << "Invalid attacker name inserted. Please check your spelling." << WHITE << endl;
        return;
    }
    // checks if elixir count is enough to attack
    if (attackernode->deployedCreature.getcost() > currentElixir) {
        cout << RED << "Not enough elixir!" << WHITE << endl;
        return;
    }
    else {
        currentElixir = currentElixir - attackernode->deployedCreature.getcost();
    }
    //if attacker is blinded, miss attack
    if (attackernode->deployedCreature.getstatus("blind") > 0) {
        cout << "MISSED!" << endl;
        attackernode->deployedCreature.setstatus("blind", -1);
    }
    else {
        // damage the target
        bool critical = false;
        int byHowMuch = attackernode->deployedCreature.getatk(critical);
        targetnode->deployedCreature.decreasehp(byHowMuch);
        if (critical == true) {
            cout << "CRITICAL ATTACK !!!" << endl;
        }
        cout << targetnode->deployedCreature.getname() << " damaged by " << byHowMuch << " hp." << endl;
        // activate thorns effect if target has thorns
        attackernode->deployedCreature.thorns(byHowMuch, targetnode->deployedCreature);
    }
    // attacker draws a card after attack if no block card status
    if (attackernode->deployedCreature.getstatus("blockcard") > 0) {
        cout << "No card drawn. Blocked." << endl;
        attackernode->deployedCreature.setstatus("blockcard", -1);
    }
    // a player can only has at most 9 cards on hand
    else if (numberOfCards(playerscard) < 9) {
        int idxOfCardDrawn = drawCard(attackernode->deployedCreature);
        addCardToHand(playerscard, attackernode->deployedCreature.cardpool[idxOfCardDrawn]);
        attackernode->deployedCreature.cardpool[idxOfCardDrawn].cardDrawn();
    } 
    else {
        cout << "Hand full." << endl;
    }
    // revert 'attack up' status
    if (attackernode->deployedCreature.getstatus("atk") != 0) {
        attackernode->deployedCreature.atk(0);
    }
    // saps elixir if elixir sap is present
    attackernode->deployedCreature.elixirsap(targetnode->deployedCreature, currentElixir, true);
    // checks if any creature is dead
    if (targetnode->deployedCreature.gethp() <= 0 && attackernode->deployedCreature.gethp() <= 0) {
        death(targetnode, opponent);
        death(attackernode, player);
    }
    else if (attackernode->deployedCreature.gethp() <= 0) {
        death (attackernode, player);
        // target counterattacks if not dead and has counterattack
        targetnode->deployedCreature.counteratk(player->deployedCreature);

        targetnode->deployedCreature.elixirsap(player->deployedCreature, currentElixir, true);

        if (player->deployedCreature.gethp() <= 0) {
            death (attackernode, player);
        }
        if (targetnode->deployedCreature.gethp() <= 0) {
            death(targetnode, opponent);
        }
    }
    else if (targetnode->deployedCreature.gethp() > 0 && attackernode->deployedCreature.gethp() > 0) {
        targetnode->deployedCreature.counteratk(attackernode->deployedCreature);

        targetnode->deployedCreature.elixirsap(attackernode->deployedCreature, currentElixir, true);
        
        if (attackernode->deployedCreature.gethp() <= 0) {
            death (attackernode, player);
        }
        if (targetnode->deployedCreature.gethp() <= 0) {
            death(targetnode, opponent);
        }
    }
    else {
        death(targetnode, opponent);
    }
    return;
}

// to use a card on a creature
// parameters: the player's and opponent's head of deployed creature linked lists, current elixir count, head of linked list of player's cards on hand
void use (deployed *&player, deployed * &opponent, int &currentElixir, cardOnHand * &playerscard) {
    string fullsentence;
    getline(cin, fullsentence);

    // rejects incorrect input
    istringstream iss (fullsentence);
    string word;
    string name = "";
    while (iss >> word && word != "on") {
        if (name == "") {
            name += word;
        }
        else {
            name = name + " " + word;
        }
    }
    if (word != "on") {
        cout << RED << "To use a card on a creature, please type \"use <card's name> on <creature's name>\"" << WHITE << endl;
        cout << RED << "You did not type the word \"on\"" << WHITE << endl;
        return;
    }
    if (name == "") {
        cout << RED << "No card name inserted." << WHITE << endl;
        return;
    }

    cardOnHand * cardnode = playerscard;
    while (cardnode != NULL && cardnode->theCard.getname() != name) {
            cardnode = cardnode->next;
    }
    if (cardnode == NULL) {
        cout << RED << "Invalid card name inserted. Please check your spelling." << WHITE << endl;
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
        cout << RED << "No creature name inserted." << WHITE << endl;
        return;
    }

    deployed * creaturenode1 = player;
    while (creaturenode1 != NULL && creaturenode1->deployedCreature.getname() != name) {
        creaturenode1 = creaturenode1->next;
    }

    deployed * creaturenode2 = opponent;
    while (creaturenode2 != NULL && creaturenode2->deployedCreature.getname() != name) {
        creaturenode2 = creaturenode2->next;
    }
    
    bool indicator = true;
    if (creaturenode1 == NULL && creaturenode2 == NULL) {
        cout << RED << "Invalid creature name inserted. Please check your spelling." << WHITE << endl;    
        return;
    }
    // if creature name is present on both sides, ask if the creature is the player's own creature or the opponent's
    else if (creaturenode1 != NULL && creaturenode2 != NULL) {
        cout << "Do you wish to use this card on your own \"" << name << "\" or opponent's \"" << name << "\"?" << endl;
        cout << "Please type ( own / opponent ) ";
        string choice;
        cin >> choice;
        while (choice != "own" && choice != "opponent") {
            cout << "Please type either \"own\" or \"opponent\": ";
            cin >> choice;
        }
        if (choice == "own") {
            indicator = true;
            creaturenode2 = NULL;
        }
        else if (choice == "opponent") {
            indicator = false;
            creaturenode1 = creaturenode2;
        }
    }
    else if (creaturenode1 == NULL && creaturenode2 != NULL) {
        indicator = false;
        creaturenode1 = creaturenode2;
    }

    deployed * previousnode = NULL;
    if (indicator) {
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
    else {
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
    // checks if silence is present, player cannot play cards on silenced creature
    if (creaturenode1->deployedCreature.getstatus("silence") > 0) {
        cout << RED << "The creature is silenced. You cannot play card on it." << WHITE << endl;
        return;
    }
    // cheks if current elixir is enough
    if (cardnode->theCard.getcost() > currentElixir) {
        cout << RED << "Not enough elixir!" << WHITE << endl;
        return;
    }
    // gets card's function
    string trash;
    string cardFunction = cardnode->theCard.getfunction(trash);
    istringstream iss2 (cardFunction);

    string condition;
    bool area = false;
    string own;
    string enemy;
    string card;
    int number;

    // do action on every function of the card
    while (iss2 >> condition) {
        iss2 >> trash;
        iss2 >> number;

        if (condition == own) {
            number = number * numberOfCreatures(player);
        }
        else if (condition == enemy) {
            number = number * numberOfCreatures(opponent);
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
                cout << "Target name? ";
                string targetname;
                getline(cin, targetname);

                deployed * targetnode = opponent;
                while (targetnode != NULL && targetnode->deployedCreature.getname() != targetname) {
                    targetnode = targetnode->next;
                }
                if (targetnode == NULL) {
                    cout << "Invalid target name inserted!" << endl;
                    return;
                }
                
                for (int i = 0; i < number; i++) {
                    creaturenode1->deployedCreature.magic(targetnode->deployedCreature);
                    if (area) {
                        if (previousnode != NULL) {
                            previousnode->deployedCreature.magic(targetnode->deployedCreature);
                        }
                        if (creaturenode1->next != NULL) {
                            creaturenode1->next->deployedCreature.magic(targetnode->deployedCreature);
                        }
                    }
                }

                if (targetnode->deployedCreature.gethp() <= 0) {
                    death(targetnode, opponent);
                }
            }
            else {
                cout << "Magic attack cards can only be used on own creatures" << endl;
                return;
            }
        }
        else if (condition == "addelixir") {
            if (indicator) {
                creaturenode1->deployedCreature.addelixir(currentElixir, number);
            }
            else {
                cout << "Addelixir cards can only be used on own creatures" << endl;
                return;
            }
        }
        else if (condition == "drawcard") {
            for (int i = 0; i < number; i++) {
                if (numberOfCards(playerscard) < 9) {
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
                    cout << "Hand full." << endl;
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
    // reduces current elixir count
    currentElixir = currentElixir - cardnode->theCard.getcost();

    // delete the card from hand
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

    // removes dead creatures
    if (creaturenode1->deployedCreature.gethp() <= 0) {
        if (indicator) {
            death(creaturenode1, player);
        }
        else {
            death(creaturenode1, opponent);
        }
    }

    return;
}

// show card or creature info in battle
// parameters: head of player's  and opponent's deployed creature linked list, the players full deck (array of creatures), head of the player's card on hand linked list
void show (deployed * player, deployed * opponent, creature deck[], cardOnHand * playerscard) {
    string type;
    cin >> type;

    cout << endl;

    // to show craeture info
    // rejects invalid input
    if (type == "creature") {
        string name;
        cin >> name;
        string temp;
        getline(cin, temp);
        name = name + temp;

        bool check = true;
        int length = name.length();
        for (int i = 0; i < length; i++) {
            check = isdigit(name[i]);
            if (check == false) {
                i = length;
            }
        }

        if (check == false) {
            cout << name << endl;
            deployed * creaturenode1 = player;
            while (creaturenode1 != NULL && creaturenode1->deployedCreature.getname() != name) {
                creaturenode1 = creaturenode1->next;
            }

            deployed * creaturenode2 = opponent;
            while (creaturenode2 != NULL && creaturenode2->deployedCreature.getname() != name) {
                creaturenode2 = creaturenode2->next;
            }

            if (creaturenode1 == NULL && creaturenode2 == NULL) {
                cout << RED << "Invalid creature name inserted. Please check your spelling." << WHITE << endl;    
                return;
            }
            else if (creaturenode1 != NULL && creaturenode2 != NULL) {
                cout << "Do you wish show your own \"" << name << "\" or opponent's \"" << name << "\"?" << endl;
                cout << "Please type ( own / opponent ) ";
                string choice;
                cin >> choice;
                while (choice != "own" && choice != "opponent") {
                    cout << "Please type either \"own\" or \"opponent\": ";
                    cin >> choice;
                }
                if (choice == "own") {
                    creaturenode2 = NULL;
                }
                else if (choice == "opponent") {
                    creaturenode1 = creaturenode2;
                }
            }
            else if (creaturenode1 == NULL && creaturenode2 != NULL) {
                creaturenode1 = creaturenode2;
            }

            creaturenode1->deployedCreature.getcurrentstats();
        }
        else {
            int number = atoi(name.c_str());
            if (number > 0 && number < 6)
                deck[number-1].getcurrentstats();
            else {
                cout << RED << "invalid creature number inserted" << WHITE << endl;
                return;
            }
        }
    }
    // to show card info
    // rejects invalid input
    else if (type == "card") {
        string name;
        cin >> name;
        string temp;
        getline(cin, temp);
        name = name + temp;

        cardOnHand * cardnode = playerscard;
        while (cardnode != NULL && cardnode->theCard.getname() != name) {
            cardnode = cardnode->next;
        }
        if (cardnode == NULL) {
            cout << RED << "Invalid card name entered. Please check your spelling." << WHITE << endl;
            return;
        }
        else {
            string printedfunction;
            string cardFunction = cardnode->theCard.getfunction(printedfunction);
            cout << BLUE << printedfunction << WHITE << endl;
            istringstream iss2 (cardFunction);

            string condition;
            string trash;
            int number;

            while (iss2 >> condition) {
                iss2 >> trash;
                iss2 >> number;

                string statusname[] = {"area", "remove",
                                    "counteratk", "haste", "atk", 
                                    "magic", "shield", "elixirsap", "addelixir", "drawcard", 
                                    "heal", "directdmg", "niceland", 
                                    "thorns", "heroic", "revenge", "defenseup", 
                                    "poison", "blind", "silence", "blockcard"};
                string description[] = {
                "Will cast the effect on the creature left and right to the creature of which the card is played onto",
                "Remove an effect",
                "A creature with counteratk will attack back it is attacked by any creature.",
                "Decrease the cost of a creature by 1 (cost -1) for n turns",
                "Increse the atk value of a creature by n%. The increase in atk value will be reverted once the creature is used to attack.",
                "Casts magic attack onto a target creature. The target creature will be damaged by the mgc value of the attacking creature",
                "Shield negates any type of damage done to the creature. One shield will be used to shield a damage once only.",
                "Steals n amount of elixir from the opponent. Opponent will lose n amount of elixir on his next turn, while you will gain n elixir on the same round.",
                "Adds n amount of elixir",
                "Draws a card from the creature the card is played on",
                "The creature heals n% hp",
                "The creature will be damaged by n% hp",
                "The creature will heal 10% hp every round if niceland effect is not removed.",
                "Gives the creature thorns for n turns. A creature with thorns will reflect the atk damage to the attacking creature when attacked.",
                "Gives the creature heroic for n turns. If there is a creature with heroic on the battlefield, then only that creature can be attacked by the opponent.",
                "A creature with revenge will accumulate the damage received by it in one round, then automatically deals damage to the opponent's creature by the accumulated amount.",
                "Gives defenseup for n turns. All damage received will be reduced by 30%.",
                "A creature with n% poison will automatically lose n% hp every round",
                "A creature with n blind will miss its attacks. (will not be able to deal damage for n times)",
                "Gives silence for n turns. You cannot play any card on a creature with silence.",
                "Gives n amount of blockcard. No card will be drawn from the creature for n times (when attacking). You can still use a card with drawcard function."
                };
                for (int i = 0; i < 21; i++) {
                    if (condition == statusname[i]) {
                        cout << BLUE << statusname[i] << WHITE << ": " << description[i] << endl;
                    }
                }
                iss2 >> trash;
            }
        }
    }
    else {
        cin.clear(); 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << RED << "To show info of a creature / card, please type \"show <type: creature/card> <name of creature/number of undeployed creature/name of card>" << WHITE << endl;
        return;
    }
    cout << endl;
}

// a centre switch to take in player's input and calls different functions based on user's input
// parameters : player's and opponent's head of linked lists of deployed creatures, current elixir count, player's full deck of creatures (array of creatures), head of linked list of player's card on hand
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
        else if (action == "use") {
            use(player, opponent, currentElixir, playerscard);
        }
        else if (action == "show") {
            show(player, opponent, deck, playerscard);
        }
        else if (action == "next") {
            cout << "------------------------------------------------------------------------------" << endl;
            cout << endl;
            return;
        }
        else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid response. Please check your spelling." << endl;
        }
    }
}

// do some in game changes at the start of the player's round
// parameters: player's and opponent's head of linked lists of deployed creatures, current elixir count
void roundStart (deployed * &player, deployed * &opponent, int &currentElixir) {
    if (player != NULL && opponent != NULL) {
        deployed * currentnode = player;
        while (currentnode != NULL) {
            // if creature has niceland, heal 10% every round
            if (currentnode->deployedCreature.getstatus("niceland") != 0) {
                currentnode->deployedCreature.heal(10);
            }

            // if creature has haste, cost -1
            currentnode->deployedCreature.elixirsap(currentnode->deployedCreature, currentElixir, false);
            currentnode->deployedCreature.haste(true);

            // if creature has revenge, revenge attack the opponent team
            currentnode->deployedCreature.revenge(0, true, opponent->deployedCreature);
            if (opponent->deployedCreature.gethp() <= 0) {
                death(opponent, opponent);
            }
            if (currentnode->deployedCreature.gethp() <= 0) {
                deployed * deathnode = currentnode;
                currentnode = currentnode->next;
                death(deathnode, player);
                break;
            }

            // if creature had poison, decrease hp at every start of round
            currentnode->deployedCreature.poison();
            if (currentnode->deployedCreature.gethp() <= 0) {
                deployed * deathnode = currentnode;
                currentnode = currentnode->next;
                death(deathnode, player);
                break;
            }

            // these status' count -1
            string minusOneTurn[4] = {"thorns", "heroic", "defenseup", "silence"};
            for (int i = 0; i < 4; i++) {
                if (currentnode->deployedCreature.getstatus(minusOneTurn[i]) != 0) {
                    currentnode->deployedCreature.setstatus(minusOneTurn[i], -1);
                }
            }

            currentnode = currentnode->next;
        }
    }
}

// prints if player lose or win
// parameters: head of player's and opponent's deployed creature's linked list, bool winlose as a reference to bring the results to main function
void battleResults (deployed * player, deployed * opponenthead, bool &winlose) {
    if (player == NULL) {
        cout << RED << "You lose!" << WHITE << endl;
        winlose = false;
    }
    else if (opponenthead == NULL) {
        cout << GREEN << "You win!" << WHITE << endl;
        winlose = true;
    }
    cout << HIGHLIGHT << "Leaving battlefield..." << WHITE << endl;
}

// overall battle function 
// call this function to start the battle
// parameters: player's deck (array of creatures of size 5), opponent of type struct 'opponent' (initialised), bool winlose to indicate the battle's results (initialisation not needed)
void battle(creature deck[], opponent currentOpponent, bool &winlose) {
    cout << HIGHLIGHT << "Heading to battlefield..."  << WHITE << endl;
    
    // initialise player's and opponents' head of deployed creatures as null
    // head 1 is player's, head 2 is opponent's
    deployed * head1 = NULL;
    deployed * head2 = NULL;
    cardOnHand * cardhead1 = NULL;
    cardOnHand * cardhead2 = NULL;

    // initialise both player's card on hand
    initialiseCard(cardhead1, deck, 0);
    initialiseCard(cardhead2, currentOpponent.opponentCreature, 5);

    int totalElixir = 1;
    int currentElixir = totalElixir;
    
    // print the battle screen
    printBattleScreen(head1, cardhead1, head2, currentElixir, deck);

    // ask player to deploy a creature
    while (currentElixir == 1) { 
        cout << "Please deploy a creature: deploy ";
        deploy(currentElixir, deck, head1);
    }
    currentElixir = totalElixir;

    cout << "------------------------------------------------------------------------------" << endl << endl;
    opponentsResponse(currentOpponent.opponentCreature, currentElixir, head2, cardhead2, head1);
     
    // repeats adding elixir, gets user's input for every round until all deployed creatures of one of the players are dead
    while (head1 != NULL && head2 != NULL) {
        if (totalElixir < 10) {
            totalElixir++;
        }
        currentElixir = totalElixir;
        roundStart(head1, head2, currentElixir);
        playersMove(head1, head2, currentElixir, deck, cardhead1);
        currentElixir = totalElixir;
        roundStart(head2, head1, currentElixir);
        //playersMove(head2, head1, currentElixir, currentOpponent.opponentCreature, cardhead2); // if pvp
        opponentsResponse(currentOpponent.opponentCreature, currentElixir, head2, cardhead2, head1);
    }
    printBattleScreen(head1, cardhead1, head2, currentElixir, deck);
    battleResults(head1, head2, winlose);
}

// same as battle but for tutorial use
// teach new players about battle mechanics
void tutorialmode (creature deck[], opponent currentOpponent, bool &winlose) {
    deployed * head1 = NULL;
    deployed * head2 = NULL;
    cardOnHand * cardhead1 = NULL;
    cardOnHand * cardhead2 = NULL;

    initialiseCard(cardhead1, deck, 0);
    initialiseCard(cardhead2, currentOpponent.opponentCreature, 5);

    int totalElixir = 1;
    int currentElixir = totalElixir;
    
    printBattleScreen(head1, cardhead1, head2, currentElixir, deck);

    string trash;
    cout << BLUE << "Now let's start the battle." << endl;
    cout << "To start off, you will need to deploy a creature from your deck to the field." << endl;
    cout << GREEN << "Press enter to continue." << WHITE << endl;
    getline(cin, trash);

    cout << BLUE << "To deploy a creature, type \"deploy <creature's no.> <deploy position>\"" << endl;
    cout << "For example, \"deploy 4 1\" will deploy the 4th creature at position 1 on the field" << endl;
    while (currentElixir == 1) { 
        cout << WHITE << "Please deploy a creature: deploy ";
        deploy(currentElixir, deck, head1);
    }

    currentElixir = totalElixir;
    cout << "------------------------------------------------------------------------------" << endl << endl;
    opponentsResponse(currentOpponent.opponentCreature, currentElixir, head2, cardhead2, head1);

    totalElixir++;
    currentElixir = totalElixir;
    roundStart(head1, head2, currentElixir);
    printBattleScreen(head1, cardhead1, head2, currentElixir, deck);

    cout << BLUE << "Great Job!" << endl;
    cout << "It seems that your opponent has also deployed a creature on the field." << endl;
    cout << "Now try to deploy 2 more creatures on the field. Deploying a creature will cost you 1 elixir." << endl;
    string response;
    while (currentElixir == totalElixir) {
        cout << WHITE << "Your move: ";
        cin >> response;
        if (response == "deploy") {
            deploy(currentElixir, deck, head1);
        }
        else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << endl;
            cout << RED << "Please deploy 2 more creatures by typing 'deploy _ _'." << endl;
        }
    }
    printBattleScreen(head1, cardhead1, head2, currentElixir, deck);

    cout << BLUE << "Deploying a creature on position '1' will put the creature at the leftmost side of the battlefield." << endl;
    cout << "Deploying a creature on position '2' will put the creature between the two creatures on the field." << endl;
    cout << "Please try to deploy 1 more creature." << endl;
    response = "";
    while (currentElixir == totalElixir-1) {
        cout << WHITE << "Your move: ";
        cin >> response;
        if (response == "deploy") {
            deploy(currentElixir, deck, head1);
        }
        else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << endl;
            cout << RED << "Please deploy 1 more creature." << endl;
        }
    }
    printBattleScreen(head1, cardhead1, head2, currentElixir, deck);

    cout << BLUE << "Now notice your elixir count. After deploying 2 creatures, you now have 0 elixir." << endl;
    cout << "Without elixir, you can't do anything. To proceed to next round, just type \"next\"." << endl;
    cout << WHITE << "Your move: ";
    cin >> response;
    while (response != "next") {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << RED << "Type \"next\" to proceed to next round." << endl;
        cout << WHITE << "Your move: ";
        cin >> response;
    }

    currentElixir = totalElixir;
    cout << "------------------------------------------------------------------------------" << endl << endl;
    opponentsResponse(currentOpponent.opponentCreature, currentElixir, head2, cardhead2, head1);

    totalElixir++;
    currentElixir = totalElixir;
    roundStart(head1, head2, currentElixir);
    printBattleScreen(head1, cardhead1, head2, currentElixir, deck);

    cout << BLUE << "To defeat the opponent, you have to eliminate all of the opponent's creature on the field." << endl;
    cout << "When a creature's hp drops to 0, the creature is eliminated." << endl;
    cout << GREEN << "Press enter to continue." << WHITE << endl;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, trash);
    cout << BLUE << "You can attack the opponent's creature by typing the command \"attack <opponent's creature name> with <your creature name>\"." << endl;
    cout << "Attacking: If you want to use " << head1->deployedCreature.getname() << " to attack the opponent's " << head2->deployedCreature.getname() << "," << endl;
    cout << "           Type 'attack " << head2->deployedCreature.getname() << " with " << head1->deployedCreature.getname() << "'." << endl;
    cout << "           Then the opponent's " << head2->deployedCreature.getname() << "'s hp (health point) will decrease by the 'atk' amount of your " << head1->deployedCreature.getname() << "." << endl;
    cout << "           And you will have used 'cost of " << head1->deployedCreature.getname() << " = " << head1->deployedCreature.getcost() << "' amount of elixir to attack the opponent's creature." << endl;
    cout << GREEN << "Press enter to continue." << WHITE << endl;
    getline(cin, trash);
    cout << BLUE << "Now try to use the attack command." << endl;
    while (currentElixir == totalElixir) {
        cout << WHITE << "Your move: ";
        cin >> response;
        if (response == "attack") {
            attack(head1, head2, cardhead1, currentElixir);
        }
        else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << endl;
            cout << RED << "Please use the attack command." << endl;
        }
    }
    printBattleScreen(head1, cardhead1, head2, currentElixir, deck);

    cout << BLUE << "Great Job!" << endl;
    cout << "Notice that your elixir count has decreased by 'cost' amount of elixir." << endl;
    cout << GREEN << "Press enter to continue." << WHITE << endl;
    getline(cin, trash);
    cout << BLUE << "And notice the cards in your hands. You now have 6 cards! You will automatically draw a card from the attacking creature every time you attack." << endl;
    cout << GREEN << "Press enter to continue." << WHITE << endl;
    getline(cin, trash);
    cout << BLUE <<"Now you can try to deploy more creatures on the field, or attack once more if you have enough elixir." << endl;
    cout << "Or just proceed to the next round by typing 'next'." << endl;
    cout << GREEN << "Press enter to continue." << WHITE << endl;
    getline(cin, trash);
    playersMove(head1, head2, currentElixir, deck, cardhead1);

    currentElixir = totalElixir;
    opponentsResponse(currentOpponent.opponentCreature, currentElixir, head2, cardhead2, head1);

    totalElixir++;
    currentElixir = totalElixir;
    roundStart(head1, head2, currentElixir);
    printBattleScreen(head1, cardhead1, head2, currentElixir, deck);

    cout << BLUE << "Now it's time to learn how to use cards in battle." << endl;
    cout << "You can use cards on one creature at a time. Each card costs a certain amount of elixir when used." << endl;
    cout << "Cards give creatures various kinds of special effects. Different cards have different effects when used." << endl;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << GREEN << "Press enter to continue." << WHITE << endl;
    getline(cin, trash);
    cout << BLUE << "You can use a card by typing the command \"use <the card's name> on <the creature's name>\"." << endl;
    cout << "Cards can be used on either your creature or opponent's creature." << endl;
    cout << "Using card: If you want to use " << cardhead1->theCard.getname() << " on " << head1->deployedCreature.getname() << "," << endl;
    cout << "            Type 'use " << cardhead1->theCard.getname() << " on " << head1->deployedCreature.getname() << "'." << endl;
    cout << "            And you will have used 'cost of " << cardhead1->theCard.getname() << " = " << cardhead1->theCard.getcost() << "' amount of elixir after using the card." << endl;
    cout << GREEN << "Press enter to continue." << WHITE << endl;
    getline(cin, trash);
    cout << BLUE << "Now try to use a card." << endl;
    while (currentElixir == totalElixir) {
        cout << WHITE << "Your move: ";
        cin >> response;
        if (response == "use") {
            use(head1, head2, currentElixir, cardhead1);
        }
        else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << endl;
            cout << RED << "Please use a card." << endl;
        }
    }
    printBattleScreen(head1, cardhead1, head2, currentElixir, deck);

    cout << BLUE << "Good Job!" << endl;
    cout << "Used card will be discarded from your hand." << endl;
    cout << GREEN << "Press enter to continue." << WHITE << endl;
    getline(cin, trash);
    cout << BLUE << "Each card has a different function. If you want to check the function of a card, you can use the {show} command" << endl;
    cout << "For example, type \"show card " << cardhead1->theCard.getname() << "\" to check the function of the card named " << cardhead1->theCard.getname() << "." << endl; 
    cout << GREEN << "Press enter to continue." << WHITE << endl;
    getline(cin, trash);
    cout << BLUE << "Now try to use the {show} command." << endl;
    cout << WHITE << "Your move: ";
    cin >> response;
    while (response != "show") {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << RED << "Please use the {show} command by typing 'show card _cardname_'." << endl;
        cout << WHITE << "Your move: ";
        cin >> response;
    }
    show(head1, head2, deck, cardhead1);
    
    cout << BLUE << "So as you can see, the function for the card is shown to you." << endl;
    cout << "You can also use the {show} command on creatures:" << endl;
    cout << "To show information about undeployed creatures: type 'show creature <creature no. on left of the screen>'" << endl;
    cout << "To show information of deployed creatures: type 'show creature <name of creature>'" << endl;
    cout << GREEN << "Press enter to continue." << WHITE << endl;
    getline(cin, trash);

    cout << BLUE << "So that's it. Now try to defeat the opponent by yourself!" << endl;
    cout << "Attack or use cards strategically to deal damage to the enemy and eliminate them from the battlefield!" << endl;
    cout << "Good luck!" << endl;
    cout << GREEN << "Press enter to continue." << WHITE << endl;
    getline(cin, trash);
    playersMove(head1, head2, currentElixir, deck, cardhead1);

    currentElixir = totalElixir;
    opponentsResponse(currentOpponent.opponentCreature, currentElixir, head2, cardhead2, head1);

    while (head1 != NULL && head2 != NULL) {
        if (totalElixir < 10) {    
            totalElixir++;
        }
        currentElixir = totalElixir;
        roundStart(head1, head2, currentElixir);
        playersMove(head1, head2, currentElixir, deck, cardhead1);
        currentElixir = totalElixir;
        
        roundStart(head2, head1, currentElixir);
        //playersMove(head2, head1, currentElixir, currentOpponent.opponentCreature, cardhead2);
        opponentsResponse(currentOpponent.opponentCreature, currentElixir, head2, cardhead2, head1);
    }
    printBattleScreen(head1, cardhead1, head2, currentElixir, deck);
    battleResults(head1, head2, winlose);
}