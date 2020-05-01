
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "../hfiles/titleScreen.h"
using namespace std;

void printTitleScreen(){
    ifstream fin("txt/titleScreen.txt");
    string line;
    while (getline(fin,line)){
        cout << line << endl;
    }
    fin.close();
}

void titleScreen(){
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
        cout << "STARTING A NEW GAME...";
        //tutorial();
        //newGame();
    }
    if (option == 2){
        cout << "LOADING GAME...";
        //loadGame();
    }
}


