#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

void color(int t,int f)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,f*16+t);
}
/*les valeurs:
0: noir
1: bleu foncé
2: vert
3: bleu-gris
4: marron
5: pourpre
6: kaki
7: gris clair
8: gris
9: bleu
10: vert fluo
11: turquoise
12: rouge
13: rose fluo
14: jaune fluo
15: blanc */

//Clear the buffer
static void purge_buffer(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {}
}

//Remove the '\n' from the user input
static void clean (char *string){
    char *p = strchr(string, '\n');

    if (p)
    {
        *p = 0;
    }

    else
    {
        purge_buffer();
    }
}

// Get input int.
int userInputInt(){
    int userInput = 0;
    char userNumber[10];

    // Indication the user should type something.
    printf("\n>> ");
    fflush(stdin);
    fgets(userNumber, 10, stdin);
    sscanf(userNumber, "%d", &userInput);
    return userInput;
}

// Get input char.
char* userInputChar(){
    char* string = malloc(50*sizeof(char));
    printf("\n>> ");
    fflush(stdin);
    fgets(string, 50*sizeof(char), stdin);
    clean(string);

    return string;
}

//Return a random number between MAX and MIN
int doRand(int MIN, int MAX){
    srand(time(NULL));
    return (rand() % (MAX - MIN + 1)) + MIN;
}

//Roll dice attack
//Always 2d4 et 1d6
//Return the sum of the three dices
//Roll the dices to attack
int rollDice_attack(){
    int sumAttack = 0;
    int dice6 = doRand(1, 6);
    int dice4a = doRand(1, 4);
    int dice4b = doRand(1, 4);
    sumAttack = dice6 + dice4a + dice4b;
    return sumAttack;
}

//Roll the dice to dodge
//number is the dodge value of the mob
//Three different dodge dices depending on the dodge value
int rollDice_dodge(int number){
    int diceResult;
    diceResult = 0;
    Sleep(800);

    if(number < 5){
        diceResult = doRand(1, 8);
        if(diceResult == 8){
            return 1;
        }
        else{
            return 0;
        }

    }
    else if(number >= 5 && number < 20){
        diceResult = doRand(1, 4);
        if(diceResult == 4){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        diceResult = doRand(1, 2);
        if(diceResult == 2){
            return 1;
        }
        else{
            return 0;
        }
    }
}

//Weapons generation
int generateType(){
    return doRand(0,6);
}

