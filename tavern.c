#include <stdlib.h>
#include <stdio.h>

#include "tavern.h"
#include "player.h"

void goToTavern(Player *player){
    int userChoice = 0;

    system("cls");

    printf("################################\n");
    printf("#                              #\n");
    printf("#    WELCOME TO THE TAVERN     #\n");
    printf("#                              #\n");
    printf("################################\n\n");

    printf("Here is all you can do there :\n");
    printf("1 - Buy new stuff\n");
    printf("2 - Sell old stuff\n");
    printf("3 - Buy new potions\n");
    printf("4 - Sell potions\n");

    switch(userChoice)
    {
        case 1:
            buyNewStuff(player);
            break;
        case 2:
            sellOldStuff(player);
            break;
        case 3:
            buyNewPotions(player);
            break;
        case 4:
            sellPotions(player);
            break;
        default:
            printf("Please, enter a correct entry !\n");
            break;
    }
}

StuffItem** generateMercant(){
    StuffItem** myMercant = malloc(sizeof(StuffItem));
    int i = 0;

    for(i = 0; i < 5; i++){
        myMercant[i] = createGobelin();
    }

    return myMercant;
}

void buyNewStuff(Player *player){
}

void sellOldStuff(Player *player){
}

void buyNewPotions(Player *player){
}

void sellPotions(Player *player){
}
