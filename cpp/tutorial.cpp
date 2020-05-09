#include <iostream>
#include <fstream>
#include <limits>

#include "../hfiles/tutorial.h"
#include "../hfiles/colours.h"
#include "../hfiles/battle.h"
#include "../hfiles/movement.h"

using namespace std;

// this tutorial is used to teach players different ways of moving around the map
// parameters: avatarCoordinate and enemyCoordinate are the current coordinates of avatar and enemy on the map, avatarSymbol and enemySymbol are the figures of current avatar and enemy respectively, currentBlock is the original block of map, newBlock is the map which includes avatar and enemy figures
void movementTutorial(int avatarCoordinate[2], int enemyCoordinate[2], string &avatarSymbol, string &enemySymbol, string &currentBlock, string &newBlock){
    int moveFlag = 0;
    // teach players the movement keys used in this game (WASD)
    cout << endl;
    cout << BLUE << "Let's begin the tutorial.\n" << WHITE << endl;
    mapWithAvatarAndEnemy(avatarSymbol,enemySymbol,avatarCoordinate,enemyCoordinate,currentBlock,newBlock);
    printMap(newBlock); 
    cout << BLUE << "\nYou can move around the map by using WASD keys and press enter." << WHITE << endl;
    int numberOfMove = 0, firstFlag = 0, secondFlag = 0; 
    string move;
    // allow player to move around using WASD 5 times before proceeding to the next part of tutorial
    while (numberOfMove < 5){
        cout << "Your move(s)?: ";
        cin >> move;
        for (int i = 0; i < move.length() && firstFlag!=1; i++){
            move[i] = tolower(move[i]);
            switch(move[i]){
                case 'w': case 'a': case 's': case 'd':
                    movement(move[i],newBlock,avatarSymbol,moveFlag);
                    numberOfMove++;
                    break;

                default:
                    cout << RED << "\nPlease enter WASD keys to move around.\n" << WHITE;
            	    firstFlag = 1;
	        }
        }
	    firstFlag=0;
	    getCoordinate(newBlock,avatarSymbol[0],avatarCoordinate);
        mapWithAvatarAndEnemy(avatarSymbol,enemySymbol,avatarCoordinate,enemyCoordinate,currentBlock,newBlock);
	    printMap(newBlock);
    }

    // teach player the shortcut characters to fast forward their avatar's movement
    cout << BLUE << "\nGood job! Now, can you see those alphabets on the map? You can fast forward your movement by typing those shortcut characters in. Try it out!" << WHITE << endl;
    while(secondFlag < 2){
        secondFlag = 0;
        cout << "Your move(s)?: ";
        cin >> move;
        for (int i = 0; i < move.length() && secondFlag==0; i++){
            move[i] = tolower(move[i]);
            switch(move[i]){
                case 'c': case 'z': case 'x': case 'b': case 'v':
                    movement(move[i],newBlock,avatarSymbol,moveFlag);
                    secondFlag = 2;
                    break;
                default:
                    cout << RED << "\nTry entering the alphabets shown on the map to fast forward your movement." << WHITE << endl;
                    secondFlag = 1;
            }

        }
        getCoordinate(newBlock,avatarSymbol[0],avatarCoordinate);
        mapWithAvatarAndEnemy(avatarSymbol,enemySymbol,avatarCoordinate,enemyCoordinate,currentBlock,newBlock);
	    printMap(newBlock);
    	moveFlag = 0;
    }

    // allow player to move freely before proceeding to the battle tutorial
    cout << BLUE << "\nGreat! You can save yourself a lot of time but using these fast forward keys to move around!\n" << WHITE;
    cout << BLUE << "Now, try moving around and explore the map. Remember, avoid hitting the wall!\n" << WHITE;
    int thirdFlag = 0;
    bool notrepeatprinting = false;
    
    while(thirdFlag < 2) {
        thirdFlag = 0; 
        getCoordinate(newBlock,avatarSymbol[0],avatarCoordinate);
        mapWithAvatarAndEnemy(avatarSymbol,enemySymbol,avatarCoordinate,enemyCoordinate,currentBlock,newBlock);
        printMap(newBlock);
	    moveFlag = 0;

        if (!notrepeatprinting) {
            if (avatarCoordinate[0] == 3 && avatarCoordinate[1] > 45){  // messages sent when they are nearing the enemy
                cout << BLUE << "\nHey, you did a great job moving around the map and exploring!" << endl;
                cout << "Look! Seems like have met your first opponent. Go nearer to it to start the battle." << WHITE << endl;
                notrepeatprinting = true;
            }
            if (avatarCoordinate[0] == 3 && avatarCoordinate[1] > 47) {  //coordinates to go to battlefield
                cout << endl;
                cout << BLUE << "Along your journey, you may often encounter with enemies at different parts of the map." << endl;
                cout << "You will have to battle with them in order to continue with your journey." << WHITE << endl;
                cout << GREEN << "Press enter to start battle." << WHITE << endl;
                string trash;
                getline(cin, trash);
                enemyCoordinate[0] = 21;
                enemyCoordinate[1] = 16;
                thirdFlag = 3;
                break;
            }
        }
        else {
            if (avatarCoordinate[0] == 3 && avatarCoordinate[1] > 47) {  //coordinates to go to battlefield
                cout << endl << BLUE << "Along your journey, you may often encounter with enemies at different parts of the map." << endl;
                cout << "You will have to battle with them in order to continue with your journey." << WHITE << endl;
                cout << GREEN << "Press enter to start battle." << WHITE << endl;
                string trash;
                getline(cin, trash);
                enemyCoordinate[0] = 21;
                enemyCoordinate[1] = 16;
                thirdFlag = 3;
                break;
            }
            else if (avatarCoordinate[1] < 45) {
                notrepeatprinting = false;
            }
        }

        cout << "\nPress WASD keys or alphabets shown in the map to move." << endl;
        cout << "Your move(s)?: ";
        getline(cin, move);
        for (int i = 0; i < move.length(); i++){
            move[i] = tolower(move[i]);
            int testCoordinate[2] = {-1,-1};
            switch(move[i]){
                case 'w': case 'a': case 's': case 'd': case 'c': case 'z': case 'x': case 'b': case 'v':
                    getCoordinate(newBlock,toupper(move[i]),testCoordinate);
                    if (((testCoordinate[0]==-1) && (move[i]=='z'||move[i]=='x'||move[i]=='c'||move[i]=='v'||move[i]=='b'))||moveFlag==1){
                        break;
                    }
                    movement(move[i],newBlock,avatarSymbol,moveFlag);
                    break;
                default:
                    cout << RED << "\nPress WASD keys or alphabets shown in the map to move." << WHITE << endl;
                    thirdFlag=1;
            }
        }
        cout << endl;
    }
}

