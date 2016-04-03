#ifndef DUNGEON_H_INCLUDED
#define DUNGEON_H_INCLUDED

#include "player.h"
#include "mob.h"

//prototypes
void goThroughDungeon(Player *player);
int calculateNomberOfMob(Player *player);
void switchDungeons(Player *player);
int choiceInDungeon();
void researchInDungeon(Player *player);
Mob* generateMob(Player *player);
int choiceInDungeon();

#endif // DUNGEON_H_INCLUDED
