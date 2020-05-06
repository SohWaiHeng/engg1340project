#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <limits>
#include <iomanip>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "../hfiles/movement.h"
#include "../hfiles/menu.h"
#include "../hfiles/structs.h"
#include "../hfiles/titleScreen.h"
#include "../hfiles/colours.h"
#include "../hfiles/battle.h"
#include "../classes/avatar.h"
#include "../classes/creature.h"
#include "../classes/currency.h"

using namespace std;

// CREATURES

// load owned creatures and unowned creatures to respective struct
void loadCreaturesFromSavedTextFile(creatures ownedCreature[100], creatures notOwnedCreature[100]){  
    string line, secondLine, thirdLine;
    int no, count = 0, secondCount = 0;
    int noArray[100] = {0};
    // load owned creatures from save.txt file and save these creature's index in an array
    ifstream fin("ownedAvatarsAndCreatures.txt");
    getline(fin, line);
    istringstream iss(line);
    iss >> secondLine;
    while (iss >> no){
        noArray[count]=no;
	count++;
    }
    fin.close();
    count = 0, secondCount = 0;
    // load creature.txt to get stats of all creatures, save them into two different structs (owned creatures and not owned creatures)
    ifstream fin2("creature.txt");
    while (getline(fin2, secondLine)){
        istringstream iss2(secondLine);
        iss2 >> no;
        // all the stats of owned creatures are saved into a struct
        if (find(noArray,end(noArray),no)!=end(noArray) && no != 0){
	    string str, name = "";
            ownedCreature[count].index = no;
            iss2 >> no;
            for (int i = 0; i < no; i++){
                iss2 >> str;
                if (name != ""){
                    name = name + " " + str;
                }
                else{
                    name += str;
                }
            }
            ownedCreature[count].name = name;
	    iss2 >> name;
            ownedCreature[count].symbol = name;
            int *cardArr = new int [5];
            for (int i = 0; i < 5; i++){
                iss2 >> no;
                cardArr[i] = no;
            }
            ifstream fin3("card.txt");
            string line;
            int count1 = 0;
            while(getline(fin3, thirdLine) && count < 5){
                istringstream iss3(thirdLine);
                int no, lengthofName;
                string str, name = "";
                iss3 >> no;
                if (find(cardArr,cardArr+5,no)!=cardArr+5){
                    iss3 >> lengthofName;
                    for (int i = 0; i < lengthofName && count1 < 5; i++){
                        iss3 >> str;
                        if (name != ""){
                            name = name + " " + str;
                        }
                        else{
                            name += str;
                        }
                    }
                    ownedCreature[count].cards[count1] = name;
                    count1++;
                }
            }
	    delete [] cardArr;
            fin3.close();
            iss2 >> no;
            ownedCreature[count].hp = no;
            iss2 >> no;
            ownedCreature[count].cost = no;
            iss2 >> no;
            ownedCreature[count].atk = no;
            iss2 >> no;
            ownedCreature[count].mgc = no;
            iss2 >> no;
            ownedCreature[count].crt = no;
            count++;
        }
        // save stats of creatures not owned into a different struct
        else if ((find(noArray,end(noArray),no)==end(noArray) && no != 0)) {
            string str, name = "";
            notOwnedCreature[secondCount].index = no;
            iss2 >> no;
            for (int i = 0; i < no; i++){
                iss2 >> str;
                if (name != ""){
                    name = name + " " + str;
                }
                else{
                    name += str;
                }
            }
            notOwnedCreature[secondCount].name = name;
            iss2 >> name;
            notOwnedCreature[secondCount].symbol = name;
            int cardArr[5];
            for (int i = 0; i < 5; i++){
                iss >> no;
                cardArr[i] = no;
            }
            ifstream fin3("card.txt");
            string line;
            int count1 = 0;
            while(getline(fin3, thirdLine) && count < 5){
                istringstream iss3(thirdLine);
                int no, lengthofName;
                string str, name = "";
                iss3 >> no;
                if (find(cardArr,end(cardArr),no)!=end(cardArr)){
                    iss3 >> lengthofName;
                    for (int j = 0; j < lengthofName; j++){
                        iss3 >> str;
                        if (name != ""){
                            name = name + " " + str;
                        }
                        else{
                            name += str;
                        }
                    }
                    notOwnedCreature[secondCount].cards[count1] = name;
                    count1++;
                }
            }
            fin3.close();
            iss2 >> no;
            notOwnedCreature[secondCount].hp = no;
            iss2 >> no;
            notOwnedCreature[secondCount].cost = no;
            iss2 >> no;
            notOwnedCreature[secondCount].atk = no;
            iss2 >> no;
            notOwnedCreature[secondCount].mgc = no;
            iss2 >> no;
            notOwnedCreature[secondCount].crt = no;
	    secondCount++;
        }
    }
    for (int i = count+1; i <100 && ownedCreature[i].index!=0; i++){
	ownedCreature[i].index == 0;
	ownedCreature[i].name == "";
    }
    for (int i = secondCount+1; i <100 && notOwnedCreature[i].index!=0; i++){
         notOwnedCreature[i].index == 0;
         notOwnedCreature[i].name == "";
    }
    fin2.close();
}

// display 10 avatars or creatures each page, owned and unowned, this function is needed in both avatar and creature menus
void displayAvatarsOrCreaturesByPage(int pageCount, string file){
    cout << "No.          NAME              SYMBOL  " <<endl;
    ifstream fin(file);
    string line;
    int count = 1;
    while (getline(fin, line) && count <= 10){
	istringstream iss(line);
        int no, lengthOfName;
        string str, name = "", outputName;
        iss >> no;
	if (no == (pageCount*10)+count){
            iss >> lengthOfName;
            for (int i = 0; i < lengthOfName; i++){
                iss >> str;
                if (name != ""){
                    name = name + " " + str;
                }
                else{
                    name += str;
                }
            }
            int space = (25-name.length())/2;
            outputName = string(space,' ')+name+string(space,' ');
            iss >> str;
            cout << setw(2) << count << '.' << setw(25) << outputName << "  "<< setw(8) << str << endl;
            count++;
        }
    }
    fin.close();
}

// display stats of avatar or creature, this function is needed in both avatar and creature menus
void displayAvatarsOrCreatureDetails(int no, string file, string stats[], int statsLength){
    ifstream fin(file);
    string line;
    while (getline(fin, line)){
        istringstream iss(line);
        int num;
        string str, name = "";
        iss >> num;
        if (num == no){
            iss >> num;
            for (int i = 0; i < num; i++){
                iss >> str;
                if (name != ""){
                    name = name + " " + str;
                }
                else{
                    name += str;
                }
            }
            cout << "\n  NAME  : " << name << endl;
            iss >> str;
            cout << " FIGURE : " << str << endl;
            cout << " CARDS  :";
            int cardNum[5];
            for (int i = 0; i < 5; i++){
                iss >> cardNum[i];
            }
            ifstream fin("card.txt");
            string secondLine;
            int count = 0;
            while (getline(fin, secondLine) && count < 5){
                istringstream iss(secondLine);
                int secondNum, *p;
                string secondStr, secondName = "";
                iss >> secondNum;
                p = find(begin(cardNum), end(cardNum), secondNum);
                if (p != end(cardNum)){
                    iss >> secondNum;
                    for (int i = 0; i < secondNum; i++){
                        iss >> secondStr;
                        if (secondName != ""){
                            secondName = secondName + " " + secondStr;
                        }
                        else{
                            secondName += secondStr;
                        }
                    }
                    if (count != 4){
                        cout << " " << secondName << ',';
                    }
                    else {
                        cout << " " << secondName;
                    }
                    count++;
                }
            }
            cout << endl;
            for (int i = 0; i < statsLength; i++){
                iss >> num;
                cout << stats[i] << ": " << num << endl;
            }
        }
    }
}


// display 10 owned creatures each page
void displayOwnedCreaturesByPage(int pageCount, creatures ownedCreature[100]){
    cout << "No.          NAME              SYMBOL  " << endl;
    int count = 0;
    cout << ownedCreature[0].name << " in creatures page" << endl;
    for (int i = 10*pageCount; i < 10*pageCount+10; i++){
        string name = ownedCreature[i].name;
        if (name.empty() || name == ownedCreature[i-1].name){
            break;
        }
        string symbol = ownedCreature[i].symbol;
        int space = (25-name.length())/2;
        string outputName = string(space,' ')+name+string(space,' ');
        cout << setw(2) << count << '.' << setw(25) << outputName << "  " << setw(8) << symbol << endl;
        count++;
    }
}

