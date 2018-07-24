#include <stdlib.h>
#include <stdio.h>

#include "perceptron.h"

int main(int argc, char *argv[]) {

    struct Perceptron p;
    int c[] = {3, 4, 5, 2};
    perceptron(&p, c, 4);

    return 0;
}