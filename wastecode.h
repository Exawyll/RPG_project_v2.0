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

/*void displayEqpt(Player *target){
    printf("                  /88888888888888888888888888\          \n");
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
    printf("                                              \\___/     \n");
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

/*void set_equip(Player *target, int position){
    StuffItem* toEquip = item_return_stuff(target->armory, position);
    int type = toEquip->type;
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
            break;
        case LEFT_HAND:
            if(target->build[LEFT_HAND])
            {printf("Good job you killed it... More %d mobs to empty this dungeon !\n", dungeonSize);
                    Sleep(2000);
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
            object2 = stuffItem_ctor("RIGHT_HAND Copy",0,TWO_HAND,0,0,0);
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
}*/


#endif // WASTECODE_H_INCLUDED
