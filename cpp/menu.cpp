#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <limits>
#include <iomanip>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "../hfiles/movement.h"
#include "../hfiles/menu.h"
#include "../hfiles/structs.h"
#include "../hfiles/titleScreen.h"
#include "../hfiles/colours.h"
#include "../hfiles/battle.h"
#include "../classes/avatar.h"
#include "../classes/creature.h"
#include "../classes/currency.h"

using namespace std;

// CREATURES

void displayCreatureByPage(int pageCount, owned * ownedhead) {
    cout << "No.          NAME              SYMBOL  " <<endl;
    int count = 0;
    while (count < 10) {
        bool own = false;
        owned * currentnode = ownedhead;
        while (currentnode != NULL && currentnode->index < ((pageCount-1) * 10 + count + 1)) {
            currentnode = currentnode->next;
        }
        if (currentnode != NULL) {
            if (currentnode->index == ((pageCount-1) * 10 + count + 1)) {
                own = true;
            }
        }
        if (own) {
            creature temp;
            temp.setbasestats(currentnode->index);
            temp.setcurrentstats(1);
            cout << setw(2) << count << '.' << setw(25) << temp.getname() << "  "<< setw(8) << temp.getsymbol() << endl;
        }
        else {
            cout << setw(2) << count << '.' << setw(25) << "???" << "  "<< setw(8) << "???" << endl;
        }
        count ++;
    }
}

void displayAvatarByPage(int avataridx[]) {
    cout << "No.          NAME              SYMBOL  " <<endl;
    for (int i = 0; i < 10; i++) {
        if (avataridx[i] != 0) {
            avatar temp;
            temp.set(i+1);
            cout << setw(2) << i << '.' << setw(25) << temp.getname() << "  "<< setw(8) << temp.getfigure() << endl;
        }
        else {
            cout << setw(2) << i << '.' << setw(25) << "???" << "  "<< setw(8) << "???" << endl;
        }
    }
}

void displayCreatureDetails (int index, int level) {
    creature temp;
    temp.setbasestats(index);
    temp.setcurrentstats(level);
    cout << endl;
    temp.getcurrentstats();
    cout << endl;
}

void displayAvatarDetails (int index) {
    avatar temp;
    temp.set(index);
    cout << temp.getfigure() << endl;
    cout << temp.getname() << endl;
    cout << "Cards:" << endl;
    for (int i = 0; i < 5; i++) {
        string clean;
        temp.cardpool[i].getfunction(clean);
        cout << i+1 << ". " << setw(25) << temp.cardpool[i].getname() << "-> Function: " << clean << endl;
    }    
}

// display 10 owned creatures each page
void displayOwnedCreaturesByPage(int pageCount, owned * ownedhead){
    cout << "No.          NAME              SYMBOL   LEVEL " << endl;
    owned * printhead = ownedhead;
    for (int i = 0; i < 10*(pageCount-1); i++) {
        printhead = printhead->next;
    }
    //cout << ownedCreature[0].name << " in creatures page" << endl;
    int count = 0;
    for (int i = 10*(pageCount-1); i < 10*(pageCount-1)+10 && printhead != NULL; i++) {
        creature temp;
        temp.setbasestats(printhead->index);
        temp.setcurrentstats(printhead->level);
        cout << setw(2) << count << '.' << setw(25) << temp.getname() << "  " << setw(8) << temp.getsymbol() << "  " << setw(6) << printhead->level << endl;
        count ++;
        printhead = printhead->next;
    }
}

