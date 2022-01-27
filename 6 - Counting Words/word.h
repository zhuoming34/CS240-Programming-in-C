/*Zhuoming Huang	12/03/2019	wordcounter.h */
#define MAXLEN 15 //max num of chars in one word
#define MAXWORD 1000 //max num of words can store

typedef struct word word;

struct word{
        int count;
        char *character;
        word *prev;
        word *next;
};

int getword(char *, int);
void sortlist(void);
void printword(void);
void freeword(word *);
void storewords(word *);
word * addword(word *, char *, int);
