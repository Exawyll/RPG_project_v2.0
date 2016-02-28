#include <stdio.h>
#include <stdlib.h>

#include "equipment.h"
#include "stuffItem.h"
#include "player.h"

/*- Equipment.c : contient les fonctions suivantes :
			- calcAttack(Equipment* equipment, Mob* mob)
			- calcRelDef(Equipment* equipment, Mob* mob)
			- calcAbsDef(Equipment* equipment, Mob* mob)*/

void calcAttributesWithEqpt(Player *target)
{
    int bonusATT = 0;
    int bonusHP = 0;
    int bonusDEF = 0;
    int bonusDEFRel = 0;
    int i = 0;
    int health = 0;
    int attack = 0;
    int defense = 0;
    int relDef = 0;
    int dodge = 0;

    health= target->health;
    attack = target->attack;
    defense = target->defense;
    relDef = target->relDef;

    for(i = 0; i < 6; i++){
        if(target->build[i])
        {
            bonusATT = target->build[i]->I_bonusATT;
            bonusHP = target->build[i]->I_bonusHP;
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
            if(bonusHP > 0)
            {
                health += bonusHP;
            }
        }
    }
    displayStatsPlayerWithEqpt(target, health, attack, defense, relDef);
}

void displayStatsPlayerWithEqpt(Player *target, int health, int attack, int defense, int relDef){
    printf("Your stats with equipment : \n");
    printf("Name: %s\nHealth: %d\nAttack: %d\nDefense : %d\nRelative Defense : %d\nDodge : %d\n\n", target->name, health, attack, defense, relDef, target->dodge);
}

void displayEqpt(Player *target)
{
    char *name;
    int price = 0;
    int type = 0;
    int bonusATT = 0;
    int bonusHP = 0;
    int bonusDEF = 0;
    int bonusDEFRel = 0;
    int bonusDEFAbs = 0;
    int i = 0;

    printf("-------------------------------\n");
    printf("-          EQUIPPED           -\n");
    printf("-------------------------------\n");

    for(i = 0; i < 6; i++){
        if(target->build[i])
        {
            name = target->build[i]->name;
            price = target->build[i]->price;
            type = target->build[i]->type;
            bonusATT = target->build[i]->I_bonusATT;
            bonusHP = target->build[i]->I_bonusHP;
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
                        printf("HAND --> ");
                        break;
                    case LEFT_HAND:
                        printf("HAND --> ");
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
                printf("         HP :%d\n", bonusHP);
                printf("         ATT :%d\n", bonusATT);
                printf("         DEF :%d\n", bonusDEFAbs);
                printf("         DEFRel :%d\n", bonusDEFRel);
            }
        }
    }
    printf("-------------------------------\n");
    printf("\n");
}

void initEqpt(Player *target){
    int i = 0;
    for(i = 0; i < 6; i++){
        StuffItem* fakeObject = stuffItem_ctor(' ',0,i,0,0,0,0);
        target->build[i] = fakeObject;
    }
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

/*void calcAttack(Equipment* equipment, Mob* mob){
}

void calcAttack(Equipment* equipment, Mob* mob){
}

void calcAbsDef(Equipment* equipment, Mob* mob){
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
