#include <stdlib.h>
#include <stdio.h>

#include <time.h>

#include "machine_learning.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    int cfg[] = {3, 4, 4, 3};
    Perceptron *p = perceptron_create(cfg, 4);

    perceptron_print(p);

    return 0;
}
