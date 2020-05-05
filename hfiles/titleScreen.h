#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <string>
#include "structs.h"


//inline creatures *ownedCreature = new creatures[100];
//inline creatures *notOwnedCreature = new creatures[100];
//inline avatars *ownedAvatar = new avatars[50];
//inline avatars *notOwnedAvatar = new avatars[50];

extern creatures ownedCreature[100];
extern creatures notOwnedCreature[100];
extern avatars ownedAvatar[50];
extern avatars notOwnedAvatar[50];

void printTitleScreen();

void titleScreen(std::string *file, int *currency, int currentCoordinate[2], std::string *currentMap, std::string *currentAvatar, std::string creaturesDeck[5], creatures ownedCreature[100], creatures  notOwnedCreature[100], avatars ownedAvatar[50], avatars notOwnedAvatar[50] );

int main();

#endif
