#include<iostream>
#include<fstream>
#include<sstream>
#include<stdlib.h>
#include<time.h>

#include "creature.h"

using namespace std;

// increase: by how much a stat increase for each level (eg: hp increase by 0.05 for every level up)
const double increase = 0.05;

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

    // initialise the 'deployed' value as false
    deployed = false;

    // intialise all status as 0
    setstatus("all", 0);
}

// calculates and sets the creature's current status based on its level
// take in creature's level from save.txt file (or the name of the save file input by player)
void creature::setcurrentstats (int creaturelvl) {
    current = base;

    // set creature's level
    current.lvl = creaturelvl;

    // set creature's stats based on its level
    // the creature's cards and crt will not change with level
    current.hp = base.hp + ((base.hp * increase) * (creaturelvl-1));
    current.atk = base.atk + ((base.atk * increase) * (creaturelvl-1));
    current.mgc = base.mgc + ((base.mgc * increase) * (creaturelvl-1));
}

// prints out all current stats and cards of a creature
// I'm considering if I should split this into getname(), gethp(), getatk() etc.
void creature::getcurrentstats () {
    cout << endl;
    cout << current.symbol << endl;
    cout << "name: " << current.name << endl;
    cout << "level: " << current.lvl << endl;
    cout << "cost: " << current.cost << endl;
    cout << "hp: " << current.hp << endl;
    cout << "atk: " << current.atk << endl;
    cout << "mgc: " << current.mgc << endl;
    cout << "crt: " << current.crt << " %" << endl;
    /*for (int i = 0; i < 5; i++) {
        cout << endl << "card " << i+1 << endl;
        cardpool[i].getfunction();
    }*/
}

int creature::getatk(bool &critical) {
    srand(time(NULL));
    int randomno = rand() % 100 + 1;
    if (randomno < current.crt) {
        critical = true;
        return (current.atk * 1.5);
    }
    else {
        critical = false;
        return current.atk;
    }
}

int creature::getmgc(bool &critical) {
    srand(time(NULL));
    int randomno = rand() % 100 + 1;
    if (randomno < current.crt) {
        critical = true;
        return (current.mgc * 1.5);
    }
    else {
        critical = false;
        return current.mgc;
    }
}

int creature::gethpratio () {
    double currenthp = current.hp;
    double basehp = base.hp;
    double ratio = ((currenthp / (basehp+0.01)) * 5) + 1;
    return ratio;
}

void creature::setstatus(string condition, int number) {
    int * status[] = {&creaturestatus.area, &creaturestatus.remove, &creaturestatus.own, &creaturestatus.enemy, &creaturestatus.card,
                    &creaturestatus.counteratk, &creaturestatus.haste, &creaturestatus.atk,
                    &creaturestatus.magic, &creaturestatus.shield, &creaturestatus.elixirsap, &creaturestatus.addelixir, &creaturestatus.drawcard,
                    &creaturestatus.heal, &creaturestatus.directdmg, &creaturestatus.niceland,  
                    &creaturestatus.thorns, &creaturestatus.heroic, &creaturestatus.revenge, &creaturestatus.defenseup, 
                    &creaturestatus.poison, &creaturestatus.blind, &creaturestatus.silence, &creaturestatus.blockcard};
    string statusname[] = {"area", "remove", "own", "enemy", "card",
                        "counteratk", "haste", "atk", 
                        "magic", "shield", "elixirsap", "addelixir", "drawcard", 
                        "heal", "directdmg", "niceland", 
                        "thorns", "heroic", "revenge", "defenseup", 
                        "poison", "blind", "silence", "blockcard"};
    if (condition == "all") {
        if (number == 0) {
            for (int i = 0; i < creaturestatus.numberofstatus; i++) {
                *status[i] = number;
            }
        }
        else {
            for (int i = 0; i < creaturestatus.numberofstatus; i++) {
                *status[i] += number;
            }
        }
    }
    else {
        for (int i = 0; i < creaturestatus.numberofstatus; i++) {
            if (statusname[i] == condition) {
                if (number == 0) {
                    *status[i] = 0;
                }
                else {
                    *status[i] += number;
                    i = creaturestatus.numberofstatus;
                }
            }
        }
    }
}

int creature::getstatus (string condition) {
    int status[] = {creaturestatus.area, creaturestatus.remove, creaturestatus.own, creaturestatus.enemy, creaturestatus.card,
                    creaturestatus.counteratk, creaturestatus.haste, creaturestatus.atk,
                    creaturestatus.magic, creaturestatus.shield, creaturestatus.elixirsap, creaturestatus.addelixir, creaturestatus.drawcard,
                    creaturestatus.heal, creaturestatus.directdmg, creaturestatus.niceland,  
                    creaturestatus.thorns, creaturestatus.heroic, creaturestatus.revenge, creaturestatus.defenseup, 
                    creaturestatus.poison, creaturestatus.blind, creaturestatus.silence, creaturestatus.blockcard};
    string statusname[] = {"area", "remove", "own", "enemy", "card",
                        "counteratk", "haste", "atk", 
                        "magic", "shield", "elixirsap", "addelixir", "drawcard", 
                        "heal", "directdmg", "niceland", 
                        "thorns", "heroic", "revenge", "defenseup", 
                        "poison", "blind", "silence", "blockcard"};
    
    for (int i = 0; i < creaturestatus.numberofstatus; i++) {
        if (statusname[i] == condition) {
            return status[i];
        }
    }
    return 0;
}

