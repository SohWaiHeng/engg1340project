/*
I created main() to test the code inside here
*/

#include <iostream>
#include <string>
#include <fstream>
#include "movement.h"
#include "tutorial.h"
#include "titleScreen.h"
#include "structs.h"
using namespace std;

//mapWithAvatar(string *currentAvatar, int currentCoordinate[2], string *currentBlock, string *newBlock)

void tutorial(int *currency, string *currentAvatar, string creaturesDeck[5] ,string *currentFile, creatures ownedCreature[100], avatars ownedAvatar[50], creatures notOwnedCreature[100], avatars notOwnedAvatar[50], int currentCoordinate[2], string *currentBlock, string *newBlock, string *avatarSymbol, int *moveFlag){
   // newFileForMap(currentBlock,&newBlock);
    cout << "\nLet's begin the tutorial.\n\n";
    mapWithAvatar(currentAvatar, avatarSymbol, ownedAvatar, currentCoordinate, currentBlock, newBlock);
    printMap(newBlock);
    cout << "\nYou can move around the map by using WASD keys and press enter.\n";
    int numberOfMove = 0, flag = 0; //numberOfMove is used to allow player to move around (WASD) 3 times 
    string move;
    while (numberOfMove < 5){
        cout << "Your move(s)?: ";
        cin >> move;
        flag = 0;
	for (int i = 0; i < move.length() && flag==0; i++){
            move[i] = tolower(move[i]);
            switch(move[i]){
                case 'w': case 'a': case 's': case 'd':
                    movement(move[i],newBlock,avatarSymbol,moveFlag);
                    numberOfMove++;
                    break;
                default:
                    cout << "\x1B[31m" << "\nPlease enter WASD keys to move around.\n" << "\x1B[0m";
            	    flag = 1;
	    }
        }
        getCoordinate(newBlock,(*avatarSymbol)[0],currentCoordinate);
	mapWithAvatar(currentAvatar, avatarSymbol, ownedAvatar, currentCoordinate, currentBlock, newBlock);
    	printMap(newBlock);
    }
    flag = 0;
    cout << "\nGood job! Now, can you see those alphabets on the map? You can fast forward your movement by typing those shortcut characters in. Try it out!\n";
    while(flag < 2){
    	flag = 0;
        cout << "Your move(s)?: ";
        cin >> move;
        for (int i = 0; i < move.length() && flag==0; i++){
            move[i] = tolower(move[i]);
            switch(move[i]){
                case 'c': case 'z': case 'x': case 'b': case 'v':
                    movement(move[i],newBlock,avatarSymbol,moveFlag);
                    flag = 2;
                    break;
                default:
                    cout << "\x1B[31m" << "\nTry entering the alphabets shown on the map to fast forward your movement." << "\x1B[0m" << endl;
                    flag = 1;
            }

        }
	getCoordinate(newBlock,(*avatarSymbol)[0],currentCoordinate);
        mapWithAvatar(currentAvatar, avatarSymbol, ownedAvatar, currentCoordinate, currentBlock, newBlock);
    	printMap(newBlock);
    }
    flag = 0;
    cout << "\nGreat! You can save yourself a lot of time but using these fast forward keys to move around!\n";
    cout << "Now, try moving around and explore the map. Remember, avoid hitting the wall!\n";
    numberOfMove = 0;
    string prev = "m";
    while(flag<2 && numberOfMove < 15){
        flag = 0;
        cout << "\nPress WASD keys or alphabets shown in the map to move.\nPress Q to quit tutorial." << endl;
        cout << "Your move(s)?: ";
        cin >> move;
        for (int i = 0; i < move.length() && flag < 1; i++){
            move[i] = tolower(move[i]);
            switch(move[i]){
                case 'w': case 'a': case 's': case 'd': case 'c': case 'z': case 'x': case 'b': case 'v':
		    if (prev==string()+move[i]&&(move[i]=='z'||move[i]=='x'||move[i]=='c'||move[i]=='b'||move[i]=='v')){   
		    	break;
		    }
		    movement(move[i],newBlock,avatarSymbol,moveFlag);
                    numberOfMove++;
		    if (numberOfMove > 10 && flag!=-1){
		    	cout << "\nIn this game, you may encounter your enemy anytime and anywhere. Remember to stay alert all the time!!\n";
		    	flag = -1;
		    
		    }
		    prev = string()+move[i];
		    break;
                case 'q':
                    flag = 2;
                    cout << "\nQuitting tutorial..." << endl;
                    moveAroundMap(currency, currentAvatar, creaturesDeck, currentFile, ownedCreature, ownedAvatar, notOwnedCreature, notOwnedAvatar, currentCoordinate, currentBlock, newBlock, avatarSymbol);
		    break;
                default:
                    cout << "\x1B[31m" << "\nPress WASD keys or alphabets shown in the map to move." << "\x1B[0m" << endl;
                    flag=1;
            }
	}
	getCoordinate(newBlock,(*avatarSymbol)[0],currentCoordinate);
        mapWithAvatar(currentAvatar, avatarSymbol, ownedAvatar, currentCoordinate, currentBlock, newBlock);
    	printMap(newBlock);
    }
    cout << "Oh uh. Seems like you have encountered your first enemy here. Let's us head to the battlefield to start the battle!\n";
} 
