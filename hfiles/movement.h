#ifndef MOVEMENT_H
#define MOVEMENT_H

#include<string>
#include "../classes/avatar.h"
using namespace std;

void printMap(string map);

void mapWithAvatar(string avatarSymbol, int currentCoordinate[2], string currentBlock, string newBlock);

bool checkForMapChange(string *currentBlock, int currentCoordinate[2], int *blockNum);

bool checkForAlphabet(std::string nextPosition);

bool checkForWall(std::string nextPosition);

void changePositions(std::string blockArray[], int currentPositionX, int currentPositionY, int nextPositionX, int nextPositionY, std::string currentCharacter, std::string toReplaceOri, std::string toReplaceNew);

void getCoordinate(string currentBlock, char input, int coordinate[2]);

void movement(char move, string &newBlock, string currentCharacter, int &moveFlag);

void moveAroundMap(avatar currentAvatar, int currentCoordinate[2], string &currentBlock, int &flag);

#endif
