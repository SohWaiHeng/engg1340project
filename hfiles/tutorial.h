#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <string>

#include "movement.h"
#include "battle.h"

void movementTutorial(int avatarCoordinate[2], int enemyCoordinate[2], std::string &avatarSymbol, std::string &enemySymbol, std::string &currentBlock, std::string &newBlock);

void battleTutorial(creature deck[5], bool &winlose, opponent currentopponent);

void tutorial(int avatarCoordinate[2], int enemyCoordinate[2], std::string &avatarSymbol, std::string &enemySymbol, std::string &currentBlock, std::string &newBlock, opponent &currentopponent, bool &winlose, creature deck[5]);

#endif
