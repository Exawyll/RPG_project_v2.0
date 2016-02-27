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
    for(i = 0; i < 6; i++){
        if(target->build[i])
        {
            bonusATT = target->build[i]->I_bonusATT;
            bonusHP = target->build[i]->I_bonusHP;
            bonusDEF = target->build[i]->I_bonusDEFAbs;
            bonusDEFRel = target->build[i]->I_bonusDEFRel;

            if(bonusATT > 0)
            {
                target->attack += bonusATT;
            }
            if(bonusDEF > 0)
            {
                target->defense += bonusDEF;
            }
            if(bonusDEFRel > 0)
            {
                target->relDef += bonusDEFRel;
            }
            if(bonusHP > 0)
            {
                target->health += bonusHP;
            }
        }
    }
}

void displayEqpt(Player *target)
{
    int i = 0;
    for(i = 0; i < 6; i++){
        if(target->build[i])
        {
            printf("Name :%s\n", target->build[i]->name);
            printf("Price :%d\n", target->build[i]->price);
            printf("Type :%d\n", target->build[i]->type);
            printf("ATT :%d\n", target->build[i]->I_bonusATT);
            printf("DEF :%d\n", target->build[i]->I_bonusDEFAbs);
            printf("DEFRel :%d\n", target->build[i]->I_bonusDEFRel);
            printf("HP :%d\n", target->build[i]->I_bonusHP);
        }
    }
}

void initEqt(Player *target){
    int i = 0;
    for(i = 0; i < 0; i++){
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