void displayCreature(string choice, owned * ownedhead, creature deck[5], currency &currentcurrency) {
    string viewChoiceList[10] = {"0","1","2","3","4","5","6","7","8","9"};  
    string pageChoiceList[10] = {"10","1","2","3","4","5","6","7","8","9"};
    string creatureStats[] = {"   HP   ", "  COST  ", "  ATK   ", "  MGC   ", "  CRT   "};
    // main menu
    if (choice=="main"){
        int pageCount = 1 ,maxPageCount = 8;  //maxPageCount can be changed depending on the number of creatures, try to not exceed single digit pages (more convenient?)
        char playersChoice[3] = "P1";
        cout << BLUE << "\n = CREATURE BOOK = \n" << WHITE;
        while (toupper(playersChoice[0])!='Q'){
            cout << "\nPAGE " << pageCount << endl;
            displayCreatureByPage(pageCount, ownedhead);
            cout << "\nPress V together with a creature's number to view the creature's stats. [Eg: V3 to view the creature 3]\n";
            cout << "Press P together with a page number to turn to that page. [Eg: P6 to skip to page 6]\n";
            cout << "Press Q to return to main menu. \n";
            cout << "Your choice: ";
            cin >> playersChoice;
            if (toupper(playersChoice[0])=='Q'){break;}
            while ((toupper(playersChoice[0]) != 'P' && toupper(playersChoice[0]) != 'V') || (toupper(playersChoice[0]) == 'P'  && find(pageChoiceList,end(pageChoiceList), string(playersChoice).substr(1)) == end(pageChoiceList)) || (toupper(playersChoice[0]) == 'V' && find(viewChoiceList,end(viewChoiceList), string(playersChoice).substr(1)) == end(viewChoiceList)) || cin.fail()){
                cin.clear();  
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "\x1B[31m" << "\nPress V together with a creature's number to view the creature's stats. [Eg: V3]\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Press P together with a page number to turn to that page. [Eg: P6]\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Press Q return to main menu.\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Your choice: "<< "\x1B[0m" ;
                cin >> playersChoice;
                if (toupper(playersChoice[0])=='Q'){break;}
            }
            switch (toupper(playersChoice[0])){
                case 'P':
                    if (stoi(string(playersChoice).substr(1)) <= maxPageCount) {
                        pageCount = stoi(string(playersChoice).substr(1));
                    }
                    else {
                        cout << RED << "Exceeded maximum page count" << WHITE << endl;
                    }
                    break;
                case 'V': {
                    int creatureNumber;
                    creatureNumber = stoi(string(playersChoice).substr(1))+((pageCount-1)*10);
                    owned * node = ownedhead;
                    while (node != NULL && node->index < creatureNumber+1) {
                        node = node->next;
                    }
                    if (node == NULL) {
                        cout << RED << "You do not own this creature." << WHITE << endl;
                    }
                    else if (node->index == creatureNumber + 1) {
                        displayCreatureDetails(creatureNumber + 1, 1);
                        cout << "Enter R to return to creature page: ";
                        cin >> playersChoice;
                        while (toupper(playersChoice[0]) != 'R'){
                            cout << "\x1B[31m" << "\nEnter R to return to creature page: " << "\x1B[0m";
                            cin >> playersChoice;
                        }
                    }
                    else {
                        cout << RED << "You do not own this creature." << WHITE << endl;
                    }
                    break;
                }
                case 'Q':
                    cout << "";
                    break;
            }
        }
    }
    // inventory menu
    if (choice=="inventory") {
        int count = 0, pageCount = 1 ,maxPageCount = 0;
        owned * iterator = ownedhead;
        while (iterator != NULL) {
            count ++;
            iterator = iterator->next;
        }
        maxPageCount = count / 10 + 1;
        count = 0;
        char playersChoice[3] = {0};
        string changeChoiceList[50];
        for (int i = 10; i < 60; i++){
            changeChoiceList[count] = to_string(i);
            count++;
        }
        while (toupper(playersChoice[0])!='Q'){
            cout << BLUE << "\n = YOUR CREATURES = \n" << WHITE;
            for (int i = 0; i < 5; i++) {
                string str = "(" + to_string(i+1) + ")";
                cout << left;
                cout << setw(27) << str;
            }
            cout << endl;
            for (int i = 0; i < 5; i++) {
                string str = "   " + deck[i].getsymbol();
                cout << left;
                cout << setw(27) << str;
            }
            cout << endl;
            for (int i = 0; i < 5; i++) {
                string str = "name: " + deck[i].getname();
                cout << left;
                cout << setw(27) << str;
            }
            cout << endl;
            for (int i = 0; i < 5; i++) {
                string str = "cost: " + to_string(deck[i].getcost());
                cout << left;
                cout << setw(27) << str;
            }
            cout << endl;
            for (int i = 0; i < 5; i++) {
                string str = "hp: " + to_string(deck[i].gethp());
                cout << left;
                cout << setw(27) << str;
            }
            cout << endl;
            for (int i = 0; i < 5; i++) {
                string str = "atk: " + to_string(deck[i].getoriginalatk());
                cout << left;
                cout << setw(27) << str;
            }
            cout << endl;
            for (int i = 0; i < 5; i++) {
                string str = "mgc: " + to_string(deck[i].getoriginalmgc());
                cout << left;
                cout << setw(27) << str;
            }
            cout << endl;
            for (int i = 0; i < 5; i++) {
                string str = "crt: " + to_string(deck[i].getcrt()) + "%";
                cout << left;
                cout << setw(27) << str;
            }
            cout << endl;
            cout << endl;
            cout << "PAGE " << pageCount << endl;
            displayOwnedCreaturesByPage(pageCount, ownedhead);
            cout << "\nPress V together with a creature's number to view the creature's stats. [Eg: V3 to view creature 3]\n";
            cout << "Press P together with a page number to turn to that page. [Eg: P6 to skip to page 6]\n";
            cout << "Press C together with creature's number on the creatures' deck that you wanna change followed by the creature's number that is swapping in.\n";
            cout << "[Eg: C37 to swap out creature 3 from the deck for creature 7 shown on current page.]\n";
            cout << "Press Q to return to inventory menu. \n";
            cout << "Your choice: ";
            cin >> playersChoice;
            if (toupper(playersChoice[0])=='Q'){break;}
            while ((toupper(playersChoice[0]) != 'P' && toupper(playersChoice[0]) != 'V' && toupper(playersChoice[0]) != 'C') || (toupper(playersChoice[0]) == 'C' && find(changeChoiceList,end(changeChoiceList), string(playersChoice).substr(1)) == end(changeChoiceList)) || (toupper(playersChoice[0]) == 'P'  && find(pageChoiceList,end(pageChoiceList), string(playersChoice).substr(1)) == end(pageChoiceList)) || (toupper(playersChoice[0]) == 'V' && find(viewChoiceList,end(viewChoiceList), string(playersChoice).substr(1)) == end(viewChoiceList)) || cin.fail() ){
                cin.clear();  
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "\x1B[31m" << "\nPress V together with a creature's number to view the creature's stats. [Eg: V3]\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Press P together with a page number to turn to that page. [Eg: P6]\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Press C together with creature's number on the creatures' deck that you wanna change followed by the creature's number that is swapping in.\n" << "\x1B[0m";
                cout << "\x1B[31m" << "[Eg: C37 to swap out creature 3 from the deck for creature 7 shown on current page.]\n" << "\x1B[0m" ;
                cout << "\x1B[31m" << "Press Q return to inventory menu.\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Your choice: "<< "\x1B[0m" ;
                cin >> playersChoice;
                if (toupper(playersChoice[0])=='Q'){break;}
            }
            switch (toupper(playersChoice[0])){
                case 'P': {
                    if (stoi(string(playersChoice).substr(1)) > maxPageCount) {
                        cout << RED << "Exceeded maximum page count" << WHITE << endl;
                        cout << endl;
                    }
                    else {
                        pageCount = stoi(string(playersChoice).substr(1));
                    }
                    break;
                }
                case 'V': {
                    int creatureNumber = stoi(string(playersChoice).substr(1)) + ((pageCount-1)*10);
                    /*if (ownedCreature[stoi(string(playersChoice).substr(1))+((pageCount-1)*10)].index == 0){
                        cout << "\x1B[31m" << "Invalid input!\n" << "\x1B[0m";
                        break;
                    }*/
                    owned * node = ownedhead;
                    for (int i = 0; node != NULL && i < creatureNumber; i++) {
                        node = node->next;
                    }
                    if (node != NULL) {
                        displayCreatureDetails(node->index, node->level);
                        cout << "\nEnter R to return to creature page: ";
                        cin >> playersChoice;
                        while (toupper(playersChoice[0]) != 'R'){
                            cout << "\x1B[31m" << "\nEnter R to return to creature page: " << "\x1B[0m";
                            cin >> playersChoice;
                        }
                    }
                    else {
                        cout << RED << "Invalid input." << WHITE << endl;
                        cout << endl;
                    }
                    break;
                }
                case 'C': {
                    int creatureNumber = stoi(string(playersChoice).substr(2,1)) + ((pageCount-1)*10);
                    owned * node = ownedhead;
                    for (int i = 0; i < creatureNumber; i++) {
                        node = node->next;
                    }
                    creature temp;
                    temp.setbasestats(node->index);
                    temp.setcurrentstats(node->level);
                    string name[5];
                    for (int i = 0; i < 5; i++) {
                        name[i] = deck[i].getname();
                    } 
                    if (find(name, name+5, temp.getname()) != name+5){
                        cout << "\x1B[31m" << "\nThis creature is already in your deck.\n" << "\x1B[0m" ;
                    }
                    else if ((stoi(string(playersChoice).substr(1))>9 || stoi(string(playersChoice).substr(1))<60)){  //
                        deck[stoi(string(playersChoice).substr(1,1))-1] = temp;   //test whether this work
                    }
                    else {cout << "\x1B[31m" << "Please enter your choice according to the instructions given. \n" << "\x1B[0m";}
                    
                    break;
                }
                case 'Q': {
                    cout << "";
                    break;
                }
            }
        }
    }
    // upgrade
    if (choice=="upgrade") {
        int count = 0, pageCount = 1 ,maxPageCount = 0;
        owned * iterator = ownedhead;
        while (iterator != NULL) {
            count ++;
            iterator = iterator->next;
        }
        maxPageCount = count / 10 + 1;
        count = 0;
        string playerschoice;
        while (toupper(playerschoice[0])!='Q') {
            cout << endl;
            cout << BLUE << "= UPGRADE =" << WHITE << endl;
            cout << "PAGE " << pageCount << endl;
            displayOwnedCreaturesByPage(pageCount, ownedhead);
            cout << endl;
            cout << "Enter a number to upgrade the creature of that index number." << endl;
            cout << "Enter 'P' along with the page number to switch page. [Eg: p4 to switch to page 4]" << endl;
            cout << "Enter 'Q' to exit." << endl;
            cout << "Your response: ";
            cin >> playerschoice;
            while (cin.fail()) {
                cin.clear();  
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << RED << "Enter a number to upgrade the creature of that index number." << endl;
                cout << "Enter 'Q' to exit." << WHITE << endl;
                cout << "Your response: ";
                cin >> playerschoice;
            }
            if (playerschoice.length() == 1 && isdigit(playerschoice[0])) {
                int creaturenumber = (playerschoice[0] - '0') + ((pageCount-1)*10);
                owned * node = ownedhead;
                for (int i = 0; node != NULL && i < creaturenumber; i++) {
                    node = node->next;
                }
                creature temp;
                temp.setbasestats(node->index);
                temp.setcurrentstats(node->level);
                cout << endl;
                cout << "You need " << BLUE << (node->level)+1 << WHITE << " food to upgrade this creature" << endl;
                cout << "Name: " << temp.getname() << endl;
                cout << "Level: " << temp.getlevel() << " -> " << temp.getlevel()+1 << endl;
                cout << "Food: " << currentcurrency.food << " - " << temp.getlevel()+1 << endl;
                cout << endl;
                cout << "Are you sure you want to proceed? (y/n)" << endl;
                cout << "Your response: ";
                char yesno;
                cin >> yesno;
                while (cin.fail() || (tolower(yesno) != 'y' && tolower(yesno) != 'n')) {
                    cout << RED << "Please type 'y' or 'n'." << WHITE << endl;
                    cout << "Your response: ";
                    cin >> yesno;
                }
                if (tolower(yesno) == 'y') {
                    node->level += 1;
                    currentcurrency.food -= node->level;
                    cout << GREEN << temp.getname() << " upgraded to level " << node->level << WHITE << endl;
                }
            }
            else if (playerschoice.length() == 2 && tolower(playerschoice[0]) == 'p') {
                if ((playerschoice[1] - '0') > maxPageCount) {
                    cout << RED << "Exceeded maximum page count" << WHITE << endl;
                    cout << endl;
                }
                else {
                    pageCount = (playerschoice[1] - '0');
                }
            }
        }
    }
}

