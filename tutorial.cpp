/*
I created main() to test the code inside here
*/

#include <iostream>
#include <fstream>
#include "movement.h"
#include "tutorial.h"
using namespace std;

void tutorial(string currentBlock, string currentCharacter){
    ifstream fin("map1.txt");   // created another text file to store so that the original map is not altered
    ofstream fout("out.txt");  
    string line;
    while(getline(fin,line)){
        fout << line << endl;
    }
    fin.close();
    fout.close();

    string newBlock = "out.txt";
    int coordinate[2];
    cout << "\nLet's begin the tutorial.\n" << endl;
    printMap(newBlock); 
    cout << "\nYou can move around the map by using WASD keys and press enter." << endl;
    int numberOfMove = 0, firstFlag = 0, secondFlag = 0; //numberOfMove is used to allow player to move around (WASD) 3 times 
    string move;
    while (firstFlag == 0 || numberOfMove < 3){
        cout << "Your move(s)?: ";
        getline(cin,move);
        for (int i = 0; i < move.length(); i++){
            move[i] = tolower(move[i]);
            switch(move[i]){
                case 'w': case 'a': case 's': case 'd':
                    movement(move[i],newBlock,currentCharacter);
                    numberOfMove++;
                    firstFlag=1;
                    break;
                default:
                    cout << "\x1B[31m" << "\nPlease enter WASD keys to move around.\n" << "\x1B[0m";
            }
        }
        cout << endl;
        printMap(newBlock);
        cout << endl;
    }
    cout << "\nGood job! Now, can you see those alphabets on the map? You can fast forward your movement by typing those shortcut characters in. Try it out!\n";
    while(secondFlag < 2){
        secondFlag = 0;
        cout << "Your move(s)?: ";
        getline(cin, move);
        cout << move;
        for (int i = 0; i < move.length() && secondFlag==0; i++){
            move[i] = tolower(move[i]);
            switch(move[i]){
                case 'c': case 'z': case 'x': case 'b': case 'v':
                    movement(move[i],newBlock,currentCharacter);
                    secondFlag = 2;
                    break;
                default:
                    cout << "\x1B[31m" << "\nTry entering the alphabets shown on the map to fast forward your movement." << "\x1B[0m" << endl;
                    secondFlag = 1;
            }

        }
        cout << endl;
        printMap(newBlock);
        cout << endl;
    }
    cout << "\nWell done! You can now move back to the previous spot by entering the same alphabet again. Press " << move[0] << " to go back!\n";
    string secondMove;
    cout << "Your move(s)?: ";
    getline(cin, secondMove);
    while (toupper(secondMove[0]) != toupper(move[0])){
        cout << "\x1B[31m" << "\nPress " << toupper(move[-1]) << " to go back!" << "\x1B[0m" << endl;
        cout << "Your move(s)?: ";
        getline(cin, secondMove);
    }
    movement(move[0],newBlock,currentCharacter);
    printMap(newBlock);
    cout << "\nGreat! Now, try moving around and explore the map. Remember, avoid hitting the wall!\n";
    int thirdFlag = 0;
    while(thirdFlag<2){
        thirdFlag = 0;
        cout << endl;
        printMap(newBlock);
        cout << endl;
        cout << "\nPress WASD keys or alphabets shown in the map to move.\nPress Q to quit tutorial." << endl;
        cout << "Your move(s)?: ";
        getline(cin, move);
        for (int i = 0; i < move.length(); i++){
            move[i] = tolower(move[i]);
            switch(move[i]){
                case 'w': case 'a': case 's': case 'd': case 'c': case 'z': case 'x': case 'b': case 'v':
                    movement(move[i],newBlock,currentCharacter);
                    break;
                case 'q':
                    thirdFlag = 2;
                    cout << "\nQuitting tutorial..." << endl;
                    break;
                default:
                    cout << "\x1B[31m" << "\nPress WASD keys or alphabets shown in the map to move." << "\x1B[0m" << endl;
                    thirdFlag=1;
            }
            getCoordinate(newBlock,']',coordinate);
            if (coordinate[0]==3&&coordinate[1]==55){  //any coordinate, first enemy pops up
                cout << "\nOMG! What's that? Seems like you have encountered your first opponent! Move nearer to your opponent to head to the battlefield.\n";
            }
            if (coordinate[0]==3&&coordinate[1]==59){  //coordinates to go to battlefield
                cout << "\x1B[7m" << "\nHeading to battlefield...\n"  << "\x1B[0m" ;
                thirdFlag = 3;
                break;
                //battleTutorial();
            }
            if (thirdFlag!=0) {break;}
        }
        cout << endl;
    }
}

void battleTutorial(){
    //to be done
}


int main(){
    string currentCharacter = "[o.o]";   // currentCharacter can be changed depending on the player's current character
    string currentBlock = "map1.txt";
    tutorial(currentBlock, currentCharacter);
    //battleTutorial();
}