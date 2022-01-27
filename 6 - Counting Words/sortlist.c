/*Zhuoming Huang sortlist.c */
#include <string.h>
#include "word.h"
extern word * wordlist[MAXWORD];
extern int count;

void sortlist(void)
{	
	int mid,i,j;//for counting
	word * temp;//for holding words
	//sort wordlist base on occurrence in increasing order 
	for(mid=count/2;mid>0;mid/=2)
		for(i=mid;i<count;i++)
			for(j=i-mid;j>=0;j-=mid){
				if((wordlist[j]->count)<=(wordlist[j+mid]->count))
					break;		
				temp = wordlist[j];
				wordlist[j] = wordlist[j+mid];
				wordlist[j+mid] = temp;
			}

	//sort wordlist base on character: upper cases to lower cases, a to z
        for(mid=count/2;mid>0;mid=mid/2)
                for(i=mid;i<count;i++)
                        for(j=i-mid;j>=0;j-=mid)
                                if((wordlist[j]->count)==(wordlist[j+mid]->count)){
                                        if((wordlist[j]->character[0])<=(wordlist[j+mid]->character[0]))
						break;
                                        temp = wordlist[j];
                                        wordlist[j] = wordlist[j+mid];
                                        wordlist[j+mid] = temp;
				}
        //sort wordlist base on length of word
        for(mid=count/2;mid>0;mid/=2)
                for(i=mid;i<count;i++)
                        for(j=i-mid;j>=0;j-=mid)
				if((wordlist[j]->count)==(wordlist[j+mid]->count))
					if((wordlist[j]->character[0])==(wordlist[j+mid]->character[0])){
                        	 		if((strlen(wordlist[j]->character))<=(strlen(wordlist[j+mid]->character)))
							break;
                                        temp = wordlist[j];
                                        wordlist[j] = wordlist[j+mid];
                                        wordlist[j+mid] = temp;
                                }
}
