#include <stdio.h>
#include <stdlib.h>

#include "equipment.h"
#include "stuffItem.h"
#include "player.h"

/*- Equipment.c : contient les fonctions suivantes :
			- calcAttack(Equipment* equipment, Mob* mob)
			- calcRelDef(Equipment* equipment, Mob* mob)
			- calcAbsDef(Equipment* equipment, Mob* mob)*/

/*void set_equipment(Player *target){
    target->build = malloc(sizeof(StuffItem));
    build[HELMET] = 0;
    build[ARMOR] = *stuffItem_ctor("Textile Armor", 10, ARMOR, 0, 0, 1, 10);
    build[LEFT_HAND] = 0;
    build[RIGHT_HAND] = *stuffItem_ctor("My First Sword", 10, RIGHT_HAND, 0, 10, 0, 0);
    build[LEGGINGS] = 0;
    build[BOOTS] = 0;
    int i = 0;
    for(i = 0; i < 6; i++){
        if(target->build[i] != 0){

        }
    }
}*/

/*void initEqt(Player *target){
    StuffItem* rienHead = stuffItem_ctor(' ',0,HELMET,0,0,0,0);
    StuffItem* rienBody = stuffItem_ctor(' ',0,ARMOR,0,0,0,0);
    StuffItem* rienLeft = stuffItem_ctor(' ',0,LEFT_HAND,0,0,0,0);
    StuffItem* rienRight = stuffItem_ctor(' ',0,RIGHT_HAND,0,0,0,0);
    StuffItem* rienLegs = stuffItem_ctor(' ',0,LEGGINGS,0,0,0,0);
    StuffItem* rienBoot = stuffItem_ctor(' ',0,BOOTS,0,0,0,0);
    Equipment* myEqpt = Equipment_ctor(rienHead,rienBody,rienLegs,rienBoot,rienRight,rienLeft);
    target->equiped = myEqpt;
}

void setEqpt(){

}*/

void displayEqpt(Player *target){
    /*printf("                  /88888888888888888888888888\          \n");
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
    printf("                                              \\___/     \n");*/
}

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
