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
    int Attack = calcPlayerAttack(player);
    int Dodge = rollDice_dodge(mob->dodge);
    char* mobName;
    mobName = displayMobNames();

    if(dodge){
        printf("")
    }
    int EffectiveAttack = (Attack) - (mob->relDef) + mob->defense;

    while (mob->health > 0) {

        DisplayFightMenu();

        switch (userInputInt()) {
            case 1:
                mob->health = mob->health - EffectiveAttack;
                printf("%s inflicted %d damage to %s.\n", player->name, EffectiveAttack, mobName);
                DisplayStats(Target);
                break;
            case 2:
                printf("Running away!\n");
                return(0);
            default:
                printf("Bad input. Try again.\n");
                break;
        }

        else{
            // Autopilot. Userless player acts independently.
            Target->health = Target->health - EffectiveAttack;
            printf("%s inflicted %d damage to %s.\n", Attacker->name, EffectiveAttack, Target->name);
            DisplayStats(Target);
        }
    }

    // Victoryǃ
    if (Target->health <= 0) {
        printf("%s has bested %s in combat.\n", Attacker->name, Target->name) ;
    }
    else {
        // Swap attacker and target.
        Player *tmp = Attacker;
        Attacker = Target;
        Target = tmp;
    }
    return(0);
}

int fightMobToPlayer (Mob *mob, Player *target) {
    int diceATT = 0;
    int diceDOD = 0;
    int EffectiveAttack = (player->attack + diceATT) - (mob->relDef) + mob->defense;

    while (Target->health > 0) {
        // Get user input if autopilot is set to false.
        if (Attacker->autoPilot == false) {
            DisplayFightMenu();

            switch (userInputInt()) {
                case 1:
                    Target->health = Target->health - EffectiveAttack;
                    printf("%s inflicted %d damage to %s.\n", Attacker->name, EffectiveAttack, Target->name);
                    DisplayStats(Target);
                    break;
                case 2:
                    printf("Running away!\n");
                    return(0);
                default:
                    printf("Bad input. Try again.\n");
                    break;
            }
        }
        else{
            // Autopilot. Userless player acts independently.
            Target->health = Target->health - EffectiveAttack;
            printf("%s inflicted %d damage to %s.\n", Attacker->name, EffectiveAttack, Target->name);
            DisplayStats(Target);
        }
    }

    // Victoryǃ
    if (Target->health <= 0) {
        printf("%s has bested %s in combat.\n", Attacker->name, Target->name) ;
    }
    else {
        // Swap attacker and target.
        Player *tmp = Attacker;
        Attacker = Target;
        Target = tmp;
    }
    return(0);
}

void DisplayFightMenu () {
    printf("1) Attack\n2) Run\n");
}
