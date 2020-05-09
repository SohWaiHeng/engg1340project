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

// stuct to store player's owned creatures in game
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
        // get creature's index number in creature.txt
        int getcreaturenumber() { return creaturenumber; };
        int getlevel() { return current.lvl; };

        int getcrt() { return current.crt; };
        int gethp() { return current.hp; };
        void decreasehp(int byhowmuch);
        int gethpratio();
        
        // obtain atk value with critical possibility included
        int getatk(bool &critical);
        // obatin raw atk value
        int getoriginalatk() { return current.atk; };

        // obtain mgc value with critical possibility included
        int getmgc(bool &critical);
        // obtain raw mgc value
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

        // sets deployed value to true if creature is deployed onto field
        void setdeployed(bool deployedbool) { deployed = deployedbool; };
        bool getdeployed() { return deployed; };

        // heal by n percentage
        void heal(int percentage);
        // counterattack the attacker
        void counteratk(creature &attacker);
        // cost -1, parameter 'start' indicates if haste value -1 at the start of a round (true = -1)
        void haste(bool start);
        // atk increase by n percentage
        void atk(int percentage);
        // attack the target with damage of mgc value
        void magic(creature &target);
        // negate damage
        void shield();
        // saps elixir from target creatues, by n elixir, if the creature is attacking (true)
        void elixirsap(creature &target, int &elixir, bool attacking);
        // adds current elixir, by byHowMuch
        void addelixir(int &elixir, int byHowMuch);
        // draw a card from creature
        void directdmg(int percentage);
        // reflects the damage back to attacker
        void thorns(int damage, creature attacker);
        // stores damage in one turn, release all damage in revenger attack if release = true, target to revenge on)
        void revenge(int store, bool release, creature &target);
        // reduce 30% damage
        void defenseup(int &damage);
        // reduce n percent hp based on poison percentage of a creature
        void poison();

        card cardpool[5];

    private:
        int creaturenumber;
        stats base;
        stats current;
        statusEffect creaturestatus;
        bool deployed;
};

#endif