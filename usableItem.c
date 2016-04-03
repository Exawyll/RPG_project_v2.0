#include <stdio.h>
#include <stdlib.h>

#include "usableItem.h"
#include "player.h"
#include "gameUtil.h"

#define NBR_POTIONS 3
#define POTION_LIFE 50
#define POTION_STRENGTH 10
#define POTION_DEFENSE 10
#define POTION_DODGE 10
#define TIME_EFFECT 3

//Constructor for Usable Items
UsableItem* usableItem_ctor(char* name, int id, char* description, int price, int timeEffect, int bonusHP, int bonusATT, int bonusDEFAbs, int bonusESQ)
{
    UsableItem* p = malloc(sizeof(UsableItem));
    p->name = name;
    p->id = id;
    p->description = description;
    p->price = price;
    p->timeEffect = timeEffect;
    p->bonusHP = bonusHP;
    p->bonusATT = bonusATT;
    p->bonusDEFAbs = bonusDEFAbs;
    p->bonusESQ = bonusESQ;
    return p;
}

//Allow to display correct info of list items
void printf_struct_item(UsableItem* item)
{
    //text to be sure the list can be empty without crashing
    if(item->name){
        printf("Name: %s\n",item->name);
        printf("     Effect: %s (for %d turns duration)\n",item->description, item->timeEffect);
        printf("     Price: %d\n",item->price);
    }

}

//Create a new list
DlistItem *useItem_new(void)
{
    DlistItem *p_new = malloc(sizeof *p_new);
    if (p_new != NULL)
    {
        p_new->length = 0;
        p_new->p_head = NULL;
        p_new->p_tail = NULL;
    }
    return p_new;
}

//Add element at the end of the list
DlistItem *useItem_append(DlistItem *p_list, UsableItem item)
{
    if (p_list != NULL)
    {
        struct node_item *p_new = malloc(sizeof *p_new);
        if (p_new != NULL)
        {
            p_new->item = item;
            p_new->p_next = NULL;
            if (p_list->p_tail == NULL)
            {
                p_new->p_prev = NULL;
                p_list->p_head = p_new;
                p_list->p_tail = p_new;
            }
            else
            {
                p_list->p_tail->p_next = p_new;
                p_new->p_prev = p_list->p_tail;
                p_list->p_tail = p_new;
            }
            p_list->length++;
        }
    }
    return p_list;
}

//This display the list of Usable Item
void useItem_display(DlistItem *p_list)
{
    if (p_list != NULL)
    {
        system("cls");

        printf("----------------------------------\n");
        printf("Welcome into your POTION INVENTORY\n");
        printf("----------------------------------\n");
        int i = 1;
        struct node_item *p_temp = p_list->p_head;
        while (p_temp != NULL)
        {
            printf("%d -> ", i);
            printf_struct_item(&p_temp->item);
            fflush(stdout);
            p_temp = p_temp->p_next;
            i++;
        }
    }
    printf("----------------------------------\n");
    printf("\n");
}

//Remove the first item regarding the item parameter
DlistItem *useItem_remove(DlistItem *p_list, UsableItem item)
{
    if (p_list != NULL)
    {
        struct node_item *p_temp = p_list->p_head;
        int found = 0;
        while (p_temp != NULL && !found)
        {
            if (&p_temp->item == &item)
            {
                if (p_temp->p_next == NULL)
                {
                    p_list->p_tail = p_temp->p_prev;
                    p_list->p_tail->p_next = NULL;
                }
                else if (p_temp->p_prev == NULL)
                {
                    p_list->p_head = p_temp->p_next;
                    p_list->p_head->p_prev = NULL;
                }
                else
                {
                    p_temp->p_next->p_prev = p_temp->p_prev;
                    p_temp->p_prev->p_next = p_temp->p_next;
                }
                free(p_temp);
                p_list->length--;
                found = 1;
            }
            else
            {
                p_temp = p_temp->p_next;
            }
        }
    }
    return p_list;
}

//Remove item with selected position
DlistItem *useItem_remove_id(DlistItem *p_list, int position)
{
    if (p_list != NULL)
    {
        struct node_item *p_temp = p_list->p_head;
        int i = 1;
        while (p_temp != NULL && i <= position)
        {
            if (position == i)
            {
                if (p_temp->p_next == NULL)
                {
                    p_list->p_tail = p_temp->p_prev;
                    if(p_list->length == 1)
                    {
                        p_list->p_tail = NULL;
                        p_list->p_head = NULL;
                    }
                    else
                    {
                        p_list->p_tail->p_next = NULL;
                    }
                }
                else if (p_temp->p_prev == NULL)
                {
                    p_list->p_head = p_temp->p_next;
                    p_list->p_head->p_prev = NULL;
                }
                else
                {
                    p_temp->p_next->p_prev = p_temp->p_prev;
                    p_temp->p_prev->p_next = p_temp->p_next;
                }
                free(p_temp);
                p_list->length--;
            }
            else
            {
                p_temp = p_temp->p_next;
            }
            i++;
        }
    }
    return p_list;
}

