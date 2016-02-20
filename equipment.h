#ifndef EQUIPMENT_H_INCLUDED
#define EQUIPMENT_H_INCLUDED

/*- Equipment.h : contient l'ensemble des objets porté par une créature :
			- tete
			- torse
			- jambe
			- botte
			- main droite
			- main gauche*/

typedef struct Equipment{
    StuffItem* head;
    StuffItem* body;
    StuffItem* legs;
    StuffItem* foots;
    StuffItem* rightHand;
    StuffItem* leftHand;
}Equipment;

#endif // EQUIPMENT_H_INCLUDED
