#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"
#include "fight.h"
#include "gameUtil.h"
#include "usableItem.h"
#include "stuffItem.h"

#define POINT_TO_ATTRIBUTE 10

//Resume the structurePlayer
/*struct playerStructure {
    char name[50];
    int health;
    int attack;
    int defense;
    int relDef;
    int dodge;
};*/

// Takes a player as an argument and prints their name, health, and attack. Returns nothing.
void DisplayStats (struct playerStructure *Target) {
    // We don't want to keep retyping all this.
    printf("Name: %s\nHealth: %d\nAttack: %d\nDefense : %d\nRelative Defense : %d\nDodge : %d\n\n", Target->name, Target->health, Target->attack, Target->defense, Target->relDef, Target->dodge);
}

// Creates player and set job.
Player* NewPlayer() {
    // Allocate memory to player pointer.
    Player *tempPlayer = malloc(sizeof(Player));

    // Keep track of players created.
    // The static int allow to keep the value even after the function return 0.
    static int PlayersCreated = 0;

    if (PlayersCreated > 0) {
        tempPlayer->autoPilot = true;
    }
    else {
        tempPlayer->autoPilot = false;
        SetName(tempPlayer);
        //initEqt(tempPlayer);
        //setJob(tempPlayer);
        //setStuffAtStart(tempPlayer);
        //buildToStart(tempPlayer);
        //setPotionAtStart(tempPlayer);

    }
    ++PlayersCreated;

    return(tempPlayer); // Return memory address of player.
}

void SetName(Player *target) {
    char* name;
    printf("Please give a name for your character : ");
    name = userInputChar();
    strcpy(target->name, name);
}

int setJob(Player *target){
    int choice = 0;

    printf("Please select your job : \n1 : WARRIOR (Start with a SWORD and a TEXTILE ARMOR)\n");
    printf("2 : RANGER (Start with a BOW and a TINY SHORT)\n");
    printf("3 : WIZARD (Start with a WAND and a ROBE)\n(NO JOB if you enter a wrong input \"not recommended\")");
    choice = userInputInt();

    // Assign stats based on the given job.
    switch(choice) {
        case 1:
            //WARRIOR
            target->health += 60;
            target->attack += 10;
            target->defense += 10;
            target->relDef += 5;
            target->dodge += 1;
            target->job = WARRIOR;
            break;
        case 2:
            //RANGER
            target->health += 50;
            target->attack += 10;
            target->defense += 8;
            target->relDef += 6;
            target->job = RANGER;
            break;
        case 3:
            //WIZARD
            target->health += 40;
            target->attack += 8;
            target->defense += 6;
            target->relDef += 5;
            target->dodge += 3;
            target->job = WIZARD;
            break;
        default:
            target->health += 10;
            target->attack += 0;
            target->defense += 20;
            target->relDef += 10;
            target->dodge += 5;
            target->job = -1;
            break;
    }
    return(0);
}

void buildToStart(Player *target){
    int skillPTS = POINT_TO_ATTRIBUTE;

    printf("\nHi %s, time to set your stats :\n", target->name);
    DisplayStats(target);
    printf("You have %d points to attribute, please select what you want to increase :\n", skillPTS);

    while(skillPTS > 0){
        printf("1: HP\n2: ATT\n3: AbsDEF\n4: RelDEF\n5: ESQ\n");

        switch(userInputInt()){
            case 1:
                target->health += 1;
                skillPTS -=1;
                break;
            case 2:
                target->attack += 1;
                skillPTS -= 1;
                break;
            case 3:
                target->defense += 1;
                skillPTS -= 1;
                break;
            case 4:
                target->relDef += 1;
                skillPTS -= 1;
                break;
            case 5:
                target->dodge += 1;
                skillPTS -= 1;
                break;
            default:
                break;
        }
        printf("\nYou still have %d points to attribute...\n", skillPTS);
        DisplayStats(target);
    }
}

void menu_player(Player *target){
    int userChoice;

    printf("########################\n");
    printf("#1 : Inventory         #\n");
    printf("########################\n");

    userChoice = userInputInt();

    switch(userChoice){
        case 1:
            show_inventory(target);
            break;
        default:
            break;
    }
}
