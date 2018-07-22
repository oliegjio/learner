PROG_NAME=learner
CC=gcc

######################

clean:
	rm *.o

build: main.o matrix.o
	$(CC) main.o matrix.o -o $(PROG_NAME)

run: build clean
	./$(PROG_NAME)

######################
## COMPILING FILES: ##
######################

main.o: main.c
	$(CC) -c main.c

matrix.o: matrix.c
	$(CC) -c matrix.c