// display 10 unowned creatures by page
void displayCreaturesNotOwnedByPage(int pageCount, creatures notOwnedCreature[100] ){
    cout << "No.          NAME              SYMBOL   COST" << endl;
    int count = 0, no;
    for (int i = 10*pageCount; i < 10*pageCount+10; i++){
        string name = notOwnedCreature[i].name;
        if (name.empty() || name == notOwnedCreature[i-1].name){
            break;
        }
        string symbol = notOwnedCreature[i].symbol;
        int space = (25-name.length())/2;
        string outputName = string(space,' ')+name+string(space,' ');
        int cost = notOwnedCreature[i].cost;
        cout << setw(2) << count << '.' << setw(25) << outputName << "  "<< setw(8) << symbol << "   " << cost << endl;
        count++;
    }
}

void changeOwnedAvatarsAndCreaturesTextFile(int num, string choice, creatures ownedCreature[100], creatures notOwnedCreature[100], avatars ownedAvatar[50], avatars notOwnedAvatar[50]){
    ifstream fin2("ownedAvatarsAndCreatures.txt");
    ofstream fout("temp.txt");
    int arrayCount = 0, number, ownedCreaturesArray[50], flag = 0;
    string secondLine, str2;
    while (getline(fin2,secondLine)){      //APPEND ONTO THE END OF LINE IN SAVE TXT FILE
        istringstream iss2(secondLine);
        iss2 >> str2;
        if (str2 == choice){
	    cout << choice << endl;
            while (iss2 >> number){
	    	cout << number << endl;
            // to ensure the number is in ascending order
                if (flag==0 && number > num){
		    ownedCreaturesArray[arrayCount] = num;
                    arrayCount++;
                    flag = 1;
                }
                ownedCreaturesArray[arrayCount] = number;
                arrayCount++;
	    }
            if (find(ownedCreaturesArray,end(ownedCreaturesArray),num)==end(ownedCreaturesArray)){                                
		ownedCreaturesArray[arrayCount] = num;
                arrayCount++;
            }
            fout << choice;
            for (int i = 0; i < arrayCount; i++){
                fout << ' ' << ownedCreaturesArray[i];
	    }
            fout << endl;
	}
	else {
            fout << secondLine << endl;
        }
    }
    fout.close();
    fin2.close();
    remove("ownedAvatarsAndCreatures.txt");
    rename("temp.txt","ownedAvatarsAndCreatures.txt");
    if (choice == "creature"){
        loadCreaturesFromSavedTextFile(ownedCreature,notOwnedCreature);
    }
    else if (choice == "avatar"){
	loadAvatarsFromSavedTextFile(ownedAvatar,notOwnedAvatar);
    }
}


