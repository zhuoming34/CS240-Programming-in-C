CC = gcc
CFLAGS = -m32

tail: tail.o lineholder.o
	$(CC) $(CFLAGS) tail.o lineholder.o -o tail
tail.o: tail.c lineholder.h
	$(CC) $(CFLAGS) -c -o tail.o tail.c
lineholder.o: lineholder.c lineholder.h
	$(CC) $(CFLAGS) -c -o lineholder.o lineholder.c
clean:
	rm *.o
