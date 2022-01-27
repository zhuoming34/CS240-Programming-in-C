/*Zhuoming Huang	11/26/2019	tail.c
interprets command line argurement*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "lineholder.h"


int main(int argc,char *argv[]){
	int t,j,len,i=0;
	char line[MAXLEN];
	if (argc == 1){
		t = DEFLINE;//default num of lines
	}else if(argc == 2 && (*++argv)[0] == '-'){
		t = atoi(argv[0]+1);        
	}else{
		printf("Enter: ./tail [-n]");
		return 0;
	}
	//initialize the 'first' slot and related variables
	if ((t==0) || (t>MAXLINE)){
		return 0;//no lines or exceed
	}else{
		initl(t);
	}
	//insert line into an array when there is a new line
	while((len=my_getline(line,MAXLEN))>0){
		insertl(line);
	}
	//print out the last n lines when receive EOF
	printl();
}

int my_getline(char s[], int lim){
	int i,c;
	for(i=0;(c=getchar())!='\n'&&c!=EOF&&i<lim-1;i++){
		s[i]=c;
	}
	if(c=='\n'){
		s[i]='\n';
		i++;
	}
	s[i]='\0';
	return i;
}