void displayCreature(string choice, int *currency, string creaturesDeck[5], creatures ownedCreature[100], creatures notOwnedCreature[100], avatars ownedAvatar[50], avatars notOwnedAvatar[50]){
    string viewChoiceList[10] = {"0","1","2","3","4","5","6","7","8","9"};  
    string pageChoiceList[10] = {"10","1","2","3","4","5","6","7","8","9"};
    string creatureStats[] = {"   HP   ", "  COST  ", "  ATK   ", "  MGC   ", "  CRT   "};
    // battle menu
    if (choice=="battle"){
        int count = 0, playersChoice = 1;
        while (playersChoice != 0){
            cout << "\n = YOUR CREATURES = \n";
            for (int i = 0; i < 5; i++){
                cout << i+1 << ". " << creaturesDeck[i] << endl;
            }
            cout << "\nEnter a number to view the avatar's stats.\n";
            cout << "Enter 9 to return to battle.\n";
            cout << "Your choice: ";
            cin >> playersChoice;
            cout << playersChoice << endl;
            if (playersChoice == 9) {break;}
            while (playersChoice < 1 || playersChoice > 5 || cin.fail()){
                cin.clear();  
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "\x1B[31m" << "\nEnter a number to view the avatar's stats.\n" << "\x1B[0m" ;
                cout << "\x1B[31m" << "Enter 9 to return to battle.\n" << "\x1B[0m";
                cout << "\x1B[31m"  << "Your choice: " << "\x1B[0m" ;
                cin >> playersChoice;
                if (playersChoice == 9) {break;}
            }
            for (int i = 0; i < 100; i++){
                if (ownedCreature[i].name == creaturesDeck[playersChoice-1]){
                    displayAvatarsOrCreatureDetails(ownedCreature[i].index, "creature.txt", creatureStats, 5);
                    cout << "\nEnter 9 to return to creature page: ";
                    cin >> playersChoice;
                    while (playersChoice != 9 || cin.fail()){
                        cin.clear();  
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                        cout << "\x1B[31m" << "\nEnter 9 to return to creature page: " << "\x1B[0m";
                        cin >> playersChoice;
                    }
                    break;
                }
            }
        }
    }
    // main menu
    if (choice=="main"){
        int pageCount = 1 ,maxPageCount = 8;  //maxPageCount can be changed depending on the number of creatures, try to not exceed single digit pages (more convenient?)
        char playersChoice[3] = "P1";
        cout << "\n = CREATURES MENU = \n\n";
        while (toupper(playersChoice[0])!='Q'){
            cout << "\nPAGE " << pageCount << endl;
            displayAvatarsOrCreaturesByPage(pageCount-1, "creature.txt");
            cout << "\nPress V together with a creature's number to view the creature's stats. [Eg: V3 to view the creature 3]\n";
            cout << "Press P together with a page number to turn to that page. [Eg: P6 to skip to page 6]\n";
            cout << "Press Q to return to main menu. \n";
            cout << "Your choice: ";
            cin >> playersChoice;
            if (toupper(playersChoice[0])=='Q'){break;}
            while ((toupper(playersChoice[0]) != 'P' && toupper(playersChoice[0]) != 'V') || (toupper(playersChoice[0]) == 'P'  && find(pageChoiceList,end(pageChoiceList), string(playersChoice).substr(1)) == end(pageChoiceList)) || (toupper(playersChoice[0]) == 'V' && find(viewChoiceList,end(viewChoiceList), string(playersChoice).substr(1)) == end(viewChoiceList)) || cin.fail()){
                cin.clear();  
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "\x1B[31m" << "\nPress V together with a creature's number to view the creature's stats. [Eg: V3]\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Press P together with a page number to turn to that page. [Eg: P6]\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Press Q return to main menu.\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Your choice: "<< "\x1B[0m" ;
                cin >> playersChoice;
                if (toupper(playersChoice[0])=='Q'){break;}
            }
            switch (toupper(playersChoice[0])){
                case 'P':
                    pageCount = stoi(string(playersChoice).substr(1));
                    break;
                case 'V':
                    int creatureNumber;
                    creatureNumber = stoi(string(playersChoice).substr(1))+((pageCount-1)*10);
                    displayAvatarsOrCreatureDetails(creatureNumber, "creature.txt", creatureStats, 5);
                    cout << "\nEnter R to return to creature page: ";
                    cin >> playersChoice;
                    while (toupper(playersChoice[0]) != 'R'){
                        cout << "\x1B[31m" << "\nEnter R to return to creature page: " << "\x1B[0m";
                        cin >> playersChoice;
                    }
                    break;
                case 'Q':
                    cout << "";
                    break;
            }
        }
    }
    // inventory menu
    if (choice=="inventory"){
        int count = 0, pageCount = 1 ,maxPageCount = 8;  
        char playersChoice[3] = {0};
        string changeChoiceList[50];
        for (int i = 10; i < 60; i++){
            changeChoiceList[count] = to_string(i);
            count++;
        }
        cout << "\n = YOUR CREATURES = \n";
        while (toupper(playersChoice[0])!='Q'){
	    cout << "\nCOINS: " << *currency << endl;
            cout << "\n - Your Creatures Deck - \n\n";
            for (int i = 0; i < 5; i++){
                cout << i+1 << ". " << creaturesDeck[i] << endl;
            }
            cout << "\nPAGE " << pageCount << endl;
            displayOwnedCreaturesByPage(pageCount-1,ownedCreature);
            cout << "\nPress V together with a creature's number to view the creature's stats. [Eg: V3 to view creature 3]\n";
            cout << "Press P together with a page number to turn to that page. [Eg: P6 to skip to page 6]\n";
            cout << "Press C together with creature's number on the creatures' deck that you wanna change followed by the creature's number that is swapping in.\n";
            cout << "[Eg: C37 to swap out creature 3 from the deck for creature 7 shown on current page.]\n";
            cout << "Press Q to return to inventory menu. \n";
            cout << "Your choice: ";
            cin >> playersChoice;
            if (toupper(playersChoice[0])=='Q'){break;}
            while ((toupper(playersChoice[0]) != 'P' && toupper(playersChoice[0]) != 'V' && toupper(playersChoice[0]) != 'C') || (toupper(playersChoice[0]) == 'C' && find(changeChoiceList,end(changeChoiceList), string(playersChoice).substr(1)) == end(changeChoiceList)) || (toupper(playersChoice[0]) == 'P'  && find(pageChoiceList,end(pageChoiceList), string(playersChoice).substr(1)) == end(pageChoiceList)) || (toupper(playersChoice[0]) == 'V' && find(viewChoiceList,end(viewChoiceList), string(playersChoice).substr(1)) == end(viewChoiceList)) || cin.fail() ){
                cin.clear();  
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "\x1B[31m" << "\nPress V together with a creature's number to view the creature's stats. [Eg: V3]\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Press P together with a page number to turn to that page. [Eg: P6]\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Press C together with creature's number on the creatures' deck that you wanna change followed by the creature's number that is swapping in.\n" << "\x1B[0m";
                cout << "\x1B[31m" << "[Eg: C37 to swap out creature 3 from the deck for creature 7 shown on current page.]\n" << "\x1B[0m" ;
                cout << "\x1B[31m" << "Press Q return to inventory menu.\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Your choice: "<< "\x1B[0m" ;
                cin >> playersChoice;
                if (toupper(playersChoice[0])=='Q'){break;}
            }
            switch (toupper(playersChoice[0])){
                case 'P':
                    pageCount = stoi(string(playersChoice).substr(1));
                    break;
                case 'V':
                    int creatureNumber;
                    creatureNumber = ownedCreature[stoi(string(playersChoice).substr(1))+((pageCount-1)*10)].index;
                    if (ownedCreature[stoi(string(playersChoice).substr(1))+((pageCount-1)*10)].index == 0){
                        cout << "\x1B[31m" << "Invalid input!\n" << "\x1B[0m";
                        break;
                    }
                    displayAvatarsOrCreatureDetails(creatureNumber, "creature.txt", creatureStats, 5);
                    cout << "\nEnter R to return to creature page: ";
                    cin >> playersChoice;
                    while (toupper(playersChoice[0]) != 'R'){
                        cout << "\x1B[31m" << "\nEnter R to return to creature page: " << "\x1B[0m";
                        cin >> playersChoice;
                    }
                    break;
                case 'C':
                    if (find(creaturesDeck, creaturesDeck+5, ownedCreature[(pageCount-1)*10+stoi(string(playersChoice).substr(2,1))].name) != creaturesDeck+5){
                        cout << "\x1B[31m" << "\nThis creature is already in your deck.\n" << "\x1B[0m" ;
                    }
                    else if (ownedCreature[(pageCount-1)*10+stoi(string(playersChoice).substr(2,1))].name.empty()){
                        cout << "\x1B[31m" << "Invalid input!\n" << "\x1B[0m";
                    }
                    else if ((stoi(string(playersChoice).substr(1))>9 || stoi(string(playersChoice).substr(1))<60)){  //
                        creaturesDeck[stoi(string(playersChoice).substr(1,1))-1] = ownedCreature[(pageCount-1)*10+stoi(string(playersChoice).substr(2,1))].name;   //test whether this work
                    }
                    else {cout << "\x1B[31m" << "Please enter your choice according to the instructions given. \n" << "\x1B[0m";}
                    
                    break;
                case 'Q':
                    cout << "";
                    break;
            }
        }
        //back to map
    }
    // shop menu
    if (choice=="shop"){
        int pageCount = 1, maxPageCount = 8;
        char playersChoice[3];
        cout << "\n = CREATURES SHOP = \n";
        while (toupper(playersChoice[0]) != 'Q'){
            cout << "\nCOINS: " << *currency << endl;
	    cout << "\nPAGE " << pageCount << endl;
            displayCreaturesNotOwnedByPage(pageCount-1,notOwnedCreature);
            cout << "\nPress V together with a creature's number to view the creature's stats. [Eg: V3 to view creature 3]\n";
            cout << "Press P together with a page number to turn to that page. [Eg: P6 to skip to page 6]\n";
            cout << "Press B together with a creature's number to purchase it. [Eg: B5 to buy creature 5]\n";
            cout << "Press Q to return to shop menu. \n";
            cout << "Your choice: ";
            cin >> playersChoice;
            if (toupper(playersChoice[0])=='Q'){break;}
            while ((toupper(playersChoice[0]) != 'P' && toupper(playersChoice[0]) != 'V' && toupper(playersChoice[0]) != 'B') || (toupper(playersChoice[0]) == 'P'  && find(pageChoiceList,end(pageChoiceList), string(playersChoice).substr(1)) == end(pageChoiceList)) || (toupper(playersChoice[0]) == 'V' && find(viewChoiceList,end(viewChoiceList), string(playersChoice).substr(1)) == end(viewChoiceList)) || (toupper(playersChoice[0]) == 'B' && find(viewChoiceList,end(viewChoiceList), string(playersChoice).substr(1)) == end(viewChoiceList)) || cin.fail()){
                cin.clear();  
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "\x1B[31m" << "\nPress V together with a creature's number to view the creature's stats. [Eg: V3]\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Press P together with a page number to turn to that page. [Eg: P6]\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Press B together with a creature's number to purchase it. [Eg: B5]\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Press Q return to shop menu.\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Your choice: "<< "\x1B[0m" ;
                cin >> playersChoice;
                if (toupper(playersChoice[0])=='Q'){break;}
            }
            switch(toupper(playersChoice[0])){
                case 'P':
                    pageCount = stoi(string(playersChoice).substr(1));
                    break;
                case 'V':
                    int creatureNumber;
                    creatureNumber = notOwnedCreature[stoi(string(playersChoice).substr(1))+((pageCount-1)*10)].index;
                    if (notOwnedCreature[stoi(string(playersChoice).substr(1))+((pageCount-1)*10)].index == 0){
                        cout << "\x1B[31m" << "Invalid input!\n" << "\x1B[0m";
                        break;
                    }
                    displayAvatarsOrCreatureDetails(creatureNumber, "creature.txt", creatureStats, 5);
                    cout << "\nEnter R to return to creature page: ";
                    cin >> playersChoice;
                    while (toupper(playersChoice[0]) != 'R'){
                        cout << "\x1B[31m" << "\nEnter R to return to creature page: " << "\x1B[0m";
                        cin >> playersChoice;
                    }
                    break;
                case 'B':
                    int cost = notOwnedCreature[(stoi(string(playersChoice).substr(1))+(pageCount-1)*10)].cost;
                    int buy = notOwnedCreature[(stoi(string(playersChoice).substr(1))+(pageCount-1)*10)].index;
                    if (buy==0){
                        cout << "\x1B[31m" << "Invalid input!\n" << "\x1B[0m";
                        break;
                    }
                    else if (*currency < cost){
                        cout << "\x1B[31m" << "You do not have enough coins to buy this creature!\n" << "\x1B[0m";
                        break;
                    }
                    cout << "\x1B[31m" << "Are you sure that you want to purchase this creature? [y/n] \n" << "\x1B[0m";
                    char toBuy;
                    cin >> toBuy;
                    while ((tolower(toBuy)!='y' && tolower(toBuy)!='n') || cin.fail()){  // havent see if enough money or not, use money > cost
                        cin.clear();  
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                        cout << "\x1B[31m" << "Please enter y or n to indicate your choice.\n" << "\x1B[0m";
                        cin >> toBuy;
                    }
                    if (toBuy=='y'){ 
		    changeOwnedAvatarsAndCreaturesTextFile(buy,"creature",ownedCreature,notOwnedCreature,ownedAvatar,notOwnedAvatar);
                       * currency = * currency - cost;
                        cout << "\nCreature " << string(playersChoice).substr(1) << " has been purchased!\n";  //need to run the loadfromsavetxtfile function again since save txt is updated
                    }
	            break;
            }
        }
    }
}


// AVATARS 

