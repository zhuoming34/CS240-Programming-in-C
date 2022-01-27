# makefile for building cs240 alloc project programs using the 
# tell make to use gcc as C compiler, -m32 -g -W... for C compiler flags--
# check "man gcc" to find out what -W flags do
CC = gcc
OBJS = alloctest.o alloc.o
CFLAGS = -m32

alloctest:  $(OBJS)
	$(CC) $(CFLAGS) -o alloctest $(OBJS)

# make knows to use $(CC) and $(CFLAGS)	
alloctest.o: alloctest.c alloc.h
alloc.o: alloc.c alloc.h

clean:
	rm -f *.o core

