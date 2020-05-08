#ifndef MENU_H
#define MENU_H

#include <string>

#include "../classes/avatar.h"
#include "../classes/creature.h"
#include "../classes/currency.h"
#include "titleScreen.h"

//CREATURES 
void displayCreatureByPage(int pageCount, owned * ownedhead);
void displayCreatureDetails (int index, int level);
void displayCreature(string choice, owned * ownedhead, creature deck[5], currency &currentcurrency);

// AVATARS
void displayAvatarByPage(int avataridx[]);
void displayAvatarDetails (int index);

// TREASURE CHEST
void treasureChest(currency &currentcurrency, owned * &ownedhead);

// save and load
void buildLinkedListOfOwnedCreatures (owned * &ownedhead, int newindex, int newlevel, bool &own);
void load(string filename, owned * &ownedhead, int avataridx[10], currency &currentcurrency, int currentCoordinate[2], string &currentMap, avatar &currentAvatar, creature deck[5], int enemycoordinate[2]);
string loadFileOption(int &option);
void save(string &filename, owned * ownedhead, int avataridx[10], currency currentcurrency, int currentCoordinate[2], string currentMap, avatar currentAvatar, creature deck[5], int enemycoordinate[2]);
string newGame();

// display menus
void shop(owned * &ownedhead, int avataridx[], currency &currentcurrency);
void displayInventory(creature deck[5], owned * ownedhead, int avataridx[], currency currentcurrency, avatar currentavatar);
void mainMenuPage(currency &currentcurrency, avatar &currentavatar, creature deck[5], string &filename, owned * ownedhead, int avataridx[10], int currentcoordinate[2], string currentMap, int &flag, int enemycoordinate[2]);

#endif
