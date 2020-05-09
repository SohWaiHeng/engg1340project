#ifndef AVATAR_H
#define AVATAR_H

#include<string>

#include "card.h"

using namespace std;

// a class to store an avatar
class avatar {
    public:
        string getname() { return avatarname; };
        string getfigure() { return avatarfigure; };
        int getindex() { return avatarindex; };
        // initialise an avatar
        void set(int index);
        // draw a card from avatar
        card drawcard();
        card cardpool[5];

    private:
        int avatarindex;
        string avatarname;
        string avatarfigure;
};

#endif