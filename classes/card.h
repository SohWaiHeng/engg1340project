#ifndef CARD_H
#define CARD_H

#include "status.h"
#include<string>

// define a struct 'card' as a data type to store cards
class card {
    public:
        void getfunction();
        void setcard(int cardno);

    private:
        status cardstatus;
        int cardnumber;
        int cardcost;
        std::string cardname;
};

#endif