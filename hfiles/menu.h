#ifndef MENU_H
#define MENU_H

#include <string>
#include "../classes/avatar.h"
#include "../classes/creature.h"
#include "../classes/currency.h"
#include "titleScreen.h"
// CREATURES
void loadCreaturesFromSavedTextFile(creatures ownedCreature[100], creatures notOwnedCreature[100]);
void displayAvatarsOrCreaturesByPage(int pageCount, std::string file);
void displayAvatarsOrCreatureDetails(int no, std::string file, std::string stats[], int statsLength);
void displayOwnedCreaturesByPage(int pageCount);
void displayCreaturesNotOwnedByPage(int pageCount);
void displayCreature(std::string choice, int *currency, std::string creatureDeck[5], creatures ownedCreature[100], creatures notOwnedCreature[100], avatars ownedAvatar[50], avatars notOwnedAvatar[50]);

// AVATARS
void loadAvatarsFromSavedTextFile(avatars ownedAvatar[50], avatars notOwnedAvatar[50]);
void displayOwnedAvatarsByPage(int pageCount);
void displayAvatarsNotOwnedByPage(int pageCount);
void displayAvatar(std::string choice, int *currency, std::string *currentAvatar, avatars ownedAvatar[50], avatars notOwnedAvatar[50], creatures ownedCreature[100], creatures notOwnedCreature[100]);

// CARDS
void displayCardsDetail(int no);
void displayCardsByPage(int pageCount);
void displayCardsByPageInBattle(std::string cardArray[], int pageCount);
void displayCards(std::string choice,std:: string creaturesDeck[5], creatures ownedCreature[100]);

// TREASURE CHEST
void treasureChest(creatures ownedCreature[100], creatures notOwnedCreature[100], avatars ownedAvatar[50], avatars notOwnedAvatar[50]);

// save and load
void buildLinkedListOfOwnedCreatures (owned * &ownedhead, int newindex, int newlevel);
void load(string filename, owned * &ownedhead, int avataridx[10], currency &currentcurrency, int currentCoordinate[2], string &currentMap, avatar &currentAvatar, creature deck[5]);
string loadFileOption();
void save(string filename, owned * ownedhead, int avataridx[10], currency currentcurrency, int currentCoordinate[2], string currentMap, avatar currentAvatar, creature deck[5]);
string newGame();

// display menus
void shop(std::string *currentFile, creatures ownedCreature[100], avatars ownedAvatar[50], creatures notOwnedCreature[100], avatars notOwnedAvatar[50], int *currency, int currentCoordinate[2], std::string *currentMap, std::string *currentAvatar,std::string creaturesDeck[5]);
void displayInventory(int *currency, std::string *currentAvatar, std::string creaturesDeck[5] , std::string *currentFile, creatures ownedCreature[100], avatars ownedAvatar[50],creatures notOwnedCreature[100], avatars notOwnedAvatar[50], int currentCoordinate[2],std::string *currentMap);
void mainMenuPage(int *currency, std::string *currentAvatar, std::string creaturesDeck[5] , std::string *currentFile, creatures ownedCreature[100], avatars ownedAvatar[50],creatures notOwnedCreature[100], avatars notOwnedAvatar[50], int currentCoordinate[2], std::string *currentMap);
void inBattleMenuPage(int *currency, std::string *currentAvatar, std::string creaturesDeck[5] , std::string *currentFile, creatures ownedCreature[100], avatars ownedAvatar[50],creatures notOwnedCreature[100], avatars notOwnedAvatar[50], int currentCoordinate[2], std::string *currentMap);

#endif