// load owned avatars and unowned avatars to respective struct, similar to creatures
void loadAvatarsFromSavedTextFile(avatars ownedAvatar[50], avatars notOwnedAvatar[50]){    
    string line, secondLine, thirdLine;
    int no, count = 0, secondCount = 0;
    int noArray[50] = {0};
    ifstream fin("ownedAvatarsAndCreatures.txt");
    getline(fin,line);
    getline(fin,line);
    istringstream iss(line);
    iss >> secondLine;
    while (iss >> no){
        noArray[count]=no;
        count++;
    }
    fin.close();
    count = 0, secondCount = 0;
    ifstream fin2("avatar.txt");
    while (getline(fin2, secondLine)){
        istringstream iss2(secondLine);
        iss2 >> no;
        if (find(noArray,end(noArray),no)!=end(noArray) && no != 0){
	    string str, name = "";
            ownedAvatar[count].index = no;
            iss2 >> no;
            for (int i = 0; i < no; i++){
                iss2 >> str;
                if (name != ""){
                    name = name + " " + str;
                }
                else{
                    name += str;
                }
            }
	    ownedAvatar[count].name = name;
	    iss2 >> name;
	    ownedAvatar[count].symbol = name;
            int *cardsArr = new int [5];
            for (int i = 0; i < 5; i++){
                iss2 >> no;
                cardsArr[i] = no;
            }
	    ifstream fin3("card.txt");
	    string line;
            int count1 = 0;
            while(getline(fin3, thirdLine)){
                istringstream iss3(thirdLine);
                int no, lengthofName;
                string str, name = "";
                iss3 >> no;
                if (find(cardsArr,cardsArr+5,no)!=cardsArr+5){
                    iss3 >> lengthofName;
                    for (int j = 0; j < lengthofName && count1 < 5; j++){
                        iss3 >> str;
                        if (name != ""){
                            name = name + " " + str;
                        }
                        else{
                            name += str;
                        }
                    }
                    ownedAvatar[count].cards[count1] = name;
                    count1++;
                }
            }
	    delete[] cardsArr;
            fin3.close();
            iss2 >> no;
            ownedAvatar[count].cost = no;
            iss2 >> no;
            ownedAvatar[count].meter = no;
            count++;
        }
        else if ((find(noArray,end(noArray),no)==end(noArray) && no != 0)) {
            string str, name = "";
            notOwnedAvatar[secondCount].index = no;
            iss2 >> no;
            for (int i = 0; i < no; i++){
                iss2 >> str;
                if (name != ""){
                    name = name + " " + str;
                }
                else{
                    name += str;
                }
            }
            notOwnedAvatar[secondCount].name = name;
            iss2 >> name;
            notOwnedAvatar[secondCount].symbol = name;
            int cardArr[5];
            for (int i = 0; i < 5; i++){
                iss2 >> no;
                cardArr[i] = no;
            }
            ifstream fin3("card.txt");
	    string line;
            int count1 = 0;
            while(getline(fin3, thirdLine) && count < 5){
                istringstream iss3(thirdLine);
                int no, lengthofName;
                string str, name = "";
                iss3 >> no;
                if (find(cardArr,cardArr+5,no)!=cardArr+5){
                    iss3 >> lengthofName;
                    for (int i = 0; i < lengthofName && count1 < 5; i++){
                        iss3 >> str;
                        if (name != ""){
                            name = name + " " + str;
                        }
                        else{
                            name += str;
                        }
                    }
                    notOwnedAvatar[secondCount].cards[count1] = name;
                    count1++;
                }
            }
            fin3.close();
            iss2 >> no;
            notOwnedAvatar[secondCount].cost = no;
            iss2 >> no;
            notOwnedAvatar[secondCount].meter = no;
            secondCount++;
        }
    }
    for (int i = count+1; i <100 && ownedAvatar[i].index!=0; i++){
         ownedAvatar[i].index == 0;
         ownedAvatar[i].name == "";
     }
     for (int i = secondCount+1; i <100 && notOwnedAvatar[i].index!=0; i++){
          notOwnedAvatar[i].index == 0;
          notOwnedAvatar[i].name == "";
     }
    fin2.close();
}

// display 10 owned avatars each page
void displayOwnedAvatarsByPage(int pageCount, avatars ownedAvatar[50]){
    cout << "No.          NAME              SYMBOL  " << endl;
    int count = 0;
    for (int i = 10*pageCount; i < 10*pageCount+10; i++){
        string name = ownedAvatar[i].name;
        if (name.empty() || name == ownedAvatar[i-1].name){
            break;
        }
        string symbol = ownedAvatar[i].symbol;
        int space = (25-name.length())/2;
        string outputName = string(space,' ')+name+string(space,' ');
        cout << setw(2) << count << '.' << setw(25) << outputName << "  " << setw(8) << symbol << endl;
        count++;
    }
}

// display 10 unowned avatars each page
void displayAvatarsNotOwnedByPage(int pageCount, avatars notOwnedAvatar[50]){
    cout << "No.          NAME              SYMBOL   COST" << endl;
    int count = 0, no;
    for (int i = 10*pageCount; i < 10*pageCount+10; i++){
        string name = notOwnedAvatar[i].name;
        if (name.empty() || name == notOwnedAvatar[i-1].name){
            break;
        }
        string symbol = notOwnedAvatar[i].symbol;
        int space = (25-name.length())/2;
        string outputName = string(space,' ')+name+string(space,' ');
        int cost = notOwnedAvatar[i].cost;
        cout << setw(2) << count << '.' << setw(25) << outputName << "  "<< setw(8) << symbol << "   " << cost << endl;
        count++;
    }
}

