#include <stdio.h>
#include <stdlib.h>

#include "equipment.h"

/*- Equipment.c : contient les fonctions suivantes :
			- calcAttack(Equipment* equipment, Mob* mob)
			- calcRelDef(Equipment* equipment, Mob* mob)
			- calcAbsDef(Equipment* equipment, Mob* mob)*/

Equipment* Equipment_ctor(StuffItem* head, StuffItem* body, StuffItem* legs, StuffItem* foots, StuffItem* rightHand, StuffItem* leftHand){
    Equipment* p = malloc(sizeof(Equipment));
    p->head = head;
    p->body = body;
    p->legs = legs;
    p->foots = foots;
    p->rightHand = rightHand;
    p->leftHand = leftHand;
    return p;
}

/*void calcAttack(Equipment* equipment, Mob* mob){
}

void calcAttack(Equipment* equipment, Mob* mob){
}

void calcAbsDef(Equipment* equipment, Mob* mob){
}*/
