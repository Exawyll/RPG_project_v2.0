#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fight.h"
#include "gameUtil.h"
#include "mob.h"
#include "player.h"
#include "mobRace.h"

#define SCORE_GOBELIN 10
#define SCORE_SKELETON 20
#define SCORE_ORC 30
#define SCORE_ZOMBIE 40
#define SCORE_URUKAI 50
#define SCORE_TROLL 60
#define SCORE_DRAGON 70

int calcPlayerAttack (Player *target){
    int diceATT = rollDice_attack();
    int AttackWithEqpt = calcAttack(target);
    int totAttack = (AttackWithEqpt + diceATT);
    return totAttack;
}

int calcMobAttack (Mob *mob) {
    int diceATT = rollDice_attack();
    int totAttack = (mob->attack + diceATT);
    return totAttack;
}

int calcPlayerRelDef (Player *target, int attack){
    int relDefWithEqpt = calcRelDef(target);
    double relDEF = (relDefWithEqpt/100);
    int resultingAttack = attack - (attack * relDEF);
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
        displayGameOverMenu(target);
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

    // Victoryǃ
    if (mob->health <= 0) {
        printf("%s has bested %s in combat.\n", target->name, mobName);
        calculateReward(target, mob);
        return 1;
    }
    else {
        // Swap mob and player.
        fightPlayerToMob(target,mob);
    }
    return(0);
}

//Print and increase the score + Gold of the player
void calculateReward(Player *player, Mob* mob){
    switch(mob->races){
        case GOBELIN:
            player->score += SCORE_GOBELIN;
            player->gold += SCORE_GOBELIN;
            Sleep(1000);
            printf("Score +10\n");
            Sleep(1000);
            printf("Gold +10\n");
            Sleep(1000);
            break;
        case SKELETON:
            player->score += SCORE_SKELETON;
            player->gold += SCORE_SKELETON;
            Sleep(1000);
            printf("Score +20\n");
            Sleep(1000);
            printf("Gold +20\n");
            Sleep(1000);
            break;
        case ORC:
            player->score += SCORE_ORC;
            player->gold += SCORE_ORC;
            Sleep(1000);
            printf("Score +30\n");
            Sleep(1000);
            printf("Gold +30\n");
            Sleep(1000);
            break;
        case ZOMBIE:
            player->score += SCORE_ZOMBIE;
            player->gold += SCORE_ZOMBIE;
            Sleep(1000);
            printf("Score +40\n");
            Sleep(1000);
            printf("Gold +40\n");
            Sleep(1000);
            break;
        case URUKAI:
            player->score += SCORE_URUKAI;
            player->gold += SCORE_URUKAI;
            Sleep(1000);
            printf("Score +50\n");
            Sleep(1000);
            printf("Gold +50\n");
            Sleep(1000);
            break;
        case TROLL:
            player->score += SCORE_TROLL;
            player->gold += SCORE_TROLL;
            Sleep(1000);
            printf("Score +60\n");
            Sleep(1000);
            printf("Gold +60\n");
            Sleep(1000);
            break;
        case DRAGON:
            player->score += SCORE_DRAGON;
            player->gold += SCORE_DRAGON;
            Sleep(1000);
            printf("Score +70\n");
            Sleep(1000);
            printf("Gold +70\n");
            Sleep(1000);
            break;
        default:
            break;
    }

    if((player->score)%100 == 0){
        Sleep(1000);
        printf("Congratulation you won a new level !!!\n");
        Sleep(1000);
        player->level++;
        increaseLevel(player);
    }
}

void increaseLevel(Player *player){
    if((player->level)%3 == 0){
        player->attack++;
        player->defense++;
        player->dodge++;
        player->health += 10;
        player->relDef++;
    }
}

void DisplayFightMenu () {
    printf("1 -> Attack\n2 -> Run\n3 -> Go back in Town");
}
