#include <iostream>
#include <fstream>
#include <limits>
#include <string>

#include "../hfiles/movement.h"
#include "../hfiles/colours.h"

using namespace std;

// to print map
void printMap(string map){
    string line;
    ifstream fin(map);
    cout << endl;
    while (getline(fin,line)){
        cout << line << endl;
    }
    cout << endl;
    fin.close();
}

// to print map together with avatar

void mapWithAvatarAndEnemy(string avatarSymbol, string enemySymbol, int avatarCoordinate[2], int enemyCoordinate[2], string currentBlock, string newBlock){
    int lineCount=0, flag=0;
    string line, newLine, newLine2;
    ifstream fin(currentBlock);
    ofstream fout(newBlock);
    while (getline(fin,line)){
        if (lineCount == avatarCoordinate[0] && lineCount == enemyCoordinate[0]){
	    newLine = line.replace(avatarCoordinate[1],5,avatarSymbol);
	    newLine2 = newLine.replace(enemyCoordinate[1],5,enemySymbol);
	    fout << newLine2 << endl;
	}
	else if (lineCount == avatarCoordinate[0]){
            newLine = line.replace(avatarCoordinate[1],5,avatarSymbol);
	    fout << newLine << endl;
        }
	else if (lineCount == enemyCoordinate[0]){
            newLine = line.replace(enemyCoordinate[1],5,enemySymbol);
            fout << newLine << endl;
        }
	else {fout << line << endl;}
	lineCount++;
    }
    fin.close();
    fout.close();
}

void getRandomCoordinateForEnemy(string currentBlock, int enemyCoordinate[2], int avatarCoordinate[2]){
    int i = 0;
    string * arr = new string [25];
    string line;
    ifstream fin(currentBlock);
    while(getline(fin, line)){
        arr[i] = line;
        cout << line << endl;
        i++;
    }
    while (true){
        srand(time(NULL));
        int randomRow = rand() % 19 + 3;  //range 3 - 21
        int randomColumn = rand() % 44 + 8;  //range 8 - 52
	//continue if avatar is on that coordinate
	if (randomRow == avatarCoordinate[0] && (randomColumn >= avatarCoordinate[1] && randomColumn <= avatarCoordinate[1]+4)){
	    continue;
	}
	// continue if coordinates in final boss dungeon
	if (currentBlock == "txt/map4.txt" && ((randomRow>=4 && randomRow<=12) && (randomColumn>=5 && randomColumn<=28))){
	    continue;
	}
	for (int i = randomRow; i < 22; i++){
            for (int j = randomColumn; j < 53; j++){
                if (arr[i].substr(j,5)== "     "){
                    enemyCoordinate[0] = i;
                    enemyCoordinate[1] = j;
                    cout << enemyCoordinate[0] << ' ' << enemyCoordinate[1];
                    delete [] arr;
                    return;
                 }
             }
         }
     }
 }

