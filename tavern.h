#ifndef TAVERN_H_INCLUDED
#define TAVERN_H_INCLUDED

#include "stuffItem.h"
#include "usableItem.h"
#include "player.h"

//prototypes
DlistStuff *generateMercantStuff();
void printAmbianceText();
void waitMenuMercant(int i);
StuffItem *item_select_id(DlistStuff *p_list, int position);
DlistItem *generateMercantItem();
UsableItem *useItem_select_id(DlistItem *p_list, int position);
void printf_stuff_mercant(StuffItem* stuff);
void mercant_stuff_display(DlistStuff *p_list);
void printf_item_mercant(UsableItem* item);
void mercant_item_display(DlistItem *p_list);
void goToTavern(Player *player);
void buyNewStuff(Player *player);
void sellOldStuff(Player *player);
void buyNewPotions(Player *player);
void sellPotions(Player *player);

#endif // TAVERN_H_INCLUDED
