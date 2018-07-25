#ifndef PERCEPTRON
#define PERCEPTRON

#include "linear_algebra.h"

struct Perceptron {

    struct Vector *l;
    int ls;

    struct Vector *b;
    int bs;

    struct Matrix *w;
    int ws;
};

bool perceptron(struct Perceptron *p, int *c, int cs);
void perceptron_clear(struct Perceptron *p);

void perceptron_randomize(struct Perceptron *p, float from, float to);
bool perceptron_feedforward(struct Perceptron *p, float *i, int s);

float perceptron_sigmoid(float x);

void perceptron_print(struct Perceptron *p);

#endif // PERCEPTRON