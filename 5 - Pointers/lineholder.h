/*Zhuoming Huang	11/26/2019	lineholder.h
symbolic variables and function prototypes */

#define MAXLINE 100
#define MAXLEN 100
#define DEFLINE 10

//read lines from input
int my_getline(char s[],int lim);
//initialize variables in lineholder.c
void initl(int nline);
//insert lines into lines pointer
void insertl(char *lines);
//print out the last n lines
void printl(void);
