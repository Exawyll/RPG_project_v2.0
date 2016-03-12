#include <stdio.h>
#include <stdlib.h>

#include "dungeon.h"
#include "mob.h"
#include "player.h"

Mob* generateMob(){
    Mob* mymob = malloc(sizeof(Mob));


    for(i = 0; i < 5; i++){
        myDungeon[i] = createGobelin();
    }

    return myDungeon;
}

int choiceInDungeon(){
    int userChoice = -1;

    system("cls");

    printf("You enter through an old gate where you can here screams quite next to you...\n");
    printf("What do you want to do :\n");
    printf("1 - Go back in town\n");
    printf("2 - Look around for a treasure\n");
    printf("3 - Go directly for a fight\n");

    userChoice = userInputInt();

    return userChoice;
}

void switchDungeons(Player *player, mob** dungeon){
    switch(choiceInDungeon()){
        case 1:
            displayMainMenu(player);
            break;
        case 2:
            researchInDungeon(player);
            break;
        case 3:
            Mob* unMob = dungeon[0];
            char* name = generateName(unMob->races);
            printf("\nOh you encountered a %s, good luck...\n", name);
            if(fightPlayerToMob(player, unMob)){
                printf("Good job you killed it\n");
            }
            break;
        default:
            printf("Please press a correct entry !\n");
            break;
    }
}

int calculateNomberOfMob(Player *player){
    static int numberOfMob = 5;

    if((player->level)%5 == 0){
        numberOfMob += 2;
    }
    return numberOfMob;
}

void goThroughDungeon(Player *player){
    int dungeonSize = calculateNomberOfMob(player);

    printf("\nWelcome to a new dungeon\nOnly the bravest stay alive through these caves, be strong and take care...\n\n");

    while(dungeonSize > 0){
        switchDungeons(player, newDungeon);
        dungeonSize--;
    }

    printf("Congratulation you emptied another dungeon!!!\n");
    printf("After a long walk... you finally arrive back in town...\n");
    displayMainMenu(player);
}


