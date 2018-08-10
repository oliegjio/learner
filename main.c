#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <string.h>

#include "machine_learning.h"

#include "perceptron_internal.h"
#include "matrix_internal.h"

int main(int argc, char *argv[]) {

    srand((unsigned int) time(NULL));

    int cfg[] = {2, 2, 1};
    Perceptron *p = perceptron_create(cfg, 3);
    perceptron_print(p);
    perceptron_randomize(p, -0.5, 0.5);

    float samples[4][3];
    samples[0][0] = 1;
    samples[0][1] = 0;
    samples[0][2] = 1;

    samples[1][0] = 0;
    samples[1][1] = 1;
    samples[1][2] = 1;

    samples[2][0] = 1;
    samples[2][1] = 1;
    samples[2][2] = 0;

    samples[3][0] = 0;
    samples[3][1] = 0;
    samples[3][2] = 0;

    float input[2];
    float target[1];
    float output[1];
    float error[1];
    int min = 0;
    int max = 4 - 1;
    int r;

    for (int i = 0; i < 10000; i++) {
        r = rand() % (max + 1 - min) + min;
        input[0] = samples[r][0];
        input[1] = samples[r][1];
        target[0] = samples[r][2];

        if (perceptron_train(p, input, 2, target, 1) == 0) return 0;
        if (perceptron_feedforward(p, input, 2, output, 1) == 0) return 0;

        error[0] = target[0] - output[0];
        if (i < 100 || i > 9900) {
            // printf("%d : %f \n", i, error[0]);
            printf("INPUT: [%.0f, %.0f]  |  TARGET: %.0f  |  OUTPUT: %.2f \n", input[0], input[1], target[0], output[0]);
        }
    }

    perceptron_destroy(p);

    return 0;
}
