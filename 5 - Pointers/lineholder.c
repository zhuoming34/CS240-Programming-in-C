/*Zhuoming Huang	11/26/2019	lineholder.c*/
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "lineholder.h"

static int first,last,full,i,n,len;
static char *lines[MAXLINE];
char *buf,*bufend,*ptr;

void initl(int nline){
	n = nline; //num of line to be printed
	i=0; //counter for read lines
	full=0; //flag checking if buffer is full
	first = 0; //location of the first line
	last = 0; //locaiton of the last line
	for(int j=0;j<MAXLINE;j++)
		lines[j] = NULL;
	buf = (char *)malloc(MAXLINE*MAXLEN); //beginning address of a buffer
	bufend = buf + MAXLINE * MAXLEN; //last address of the buffer
	ptr = buf; //current address
}

void insertl(char *line){
	len = strlen(line);
        if(full==0){
		last = i;
		lines[last] = ptr;
	        strcpy(lines[last],line);
	        ptr += len + 1;
		if (i==n-1){
			full = 1;
			ptr = buf;
		}
	}else{
		last = i%n;
		lines[last] = ptr;
	        strcpy(lines[last],line);
	        ptr += len + 1;
		if (last==n-1)
			first = 0;
		else
			first = last + 1;
	}
	i++;
}

void printl(void){
	int j;
	
	if(last<first){
		//buffer wrap around
		for(j=first;j<n;j++){
			printf("%s",lines[j]);
		}
		for(j=0;j<first;j++){
			printf("%s",lines[j]);
		}
	}else{
		//#lines read is less than required #line, print read lines
		if(i<n)
			last = i-1;
		//the last read line is at the last position of buffer
		for(j=0;j<=last;j++){
			printf("%s",lines[j]);
        	}
	}
	//free memory not in used
	free(buf);
	buf=NULL;
}
