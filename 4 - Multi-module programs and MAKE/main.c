/*
 * main.c
 *
 * reverse polish calculator
 */

#include <stdio.h>
#include "calc.h" /* header file */
#include <math.h>
#include <stdlib.h>

#define MAXOP 100

int main(void)
{
  int type;
  int op2;
  char s[MAXOP];
  
  while ((type = getop(s)) != EOF) 
    {
      switch(type) 
	{
	case NUMBER:
	  push(atoi(s));
	  break;
	case '+':
	  push(pop() + pop());
	  break;
	case '*':
	  push(pop() * pop());
	  break;
	case '-':
	  op2 = pop();
	  push(pop() - op2);
	  break;
	case '/':
	  op2 = pop();
	  if (op2 != 0)
	    push(pop() / op2);
	  else 
	    {
	      printf("error : zero divisor\n");
	      exit(1);
	    }
	  break;
	case '%':
	  op2 = pop();
	  if (op2 != 0)
	    push(pop() % op2);
	  break;
	case '^':
	  push(pop() ^ pop());
	  break;
	case '|':
	  push(pop() | pop());
	  break;
	case '&':
	  push(pop() & pop());
	  break;
	case '~':
	  push(~pop());
	  break;
	case '\n':
	  printf("The answer is %d.\n", pop());
	  break;
	default:
	  printf("error: unknown command %s\n", s);
	  exit(1);
	}
    }
    return 0;
}
