#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "usableItem.h"
#include "stuffItem.h"
#include "equipment.h"
#include "mob.h"

// Classes are enumerated. WARRIOR = 0; RANGER = 1, etc.
typedef enum ClassEnum  {
    WARRIOR,
    RANGER,
    WIZARD,
} job;

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
    DlistStuff *armory;
    StuffItem* build[6];
    int gold;
    int score;
    int level;
    int life;
    int nbrKills;
}Player;

Player* player_ctor(char[50], int health, int attack, int defense, int relDef, int dodge, int gold, int score, int level, int life, int nbrKills, int maxHP);

// Function Prototype
void DisplayStats (Player *target);
void SetName(Player *target);
Player* NewPlayer();    // Creates player and sets class.
int setJob(Player* target);
void buildToStart(Player *target);
int menu_player(Player *target, int callingPlace);
//Concern USABLE ITEMS
UsableItem createUsableItems(enum itemNumber);
void menuSelectPotion();
void init_inventory(Player* target);
void setPotionAtStart(Player *target);
int show_inventory(Player *target);
void useYourPotion(Player *target);
void deletePotion(Player *target);
//Concern STUFF ITEMS
void setStuffAtStart(Player *target);
void show_stuff(Player *target);
//void set_equip(Player *target, int position);
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
//Concern Dungeon
Mob* generateMob(Player *player);
int choiceInDungeon();
void researchInDungeon(Player *player);
void switchDungeons(Player *player);
int calculateNomberOfMob(Player *player);
void goThroughDungeon(Player *player);
//Concern Tavern
void goToTavern(Player *player);
DlistStuff *generateMercantStuff();
void printAmbianceText();
void waitMenuMercant(int i);
StuffItem *item_select_id(DlistStuff *p_list, int position);
void buyNewStuff(Player *player);
void sellOldStuff(Player *player);
DlistItem *generateMercantItem();
UsableItem *useItem_select_id(DlistItem *p_list, int position);
void buyNewPotions(Player *player);
void sellPotions(Player *player);
void printf_stuff_mercant(StuffItem* stuff);
void mercant_stuff_display(DlistStuff *p_list);
void printf_item_mercant(UsableItem* item);
void mercant_item_display(DlistItem *p_list);

#endif // PLAYER_H_INCLUDED