// main avatar displaying function
void displayAvatar(string choice, int *currency, string *currentAvatar, avatars ownedAvatar[50], avatars notOwnedAvatar[50], creatures ownedCreature[100], creatures notOwnedCreature[100]){
    string pageChoiceList[10] = {"10","1","2","3","4","5","6","7","8","9"};  //record the number of pages
    string viewChoiceList[10] = {"0","1","2","3","4","5","6","7","8","9"};
    string avatarStats[2] = {"  COST  "," METER  "};
    // battle menu
    if (choice=="battle"){
        cout << "\n = YOUR CURRENT AVATAR = \n";
        for (int i = 0; i < 50; i++){
            if (ownedAvatar[i].name == *currentAvatar){
                displayAvatarsOrCreatureDetails(ownedAvatar[i].index, "avatar.txt", avatarStats, 2);
                cout << endl;
                break;
            }
        }
    }
    // main menu
    if (choice=="main"){
        int pageCount = 1 ,maxPageCount = 8;  //maxPageCount can be changed depending on the number of avatars, try to not exceed single digit pages (more convenient?)
        char playersChoice[3] = "P1";
        cout << "\n = AVATARS MENU = \n\n";
        while (toupper(playersChoice[0])!='Q'){
            cout << "PAGE " << pageCount << endl;
            displayAvatarsOrCreaturesByPage(pageCount-1, "avatar.txt");
            cout << "\nPress V together with an avatar's number to view the avatar's stats. [Eg: V3 to view avatar 3]\n";
            cout << "Press P together with a page number to turn to that page. [Eg: P6 to skip to page 6]\n";
            cout << "Press Q to return to main menu. \n";
            cout << "Your choice: ";
            cin >> playersChoice;
            if (toupper(playersChoice[0])=='Q'){break;}
            while ((toupper(playersChoice[0]) != 'P' && toupper(playersChoice[0]) != 'V') || (toupper(playersChoice[0]) == 'P'  && find(pageChoiceList,end(pageChoiceList), string(playersChoice).substr(1)) == end(pageChoiceList)) || (toupper(playersChoice[0]) == 'V' && find(viewChoiceList,end(viewChoiceList), string(playersChoice).substr(1)) == end(viewChoiceList)) || cin.fail()){
                cin.clear();  
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "\x1B[31m" << "\nPress V together with an avatar's number to view the avatar's stats. [Eg: V3]\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Press P together with a page number to turn to that page. [Eg: P6]\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Press Q return to main menu.\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Your choice: "<< "\x1B[0m" ;
                cin >> playersChoice;
                if (toupper(playersChoice[0])=='Q'){break;}
            }
            switch (toupper(playersChoice[0])){
                case 'P':
                    pageCount = stoi(string(playersChoice).substr(1));
                    break;
                case 'V':
                    int avatarNumber;
                    avatarNumber = stoi(string(playersChoice).substr(1))+((pageCount-1)*10);
                    displayAvatarsOrCreatureDetails(avatarNumber, "avatar.txt", avatarStats, 2);
                    cout << "\nEnter R to return to avatar page: ";
                    cin >> playersChoice;
                    while (toupper(playersChoice[0]) != 'R'){
                        cout << "\x1B[31m" << "\nEnter R to return to avatar page: " << "\x1B[0m";
                        cin >> playersChoice;
                    }
                    break;
                case 'Q':
                    break;
            }
        }
    }
    // inventory menu
    if (choice=="inventory"){
        int count = 0, pageCount = 1 ,maxPageCount = 8;  //maxPageCount can be changed depending on the number of avatars, try to not exceed single digit pages (more convenient?)
        char playersChoice[3] = "P1";
        cout << "\n = YOUR AVATARS = \n";
        while (toupper(playersChoice[0])!='Q'){
            cout << "\n - Your Current Avatar : " << *currentAvatar << " -" << endl;
            cout << "\nPAGE " << pageCount << endl;
            displayOwnedAvatarsByPage(pageCount-1, ownedAvatar);
            cout << "\nPress V together with an avatar's number to view the avatar's stats. [Eg: V3 to view cavatar 3]\n";
            cout << "Press P together with a page number to turn to that page. [Eg: P6 to skip to page 6]\n";
            cout << "Press C together with an avatar's number to make that avatar your current avatar. [Eg: C5 to make avatar 5 your current avatar]\n";
            cout << "Press Q to return to inventory menu. \n";
            cout << "Your choice: ";
            cin >> playersChoice;
            if (toupper(playersChoice[0])=='Q'){break;}
            while ((toupper(playersChoice[0]) != 'P' && toupper(playersChoice[0]) != 'V' && toupper(playersChoice[0]) != 'C') || (toupper(playersChoice[0]) == 'C' && find(viewChoiceList,end(viewChoiceList), string(playersChoice).substr(1)) == end(viewChoiceList)) || (toupper(playersChoice[0]) == 'P'  && find(pageChoiceList,end(pageChoiceList), string(playersChoice).substr(1)) == end(pageChoiceList)) || (toupper(playersChoice[0]) == 'V' && find(viewChoiceList,end(viewChoiceList), string(playersChoice).substr(1)) == end(viewChoiceList)) || cin.fail() ){
                cin.clear();  
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "\x1B[31m" << "\nPress V together with an avatar's number to view the avatar's stats. [Eg: V3]\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Press P together with a page number to turn to that page. [Eg: P6]\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Press C together with an avatar's number to make that avatar your current avatar. [Eg: C5 to make avatar 5 your current avatar]\n" << "\x1B[0m" ;
                cout << "\x1B[31m" << "Press Q return to inventory menu.\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Your choice: "<< "\x1B[0m" ;
                cin >> playersChoice;
                if (toupper(playersChoice[0])=='Q'){break;}
            }
            switch (toupper(playersChoice[0])){
                case 'P':
                    pageCount = stoi(string(playersChoice).substr(1));
                    break;
                case 'V':
                    int avatarNumber;
                    avatarNumber = ownedAvatar[stoi(string(playersChoice).substr(1))+((pageCount-1)*10)].index;
                    if (avatarNumber==0){
                        cout << "\x1B[31m" << "\nInvalid input!\n" << "\x1B[0m";
                        break;
                    }
                    displayAvatarsOrCreatureDetails(avatarNumber, "avatar.txt", avatarStats, 2);
                    cout << "\nEnter R to return to avatar page: ";
                    cin >> playersChoice;
                    while (toupper(playersChoice[0]) != 'R'){
                        cout << "\x1B[31m" << "\nEnter R to return to avatar page: " << "\x1B[0m";
                        cin >> playersChoice;
                    }
                    break;
                case 'C':
                    int num, avatarIndex = stoi(string(playersChoice).substr(1))+((pageCount-1)*10); 
                    if (ownedAvatar[avatarIndex].name == *currentAvatar){
                        cout << "\x1B[31m" << "\nThis avatar is already your current avatar.\n" << "\x1B[0m";
			break;
                    }
                    else if (ownedAvatar[avatarIndex].name.empty()){
                        cout << "\x1B[31m" << "\nInvalid input!\n" << "\x1B[0m";
			break;
                    }
                    else if ((stoi(string(playersChoice).substr(1))>0 || stoi(string(playersChoice).substr(1))<11)){  
                        *currentAvatar = ownedAvatar[avatarIndex].name;  
                        cout << "\nYour avatar has been changed!\n";
			break;
                    }
                    else {cout << "\x1B[31m" << "Please enter your choice according to the instructions given. \n" << "\x1B[0m";}
                    break;
            }
        }
        //back to map
    }
    // shop menu
    if (choice=="shop"){
        int pageCount = 1, maxPageCount = 8;
        char playersChoice[3];
        cout << "\n = AVATARS SHOP = \n";
        while (toupper(playersChoice[0]) != 'Q'){
	    cout << "\nCOINS: " << *currency << endl;
            cout << "\nPAGE " << pageCount << endl;
            displayAvatarsNotOwnedByPage(pageCount-1, notOwnedAvatar);
            cout << "\nPress V together with an avatar's number to view the avatar's stats. [Eg: V3 to view avatar 3]\n";
            cout << "Press P together with a page number to turn to that page. [Eg: P6 to skip to page 6]\n";
            cout << "Press B together with an avatar's number to purchase that avatar. [Eg: B5 to buy avatar 5]\n";
            cout << "Press Q to return to shop menu. \n";
            cout << "Your choice: ";
            cin >> playersChoice;
            if (toupper(playersChoice[0])=='Q'){break;}
            while ((toupper(playersChoice[0]) != 'P' && toupper(playersChoice[0]) != 'V' && toupper(playersChoice[0]) != 'B') || (toupper(playersChoice[0]) == 'P'  && find(pageChoiceList,end(pageChoiceList), string(playersChoice).substr(1)) == end(pageChoiceList)) || (toupper(playersChoice[0]) == 'V' && find(viewChoiceList,end(viewChoiceList), string(playersChoice).substr(1)) == end(viewChoiceList)) || (toupper(playersChoice[0]) == 'B' && find(viewChoiceList,end(viewChoiceList), string(playersChoice).substr(1)) == end(viewChoiceList)) || cin.fail()){
                cin.clear();  
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "\x1B[31m" << "\nPress V together with an avatar's number to view the avatar's stats. [Eg: V3]\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Press P together with a page number to turn to that page. [Eg: P6]\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Press B together with an avatar's number to purchase it. [Eg: B5 to buy avatar 5]\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Press Q return to shop menu.\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Your choice: "<< "\x1B[0m" ;
                cin >> playersChoice;
                if (toupper(playersChoice[0])=='Q'){break;}
            }
            switch(toupper(playersChoice[0])){
                case 'P':
                    pageCount = stoi(string(playersChoice).substr(1));
                    break;
                case 'V':
                    int avatarNumber;
                    avatarNumber = notOwnedAvatar[stoi(string(playersChoice).substr(1))+((pageCount-1)*10)].index;
                    if (avatarNumber==0){
                        cout << "\x1B[31m" << "\nInvalid input!\n" << "\x1B[0m";
                        break;
                    }
                    displayAvatarsOrCreatureDetails(avatarNumber, "avatar.txt", avatarStats, 2);
                    cout << "\nEnter R to return to avatar page: ";
                    cin >> playersChoice;
                    while (toupper(playersChoice[0]) != 'R'){
                        cout << "\x1B[31m" << "\nEnter R to return to avatar page: " << "\x1B[0m";
                        cin >> playersChoice;
                    }
                    break;
                case 'B':
                    int buy = notOwnedAvatar[(stoi(string(playersChoice).substr(1))+(pageCount-1)*10)].index;
                    int cost = notOwnedAvatar[(stoi(string(playersChoice).substr(1))+(pageCount-1)*10)].cost;
                    if (buy==0){
                        cout << "\x1B[31m" << "\nInvalid input!\n" << "\x1B[0m";
                        break;
                    }
                    else if( *currency < cost){
                        cout << "\x1B[31m" << "You do not have enough coins to buy this avatar. \n" << "\x1B[0m";
                        break;
                    }
                    cout << "\x1B[31m" << "Are you sure that you want to purchase this avatar? [y/n] \n" << "\x1B[0m";
                    char toBuy;
                    cin >> toBuy;
                    while ((tolower(toBuy)!='y' && tolower(toBuy)!='n') || cin.fail()){  // havent see if enough money or not, use money > cost
                        cin.clear();  
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                        cout << "\x1B[31m" << "Please enter y or n to indicate your choice.\n" << "\x1B[0m";
                        cin >> toBuy;
                    }
                    if (toBuy=='y'){
                        changeOwnedAvatarsAndCreaturesTextFile(buy,"avatar",ownedCreature,notOwnedCreature,ownedAvatar,notOwnedAvatar);                          
			*currency = *currency - cost;
                        cout << "\nAvatar " << string(playersChoice).substr(1) << " has been purchased!\n";  //need to run the loadfromsavetxtfile function again since save txt is updated
                    }
                    break;
		}
            }
    }
}

// CARDS

// load all details of cards
void displayCardsDetail(int no){
    ifstream fin("card.txt");
    string line;
    while (getline(fin, line)){
        istringstream iss(line);
        int num;
        string str, name = "";
        string statList[] = {"   AREA    ","  REMOVE   ","COUNTERATK ","   HASTE   ","    ATK    ","   MAGIC   ","  SHIELD   "," ELIXIRSAP "," ADDELIXIR "," DRAWCARD  ",
                            "   HEAL    "," DIRECTDMG "," NICELAND  ","  THORNS   ","  HEROIC   ","  REVENGE  "," DEFENSEUP ","  POISON   ","   BLIND   ","  SILENCE  "," BLOCKCARD "};
        iss >> num;
        if (num == no){
            iss >> num;
            for (int i = 0; i < num; i++){
                iss >> str;
                if (name != ""){
                    name = name + " " + str;
                }
                else{
                    name += str;
                }
            }
            cout << "\n CARD NAME : " << name << endl;
            iss >> num;
            cout << " COST : " << num << endl;
            iss >> num;
            cout << " RARITY : " << num << endl << endl;
            for (int i = 0; i < 7; i++){
                int secondNum, thirdNum, fourthNum;
                iss >> secondNum >> thirdNum >> fourthNum;
                cout << statList[i*3] << ": " << setw(3) << secondNum << "      ";
                cout << statList[i*3+1] << ": " << setw(3) << thirdNum << "      ";
                cout << statList[i*3+2] << ": " << setw(3) << fourthNum << endl;
            }
            break;
        }
    }
    fin.close();
}

