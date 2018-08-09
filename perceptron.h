#ifndef PERCEPTRON_H_
#define PERCEPTRON_H_

#include "matrix.h"

typedef struct Perceptron Perceptron;

Perceptron *perceptron_create(int *c, size_t cs);
void perceptron_destroy(Perceptron *p);

void perceptron_randomize(Perceptron *p, float from, float to);
int perceptron_feedforward(Perceptron *p, float *i, int is, float *o, int os);
int perceptron_train(Perceptron *p, float *i, int is, float *t, int ts);

float perceptron_sigmoid(float x);

void perceptron_print(const Perceptron *p);

#endif // PERCEPTRON_H_
