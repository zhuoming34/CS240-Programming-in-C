/*Zhuoming Huang	modified getword.c
get next word or character from input
K&R page136*/
#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100
char buf[BUFSIZE];        /* buffer for ungetch */
int  bufp = 0;            /* next free position in buf */

int getch(void)           /* get a (possibly pushed back) character */
{
    return(bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)        /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many character \n");
    else
        buf[bufp++] = c;
}

int getword(char *word, int lim){
	int c,len=0;
	while(isspace(c=getch()))
		;
	if(c!=EOF)
		*word++ = c;
		len++;
	if(!isalpha(c)){
		*word = '\0';
		return c;
	}
	for(;--lim>0;word++)
		if(!isalnum(*word=getch())){
			ungetch(*word);
			break;
		}
	*word = '\0';
	return len;
}
