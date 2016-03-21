#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "stuffItem.h"
#include "player.h"
#include "equipment.h"
#include "gameUtil.h"

/*- StuffItem.c : contient les fonctions suivantes :
			- eqpStuffItem(StuffItem* item, Mob* mob)
			- unEqpStuffItem(StuffItem* item, Mob* mob)
			- sellStuffItem(StuffItem* item, Player* player)*/

StuffItem* stuffItem_ctor(char* name, int price, int type, int I_bonusATT, int I_bonusDEFRel, int I_bonusDEFAbs){
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
            item_append(p_list, *stuffItem_ctor(stuff->name, stuff->price, stuff->type, stuff->I_bonusATT, stuff->I_bonusDEFRel, stuff->I_bonusDEFAbs));
        }
        printf("\n");
    }

    fclose(fptr);

    return p_list;
}
//endregion

void setStuffAtStart(Player *target){
    target->armory = item_new();
    printf("Would you like to auto-equip the basic stuff ?\n1 : Yes\n2 : No\n");
    int userChoice = userInputInt();

    switch(target->job){
        case WARRIOR:
            if(userChoice == 1){
                autoEquip(target, stuffItem_ctor("My First Sword", 10, RIGHT_HAND, 10, 0, 0));
                autoEquip(target, stuffItem_ctor("Textile Armor", 10, ARMOR, 0, 1, 10));
            }
            else{
                item_append(target->armory, *stuffItem_ctor("My First Sword", 10, RIGHT_HAND, 10, 0, 0));
                item_append(target->armory, *stuffItem_ctor("Textile Armor", 10, ARMOR, 0, 1, 10));
            }
            break;
        case RANGER:
            if(userChoice == 1){
                autoEquip(target, stuffItem_ctor("My First Bow", 10, TWO_HAND, 10, 0, 0));
                autoEquip(target, stuffItem_ctor("A Tiny Short", 10, ARMOR, 0, 1, 10));
            }
            else{
                item_append(target->armory, *stuffItem_ctor("My First Bow", 10, TWO_HAND, 10, 0, 0));
                item_append(target->armory, *stuffItem_ctor("A Tiny Short", 10, ARMOR, 0, 1, 10));
            }
            break;
        case WIZARD:
            if(userChoice == 1){
                autoEquip(target, stuffItem_ctor("My First Wand", 10, RIGHT_HAND, 10, 0, 0));
                autoEquip(target, stuffItem_ctor("My First Robe", 10, ARMOR, 0, 1, 10));
            }
            else{
                item_append(target->armory, *stuffItem_ctor("My First Wand", 10, RIGHT_HAND, 10, 0, 0));
                item_append(target->armory, *stuffItem_ctor("My First Robe", 10, ARMOR, 0, 1, 10));
            }
            break;
        default:
            break;
    }
}

int autoEquip(Player *target, StuffItem *toEquip){
    int type = toEquip->type;
    StuffItem *object2;
    switch(type){
        case HELMET:
            target->build[HELMET] = toEquip;
            break;
        case ARMOR:
            target->build[ARMOR] = toEquip;
            break;
        case RIGHT_HAND:
            target->build[RIGHT_HAND] = toEquip;
            break;
        case LEFT_HAND:
            target->build[LEFT_HAND] = toEquip;
            break;
        case LEGGINGS:
            target->build[LEGGINGS] = toEquip;
            break;
        case BOOTS:
            target->build[BOOTS] = toEquip;
            break;
        case TWO_HAND:
            object2 = stuffItem_ctor("RIGHT_HAND Copy",0,LEFT_HAND,0,0,0);
            target->build[RIGHT_HAND] = toEquip;
            target->build[LEFT_HAND] = object2;
            break;
        default:
            break;
    }
    return(0);
}

void show_stuff(Player *target){
    int userChoice = 0;
    int userChoice2 = 0;
    useItem_display(target->armory);

    printf("1 : EQUIP item\n2 : DELETE item\n(press 0 to get back)\n");

    userChoice = userInputInt();
    switch(userChoice)
    {
        case 1:
            printf("Which object you want to EQUIP ?\n(Type the corresponding number)\n");
            userChoice2 = userInputInt();
            set_equip(target, userChoice2);
            break;
        case 2:
            printf("Which object you want to DELETE ?\n(Type the corresponding number)\n");
            userChoice2 = userInputInt();
            item_remove_id(target->armory, userChoice2);
            break;
        case 0:
            displayMainMenu(target);
            break;
        default:
            printf("Please choose only 1 or 2\n");
            break;
    }

}

