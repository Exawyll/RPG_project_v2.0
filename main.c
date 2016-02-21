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
    //Hero->build[HELMET] = 0;
    /*Hero->build[ARMOR] = stuffItem_ctor("Textile Armor", 10, ARMOR, 0, 0, 1, 10);
    //Hero->build[LEFT_HAND] = 0;
    Hero->build[RIGHT_HAND] = stuffItem_ctor("My First Sword", 10, RIGHT_HAND, 0, 10, 0, 0);
    //Hero->build[LEGGINGS] = 0;
    //Hero->build[BOOTS] = 0;*/
    /*int i = 0;
    for(i = 0; i < 6; i++){
        Hero->build[i] = 0;
        printf("Name : %s\n", Hero->build[i]->name);
        if(Hero->build[i] != 0){
            printf("Name : %s\n", Hero->build[i]->name);
            Hero->attack += Hero->build[i]->I_bonusATT;
            Hero->health += Hero->build[i]->I_bonusHP;
            Hero->defense += Hero->build[i]->I_bonusDEFAbs;
            Hero->relDef += Hero->build[i]->I_bonusDEFRel;
        }
    }*/
    DisplayStats(Hero);


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