// display 10 cards each page, the parameter is the page of cards that player is viewing
void displayCardsByPage(int pageCount){
    cout << "No.           NAME" << endl;
    // get names of cards from card.txt
    ifstream fin("card.txt");
    string line;
    int count = 1;
    while (getline(fin, line) && count <= 10){
        istringstream iss(line);
        int no, lengthOfName;
        string str, name = "", outputName;
        iss >> no;
        if (no == (pageCount*10)+count){
            iss >> lengthOfName;
            for (int i = 0; i < lengthOfName; i++){
                iss >> str;
                if (name != ""){
                    name = name + " " + str;
                }
                else{
                    name += str;
                }
            }
            int space = (25-name.length())/2;
            outputName = string(space,' ')+name+string(space,' ');
            cout << setw(2) << count << '.' << setw(25) << outputName << endl;
            count++;
        }
    }
    fin.close();
}

// displays 10 cards each page for battlefield's cards menu
void displayCardsByPageInBattle(string cardArray[], int pageCount){
    for (int i = 0; i < 10; i++){
        // break if there's no more card to display
        if (cardArray[pageCount*10+i].empty()){
            break;
        }
        cout << i << ". " << cardArray[pageCount*10+i] << endl;
    }
}

// main cards displaying function, to display cards in battle, main menu, inventory and shop menu
void displayCards(string choice, string creaturesDeck[5], creatures ownedCreature[100]){
    string viewChoiceList[10] = {"1","2","3","4","5","6","7","8","9","10"};  
    string pageChoiceList[3] = {"1","2","3"};
   // battle menu
    if (choice=="battle"){
        string cardArray[25], playersChoice = "P1";
        int count = 0, cardCount = 0, pageCount = 1;
        cout << "\n = YOUR CARDS = \n";
        for (int i = 0; i < 100 && count < 5; i++){
            if (find(creaturesDeck, creaturesDeck+5, ownedCreature[i].name)!=creaturesDeck+5){
                for (int j = 0; j < 5; j++){
                    if (find(cardArray, end(cardArray), ownedCreature[i].cards[j])== end(cardArray)){
                        cardArray[cardCount] = ownedCreature[i].cards[j];
                        cardCount++;
                    }
                }
                count++;
            }
        }
        while (toupper(playersChoice[0])!='Q'){
            cout << "\nPAGE " << pageCount << endl;
            displayCardsByPageInBattle(cardArray, pageCount-1);
            cout << "\nPress V together with a card's number to view the card's stats. [Eg: V3 to view the card 3]\n";
            cout << "Press P together with a page number to turn to that page. [Eg: P6 to skip to page 6]\n";
            cout << "Press Q to return to battle menu. \n";
            cout << "Your choice: ";
            cin >> playersChoice;
            int flag = 0;
            if (toupper(playersChoice[0])=='Q'){break;}
            while ((toupper(playersChoice[0]) != 'P' && toupper(playersChoice[0]) != 'V') || cin.fail() || (toupper(playersChoice[0]) == 'P'  && find(pageChoiceList,end(pageChoiceList), string(playersChoice).substr(1)) == end(pageChoiceList)) || (toupper(playersChoice[0]) == 'V' && find(viewChoiceList,end(viewChoiceList), string(playersChoice).substr(1)) == end(viewChoiceList))){
                cin.clear();  
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "\n PAGE " << pageCount << endl;
                displayCardsByPage(pageCount-1);
                cout << "\x1B[31m" << "\nPress V together with a card's number to view the card's stats. [Eg: V3]\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Press P together with a page number to turn to that page. [Eg: P6]\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Press Q to return to battle menu.\n" << "\x1B[0m";
                cout << "Your choice: ";
                cin >> playersChoice;
                if (toupper(playersChoice[0])=='Q'){break;}
            }
            switch (toupper(playersChoice[0])){
                case 'P':
                    pageCount = stoi(string(playersChoice).substr(1));
                    break;
                case 'V':
                    int cardNumber, flag = 0, index, num;
                    string line, str;
                    ifstream fin("card.txt");
                    while (getline(fin, line)){
                        string name="";
                        istringstream iss(line);
                        iss >> index;
                        iss >> num;
                        for (int i = 0; i < num; i++){
                            iss >> str;
                            if (name != ""){
                                name = name + " " + str;
                            }
                            else{
                                name += str;
                            }
                        }
                        if (name == cardArray[stoi(string(playersChoice).substr(1))+((pageCount-1)*10)]){
                            cardNumber = index;
                            break;
                        }
                    }
                    displayCardsDetail(cardNumber);
                    cout << "\nEnter R to return to card page: ";
                    cin >> playersChoice;
                    while (toupper(playersChoice[0]) != 'R'){
                        cout << "\x1B[31m" << "\nEnter R to return to card page: " << "\x1B[0m";
                        cin >> playersChoice;
                    }
                    break;
            }
        }
    }
    // main menu 
    if (choice=="main"){
        int pageCount = 1 ,maxPageCount = 10;  //maxPageCount can be changed depending on the number of cards
        char playersChoice[3] = "P1";
        cout << "\n = CARDS MENU = \n\n";
        while (toupper(playersChoice[0])!='Q'){
            cout << "\nPAGE " << pageCount << endl;
            displayCardsByPage(pageCount-1);
            cout << "\nPress V together with a card's number to view the card's stats. [Eg: V3 to view the card 3]\n";
            cout << "Press P together with a page number to turn to that page. [Eg: P6 to skip to page 6]\n";
            cout << "Press Q to return to main menu. \n";
            cout << "Your choice: ";
            cin >> playersChoice;
            int flag = 0;
            if (toupper(playersChoice[0])=='Q'){break;}
            while ((toupper(playersChoice[0]) != 'P' && toupper(playersChoice[0]) != 'V') || cin.fail() || (toupper(playersChoice[0]) == 'P'  && find(viewChoiceList,end(viewChoiceList), string(playersChoice).substr(1)) == end(viewChoiceList)) || (toupper(playersChoice[0]) == 'V' && find(viewChoiceList,end(viewChoiceList), string(playersChoice).substr(1)) == end(viewChoiceList))){
                cin.clear();  
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "\n PAGE " << pageCount << endl;
                displayCardsByPage(pageCount-1);
                cout << "\x1B[31m" << "\nPress V together with a card's number to view the card's stats. [Eg: V3]\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Press P together with a page number to turn to that page. [Eg: P6]\n" << "\x1B[0m";
                cout << "\x1B[31m" << "Press Q to return to main menu.\n" << "\x1B[0m";
                cout << "Your choice: ";
                cin >> playersChoice;
                if (toupper(playersChoice[0])=='Q'){break;}
            }
            switch (toupper(playersChoice[0])){
                case 'P':
                    pageCount = stoi(string(playersChoice).substr(1));
                    break;
                case 'V':
                    int cardNumber;
                    cardNumber = stoi(string(playersChoice).substr(1))+((pageCount-1)*10);
                    displayCardsDetail(cardNumber);
                    cout << "\nEnter R to return to card page: ";
                    cin >> playersChoice;
                    while (toupper(playersChoice[0]) != 'R'){
                        cout << "\x1B[31m" << "\nEnter R to return to card page: " << "\x1B[0m";
                        cin >> playersChoice;
                    }
                    break;
            }
        }
        //back to map
    }
    
}

// treasure chest
void treasureChest(int *currency, creatures ownedCreature[100], creatures notOwnedCreature[100], avatars ownedAvatar[50], avatars notOwnedAvatar[50]){
    char choice;
    int num;
    if (*currency < 10){
    	cout << "\x1B[31m" << "Sorry, you do not have enough coins to open the chest.\n" << "\x1B[0m";
	return;
    }
    cout << "\nCOINS: " << *currency << endl;
    cout << "\nWould you like to open a treasure chest? It will cost you 10 coins.\n";
    cout << "Your choice [y/n] : ";
    cin >> choice;
    while ((tolower(choice)!='y'&&tolower(choice)!='n')||cin.fail()){
    	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
    	cout << "\x1B[31m" << "\nCOINS: " << *currency << endl << "\x1B[0m" ;
	cout << "\x1B[31m" << "\nWould you like to open a treasure chest? It will cost you 10 coins.\n" << "\x1B[0m" ;
	cout << "\x1B[31m" << "Your choice : "<< "\x1B[0m" ;
	cin >> choice;
    }
    if (tolower(choice) == 'y'){
        *currency = *currency - 10;
	srand (time(NULL));
        num = rand() % 10 + 1;
        ifstream fin("creature.txt");
        string line;
        while (getline(fin, line)){
            int no, lengthOfName;
            string name="", str;
            istringstream iss(line);
            iss >> no;
	    cout << no << endl;
            if (no == num){
                iss >> lengthOfName;
                for (int i = 0; i < lengthOfName; i++){
                    iss >> str;
                    if (name != ""){
                        name = name + " " + str;
                    }
                    else{
                        name += str;
                    }
                }
                cout << "\nThe creature you have gotten is " << name << '.' << endl;
                int flag=0;
                for (int i = 0; i < 100; i++){
                    if (ownedCreature[i].index==num){
                        flag=1;
                        cout << "You already have this creature in your inventory. Better luck next time!\n";
                        break;
                    }
                }
                if (flag==0){
                    cout << "Congratulation! This new creature has been stored in your inventory. \n";
		    changeOwnedAvatarsAndCreaturesTextFile(num,"creature",ownedCreature,notOwnedCreature,ownedAvatar,notOwnedAvatar);
		}
	    }
	}
    }
}


