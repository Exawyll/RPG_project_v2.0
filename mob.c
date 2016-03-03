#include <stdio.h>
#include <stdlib.h>

#include "mob.h"
#include "mobRace.h"

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
    Mob* gobelin = mob_ctor(GOBELIN, 100, 3, 3, 1, 1);
    return gobelin;
}

Mob* createSkeleton(){
    Mob* skeleton = mob_ctor(SKELETON, 110, 4, 4, 2, 1);
    return skeleton;
}

Mob* createOrc(){
    Mob* orc = mob_ctor(ORC, 120, 5, 5, 2, 2);
    return orc;
}

Mob* createZombie(){
    Mob* zombie = mob_ctor(ZOMBIE, 130, 6, 6, 2, 2);
    return zombie;
}

Mob* createUrukai(){
    Mob* urukai = mob_ctor(URUKAI, 140, 7, 7, 3, 3);
    return urukai;
}

Mob* createTroll(){
    Mob* troll = mob_ctor(TROLL, 150, 8, 8, 4, 4);
    return troll;
}

Mob* createDragon(){
    Mob* dragon = mob_ctor(DRAGON, 170, 10, 10, 5, 5);
    return dragon;
}

// Takes a player as an argument and prints their name, health, and attack. Returns nothing.
void displayStatsMob(Mob *mob) {
    // We don't want to keep retyping all this.
    char* nameMob = setMobNames(mob->races);
    printf("Name: %s\nHealth: %d\n\n", nameMob, mob->health);
}
