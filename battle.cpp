#include<iostream>
#include<string>
#include<sstream>
#include<stdlib.h>
#include<time.h>
#include<limits>
#include "battle.h"
using namespace std;

// to deploy a creature on battle field
// format : deploy <creature number> <creature position>
// negates all invalid input
void deploy (int &currentElixir, creature deck[], deployed * &head) {
    if (numberOfCreatures(head) == 4) {
        cin.clear(); 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "You can only have a maximum of 4 creatures on the field" << endl;
        return;
    }
    
    int creatureidx;
    cin >> creatureidx;
    while ( cin.fail() ) {
        cin.clear(); 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "To deploy a creature, please type the <creature number>, followed by the <position> that you wish to deploy the creature at." << endl;
        cout << "Please enter the creature number properly" << endl;
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
    return;
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
    return;
}

// randomly draw 5 cards from all creatures' card at start of battle
void initialiseCard (cardOnHand * &cardhead, creature deck[], int push) {
    for (int i = 0; i < 5; i++) {
        srand(time(NULL)+push);
        addCardToHand(cardhead, deck[( rand() % 24 ) / 5].cardpool[( rand() % 24 ) % 5]);
        push++;
    }
    return;
}

void death (deployed * &creaturenode, deployed * &head) {
    deployed * deleteafter = head;
    if (deleteafter == creaturenode) {
        head = creaturenode->next;
        if (creaturenode->deployedCreature.getstatus("elixirsap") < 0) {
            creaturenode->next->deployedCreature.setstatus("elixirsap", creaturenode->deployedCreature.getstatus("elixirsap"));
        }
        delete creaturenode;
    }
    else {
        while (deleteafter->next != creaturenode) {
            deleteafter = deleteafter->next;
        }
        if (creaturenode->deployedCreature.getstatus("elixirsap") < 0) {
            deleteafter->deployedCreature.setstatus("elixirsap", creaturenode->deployedCreature.getstatus("elixirsap"));
        }
        deleteafter->next = creaturenode->next;
        delete creaturenode;
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
        cout << "Invalid target name inserted. Please check your spelling." << endl;
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
    
    if (heroic == true && targetnode->deployedCreature.getstatus("heroic") == 0) {
        cout << "You can only attack creatures with heroic." << endl;
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
        cout << "Not enough elixir!" << endl;
        return;
    }
    else {
        currentElixir = currentElixir - attackernode->deployedCreature.getcost();
    }

    if (targetnode->deployedCreature.getstatus("blind") > 0) {
        cout << "MISSED!" << endl;
        targetnode->deployedCreature.setstatus("blind", -1);
    }
    
    bool critical = false;
    int byHowMuch = attackernode->deployedCreature.getatk(critical);
    targetnode->deployedCreature.decreasehp(byHowMuch);
    if (critical == true) {
        cout << "CRITICAL ATTACK !!!" << endl;
    }

    if (attackernode->deployedCreature.getstatus("blockcard") > 0) {
        cout << "No card drawn. Blocked." << endl;
        attackernode->deployedCreature.setstatus("blockcard", -1);
    }
    else if (numberOfCards(playerscard) < 10) {
        int idxOfCardDrawn = drawCard(attackernode->deployedCreature);
        addCardToHand(playerscard, attackernode->deployedCreature.cardpool[idxOfCardDrawn]);
        attackernode->deployedCreature.cardpool[idxOfCardDrawn].cardDrawn();
    } 
    else {
        cout << "Hand full." << endl;
    }

    if (attackernode->deployedCreature.getstatus("atk") != 0) {
        attackernode->deployedCreature.atk(0);
    }
    
    attackernode->deployedCreature.thorns(byHowMuch, targetnode->deployedCreature);

    attackernode->deployedCreature.elixirsap(targetnode->deployedCreature, currentElixir, true);

    if (targetnode->deployedCreature.gethp() <= 0) {
        death(targetnode, opponent);
    }
    else if (attackernode->deployedCreature.gethp() <= 0) {
        death (attackernode, player);

        targetnode->deployedCreature.counteratk(player->deployedCreature);

        targetnode->deployedCreature.elixirsap(player->deployedCreature, currentElixir, true);

        if (player->deployedCreature.gethp() <= 0) {
            death (attackernode, player);
        }
        if (targetnode->deployedCreature.gethp() <= 0) {
            death(targetnode, opponent);
        }
    }
    else {
        targetnode->deployedCreature.counteratk(attackernode->deployedCreature);
        
        if (attackernode->deployedCreature.gethp() <= 0) {
            death (attackernode, player);
        }
        if (targetnode->deployedCreature.gethp() <= 0) {
            death(targetnode, opponent);
        }
    }
    return;
}

void use (deployed *&player, deployed * &opponent, int &currentElixir, cardOnHand * &playerscard) {
    string fullsentence;
    getline(cin, fullsentence);

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
        cout << "To use a card on a creature, please type \"use <card's name> on <creature's name>\"" << endl;
        cout << "You did not type the word \"on\"" << endl;
        return;
    }
    if (name == "") {
        cout << "No card name inserted." << endl;
        return;
    }

    cardOnHand * cardnode = playerscard;
    while (cardnode != NULL && cardnode->theCard.getname() != name) {
            cardnode = cardnode->next;
    }
    if (cardnode == NULL) {
        cout << "Invalid card name inserted. Please check your spelling." << endl;
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
        cout << "No creature name inserted." << endl;
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
        cout << "Invalid creature name inserted. Please check your spelling." << endl;    
        return;
    }
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

    if (creaturenode1->deployedCreature.getstatus("silence") > 0) {
        cout << "The creature is silenced. You cannot play card on it." << endl;
        return;
    }

    if (cardnode->theCard.getcost() > currentElixir) {
        cout << "Not enough elixir!" << endl;
        return;
    }
    else {
        currentElixir = currentElixir - cardnode->theCard.getcost();
    }

    string cardFunction = cardnode->theCard.getfunction();
    istringstream iss2 (cardFunction);

    string condition;
    string trash;
    int number;

    while (iss2 >> condition) {
        iss2 >> trash;
        iss2 >> number;

        if (condition == "magic") {
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

                creaturenode1->deployedCreature.magic(targetnode->deployedCreature);
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
                if (numberOfCards(playerscard) < 10) {
                    int idxOfCardDrawn = drawCard(creaturenode1->deployedCreature);
                    addCardToHand(playerscard, creaturenode1->deployedCreature.cardpool[idxOfCardDrawn]);
                    creaturenode1->deployedCreature.cardpool[idxOfCardDrawn].cardDrawn();
                } 
                else {
                    cout << "Hand full." << endl;
                    i = number;
                }
            }
            cout << number << " card drawn from " << creaturenode1->deployedCreature.getname() << endl;
        }
        else if (condition == "atk") {
            creaturenode1->deployedCreature.atk(number);
        } 
        else if (condition == "heal") {
            creaturenode1->deployedCreature.heal(number);
        }
        else if (condition == "directdmg") {
            creaturenode1->deployedCreature.directdmg(number);
        }
        else {
            creaturenode1->deployedCreature.setstatus(condition, number);
        }

        creaturenode1->deployedCreature.haste(false);

        iss2 >> trash;
    }

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

    return;
}

