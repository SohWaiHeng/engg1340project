#include<iostream>
#include<fstream>
#include<sstream>
#include "card.h"
using namespace std;

// set the card's name, cost and its functions
void card::setcard (int cardno) {
    // take in input from card.txt
    // card.txt stores all available cards in the game
    ifstream fin;
    fin.open("classes/txt/card.txt");
    if (fin.fail()) {
        cout << "fail to load cards" << endl;
    }

    int line = -1;
    string fullstatus;
    // find the card's index no. in card.txt
    while (cardno > line) {
        getline(fin, fullstatus);
        line++;
        if (cardno == line) {
            int integer;
            string name;
            istringstream iss(fullstatus);
            
            // take in card's index no.
            iss >> integer;
            cardnumber = integer;

            // take in card's name
            iss >> integer;
            cardnamelength = integer;
            cardname = "";
            for (int i = 0; i < integer; i++) {
                iss >> name;
                if (cardname != "") {
                    cardname = cardname + " " + name;
                }
                else {
                    cardname += name;
                }
            }

            // take in card's cost
            iss >> integer;
            cardcost = integer;

            // take in card's rarity
            iss >> integer;
            cardrarity = integer;

            // take in card's functions
            // card functions are stored in the variable cardstatus of type "struct status" defined in status.h
            // eg: if the card's function is "give the creature 2 shields", then cardstatus.shield = 2, other members in cardstatus = 0
            int count = 0;
            int * status[] = {&cardstatus.area, &cardstatus.remove,
                            &cardstatus.counteratk, &cardstatus.haste, &cardstatus.atk,
                            &cardstatus.magic, &cardstatus.shield, &cardstatus.elixirsap, &cardstatus.addelixir, &cardstatus.drawcard,
                            &cardstatus.heal, &cardstatus.directdmg, &cardstatus.niceland,  
                            &cardstatus.thorns, &cardstatus.heroic, &cardstatus.revenge, &cardstatus.defenseup, 
                            &cardstatus.poison, &cardstatus.blind, &cardstatus.silence, &cardstatus.blockcard};
            while (iss >> integer) {
                (*status[count]) = integer;
                count ++;
            }
        }
    }
    // and thus a card is stored
    fin.close();
}

// print out the card's functions
void card::getfunction () {
    int status[] = {cardstatus.area, cardstatus.remove,
                    cardstatus.counteratk, cardstatus.haste, cardstatus.atk,
                    cardstatus.magic, cardstatus.shield, cardstatus.elixirsap, cardstatus.addelixir, cardstatus.drawcard,
                    cardstatus.heal, cardstatus.directdmg, cardstatus.niceland,  
                    cardstatus.thorns, cardstatus.heroic, cardstatus.revenge, cardstatus.defenseup, 
                    cardstatus.poison, cardstatus.blind, cardstatus.silence, cardstatus.blockcard};
    string statusname[] = {"area", "remove",
                        "counteratk", "haste", "atk", 
                        "magic", "shield", "elixirsap", "addelixir", "drawcard", 
                        "heal", "directdmg", "niceland", 
                        "thorns", "heroic", "revenge", "defenseup", 
                        "poison", "blind", "silence", "blockcard"};
    
    // print out the name and elixir cost of the card
    cout << "name: " << cardname << endl;
    cout << "cost: " << cardcost << endl;

    // print out all status which are not equal to zero
    for (int i = 0; i < cardstatus.numberofstatus; i++) {
        if (status[i] != 0) {
            if (i == 0 || i == 1) {
                cout << statusname[i] << ' ';
            } 
            else {
                if (i == 4 || (i == 10 || (i == 11 || i == 17))) {
                    cout << "- " << status[i] << "% " << statusname[i] << endl;
                } 
                else {
                    cout << "- " << statusname[i] << " x " << status[i] << endl;
                }
            }
        }
    }
}