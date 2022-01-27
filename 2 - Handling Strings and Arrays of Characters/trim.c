/* name:Zhuoming Huang
   date: 09/26/2019
   file: trim.c
*/

#include <stdio.h>
#define MAXLINE 1000

int my_getline(char line[], int maxline);

int main(void){
        int len,i;
        char line[MAXLINE];
/*pseude code for the trim program
while there is another line
        for each character starting at the end of the line
                 find the first non blank character of the line
                if a non-blank character is found
                        add an eof and terminating zero
                        and print it out
end of pseudo code
*/

        while((len=my_getline(line,MAXLINE)) > 0){
		for(i=len-2;i>0;i--){
        	        if (line[i]!=' ' && line[i]!='\t' && line[i]!='\n'){
				line[i+1] = '\n';
				line[i+2] = '\0';
				printf("%s",line);
				break;
			}
		}
	}
	return 0;
}

int my_getline(char s[], int lim){
	int c, i;
	for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n'){
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
} 
	
