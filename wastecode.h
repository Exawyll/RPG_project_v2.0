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


#endif // WASTECODE_H_INCLUDED
