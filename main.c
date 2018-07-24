#include <stdlib.h>
#include <stdio.h>

#include "perceptron.h"

int main(int argc, char *argv[]) {

    struct Perceptron p;
    int c[] = {16000, 20000, 25000, 20000, 1000};
    perceptron(&p, c, 4);

    perceptron_print(&p);

    return 0;
}