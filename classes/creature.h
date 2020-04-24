#ifndef CREATURE_H
#define CREATURE_H

#include "status.h"
#include "card.h"
#include<string>

// struct to store creatures' stats
struct stats {
    std::string name;
    std::string symbol;
    int lvl;
    int cost;
    int hp;
    int atk;
    int mgc;
    int crt;
};

/* define a class 'creature' as a data type to store creatures
    member variables:
        - creaturenumber: index no. of creature in creature.txt
        - creaturestatus: the creature's status in battle (eg: how many shields etc.)
        - base: base stats of the creature (the creature's status at level 1)
        - current: current stats of the creature (the creature's status at current level)
        - cardpool[]: the cards of the creature

    member functions:
        - setbasestats(): take in creaturenumber (index no. of creature in creature.txt) and set the variable 'base' to the stats recorded in the txt file
        - setcurrentstats(): take in the creature's level, calculate and set the variable 'current' to the stats of the creature based on its level
        - getcurrentstats(): print out the creature's current stats and its cards
        - getcreaturenumber(): returns index no. of the creature in creature.txt (eg: when saving, getcreaturenumber of all creatures the player has and store them in save.txt)
        - setstatus(): to be done
        - getstatus(): to be done
*/
class creature {
    public:
        int getcreaturenumber() { return creaturenumber; };

        int gethp() { return current.hp; };
        void decreasehp(int byhowmuch) { current.hp = current.hp - byhowmuch; };
        int gethpratio();

        int getatk(bool &critical);
        int getoriginalatk() { return current.atk; };

        int getmgc(bool &critical);
        int getoriginalmgc() { return current.mgc; };

        std::string getname() { return current.name; };
        int getcost() { return current.cost; };
        std::string getsymbol() { return current.symbol; };
        void getcurrentstats();

        void setbasestats(int creatureno);
        void setcurrentstats(int creaturelvl);
        
        void setstatus();
        void getstatus();

        void setdeployed(bool deployedbool) { deployed = deployedbool; };
        bool getdeployed() { return deployed; };

        card cardpool[5];

    private:
        int creaturenumber;
        stats base;
        stats current;
        status creaturestatus;
        bool deployed;
};

#endif