//Return current list size
size_t useItem_length(DlistItem *p_list)
{
    size_t ret = 0;
    if (p_list != NULL)
    {
        ret = p_list->length;
    }
    return ret;
}

//Return the type/id of the selected Usable Item from the list
int useItem_return_id(DlistItem *p_list, int position)
{
    if (p_list != NULL)
    {
        struct node_item *p_temp = p_list->p_head;
        int i = 1;
        while (p_temp != NULL && i <= position)
        {
            if (position == i)
            {
                UsableItem *monObjet;
                monObjet = &p_temp->item;
                return monObjet->id;
            }
            else
            {
                p_temp = p_temp->p_next;
            }
            i++;
        }
    }
    return -1;
}

// FIND ITEM
// Can't return 0 because it's interpreted as an int. Return NULL for functions
// that are supposed to return pointers.
//Return choosen item to a new list
int useItem_find_id(DlistItem *p_list, enum itemNumber number)
{
    int ret = 0;
    //DlistItem *ret = NULL;
    if (p_list != NULL)
    {
        struct node_item *p_temp = p_list->p_head;
        int found = 0;
        while (p_temp != NULL && !found)
        {
            UsableItem *monObjet;
            monObjet = &p_temp->item;
            if (monObjet->id == number)
            {
                ret = number;
                found = 1;
            }
            else
            {
                p_temp = p_temp->p_next;
            }
        }
    }
    return ret;
}

//region saving/loading
//Write the whole list in a file
void writeToFile_item(DlistItem *p_list){
    FILE *fptr;
    fptr=fopen("./list_item.txt","w+");

    UsableItem* item = malloc(sizeof(UsableItem));
    if (p_list != NULL)
    {
        struct node_item *p_temp = p_list->p_head;
        while (p_temp != NULL)
        {
            item = &p_temp->item;
            fwrite(item,sizeof(UsableItem),1,fptr);
            p_temp = p_temp->p_next;
        }
        printf("\n");
    }
    fclose(fptr);
}

//Read a list of structure to display it
DlistItem* readFromFile_item(){
    DlistItem *p_list = useItem_new();
    UsableItem* item = malloc(sizeof(UsableItem));
    FILE *fptr;

    fptr=fopen("./list_item.txt","r");

    if (fptr) {
        /* File was opened successfully. */

        /* Attempt to read element one by one */
        while (fread(item,sizeof(UsableItem),1,fptr) == 1) {
            useItem_append(p_list, *usableItem_ctor(item->name,item->id,item->description,item->price,item->timeEffect,item->bonusHP,item->bonusATT,item->bonusDEFAbs,item->bonusESQ));
        }
        printf("\n");
    }

    fclose(fptr);

    return p_list;
}
//endregion

//Generate the 4 available potions to start
UsableItem createUsableItems(enum itemNumber number)
{
    if(number == HEALTH_POTION){
        UsableItem health = *usableItem_ctor("HEALTH_POTION", HEALTH_POTION, "Heals 50 health points.", 50, 0, POTION_LIFE, 0, 0, 0);
        return health;
    }
    else if(number == STRENGTH_POTION){
        UsableItem strength = *usableItem_ctor("STRENGTH_POTION", STRENGTH_POTION, "Add 10 attack points.", 100, TIME_EFFECT, 0, POTION_STRENGTH, 0, 0);
        return strength;
    }
    else if(number == DEFENSE_POTION){
        UsableItem defense = *usableItem_ctor("DEFENSE_POTION", DEFENSE_POTION, "Add 10 defense points.", 100, TIME_EFFECT, 0, 0, POTION_DEFENSE, 0);
        return defense;
    }
    else if(number == GHOST_POTION){
        UsableItem ghost = *usableItem_ctor("GHOST_POTION", GHOST_POTION,"Add 10 dodge points.", 100, TIME_EFFECT, 0, 0, 0, POTION_DODGE);
        return ghost;
    }
}

//Display menu to select potions to start the game
void menuSelectPotion()
{
    printf("Now you have 3 potions to add to your inventory, what will you choose ?\n\n(trick : you can have many of the same type)\n\n");
    printf("1 : HEALTH POTION (increase 50 HP)\n");
    printf("2 : STRENGTH POTION (increase temporally 10 attack points)\n");
    printf("3 : DEFENSE POTION (increase temporally 10 defense points)\n");
    printf("4 : GHOST POTION (increase temporally 10 dodge points)\n\n");
    printf("(WARNING : if you enter a wrong input, you won't have ANY POTION !!!)\n");
}