// treasure chest
void treasureChest(currency &currentcurrency, owned * &ownedhead) {
    char choice;
    int num;
    if (currentcurrency.coins < 50){
    	cout << "\x1B[31m" << "Sorry, you do not have enough coins to open the chest.\n" << "\x1B[0m";
	    return;
    }
    cout << "\nCOINS: " << currentcurrency.coins << endl;
    cout << "\nWould you like to open a treasure chest? It will cost you 50 coins.\n";
    cout << "Your choice [y/n] : ";
    cin >> choice;
    while ((tolower(choice)!='y'&&tolower(choice)!='n')||cin.fail()){
    	cin.clear();
	    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    	cout << "\x1B[31m" << "\nCOINS: " << currentcurrency.coins << endl << "\x1B[0m" ;
	    cout << "\x1B[31m" << "\nWould you like to open a treasure chest? It will cost you 10 coins.\n" << "\x1B[0m" ;
	    cout << "\x1B[31m" << "Your choice : "<< "\x1B[0m" ;
	    cin >> choice;
    }
    if (tolower(choice) == 'y'){
        currentcurrency.coins = currentcurrency.coins - 50;
	    srand (time(NULL));
        num = rand() % 75 + 1;

        creature temp;
        temp.setbasestats(num);

        cout << "\nThe creature you have gotten is " << temp.getname() << '.' << endl;
        bool own = false;
        buildLinkedListOfOwnedCreatures(ownedhead, num, 1, own);
        if (!own){
            cout << "Congratulation! This new creature has been stored in your inventory. \n";
		}
        else {
            currentcurrency.food += 2;
            cout << "You already have this creature in your inventory. You earned 2 food instead. Better luck next time!\n";
        }
	}
}

