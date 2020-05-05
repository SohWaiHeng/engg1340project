#include <iostream>
#include <fstream>
#include <string>
#include <limits>

#include "titleScreen.h"
#include "menu.h"
#include "movement.h"
#include "structs.h"

using namespace std;

void printTitleScreen(){
    ifstream fin("titleScreen.txt");
    string line;
    while (getline(fin,line)){
        cout << line << endl;
    }
    fin.close();
}

void titleScreen(std::string *file, int *currency, int currentCoordinate[2], std::string *currentMap, std::string *currentAvatar, std::string creaturesDeck[5], creatures ownedCreature[100], creatures notOwnedCreature[100], avatars ownedAvatar[50], avatars notOwnedAvatar[50]){
    printTitleScreen();
    int option;
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
    if (option == 1){
	newGame(file, currency, currentCoordinate, currentMap, currentAvatar, creaturesDeck);
        //tutorial();
    }
    else if (option == 2){
	loadFileOption(file, currency, currentCoordinate, currentMap, currentAvatar, creaturesDeck, ownedCreature, notOwnedCreature, ownedAvatar, notOwnedAvatar);
    }
    loadAvatarsFromSavedTextFile(ownedAvatar, notOwnedAvatar);
    loadCreaturesFromSavedTextFile(ownedCreature, notOwnedCreature);
}

int main(){
    creatures ownedCreature[100], notOwnedCreature[100];
    avatars ownedAvatar[50], notOwnedAvatar[50];
    int currency, currentCoordinate[2];
    string currentFile = "", currentMap, currentAvatar, creaturesDeck[5];
   // moveAroundMap(&currency, &currentAvatar, creaturesDeck, &currentFile, ownedCreature, ownedAvatar, notOwnedCreature, notOwnedAvatar, currentCoordinate, &currentMap);
    titleScreen(&currentFile,&currency,currentCoordinate,&currentMap,&currentAvatar,creaturesDeck,ownedCreature,notOwnedCreature,ownedAvatar,notOwnedAvatar);
//    moveAroundMap(&currency, &currentAvatar, creaturesDeck, &currentFile, ownedCreature, ownedAvatar, notOwnedCreature, notOwnedAvatar, currentCoordinate, &currentMap);
    mainMenuPage(&currency, &currentAvatar, creaturesDeck, &currentFile, ownedCreature, ownedAvatar, notOwnedCreature, notOwnedAvatar, currentCoordinate, &currentMap);
}
