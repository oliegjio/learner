#include <stdlib.h>
#include <stdio.h>

#include "perceptron.h"

int main(int argc, char *argv[]) {

    struct Perceptron p;
    int c[] = {3, 4, 2};
    perceptron(&p, c, 3);

    return 0;
}