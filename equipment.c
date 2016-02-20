#include <stdio.h>
#include <stdlib.h>

#include "equipment.h"
#include "stuffItem.h"
#include "player.h"

/*- Equipment.c : contient les fonctions suivantes :
			- calcAttack(Equipment* equipment, Mob* mob)
			- calcRelDef(Equipment* equipment, Mob* mob)
			- calcAbsDef(Equipment* equipment, Mob* mob)*/

Equipment* Equipment_ctor(StuffItem* head, StuffItem* body, StuffItem* legs, StuffItem* foots, StuffItem* rightHand, StuffItem* leftHand){
    Equipment* p = malloc(sizeof(Equipment));
    p->head = head;
    p->body = body;
    p->legs = legs;
    p->foots = foots;
    p->rightHand = rightHand;
    p->leftHand = leftHand;
    return p;
}

/*void printf_struct_equip(Equipment* equip)
{
    printf("Name : %s\nPrice : %d\n", equip->name, equip->price);
    int type = equip->type;
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
    printf("HP : +%d\nATT : +%d\nDEFRel : +%d\nDEF : +%d\n\n", equip->I_bonusHP, equip->I_bonusATT, equip->I_bonusDEFRel, equip->I_bonusDEFAbs);
}*/

/*int* display_list_ids(Dlisteqpt *p_list)
{
}*/

//Create a new list
Dlisteqpt *eqpt_new(void)
{
    Dlisteqpt *p_new = malloc(sizeof *p_new);
    if (p_new != NULL)
    {
        p_new->length = 0;
        p_new->p_head = NULL;
        p_new->p_tail = NULL;
    }
    return p_new;
}