// display inventory menu
void displayInventory(creature deck[5], owned * ownedhead, int avataridx[], currency currentcurrency, avatar currentavatar){
    int choice = 0;
    while (choice!=3){
        cout << endl << HIGHLIGHT << " = INVENTORY = " << WHITE << endl;
        cout << endl;
        cout << left;
        cout << BLUE << "Coins: " << WHITE << left << setw(8) << currentcurrency.coins << BLUE << "Food: " << WHITE << left << setw(8) << currentcurrency.food << BLUE << "Gems: " << WHITE << currentcurrency.gems << endl;
        cout << BLUE << "Avatar: " << WHITE << currentavatar.getfigure() << " -> " << currentavatar.getname() << endl;
        cout << BLUE << "Deck: " << WHITE << endl;
        for (int i = 0; i < 5; i++) {
            cout << i+1 << ". " << setw(25) << deck[i].getname() << "level: " << deck[i].getlevel() << endl;
        }
        cout << endl;
        cout << BLUE << "Options:" << WHITE << endl;
        cout << "0. Change my avatar\n";
        cout << "1. Change my deck\n";
        cout << "2. Level up my deck\n";
        cout << "3. Return to main menu\n";
        cout << "Your choice: ";
        cin >> choice;
        while (choice < 0 || choice > 3 || cin.fail()) {
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << RED << "\nWhat are you looking for?\n" << WHITE;
            cout << "0. Change my avatar\n";
            cout << "1. Change my deck\n";
            cout << "2. Level up my deck\n";
            cout << "3. Return to main menu\n" << WHITE;
            cout << "Your choice: ";
            cin >> choice;
        }
        switch (choice){
            case 0: {
                string input = "";
                while (tolower(input[0]) != 'q') {
                    cout << endl;
                    cout << BLUE << "Current Avatar:" << WHITE << endl;
                    displayAvatarDetails(currentavatar.getindex());
                    cout << endl;
                    displayAvatarByPage(avataridx);
                    cout << "Which avatar do you want to change to?" << endl;
                    cout << "Enter a number, or enter 'q' to exit: ";
                    cin >> input;
                    if (input.length() == 1 && isdigit(input[0])) {
                        int num = stoi(input);
                        if (avataridx[num] != 0) {
                            currentavatar.set(num+1);
                        }
                        else {
                            cout << RED << "You do not own this avatar." << WHITE << endl;
                        }
                    }
                    else {
                        cout << endl;
                        break;
                    }
                }
                break;
            }
            case 1: {
                displayCreature("inventory", ownedhead, deck, currentcurrency);
                break;
            }
            case 2: {
                displayCreature("upgrade", ownedhead, deck, currentcurrency);
                break;
            }
            case 3:
                return;
        }
    }
}

