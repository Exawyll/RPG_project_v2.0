#ifndef GAMEUTIL_H_INCLUDED
#define GAMEUTIL_H_INCLUDED

void clean (char *chaine);
void purge_buffer(void);
int userInputInt();
char* userInputChar();
int rollDice_dodge(int number);
int rollDice_attack();
int doRand(int MIN, int MAX);

#endif // GAMEUTIL_H_INCLUDED
