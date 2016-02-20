#ifndef STUFFITEM_H_INCLUDED
#define STUFFITEM_H_INCLUDED

/*- StuffItem.h : contient l'ensemble des caractéristiques d'un objet porté par une créature :
			- nom
			- valeur (valeur en or)
			- type (tete, torse, jambe, botte, main droite, main gauche)
			- point de vie
			- attaque
			- defense relative
			- defense absolue*/

// 0 based.
enum stuffNumber {
    HELMET,
    ARMOR,
    RIGHT_HAND,
    LEFT_HAND,
    TWO_HAND,
    LEGGINGS,
    BOOTS
};

//Gives attributes to all the items which equip a creature
typedef struct StuffItem{
    char* name;
    int price;
    int type;
    int I_bonusHP;
    int I_bonusATT;
    int I_bonusDEFRel;
    int I_bonusDEFAbs;
}StuffItem;

//prototype for the stuffDlistStuff builder
StuffItem* stuffItem_ctor(char* name, int price, int type, int I_bonusHP, int I_bonusATT, int I_bonusDEFRel, int I_bonusDEFAbs);

//Create of list for stuffDlistStuff
struct node_stuff
{
    StuffItem stuff;
    struct node_stuff *p_next;
    struct node_stuff *p_prev;
} Node_stuff;

typedef struct item
{
    size_t length;
    struct node_stuff *p_tail;
    struct node_stuff *p_head;
} DlistStuff;

DlistStuff* readFromFile_stuff();
void writeToFile_stuff(DlistStuff *p_list);
DlistStuff *item_find_all(DlistStuff *p_list, StuffItem stuff);
DlistStuff *item_find(DlistStuff *p_list, StuffItem stuff);
size_t item_length(DlistStuff *p_list);
DlistStuff *item_remove_id(DlistStuff *p_list, int position);
DlistStuff *item_remove_all(DlistStuff *p_list, int stuff);
DlistStuff *item_remove(DlistStuff *p_list, StuffItem stuff);
void item_display(DlistStuff *p_list);
void item_delete(DlistStuff **p_list);
DlistStuff *item_insert(DlistStuff *p_list, StuffItem stuff, int position);
DlistStuff *item_prepend(DlistStuff *p_list, StuffItem stuff);
DlistStuff *item_append(DlistStuff *p_list, StuffItem stuff);
DlistStuff *item_new(void);
void printf_struct_stuff(StuffItem* stuff);

//Prototype of functions

#endif // STUFFITEM_H_INCLUDED
