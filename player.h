#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "usableItem.h"
#include "stuffItem.h"
#include "equipment.h"

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
    DlistItem *inventory;
    DlistStuff *armory;
    StuffItem* build[6];
    int gold;
    int score;
    int level;
}Player;

Player* player_ctor(char[50], int health, int attack, int defense, int relDef, int dodge, int gold, int score);

// Function Prototype
void DisplayStats (Player *target);
void SetName(Player *target);
Player* NewPlayer();    // Creates player and sets class.
int setJob(Player* target);
void buildToStart(Player *target);
void menu_player(Player *target);
//Concern USABLE ITEMS
UsableItem createUsableItems(enum itemNumber);
void menuSelectPotion();
void init_inventory(Player* target);
void setPotionAtStart(Player *target);
void show_inventory(Player *target);
void useYourPotion(Player *target);
void deletePotion(Player *target);
//Concern STUFF ITEMS
void setStuffAtStart(Player *target);
void show_stuff(Player *target);
void set_equip(Player *target, int position);
//Concern Equipment
void initEqpt(Player *target);
void displayEqpt(Player *target);
void calcAttributesWithEqpt(Player *target);
int autoEquip(Player *target, StuffItem *toEquip);
void displayStatsPlayerWithEqpt(Player *target, int attack, int defense, int relDef);
int calcAbsDef(Player *target);
int calcRelDef(Player *target);
int calcAttack(Player *target);


#endif // PLAYER_H_INCLUDED
