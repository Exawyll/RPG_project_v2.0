#ifndef USABLEITEM_H_INCLUDED
#define USABLEITEM_H_INCLUDED

/*- Usableitem.h : contient l'ensemble des objets utilisable par une créature :
			- nom
			- valeur (valeur en or)
			- tour d'effectivité
			- action point vie
			- action attaque
			- action defense relative
			- action defense absolue
			- action esquive*/

// 0 based.
enum itemNumber {
    HEALTH_POTION,
    STRENGTH_POTION,
    DEFENSE_POTION,
    GHOST_POTION
};

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
DlistItem *useItem_find_all(DlistItem *p_list, UsableItem item);
//DlistItem *useItem_find(DlistItem *p_list, UsableItem item);
int useItem_find_id(DlistItem *p_list, enum itemNumber number);
size_t useItem_length(DlistItem *p_list);
DlistItem *useItem_remove_id(DlistItem *p_list, int position);

int useItem_return_id(DlistItem *p_list, int position);

DlistItem *useItem_remove_all(DlistItem *p_list, int item);
DlistItem *useItem_remove(DlistItem *p_list, UsableItem item);
void useItem_display(DlistItem *p_list);
void useItem_delete(DlistItem **p_list);
DlistItem *useItem_insert(DlistItem *p_list, UsableItem item, int position);
DlistItem *useItem_prepend(DlistItem *p_list, UsableItem item);
DlistItem *useItem_append(DlistItem *p_list, UsableItem item);
DlistItem *useItem_new(void);
void printf_struct_item(UsableItem* item);

//Prototype functions
UsableItem createUsableItems(enum itemNumber);
void menuSelectPotion();


#endif // USABLEITEM_H_INCLUDED