// display shop 
void shop(owned * &ownedhead, int avataridx[], currency &currentcurrency){
    int choice = 0;
    while (choice != 3){
        cout << endl;
        cout << BLUE << "= SHOP =" << endl << endl << "Options:" << WHITE << endl;
        cout << "0. Avatars\n";
        cout << "1. Food\n";
        cout << "2. Treasure chests (random creature)\n";
        cout << "3. Return to main menu\n" << endl;
        cout << "What do you want to buy? Enter a number to choose: ";
        cin >> choice;
        while (choice > 3 || choice < 0 || cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << BLUE << "= SHOP =" << endl << endl << "Options:" << WHITE << endl;
            cout << "0. Avatars\n";
            cout << "1. Food\n";
            cout << "2. Treasure chests (random creature)\n";
            cout << "3. Return to main menu\n" << endl;
            cout << "Please enter a correct number to indicate your choice: ";
            cin >> choice;
        }
        switch (choice){
            case 0: {
                string input;
                while (toupper(input[0]) != 'Q') {
                    cout << BLUE << endl;
                    cout << "You can use 50 gems to buy one random avatar." << endl;
                    cout << "Gems: " << WHITE << currentcurrency.gems << endl;
                    cout << endl;
                    displayAvatarByPage(avataridx);
                    cout << endl;
                    cout << "Press B together with an avatar's number to purchase that avatar. [Eg: B5 to buy avatar 5]\n";
                    cout << "Press Q to return to shop menu. \n";
                    cout << "Your choice: ";
                    cin >> input;
                    while ((input.length() > 2 || input.length() < 1)) {
                        cout << RED << endl;
                        cout << "Press B together with an avatar's number to purchase that avatar. [Eg: B5 to buy avatar 5]\n";
                        cout << "Press Q to return to shop menu. \n";
                        cout << "Your choice: " << WHITE;
                        cin >> input;
                    }
                    if (toupper(input[0]) == 'B') {
                        if (!isdigit(input[1])) {
                            cout << RED << "Please enter you choice according to the format specified." << WHITE << endl;
                            break;
                        }
                        else {
                            if (avataridx[stoi(string(input).substr(1))] != 0) {
                                cout << RED << "You already owned this avatar!" << WHITE << endl;
                                cout << endl;
                                break;
                            }
                            else if (currentcurrency.gems < 50) {
                                cout << RED << "You do not have enough gems" << WHITE << endl;
                                cout << endl;
                                break;
                            }
                            else {
                                cout << "Are you sure you want to buy this avatar? (Y/N) ";
                                string input2;
                                cin >> input2;
                                if (input2 == "Y" || input2 == "y") {
                                    currentcurrency.gems -= 50;
                                    avataridx[stoi(string(input).substr(1))] = 1;
                                    cout << GREEN << "You have bought avatar " << input[1] << "!" << WHITE << endl;
                                    break;
                                }
                                else {
                                    break;
                                }
                            }
                        }

                    }
                }
                break;
            }
            case 1: {
                string input = "";
                while (input != "Q") {
                    cout << endl;
                    cout << BLUE << "You can buy 1 food using 25 coins" << WHITE << endl;
                    cout << endl;
                    cout << BLUE << "Coins: " << WHITE << currentcurrency.coins << endl;
                    cout << BLUE << "Food: " << WHITE << currentcurrency.food << endl;
                    cout << endl;
                    cout << "Press B to buy food." << endl;
                    cout << "Press Q to exit to shop." << endl;
                    string input;
                    cin >> input;
                    if (toupper(input[0]) == 'B') {
                        int number;
                        cout << "How many food do you wish to buy? ";
                        cin >> number;
                        if (cin.fail()) {
                            cin.clear();  
                            cin.ignore(numeric_limits<streamsize>::max(),'\n');
                            cout << RED << "Invalid input" << endl;
                            break;
                        }
                        else {
                            if (currentcurrency.coins < number*25) {
                                cout << RED << "You don't have enough coins to buy " << number << " food" << WHITE << endl;
                            }
                            else {
                                currentcurrency.coins -= (number*25);
                                currentcurrency.food += number;
                                cout << GREEN << "You bought " << number << " x food" << WHITE << endl;
                                break;
                            }
                        }
                    }
                    else {
                        break;
                    }
                }
                break;
            }
            case 2:
                treasureChest(currentcurrency, ownedhead);
                break;
            case 3:
                break;
        }
    }
}