//Add selected potions into the player inventory
void setPotionAtStart(Player *target)
{
    int choice = 0;
    int i = 0;

    target->inventory = useItem_new();
    menuSelectPotion();

    for(i = 0; i < NBR_POTIONS; i++){
        choice = userInputInt();
        switch(choice){
            case 1:
                useItem_append(target->inventory, createUsableItems(HEALTH_POTION));
                break;
            case 2:
                useItem_append(target->inventory, createUsableItems(STRENGTH_POTION));
                break;
            case 3:
                useItem_append(target->inventory, createUsableItems(DEFENSE_POTION));
                break;
            case 4:
                useItem_append(target->inventory, createUsableItems(GHOST_POTION));
                break;
            default:
                break;
        }
    }
    useItem_display(target->inventory);
}

//Display the inventory menu
int show_inventory(Player *target)
{
    int userChoice = 0;

    useItem_display(target->inventory);

    printf("1 : Use item\n2 : Delete item\n(press 0 to get back)\n");
    userChoice = userInputInt();

    //You can only use or delete an Item
    if(userChoice == 1){
        useYourPotion(target);
    }
    else if(userChoice == 2){
        deletePotion(target);
    }
    else if (userChoice == 0){
        return (0);
    }
    else{

        //Control the user input
        printf("Please choose only 1 or 2\n");
    }
    return (0);
}

//Deals with the use of a potion
void useYourPotion(Player *target)
{
    int userChoice = 0;
    int id = 0;
    printf("Select the item your want to USE by pressing the corresponding number :");
    userChoice = userInputInt();

    //Catch the type of potion the player wants to use
    id = useItem_return_id(target->inventory, userChoice);

    //Act depending on the type of the potion
    switch(id){
        case HEALTH_POTION:

            //Conditions depending on the health of the player
            if((target->health + POTION_LIFE) <= target->maxHP){
                target->health += POTION_LIFE;
                useItem_remove_id(target->inventory, userChoice);
            }

            //Cannot drink a potion if the health is full
            else if (target->health == target->maxHP){
                printf("Your life is full, you don't need health potion !");
                Sleep(1000);
            }

            //Cannot go over the maximum HP of the player
            else{
                target->health = target->maxHP;
                useItem_remove_id(target->inventory, userChoice);
            }
            break;

        //The three other potions have a time Effect to deal with
        case STRENGTH_POTION:

            //Cannot have more than one potion at a time
            if(target->potion == 0){

                //Call the time Effect potion
                handleTimeEffect(target, POTION_STRENGTH, 0, 0);
                useItem_remove_id(target->inventory, userChoice);
                target->potion = TIME_EFFECT+1;
            }
            else{
                printf("You can only have one potion at a time !\n");
                Sleep(2000);
            }
            break;
        case DEFENSE_POTION:
            if(target->potion == 0){
                handleTimeEffect(target, 0, POTION_DEFENSE, 0);
                useItem_remove_id(target->inventory, userChoice);
                target->potion = TIME_EFFECT+1;
            }
            else{
                printf("You can only have one potion at a time !\n");
                Sleep(2000);
            }
            break;
        case GHOST_POTION:
            if(target->potion == 0){
                handleTimeEffect(target, 0, 0, POTION_DODGE);
                useItem_remove_id(target->inventory, userChoice);
                target->potion = TIME_EFFECT+1;
            }
            else{
                printf("You can only have one potion at a time !\n");
                Sleep(2000);
            }
            break;
        default:
            break;
    }
    show_inventory(target);
}

//Function to deal the time Effect of potions
void handleTimeEffect(Player *player, int att, int def, int esq)
{

    //Static int to remember if the player already drink a potion
    static int attack = 0;
    static int defense = 0;
    static int dodge = 0;

    //If the function is called with at least one argument > 0, it's a new potion coming
    if(att > 0 || def > 0 || esq > 0){
        attack = att;
        defense = def;
        dodge = esq;

        //Increase the player attributes
        player->attack += attack;
        player->defense += defense;
        player->dodge += dodge;
    }

    //else if all the argument are 0, it's the end of the potion effect
    else{
        printf("Your potion effect disappear...\n");
        Sleep(2000);

        //Decrease the player attributes
        if(attack > 0){
            player->attack -= attack;
            attack = 0;
        }
        if(defense > 0){
            player->defense -= defense;
            defense = 0;
        }
        if(dodge > 0){
            player->dodge -= dodge;
            dodge = 0;
        }
    }
}

//Delete a potion from inventory
void deletePotion(Player *target)
{
    int userChoice = 0;
    printf("Select the item your want to DELETE by pressing the corresponding number :");
    userChoice = userInputInt();
    useItem_remove_id(target->inventory, userChoice);
}
