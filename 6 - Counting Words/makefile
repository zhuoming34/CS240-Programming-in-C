# makefile for hw6
cc = gcc
CFLAGS = -m32 

wordcounter:	wordcounter.o getword.o addword.o sortlist.o printword.o
		$(cc) $(CFLAGS) -g -o wordcounter wordcounter.o getword.o addword.o sortlist.o printword.o
wordcounter.o:	wordcounter.c word.h
		$(cc) $(CFLAGS) -c -o wordcounter.o wordcounter.c
getword.o:	getword.c word.h
		$(cc) $(CFLAGS) -c -o getword.o getword.c
addword.o:	addword.c word.h
		gcc $(CFLAGS) -c -o addword.o addword.c
sortlist.o:     sortlist.c word.h
		$(cc) $(CFLAGS) -c -o sortlist.o sortlist.c
printword.o:	printword.c word.h
		$(cc) $(CFLAGS) -c -o printword.o printword.c
clean:
		rm *.o
