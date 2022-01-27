/* Zhuoming Huang 10/22/2019 xbits.c */
/*
 *  stubs for functions to study
 *  integer-hex conversions
 *
 */

#include <stdio.h>
#include "xbits.h"

/* function represents the int n as a hexstring which it places in the
hexstring array */

void itox(char hexstring[], int n) {
   printf("in itox, processing %d\n",n);
	int i,rmd,quo=n,len=0;
	char c;
	for (i=0;quo>0;i++){
		rmd = quo%16;
		quo = quo/16;
		if (rmd>9)
			rmd += 55;
		else
			rmd += 48;
		hexstring[i]=rmd;
		hexstring[i+1]='\0';
		len++;
	}
	for (i=0;i<len/2;i++){
		c = hexstring[i];
                hexstring[i]=hexstring[len-i-1];
                hexstring[len-i-1]=c;
        }
}

/* function converts hexstring array to equivalent integer value  */

int xtoi( char hexstring[]) {
  printf("in xtoi, processing %s\n", hexstring);
	int i,len=0,num,sum=0,weight;
	char c;
	for(i=0;hexstring[i]!='\0';i++)
		len++;
	for(i=len-1,weight=1;hexstring[i]!='\0';i--,weight*=16){
		if (hexstring[i]<58)
			num = hexstring[i]-48;
		else
			num = hexstring[i]-55;
		num *= weight;
		sum += num;
	}
	return sum;
}
