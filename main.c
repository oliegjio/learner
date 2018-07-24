#include <stdlib.h>
#include <stdio.h>

#include "perceptron.h"

int main(int argc, char *argv[]) {

    struct Perceptron p;
    int c[] = {3, 4, 4, 3};
    perceptron(&p, c, 4);

    perceptron_print(&p);

    return 0;
}