#include <stdlib.h>
#include <stdio.h>

#include "stuffItem.h"
#include "player.h"
#include "equipment.h"

/*- StuffItem.c : contient les fonctions suivantes :
			- eqpStuffItem(StuffItem* item, Mob* mob)
			- unEqpStuffItem(StuffItem* item, Mob* mob)
			- sellStuffItem(StuffItem* item, Player* player)*/

StuffItem* stuffItem_ctor(char* name, int price, int type, int I_bonusHP, int I_bonusATT, int I_bonusDEFRel, int I_bonusDEFAbs){
    StuffItem* p = malloc(sizeof(StuffItem));
    p->name = name;
    p->price = price;
    p->type = type;
    p->I_bonusHP = I_bonusHP;
    p->I_bonusATT = I_bonusATT;
    p->I_bonusDEFRel = I_bonusDEFRel;
    p->I_bonusDEFAbs = I_bonusDEFAbs;
    return p;
}

/*void eqpStuffItem(StuffItem* item, Mob* mob){
}

void unEqpStuffItem(StuffItem* item, Mob* mob){
}

void sellStuffItem(StuffItem* item, Player* player){
}*/

//Allow to display correct info of list items
void printf_struct_stuff(StuffItem* stuff)
{
    printf("Name : %s\nPrice : %d\n", stuff->name, stuff->price);
    int type = stuff->type;
    switch(type){
        case HELMET:
            printf("Type : HELMET\n");
            break;
        case ARMOR:
            printf("Type : ARMOR\n");
            break;
        case RIGHT_HAND:
            printf("Type : RIGHT_HAND\n");
            break;
        case LEFT_HAND:
            printf("Type : LEFT_HAND\n");
            break;
        case LEGGINGS:
            printf("Type : LEGGINGS\n");
            break;
        case BOOTS:
            printf("Type : BOOTS\n");
            break;
    }
    printf("HP : +%d\nATT : +%d\nDEFRel : +%d\nDEF : +%d\n\n", stuff->I_bonusHP, stuff->I_bonusATT, stuff->I_bonusDEFRel, stuff->I_bonusDEFAbs);
}

/*int* display_list_ids(DlistStuff *p_list)
{
}*/

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
    if (p_list != NULL) /* On vérifie si notre liste a été allouée */
    {
        struct node_stuff *p_new = malloc(sizeof *p_new); /* Création d'un nouveau node_stuff */
        if (p_new != NULL) /* On vérifie si le malloc n'a pas échoué */
        {
            p_new->stuff = stuff; /* On 'enregistre' notre donnée */
            p_new->p_next = NULL; /* On fait pointer p_next vers NULL */
            if (p_list->p_tail == NULL) /* Cas où notre liste est vide (pointeur vers fin de liste à  NULL) */
            {
                p_new->p_prev = NULL; /* On fait pointer p_prev vers NULL */
                p_list->p_head = p_new; /* On fait pointer la tête de liste vers le nouvel élément */
                p_list->p_tail = p_new; /* On fait pointer la fin de liste vers le nouvel élément */
            }
            else /* Cas où des éléments sont déjà présents dans notre liste */
            {
                p_list->p_tail->p_next = p_new; /* On relie le dernier élément de la liste vers notre nouvel élément (début du chaînage) */
                p_new->p_prev = p_list->p_tail; /* On fait pointer p_prev vers le dernier élément de la liste */
                p_list->p_tail = p_new; /* On fait pointer la fin de liste vers notre nouvel élément (fin du chaînage: 3 étapes) */
            }
            p_list->length++; /* Incrémentation de la taille de la liste */
        }
    }
    return p_list; /* on retourne notre nouvelle liste */
}

//Add element at start of the list
DlistStuff *item_prepend(DlistStuff *p_list, StuffItem stuff)
{
    if (p_list != NULL)
    {
        struct node_stuff *p_new = malloc(sizeof *p_new);
        if (p_new != NULL)
        {
            p_new->stuff = stuff;
            p_new->p_prev = NULL;
            if (p_list->p_tail == NULL)
            {
                p_new->p_next = NULL;
                p_list->p_head = p_new;
                p_list->p_tail = p_new;
            }
            else
            {
                p_list->p_head->p_prev = p_new;
                p_new->p_next = p_list->p_head;
                p_list->p_head = p_new;
            }
            p_list->length++;
       }
    }
    return p_list;
}

