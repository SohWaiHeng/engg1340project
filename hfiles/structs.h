#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

struct creatures{
    int index;
    std::string name;
    std::string symbol;
    std::string cards[5];
    int hp, cost, atk, mgc, crt;
};


struct avatars{
    int index;
    std::string name;
    std::string symbol;
    std::string cards[5];
    int cost, meter;
};


#endif
