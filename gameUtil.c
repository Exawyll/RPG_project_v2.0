#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*- GameUtil.c : contient l'ensemble des fonctions utilitaires (redondante ou non) du programme
			- doRand(int start, int end)
			- https://openclassrooms.com/courses/les-listes-doublement-chainees-en-langage-c
			- ...*/

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
/*int doRand(int MIN, int MAX){
    srand(time(NULL));
    return (rand() % (MAX - MIN + 1)) + MIN;
}

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
int rollDice_dodge(){
    return doRand(1, 8);
}*/
