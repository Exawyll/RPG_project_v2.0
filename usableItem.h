#ifndef USABLEITEM_H_INCLUDED
#define USABLEITEM_H_INCLUDED

enum itemNumber {
    HEALTH_POTION,
    STRENGTH_POTION,
    DEFENSE_POTION,
    GHOST_POTION
};

//Structure for Usable Items
typedef struct UsableItem{
    char* name;
    int id;
    char* description;
    int price;
    int timeEffect;
    int bonusHP;
    int bonusATT;
    int bonusDEFAbs;
    int bonusESQ;
}UsableItem;

UsableItem* usableItem_ctor(char* name, int id, char* description, int price, int TimeEffect, int bonusHP, int bonusATT, int bonusDEFAbs, int bonusESQ);

//Creation of list for UsableItem
struct node_item
{
    UsableItem item;
    struct node_item *p_next;
    struct node_item *p_prev;
} Node_item;

typedef struct useItem
{
    size_t length;
    struct node_item *p_tail;
    struct node_item *p_head;
} DlistItem;

DlistItem* readFromFile_item();
void writeToFile_item(DlistItem *p_list);
size_t useItem_length(DlistItem *p_list);
DlistItem *useItem_remove_id(DlistItem *p_list, int position);
int useItem_return_id(DlistItem *p_list, int position);
DlistItem *useItem_remove(DlistItem *p_list, UsableItem item);
void useItem_display(DlistItem *p_list);
DlistItem *useItem_append(DlistItem *p_list, UsableItem item);
DlistItem *useItem_new(void);
void printf_struct_item(UsableItem* item);

//Prototype functions
void menuSelectPotion();
UsableItem createUsableItems(enum itemNumber);

#endif // USABLEITEM_H_INCLUDED
