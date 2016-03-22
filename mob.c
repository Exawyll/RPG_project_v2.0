#include <stdio.h>
#include <stdlib.h>

#include "mob.h"
#include "mobRace.h"

#define MOB_LIFE 100
#define MOB_ATT 5
#define MOB_DEF 5
#define MOB_RELDEF 1
#define MOB_DODGE 1

Mob* mob_ctor(int races, int health, int attack, int defense, int relDef, int dodge){
    Mob* p = malloc(sizeof(Mob));
    p->races = races;
    p->health = health;
    p->attack = attack;
    p->defense = defense;
    p->relDef = relDef;
    p->dodge = dodge;
    return p;
}

Mob* createGobelin(){
    Mob* gobelin = mob_ctor(GOBELIN, MOB_LIFE, MOB_ATT, MOB_DEF,MOB_RELDEF, MOB_DODGE);
    return gobelin;
}

Mob* createSkeleton(){
    Mob* skeleton = mob_ctor(SKELETON, MOB_LIFE+10, MOB_ATT+5, MOB_DEF+5,MOB_RELDEF+1, MOB_DODGE+1);
    return skeleton;
}

Mob* createOrc(){
    Mob* orc = mob_ctor(ORC, MOB_LIFE+20, MOB_ATT+6, MOB_DEF+6,MOB_RELDEF+2, MOB_DODGE+2);
    return orc;
}

Mob* createZombie(){
    Mob* zombie = mob_ctor(ZOMBIE, MOB_LIFE+30, MOB_ATT+7, MOB_DEF+7,MOB_RELDEF+3, MOB_DODGE+3);
    return zombie;
}

Mob* createUrukai(){
    Mob* urukai = mob_ctor(URUKAI, MOB_LIFE+40, MOB_ATT+8, MOB_DEF+8,MOB_RELDEF+4, MOB_DODGE+4);
    return urukai;
}

Mob* createTroll(){
    Mob* troll = mob_ctor(TROLL, MOB_LIFE+50, MOB_ATT+9, MOB_DEF+9,MOB_RELDEF+5, MOB_DODGE+5);
    return troll;
}

Mob* createDragon(){
    Mob* dragon = mob_ctor(DRAGON, MOB_LIFE+60, MOB_ATT+10, MOB_DEF+10,MOB_RELDEF+6, MOB_DODGE+6);
    return dragon;
}

// Takes a player as an argument and prints their name, health, and attack. Returns nothing.
void displayStatsMob(Mob *mob) {
    // We don't want to keep retyping all this.
    char* nameMob = setMobNames(mob->races);
    printf("Name: %s\nHealth: %d\n\n", nameMob, mob->health);
}
