#ifndef MOB_H_INCLUDED
#define MOB_H_INCLUDED

typedef struct mobStructure {
    int races;
    int health;
    int maxHP;
    int attack;
    int defense;
    int relDef;
    int dodge;
}Mob;
//Prototype of constructor for mob
Mob* mob_ctor(int races, int health, int maxHP, int attack, int defense, int relDef, int dodge);

//Prototype of functions
void createMobs();
void displayStatsMob(Mob *mob);
Mob* createGobelin();
Mob* createSkeleton();
Mob* createOrc();
Mob* createZombie();
Mob* createUrukai();
Mob* createTroll();
Mob* createDragon();

#endif // MOB_H_INCLUDED
