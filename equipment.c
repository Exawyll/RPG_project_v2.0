#include <stdio.h>
#include <stdlib.h>

#include "equipment.h"
#include "stuffItem.h"
#include "player.h"

int calcAttack(Player *target){
    int bonusATT = 0;
    int attack = 0;
    int i = 0;
    attack = target->attack;

    for(i = 0; i < 6; i++){
        bonusATT = target->build[i]->I_bonusATT;
        if(bonusATT > 0){
            attack += bonusATT;
        }
    }
    return attack;
}

int calcRelDef(Player *target){
    int bonusDEFRel = 0;
    int relDef = 0;
    int i = 0;
    relDef = target->relDef;

    for(i = 0; i < 6; i++){
        bonusDEFRel = target->build[i]->I_bonusDEFRel;
        if(bonusDEFRel > 0){
            relDef += bonusDEFRel;
        }
    }
    return relDef;
}

int calcAbsDef(Player *target){
    int bonusDEF = 0;
    int defense = 0;
    int i = 0;
    defense = target->defense;

    for(i = 0; i < 6; i++){
        bonusDEF = target->build[i]->I_bonusDEFAbs;
        if(bonusDEF > 0){
            defense += bonusDEF;
        }
    }
    return defense;
}

void calcAttributesWithEqpt(Player *target)
{
    int bonusATT = 0;
    int bonusDEF = 0;
    int bonusDEFRel = 0;
    int i = 0;
    int attack = 0;
    int defense = 0;
    int relDef = 0;

    attack = target->attack;
    defense = target->defense;
    relDef = target->relDef;

    for(i = 0; i < 6; i++){
        if(target->build[i])
        {
            bonusATT = target->build[i]->I_bonusATT;
            bonusDEF = target->build[i]->I_bonusDEFAbs;
            bonusDEFRel = target->build[i]->I_bonusDEFRel;

            if(bonusATT > 0)
            {
                attack += bonusATT;
            }
            if(bonusDEF > 0)
            {
                defense += bonusDEF;
            }
            if(bonusDEFRel > 0)
            {
                relDef += bonusDEFRel;
            }
        }
    }
    displayStatsPlayerWithEqpt(target, attack, defense, relDef);
}

void displayStatsPlayerWithEqpt(Player *target, int attack, int defense, int relDef){
    printf("Your stats with equipment : \n");
    printf("Level : %d\nName: %s\nHealth: %d/%d\nAttack: %d\nDefense : %d\nRelative Defense : %d\nDodge : %d\n", target->level, target->name, target->health, target->maxHP, attack, defense, relDef, target->dodge);
    printf("Gold: %d\nScore: %d\nLife: %d\nKills: %d\n\n", target->gold, target->score, target->life, target->nbrKills);
}

void displayEqpt(Player *target)
{
    char *name;
    int price = 0;
    int type = 0;
    int bonusATT = 0;
    int bonusDEF = 0;
    int bonusDEFRel = 0;
    int bonusDEFAbs = 0;
    int i = 0;

    printf("-------------------------------\n");
    printf("-          EQUIPPED           -\n");
    printf("-------------------------------\n");

    for(i = 0; i < 6; i++){
        if(target->build[i] != NULL)
        {
            name = target->build[i]->name;
            price = target->build[i]->price;
            type = target->build[i]->type;
            bonusATT = target->build[i]->I_bonusATT;
            bonusDEFAbs = target->build[i]->I_bonusDEFAbs;
            bonusDEFRel = target->build[i]->I_bonusDEFRel;
            if(name != ' '){
                switch(type){
                    case HELMET:
                        printf("HEAD --> ");
                        break;
                    case ARMOR:
                        printf("BODY --> ");
                        break;
                    case RIGHT_HAND:
                        printf("R.HAND-> ");
                        break;
                    case LEFT_HAND:
                        printf("L.HAND-> ");
                        break;
                    case LEGGINGS:
                        printf("LEGS --> ");
                        break;
                    case BOOTS:
                        printf("FOOT --> ");
                        break;
                }
                printf("Name :%s\n", name);
                printf("         Price :%d\n", price);
                printf("         ATT :%d\n", bonusATT);
                printf("         DEF :%d\n", bonusDEFAbs);
                printf("         DEFRel :%d\n", bonusDEFRel);
            }
        }
    }
    printf("-------------------------------\n");
    displayEqptMenu(target);
    printf("\n");
}

