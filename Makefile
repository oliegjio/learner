PROG_NAME=learner
CC=gcc

build: main.c
	$(CC) main.c -o $(PROG_NAME)

run: build
	./$(PROG_NAME)