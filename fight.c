#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fight.h"
#include "gameUtil.h"
#include "mob.h"
#include "player.h"
#include "mobRace.h"

#define SCORE_MOB 10

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
    double resultingAttack = attack - (attack * relDEF);
    if(resultingAttack > 0){
        return resultingAttack;
    }
    else{
        return(0);
    }
}

int calcMobRelDef (Mob *mob, int attack){
    double relDEF = (mob->relDef/100);
    double resultingAttack = attack - (attack * relDEF);
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
    int victory = 0;

    mobName = setMobNames(mob->races);

    DisplayFightMenu();
    int userInput = userInputInt();
    attack = calcPlayerAttack(target);
    system("cls");

    switch (userInput) {
        case 1:
            if(dodge){
                printf("%s has dodged.\n", mobName);
            }
            else{
                attack = calcMobRelDef(mob, attack);
                int effectiveAttack = attack - mob->defense;
                if(effectiveAttack > 0){
                    mob->health -= effectiveAttack;
                    printf("%s inflicted %d damage to %s.\n", target->name, effectiveAttack, mobName);
                }
                else{
                    printf("%s inflicted 0 damage to %s.\n", target->name, mobName);
                }
            }
            printf("\n%s : %d/%d HP\n\n", mobName, mob->health, mob->maxHP);
            break;
        case 2:
            printf("Running away!\n");
            return(0);
        case 3:
            show_inventory(target);
            system("cls");
            fightPlayerToMob(target, mob);
            break;
        default:
            printf("Bad input. Try again.\n");
            break;
    }

    //Check potions
    if (target->potion > 0) {
        target->potion--;
        if (target->potion == 0){
            handleTimeEffect(target, 0, 0, 0);
        }
    }

    // Victoryǃ
    if (mob->health <= 0) {
        system("cls");
        printf("%s has bested %s in combat.\n", target->name, mobName);
        target->nbrKills++;
        calculateReward(target, mob);
        chanceOfDrop(target);
        return (0);
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
    }
    printf("\n%s : %d/%d HP\n\n", target->name, target->health, target->maxHP);

    // Victoryǃ
    if (target->health <= 0) {
        printf("%s has bested %s in combat.\n", mobName, target->name);
        displayGameOverMenu(target);
    }
    else {
        // Swap mob and player.
        fightPlayerToMob(target,mob);
    }
    return(0);
}

void chanceOfDrop(Player* target)
{
    int chance = doRand(1,10);
    if(chance == 10){
        printf("The mob left a weapon for you in your armory\n");
        Sleep(1000);
        StuffItem *luckyWeapon = generateWeapon();
        item_append(target->armory, *luckyWeapon);
    }
}

//Print and increase the score + Gold of the player
void calculateReward(Player *player, Mob* mob){
    switch(mob->races){
        case GOBELIN:
            player->score += SCORE_MOB;
            player->gold += SCORE_MOB;
            Sleep(1000);
            printf("Score +10\n");
            Sleep(1000);
            printf("Gold +10\n");
            Sleep(1000);
            break;
        case SKELETON:
            player->score += SCORE_MOB+10;
            player->gold += SCORE_MOB+10;
            Sleep(1000);
            printf("Score +20\n");
            Sleep(1000);
            printf("Gold +20\n");
            Sleep(1000);
            break;
        case ORC:
            player->score += SCORE_MOB+20;
            player->gold += SCORE_MOB+20;
            Sleep(1000);
            printf("Score +30\n");
            Sleep(1000);
            printf("Gold +30\n");
            Sleep(1000);
            break;
        case ZOMBIE:
            player->score += SCORE_MOB+30;
            player->gold += SCORE_MOB+30;
            Sleep(1000);
            printf("Score +40\n");
            Sleep(1000);
            printf("Gold +40\n");
            Sleep(1000);
            break;
        case URUKAI:
            player->score += SCORE_MOB+40;
            player->gold += SCORE_MOB+40;
            Sleep(1000);
            printf("Score +50\n");
            Sleep(1000);
            printf("Gold +50\n");
            Sleep(1000);
            break;
        case TROLL:
            player->score += SCORE_MOB+50;
            player->gold += SCORE_MOB+50;
            Sleep(1000);
            printf("Score +60\n");
            Sleep(1000);
            printf("Gold +60\n");
            Sleep(1000);
            break;
        case DRAGON:
            player->score += SCORE_MOB+60;
            player->gold += SCORE_MOB+60;
            Sleep(1000);
            printf("Score +70\n");
            Sleep(1000);
            printf("Gold +70\n");
            Sleep(1000);
            break;
        default:
            break;
    }

    if((player->nbrKills)%3 == 0){
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
        player->maxHP += 10;
        player->relDef++;
    }
}

void DisplayFightMenu () {
    printf("1 -> Attack\n2 -> Run\n3 -> Potions\n");
}
