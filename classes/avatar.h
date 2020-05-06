#ifndef AVATAR_H
#define AVATAR_H

#include<string>
#include "card.h"
using namespace std;

class avatar {
    public:
        string getname() { return avatarname; };
        string getfigure() { return avatarfigure; };
        int getindex() { return avatarindex; };
        void set(int index);
        card drawcard();


    private:
        int avatarindex;
        string avatarname;
        string avatarfigure;
        card cardpool[5];
};

#endif