// display inventory menu
void displayInventory(string *currentFile, creatures ownedCreature[100], avatars ownedAvatar[50], creatures notOwnedCreature[100], avatars notOwnedAvatar[50], int *currency, int currentCoordinate[2], string *currentMap, string *currentAvatar, string creaturesDeck[5]){
    int choice = 0;
    while (choice!=2){
        cout << "\n = INVENTORY = " << endl;
        cout << "\nWhat are you looking for?\n";
        cout << "0. View my avatars\n";
        cout << "1. View my creatures\n";
        cout << "2. Return to main menu\n";
        cout << "Your choice: ";
        cin >> choice;
        while (choice < 0 || choice > 2 || cin.fail()){
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "\x1B[31m" << "\nWhat are you looking for?\n";
            cout << "0. View my avatars\n";
            cout << "1. View my creatures\n";
            cout << "2. Return to main menu\n";
            cout << "Your choice: " << "\x1B[0m";
            cin >> choice;
        }
        switch (choice){
            case 0:
                displayAvatar("inventory", currency, currentAvatar, ownedAvatar, notOwnedAvatar, ownedCreature, notOwnedCreature);
                break;
            case 1:
                displayCreature("inventory", currency, creaturesDeck, ownedCreature, notOwnedCreature, ownedAvatar, notOwnedAvatar);
                break;
            case 2:
                mainMenuPage(currency, currentAvatar, creaturesDeck, currentFile, ownedCreature, ownedAvatar, notOwnedCreature, notOwnedAvatar, currentCoordinate, currentMap);
                break;
        }
    }
}

// display shop 
void shop(string *currentFile, creatures ownedCreature[100], avatars ownedAvatar[50], creatures notOwnedCreature[100], avatars notOwnedAvatar[50], int *currency, int currentCoordinate[2], string *currentMap, string *currentAvatar, string creaturesDeck[5]){
    int choice = 0;
    cout << "\n = SHOP = \n";
    while (choice != 3){
        cout << "\n0. Avatars\n";
        cout << "1. Creatures\n";
        cout << "2. Treasure chests\n";
        cout << "3. Return to main menu\n";
        cout << "What do you want to buy? Enter a number to choose: ";
        cin >> choice;
        while (choice > 3 || choice < 0 || cin.fail()){
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "\n0. Avatars\n";
            cout << "1. Creatures\n";
            cout << "2. Treasure chests\n";
            cout << "3. Return to main menu\n";
            cout << "Please enter a correct number to indicate your choice: ";
            cin >> choice;
        }
        switch (choice){
            case 0:
                displayAvatar("shop", currency, currentAvatar, ownedAvatar, notOwnedAvatar, ownedCreature, notOwnedCreature);
                break;
            case 1:
                displayCreature("shop", currency, creaturesDeck, ownedCreature, notOwnedCreature, ownedAvatar, notOwnedAvatar);
                break;
            case 2:
                treasureChest(currency, ownedCreature, notOwnedCreature, ownedAvatar, notOwnedAvatar);
                break;
            case 3:
                mainMenuPage(currency, currentAvatar, creaturesDeck, currentFile, ownedCreature, ownedAvatar, notOwnedCreature, notOwnedAvatar, currentCoordinate, currentMap);
                break;
        }
    }
}

void buildLinkedListOfOwnedCreatures (owned * &ownedhead, int newindex, int newlevel) {
    owned * newnode = new owned;
    newnode->index = newindex;
    newnode->level = newlevel;
    
    owned * currentnode = ownedhead;
    while (currentnode != NULL) {
        if (newindex <= currentnode->index) {
            if (newindex == currentnode->index) {
                if (newlevel >= currentnode->level) {
                    owned * previousnode = ownedhead;
                    while (previousnode->next != currentnode) {
                        previousnode = previousnode->next;
                    }
                    previousnode->next = newnode;
                    newnode->next = currentnode;
                    return;
                }
                else {
                    currentnode = currentnode->next;
                }
            }
            else {
                owned * previousnode = ownedhead;
                while (previousnode->next != currentnode) {
                    previousnode = previousnode->next;
                }
                previousnode->next = newnode;
                newnode->next = currentnode;
                return;
            }
        }
        else {
            currentnode = currentnode->next;
        }
    }
    if (currentnode == ownedhead) {
        ownedhead = newnode;
        newnode->next = NULL;
    }
    else {
        currentnode = ownedhead;
        while (currentnode->next != NULL) {
            currentnode = currentnode->next;
        }
        newnode->next = NULL;
        currentnode->next = newnode;
    }
    return;
}

void load(string filename, owned * &ownedhead, int avataridx[10], currency &currentcurrency, int currentCoordinate[2], string &currentMap, avatar &currentAvatar, creature deck[5]){
    int index, level;
    string line, trash;
    ifstream fin(filename);
    
    getline(fin, line);
    istringstream iss(line);
    iss >> trash;
    while (iss >> index) {
        iss >> level;
        buildLinkedListOfOwnedCreatures(ownedhead, index, level);
    }

    getline(fin, line);
    istringstream iss1(line);
    iss1 >> trash;
    while (iss1 >> index) {
        avataridx[index] = 1;
    }
   
    getline(fin, line);
    istringstream iss2(line);
    iss2 >> trash;
    int count = 0;
    while (iss2 >> index) {
        iss2 >> level;
        deck[count].setbasestats(index);
        deck[count].setcurrentstats(level);
        count ++;
    }
    /*for (int i = 0; i < 5; i++){
        iss >> no;
	cout << "no: " << no << endl;
	string name="", fullName="";
	for (int j = 0; j < no; j++){
	    iss >> name;
	    if (fullName == ""){
		fullName += name;
	    }
	    else {
	    	fullName = fullName + ' ' + name;
	    }
	 creaturesDeck[i] = fullName;
    	}
    }*/

    getline(fin, line);
    istringstream iss3(line);
    iss3 >> trash >> index;
    currentAvatar.set(index);

    getline(fin, line);
    istringstream iss4(line);
    iss4 >> trash;
    iss4 >> currentcurrency.coins;
    iss4 >> currentcurrency.food;
    iss4 >> currentcurrency.gems;

    getline(fin,line);
    istringstream iss5(line);
    iss5 >> trash >> currentMap;

    getline(fin, line);
    istringstream iss6(line);
    iss6 >> trash >> currentCoordinate[0] >> currentCoordinate[1];

    fin.close();
}

// to start a new game, initialize items that player has, set the avatar and creatures for players to start with
string newGame() {
    //string *file, int *currency, int currentCoordinate[2], string *currentMap, string *currentAvatar, string creaturesDeck[5]
    /**file = "", *currentMap = "map1.txt", *currentAvatar = "pantherman", *currency = 50, currentCoordinate[0] = 2, currentCoordinate[1] = 9;
    creaturesDeck[0] = "happy fish", creaturesDeck[1] = "happy polla", creaturesDeck[2] = "gg" , creaturesDeck[3] = "lol", creaturesDeck[4] = "ripperoni";
    cout << "\n\nHi there! Welcome to The Cardmaster!\n\n";
    cout << "These are the items you currently have in your inventory!\n";
    cout << "  COINS    : " << *currency << endl;
    cout << "  AVATAR   : " << *currentAvatar << endl;
    cout << " CREATURES : " << creaturesDeck[0] << ", " << creaturesDeck[1] << ", " << creaturesDeck[2] << ", " << creaturesDeck[3] << ", " << creaturesDeck[4]<< endl;
    ofstream fout("ownedAvatarsAndCreatures.txt");
    fout << "creature 1 2 3 4 5\n";
    fout << "avatar 1\n";
    fout.close();*/

    cout << "To start a new game, you need to create a save file to store the progress of your game." << endl;
    cout << "Please name your save file: " << endl;
    string filename;
    getline(cin, filename);
    cout << endl;
    cout << HIGHLIGHT << "Saving to " << filename << ".txt ..." << endl;
    
    ifstream fin ("txt/newgame.txt");
    string temp, total = "";
    while (getline(fin, temp)) {
        total = total + temp + "\n";
    }
    fin.close();

    string record = "txt/filenames.txt";
    ofstream fout;
    fout.open(record, ios::app);
    fout << filename << endl;
    fout.close();

    string fullfilename = "save/" + filename + ".txt";
    ofstream fout (fullfilename);
    fout << total;
    fout.close();

    delay(1);
    cout << HIGHLIGHT << "Success!" << endl;
    string trash;
    cout << GREEN << "Press enter to continue" << endl;
    cin >> trash;

    return fullfilename;
}