// this tutorial is used to give the player an overview of how the batlles in our game will be like
// parameter: deck is a deck of 5 creatures, winlose is to determine if player has win the battle (true when player wins, false otherwise), currentopponent is the current opponent player is facing
void battleTutorial(creature deck[5], bool &winlose, opponent currentOpponent) {
    cout << HIGHLIGHT << "Heading to battlefield..."  << WHITE << endl;
    delay(3);
    
    ifstream fin;
    fin.open("txt/battletutorial.txt");
    if (fin.fail()) {
        cout << "Failed to open battletutorial.txt" << endl;
    }

    string line;
    int linecount = 0;
    while ((linecount) % 29 != 0 || linecount == 0){
        getline(fin, line);
        cout << line << endl;
        linecount++;
    }

    cout << endl;
    cout << BLUE << "Great! You're now in the battlefield." << endl;
    cout << GREEN << "Press enter to continue." << WHITE << endl;
    string trash;
    getline(cin, trash);

    getline(fin, line);
    cout << line << endl;
    linecount++;
    while ((linecount) % 29 != 0){
        getline(fin, line);
        cout << line << endl;
        linecount++;
    }

    cout << endl;
    cout << BLUE << "In this game you will use a deck of 5 creatures in battle." << endl;
    cout << "See the characters at the left of the console above? Those are the creatures in your deck." << endl;
    cout << GREEN << "Press enter to continue." << WHITE << endl;
    getline(cin, trash);
    
    cout << endl;
    cout << BLUE << "The deck you have now is the deck preset at the beginning of the game." << endl;
    cout << "Along with the progression of the game, you will collect more creatures and you will be able to build stronger decks." << endl;
    cout << GREEN << "Press enter to continue." << WHITE << endl;
    getline(cin, trash);

    getline(fin, line);
    cout << line << endl;
    linecount++;
    while ((linecount) % 29 != 0){
        getline(fin, line);
        cout << line << endl;
        linecount++;
    }

    cout << endl;
    cout << BLUE << "The 5 rectangles at the bottom represent the cards in your hand." << endl;
    cout << "You can use these cards onto creatures in battle to give the creatures special effects." << endl;
    cout << GREEN << "Press enter to continue." << WHITE << endl;
    getline(cin, trash);
    
    cout << endl;
    cout << BLUE << "The cards in your hand depend on the deck of creatures you use in the battlefield." << endl;
    cout << "Each creature owns 5 cards (so you have a total of 25 cards), and 5 cards will be drawn randomly from these 25 cards at the start of a battle." << endl;
    cout << GREEN << "Press enter to continue." << WHITE << endl;
    getline(cin, trash);

    getline(fin, line);
    cout << line << endl;
    linecount++;
    while ((linecount) % 29 != 0){
        getline(fin, line);
        cout << line << endl;
        linecount++;
    }

    cout << endl;
    cout << BLUE << "Every round, elixir will be given to you and your opponent." << endl;
    cout << "Elixir is used to perform actions in battle. For example, to use the card named \"combo\" you will need 4 elixir." << endl;
    cout << GREEN << "Press enter to continue." << WHITE << endl;
    getline(cin, trash);

    // more tutorial on the battle
    tutorialmode(deck, currentOpponent, winlose);
}

// main tutorial function
// parameters are same as the parameters mentioned above
void tutorial (int avatarCoordinate[2], int enemyCoordinate[2], string &avatarSymbol, string &enemySymbol, string &currentBlock, string &newBlock, opponent &currentopponent, bool &winlose, creature deck[5]) {
    // movement tutorial
    movementTutorial(avatarCoordinate, enemyCoordinate, avatarSymbol, enemySymbol, currentBlock, newBlock);

    // battle tutorial
    determineopponent("tutorial", currentopponent, deck);
    battleTutorial(deck, winlose, currentopponent);
}
