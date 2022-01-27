/*Zhuoming Huang wordcounter.c */
#include <stdio.h>
#include <ctype.h>
#include "word.h"

word *wordlist[MAXWORD];
int count=0;

int main(void){
	word * firstw=NULL;
	char c,aword[MAXLEN];
	int len=0;//length of a single word be read
	//read words from inputs
	while((len=getword(aword,MAXWORD))>0){
		if(isalpha(aword[0])){
			firstw = addword(firstw,aword,len);
		}
	}
	storewords(firstw);
	sortlist();
	printword();
	freeword(firstw);
	return 0;
}
