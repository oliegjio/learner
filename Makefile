PROG_NAME=learner
CC=gcc

######################

clean:
	rm *.o

build: vector.o matrix.o linear_algebra.o perceptron.o main.o
	$(CC) vector.o matrix.o linear_algebra.o perceptron.o main.o -o $(PROG_NAME) -l m

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

linear_algebra.o: linear_algebra.c
	$(CC) -c linear_algebra.c

perceptron.o: perceptron.c
	$(CC) -c perceptron.c