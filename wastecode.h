#ifndef WASTECODE_H_INCLUDED
#define WASTECODE_H_INCLUDED

/*Equipment* Equipment_ctor(StuffItem* head, StuffItem* body, StuffItem* legs, StuffItem* foots, StuffItem* rightHand, StuffItem* leftHand){
    Equipment* p = malloc(sizeof(Equipment));
    p->head = head;
    p->body = body;
    p->legs = legs;
    p->foots = foots;
    p->rightHand = rightHand;
    p->leftHand = leftHand;
    return p;
}*/

/*enum itemNumber {
    HEALTH_POTION,
    STRENGTH_POTION,
    DEFENSE_POTION,
    GHOST_POTION
};*/

/*typedef struct ItemStructure {
    char name[50];
    char description [100];
    int health;
    int attack;
    int defense;
    int dodge;
    int quantity;
    int usesLeft;
    int id;
} item;

//Creation of list for UsableItem
struct node_item
{
    item current;
    struct node_item *p_next;
    struct node_item *p_prev;
} Node_item;

typedef struct useItem
{
    size_t length;
    struct node_item *p_tail;
    struct node_item *p_head;
} DlistItem;*/

// Doubly linked list for items.
/*typedef struct itemNodeStructure {
    item *current;
    struct itemNodeStructure *previous;
    struct itemNodeStructure *next;
} itemNode;*/



// Function Prototypes
/*int DisplayInventory(itemNode *node);
int AddItem(itemNode *inventory, enum itemNumber number);
itemNode* findItem (itemNode *node, enum itemNumber number);
int RemoveItem(itemNode *node, enum itemNumber number);*/

/*- Equipment.h : contient l'ensemble des objets porté par une créature :
			- tete
			- torse
			- jambe
			- botte
			- main droite
			- main gauche*/

/*typedef struct Equipment{
    StuffItem head;
    StuffItem body;
    StuffItem legs;
    StuffItem foots;
    StuffItem rightHand;
    StuffItem leftHand;
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
void printf_struct_equip(Equipment* equip);*/


#endif // WASTECODE_H_INCLUDED
