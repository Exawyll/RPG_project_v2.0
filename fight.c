#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fight.h"
#include "gameUtil.h"

int calcPlayerAttack(Player *target)
{
    int diceATT = rollDice_attack();
    int totAttack = (target->attack + diceATT);
    return totAttack;
}

int calcMobAttack(Mob *mob)
{
    int diceATT = rollDice_attack();
    int totAttack = (mob->attack + diceATT);
    return totAttack;
}

int calcDefenseRel_player(Player *target, int attack)
{

}

int calcDefenseRel_mob(Player *target, int attack)
{

}

int Fight (Player *player, Mob *mob) {
    int diceATT = 0;
    int diceDOD = 0;
    int EffectiveAttack = (Attacker->attack + diceATT) - (mob->relDef) + mob->defense;

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