void displayEqptMenu(Player* player)
{
    int userChoice;
    int userChoice2;
    printf("press 1 to unequip stuff or 0 to go back\n");
    userChoice = userInputInt();
    switch(userChoice){
        case 1:
            printf("Select the weapon to unequip\n");
            printf("1:HEAD\n2:BODY\n3:R.HAND\n4:L.HAND\n5:LEGS\n6:FOOT\n");
            userChoice2 = userInputInt();
            userChoice2--;
            Unequip(player, userChoice2);
            break;
        case 0:
            //menu_player(player, 0);
            return (0);
    }
}

void initEqpt(Player *target){
    int i = 0;
    for(i = 0; i < 6; i++){
        StuffItem* fakeObject = stuffItem_ctor(' ',0,i,0,0,0);
        target->build[i] = malloc(sizeof(StuffItem));
        target->build[i] = fakeObject;
    }
}

//How to save the stuff equipped on the player
void writeToFile_eqpt(StuffItem** build){
    int i = 0;
    FILE *fptr;
    fptr=fopen("./list_eqpt.txt","w+");

    StuffItem* stuff = malloc(sizeof(StuffItem));

    for(i = 0; i < 6; i++)
    {
        if (build[i] != NULL)
        {
        stuff = stuffItem_ctor(build[i]->name,build[i]->price,build[i]->type,build[i]->I_bonusATT,build[i]->I_bonusDEFRel,build[i]->I_bonusDEFAbs);
        fwrite(stuff,sizeof(StuffItem),1,fptr);
        }
    }
    printf("\n");
    fclose(fptr);
}

//Read a list of structure to display it
StuffItem** readFromFile_eqpt(){
    StuffItem** build = malloc(sizeof(StuffItem));
    StuffItem* stuff = malloc(sizeof(StuffItem));
    StuffItem* object2 = malloc(sizeof(StuffItem));
    FILE *fptr;

    fptr=fopen("./list_eqpt.txt","r");

    if (fptr) {
        /* File was opened successfully. */

        /* Attempt to read element one by one */
        while (fread(stuff,sizeof(StuffItem),1,fptr) == 1) {
            switch(stuff->type){
                case HELMET:
                    build[HELMET] = stuffItem_ctor(stuff->name,stuff->price,stuff->type,stuff->I_bonusATT,stuff->I_bonusDEFRel,stuff->I_bonusDEFAbs);
                    break;
                case ARMOR:
                    build[ARMOR] = stuffItem_ctor(stuff->name,stuff->price,stuff->type,stuff->I_bonusATT,stuff->I_bonusDEFRel,stuff->I_bonusDEFAbs);;
                    break;
                case RIGHT_HAND:
                    build[RIGHT_HAND] = stuffItem_ctor(stuff->name,stuff->price,stuff->type,stuff->I_bonusATT,stuff->I_bonusDEFRel,stuff->I_bonusDEFAbs);;
                    break;
                case LEFT_HAND:
                    build[LEFT_HAND] = stuffItem_ctor(stuff->name,stuff->price,stuff->type,stuff->I_bonusATT,stuff->I_bonusDEFRel,stuff->I_bonusDEFAbs);;
                    break;
                case LEGGINGS:
                    build[LEGGINGS] = stuffItem_ctor(stuff->name,stuff->price,stuff->type,stuff->I_bonusATT,stuff->I_bonusDEFRel,stuff->I_bonusDEFAbs);;
                    break;
                case BOOTS:
                    build[BOOTS] = stuffItem_ctor(stuff->name,stuff->price,stuff->type,stuff->I_bonusATT,stuff->I_bonusDEFRel,stuff->I_bonusDEFAbs);;
                    break;
                case TWO_HAND:
                    object2 = stuffItem_ctor("RIGHT_HAND Copy",0,LEFT_HAND,0,0,0);
                    build[RIGHT_HAND] = stuffItem_ctor(stuff->name,stuff->price,stuff->type,stuff->I_bonusATT,stuff->I_bonusDEFRel,stuff->I_bonusDEFAbs);;
                    build[LEFT_HAND] = object2;
                    break;
                default:
                    break;
            }
        }
        printf("\n");
    }

    fclose(fptr);

    return build;
}

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
