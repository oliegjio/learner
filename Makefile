PROG_NAME=learner
CC=gcc

######################

clean:
	rm *.o

build: vector.o matrix.o main.o
	$(CC) vector.o matrix.o main.o -o $(PROG_NAME)

run: build clean
	./$(PROG_NAME)

######################
## COMPILING FILES: ##
######################

main.o: main.c
	$(CC) -c main.c

matrix.o: matrix.c
	$(CC) -c matrix.c

vector.o: vector.c
	$(CC) -c vector.c