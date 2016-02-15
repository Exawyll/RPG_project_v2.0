

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
