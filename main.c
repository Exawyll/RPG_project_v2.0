#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "player.h"
#include "fight.h"
#include "usableItem.h"
#include "gameUtil.h"
#include "mob.h"
#include "mobRace.h"
#include "dungeon.h"
#include "equipment.h"

int startMenu();
void displayMainMenu(Player *player);
void startNewGame();
Player* loadYourGame();
void displayGameOverMenu(Player *player);
void saveYourGame(Player *player);

int main(int argc, char *argv[])
{
    startMenu();

    return(0);
}

int startMenu()
{
    Player* newPlayer;
    int userChoice = 0;

    //system("cls");

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~~                                                   ~~~\n");
    printf("~~~        ***       LOST IN A DUNGEON      ***       ~~~\n");
    printf("~~~                         BY                        ~~~\n");
    printf("~~~                    --- EX@W ---                   ~~~\n");
    printf("~~~                                                   ~~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\n");
    printf("Would you like to continue a story or start a new one? \n");
    printf("-------------------------------------------------------\n");
    printf("1 : New Game\n");
    printf("2 : Load Game\n\n");
    printf("Press 0 to exit the game...\n");

    userChoice = userInputInt();

    switch(userChoice){
        case 1:
            startNewGame();
            break;
        case 2:
            newPlayer = loadYourGame();
            displayMainMenu(newPlayer);
            break;
        case 0:
            return (0);
        default:
            break;
    }
    return (0);
}

void startNewGame()
{
    system("cls");

    printf("Here start a great adventure, and everything starts with you,\nso tell me more about you...\n\n");

    Player *Hero = NewPlayer();

    //printf("Dear %s, you have been sent by gods to free our caves\nfull of evil creatures.\n\nThey infested our cities since the day...\n\n");

    displayMainMenu(Hero);
}

void displayMainMenu(Player *player)
{
    int userChoice = 0;

    //system("cls");

    printf("<< IN TOWN >>\n\n");
    printf("----------------------------------\n");
    printf("Here are all the things you can do :\n");
    printf("--------------------------------------\n");
    printf("1 - Empty an infested Dungeon\n");
    printf("2 - Go to the tavern if you want to buy new stuff or potions\n");
    printf("3 - Display player menu\n");
    printf("4 - Save and quit\n");

    while(1){
        userChoice = userInputInt();

        switch(userChoice){
            case 1:
                goThroughDungeon(player);
                break;
            case 2:
                goToTavern(player);
                break;
            case 3:
                menu_player(player, 0);
                break;
            case 4:
                saveYourGame(player);
                startMenu();
                break;
            default:
                printf("Please enter a correct entry !\n");
                Sleep(1500);
                displayMainMenu(player);
                break;
        }
    }

}

void displayGameOverMenu(Player *player){
    int userChoice;

    system("cls");

    printf("#####################################\n");
    printf("############# GAME OVER #############\n");
    printf("#####################################\n");

    printf("\nYour score is -> %d\n", player->score);

    if(player->life > 0){
        printf("\nYou still have %d life\n", player->life);
        printf("Would you like to continue ?\n");
        printf("1 : yes\n2 : No\n");
        userChoice = userInputInt();

        switch(userChoice){
            case 1:
                player->life--;
                displayMainMenu(player);
                break;
            case 2:
                printf("You are dead, you finished the game with :\n");
                printf("Score -> %d\n", player->score);
                printf("Try to do better next time...\n");
                Sleep(5000);
                startMenu();
                break;
            default:
                break;
        }
    }
    else{
        printf("You are dead, you finished the game with :\n");
        printf("Score -> %d\n", player->score);
        printf("Try to do better next time...\n");
        Sleep(5000);
        startMenu();
    }
}

void saveYourGame(Player *player)
{
    Player *toSave = malloc(sizeof(Player));
    strcpy(toSave->name, player->name);
    toSave->attack = player->attack;
    toSave->defense = player->defense;
    toSave->dodge = player->dodge;
    toSave->gold = player->gold;
    toSave->health = player->health;
    toSave->job = player->job;
    toSave->level = player->level;
    toSave->life = player->life;
    toSave->relDef = player->relDef;
    toSave->score = player->score;
    writeToFile_item(player->inventory);
    writeToFile_stuff(player->armory);
    writeToFile_eqpt(player->build);
    FILE * saved_player = fopen("./saved_player.txt", "w+");
    if (saved_player != NULL) {
        fwrite(toSave, sizeof(Player), 1, saved_player);
        fclose(saved_player);
    }
}

Player* loadYourGame()
{
    int i = 0;
    Player *loadPlayer = malloc(sizeof(Player));
    DlistItem *loadInventory = useItem_new();
    DlistStuff *loadArmory = item_new();
    StuffItem** loadBuild = malloc(sizeof(StuffItem));

    initEqpt(loadPlayer);
    loadInventory = readFromFile_item();
    loadArmory = readFromFile_stuff();
    loadBuild = readFromFile_eqpt();

    printf("price : %d\n", loadBuild[1]->price);

    FILE * saved_player = fopen("./saved_player.txt", "r");
    if (saved_player != NULL) {
        fread(loadPlayer, sizeof(Player), 1, saved_player);
        fclose(saved_player);
    }

    loadPlayer->inventory = loadInventory;
    loadPlayer->armory = loadArmory;
    for(i = 0; i < 6; i++){
        loadPlayer->build[i] = loadBuild[i];
    }
    return loadPlayer;
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
