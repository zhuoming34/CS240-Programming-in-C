/*Zhuoming Huang
  10/22/2019
  showxbits.c
*/
/*
 *  stub driver for functions to study integer-hex conversions
 *
 */

#include <stdio.h>
#include <string.h>
#include "xbits.h"

#define ENOUGH_SPACE 1000 /* not really enough space */

int main() {
  char hexstring[ENOUGH_SPACE];
  int m=0, n;
  while(scanf("%d",&n)==1){
  itox(hexstring, n);
  m= xtoi(hexstring);
  printf("%12d %s %12d\n", n,hexstring, m);
  }
  return 0;  /* everything is just fine */
}