//Insert an element at the position choice
//Warning: position have to start to 1 and end to the current number of items
//Warning: use only if you already have an item in the list
/*DlistStuff *item_insert(DlistStuff *p_list, StuffItem stuff, int position)
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
                    p_list = item_append(p_list, stuff);
                }
                else if (p_temp->p_prev == NULL)
                {
                    p_list = item_prepend(p_list, stuff);
                }
                else
                {
                    struct node_stuff *p_new = malloc(sizeof *p_new);
                    if (p_new != NULL)
                    {
                        p_new->stuff = stuff;
                        p_temp->p_next->p_prev = p_new;
                        p_temp->p_prev->p_next = p_new;
                        p_new->p_prev = p_temp->p_prev;
                        p_new->p_next = p_temp;
                        p_list->length++;
                    }
                }
            }
            else
            {
                p_temp = p_temp->p_next;
            }
            i++;
        }
    }
    return p_list;
}*/

//This will unallocate the entire list this cannot be access after
void item_delete(DlistStuff **p_list)
{
    if (*p_list != NULL)
    {
        struct node_stuff *p_temp = (*p_list)->p_head;
        while (p_temp != NULL)
        {
            struct node_stuff *p_del = p_temp;
            p_temp = p_temp->p_next;
            free(p_del);
        }
        free(*p_list), *p_list = NULL;
    }
}

