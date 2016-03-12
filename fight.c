#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fight.h"
#include "gameUtil.h"
#include "mob.h"
#include "player.h"

int calcPlayerAttack (Player *target){
    int diceATT = rollDice_attack();
    printf("dice ATT player : %d\n", diceATT);
    int AttackWithEqpt = calcAttack(target);
    int totAttack = (AttackWithEqpt + diceATT);
    return totAttack;
}

int calcMobAttack (Mob *mob) {
    int diceATT = rollDice_attack();
    printf("dice ATT mob : %d\n", diceATT);
    int totAttack = (mob->attack + diceATT);
    return totAttack;
}

int calcPlayerRelDef (Player *target, int attack){
    int relDefWithEqpt = calcRelDef(target);
    double relDEF = (relDefWithEqpt/100);
    int resultingAttack = attack - (attack * relDEF);
    printf("Resulting ATT player : %d\n", resultingAttack);
    if(resultingAttack > 0){
        return resultingAttack;
    }
    else{
        return(0);
    }
}

int calcMobRelDef (Mob *mob, int attack){
    double relDEF = (mob->relDef/100);
    int resultingAttack = attack - (attack * relDEF);
    printf("Resulting ATT mob : %d\n", resultingAttack);
    if(resultingAttack > 0){
        return resultingAttack;
    }
    else{
        return(0);
    }
}

int fightPlayerToMob (Player *target, Mob *mob) {
    int attack = 0;
    int dodge = rollDice_dodge(mob->dodge);
    char* mobName;
    mobName = setMobNames(mob->races);

    //while (mob->health > 0) {
    DisplayFightMenu();
    int userInput = userInputInt();
    attack = calcPlayerAttack(target);

    switch (userInput) {
        case 1:
            if(dodge){
                printf("%s has dodged.\n", mobName);
            }
            else{
                attack = calcMobRelDef(mob, attack);
                int effectiveAttack = attack - mob->defense;
                if(effectiveAttack > 0){
                    mob->health = mob->health - effectiveAttack;
                    printf("%s inflicted %d damage to %s.\n", target->name, effectiveAttack, mobName);
                }
                else{
                    printf("%s inflicted 0 damage to %s.\n", target->name, mobName);
                }
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

    // Victoryǃ
    if (target->health <= 0) {
        printf("%s has bested %s in combat.\n", mobName, target->name);
    }
    else {
        // Swap player and mob.
        fightMobToPlayer(mob,target);
    }
    return(0);
}

int fightMobToPlayer (Mob *mob, Player *target) {
    int attack = 0;
    int defensePlayerWithEqpt = 0;
    int dodge = rollDice_dodge(mob->dodge);
    char* mobName;
    mobName = setMobNames(mob->races);

    attack = calcMobAttack(mob);
    defensePlayerWithEqpt = calcAbsDef(target);
    //while (target->health > 0) {
    if(dodge){
        printf("%s has dodged.\n", target->name);
    }
    else{
        attack = calcPlayerRelDef(target, attack);
        int effectiveAttack = attack - defensePlayerWithEqpt;
        if(effectiveAttack > 0){
            target->health = target->health - effectiveAttack;
            printf("%s inflicted %d damage to %s.\n", mobName, effectiveAttack, target->name);
        }
        else{
            printf("%s inflicted 0 damage to %s.\n", mobName, target->name);
        }
        printf("Name : %s\nHealth : %d\n", target->name, target->health);
    }
    //}

    // Victoryǃ
    if (mob->health <= 0) {
        printf("%s has bested %s in combat.\n", target->name, mobName);
        calculateReward(player, mob);
        return 1;
    }
    else {
        // Swap mob and player.
        fightPlayerToMob(target,mob);
    }
    return(0);
}

void calculateReward(Player *player, Mob* mob){
    switch(mob->races){
        case GOBELIN:
            player->score += 10;
            player->gold += 10;
            break;
        case SKELETON:
            player->score += 20;
            player->gold += 20;
            break;
        case ORC:
            player->score += 30;
            player->gold += 30;
            break;
        case ZOMBIE:
            player->score += 40;
            player->gold += 40;
            break;
        case URUKAI:
            player->score += 50;
            player->gold += 50;
            break;
        case TROLL:
            player->score += 60;
            player->gold += 60;
            break;
        case DRAGON:
            player->score += 70;
            player->gold += 70;
            break;
        default:
            break;
    }

    if((player->score)%100 == 0){
        player->level++;
    }
}

calculateGold(Player *player, Mob* mob){
}

void DisplayFightMenu () {
    printf("1 -> Attack\n2 -> Run\n3 -> Go back in Town");
}
