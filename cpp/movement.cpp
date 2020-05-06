/*
This is the codes I written to allow the avatar to move in the map
I thought of a few ways but decided to go with this one (er not sure whether it is the most efficient one though)
The part after "switch(move)" can be shorten I guess, but I think I will leave it till the last part if we still have time
I have assumed our avatar has width of 5 pixels and the alphabets used at junctions are Z,X,C,V,B only (these 2 criterias can be changed)
I have assumed the wall on the map is represented by '-' and '|'
*/

#include <iostream>
#include <fstream>
#include "../hfiles/colours.h"
#include "../hfiles/movement.h"
using namespace std;

// to print map
void printMap(string map){
    string line;
    ifstream fin(map);
    while (getline(fin,line)){
        cout << line << endl;
    }
}

// to see whether there's an alphabet on position avatar is heading to
bool checkForAlphabet(string nextPosition){
    if (nextPosition.find('Z')==-1 && nextPosition.find('X')==-1 && nextPosition.find('C')==-1 && nextPosition.find('V')==-1 && nextPosition.find('B')==-1 && nextPosition.find('N')==-1 && nextPosition.find('M')==-1)
        return false;
    else {return true;}
}

// to see if there's a wall on position avatar is heading to
bool checkForWall(string nextPosition){
    if (nextPosition.find('|')==-1 && nextPosition.find('-')==-1)
        return false;
    else {return true;}
}

// to change position of avatar
void changePositions(string blockArray[], int currentPositionX, int currentPositionY, int nextPositionX, int nextPositionY, string currentCharacter, string toReplaceOri, string toReplaceNew){
    blockArray[currentPositionX].replace(currentPositionY, toReplaceOri.length(),toReplaceOri);
    blockArray[nextPositionX].replace(nextPositionY, toReplaceNew.length(),toReplaceNew);
}

// to get coordinate of any given alphabet/character
void getCoordinate(string currentBlock, char input, int coordinate[2]){
    string line;
    int lineCount;
    ifstream fin(currentBlock);
    while(getline(fin, line)){
        for (int i = 0; i < line.length(); i++){
            if (line[i] == input){
                coordinate[0]=lineCount;
                coordinate[1]=i;
            }
        }
        lineCount++;
    }
}


// to move around
void movement(char move, string currentBlock, string currentCharacter){
    string line;
    int lineCount = 0;
    string * blockArray = new string [25];  //dynamic array to store lines in map
    ifstream fin(currentBlock); 
    while (getline(fin,line)){
        blockArray[lineCount] = line;
        lineCount++;
    }

    int flag = 0, positionX = -1, positionY = -1;  //positionX and positionY are used to save the row and column of the move character
    for (int i = 0; i < lineCount; i++){
        for (int j = 0; j < (blockArray[i].length()-currentCharacter.length()); j++){
            if (blockArray[i][j]==toupper(move)) {positionX=i; positionY=j-2;}  //to save coordinates of alphabet(the one on the junctions), for cases which the avatar is not yet encountered in this loop
            if (blockArray[i].substr(j,currentCharacter.length())==currentCharacter){    
                switch (move){ 
                    case 'w':
                        if (checkForAlphabet(blockArray[i-1].substr(j,currentCharacter.length()))==true){  // swap the positions of avatar and alphabet when an alphabet is encountered
                            changePositions(blockArray, i, j, i-1, j, currentCharacter, blockArray[i-1].substr(j,currentCharacter.length()), currentCharacter);
                            flag = 1;
                        }
                        else if (checkForWall(blockArray[i-1].substr(j,currentCharacter.length()))==true) {  // send warning to player when wall is encountered
                            cout << "\x1B[31m" << "\nYou've hit the wall. Be careful!" << "\x1B[0m" << endl;
                        }
                        else {  
                            changePositions(blockArray, i, j, i-1, j, currentCharacter, "     ", currentCharacter);
                            flag = 1;
                        }
                        break;
                    case 'a':
                        if (checkForAlphabet(blockArray[i].substr(j-1,1))==true){
                            string alphabet = blockArray[i].substr(j-1,1);
                            changePositions(blockArray, i, j+4, i, j-1, string()+move, alphabet, currentCharacter);
                            flag = 1;
                        }
                        else if (checkForWall(blockArray[i].substr(j-1,currentCharacter.length()))==true) {
                            cout << RED << "\nYou've hit the wall. Be careful!" << WHITE << endl;
                        }
                        else if (checkForWall(blockArray[i].substr(j-1,currentCharacter.length()))==false){
                            changePositions(blockArray, i, j, i, j-1, currentCharacter, "     ", currentCharacter);
                            flag = 1;
                        }
                        break;
                    case 's':
                        if (checkForAlphabet(blockArray[i+1].substr(j,currentCharacter.length()))==true){
                            changePositions(blockArray, i, j, i+1, j, currentCharacter, blockArray[i+1].substr(j,currentCharacter.length()), currentCharacter);
                            flag = 1;
                        }
                        else if (checkForWall(blockArray[i+1].substr(j,currentCharacter.length()))==true) {
                            cout << "\x1B[31m" << "\nYou've hit the wall. Be careful!" << "\x1B[0m" << endl;
                        }
                        else if (checkForWall(blockArray[i+1].substr(j,currentCharacter.length()))==false){
                            changePositions(blockArray, i, j, i+1, j, currentCharacter, "     ", currentCharacter);
                            flag = 1;
                        }
                        break;
                    case 'd':
                        if (checkForAlphabet(blockArray[i].substr(j+5,1))==true){
                            string alphabet = blockArray[i].substr(j+5,1);
                            changePositions(blockArray, i, j, i, j+1, currentCharacter, alphabet, currentCharacter);
                            flag = 1;
                        }
                        else if (checkForWall(blockArray[i].substr(j+1,currentCharacter.length()))==true) {
                            cout << "\x1B[31m" << "\nYou've hit the wall. Be careful!" << "\x1B[0m" << endl;
                        }
                        else if (checkForWall(blockArray[i].substr(j+1,currentCharacter.length()))==false){
                            changePositions(blockArray, i, j, i, j+1, currentCharacter, "     ", currentCharacter);
                            flag = 1;
                        }
                        break;
                    default:    // for alphabets on junctions
                        move = toupper(move);
                        string add = string ()+"  "+move+"  ";
                        if (positionX == -1) {  // to continue finding the alphabet if it is not yet encountered
                            for (int k = i; k < lineCount && flag==0; k++){
                                for (int l = 0; l < (blockArray[k].length()-currentCharacter.length()); l++){
                                    if (blockArray[k][l]==move) { 
                                        positionX=k; positionY=l-2;
                                        flag = 1;
                                        break;
                                    }
                                }
                            }
                        }
                        changePositions(blockArray,i,j,positionX,positionY,currentCharacter,add,currentCharacter);
                }
            }
            if (flag == 1){break;}
        }
        if (flag == 1){break;}
    }

    fin.close();
    ofstream fout(currentBlock);
    for (int i = 0; i < lineCount-1; i++){
        fout << blockArray[i] << endl;
    }
    fout << blockArray[lineCount-1];
    fout.close();

    delete[] blockArray;
}
