#ifndef MOB_H_INCLUDED
#define MOB_H_INCLUDED

// Races of mobs are enumerated.
typedef enum RacesEnum  {
    GOBELIN,
    ORC,
    URUKAI,
    TROLL,
    DRAGON
} races;

typedef struct monsterStructure {
    char name[50];
    int health;
    int attack;
    int defense;
    int relDef;
    int dodge;
    int job;
    bool autoPilot;
    DlistItem *inventory;
    DlistStuff *armory;
    StuffItem* build[6];
}Monster;

#endif // MOB_H_INCLUDED
