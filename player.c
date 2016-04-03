#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"
#include "fight.h"
#include "gameUtil.h"
#include "usableItem.h"
#include "stuffItem.h"

#define POINT_TO_ATTRIBUTE 10

//Constructor for a player
Player* player_ctor(char name[50], int maxHP, int health, int attack, int defense, int relDef, int dodge, int potion, int gold, int score, int level, int life, int nbrKills, int nbrDungeons)
{
    Player* p = malloc(sizeof(Player));
    p->name[50] = name[50];
    p->maxHP = maxHP;
    p->health = health;
    p->attack = attack;
    p->defense = defense;
    p->relDef = relDef;
    p->dodge = dodge;
    p->potion = potion;
    p->gold = gold;
    p->score = score;
    p->level = level;
    p->life = life;
    p->nbrKills = nbrKills;
    p->nbrDungeons = nbrDungeons;
    return p;
}

// Creates player and set job/Eqpt/Potions.
Player* NewPlayer()
{
    Player *tempPlayer = player_ctor("Exaw", 0,0,0,0,0,0,0,0,0,1,3,0,0);

    SetName(tempPlayer);
    setJob(tempPlayer);
    initEqpt(tempPlayer);
    setStuffAtStart(tempPlayer);
    buildToStart(tempPlayer);
    setPotionAtStart(tempPlayer);

    return(tempPlayer);
}

//Ask to the user the name of the player
void SetName(Player *target)
{
    char* name;
    printf("Please give a name for your character : ");
    name = userInputChar();
    strcpy(target->name, name);

    system("cls");

    printf("Hi dear %s, future great hero\n", target->name);
    Sleep(2000);
    printf("What do you do in your life ?\n\n");
    Sleep(2000);
}

//Set the job and give a starting stuff to the player
int setJob(Player *target)
{
    int choice = 0;

    printf("Please select your job : \n\n1 : WARRIOR (Start with a SWORD and a TEXTILE ARMOR)\n");
    printf("2 : RANGER (Start with a BOW and a TINY SHORT)\n");
    printf("3 : WIZARD (Start with a WAND and a ROBE)\n\n(WARNING : NO JOB if you enter a wrong input \"not recommended\")\n");
    choice = userInputInt();
    choice--;

    // Assign stats based on the given job.
    switch(choice) {
        case WARRIOR:
            target->health += 100;
            target->maxHP += 100;
            target->attack += 10;
            target->defense += 2;
            target->relDef += 2;
            target->dodge += 1;
            target->job = WARRIOR;
            break;
        case RANGER:
            target->health += 100;
            target->maxHP += 100;
            target->attack += 10;
            target->defense += 2;
            target->relDef += 3;
            target->dodge += 5;
            target->job = RANGER;
            break;
        case WIZARD:
            target->health += 90;
            target->maxHP += 90;
            target->attack += 8;
            target->defense += 1;
            target->relDef += 1;
            target->dodge += 3;
            target->job = WIZARD;
            break;
        default:
            target->health += 10;
            target->maxHP += 10;
            target->attack += 0;
            target->defense += 1;
            target->relDef += 1;
            target->dodge += 1;
            target->job = -1;
            break;
    }
    return(0);
}

//Attribute the stats to start
void buildToStart(Player *target)
{
    int skillPTS = POINT_TO_ATTRIBUTE;

    system("cls");

    printf("Hi %s, time to set your stats :\n", target->name);
    printf("You have %d points to attribute, please select what you want to increase :\n", skillPTS);

    while(skillPTS > 0){

        if(skillPTS < 10){
            printf("You still have %d points to attribute...\n\n", skillPTS);
        }

        calcAttributesWithEqpt(target);
        printf("1: maxHP\n2: ATT\n3: AbsDEF\n4: RelDEF\n5: ESQ\n");

        switch(userInputInt()){
            case 1:
                target->maxHP += 1;
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
        system("cls");
    }
}

//Player menu to see potions/Stuff/equipment/stats
int menu_player(Player *target, int callingPlace)
{
    int userChoice;

    system("cls");
    color(15, 0);

    printf("########################\n");
    printf("#1 : POTION inventory  #\n");
    printf("#2 : STUFF Inventory   #\n");
    printf("#3 : EQUIPMENT         #\n");
    printf("#4 : CHARACTER stats   #\n");
    printf("#>> press 0 to return  #\n");
    printf("########################\n");

    userChoice = userInputInt();

    switch(userChoice){
        case 1:
            show_inventory(target);
            menu_player(target, 0);
            break;
        case 2:
            show_stuff(target);
            menu_player(target, 0);
            break;
        case 3:
            displayEqpt(target);
            menu_player(target, 0);
            break;
        case 4:
            calcAttributesWithEqpt(target);
            printf("Press 0 to return\n");
            while(userChoice != 0){
                userChoice = userInputInt();
            }
            menu_player(target, 0);
            break;
        case 0:
            if(callingPlace == 0){
                displayMainMenu(target);
            }
            break;
        default:
            printf("Please, write only a correct entry !\n");
            break;
    }
}

//Give a name for the chosen job
char* setJobNames(int job)
{
    switch(job)
    {
        case WARRIOR:
            return "WARRIOR";
        case RANGER:
            return "RANGER";
        case WIZARD:
            return "WIZARD";
        default:
            return "NO JOB";
    }
}
