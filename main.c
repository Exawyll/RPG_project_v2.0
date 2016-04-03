#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "player.h"

//Prototype to avoid implicit declaration warnings
void goToTavern(Player *player);
void goThroughDungeon(Player *player);
int userInputInt();
void color(int t,int f);
int startMenu();
void displayMainMenu(Player *player);
void startNewGame();
Player* loadYourGame();
void displayGameOverMenu(Player *player);
void saveYourGame(Player *player);

//Starting block of the program
int main(int argc, char *argv[])
{
    startMenu();

    return(0);
}

//First menu where you can start or load
int startMenu()
{
    Player* newPlayer;
    int userChoice = 0;

    system("cls");
    color(12, 0);

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~~                                                   ~~~\n");
    printf("~~~        ***       LOST IN A DUNGEON      ***       ~~~\n");
    printf("~~~                         BY                        ~~~\n");
    printf("~~~                    --- EX@W ---                   ~~~\n");
    printf("~~~                                                   ~~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    color(15, 0);

    printf("\n\n");
    printf("Would you like to continue a story or start a new one? \n");
    printf("-------------------------------------------------------\n");
    printf("1 : New Game\n");
    printf("2 : Load Game\n\n");
    printf("Press enter to exit the game...\n");

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
            exit (0);
        default:
            printf("Please enter a correct entry...\n");
            Sleep(2000);
            startMenu();
            break;
    }
    return (0);
}

//Starting story after new game
void startNewGame()
{
    system("cls");

    printf("Here start a great adventure.\n\n");
    Sleep(2000);
    printf("...Hello young Hero\n\n");
    Sleep(1000);
    printf("you have been sent by gods to help us\n\n");
    Sleep(1000);
    printf("all our caves are now full of evil creatures\n\n");
    Sleep(1000);
    printf("they infested our cities and take all our needs\n\n");
    Sleep(1000);
    printf("we don't have anything left and our sons and wifes\n\n");
    Sleep(1000);
    printf("need food and drugs to survive\n\n");
    Sleep(1000);
    printf("you are our only hope\n\n");
    Sleep(1000);
    printf("so tell me more about you...\n\n");
    Sleep(3000);

    Player *Hero = NewPlayer();

    displayMainMenu(Hero);
}

//Main menu in town
void displayMainMenu(Player *player)
{
    int userChoice = 0;

    system("cls");
    color(10, 0);

    printf("<< IN TOWN >>\n\n");
    printf("----------------------------------\n");
    printf("Here are all the things you can do :\n");
    printf("--------------------------------------\n\n");
    color(11, 0);
    printf("1 - Empty an infested Dungeon\n");
    color(14, 0);
    printf("2 - Go to the tavern if you want to buy new stuff or potions\n");
    color(15, 0);
    printf("3 - Display player menu\n");
    color(12, 0);
    printf("4 - Save and quit\n");
    color(15, 0);

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

//Display the game over menu
void displayGameOverMenu(Player *player)
{
    int userChoice;
    int flag = 0;
    int i = 0;

    system("cls");

    while(flag < 10){
        for(i = 0; i < 15; i++){
            Sleep(10);
            system("cls");
            color(i, 0);

            printf("#####################################\n");
            printf("############# GAME OVER #############\n");
            printf("#####################################\n");

            printf("\nYour score is -> %d\n", player->score);
            printf("Dungeon(s) done : %d\n", player->nbrDungeons);
            printf("You killed %d monster(s)...\n", player->nbrKills);
        }
        flag++;
    }

    if(player->life > 0){
        printf("\nYou still have %d life(s)\n", player->life);
        printf("Would you like to continue ?\n");
        printf("1 : yes\n2 : No\n");
        userChoice = userInputInt();

        switch(userChoice){
            case 1:
                player->life--;
                player->health = player->maxHP;
                player->gold = 0;
                setPotionAtStart(player);
                displayMainMenu(player);
                break;
            default:
                break;
        }
    }
    printf("You are dead, you finished the game with :\n");
    printf("Score -> %d\n", player->score);
    printf("Kills -> %d\n", player->nbrKills);
    printf("Dungeon(s) -> %d\n", player->nbrDungeons);
    printf("Try to do better next time...\n");
    Sleep(5000);
    startMenu();
}

//Save current player in a file
void saveYourGame(Player *player)
{
    Player *toSave = malloc(sizeof(Player));
    strcpy(toSave->name, player->name);
    toSave->attack = player->attack;
    toSave->defense = player->defense;
    toSave->dodge = player->dodge;
    toSave->gold = player->gold;
    toSave->health = player->health;
    toSave->maxHP = player->maxHP;
    toSave->job = player->job;
    toSave->level = player->level;
    toSave->life = player->life;
    toSave->relDef = player->relDef;
    toSave->score = player->score;
    toSave->nbrKills = player->nbrKills;
    toSave->nbrDungeons = player->nbrDungeons;
    writeToFile_item(player->inventory);
    writeToFile_stuff(player->armory);
    writeToFile_eqpt(player->build);
    FILE * saved_player = fopen("./saved_player.txt", "w+");
    if (saved_player != NULL) {
        fwrite(toSave, sizeof(Player), 1, saved_player);
        fclose(saved_player);
    }
}

//load existing player from a file
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
