#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<fstream>
#include<sstream>
#include "avatar.h"
using namespace std;

void avatar::set(int index){
    int j = 0;
    ifstream fin ("classes/txt/avatar.txt");
    string line;
    while (j <= index) {
        getline(fin, line);
        j++;
    }
    fin.close();

    string word;
    int number;
    istringstream iss (line);
    iss >> number;
    avatarindex = number;
            
    string name = "";
    iss >> number;
    for (int i = 0; i < number; i++) {
        iss >> word;
        if (name == "") {
            name += word;
        }
        else {
            name = name + " " + word;
        }
    }
    avatarname = name;

    iss >> word;
    avatarfigure = word;

   for (int i = 0; i < 5; i++) {
        iss >> number;
        cardpool[i].setcard(number);
    }
}

card avatar::drawcard() {
    srand(time(NULL));
    return cardpool[(rand()%5)];
}