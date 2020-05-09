#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <string>

using namespace std;

void printMap(std::string map);

void mapWithAvatarAndEnemy(std::string avatarSymbol, std::string enemySymbol, int avatarCoordinate[2], int enemyCoordinate[2], std::string currentBlock, std::string newBlock);

void getRandomCoordinateForEnemy(std::string currentBlock, int enemyCoordinate[2], int avatarCoordinate[2]);

bool checkForMapChange(std::string &currentBlock, int currentCoordinate[2], int &blockNum);

bool checkForAlphabet(std::string nextPosition);

bool checkForWall(std::string nextPosition);

void changePositions(std::string blockArray[], int currentPositionX, int currentPositionY, int nextPositionX, int nextPositionY, std::string toReplaceOri, std::string toReplaceNew);

void getCoordinate(std::string currentBlock, char alphabet, int coordinate[2]);

void movement(char move, std::string &newBlock, std::string currentCharacter, int &moveFlag);

void moveAroundMap(int avatarCoordinate[2], int enemyCoordinate[2], string &avatarSymbol, string &enemySymbol, string &currentBlock, string &newBlock, int &flag, string &battlemode, int enemyCoordinateArray[6][2]);

#endif
