#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#include "tavern.h"
#include "player.h"
#include "gameUtil.h"

#define NBR_WEAPON_MERCANT 12

void goToTavern(Player *player){
    int userChoice = 0;

    system("cls");

    printf("################################\n");
    printf("#                              #\n");
    printf("#    WELCOME TO THE TAVERN     #\n");
    printf("#                              #\n");
    printf("################################\n\n");

    printf("Here is all you can do there :\n");
    printf("1 - Buy new stuff\n");
    printf("2 - Sell old stuff\n");
    printf("3 - Buy new potions\n");
    printf("4 - Sell potions\n");
    userChoice = userInputInt();

    switch(userChoice)
    {
        case 1:
            buyNewStuff(player);
            break;
        case 2:
            sellOldStuff(player);
            break;
        case 3:
            buyNewPotions(player);
            break;
        case 4:
            sellPotions(player);
            break;
        default:
            printf("Please, enter a correct entry !\n");
            break;
    }
}

void generateMercantStuff(){
    int i = 0;
    DlistStuff *armory = item_new();

    for(i = 0; i < NBR_WEAPON_MERCANT; i++){
        Sleep(1000);
        item_append(armory, *generateWeapon());
        waitMenuMercant(i);
    }
    system("cls");
    mercant_display(armory);
}

void waitMenuMercant(int i){
    system("cls");
    if(i == 0 || i == 3 || i == 6 || i == 9){
        printf("Hello young hero, hard time to get new stuff with the infested caves\nall around us... But I've got something for you right here\nplease have a look and choose carefully what you need :\n\n");
        printf("Please wait for the generation of the market place.\n\n");
    }
    else if(i == 1 || i == 4 || i == 7){
        printf("Hello young hero, hard time to get new stuff with the infested caves\nall around us... But I've got something for you right here\nplease have a look and choose carefully what you need :\n\n");
        printf("Please wait for the generation of the market place..\n\n");
    }
    else{
        printf("Hello young hero, hard time to get new stuff with the infested caves\nall around us... But I've got something for you right here\nplease have a look and choose carefully what you need :\n\n");
        printf("Please wait for the generation of the market place...\n\n");
    }
}

void buyNewStuff(Player *player){
    generateMercantStuff();
    printf("*** YOUR GOLD : %d PO ***\n",player->gold);
}

void sellOldStuff(Player *player){
}

void buyNewPotions(Player *player){
}

void sellPotions(Player *player){
}

//Allow to display correct info of list items
void printf_struct_mercant(StuffItem* stuff)
{
    if(stuff->name)
    {
        printf("Name : %s   Price : %d", stuff->name, stuff->price);
        printf("   ATT : +%d   DEFRel : +%d   DEF : +%d\n\n", stuff->I_bonusATT, stuff->I_bonusDEFRel, stuff->I_bonusDEFAbs);
    }
}

//This display the list
void mercant_display(DlistStuff *p_list)
{
    if (p_list != NULL)
    {
        printf("---------------------------------------------------------------------\n");
        printf("                Welcome into the market for STUFF\n");
        printf("---------------------------------------------------------------------\n");
        int i = 1;
        struct node_stuff *p_temp = p_list->p_head;
        while (p_temp != NULL)
        {
            printf("%d -> ", i);
            printf_struct_mercant(&p_temp->stuff);
            fflush(stdout);
            p_temp = p_temp->p_next;
            i++;
        }
    }
    printf("---------------------------------------------------------------------\n");
    printf("\n");
}
