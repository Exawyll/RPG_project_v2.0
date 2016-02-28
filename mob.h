#ifndef MOB_H_INCLUDED
#define MOB_H_INCLUDED

typedef struct mobStructure {
    int races;
    int health;
    int attack;
    int defense;
    int relDef;
    int dodge;
}Mob;
//Prototype of constructor for mob
Mob* mob_ctor(int races, int health, int attack, int defense, int relDef, int dodge);

//Prototype of functions
void createMobs();
void displayStatsMob(Mob *mob);
#endif // MOB_H_INCLUDED
