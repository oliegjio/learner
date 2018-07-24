#ifndef PERCEPTRON
#define PERCEPTRON

#include "linear_algebra.h"

struct Perceptron {

    struct Vector *l;
    int ls;

    struct Matrix *w;
    int ws;
};

bool perceptron(struct Perceptron *p, int *c, int cs);

void perceptron_clear(struct Perceptron *p);

#endif // PERCEPTRON