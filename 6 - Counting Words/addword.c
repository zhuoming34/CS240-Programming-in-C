/*Zhuoming Huang addword.c */
#include <string.h>
#include <malloc.h>
#include "word.h"

extern word * wordlist[MAXWORD];
extern int count;

word * addword(word * firstw, char * aword, int len){
	int cmpresult;
	
	if(firstw == NULL){
		firstw = (word *)malloc(sizeof(word));
		firstw->character = (char *)malloc(len+1); //+1 for '\0'
		if(firstw->character != NULL)
			strcpy(firstw->character,aword);
		firstw->count = 1;
		firstw->next = NULL;
		firstw->prev = firstw->next;
	}else if((cmpresult = strcmp(aword,firstw->character)) == 0){
		firstw->count++; //same word found
	}else if(cmpresult > 0){ //sort base on alphabet 
		firstw->next = addword(firstw->next,aword,len);
	}else{
		firstw->prev = addword(firstw->prev,aword,len);
	}
	return firstw;
}

void storewords(word * firstw){
        if(firstw!=NULL){
                storewords(firstw->prev);
                if(count<MAXWORD){
                        wordlist[count++]=firstw;
                }
		storewords(firstw->next);
        }
}
