#ifndef PERCEPTRON
#define PERCEPTRON

#include "linear_algebra.h"

typedef struct Perceptron {

    Vector *l;
    int ls;

    Vector *b;
    int bs;

    Matrix *w;
    int ws;
} Perceptron;

bool perceptron(Perceptron *p, int *c, int cs);
void perceptron_clear(struct Perceptron *p);

void perceptron_randomize(Perceptron *p, float from, float to);
bool perceptron_feedforward(Perceptron *p, float *i, int is, float *o, int os);
bool perceptron_train(Perceptron *p, float *i, int is, float *t, int ts);

float perceptron_sigmoid(float x);

void perceptron_print(Perceptron *p);

#endif // PERCEPTRON