//This display the list
void item_display(DlistStuff *p_list)
{
    if (p_list != NULL)
    {
        struct node_stuff *p_temp = p_list->p_head;
        while (p_temp != NULL)
        {
            printf_struct_stuff(&p_temp->stuff);
            fflush(stdout);
            p_temp = p_temp->p_next;
        }
    }
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

//Remove all items regarding the stuff parameter
DlistStuff *item_remove_all(DlistStuff *p_list, int stuff)
{
    if (p_list != NULL)
    {
        struct node_stuff *p_temp = p_list->p_head;
        while (p_temp != NULL)
        {
            if (&p_temp->stuff == &stuff)
            {
                struct node_stuff *p_del = p_temp;
                p_temp = p_temp->p_next;
                if (p_del->p_next == NULL)
                {
                    p_list->p_tail = p_del->p_prev;
                    p_list->p_tail->p_next = NULL;
                }
                else if (p_del->p_prev == NULL)
                {
                    p_list->p_head = p_del->p_next;
                    p_list->p_head->p_prev = NULL;
                }
                else
                {
                    p_del->p_next->p_prev = p_del->p_prev;
                    p_del->p_prev->p_next = p_del->p_next;
                }
                free(p_del);
                p_list->length--;
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

//Return choosen item to a new list
DlistStuff *item_find(DlistStuff *p_list, StuffItem stuff)
{
    DlistStuff *ret = NULL;
    if (p_list != NULL)
    {
        struct node_stuff *p_temp = p_list->p_head;
        int found = 0;
        while (p_temp != NULL && !found)
        {
            if (&p_temp->stuff == &stuff)
            {
                ret = item_new();
                ret = item_append(ret, stuff);
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

//Return all choosen items to a new list
DlistStuff *item_find_all(DlistStuff *p_list, StuffItem stuff)
{
    DlistStuff *ret = NULL;
    if (p_list != NULL)
    {
        struct node_stuff *p_temp = p_list->p_head;
        while (p_temp != NULL)
        {
            if (&p_temp->stuff == &stuff)
            {
                if (ret == NULL)
                {
                    ret = item_new();
                }
                ret = item_append(ret, stuff);
            }
            p_temp = p_temp->p_next;
        }
    }
    return ret;
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
            item_append(p_list, *stuffItem_ctor(stuff->name, stuff->price, stuff->type, stuff->I_bonusHP, stuff->I_bonusATT, stuff->I_bonusDEFRel, stuff->I_bonusDEFAbs));
        }
        printf("\n");
    }

    fclose(fptr);

    return p_list;
}
//endregion

void setStuffAtStart(Player *target){
    target->armory = item_new();
    switch(target->job){
        case WARRIOR:
            item_append(target->armory, *stuffItem_ctor("My First Sword", 10, RIGHT_HAND, 0, 10, 0, 0));
            item_append(target->armory, *stuffItem_ctor("Textile Armor", 10, ARMOR, 0, 0, 1, 10));
            printf("Would you like to auto-equip ?\n1 : Yes\n2 : No\n");
            int userChoice = userInputInt();
            if(userChoice == 1){
                StuffItem sword = *stuffItem_ctor("My First Sword", 10, RIGHT_HAND, 0, 10, 0, 0);
                StuffItem armor = *stuffItem_ctor("Textile Armor", 10, ARMOR, 0, 0, 1, 10);
                Equipment myEqpt = *Equipment_ctor(0,&armor,0,0,&sword,0);
                eqpt_append(target->equiped, myEqpt);
                item_remove_id(target->armory,1);
                item_remove_id(target->armory,2);
            }
            break;
        /*case RANGER:
            item_append(target->armory, *stuffItem_ctor("My First Bow", 10, TWO_HAND, 0, 10, 0, 0));
            item_append(target->armory, *stuffItem_ctor("A Tiny Short", 10, ARMOR, 0, 0, 1, 10));
            printf("Would you like to auto-equip ?\1 : Yes\2 : No");
            int userChoice = userInputInt();
            if(userChoice == 1){
                target->equiped->rightHand = *stuffItem_ctor("My First Sword", 10, RIGHT_HAND, 0, 10, 0, 0);
                target->equiped->body = *stuffItem_ctor("Textile Armor", 10, ARMOR, 0, 0, 1, 10);
                item_remove_id(target->armory,1);
                item_remove_id(target->armory,2);
            }
            break;
        case WIZARD:
            item_append(target->armory, *stuffItem_ctor("My First Wand", 10, RIGHT_HAND, 0, 10, 0, 0));
            item_append(target->armory, *stuffItem_ctor("My First Robe", 10, ARMOR, 0, 0, 1, 10));
            printf("Would you like to auto-equip ?\1 : Yes\2 : No");
            int userChoice = userInputInt();
            if(userChoice == 1){
                target->equiped->rightHand = *stuffItem_ctor("My First Sword", 10, RIGHT_HAND, 0, 10, 0, 0);
                target->equiped->body = *stuffItem_ctor("Textile Armor", 10, ARMOR, 0, 0, 1, 10);
                item_remove_id(target->armory,1);
                item_remove_id(target->armory,2);
            }
            break;
        default:
            break;*/
    }
    item_display(target->armory);
}


/*void createStuff(){
    DlistStuff* stuffList = item_new();

    StuffItem* casque = stuffItem_ctor("beret", 100, 0, 10, 2, 10, 3);
    StuffItem* armor = stuffItem_ctor("plate", 100, 1, 10, 2, 10, 3);
    StuffItem* leggings = stuffItem_ctor("cuir", 100, 2, 10, 2, 10, 3);
    StuffItem* boots = stuffItem_ctor("sandales", 100, 1, 10, 2, 10, 3);
    StuffItem* sword = stuffItem_ctor("katana", 100, 1, 10, 2, 10, 3);
    StuffItem* shield = stuffItem_ctor("bouclier", 100, 1, 10, 2, 10, 3);

    item_append(stuffList, *casque);
    item_append(stuffList, *armor);
    item_append(stuffList, *leggings);
    item_append(stuffList, *boots);
    item_append(stuffList, *sword);
    item_append(stuffList, *shield;

    item_display(stuffList);

    Equipment* start = Equipment_ctor(casque, armor, leggings, boots, sword, shield);

    writeToFile_stuff(stuffList);
    DlistStuff* newStuffList = readFromFile_stuff();

    item_display(newStuffList);
}*/
