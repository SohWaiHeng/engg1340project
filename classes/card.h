#ifndef CARD_H
#define CARD_H

#include "status.h"
#include<string>

// define a class 'card' as a data type to store cards
class card {
    public:
        void getfunction();
        int getrarity() { return cardrarity; };
        int getcardnumber() { return cardnumber; };
        std::string getname() { return cardname; };
        void cardDrawn() { cardrarity--; };
        void setcard(int cardno);
        int getcost() { return cardcost; };
        int getnamelength() { return cardnamelength; };

    private:
        status cardstatus;
        int cardnumber;
        int cardcost;
        std::string cardname;
        int cardnamelength;
        int cardrarity;
};

#endif