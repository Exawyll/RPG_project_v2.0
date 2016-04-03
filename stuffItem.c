#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "stuffItem.h"
#include "player.h"
#include "equipment.h"
#include "gameUtil.h"

//Constructor for to create a stuffItem
StuffItem* stuffItem_ctor(char* name, int price, int type, int I_bonusATT, int I_bonusDEFRel, int I_bonusDEFAbs)
{
    StuffItem* p = malloc(sizeof(StuffItem));
    p->name = name;
    p->price = price;
    p->type = type;
    p->I_bonusATT = I_bonusATT;
    p->I_bonusDEFRel = I_bonusDEFRel;
    p->I_bonusDEFAbs = I_bonusDEFAbs;
    return p;
}

//Allow to display correct info of list items
void printf_struct_stuff(StuffItem* stuff)
{
    //text to be sure the list can be empty without crashing
    if(stuff->name)
    {
        printf("Name : %s\n     Price : %d\n", stuff->name, stuff->price);
        int type = stuff->type;
        switch(type){
            case HELMET:
                printf("     Type : HELMET\n");
                break;
            case ARMOR:
                printf("     Type : ARMOR\n");
                break;
            case RIGHT_HAND:
                printf("     Type : RIGHT_HAND\n");
                break;
            case LEFT_HAND:
                printf("     Type : LEFT_HAND\n");
                break;
            case LEGGINGS:
                printf("     Type : LEGGINGS\n");
                break;
            case BOOTS:
                printf("     Type : BOOTS\n");
                break;
        }
        printf("     ATT : +%d\n     DEFRel : +%d\n     DEF : +%d\n\n", stuff->I_bonusATT, stuff->I_bonusDEFRel, stuff->I_bonusDEFAbs);
    }
}

//Create a new list
DlistStuff *item_new(void)
{
    DlistStuff *p_new = malloc(sizeof *p_new);
    if (p_new != NULL)
    {
        p_new->length = 0;
        p_new->p_head = NULL;
        p_new->p_tail = NULL;
    }
    return p_new;
}