void buildLinkedListOfOwnedCreatures (owned * &ownedhead, int newindex, int newlevel, bool &own) {
    owned * newnode = new owned;
    newnode->index = newindex;
    newnode->level = newlevel;
    own = false;
    
    owned * currentnode = ownedhead;
    while (currentnode != NULL) {
        if (newindex <= currentnode->index) {
            if (newindex == currentnode->index) {
                own = true;
                return;
            }
            else {
                owned * previousnode = ownedhead;
                while (previousnode->next != currentnode) {
                    previousnode = previousnode->next;
                }
                previousnode->next = newnode;
                newnode->next = currentnode;
                return;
            }
        }
        else {
            currentnode = currentnode->next;
        }
    }
    if (currentnode == ownedhead) {
        ownedhead = newnode;
        newnode->next = NULL;
    }
    else {
        currentnode = ownedhead;
        while (currentnode->next != NULL) {
            currentnode = currentnode->next;
        }
        newnode->next = NULL;
        currentnode->next = newnode;
    }
    return;
}

void load(string filename, owned * &ownedhead, int avataridx[10], currency &currentcurrency, int currentCoordinate[2], string &currentMap, avatar &currentAvatar, creature deck[5]){
    int index, level;
    string line, trash;
    ifstream fin(filename);
    
    getline(fin, line);
    istringstream iss(line);
    iss >> trash;
    while (iss >> index) {
        iss >> level;
        bool own;
        buildLinkedListOfOwnedCreatures(ownedhead, index, level, own);
    }

    getline(fin, line);
    istringstream iss1(line);
    iss1 >> trash;
    while (iss1 >> index) {
        avataridx[index-1] = 1;
    }
   
    getline(fin, line);
    istringstream iss2(line);
    iss2 >> trash;
    int count = 0;
    while (iss2 >> index) {
        iss2 >> level;
        deck[count].setbasestats(index);
        deck[count].setcurrentstats(level);
        count ++;
    }
    
    getline(fin, line);
    istringstream iss3(line);
    iss3 >> trash >> index;
    currentAvatar.set(index);

    getline(fin, line);
    istringstream iss4(line);
    iss4 >> trash;
    iss4 >> currentcurrency.coins;
    iss4 >> currentcurrency.food;
    iss4 >> currentcurrency.gems;

    getline(fin,line);
    istringstream iss5(line);
    iss5 >> trash >> currentMap;

    getline(fin, line);
    istringstream iss6(line);
    iss6 >> trash >> currentCoordinate[0] >> currentCoordinate[1];

    fin.close();
}

