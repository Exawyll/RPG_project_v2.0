#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "stuffItem.h"
#include "usableItem.h"

// Classes are enumerated. WARRIOR = 0; RANGER = 1, etc.
typedef enum ClassEnum  {
    WARRIOR,
    RANGER,
    WIZARD,
} job;

//The most important player structure that store all the player data
typedef struct playerStructure {
    char name[50];
    int maxHP;
    int health;
    int attack;
    int defense;
    int relDef;
    int dodge;
    int job;
    DlistItem *inventory;
    int potion;
    DlistStuff *armory;
    StuffItem* build[6];
    int gold;
    int score;
    int level;
    int life;
    int nbrKills;
    int nbrDungeons;
}Player;

//Constructor prototype
Player* player_ctor(char[50], int maxHP, int health, int attack, int defense, int relDef, int dodge, int potion, int gold, int score, int level, int life, int nbrKills, int nbrDungeons);

// Function Prototype for Player.c
void SetName(Player *target);
Player* NewPlayer();
int setJob(Player* target);
void buildToStart(Player *target);
int menu_player(Player *target, int callingPlace);
char* setJobNames(int job);

//Concern USABLE ITEMS
void init_inventory(Player* target);
void setPotionAtStart(Player *target);
int show_inventory(Player *target);
void useYourPotion(Player *target);
void deletePotion(Player *target);
void handleTimeEffect(Player *player, int att, int def, int esq);

//Concern STUFF ITEMS
void setStuffAtStart(Player *target);
void show_stuff(Player *target);
void unEquip(Player *target, int typeStuff);
int autoEquip(Player *target, StuffItem *toEquip);

//Concern Equipment
void initEqpt(Player *target);
void displayEqpt(Player *target);
void calcAttributesWithEqpt(Player *target);
int autoEquip(Player *target, StuffItem *toEquip);
void displayStatsPlayerWithEqpt(Player *target, int attack, int defense, int relDef);
int calcAbsDef(Player *target);
int calcRelDef(Player *target);
int calcAttack(Player *target);
void displayEqptMenu(Player* player);
void writeToFile_eqpt(StuffItem** build);
StuffItem** readFromFile_eqpt();

//Concern Dungeon
/*Mob* generateMob(Player *player);
void researchInDungeon(Player *player);
void switchDungeons(Player *player);
int calculateNomberOfMob(Player *player);
void goThroughDungeon(Player *player);*/

//Concern Tavern
/*void goToTavern(Player *player);
void buyNewStuff(Player *player);
void sellOldStuff(Player *player);
void buyNewPotions(Player *player);
void sellPotions(Player *player);*/

#endif // PLAYER_H_INCLUDED
