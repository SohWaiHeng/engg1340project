#include<iostream>
#include<fstream>
#include<sstream>
#include "creature.h"
using namespace std;

// set base stats of a creature
// take in the index no. of the creature concerned
void creature::setbasestats (int creatureno) {
    // input from creature.txt
    // creature.txt saves all available creatures in the game
    ifstream fin;
    fin.open("classes/txt/creature.txt");
    if (fin.fail()) {
        cout << "fail to load creature's base stats" << endl;
    }

    int line = -1;
    string fullstats;
    // iterate line by line until found the creature in creature.txt
    while (creatureno > line) {
        getline(fin, fullstats);
        line++;
        // store the creature's line in a string
        if (creatureno == line) {
            int integer;
            string name;
            istringstream iss(fullstats);
            
            // take in creature's index no.
            iss >> integer;
            creaturenumber = integer;

            // take in creature's name
            iss >> integer;
            base.name = "";
            for (int i = 0; i < integer; i++) {
                iss >> name;
                if (base.name != "") {
                    base.name = base.name + " " + name;
                }
                else {
                    base.name += name;
                }
            }

            // take in creature's symbol
            iss >> name;
            base.symbol = name;

            for (int i = 0; i < 5; i++) {
                iss >> integer;
                card newcard;
                newcard.setcard(integer);
                cardpool[i] = newcard;
            }

            // since this is base stats, set creature's level to 1
            base.lvl = 1;
            
            // take in the creature's hp, cost, atk, mgc and crt
            int count = 0;
            int * stats[] = {&base.hp, &base.cost, &base.atk, &base.mgc, &base.crt};
            while (iss >> integer) {
                (*stats[count]) = integer;
                count ++;
            }
        }
    }
    // and thus a creature is stored
    fin.close();
}

// calculates and sets the creature's current status based on its level
// take in creature's level from save.txt file (or the name of the save file input by player)
void creature::setcurrentstats (int creaturelvl) {
    current = base;

    // increase: by how much a stat increase for each level (eg: hp increase by 0.05 for every level up)
    const double increase = 0.05;

    // set creature's level
    current.lvl = creaturelvl;

    // set creature's stats based on its level
    // the creature's cards and crt will not change with level
    current.hp = base.hp + ((base.hp * increase) * creaturelvl);
    current.atk = base.atk + ((base.atk * increase) * creaturelvl);
    current.mgc = base.mgc + ((base.mgc * increase) * creaturelvl);
}

// prints out all current stats and cards of a creature
// I'm considering if I should split this into getname(), gethp(), getatk() etc.
void creature::getcurrentstats () {
    cout << current.symbol << endl;
    cout << "name: " << current.name << endl;
    cout << "cost: " << current.cost << endl;
    cout << "hp: " << current.hp << endl;
    cout << "atk: " << current.atk << endl;
    cout << "mgc: " << current.mgc << endl;
    cout << "crt: " << current.crt << " %" << endl;
    for (int i = 0; i < 5; i++) {
        cout << endl << "card " << i+1 << endl;
        cardpool[i].getfunction();
    }
}
