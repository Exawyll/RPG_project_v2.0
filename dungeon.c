#include <stdio.h>
#include <stdlib.h>

#include "dungeon.h"
#include "mob.h"
#include "player.h"

Mob** generateDungeon(){
    Mob** myDungeon = malloc(sizeof(Mob));
    int i = 0;

    for(i = 0; i < 5; i++){
        myDungeon[i] = createGobelin();
    }

    return myDungeon;
}

void goThroughDungeon(Player *player){
    int i = 0;
    Mob** newDungeon = generateDungeon();

    printf("\nWelcome to a new dungeon\nOnly the bravest stay alive through that caves, be strong\n\n");

    for(i = 0; i < 5; i++){

        Mob* unMob = newDungeon[i];
        fightPlayerToMob(player, unMob);
        printf("\nOh you encountered another Gobelin, good luck...\n");
    }

    printf("Congratulation you've finished your first dungeon!!!\n");
}