// for player to choose a file to load
string loadFileOption() {
    int count = 1;
    string name = "";
    string str;

    ifstream fin ("txt/filenames.txt");
    if (fin.fail()) {
        cout << RED  << "\nNo save file exists. Please start a new game.\n" << WHITE ;
        string filename = titleScreen();
        return filename;
    }
    while (getline(fin, name)){
        cout << setw(2) << count << ".  " << name << endl;
        count++;
    }
    cout << setw(2) << count << ".  " << "Exit to title screen" << endl;

    fin.close();
	
    int choice;
    cout << "Which file do you want to load? Enter a number to indicate your choice: ";
    cin >> choice;
    while (choice < 1 || choice > count || cin.fail()){
        cin.clear();  
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << RED << "Please enter a valid number: "<< WHITE ;
        cin >> choice;
    }

    if (choice == count) {
        string filename = titleScreen();
        return filename;
    }

    ifstream fin ("txt/filenames.txt");
    for (int i = 0; i < choice; i++) {
        getline(fin, name);
    }
    fin.close();

    cout << "Loading..." << endl;
    delay(1);

    string fullfilename = "save/" + name + ".txt";
    return fullfilename;
}

void saveGame(string &filename, owned * ownedhead, int avataridx[10], currency currentcurrency, int currentCoordinate[2], string currentMap, avatar &currentAvatar, creature deck[5]){
    int option;
    cout << endl;
    cout << "Do you wish to overwrite the existing file or save to a new file?" << endl;
    cout << "1: Overwrite" << endl;
    cout << "2. New file" << endl;
    cout << "Please enter a number: ";
    cin >> option;
    while (cin.fail() || (option != 1 && option != 2)) {
        cin.clear();  
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << RED << "Please enter a valid number: " << WHITE;
        cin >> option;
    }
    if (option == 2) {
        cout << "\nWhat would you like to name your new file? ";
        cin >> filename;
        ofstream fout("txt/filenames.txt",ios::app);
        fout << filename << endl;
        fout .close();

        filename = "save/" + filename + ".txt";
    }
    string line;
    ofstream fout(filename);

    fout << "creature";
    while (ownedhead != NULL) {
        fout << ' ' << ownedhead->index << ' ' << ownedhead->level;
        ownedhead = ownedhead->next;
    }
    fout << endl << "avatar";
    for (int i = 0; i < 10 && avataridx[i] != 0; i++){
        fout << ' ' << i+1;
    }
    fout << endl << "creaturesDeck";
    for (int i = 0; i < 5; i++){
        fout << ' ' << deck[i].getcreaturenumber() << ' ' << deck[i].getlevel();
	}
    fout << endl << "currentAvatar " << currentAvatar.getindex() << endl;
    fout << "currency " << currentcurrency.coins << ' ' << currentcurrency.food << ' ' << currentcurrency.gems << endl;
    fout << "currentMap " << currentMap << endl;
    fout << "currentCoordinate " << currentCoordinate[0] << ' ' << currentCoordinate[1] << endl;
    fout.close();

    cout << endl << HIGHLIGHT << "Progress saved successfully!"  << WHITE << endl << endl;
}

// main menu page
void mainMenuPage(int *currency, string *currentAvatar, string creaturesDeck[5] ,string *currentFile, creatures ownedCreature[100], avatars ownedAvatar[50], creatures notOwnedCreature[100], avatars notOwnedAvatar[50], int currentCoordinate[2], string *currentMap){
    cout << "\n = MENU PAGE = \n";
    int choice = 0;
    while (choice < 8){
        cout << "\n0. Avatars\n"; 
        cout << "1. Creatures\n";
        cout << "2. Cards\n";
        cout << "3. Inventory\n";
        cout << "4. Shop\n";
        cout << "5. Save Game\n";
        cout << "6. Exit Menu\n";
        cout << "7. Exit Game\n";
        cout << "What are you looking for? Enter a number to select. ";
        cin >> choice;
        while (choice>7 || choice<0 || cin.fail()){
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "\n0. Avatars\n";
            cout << "1. Creatures\n";
            cout << "2. Cards\n";
            cout << "3. Inventory\n";
            cout << "4. Shop\n";
            cout << "5. Save Game\n";
            cout << "6. Exit Menu\n";
            cout << "7. Exit Game\n";
            cout << "\x1B[31m" << "Please enter a correct number to indicate your choice. [0,1,2,3,4,5,6,7]\n" << "\x1B[0m" ;
            cin >> choice;
        }
        switch (choice) {
            case 0:
                displayAvatar("main", currency, currentAvatar, ownedAvatar, notOwnedAvatar, ownedCreature, notOwnedCreature);
                break;
            case 1:
                displayCreature("main", currency, creaturesDeck, ownedCreature, notOwnedCreature, ownedAvatar, notOwnedAvatar);
                break;
            case 2:
                displayCards("main", creaturesDeck, ownedCreature);
                break;
            case 3:
                displayInventory(currentFile, ownedCreature, ownedAvatar, notOwnedCreature, notOwnedAvatar, currency, currentCoordinate, currentMap, currentAvatar, creaturesDeck);
                break;
            case 4:
                shop(currentFile, ownedCreature, ownedAvatar, notOwnedCreature, notOwnedAvatar, currency, currentCoordinate, currentMap, currentAvatar, creaturesDeck);
                break;
            case 5:
		saveGame(currentFile, ownedCreature, ownedAvatar, currency, currentCoordinate, currentMap, currentAvatar, creaturesDeck);
		break;
	    case 6:
//                moveAroundMap(currency, currentAvatar, creaturesDeck , currentFile, ownedCreature, ownedAvatar, notOwnedCreature, notOwnedAvatar, currentCoordinate, currentMap);
                break;
            case 7:
                cout << "\x1B[31m" << "Are you sure that you want to quit the game? [y/n] \n" << "\x1B[0m";
                char toQuit;
                cin >> toQuit;
                while ((tolower(toQuit)!='y' && tolower(toQuit)!='n') || cin.fail()){
                    cin.clear();  
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "\x1B[31m" << "Please enter y or n to indicate your choice.\n" << "\x1B[0m";
                    cin >> toQuit;
                }
                if (toQuit=='y'){
                    saveGame(currentFile, ownedCreature, ownedAvatar, currency, currentCoordinate, currentMap, currentAvatar, creaturesDeck);
                }
                else { 
                    //return back to map 
                }
                break;
        }

    }
}

// menu page in battlefield
void inBattleMenuPage(int *currency, string *currentAvatar, string creaturesDeck[5] ,string *currentFile, creatures ownedCreature[100], avatars ownedAvatar[50], creatures notOwnedCreature[100], avatars notOwnedAvatar[50], int currentCoordinate[2], string *currentMap){
    cout << "\n = MENU PAGE = \n";
    int choice = 0;
    while (choice < 4){
        cout << "\n0. Avatar\n";
        cout << "1. Creatures\n";
        cout << "2. Cards\n";
        cout << "3. Exit Menu\n";
        cout << "4. Exit Battle\n";
        cout << "What are you looking for? Enter a number to select.\n";
        cin >> choice;
        while (choice>4 || choice<0 || cin.fail()){
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "\n0. Avatar\n";
            cout << "1. Creatures\n";
            cout << "2. Cards\n";
            cout << "3. Exit Menu\n";
            cout << "4. Exit Battle\n";
            cout << "\x1B[31m" << "Please enter a correct number to indicate your choice. [0,1,2,3,4]\n" << "\x1B[0m" ;
            cin >> choice;
        }
        switch (choice){
            case 0:
                // load player's current creature and its stats
                displayAvatar("battle", currency, currentAvatar, ownedAvatar, notOwnedAvatar, ownedCreature, notOwnedCreature);
                break;
            case 1:
                // load deck of creatures player brought to the battle
                displayCreature("battle", currency, creaturesDeck, ownedCreature, notOwnedCreature, ownedAvatar, notOwnedAvatar);
                break;
            case 2:
                // load cards that belong to the creatures brought to battle
                displayCards("battle",creaturesDeck, ownedCreature);
                break;
            case 3:
                // back to battle();
                break;
            case 4:
                cout << "\x1B[31m" << "Are you sure that you want to quit the current battle? [y/n] \n" << "\x1B[0m";
                char toQuit;
                cin >> toQuit;
                while ((tolower(toQuit)!='y' && tolower(toQuit)!='n') || cin.fail()){
                    cin.clear();  
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "\x1B[31m" << "Please enter y or n to indicate your choice.\n" << "\x1B[0m";
                    cin >> toQuit;
                }
                if (toQuit=='y'){
  //                  moveAroundMap(currency, currentAvatar, creaturesDeck , currentFile, ownedCreature, ownedAvatar, notOwnedCreature, notOwnedAvatar, currentCoordinate, currentMap);
                }
                else{
                    //return back to battle 
                }
                break;
        }
    }
}

