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

struct owned {
    int index;
    int level;
    owned * next;
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
        int getlevel() { return current.lvl; };

        int getcrt() { return current.crt; };
        int gethp() { return current.hp; };
        void decreasehp(int byhowmuch);
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
        
        void setstatus(std::string condition, int number);
        int getstatus(std::string condition);
        int getnumberofstatus() { return creaturestatus.numberofstatus; };

        void setdeployed(bool deployedbool) { deployed = deployedbool; };
        bool getdeployed() { return deployed; };

        void heal(int percentage);
        void counteratk(creature &attacker);
        void haste(bool start);
        void atk(int percentage);
        void magic(creature &target);
        void shield();
        void elixirsap(creature &target, int &elixir, bool attacking);
        void addelixir(int &elixir, int byHowMuch);
        void drawcard();
        void directdmg(int percentage);
        void thorns(int damage, creature attacker);
        void revenge(int store, bool release, creature &target);
        void defenseup(int &damage);
        void poison();
        void silence();
        void blockcard();

        card cardpool[5];

    private:
        int creaturenumber;
        stats base;
        stats current;
        statusEffect creaturestatus;
        bool deployed;
};

#endif