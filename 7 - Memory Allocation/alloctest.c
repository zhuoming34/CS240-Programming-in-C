/*********************************************************************
 *
 *                            alloctest
 *
 *	       interactive driver for storage allocator
 *
 *  Ethan Bolker
 *  CS240
 *  Fall 1988
 *  edited by Betty O'Neil Spring 1989, Spring 1990, Spring 2000
 *  edited by Bob Wilson Fall 2004
 *
 ********************************************************************/

/* 
 * commands are
 *
 *    #      comment line
 *    a n  # call p = alloc(n), print p and save it in new slot in holdp
 *    f n  # call freef(n), where n is slot# of saved ptr in holdp
 *    d    # debug dump of free list (temp service, removed at end)
 */

#include <stdio.h>
#include <stdlib.h>
#include "alloc.h"

#define MAXSTR 100
#define ALLOC 'a'
#define FREE  'f'
#define DEBUGDUMP 'd'
#define COM   '#'
#define QUIT  'q'

char prompt[]= "> ";

void instruct(void);
int main(void);
/**************************************************************************/

int main()
{

  char line[MAXSTR];
  char command;
  int n;
  char * holdp[100];
  int holdindex=0;		/* in holdp */
  int done=0;

  for (n = 0; n < 100; n++)	/* clear pointer holding array */
        holdp[n] = NULL;
  
  instruct();
  initalloc();
  printf("%s",prompt);
  while (!done && fgets( line, MAXSTR, stdin) != NULL) {
    printf("%s", line);
    command = line[0];
    switch (command) {
    case ALLOC: 
      n = atoi(line+1);
      holdp[holdindex++] = alloc(n);
      printf("alloc #%d returned pointer: %p\n",
	     holdindex-1,holdp[holdindex-1]);
      break;
    case FREE: 
      n = atoi(line+1);
      freef(holdp[n]);
      break;
    case DEBUGDUMP: 
      dumpfree();
      break;
    case COM:
      break;
    case QUIT:  
      done=1;
      break;
    default:
      fprintf(stderr, "unknown command -%c-\n", command);
    }
    if (!done) printf("%s",prompt);
  }
  putchar('\n');
  return(0);
}

void instruct() 
{
  printf("interactive driver for testing storage allocator - commands are\n");
  printf("\n");    
  printf("   #      comment line\n");
  printf("   a n  # call p = alloc(n), print p and save in new slot in holdp\n");
  printf("   f n  # call freef(holdp[n]), i.e. free nth-obtained block\n");
  printf("   d    # dump free list (temp debugging aid)\n");
  printf("   q    # quit\n");
  printf("\n");    
}

