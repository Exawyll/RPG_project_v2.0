#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "dungeon.h"
#include "fight.h"
#include "mob.h"
#include "mobRace.h"
#include "player.h"
#include "gameUtil.h"

//Generation of mobs for dungeons, depending on the level of the player
Mob* generateMob(Player *player)
{
    Mob* myMob = malloc(sizeof(Mob));
    int randNbr;

    //weakest mobs if level under 5
    if((player->level) < 5){
        randNbr = doRand(1, 3);
        switch(randNbr){
            case 1:
                myMob = createGobelin();
                break;
            case 2:
                myMob = createSkeleton();
                break;
            case 3:
                myMob = createOrc();
                break;
            default:
                break;
        }
    }

    //Can generate all the mobs if level between 5 and 10
    else if((player->level) >= 5 && (player->level) < 10){
        randNbr = doRand(1, 7);
        switch(randNbr){
            case 1:
                myMob = createGobelin();
                break;
            case 2:
                myMob = createSkeleton();
                break;
            case 3:
                myMob = createOrc();
                break;
            case 4:
                myMob = createZombie();
                break;
            case 5:
                myMob = createUrukai();
                break;
            case 6:
                myMob = createTroll();
                break;
            case 7:
                myMob = createDragon();
                break;
            default:
                break;
        }
    }

    //Generation of cheated mobs if level of the player over 10
    else{
        int race = doRand(1, 7);
        int health = doRand(170, 300);
        int maxHP = health;
        int attack = doRand(40, 100);
        int defense = doRand(10, 30);
        int relDef = doRand(5, 20);
        int dodge = doRand(5, 20);

        myMob = mob_ctor(race, health, maxHP, attack, defense, relDef, dodge);
    }
    return myMob;
}

//Randomize with a dice 15 for awards in dungeons if you begin to search
void researchInDungeon(Player *player)
{
    int luckyDice = doRand(1,15);
    int giftGold = doRand(50, 350);
    StuffItem *giftStuff;
    switch(luckyDice){
        case 15:
            giftStuff = generateWeapon();
            printf("So lucky you are, you just found a new weapon !\n");
            item_append(player->armory, *giftStuff);
            Sleep(2000);
            break;
        case 1:
            printf("Oh oh it's a trap, you lose 20 HP !\n");
            player->health -= 20;
            Sleep(2000);
            if (player->health < 0) {
                displayGameOverMenu(player);
            }
            break;
        case 10:
            printf("Good job you found %d gold !", giftGold);
            player->gold += giftGold;
            Sleep(2000);
            break;
        default:
            printf("After few minutes looking, you found nothing...\n");
            Sleep(2000);
            break;
    }
}

//Menu in dungeon with user choice
int choiceInDungeon()
{
    int userChoice = -1;

    system("cls");
    color(11, 0);

    printf("<< IN DUNGEON >>\n\n");
    printf("You hear screams all around you...\n\n");
    printf("------------------------\n");
    printf("What do you want to do :\n");
    printf("------------------------\n");
    printf("1 - Go directly for a fight\n");
    printf("2 - Look around for a treasure\n");
    printf("3 - Display potions\n");
    printf("4 - Display stuff\n");
    printf("5 - Display equipment\n");
    printf("6 - Display stats\n");
    printf("7 - Go back in town (you won't be able to continue this dungeon)\n");

    userChoice = userInputInt();

    return userChoice;
}

//Calling of the different actions available in a dungeon
void switchDungeons(Player *player)
{
    Mob* unMob;
    int userChoice;
    int dungeonSize = calculateNomberOfMob(player);
    int flag = 0;

    while(dungeonSize > 0){
        switch(choiceInDungeon()){
            case 1:
                flag = player->nbrKills;
                unMob = generateMob(player);
                char* name = setMobNames(unMob->races);
                system("cls");
                printf("Oh you encountered a %s, good luck...\n\n", name);
                fightPlayerToMob(player, unMob);
                if(player->nbrKills > flag){
                    dungeonSize--;
                    printf("Good job you killed it... More %d mobs to empty this dungeon !\n", dungeonSize);
                    Sleep(2000);
                }
                else{
                    printf("You ran away, you still have %d mobs to kill in this dungeon !\n", dungeonSize);
                    Sleep(2000);
                }
                break;
            case 2:
                researchInDungeon(player);
                break;
            case 3:
                show_inventory(player);
                break;
            case 4:
                show_stuff(player);
                break;
            case 5:
                displayEqpt(player);
                break;
            case 6:
                calcAttributesWithEqpt(player);
                printf("Press 0 to return\n");
                userChoice = 1;
                while(userChoice != 0){
                    userChoice = userInputInt();
                }
                break;
            case 7:
                displayMainMenu(player);
                break;
            default:
                printf("Please press a correct entry !\n");
                Sleep(2000);
                break;
        }
    }
}

//Calculate the size of the dungeon depending on the level of the player
//Start with 3 mobs and increase by 2 every three levels
int calculateNomberOfMob(Player *player)
{
    static int numberOfMob = 3;

    if((player->level)%3 == 0){
        numberOfMob += 2;
    }
    return numberOfMob;
}

//Menu to start a dungeon
void goThroughDungeon(Player *player)
{
    system("cls");

    printf("*** Welcome to a new dungeon ***\n\nOnly the bravest will stay alive, be strong if you want to survive...\n\n");
    printf("You'll receive Gold if you empty this dungeon, good luck !\n");
    Sleep(5000);

    //Go to the menu of dungeons
    switchDungeons(player);

    printf("\n*** Congratulation you emptied another dungeon ***\n\n");
    player->nbrDungeons++;
    printf("Gold +%d\n\n", (player->nbrDungeons * 100));

    player->gold += (player->nbrDungeons * 100);
    Sleep(500);

    printf("After a long walk... you finally arrive back in town...\n\n");
    Sleep(500);
    printf("You life is back to maximum now !\n\n");
    printf("Number of kills : %d\nScore : %d\n", player->nbrKills, player->score);
    Sleep(4000);

    player->health = player->maxHP;
    displayMainMenu(player);
}
