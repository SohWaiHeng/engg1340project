#ifndef MENU_H
#define MENU_H

#include <string>
#include "structs.h"
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
void changeOwnedAvatarsAndCreaturesTextFile(int num, std::string choice, creatures ownedCreature[100], creatures notOwnedCreature[100], avatars ownedAvatar[50], avatars notOwnedAvatar[50]);
void loadFile(std::string *currentFile, int *currency, int currentCoordinate[2], std::string *currentMap, std::string *currentAvatar, std::string creaturesDeck[5]);
void loadFileOption(std::string *file, int *currency, int currentCoordinate[2], std::string *currentMap, std::string *currentAvatar, std::string creaturesDeck[5], creatures ownedCreature[100], creatures notOwnedCreature[100], avatars notOwnedAvatar[50], avatars ownedAvatar[50]);
void saveGame(std::string *currentFile, creatures ownedCreature[100], avatars ownedAvatar[50], int *currency, int currentCoordinate[2], std::string *currentMap, std::string *currentAvatar, std::string creaturesDeck[5]);
void newGame(std::string *file, int *currency, int currentCoordinate[2], std::string *currentMap, std::string *currentAvatar, std::string creaturesDeck[5]);

// display menus
void shop(std::string *currentFile, creatures ownedCreature[100], avatars ownedAvatar[50], creatures notOwnedCreature[100], avatars notOwnedAvatar[50], int *currency, int currentCoordinate[2], std::string *currentMap, std::string *currentAvatar,std::string creaturesDeck[5]);
void displayInventory(int *currency, std::string *currentAvatar, std::string creaturesDeck[5] , std::string *currentFile, creatures ownedCreature[100], avatars ownedAvatar[50],creatures notOwnedCreature[100], avatars notOwnedAvatar[50], int currentCoordinate[2],std::string *currentMap);
void mainMenuPage(int *currency, std::string *currentAvatar, std::string creaturesDeck[5] , std::string *currentFile, creatures ownedCreature[100], avatars ownedAvatar[50],creatures notOwnedCreature[100], avatars notOwnedAvatar[50], int currentCoordinate[2], std::string *currentMap);
void inBattleMenuPage(int *currency, std::string *currentAvatar, std::string creaturesDeck[5] , std::string *currentFile, creatures ownedCreature[100], avatars ownedAvatar[50],creatures notOwnedCreature[100], avatars notOwnedAvatar[50], int currentCoordinate[2], std::string *currentMap);

#endif
