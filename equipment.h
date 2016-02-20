#ifndef EQUIPMENT_H_INCLUDED
#define EQUIPMENT_H_INCLUDED

#include "equipment.h"
#include "stuffItem.h"
/*- Equipment.h : contient l'ensemble des objets porté par une créature :
			- tete
			- torse
			- jambe
			- botte
			- main droite
			- main gauche*/

typedef struct Equipment{
    StuffItem** head;
    StuffItem** body;
    StuffItem** legs;
    StuffItem** foots;
    StuffItem** rightHand;
    StuffItem** leftHand;
}Equipment;

Equipment* Equipment_ctor(StuffItem* head, StuffItem* body, StuffItem* legs, StuffItem* foots, StuffItem* rightHand, StuffItem* leftHand);

//Create of list for equipDlisteqpt
struct node_eqpt
{
    Equipment equip;
    struct node_eqpt *p_next;
    struct node_eqpt *p_prev;
} Nodeeqpt;

typedef struct eqpt
{
    size_t length;
    struct node_eqpt *p_tail;
    struct node_eqpt *p_head;
} Dlisteqpt;

Dlisteqpt* readFromFile_equip();
void writeToFile_equip(Dlisteqpt *p_list);
Dlisteqpt *eqpt_find_all(Dlisteqpt *p_list, Equipment equip);
Dlisteqpt *eqpt_find(Dlisteqpt *p_list, Equipment equip);
size_t eqpt_length(Dlisteqpt *p_list);
Dlisteqpt *eqpt_remove_id(Dlisteqpt *p_list, int position);
Dlisteqpt *eqpt_remove_all(Dlisteqpt *p_list, int equip);
Dlisteqpt *eqpt_remove(Dlisteqpt *p_list, Equipment equip);
void eqpt_display(Dlisteqpt *p_list);
void eqpt_delete(Dlisteqpt **p_list);
Dlisteqpt *eqpt_insert(Dlisteqpt *p_list, Equipment equip, int position);
Dlisteqpt *eqpt_prepend(Dlisteqpt *p_list, Equipment equip);
Dlisteqpt *eqpt_append(Dlisteqpt *p_list, Equipment equip);
Dlisteqpt *eqpt_new(void);
void printf_struct_equip(Equipment* equip);

#endif // EQUIPMENT_H_INCLUDED
