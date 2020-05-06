#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <string>

#include "structs.h"

void printMap(std::string *map);

void mapWithAvatar(std::string *currentAvatar, std::string *avatarSymbol, avatars ownedAvatar[50], int currentCoordinate[2], std::string *currentBlock, std::string *newBlock);

bool checkForMapChange(std::string *currentBlock, int currentCoordinate[2], int *blockNum);

bool checkForAlphabet(std::string nextPosition);

bool checkForWall(std::string nextPosition);

void changePositions(std::string blockArray[], int currentPositionX, int currentPositionY, int nextPositionX, int nextPositionY, std::string currentCharacter, std::string toReplaceOri, std::string toReplaceNew);

void getCoordinate(std::string *currentBlock, char alphabet, int coordinate[2]);

void movement(char move, std::string *currentBlock, std::string *currentCharacter, int *moveFlag);

void moveAroundMap(int *currency, std::string *currentAvatar, std::string creaturesDeck[5] ,std::string *currentFile, creatures ownedCreature[100], avatars ownedAvatar[50], creatures notOwnedCreature[100], avatars notOwnedAvatar[50], int currentCoordinate[2], std::string *currentBlock, std::string *newBlock, std::string *avatarSymbol);

#endif
