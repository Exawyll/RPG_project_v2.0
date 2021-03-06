#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#include "tavern.h"
#include "player.h"
#include "gameUtil.h"

#define NBR_WEAPON_MERCANT 12

//Prototype for the Main menu
void displayMainMenu(Player *player);

//Menu entrance in a tavern with all the things you can do
void goToTavern(Player *player)
{
    int userChoice = 0;

    system("cls");
    color(14, 0);

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
    printf("5 - Back in Town...\n");
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
        case 5:
            displayMainMenu(player);
            break;
        default:
            printf("Please, enter a correct entry !\n");
            Sleep(1000);
            goToTavern(player);
            break;
    }
}

//The stuffItem merchant is generated randomly
DlistStuff *generateMercantStuff()
{
    int i = 0;
    DlistStuff *armory = item_new();

    for(i = 0; i < NBR_WEAPON_MERCANT; i++){

        //The Sleep function is used to slow down the program in order to generate different numbers with the random function
        Sleep(1000);
        item_append(armory, *generateWeapon());
        waitMenuMercant(i);
    }
    mercant_stuff_display(armory);
    return armory;
}

//Text displayed during the merchant generation in order to occupy the user
void printAmbianceText()
{
    printf("Hello young hero, hard time to get new stuff with the infested caves\nall around us... But I've got something for you right here\nplease have a look and choose carefully what you need :\n\n");
    printf("Please wait for the generation of the market place");
}

//Tricky menu to display dots like if the program is loading something
void waitMenuMercant(int i)
{
    system("cls");
    if(i%3 == 0){
        printAmbianceText();
        printf(".\n\n");
    }
    else if((i - 1)%3 == 0){
        printAmbianceText();
        printf("..\n\n");
    }
    else{
        printAmbianceText();
        printf("...\n\n");
    }
}

//Return stuffitem with selected position
StuffItem *item_select_id(DlistStuff *p_list, int position)
{
    if (p_list != NULL)
    {
        int i = 1;
        struct node_stuff *p_temp = p_list->p_head;
        while (p_temp != NULL)
        {
            if(i == position){
                return &p_temp->stuff;
            }
            else{
                p_temp = p_temp->p_next;
                i++;
            }
        }
    }
    return NULL;
}

//Function allowing to buy new StuffItem is user have enough gold
void buyNewStuff(Player *player){
    DlistStuff *mercant;
    int objectToBuy = -1;
    StuffItem *objectBought;
    int badChoice = 0;

    //Generate the merchant
    mercant = generateMercantStuff();

    //Infinite loop until the user call the tavern menu
    while(objectToBuy){

        printf("*** YOUR GOLD : %d PO ***\n",player->gold);

        //Control user input
        if(badChoice == 0){
            printf("Please, select the weapon you want to buy : (press 0 to exit)\n");
        }

        objectToBuy = userInputInt();

        //Control the user to not crash the later lists functions
        while(objectToBuy > mercant->length){
            printf("Please select an existing weapon !!!\n");
            objectToBuy = userInputInt();
        }

        //Option to return to the tavern
        if(objectToBuy == 0){
            goToTavern(player);
        }

        //Return the StuffItem the user wants to buy
        objectBought = item_select_id(mercant, objectToBuy);

        //Check if user have enough gold
        if(objectBought->price > player->gold || badChoice == 1){
            printf("\n\nSorry, buddy you don't have enough coins, get richer and come back\n");
            printf("or buy cheaper... (press 0 to exit)\n\n\n");
            badChoice = 1;
        }
        else{
            //If he can buy
            //Decrease the gold amount
            player->gold -= objectBought->price;

            //insert the StuffItem in armory
            item_append(player->armory, *objectBought);

            //Remove it from the merchant
            item_remove_id(mercant, objectToBuy);

            //Display the merchant he wants to buy more
            mercant_stuff_display(mercant);
        }
    }
}

//Function to sell your old stuff
void sellOldStuff(Player *player)
{
    int objectToSell = -1;
    StuffItem *objectSold;

    system("cls");

    item_display(player->armory);

    while(objectToSell){

        printf("*** YOUR GOLD : %d PO ***\n",player->gold);

        printf("Please, select the weapon you want to sell : (press 0 to exit)\n");

        objectToSell = userInputInt();

        //Control the user to not crash the later lists functions
        while(objectToSell > player->armory->length || objectToSell < 0){
            printf("Please select an existing weapon !!!\n");
            objectToSell = userInputInt();
        }

        if(objectToSell == 0){
            goToTavern(player);
        }

        objectSold = item_select_id(player->armory, objectToSell);

        //Increase the gold
        player->gold += objectSold->price;

        //Remove the stuffItem from the player
        item_remove_id(player->armory, objectToSell);

        //Display the new armory to sell more
        item_display(player->armory);
    }
}

