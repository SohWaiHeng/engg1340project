#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "../hfiles/titleScreen.h"
#include "../hfiles/menu.h"

using namespace std;

void printTitleScreen(){
    ifstream fin("txt/titleScreen.txt");
    string line;
    while (getline(fin,line)){
        cout << line << endl;
    }
    fin.close();
}

string titleScreen(int &option){
    printTitleScreen();
    cout << "Please Enter a Number: ";
    cin >> option;
    while (option != 1 && option != 2){
        // solve the issue of incorrect datatype entered
        if(cin.fail()){ 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
        }
        cout << "Please Enter 1 or 2: ";
            cin >> option;
    }
    string filename;
    // start a new game
    if (option == 1){
        filename = newGame();
    }
    // load an existing game
    else if (option == 2) {
	    filename = loadFileOption(option);
    }
    return filename;
}

/*int main(){
    creatures ownedCreature[100], notOwnedCreature[100];
    avatars ownedAvatar[50], notOwnedAvatar[50];
    int currency, currentCoordinate[2];
    string currentFile = "", currentMap, currentAvatar, creaturesDeck[5];
   // moveAroundMap(&currency, &currentAvatar, creaturesDeck, &currentFile, ownedCreature, ownedAvatar, notOwnedCreature, notOwnedAvatar, currentCoordinate, &currentMap);
    titleScreen();
//    moveAroundMap(&currency, &currentAvatar, creaturesDeck, &currentFile, ownedCreature, ownedAvatar, notOwnedCreature, notOwnedAvatar, currentCoordinate, &currentMap);
    mainMenuPage(&currency, &currentAvatar, creaturesDeck, &currentFile, ownedCreature, ownedAvatar, notOwnedCreature, notOwnedAvatar, currentCoordinate, &currentMap);
}*/
