/*Zhuoming Huang printword.c */
#include <stdio.h>
#include <malloc.h>
#include "word.h"

extern word * wordlist[MAXWORD];
extern int count;

void printword(void)
{
	int i;
	for(i=0; i<count; i++)
		printf("%2d:	%.10s\n",wordlist[i]->count,wordlist[i]->character);
}

void freeword(word * firstw)
{
	free(firstw->character);
	firstw->character = NULL;
	free(firstw);
	firstw = NULL;	
}