//Add element at the end of the list
Dlisteqpt *eqpt_append(Dlisteqpt *p_list, Equipment equip)
{
    if (p_list != NULL) /* On vérifie si notre liste a été allouée */
    {
        struct node_eqpt *p_new = malloc(sizeof *p_new); /* Création d'un nouveau node_eqpt */
        if (p_new != NULL) /* On vérifie si le malloc n'a pas échoué */
        {
            p_new->equip = equip; /* On 'enregistre' notre donnée */
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
Dlisteqpt *eqpt_prepend(Dlisteqpt *p_list, Equipment equip)
{
    if (p_list != NULL)
    {
        struct node_eqpt *p_new = malloc(sizeof *p_new);
        if (p_new != NULL)
        {
            p_new->equip = equip;
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
//Warning: position have to start to 1 and end to the current number of eqpts
//Warning: use only if you already have an eqpt in the list
/*Dlisteqpt *eqpt_insert(Dlisteqpt *p_list, Equipment equip, int position)
{
    if (p_list != NULL)
    {
        struct node_eqpt *p_temp = p_list->p_head;
        int i = 1;
        while (p_temp != NULL && i <= position)
        {
            if (position == i)
            {
                if (p_temp->p_next == NULL)
                {
                    p_list = eqpt_append(p_list, equip);
                }
                else if (p_temp->p_prev == NULL)
                {
                    p_list = eqpt_prepend(p_list, equip);
                }
                else
                {
                    struct node_eqpt *p_new = malloc(sizeof *p_new);
                    if (p_new != NULL)
                    {
                        p_new->equip = equip;
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
void eqpt_delete(Dlisteqpt **p_list)
{
    if (*p_list != NULL)
    {
        struct node_eqpt *p_temp = (*p_list)->p_head;
        while (p_temp != NULL)
        {
            struct node_eqpt *p_del = p_temp;
            p_temp = p_temp->p_next;
            free(p_del);
        }
        free(*p_list), *p_list = NULL;
    }
}

//This display the list
void eqpt_display(Dlisteqpt *p_list)
{
    if (p_list != NULL)
    {
        struct node_eqpt *p_temp = p_list->p_head;
        while (p_temp != NULL)
        {
            //printf_struct_equip(&p_temp->equip);
            fflush(stdout);
            p_temp = p_temp->p_next;
        }
    }
    printf("\n");
}

//Remove the first eqpt regarding the equip parameter
Dlisteqpt *eqpt_remove(Dlisteqpt *p_list, Equipment equip)
{
    if (p_list != NULL)
    {
        struct node_eqpt *p_temp = p_list->p_head;
        int found = 0;
        while (p_temp != NULL && !found)
        {
            if (&p_temp->equip == &equip)
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

//Remove all eqpts regarding the equip parameter
Dlisteqpt *eqpt_remove_all(Dlisteqpt *p_list, int equip)
{
    if (p_list != NULL)
    {
        struct node_eqpt *p_temp = p_list->p_head;
        while (p_temp != NULL)
        {
            if (&p_temp->equip == &equip)
            {
                struct node_eqpt *p_del = p_temp;
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

//Remove eqpt with selected position
Dlisteqpt *eqpt_remove_id(Dlisteqpt *p_list, int position)
{
    if (p_list != NULL)
    {
        struct node_eqpt *p_temp = p_list->p_head;
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
size_t eqpt_length(Dlisteqpt *p_list)
{
    size_t ret = 0;
    if (p_list != NULL)
    {
        ret = p_list->length;
    }
    return ret;
}

//Return choosen eqpt to a new list
Dlisteqpt *eqpt_find(Dlisteqpt *p_list, Equipment equip)
{
    Dlisteqpt *ret = NULL;
    if (p_list != NULL)
    {
        struct node_eqpt *p_temp = p_list->p_head;
        int found = 0;
        while (p_temp != NULL && !found)
        {
            if (&p_temp->equip == &equip)
            {
                ret = eqpt_new();
                ret = eqpt_append(ret, equip);
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

//Return all choosen eqpts to a new list
Dlisteqpt *eqpt_find_all(Dlisteqpt *p_list, Equipment equip)
{
    Dlisteqpt *ret = NULL;
    if (p_list != NULL)
    {
        struct node_eqpt *p_temp = p_list->p_head;
        while (p_temp != NULL)
        {
            if (&p_temp->equip == &equip)
            {
                if (ret == NULL)
                {
                    ret = eqpt_new();
                }
                ret = eqpt_append(ret, equip);
            }
            p_temp = p_temp->p_next;
        }
    }
    return ret;
}

//region saving/loading
//Write the whole list in a file
void writeToFile_equip(Dlisteqpt *p_list){
    FILE *fptr;
    fptr=fopen("./list_eqpt.txt","w+");

    Equipment* equip = malloc(sizeof(Equipment));
    if (p_list != NULL)
    {
        struct node_eqpt *p_temp = p_list->p_head;
        while (p_temp != NULL)
        {
            equip = &p_temp->equip;
            fwrite(equip,sizeof(Equipment),1,fptr);
            p_temp = p_temp->p_next;
        }
        printf("\n");
    }
    fclose(fptr);
}

//Read a list of structure to display it
Dlisteqpt* readFromFile_equip(){
    Dlisteqpt *p_list = eqpt_new();
    Equipment* equip = malloc(sizeof(Equipment));
    FILE *fptr;

    fptr=fopen("./list_eqpt.txt","r");

    if (fptr) {
        /* File was opened successfully. */

        /* Attempt to read element one by one */
        while (fread(equip,sizeof(Equipment),1,fptr) == 1) {
            eqpt_append(p_list, *Equipment_ctor(equip->head, equip->body, equip->leftHand, equip->rightHand, equip->legs, equip->foots));
        }
        printf("\n");
    }

    fclose(fptr);

    return p_list;
}
//endregion

void initEqt(Player *target){
    StuffItem* rienHead = stuffItem_ctor(' ',0,HELMET,0,0,0,0);
    StuffItem* rienBody = stuffItem_ctor(' ',0,ARMOR,0,0,0,0);
    StuffItem* rienLeft = stuffItem_ctor(' ',0,LEFT_HAND,0,0,0,0);
    StuffItem* rienRight = stuffItem_ctor(' ',0,RIGHT_HAND,0,0,0,0);
    StuffItem* rienLegs = stuffItem_ctor(' ',0,LEGGINGS,0,0,0,0);
    StuffItem* rienBoot = stuffItem_ctor(' ',0,BOOTS,0,0,0,0);
    Equipment* myEqpt = Equipment_ctor(rienHead,rienBody,rienLegs,rienBoot,rienRight,rienLeft);
    target->equiped = myEqpt;
}

void setEqpt(){

}

void displayEqpt(Player *target){
    /*printf("                  /88888888888888888888888888\          \n");
    printf("                  |88888888888888888888888888/      <---    \n");
    printf("                   |~~____~~~~~~~~~\"\"\"\"\"\"\"\"\"|           \n");
    printf("                  / \_________/\"\"\"\"\"\"\"\"\"\"\"\"\"\           \n");
    printf("                 /  |              \\         \\          \n");
    printf("                /   |  88    88     \\         \\         \n");
    printf("               /    |  88    88      \\         \\        \n");
    printf("              /    /                  \\        |        \n");
    printf("             /     |   ________        \\       |        \n");
    printf("             \\     |   \______/        /       |        \n");
    printf("  /\\\"\\         \\     \\____________     /        |        \n");
    printf("  | |__________\\_        |  |        /        /         \n");
    printf("/\"\"\"\"\\           \\_------\'  \'-------/       --          \n");
    printf("\\____/,___________\\                 -------/            \n");
    printf("------*            |                    \\               \n");
    printf("  ||               |                     \\              \n");
    printf("  ||               |                 ^    \\             \n");
    printf("  ||               |                | \\    \\            \n");
    printf("  ||               |                |  \\    \\           \n");
    printf("  ||               |                |   \\    \\          \n");
    printf("  \\|              /                /\"\"\\\"\\/    /          \n");
    printf("     -------------                |    |    /           \n");
    printf("     |\\--_                        \____/___/            \n");
    printf("     |   |\\-_                       |                   \n");
    printf("     |   |   \\_                     |                   \n");
    printf("     |   |     \\                    |                   \n");
    printf("     |   |      \\_                  |                   \n");
    printf("     |   |        ----___           |                   \n");
    printf("     |   |               \\----------|                   \n");
    printf("     /   |                     |     ----------\"\"\\      \n");
    printf("/\"\--\"--_|                     |               |  \\     \n");
    printf("|_______/                      \\______________/    )    \n");
    printf("                                              \\___/     \n");*/
}

/*void calcAttack(Equipment* equipment, Mob* mob){
}

void calcAttack(Equipment* equipment, Mob* mob){
}

void calcAbsDef(Equipment* equipment, Mob* mob){
}*/

/*Example of SAVE STRUCT
struct date *object=malloc(sizeof(struct date));
strcpy(object->day,"Good day");
object->month=6;
object->year=2013;
FILE * file= fopen("output", "wb");
if (file != NULL) {
    fwrite(object, sizeof(struct date), 1, file);
    fclose(file);
}

struct date *object2=malloc(sizeof(struct date));
    FILE * file= fopen("output", "rb");
    if (file != NULL) {
        fread(object2, sizeof(struct date), 1, file);
        fclose(file);
    }
    printf("%s/%d/%d\n",object2->day,object2->month,object2->year);*/
