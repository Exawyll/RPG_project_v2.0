#ifndef FIGHT_H_INCLUDED
#define FIGHT_H_INCLUDED

#include "player.h"
#include "mob.h"

int fightPlayerToMob(Player *target, Mob *mob);
int fightMobToPlayer(Mob *mob, Player *target);
void DisplayFightMenu ();
int calcPlayerRelDef (Player *target, int attack);
int calcMobRelDef (Mob *mob, int attack);

#endif // FIGHT_H_INCLUDED