// to start a new game, initialize items that player has, set the avatar and creatures for players to start with
string newGame() {
    cout << "To start a new game, you need to create a save file to store the progress of your game." << endl;
    cout << "Please name your save file: ";
    string filename;
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
    getline(cin, filename);
    cout << endl;
    cout << HIGHLIGHT << "Saving to " << filename << ".txt ..." << WHITE << endl;
    
    ifstream fin ("txt/newgame.txt");
    string temp, total = "";
    while (getline(fin, temp)) {
        total = total + temp + "\n";
    }
    fin.close();

    string record = "txt/filenames.txt";
    ofstream fout;
    fout.open(record, ios::app);
    fout << filename << endl;
    fout.close();

    string fullfilename = "save/" + filename + ".txt";
    ofstream fout2 (fullfilename);
    fout2 << total;
    fout2.close();

    delay(2);
    cout << endl;
    cout << GREEN << "Success!" << WHITE << endl;
    string trash;
    cout << GREEN << "Press enter to continue" << WHITE << endl;
    cin >> trash;

    return fullfilename;
}

// for player to choose a file to load
string loadFileOption(int &option) {
    int count = 1;
    string name = "";
    string str;

    ifstream fin ("txt/filenames.txt");
    if (fin.fail()) {
        cout << RED  << "\nNo save file exists. Please start a new game.\n" << WHITE ;
        string filename = titleScreen(option);
        return filename;
    }
    while (getline(fin, name)){
        cout << setw(2) << count << ".  " << name << endl;
        count++;
    }
    cout << setw(2) << count << ".  " << "Exit to title screen" << endl;

    fin.close();
	
    int choice;
    cout << "Which file do you want to load? Enter a number to indicate your choice: ";
    cin >> choice;
    while (choice < 1 || choice > count || cin.fail()){
        cin.clear();  
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << RED << "Please enter a valid number: "<< WHITE ;
        cin >> choice;
    }

    if (choice == count) {
        string filename = titleScreen(option);
        return filename;
    }

    ifstream fin2 ("txt/filenames.txt");
    for (int i = 0; i < choice; i++) {
        getline(fin2, name);
    }
    fin2.close();

    cout << "Loading..." << endl;
    delay(1);

    string fullfilename = "save/" + name + ".txt";
    return fullfilename;
}

