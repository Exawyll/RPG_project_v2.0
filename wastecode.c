

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "usableItem.h"
#include "player.h"
#include "gameUtil.h"

#define START_POTIONS 3

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
} item;*/

/*int DisplayInventory(itemNode *node) {
  // While there is an item present, print said item.
  while (node->current != NULL)  {
    printf("Name: %s\n", node->current->name);
    printf("Description: %s\n", node->current->description);
    /*printf("Health: %d\n", node->current->health);
    printf("Mana: %d\n", node->current->mana);*/
    /*printf("Uses Left: %d\n", node->current->usesLeft);
    printf("Quantity: %d\n\n", node->current->quantity);

    // If there is another item in the list, go to it, else, stop.
    if (node->next != NULL) {
      node = node->next;
    } else {
      return(0);
    }
  }
  printf("Inventory is empty.\n");
  return(0);
}

// FIND ITEM
// Can't return 0 because it's interpreted as an int. Return NULL for functions
// that are supposed to return pointers.
itemNode* findItem (itemNode *node, enum itemNumber number) {
  if (node == NULL) {
    return(NULL);
  }

  // Avoid unitialized or unassigned nodes.
  while (node->current != NULL) {
     if (node->current->id == number) {
       return(node);
     }

     if (node->next != NULL) {
       node = node->next;
     } else {
       return(NULL);
     }
  }
  return(NULL);
}

int AddItem(itemNode *node, enum itemNumber number) {
  itemNode *previousNode;
  itemNode *searchResult;

  // See if item already exists.
  searchResult = findItem(node, number);
  if (searchResult != NULL) {
    searchResult->current->quantity += 1;
    return(0);
  }

  // Generate item if it doesn't exist.
  item *object = malloc(sizeof(item)); // Item.
  switch(number) {
        case HEALTH_POTION:
            strcpy(object->name, "Health Potion");
            strcpy(object->description, "Drinkable item that heals 20 health points.");
            object->health = 20;
            object->usesLeft = 1;
            object->quantity = 1;
            object->id = number;          // ID and ItemNumber are the same.
            break;
        case STRENGTH_POTION:
            strcpy(object->name, "Strength Potion");
            strcpy(object->description, "Drinkable item that increase 10 attack.");
            object->usesLeft = 1;
            object->quantity = 1;
            object->attack = 10;
            object->id = number;
            break;
        case DEFENSE_POTION:
            strcpy(object->name, "Defense Potion");
            strcpy(object->description, "Drinkable item that increase 10 defense.");
            object->usesLeft = 1;
            object->quantity = 1;
            object->defense = 10;
            object->id = number;
            break;
        case GHOST_POTION:
            strcpy(object->name, "Ghost Potion");
            strcpy(object->description, "Drinkable item that increase 10 dodge.");
            object->usesLeft = 1;
            object->quantity = 1;
            object->dodge = 10;
            object->id = number;
            break;
    }

  // If node is unused allocate memory and assign item.
  if (node->current == NULL) {
    node->current = object;
  // If node is occupied, check next node.
  } else if (node->next == NULL) {
    node->next = malloc(sizeof(itemNode));
    previousNode = node;
    node = node->next;
    node->previous = previousNode;
    node->current = object;
  // If current and next node are occupied, search for the last node.
  // The last node will have an empty "next" spot.
  } else {
    while (node->next != NULL) {
      node = node->next;
    }

    node->next = malloc(sizeof(itemNode));
    previousNode = node;
    node = node->next;
    node->previous = previousNode;
    node->current = object;
  }
  return(0);
}

int RemoveItem(itemNode *node, enum itemNumber number) {
  itemNode *searchResult;
  itemNode *previous;
  itemNode *next;

  // See if item already exists.
  searchResult = findItem(node, number);

  // If item exists, and reduce quantity by 1.
  if (searchResult != NULL) {
    searchResult->current->quantity -= 1;

    // If reduction results in 0 quantity, remove item entirely.
    if (searchResult->current->quantity <= 0) {
      previous = searchResult->previous;
      next = searchResult->next;

      // Free the item and then the node containing it.
      free(searchResult->current);
      free(searchResult);

      // Switch linked list together.
      // We can't assign the next/previous members if the itemNode is null.
      if (previous != NULL) {
        searchResult = previous;
        searchResult->next = next;
      }
      if (next != NULL) {
        searchResult = next;
        searchResult->previous = previous;
      }
    }
  }
  return(0);
}
void setPotionAtStart(Player *target){
    int nbrPotion = START_POTIONS;
    int choice = 0;

    init_inventory(target);

    printf("Now you have 3 potions to add to your inventory, what will you choose ?\n(trick : you can have many of the same type)\n");
    printf("1 : HEALTH POTION (increase temporally 10 HP)\n"
           "2 : STRENGTH POTION (increase temporally 10 attack points)\n"
           "3 : DEFENSE POTION (increase temporally 10 defense points)\n"
           "4 : GHOST POTION (increase temporally 10 dodge points)\n"
           "(WARNING : if you enter a wrong input, you won't have ANY POTION !!!");
    while(nbrPotion > 0){
        choice = userInputInt();
        switch(choice){
            case 1:
                AddItem(target->inventory, HEALTH_POTION);
                nbrPotion--;
                DisplayInventory(target->inventory);
                break;
            case 2:
                AddItem(target->inventory, STRENGTH_POTION);
                nbrPotion--;
                DisplayInventory(target->inventory);
                break;
            case 3:
                AddItem(target->inventory, DEFENSE_POTION);
                nbrPotion--;
                DisplayInventory(target->inventory);
                break;
            case 4:
                AddItem(target->inventory, GHOST_POTION);
                nbrPotion--;
                DisplayInventory(target->inventory);
                break;
            default:
                nbrPotion--;
                DisplayInventory(target->inventory);
                break;
        }
    }
    //DisplayInventory(target->inventory);
}

void init_inventory(Player* target){
    target->inventory = malloc(sizeof(itemNode)); // It's necessary to initialize the inventory property with a
                                                // memory address. That way we can pass the address instead of the pointer address.
                                                // Then our function would need to accept a pointer to a pointer to an itemNode
                                                // as an argument and that's too much overhead.
    if (target->inventory != NULL)
    {
        target->inventory->current = 0;
        target->inventory->next = NULL;
        target->inventory->previous = NULL;
    }
}*/

