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

void createMobs(){
    Mob* gobelin = mob_ctor(GOBELIN, 10, 3, 3, 1, 1);
    Mob* squelet = mob_ctor(SQUELET, 10, 4, 4, 2, 1);
    Mob* orc = mob_ctor(ORC, 20, 5, 5, 2, 2);
    Mob* zombie = mob_ctor(ZOMBIE, 30, 6, 6, 2, 2);
    Mob* urukai = mob_ctor(URUKAI, 40, 7, 7, 3, 3);
    Mob* troll = mob_ctor(TROLL, 50, 8, 8, 4, 4);
    Mob* dragon = mob_ctor(DRAGON, 70, 10, 10, 5, 5);
}