void set_equip(Player *target, int position){
    StuffItem* toEquip = item_return_stuff(target->armory, position);
    int type = toEquip->type;
    printf("Type : %d\n", type);
    StuffItem *object;
    StuffItem *object2;
    switch(type){
        case HELMET:
            if(target->build[HELMET])
            {
                object = target->build[HELMET];
                item_append(target->armory, *object);
                target->build[HELMET] = toEquip;
                item_remove_id(target->armory, position);
            }
            else
            {
                target->build[HELMET] = toEquip;
                item_remove_id(target->armory, position);
            }
            break;
        case ARMOR:
            if(target->build[ARMOR])
            {
                object = target->build[ARMOR];
                item_append(target->armory, *object);
                target->build[ARMOR] = toEquip;
                item_remove_id(target->armory, position);
            }
            else
            {
                target->build[ARMOR] = toEquip;
                item_remove_id(target->armory, position);
            }
            break;
        case RIGHT_HAND:
            printf("Name : \n");
            if(target->build[RIGHT_HAND])
            {
                printf("la\n");
                object = target->build[RIGHT_HAND];
                printf("reussi\n");
                item_append(target->armory, *object);
                printf("dur\n");
                target->build[RIGHT_HAND] = toEquip;
                item_remove_id(target->armory, position);
            }
            else
            {
                printf("Dans right hand\n");
                target->build[RIGHT_HAND] = toEquip;
                item_remove_id(target->armory, position);
            }
            break;
        case LEFT_HAND:
            if(target->build[LEFT_HAND])
            {
                object = target->build[LEFT_HAND];
                item_append(target->armory, *object);
                target->build[LEFT_HAND] = toEquip;
                item_remove_id(target->armory, position);
            }
            else
            {
                target->build[LEFT_HAND] = toEquip;
                item_remove_id(target->armory, position);
            }
            break;
        case LEGGINGS:
            if(target->build[LEGGINGS])
            {
                object = target->build[LEGGINGS];
                item_append(target->armory, *object);
                target->build[LEGGINGS] = toEquip;
                item_remove_id(target->armory, position);
            }
            else
            {
                target->build[LEGGINGS] = toEquip;
                item_remove_id(target->armory, position);
            }
            break;
        case BOOTS:
            if(target->build[BOOTS])
            {
                object = target->build[BOOTS];
                item_append(target->armory, *object);
                target->build[BOOTS] = toEquip;
                item_remove_id(target->armory, position);
            }
            else
            {
                target->build[BOOTS] = toEquip;
                item_remove_id(target->armory, position);
            }
            break;
        case TWO_HAND:
            object2 = stuffItem_ctor("RIGHT_HAND Copy",0,LEFT_HAND,0,0,0);
            if(target->build[RIGHT_HAND])
            {
                object = target->build[RIGHT_HAND];
                item_append(target->armory, *object);
                target->build[RIGHT_HAND] = toEquip;
                item_remove_id(target->armory, position);
            }
            else
            {
                target->build[RIGHT_HAND] = toEquip;
                item_remove_id(target->armory, position);
            }
            if(target->build[LEFT_HAND])
            {
                object = target->build[LEFT_HAND];
                item_append(target->armory, *object);
                target->build[LEFT_HAND] = object2;
            }
            else
            {
                target->build[LEFT_HAND] = object2;
            }
            break;
        default:
            break;
    }
}

StuffItem* generateWeapon(){

    int price = doRand(100, 1000);
    int type = doRand(0,6);
    char *name = generateName(type);
    int bonusATT = doRand(1,20);
    int bonusDEFRel = doRand(1,5);
    int bonusDEFAbs = doRand(1,20);

    StuffItem* newStuff = stuffItem_ctor(name,price,type,bonusATT,bonusDEFRel,bonusDEFAbs);

    return newStuff;
}

//WARNING simple quotes for names doesn't work
char* generateName(int type){
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
            name = "Big Weapon";
            break;
    }
    return name;
}