void save(string &filename, owned * ownedhead, int avataridx[10], currency currentcurrency, int currentCoordinate[2], string currentMap, avatar currentAvatar, creature deck[5]){
    int option;
    cout << endl;
    cout << "Do you wish to overwrite the existing file or save to a new file?" << endl;
    cout << "1: Overwrite" << endl;
    cout << "2. New file" << endl;
    cout << "Please enter a number: ";
    cin >> option;
    while (cin.fail() || (option != 1 && option != 2)) {
        cin.clear();  
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << RED << "Please enter a valid number: " << WHITE;
        cin >> option;
    }
    if (option == 2) {
        cout << "\nWhat would you like to name your new file? ";
        cin >> filename;
        ofstream fout("txt/filenames.txt",ios::app);
        fout << filename << endl;
        fout .close();

        filename = "save/" + filename + ".txt";
    }
    string line;
    ofstream fout(filename);

    fout << "creature";
    while (ownedhead != NULL) {
        fout << ' ' << ownedhead->index << ' ' << ownedhead->level;
        ownedhead = ownedhead->next;
    }
    fout << endl << "avatar";
    for (int i = 0; i < 10 && avataridx[i] != 0; i++){
        fout << ' ' << i+1;
    }
    fout << endl << "creaturesDeck";
    for (int i = 0; i < 5; i++){
        fout << ' ' << deck[i].getcreaturenumber() << ' ' << deck[i].getlevel();
	}
    fout << endl << "currentAvatar " << currentAvatar.getindex() << endl;
    fout << "currency " << currentcurrency.coins << ' ' << currentcurrency.food << ' ' << currentcurrency.gems << endl;
    fout << "currentMap " << currentMap << endl;
    fout << "currentCoordinate " << currentCoordinate[0] << ' ' << currentCoordinate[1] << endl;
    fout.close();

    cout << endl << HIGHLIGHT << "Progress saved successfully!"  << WHITE << endl << endl;
}

// main menu page
void mainMenuPage(currency &currentcurrency, avatar &currentavatar, creature deck[5], string &filename, owned * ownedhead, int avataridx[10], int currentcoordinate[2], string currentMap, bool &quit){
    int choice = 0;
    while (choice != 5 && choice != 6) {
        cout << endl;
        cout << HIGHLIGHT << "\n = MENU PAGE = \n" << WHITE;
        cout << endl;
        cout << "1. Inventory\n";
        cout << "2. Creature book\n";
        cout << "3. Shop\n";
        cout << "4. Save Game\n";
        cout << "5. Exit Menu\n";
        cout << "6. Exit Game\n";
        cout << "What are you looking for? Enter a number to select. ";
        cin >> choice;
        while (choice>6 || choice<1 || cin.fail()){
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << endl;
            cout << HIGHLIGHT << "\n = MENU PAGE = \n" << WHITE;
            cout << endl;
            cout << "1. Inventory\n";
            cout << "2. Creature book\n";
            cout << "3. Shop\n";
            cout << "4. Save Game\n";
            cout << "5. Exit Menu\n";
            cout << "6. Exit Game\n"; 
            cout << RED << "Please enter a correct number to indicate your choice. [0,1,2,3,4,5,6,7]\n" << WHITE ;
            cout << "Please enter a number: "; 
            cin >> choice;
        }
        switch (choice) {
            case 1:
                displayInventory(deck, ownedhead, avataridx, currentcurrency, currentavatar);
                break;
            case 2:
                displayCreature("main", ownedhead, deck, currentcurrency);
                break;
            case 3:
                shop(ownedhead, avataridx, currentcurrency);
                break;
            case 4:
                save(filename, ownedhead, avataridx, currentcurrency, currentcoordinate, currentMap, currentavatar, deck);
                break;
	        case 5:
                break;
            case 6:
                cout << "\x1B[31m" << "Are you sure that you want to quit the game? [y/n] \n" << "\x1B[0m";
                char toQuit;
                cin >> toQuit;
                while ((tolower(toQuit)!='y' && tolower(toQuit)!='n') || cin.fail()){
                    cin.clear();  
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "\x1B[31m" << "Please enter y or n to indicate your choice.\n" << "\x1B[0m";
                    cin >> toQuit;
                }
                if (toQuit=='y'){
                    save(filename, ownedhead, avataridx, currentcurrency, currentcoordinate, currentMap, currentavatar, deck);
                    quit = true;
                }
                else { 
                    break;
                }
                break;
        }

    }
}
