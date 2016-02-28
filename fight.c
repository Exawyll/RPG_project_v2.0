#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fight.h"
#include "gameUtil.h"
#include "mob.h"
#include "player.h"

int calcPlayerAttack (Player *target){
    int diceATT = rollDice_attack();
    int totAttack = (target->attack + diceATT);
    return totAttack;
}

int calcMobAttack (Mob *mob) {
    int diceATT = rollDice_attack();
    int totAttack = (mob->attack + diceATT);
    return totAttack;
}

int calcPlayerRelDef (Player *target, int attack){
    double relDEF = (target->relDef/100);
    int resultingAttack = attack - (attack * relDEF);
    return resultingAttack;
}

int calcMobRelDef (Mob *mob, int attack){
    double relDEF = (mob->relDef/100);
    int resultingAttack = attack - (attack * relDEF);
    return resultingAttack;
}

int fightPlayerToMob (Player *target, Mob *mob) {
    int attack = calcPlayerAttack(target);
    int dodge = rollDice_dodge(mob->dodge);
    char* mobName;
    mobName = setMobNames(mob->races);

    while (mob->health > 0) {

        DisplayFightMenu();
        int userInput = userInputInt();

        switch (userInput) {
            case 1:
                if(dodge){
                    printf("%s has dodged.\n", mobName);
                }
                else{
                    attack = calcMobRelDef(mob, attack);
                    int effectiveAttack = attack - mob->defense;
                    mob->health = mob->health - effectiveAttack;
                    printf("%s inflicted %d damage to %s.\n", target->name, effectiveAttack, mobName);
                    displayStatsMob(mob);
                }
                break;
            case 2:
                printf("Running away!\n");
                return(0);
            default:
                printf("Bad input. Try again.\n");
                break;
        }
    }

    // Victoryǃ
    if (target->health <= 0) {
        printf("%s has bested %s in combat.\n", target->name, mobName);
    }
    else {
        // Swap player and mob.
        fightMobToPlayer(mob,target);
    }
    return(0);
}

int fightMobToPlayer (Mob *mob, Player *target) {
    int attack = calcMobAttack(mob);
    int dodge = rollDice_dodge(mob->dodge);
    char* mobName;
    mobName = setMobNames(mob->races);

    while (target->health > 0) {

        if(dodge){
            printf("%s has dodged.\n", target->name);
        }
        else{
            attack = calcPlayerRelDef(mob, attack);
            int effectiveAttack = attack - target->defense;
            target->health = target->health - effectiveAttack;
            printf("%s inflicted %d damage to %s.\n", mobName, effectiveAttack, target->name);
        }
    }

    // Victoryǃ
    if (target->health <= 0) {
        printf("%s has bested %s in combat.\n", mobName, target->name);
    }
    else {
        // Swap mob and player.
        fightPlayerToMob(target,mob);
    }
    return(0);
}

void DisplayFightMenu () {
    printf("1) Attack\n2) Run\n");
}
