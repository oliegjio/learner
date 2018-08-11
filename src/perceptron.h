#ifndef PERCEPTRON_H_
#define PERCEPTRON_H_

#include "matrix.h"

typedef struct Perceptron Perceptron;

Perceptron *perceptron_create(const int *c, size_t cs);
void perceptron_destroy(Perceptron *p);

void perceptron_randomize(Perceptron *p, float from, float to);
int perceptron_feedforward(Perceptron *p, const float *i, size_t is, float *o, size_t os);
int perceptron_train(Perceptron *p, const float *i, size_t is, float *o, size_t os);

void perceptron_print(const Perceptron *p);

#endif // PERCEPTRON_H_
