#include <stdio.h>
#include <stdlib.h>

#include "mob.h"
#include "mobRace.h"

#define MOB_LIFE 90
#define MOB_ATT 10
#define MOB_DEF 7
#define MOB_RELDEF 2
#define MOB_DODGE 3

//Constructor for mobs
Mob* mob_ctor(int races, int health, int maxHP, int attack, int defense, int relDef, int dodge)
{
    Mob* p = malloc(sizeof(Mob));
    p->races = races;
    p->health = health;
    p->attack = attack;
    p->defense = defense;
    p->relDef = relDef;
    p->dodge = dodge;
    p->maxHP = maxHP;
    return p;
}

//Gobelin generator
Mob* createGobelin()
{
    Mob* gobelin = mob_ctor(GOBELIN, MOB_LIFE, MOB_LIFE, MOB_ATT, MOB_DEF,MOB_RELDEF, MOB_DODGE);
    return gobelin;
}

//Skeleton generator
Mob* createSkeleton()
{
    Mob* skeleton = mob_ctor(SKELETON, MOB_LIFE+10, MOB_LIFE+10, MOB_ATT+5, MOB_DEF+5,MOB_RELDEF+1, MOB_DODGE+1);
    return skeleton;
}

//Orc generator
Mob* createOrc()
{
    Mob* orc = mob_ctor(ORC, MOB_LIFE+20, MOB_LIFE+20, MOB_ATT+6, MOB_DEF+6,MOB_RELDEF+2, MOB_DODGE+2);
    return orc;
}

//Zombie generator
Mob* createZombie()
{
    Mob* zombie = mob_ctor(ZOMBIE, MOB_LIFE+30, MOB_LIFE+30, MOB_ATT+10, MOB_DEF+7,MOB_RELDEF+3, MOB_DODGE+3);
    return zombie;
}

//Urukai generator
Mob* createUrukai()
{
    Mob* urukai = mob_ctor(URUKAI, MOB_LIFE+40, MOB_LIFE+40, MOB_ATT+20, MOB_DEF+8,MOB_RELDEF+4, MOB_DODGE+4);
    return urukai;
}

//Troll generator
Mob* createTroll()
{
    Mob* troll = mob_ctor(TROLL, MOB_LIFE+50, MOB_LIFE+50, MOB_ATT+30, MOB_DEF+9,MOB_RELDEF+5, MOB_DODGE+5);
    return troll;
}

//Dragon generator
Mob* createDragon()
{
    Mob* dragon = mob_ctor(DRAGON, MOB_LIFE+60, MOB_LIFE+60, MOB_ATT+40, MOB_DEF+10,MOB_RELDEF+6, MOB_DODGE+6);
    return dragon;
}