// to check if change of map block is needed
bool checkForMapChange(string &currentBlock, int currentCoordinate[2], int &blockNum){
    int fileArray[6][14][3] = {
    			         {{3,64,2}},
			         {{3,0,1},{24,5,5},{24,6,5},{24,7,5},{24,9,5},{24,10,5},{24,11,5},{24,58,5},{24,59,5},{24,62,5},{24,63,5},{11,64,3}},
				 {{11,0,2},{24,52,6},{24,53,6},{24,54,6},{24,55,6},{24,56,6},{24,57,6},{24,58,6},{24,59,6}},
				 {{12,64,5},{19,64,5}},
				 {{0,5,2},{0,6,2},{0,7,2},{0,9,2},{0,10,2},{0,11,2},{0,58,2},{0,59,2},{0,62,2},{0,63,2},{12,0,4},{19,0,4},{8,64,6},{16,64,6}},
				 {{8,0,5},{16,0,5},{0,52,3},{0,53,3},{0,54,3},{0,55,3},{0,56,3},{0,57,3},{0,58,3},{0,59,3}}
    			      };
    int moveArray[6][14][2] = {
    				{{3,5}},
				{{3,59},{1,5},{1,6},{1,7},{1,9},{1,10},{1,11},{1,58},{1,59},{1,62},{1,63},{11,5}},
				{{11,59},{1,52},{1,53},{1,54},{1,55},{1,56},{1,57},{1,58},{1,59}},
				{{12,5},{19,5}},
				{{23,5},{23,6},{23,7},{23,9},{23,10},{23,11},{23,58},{23,59},{23,62},{23,63},{12,59},{19,59},{8,5},{16,5}},
				{{8,59},{16,59},{23,52},{23,53},{23,54},{23,55},{23,56},{23,57},{23,58},{23,59}}
			      };
    int num = stoi((currentBlock).substr(7,1));
    for (int i = 0; i < 6; i++){
    	for (int j = 0; j < 14; j++){
	    if (fileArray[i][j][0] == currentCoordinate[0] && fileArray[i][j][1] == currentCoordinate[1] && i == num-1){
	    	string newBlock = "txt/map"+to_string(fileArray[i][j][2])+".txt";
		currentBlock = newBlock;
		currentCoordinate[0] = moveArray[i][j][0];
		currentCoordinate[1] = moveArray[i][j][1];
		blockNum = stoi((currentBlock).substr(7,1));
		return true;
	    }
	}
    }
    blockNum = num;
    return false;
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
    int lineCount=0;
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
void movement(char move, string &newBlock, string currentCharacter, int &moveFlag){
    string line;
    int lineCount = 0;
    string * blockArray = new string [25];  //dynamic array to store lines in map
    ifstream fin(newBlock); 
    while (getline(fin,line)){
        blockArray[lineCount] = line;
        lineCount++;
    }
    int flag = 0, positionX = -1, positionY = -1;  //positionX and positionY are used to save the row and column of the move character
    for (int i = 0; i < lineCount; i++){
        for (int j = 0; j < (blockArray[i].length()-(currentCharacter).length()); j++){
            if (blockArray[i][j]==toupper(move)) {positionX=i; positionY=j-2;}  //to save coordinates of alphabet(the one on the junctions), for cases which the avatar is not yet encountered in this loop
            if (blockArray[i].substr(j,(currentCharacter).length())==currentCharacter){    
                switch (move){ 
                    case 'w':
                        if (checkForAlphabet(blockArray[i-1].substr(j,(currentCharacter).length()))==true){  // swap the positions of avatar and alphabet when an alphabet is encountered
                            changePositions(blockArray, i, j, i-1, j, currentCharacter, blockArray[i-1].substr(j,(currentCharacter).length()), currentCharacter);
                            flag = 1;
                        }
                        else if (checkForWall(blockArray[i-1].substr(j,(currentCharacter).length()))==true) {  // send warning to player when wall is encountered
                            cout << RED << "\nYou've hit the wall. Be careful!" << WHITE << endl;
                            moveFlag = 1;
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
                        else if (checkForWall(blockArray[i].substr(j-1,(currentCharacter).length()))==true) {
                            cout << RED << "\nYou've hit the wall. Be careful!" << WHITE << endl;
                            moveFlag = 1;
			}
                        else if (checkForWall(blockArray[i].substr(j-1,(currentCharacter).length()))==false){
                            changePositions(blockArray, i, j, i, j-1, currentCharacter, "     ", currentCharacter);
                            flag = 1;
                        }
                        break;
                    case 's':
                        if (checkForAlphabet(blockArray[i+1].substr(j,(currentCharacter).length()))==true){
                            changePositions(blockArray, i, j, i+1, j, currentCharacter, blockArray[i+1].substr(j,(currentCharacter).length()), currentCharacter);
                            flag = 1;
                        }
                        else if (checkForWall(blockArray[i+1].substr(j,(currentCharacter).length()))==true) {
                            cout << RED << "\nYou've hit the wall. Be careful!" << WHITE << endl;
			    moveFlag = 1;
                        }
                        else if (checkForWall(blockArray[i+1].substr(j,(currentCharacter).length()))==false){
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
                        else if (checkForWall(blockArray[i].substr(j+1,(currentCharacter).length()))==true) {
                            cout << RED << "\nYou've hit the wall. Be careful!" << WHITE << endl;
                            flag = 1;
			    moveFlag = 1;
			}
                        else if (checkForWall(blockArray[i].substr(j+1,(currentCharacter).length()))==false){
                            changePositions(blockArray, i, j, i, j+1, currentCharacter, "     ", currentCharacter);
                            flag = 1;
                        }
                        break;
                    default:    // for alphabets on junctions
                        int flag1 = 0;
			move = toupper(move);
			string add = string ()+"  "+move+"  ";
			if (positionX == -1) {  // to continue finding the alphabet if it is not yet encountered
                            for (int k = i; k < lineCount && flag==0; k++){
                                for (int l = 0; l < (blockArray[k].length()-(currentCharacter).length()+1); l++){
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
    ofstream fout(newBlock);
    for (int i = 0; i < lineCount-1; i++){
        fout << blockArray[i] << endl;
    }
    fout << blockArray[lineCount-1];
    fout.close();

    delete[] blockArray;
}

// main function for avatar to move around the map
void moveAroundMap(int avatarCoordinate[2], int enemyCoordinate[2], string &avatarSymbol, string &enemySymbol, string &currentBlock, string &newBlock){
    string moveArray[5] = {"z","x","c","v","b"};
    string move, prevMove = "m";   
    int enemyCoordinateArray[6][2] = {{3,43},{17,26},{21,10},{19,13},{22,35},{15,48}}; //set initial enemy coordinates, after enemy is defeated its position will be randomly placed on the same block
    int moveFlag = 0;
    int flag = 0, flag1 = 0, blockNum = 1; 
    mapWithAvatarAndEnemy(avatarSymbol,enemySymbol,avatarCoordinate,enemyCoordinate,currentBlock,newBlock);
    printMap(newBlock);
    while (flag != 2){
        cout << "Press WASD or alphabets shown in the map to move around.\n";
        cout << "Press M to open up the menu page.\n";
	cout << "Your move(s): ";
        cin >> move;
	flag = 0;
        flag1 = 0;
	for (int i = 0; i < move.length() && flag == 0 && moveFlag==0; i++){
	    move[i] = tolower(move[i]);
            switch(move[i]){
                case 'w': case 'a': case 's': case 'd': case 'c': case 'z': case 'x': case 'b': case 'v':{
                    //moveFlag to avoid warning is sent multiple times at once, prevMove is to avoid error when player choosing the same shortcut character
		    if (moveFlag==1||(prevMove == string()+move[i] && (move[i]=='z'||move[i]=='x'||move[i]=='c'||move[i]=='v'||move[i]=='b'))){
			break;
		    }
		    movement(move[i],newBlock,avatarSymbol,moveFlag);
		    getCoordinate(newBlock,(avatarSymbol)[0],avatarCoordinate);
		    // to check if change of block is needed
		    if (checkForMapChange(currentBlock,avatarCoordinate,blockNum) == true){
			flag1 = 1;
		    }
		    if (flag1 == 0){
		    	avatarCoordinate[1] += 4;
		    	checkForMapChange(currentBlock,avatarCoordinate,blockNum);
		    	avatarCoordinate[1] -= 4;
			flag1 = 1;
		    }
		    if (flag1 = 1){  // get random coordinate to print enemy when player change block of map
	        	enemyCoordinate[0] = enemyCoordinateArray[blockNum-1][0];
			enemyCoordinate[1] = enemyCoordinateArray[blockNum-1][1];
		    }

		    // when player encounters enemy on map
		    char choice;
		    if ((avatarCoordinate[0] >= enemyCoordinate[0]-1 && avatarCoordinate[0] <= enemyCoordinate[0]+1) && (avatarCoordinate[1] >= enemyCoordinate[1]-5 && avatarCoordinate[1] <= enemyCoordinate[1]+5)){
		    	mapWithAvatarAndEnemy(avatarSymbol,enemySymbol,avatarCoordinate,enemyCoordinate,currentBlock,newBlock);
			printMap(newBlock);
			cout << BLUE << "Look, seems like there is an enemy near you. Do you want to fight the enemy? [y/n] \n";
			cout << "Your choice: " << WHITE;
			cin >> choice;
			while ((tolower(choice)!='y'&&tolower(choice)!='n')||cin.fail()){
			    cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(),'\n');
			    cout << RED << "Please type in \"y\" or \"n\" to choose. \n";
                            cout << "Your choice: " << WHITE ;
			    cin >> choice;
			}
			if (tolower(choice)=='y'){
		            //go to battle
		  	    getRandomCoordinateForEnemy(currentBlock,enemyCoordinate,avatarCoordinate);
                            enemyCoordinateArray[blockNum-1][0] = enemyCoordinate[0];
                            enemyCoordinateArray[blockNum-1][1] = enemyCoordinate[1];
			}
		    }

		    // FINAL BOSS
		    if (avatarCoordinate[0] == 8 && avatarCoordinate[1] == 30 && currentBlock == "txt/map4.txt"){
		    	mapWithAvatarAndEnemy(avatarSymbol,enemySymbol,avatarCoordinate,enemyCoordinate,currentBlock,newBlock);
                        printMap(newBlock);
			cout << BLUE <<"You have now reached the dungeon of our final boss.\n";
			cout << "This will be the toughest challenge that you may encounter. Are you sure that you are ready to go in and fight the final boss? [y/n]\n" << WHITE;
			while ((tolower(choice)!='y'&&tolower(choice)!='n')||cin.fail()){
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(),'\n');
			    cout << RED << "Are you sure you are ready to fight the boss? Please type in \"y\" or \"n\" to choose.\n";
                            cout << "Your choice: " << WHITE ;
                            cin >> choice;
                        }
                        if (tolower(choice)=='y'){
                            //go to battle
                        }
		    }

		    prevMove = string()+move[i];
		    mapWithAvatarAndEnemy(avatarSymbol,enemySymbol,avatarCoordinate,enemyCoordinate,currentBlock,newBlock);
		    break;
		}
                case 'm':
		    // to main menu
		    flag = 2;
		    break;
                default:
                    cout << RED << "\nPress WASD keys or alphabets shown in the map to move.\n";
                    cout << "Press M to open up the menu page.\n" << WHITE ; 
		    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
		    flag = 1;
		    break;
            }
	}
	moveFlag = 0;
	printMap(newBlock);
    }	
}
/*
int main(){
    int avatarCoordinate[2] = {2,13};
    int enemyCoordinate[2] = {3,54};
    string avatarSymbol = "[o.o]";
    string enemySymbol = "(^<^)";
    string currentBlock = "txt/map1.txt";
    string newBlock = "txt/out.txt";
    moveAroundMap(avatarCoordinate,enemyCoordinate,avatarSymbol,enemySymbol,currentBlock,newBlock);
}*/