void creature::decreasehp(int byhowmuch) { 
    creature trash;
    revenge(byhowmuch, false, trash);
    if (creaturestatus.shield > 0) {
        shield();
    }
    else {
        defenseup(byhowmuch);
        current.hp = current.hp - byhowmuch;
    }
}

void creature::heal (int percentage) {
    current.hp = current.hp + (base.hp + ((base.hp * increase) * current.lvl)) * (percentage / 100.0);
    if (current.hp > (base.hp + ((base.hp * increase) * current.lvl))) {
        current.hp = base.hp + ((base.hp * increase) * current.lvl);
    }
    cout << getname() << " healed " << percentage << "% hp." << endl;
}

void creature::counteratk (creature &attacker) {
    if (creaturestatus.counteratk > 0) {
        bool critical = false;
        int damage = getatk(critical);
        attacker.decreasehp(damage);
        cout << getname() << " counterattacks " << attacker.getname() << " !" << endl;
        if (critical == true) {
            cout << "CRITICAL ATTACK !!!" << endl;
        }
        if (getstatus("atk") != 0) {
            atk(0);
        }
        cout << attacker.getname() << " damaged by " << getname() << damage << " hp." << endl;
        thorns(damage, attacker);
        creaturestatus.counteratk--;
    }
}

void creature::haste (bool start) {
    if (creaturestatus.haste > 0) {
        if (start) {
            creaturestatus.haste--;
        } 
        if (creaturestatus.haste > 0) {
            current.cost = base.cost - 1;
        }
        else {
            current.cost = base.cost;
        }
    }
}

void creature::atk (int percentage) {
    if ((getstatus("atk") > 0 && percentage < 0) || (getstatus("atk") < 0 && percentage > 0)) {
        setstatus("atk", -getstatus("atk") + percentage);
    }
    else {
        setstatus("atk", percentage);
    }

    if (percentage != 0) {
        current.atk = current.atk + (base.atk + ((base.atk * increase) * current.lvl)) * (percentage/100.0);
    }
    else {
        current.atk = base.atk + ((base.atk * increase) * current.lvl);
    }
}


void creature::magic(creature &target) {
    bool critical = false;
    target.decreasehp(getmgc(critical));
    cout << getname() << " used magic attack on " << target.getname() << "!" << endl;
    if (critical == true) {
        cout << "CRITICAL ATTACK !!!" << endl;
    }
}

void creature::shield() {
    cout << getname() << " used a shield." << endl;
    creaturestatus.shield--;
}

void creature::elixirsap(creature &target, int &elixir, bool attacking) {
    if (creaturestatus.elixirsap == 0) {
        return;
    }
    else if (creaturestatus.elixirsap > 0 && attacking) {
        elixir = elixir + creaturestatus.elixirsap;
        target.setstatus("elixirsap", 0);
        cout << creaturestatus.elixirsap << " elixir sapped from opponent." << endl;
        setstatus("elixirsap", -creaturestatus.elixirsap);
    }
    else if (creaturestatus.elixirsap < 0) {
        elixir = elixir + creaturestatus.elixirsap;
        setstatus("elixirsap", 0);
    }
}

void creature::addelixir(int &elixir, int byHowMuch) {
    elixir = elixir + byHowMuch;
    cout << "Added " << byHowMuch << " elixir." << endl;
}

void creature::directdmg (int percentage) {
    int byHowMuch = (base.hp + ((base.hp * increase) * current.lvl)) * (percentage/100.0);
    cout << getname() << " damaged by " << percentage << "%" << endl;
    decreasehp(byHowMuch);
}

void creature::thorns (int damage, creature target) {
    if (target.getstatus("thorns") != 0) {
        cout << "Damage reflected from " << target.getname() << "!!" << endl;
        decreasehp(damage);
    }
}

void creature::revenge (int store, bool release, creature &target) {
    if (getstatus("revenge") != 0) {    
        if (release) {
            int damage = getstatus("revenge") - 1;
            cout << "Revenge attack onto " << target.getname() << "!!" << endl;
            target.decreasehp(damage);
            atk(0);
            setstatus("revenge", 0);
            thorns(damage, target);
        }
        else {
            setstatus("revenge", store);
        }
    }
}

void creature::defenseup(int &damage) {
    if (creaturestatus.defenseup > 0) {    
        damage = damage * (0.7);
        cout << "damage onto " << getname() << "reduced by 30%" << endl;
    }
}

void creature::poison() {
    if (creaturestatus.poison != 0) {
        int byHowMuch = (base.hp + ((base.hp * increase) * current.lvl)) * (creaturestatus.poison/100.0);
        cout << getname() << " poisoned by " << creaturestatus.poison << "%" << endl;
        decreasehp(byHowMuch);
    }
}