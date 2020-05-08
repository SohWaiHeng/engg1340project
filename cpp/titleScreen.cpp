#include <iostream>
#include <fstream>
#include <string>
#include <limits>

#include "../hfiles/titleScreen.h"
#include "../hfiles/menu.h"

using namespace std;

// to print out title screen from txt file at the start of the game
void printTitleScreen(){
    ifstream fin("txt/titleScreen.txt");
    string line;
    while (getline(fin,line)){
        cout << line << endl;
    }
    fin.close();
}

// for player to choose either starting a new game or load previous progress
// return either a new game or a previously saved progress
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