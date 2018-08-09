#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "machine_learning.h"

#include "perceptron_internal.h"
#include "matrix_internal.h"

int main(int argc, char *argv[]) {

    srand((unsigned int) time(NULL));

    int cfg[] = {3, 4, 4, 3};
    Perceptron *p = perceptron_create(cfg, 4);
    perceptron_print(p);

    perceptron_randomize(p, -1, 1);

    float input[] = {1, 2, 3};
    float output[3];
    if (perceptron_feedforward(p, input, 3, output, 3) != 0) printf("TRUE \n");

    printf("%f \n", output[0]);
    printf("%f \n", output[1]);
    printf("%f \n", output[2]);

    perceptron_destroy(p);

    return 0;
}
