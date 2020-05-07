#ifndef MENU_H
#define MENU_H

#include <string>
#include "../classes/avatar.h"
#include "../classes/creature.h"
#include "../classes/currency.h"
#include "titleScreen.h"
// CREATURES
//void loadCreaturesFromSavedTextFile(creatures ownedCreature[100], creatures notOwnedCreature[100]);
void displayCreatureByPage(int pageCount, owned * ownedhead);
void displayCreatureDetails (int index, int level);
//void displayAvatarsOrCreatureDetails(int no, std::string file, std::string stats[], int statsLength);
//void displayOwnedCreaturesByPage(int pageCount);
//void displayCreaturesNotOwnedByPage(int pageCount);
void displayCreature(string choice, owned * ownedhead, creature deck[5], currency &currentcurrency);

// AVATARS
//void loadAvatarsFromSavedTextFile(avatars ownedAvatar[50], avatars notOwnedAvatar[50]);
void displayAvatarByPage(int avataridx[]);
void displayAvatarDetails (int index);
//void displayOwnedAvatarsByPage(int pageCount);
//void displayAvatarsNotOwnedByPage(int pageCount);
//void displayAvatar(std::string choice, int *currency, std::string *currentAvatar, avatars ownedAvatar[50], avatars notOwnedAvatar[50], creatures ownedCreature[100], creatures notOwnedCreature[100]);

// CARDS
//void displayCardsDetail(int no);
//void displayCardsByPage(int pageCount);
//void displayCardsByPageInBattle(std::string cardArray[], int pageCount);
//void displayCards(std::string choice,std:: string creaturesDeck[5], creatures ownedCreature[100]);

// TREASURE CHEST
void treasureChest(currency &currentcurrency, owned * &ownedhead);

// save and load
void buildLinkedListOfOwnedCreatures (owned * &ownedhead, int newindex, int newlevel, bool &own);
void load(string filename, owned * &ownedhead, int avataridx[10], currency &currentcurrency, int currentCoordinate[2], string &currentMap, avatar &currentAvatar, creature deck[5]);
string loadFileOption(int &option);
void save(string &filename, owned * ownedhead, int avataridx[10], currency currentcurrency, int currentCoordinate[2], string currentMap, avatar currentAvatar, creature deck[5]);
string newGame();

// display menus
void shop(owned * &ownedhead, int avataridx[], currency &currentcurrency);
void displayInventory(creature deck[5], owned * ownedhead, int avataridx[], currency currentcurrency, avatar currentavatar);
void mainMenuPage(currency &currentcurrency, avatar &currentavatar, creature deck[5], string &filename, owned * ownedhead, int avataridx[10], int currentcoordinate[2], string currentMap, bool &quit);
//void inBattleMenuPage(int *currency, std::string *currentAvatar, std::string creaturesDeck[5] , std::string *currentFile, creatures ownedCreature[100], avatars ownedAvatar[50],creatures notOwnedCreature[100], avatars notOwnedAvatar[50], int currentCoordinate[2], std::string *currentMap);

#endif
