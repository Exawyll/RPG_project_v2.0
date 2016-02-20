#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"
#include "fight.h"
#include "usableItem.h"
#include "gameUtil.h"

#define NBR_POTIONS 3


void clean (char *chaine);
void purge_buffer(void);
int userInputInt();
char* userInputChar(char* string);

int main(int argc, char *argv[])
{
    Player *Hero = NewPlayer();
    //Player *Mob = NewPlayer();
    //menu_player(Hero);

    return(0);
}

/*void menuSelectPotion(){
        printf("Now you have 3 potions to add to your inventory, what will you choose ?\n(trick : you can have many of the same type)\n");
        printf("1 : HEALTH POTION (increase temporally 10 HP)\n");
        printf("2 : STRENGTH POTION (increase temporally 10 attack points)\n");
        printf("3 : DEFENSE POTION (increase temporally 10 defense points)\n");
        printf("4 : GHOST POTION (increase temporally 10 dodge points)\n");
        printf("(WARNING : if you enter a wrong input, you won't have ANY POTION !!!)");
    }

void addHealthPotion(Player *target){
    AddItem(target->inventory, HEALTH_POTION);
}
void addStrengthPotion(Player *target){
    AddItem(target->inventory, STRENGTH_POTION);
}
void addDefensePotion(Player *target){
    AddItem(target->inventory, DEFENSE_POTION);
}*/
