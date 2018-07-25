#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "perceptron.h"

int main(int argc, char *argv[]) {

    srand((unsigned int) time(NULL));

    struct Perceptron p;
    int c[] = {3, 4, 4, 3};
    perceptron(&p, c, 4);

    perceptron_randomize(&p, -1, 1);

    #define INPUT_SIZE 3

    float input[INPUT_SIZE] = {1, 2, 3};
    float output[INPUT_SIZE];
    perceptron_feedforward(&p, input, output, INPUT_SIZE);

    struct Vector result;
    vector_from_array(&result, output, INPUT_SIZE);
    vector_print(&result);

    perceptron_print(&p);

    return 0;
}