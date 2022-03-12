/*name: Zhuoming Huang
  date: 10/01/2019
  file: reverse.c
*/
#include <stdio.h>
#define MAXLINE 1000

int my_getline(char s[],int lim);

int main(void){

	int len,i;
	char line[MAXLINE],c;

/* pseudo code for reverse function

	find length of the string to reverse
	for each character from the beginning of the string to half way
		copy the character here to a holding variable
		copy the character the same distance from end to here
		copy the holding variable to the same distance from end

end of pseudo code
*/
	while ((len=my_getline(line,MAXLINE))>0){
		for (i=0;i<(len/2);i++){
			c=line[i];
			line[i]=line[len-2-i];
			line[len-2-i]=c;
		}
		printf("%s",line);
	}	
	return 0;
}

int my_getline(char s[],int lim){
	int c,i;
	for(i=0;i<lim-1 && (c=getchar())!=EOF && c!='\n';++i)
		s[i] = c;
	if (c == '\n'){
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