void show (deployed * player, deployed * opponent, creature deck[], cardOnHand * playerscard) {
    string type;
    cin >> type;

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
                cout << "Invalid creature name inserted. Please check your spelling." << endl;    
                return;
            }
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
                cout << "invalid creature number inserted" << endl;
                return;
            }
        }
    }
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
            cout << "Invalid card name entered. Please check your spelling." << endl;
            return;
        }
        else {
            cout << cardnode->theCard.getfunction();
        }
    }
    else {
        cin.clear(); 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "To show info of a creature / card, please type \"show <type: creature/card> <name of creature/number of undeployed creature/name of card>" << endl;
        return;
    }
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
        else if (action == "use") {
            use(player, opponent, currentElixir, playerscard);
        }
        else if (action == "show") {
            show(player, opponent, deck, playerscard);
        }
        else if (action == "next") {
            cout << "------------------------------------------------------------------------------" << endl;
            return;
        }
        else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid response. Please check your spelling." << endl;
        }
    }
}

void roundStart (deployed * &player, deployed * &opponent, int &currentElixir) {
    if (player != NULL && opponent != NULL) {
        deployed * currentnode = player;
        while (currentnode != NULL) {
            if (currentnode->deployedCreature.getstatus("niceland") != 0) {
                currentnode->deployedCreature.heal(10);
            }

            currentnode->deployedCreature.elixirsap(currentnode->deployedCreature, currentElixir, false);
            currentnode->deployedCreature.haste(true);

            currentnode->deployedCreature.revenge(0, true, opponent->deployedCreature);
            if (opponent->deployedCreature.gethp() <= 0) {
                death(opponent, opponent);
            }
            if (currentnode->deployedCreature.gethp() <= 0) {
                currentnode = currentnode->next;
                death(currentnode, player);
                break;
            }

            currentnode->deployedCreature.poison();
            if (currentnode->deployedCreature.gethp() <= 0) {
                currentnode = currentnode->next;
                death(currentnode, player);
                break;
            }

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

void battleResults (deployed * player, deployed * opponent) {
    if (player == NULL) {
        cout << "You lose!" << endl;
    }
    else if (opponent == NULL) {
        cout << "You win!" << endl;
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
        roundStart(head1, head2, currentElixir);
        playersMove(head1, head2, currentElixir, deck, cardhead1);
        currentElixir = totalElixir;
        roundStart(head2, head1, currentElixir);
        playersMove(head2, head1, currentElixir, currentOpponent.opponentCreature, cardhead2);
        //opponentsResponse();
    }
    printBattleScreen(head1, cardhead1, head2, currentElixir, deck);
    battleResults(head1, head2);
}