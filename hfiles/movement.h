#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <string>

void printMap(std::string map);

bool checkForAlphabet(std::string nextPosition);

bool checkForWall(std::string nextPosition);

void changePositions(std::string blockArray[], int currentPositionX, int currentPositionY, int nextPositionX, int nextPositionY, std::string currentCharacter, std::string toReplaceOri, std::string toReplaceNew);

void getCoordinate(std::string currentBlock, char alphabet, int coordinate[2]);

void movement(char move, std::string currentBlock, std::string currentCharacter);

#endif