/*void printf_struct_equip(Equipment* equip)
{
    printf("Name : %s\nPrice : %d\n", equip->, equip->price);
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
    if (p_list != NULL) /* On v�rifie si notre liste a �t� allou�e */
    {
        struct node_eqpt *p_new = malloc(sizeof *p_new); /* Cr�ation d'un nouveau node_eqpt */
        if (p_new != NULL) /* On v�rifie si le malloc n'a pas �chou� */
        {
            p_new->equip = equip; /* On 'enregistre' notre donn�e */
            p_new->p_next = NULL; /* On fait pointer p_next vers NULL */
            if (p_list->p_tail == NULL) /* Cas o� notre liste est vide (pointeur vers fin de liste �  NULL) */
            {
                p_new->p_prev = NULL; /* On fait pointer p_prev vers NULL */
                p_list->p_head = p_new; /* On fait pointer la t�te de liste vers le nouvel �l�ment */
                p_list->p_tail = p_new; /* On fait pointer la fin de liste vers le nouvel �l�ment */
            }
            else /* Cas o� des �l�ments sont d�j� pr�sents dans notre liste */
            {
                p_list->p_tail->p_next = p_new; /* On relie le dernier �l�ment de la liste vers notre nouvel �l�ment (d�but du cha�nage) */
                p_new->p_prev = p_list->p_tail; /* On fait pointer p_prev vers le dernier �l�ment de la liste */
                p_list->p_tail = p_new; /* On fait pointer la fin de liste vers notre nouvel �l�ment (fin du cha�nage: 3 �tapes) */
            }
            p_list->length++; /* Incr�mentation de la taille de la liste */
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
