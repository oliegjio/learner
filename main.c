#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "perceptron.h"

int main(int argc, char *argv[]) {

    srand((unsigned int) time(NULL));

    struct Perceptron p;
    int c[] = {3, 4, 4, 3};
    perceptron(&p, c, 4);

    perceptron_random_weights(&p, -1, 1);

    perceptron_print(&p);

    return 0;
}