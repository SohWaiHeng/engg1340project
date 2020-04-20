#include<iostream>
#include "creature.h"
using namespace std;

// just to test if my code works well (if it store all necessary info in card and creature classes)
int main () {
    // creates a new creature
    creature newcreature;

    // the creature to be set is the 1st creature listed in creature.txt. So put in argument "1"
    newcreature.setbasestats(1);

    // the creature is already level 5, set the current stats based on the level
    newcreature.setcurrentstats(5);

    // print out to see if everything's correct
    cout << newcreature.getcreaturenumber() << endl;
    newcreature.getcurrentstats();
    return 0;
}