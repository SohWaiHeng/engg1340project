#include <iostream>
#include <fstream>
#include <limits>
#include "../hfiles/tutorial.h"
#include "../hfiles/colours.h"
using namespace std;

void movementTutorial(string currentBlock, string currentCharacter){
    ifstream fin("txt/map1.txt");   // created another text file to store so that the original map is not altered
    ofstream fout("txt/out.txt");  
    string line;
    while(getline(fin,line)){
        fout << line << endl;
    }
    fin.close();
    fout.close();

    string newBlock = "txt/out.txt";
    int coordinate[2];

    // teach player to move around using wasd
    cout << endl;
    cin.clear(); 
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << BLUE << "Let's begin the tutorial.\n" << WHITE << endl;
    printMap(newBlock); 
    cout << BLUE << "\nYou can move around the map by using WASD keys and press enter." << WHITE << endl;

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
                    cout << RED << "\nPlease enter WASD keys to move around.\n" << WHITE;
            }
        }
        cout << endl;
        printMap(newBlock);
        cout << endl;
    }

    // teach player shorcut movement
    cout << BLUE << "\nGood job! Now, can you see those alphabets on the map? You can fast forward your movement by typing those shortcut characters in. Try it out!" << WHITE << endl;
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
                    cout << RED << "\nTry entering the alphabets shown on the map to fast forward your movement." << WHITE << endl;
                    secondFlag = 1;
            }

        }
        cout << endl;
        printMap(newBlock);
        cout << endl;
    }

    // Ask player to go back
    cout << BLUE << "\nWell done! You can now move back to the previous spot by entering the same alphabet again. Press " << move[0] << " to go back!" << WHITE << endl;
    string secondMove;
    cout << "Your move(s)?: ";
    getline(cin, secondMove);
    while (toupper(secondMove[0]) != toupper(move[0])){
        cout << RED << "\nPress " << toupper(move[-1]) << " to go back!" << WHITE << endl;
        cout << "Your move(s)?: ";
        getline(cin, secondMove);
    }

    // player can move freely
    movement(move[0],newBlock,currentCharacter);
    printMap(newBlock);
    cout << BLUE << "\nGreat! Now, try moving around and explore the map. Remember, avoid hitting the wall!\n" << WHITE;
    int thirdFlag = 0;
    bool notrepeatprinting = false;
    
    while(thirdFlag < 2) {
        thirdFlag = 0; // 1:?? , 2: quit tutorial, 3: battle
        
        cout << endl;
        printMap(newBlock);
        cout << endl;

        getCoordinate(newBlock,']',coordinate);

        if (!notrepeatprinting) {
            if (coordinate[0] == 103 && coordinate[1] > 54){  //any coordinate, first enemy pops up
                cout << BLUE << "\nOMG! See that character on your right? What's that?" << endl;
                cout << "Seems like you have encountered your first opponent! Move nearer to your opponent to head to the battlefield." << WHITE << endl;
                notrepeatprinting = true;
            }
            if (coordinate[0] == 103 && coordinate[1] > 59) {  //coordinates to go to battlefield
                cout << endl;
                cout << BLUE << "Along your journey, you may often encounter with enemies at different parts of the map." << endl;
                cout << "You will have to battle with them in order to continue with your journey." << WHITE << endl;
                cout << GREEN << "Press enter to start battle." << WHITE << endl;
                string trash;
                getline(cin, trash);
                thirdFlag = 3;
                break;
            }
        }
        else {
            if (coordinate[0] == 103 && coordinate[1] > 59) {  //coordinates to go to battlefield
                cout << endl << BLUE << "Along your journey, you may often encounter with enemies at different parts of the map." << endl;
                cout << "You will have to battle with them in order to continue with your journey." << WHITE << endl;
                cout << GREEN << "Press enter to start battle." << WHITE << endl;
                string trash;
                getline(cin, trash);
                thirdFlag = 3;
                break;
            }
            else if (coordinate[1] < 55) {
                notrepeatprinting = false;
            }
        }

        cout << "\nPress WASD keys or alphabets shown in the map to move." << endl;
        cout << "Your move(s)?: ";
        
        getline(cin, move);
        for (int i = 0; i < move.length(); i++){
            move[i] = tolower(move[i]);
            switch(move[i]){
                case 'w': case 'a': case 's': case 'd': case 'c': case 'z': case 'x': case 'b': case 'v':
                    movement(move[i],newBlock,currentCharacter);
                    break;
                default:
                    cout << RED << "\nPress WASD keys or alphabets shown in the map to move." << WHITE << endl;
                    thirdFlag=1;
            }
        }
        cout << endl;
    }
}

void battleTutorial(creature deck[5]) {
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

    opponent currentOpponent;
    for (int i = 0; i < 5; i++) {
        currentOpponent.opponentCreature[i].setbasestats(i+1);
        currentOpponent.opponentCreature[i].setcurrentstats(1);
    }

    tutorialmode(deck, currentOpponent);
}

void tutorial () {
    // movement tutorial
    string currentCharacter = "[o.o]";   // currentCharacter can be changed depending on the player's current character
    string currentBlock = "map1.txt";
    movementTutorial(currentBlock, currentCharacter);

    // automatically give player initial deck
    creature deck[5];
    for (int i = 0; i < 5; i++) {
        deck[i].setbasestats(i+1);
        deck[i].setcurrentstats(1);
    }

    battleTutorial(deck);
}