//Generate the Item merchant with the 4 available potions
DlistItem *generateMercantItem()
{
    DlistItem *potions = useItem_new();

    useItem_append(potions, createUsableItems(HEALTH_POTION));
    useItem_append(potions, createUsableItems(STRENGTH_POTION));
    useItem_append(potions, createUsableItems(DEFENSE_POTION));
    useItem_append(potions, createUsableItems(GHOST_POTION));

    mercant_item_display(potions);
    return potions;
}

//Remove item with selected position
UsableItem *useItem_select_id(DlistItem *p_list, int position)
{
    if (p_list != NULL)
    {
        int i = 1;
        struct node_item *p_temp = p_list->p_head;
        while (p_temp != NULL)
        {
            if(i == position){
                return &p_temp->item;
            }
            else{
                p_temp = p_temp->p_next;
                i++;
            }
        }
    }
    return NULL;
}

//Function to buy new potions
void buyNewPotions(Player *player)
{
    int objectToBuy = -1;
    UsableItem *objectBought;
    DlistItem *mercant = generateMercantItem();
    int badChoice = 0;

    while(objectToBuy){

        printf("*** YOUR GOLD : %d PO ***\n",player->gold);

        if(badChoice == 0){
            printf("Please, select the potion you want to buy : (press 0 to exit)\n");
        }

        objectToBuy = userInputInt();

        //Control the user to not crash the later lists functions
        while(objectToBuy > mercant->length){
            printf("Please select an existing potion !!!\n");
            objectToBuy = userInputInt();
        }

        if(objectToBuy == 0){
            goToTavern(player);
        }

        objectBought = useItem_select_id(mercant, objectToBuy);

        if(objectBought->price > player->gold || badChoice == 1){
            printf("\n\nSorry, buddy you don't have enough coins, get richer and come back\n");
            printf("or buy cheaper... (press 0 to exit)\n\n\n");
            badChoice = 1;
        }
        else{
            player->gold -= objectBought->price;
            useItem_append(player->inventory, *objectBought);
            mercant_item_display(mercant);
        }
    }
}

//Function to sell potions
void sellPotions(Player *player)
{
    int potionToSell = -1;
    UsableItem *potionSold;

    system("cls");

    useItem_display(player->inventory);

    while(potionToSell){

        printf("*** YOUR GOLD : %d PO ***\n",player->gold);

        printf("Please, select the potion you want to sell : (press 0 to exit)\n");

        potionToSell = userInputInt();

        //Control the user to not crash the later lists functions
        while(potionToSell > player->inventory->length || potionToSell < 0){
            printf("Please select an existing weapon !!!\n");
            potionToSell = userInputInt();
        }

        if(potionToSell == 0){
            goToTavern(player);
        }

        potionSold = useItem_select_id(player->inventory, potionToSell);

        player->gold += potionSold->price;
        useItem_remove_id(player->inventory, potionToSell);
        useItem_display(player->inventory);
    }
}

//Allow to display correct info of list items
void printf_stuff_mercant(StuffItem* stuff)
{
    if(stuff->name)
    {
        printf("%s   Price : %d", stuff->name, stuff->price);
        printf("   ATT : +%d   DEFRel : +%d   DEF : +%d\n\n", stuff->I_bonusATT, stuff->I_bonusDEFRel, stuff->I_bonusDEFAbs);
    }
}

//This display the list of StuffItems for the merchant
void mercant_stuff_display(DlistStuff *p_list)
{
    system("cls");

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
            printf_stuff_mercant(&p_temp->stuff);
            fflush(stdout);
            p_temp = p_temp->p_next;
            i++;
        }
    }
    printf("---------------------------------------------------------------------\n");
    printf("\n");
}

//Allow to display correct info of list items
void printf_item_mercant(UsableItem* item)
{
    printf("%s   Price : %d\n", item->name, item->price);
    if(item->timeEffect > 0){
        printf("     Effect : %s FOR : %d turns\n\n", item->description, item->timeEffect);
    }
    else{
        printf("     Effect : %s\n\n", item->description);
    }

}

//This display the list of Usable Item from the merchant
void mercant_item_display(DlistItem *p_list)
{
    system("cls");

    if (p_list != NULL)
    {
        printf("---------------------------------------------------------------------\n");
        printf("                Welcome into the market for POTIONS\n");
        printf("---------------------------------------------------------------------\n");
        int i = 1;
        struct node_item *p_temp = p_list->p_head;
        while (p_temp != NULL)
        {
            printf("%d -> ", i);
            printf_item_mercant(&p_temp->item);
            fflush(stdout);
            p_temp = p_temp->p_next;
            i++;
        }
    }
    printf("---------------------------------------------------------------------\n");
    printf("\n");
}
