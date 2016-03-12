#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "player.h"
#include "fight.h"
#include "usableItem.h"
#include "gameUtil.h"
#include "mob.h"
#include "mobRace.h"
#include "dungeon.h"

#define NBR_POTIONS 3


void startMenu();
void displayMainMenu(Player *player);
void startNewGame();

int main(int argc, char *argv[])
{
    //startMenu();
    Player *Hero = NewPlayer();

    return(0);
}

void startMenu(){
    int userChoice = 0;

    system("cls");

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~~                                                   ~~~\n");
    printf("~~~        ***       LOST IN A DUNGEON      ***       ~~~\n");
    printf("~~~                         BY                        ~~~\n");
    printf("~~~                    --- EX@W ---                   ~~~\n");
    printf("~~~                                                   ~~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");


    printf("\n\n");
    printf("Would you like to continue a story or start a new one? \n");
    printf("_______________________________________________________\n");
    printf("1 : New Game\n");
    printf("2 : Load Game\n\n");

    userChoice = userInputInt();

    switch(userChoice){
        case 1:
            startNewGame();
            break;
        case 2:
            //loadExistingGame();
            break;
        default:
            break;
    }
}

void startNewGame(){

    system("cls");

    printf("Here start a great adventure, and everything starts with you, so tell me more about you...\n\n");

    Player *Hero = NewPlayer();

    printf("Dear %s, you have been sent by gods to free our caves full of evil creatures."
           "They infested our cities since the day...\n");

    displayMainMenu(Hero);
}

void displayMainMenu(Player *player){
    int userChoice = 0;

    system("cls");

    printf("<< IN TOWN >>\n\n");
    printf("----------------------------------\n");
    printf("Here are all the things you can do :\n");
    printf("--------------------------------------\n");
    printf("1 - Empty an infested Dungeon\n");
    printf("2 - Go to the tavern if you want to buy new stuff or potions\n");
    printf("3 - See your potion inventory\n");
    printf("4 - See your stuff inventory\n");
    printf("5 - See your equipment\n");

    userChoice = userInputInt();

    switch(userChoice){
        case 1:
            goThroughDungeon(player);
            break;
        case 2:
            goToTavern(player);
            break;
        case 3:
            show_inventory(player);
            break;
        case 4:
            show_stuff(player);
            break;
        case 5:
            calcAttributesWithEqpt(player);
            break;
        default:
            printf("Please enter a correct entry !\n");
            Sleep(1500);
            displayMainMenu(player);
            break;
    }

}

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
