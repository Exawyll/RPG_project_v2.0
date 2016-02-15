#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <stdbool.h>
#include "usableItem.h"

// Classes are enumerated. WARRIOR = 0; RANGER = 1, etc.
typedef enum ClassEnum  {
    WARRIOR,
    RANGER,
    WIZARD,
} job;

typedef struct playerStructure {
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
}Player;

// Function Prototype
void DisplayStats (struct playerStructure *Target);
void SetName(Player *target);
Player* NewPlayer();    // Creates player and sets class.
int setJob(Player* target);
void buildToStart(Player *target);
void setPotionAtStart(Player *target);
void init_inventory(Player* target);

void setPotionAtStart(Player *target);

#endif // PLAYER_H_INCLUDED
