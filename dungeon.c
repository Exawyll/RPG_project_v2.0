#include <stdio.h>
#include <stdlib.h>

#include "dungeon.h"
#include "mob.h"
#include "player.h"

Mob* generateMob(Player *player)
{
    Mob* myMob = malloc(sizeof(Mob));
    int randNbr;

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
    else{
        int race = doRand(1, 7);
        int health = doRand(170, 300);
        int attack = doRand(10, 30);
        int defense = doRand(10, 30);
        int relDef = doRand(5, 20);
        int dodge = doRand(5, 20);

        myMob = mob_ctor(race, health, attack, defense, relDef, dodge);
    }
    return myMob;
}

void researchInDungeon(Player *player)
{
    int luckyDice = doRand(1,20);
    int giftGold = doRand(50, 350);
    StuffItem *giftStuff;
    switch(luckyDice){
        case 20:
            giftStuff = generateWeapon();
            printf("So lucky you are, you just found a new weapon !\n");
            item_append(player->armory, *giftStuff);
            Sleep(2000);
            break;
        case 1:
            printf("Oh oh it's a trap, you lose 20 HP !\n");
            player->health -= 20;
            Sleep(2000);
            break;
        case 10:
            printf("Good job you just found %d gold !", giftGold);
            player->gold;
            Sleep(2000);
            break;
        default:
            printf("After few minutes looking, you found nothing...\n");
            Sleep(2000);
            break;
    }
}

int choiceInDungeon()
{
    int userChoice = -1;

    system("cls");

    printf("You enter through an old gate where you can here screams quite next to you...\n");
    printf("What do you want to do :\n");
    printf("1 - Go directly for a fight\n");
    printf("2 - Look around for a treasure\n");
    printf("3 - Display potions\n");
    printf("4 - Display your stuff\n");
    printf("5 - Display your equipment\n");
    printf("6 - Display your stats\n");
    printf("7 - Go back in town (you won't be able to continue this dungeon)\n");

    userChoice = userInputInt();

    return userChoice;
}

void switchDungeons(Player *player)
{
    int flag = 0;
    Mob* unMob;
    int userChoice;
    int numberOfMob = 0;
    switch(choiceInDungeon()){
        case 1:
            unMob = generateMob(player);
            char* name = setMobNames(unMob->races);
            printf("\nOh you encountered a %s, good luck...\n", name);
            flag = fightPlayerToMob(player, unMob);
            if(flag){
                printf("Good job you killed it\n");
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
            while(userChoice != 0){
                userChoice = userInputInt();
            }
            menu_player(player);
            break;
        case 7:
            displayMainMenu(player);
            break;
        default:
            printf("Please press a correct entry !\n");
            break;
    }
}

int calculateNomberOfMob(Player *player)
{
    static int numberOfMob = 5;

    if((player->level)%3 == 0){
        numberOfMob += 2;
    }
    return numberOfMob;
}

void goThroughDungeon(Player *player)
{
    int dungeonSize = calculateNomberOfMob(player);

    printf("\nWelcome to a new dungeon\nOnly the bravest stay alive through these caves, be strong and take care...\n\n");

    while(dungeonSize > 0){
        switchDungeons(player);
        dungeonSize--;
    }

    printf("Congratulation you emptied another dungeon!!!\n");
    printf("After a long walk... you finally arrive back in town...\n");
    displayMainMenu(player);
}
