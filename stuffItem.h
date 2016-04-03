#ifndef STUFFITEM_H_INCLUDED
#define STUFFITEM_H_INCLUDED

enum stuffNumber {
    HELMET,
    ARMOR,
    RIGHT_HAND,
    LEFT_HAND,
    LEGGINGS,
    BOOTS,
    TWO_HAND
};

//Gives attributes to all the items which equip a creature
typedef struct StuffItem{
    char* name;
    int price;
    int type;
    int I_bonusATT;
    int I_bonusDEFRel;
    int I_bonusDEFAbs;
}StuffItem;

//prototype for the Stuff builder
StuffItem* stuffItem_ctor(char* name, int price, int type, int I_bonusATT, int I_bonusDEFRel, int I_bonusDEFAbs);

//Create of list for DlistStuff
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
size_t item_length(DlistStuff *p_list);
DlistStuff *item_remove_id(DlistStuff *p_list, int position);
DlistStuff *item_remove(DlistStuff *p_list, StuffItem stuff);
void item_display(DlistStuff *p_list);
DlistStuff *item_append(DlistStuff *p_list, StuffItem stuff);
DlistStuff *item_new(void);
void printf_struct_stuff(StuffItem* stuff);
StuffItem *item_return_stuff(DlistStuff *p_list, int position);

//Prototype of functions
StuffItem* generateWeapon();
char* generateName(int type);

#endif // STUFFITEM_H_INCLUDED