//Add element at the end of the list
DlistStuff *item_append(DlistStuff *p_list, StuffItem stuff)
{
    if (p_list != NULL)
    {
        struct node_stuff *p_new = malloc(sizeof *p_new);
        if (p_new != NULL)
        {
            p_new->stuff = stuff;
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

//This display the list
void item_display(DlistStuff *p_list)
{
    if (p_list != NULL)
    {
        system("cls");

        printf("---------------------------------\n");
        printf("Welcome into your STUFF INVENTORY\n");
        printf("---------------------------------\n");
        int i = 1;
        struct node_stuff *p_temp = p_list->p_head;
        while (p_temp != NULL)
        {
            printf("%d -> ", i);
            printf_struct_stuff(&p_temp->stuff);
            fflush(stdout);
            p_temp = p_temp->p_next;
            i++;
        }
    }
    printf("---------------------------------\n");
    printf("\n");
}

//Remove the first item regarding the stuff parameter
DlistStuff *item_remove(DlistStuff *p_list, StuffItem stuff)
{
    if (p_list != NULL)
    {
        struct node_stuff *p_temp = p_list->p_head;
        int found = 0;
        while (p_temp != NULL && !found)
        {
            if (&p_temp->stuff == &stuff)
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
DlistStuff *item_remove_id(DlistStuff *p_list, int position)
{
    if (p_list != NULL)
    {
        struct node_stuff *p_temp = p_list->p_head;
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
size_t item_length(DlistStuff *p_list)
{
    size_t ret = 0;
    if (p_list != NULL)
    {
        ret = p_list->length;
    }
    return ret;
}

//Return the StuffItem at the specified position
StuffItem *item_return_stuff(DlistStuff *p_list, int position)
{
    if (p_list != NULL)
    {
        struct node_stuff *p_temp = p_list->p_head;
        int i = 1;
        while (p_temp != NULL && i <= position)
        {
            if (position == i)
            {
                StuffItem *monObjet;
                monObjet = &p_temp->stuff;
                return monObjet;
            }
            else
            {
                p_temp = p_temp->p_next;
            }
            i++;
        }
    }
}

//region saving/loading
//Write the whole list in a file
void writeToFile_stuff(DlistStuff *p_list){
    FILE *fptr;
    fptr=fopen("./list_stuff.txt","w+");

    StuffItem* stuff = malloc(sizeof(StuffItem));
    if (p_list != NULL)
    {
        struct node_stuff *p_temp = p_list->p_head;
        while (p_temp != NULL)
        {
            stuff = &p_temp->stuff;
            fwrite(stuff,sizeof(StuffItem),1,fptr);
            p_temp = p_temp->p_next;
        }
        printf("\n");
    }
    fclose(fptr);
}

//Read a list of structure to display it
DlistStuff* readFromFile_stuff(){
    DlistStuff *p_list = item_new();
    StuffItem* stuff = malloc(sizeof(StuffItem));
    FILE *fptr;

    fptr=fopen("./list_stuff.txt","r");

    if (fptr) {
        /* File was opened successfully. */

        /* Attempt to read element one by one */
        while (fread(stuff,sizeof(StuffItem),1,fptr) == 1) {
            item_append(p_list, *stuffItem_ctor(stuff->name, stuff->price, stuff->type, stuff->I_bonusATT, stuff->I_bonusDEFRel, stuff->I_bonusDEFAbs));
        }
        printf("\n");
    }

    fclose(fptr);

    return p_list;
}
//endregion

//Give the stuff at start depending on the job chosen
void setStuffAtStart(Player *target)
{
    target->armory = item_new();

    switch(target->job){
        case WARRIOR:
                autoEquip(target, stuffItem_ctor("My First Sword", 10, RIGHT_HAND, 5, 0, 0));
                autoEquip(target, stuffItem_ctor("Textile Armor", 10, ARMOR, 0, 1, 5));
            break;
        case RANGER:
                autoEquip(target, stuffItem_ctor("My First Bow", 10, TWO_HAND, 4, 0, 0));
                autoEquip(target, stuffItem_ctor("A Tiny Short", 10, ARMOR, 0, 1, 4));
            break;
        case WIZARD:
                autoEquip(target, stuffItem_ctor("My First Wand", 10, RIGHT_HAND, 5, 0, 0));
                autoEquip(target, stuffItem_ctor("My First Robe", 10, ARMOR, 0, 2, 3));
            break;
        default:
            break;
    }
}

//Function to Equip stuff
int autoEquip(Player *target, StuffItem *toEquip)
{
    int type = toEquip->type;
    StuffItem *object2;
    switch(type){
        case HELMET:
            //Before equipping, is there stuff equipped
            if(target->build[HELMET]->name != ' '){

                //If yes then first unequip it
                unEquip(target, target->build[HELMET]->type);
            }

            //Then equip it
            target->build[HELMET] = toEquip;
            break;
        case ARMOR:
            if(target->build[ARMOR]->name != ' '){
                unEquip(target, target->build[ARMOR]->type);
            }
            target->build[ARMOR] = toEquip;
            break;
        case RIGHT_HAND:
            if(target->build[RIGHT_HAND]->name != ' '){
                unEquip(target, target->build[RIGHT_HAND]->type);
            }
            target->build[RIGHT_HAND] = toEquip;
            break;
        case LEFT_HAND:
            if(target->build[LEFT_HAND]->name != ' '){
                unEquip(target, target->build[LEFT_HAND]->type);
            }
            target->build[LEFT_HAND] = toEquip;
            break;
        case LEGGINGS:
            if(target->build[LEGGINGS]->name != ' '){
                unEquip(target, target->build[LEGGINGS]->type);
            }
            target->build[LEGGINGS] = toEquip;
            break;
        case BOOTS:
            if(target->build[BOOTS]->name != ' '){
                unEquip(target, target->build[BOOTS]->type);
            }
            target->build[BOOTS] = toEquip;
            break;

        //If the type is two_hand we have to deal with both hands
        case TWO_HAND:
            if(target->build[LEFT_HAND]->name != ' '){
                unEquip(target, target->build[LEFT_HAND]->type);
            }
            if(target->build[RIGHT_HAND]->name != ' '){
                unEquip(target, target->build[RIGHT_HAND]->type);
            }
            object2 = stuffItem_ctor("RIGHT_HAND Copy",0,TWO_HAND,0,0,0);
            target->build[RIGHT_HAND] = toEquip;
            target->build[LEFT_HAND] = object2;
            break;
        default:
            break;
    }
}

//Display the StuffItem menu
void show_stuff(Player *target)
{
    int userChoice = 0;
    int userChoice2 = 0;
    StuffItem* toEquip;
    item_display(target->armory);

    printf("1 : EQUIP item\n2 : DELETE item\n(press 0 to get back)\n");

    userChoice = userInputInt();
    switch(userChoice)
    {
        case 1:
            printf("Which object you want to EQUIP ?\n(Type the corresponding number)\n");
            userChoice2 = userInputInt();

            //Take the stuffitem the user wants to equip
            toEquip = item_return_stuff(target->armory, userChoice2);

            //Equip it
            autoEquip(target, stuffItem_ctor(toEquip->name,toEquip->price,toEquip->type,toEquip->I_bonusATT,toEquip->I_bonusDEFRel,toEquip->I_bonusDEFAbs));

            //Then remove it from the armory
            item_remove_id(target->armory, userChoice2);
            show_stuff(target);
            break;
        case 2:
            printf("Which object you want to DELETE ?\n(Type the corresponding number)\n");
            userChoice2 = userInputInt();

            //Simply delete the selected stuffItem
            item_remove_id(target->armory, userChoice2);
            show_stuff(target);
            break;
        case 0:
            //menu_player(target, 0);
            return (0);
        default:
            printf("Please choose only 1 or 2\n");
            break;
    }
}

//Function to UnEquip selected stuffItem depending on there type
void unEquip(Player *target, int typeStuff)
{
    StuffItem* toUnEquip = target->build[typeStuff];
    StuffItem* object;

    switch(typeStuff){
        case HELMET:

            //Is there something in the HELMET position
            if(target->build[HELMET]->name != ' ')
            {

                //If yes store the stuffitem in the armory
                toUnEquip = target->build[HELMET];
                item_append(target->armory, *toUnEquip);

                //End reinitialize the HELMET position with an empty stuff
                target->build[HELMET] = stuffItem_ctor(' ',0,HELMET,0,0,0);
            }
            else{

                //If no you cannot unequip
                printf("You don't have anything equipped here...\n");
                displayEqptMenu(target);
            }
            break;
        case ARMOR:
            if(target->build[ARMOR]->name != ' ')
            {
                toUnEquip = target->build[ARMOR];
                item_append(target->armory, *toUnEquip);
                target->build[ARMOR] = stuffItem_ctor(' ',0,ARMOR,0,0,0);
            }
            else{
                printf("You don't have anything equipped here...\n");
                displayEqptMenu(target);
            }
            break;
        case RIGHT_HAND:
            if(target->build[RIGHT_HAND]->name != ' ')
            {
                if (target->build[RIGHT_HAND]->type == TWO_HAND){
                    toUnEquip = target->build[RIGHT_HAND];
                    item_append(target->armory, *toUnEquip);
                    target->build[RIGHT_HAND] = stuffItem_ctor(' ',0,RIGHT_HAND,0,0,0);
                    target->build[LEFT_HAND] = stuffItem_ctor(' ',0,LEFT_HAND,0,0,0);
                }
                else{
                    toUnEquip = target->build[RIGHT_HAND];
                    item_append(target->armory, *toUnEquip);
                    target->build[RIGHT_HAND] = stuffItem_ctor(' ',0,RIGHT_HAND,0,0,0);
                }
            }
            else{
                printf("You don't have anything equipped here...\n");
                displayEqptMenu(target);
            }
            break;
        case LEFT_HAND:
            if(target->build[LEFT_HAND]->name != ' ')
            {
                if (target->build[LEFT_HAND]->type == TWO_HAND){
                    toUnEquip = target->build[RIGHT_HAND];
                    item_append(target->armory, *toUnEquip);
                    target->build[RIGHT_HAND] = stuffItem_ctor(' ',0,RIGHT_HAND,0,0,0);
                    target->build[LEFT_HAND] = stuffItem_ctor(' ',0,LEFT_HAND,0,0,0);
                }
                else{
                    toUnEquip = target->build[LEFT_HAND];
                    item_append(target->armory, *toUnEquip);
                    target->build[LEFT_HAND] = stuffItem_ctor(' ',0,LEFT_HAND,0,0,0);
                }
            }
            else{
                printf("You don't have anything equipped here...\n");
                displayEqptMenu(target);
            }
            break;
        case LEGGINGS:
            if(target->build[LEGGINGS]->name != ' ')
            {
                toUnEquip = target->build[LEGGINGS];
                item_append(target->armory, *toUnEquip);
                target->build[LEGGINGS] = stuffItem_ctor(' ',0,LEGGINGS,0,0,0);
            }
            else{
                printf("You don't have anything equipped here...\n");
                displayEqptMenu(target);
            }
            break;
        case BOOTS:
            if(target->build[BOOTS]->name != ' ')
            {
                toUnEquip = target->build[BOOTS];
                item_append(target->armory, *toUnEquip);
                target->build[BOOTS] = stuffItem_ctor(' ',0,BOOTS,0,0,0);
            }
            else{
                printf("You don't have anything equipped here...\n");
                displayEqptMenu(target);
            }
            break;
        case TWO_HAND:
            if(target->build[RIGHT_HAND]->name != ' ')
            {
                toUnEquip = target->build[RIGHT_HAND];
                item_append(target->armory, *toUnEquip);
                target->build[RIGHT_HAND] = stuffItem_ctor(' ',0,RIGHT_HAND,0,0,0);
                target->build[LEFT_HAND] = stuffItem_ctor(' ',0,LEFT_HAND,0,0,0);
            }
            else{
                printf("You don't have anything equipped here...\n");
                displayEqptMenu(target);
            }
            break;
        default:
            break;
    }
}

//Function to generate StuffItem randomly
StuffItem* generateWeapon()
{

    int price = doRand(100, 1000);
    int type = doRand(0,6);
    char *name = generateName(type);
    int bonusATT = doRand(1,10);
    int bonusDEFRel = doRand(1,5);
    int bonusDEFAbs = doRand(1,10);

    StuffItem* newStuff = stuffItem_ctor(name,price,type,bonusATT,bonusDEFRel,bonusDEFAbs);

    return newStuff;
}

//Generate the name of the weapon depending on there type
//WARNING simple quotes for names does not work
char* generateName(int type)
{
    char *name;

    switch(type)
    {
        case 0:
            name = "Helmet";
            break;
        case 1:
            name = "Armor";
            break;
        case 2:
            name = "Weapon";
            break;
        case 3:
            name = "Shield";
            break;
        case 4:
            name = "leggings";
            break;
        case 5:
            name = "boots";
            break;
        case 6:
            name = "Two hand Weapon";
            break;
    }
    return name;
}


