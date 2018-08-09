#ifndef PERCEPTRON_INTERNAL_H_
#define PERCEPTRON_INTERNAL_H_

typedef struct Perceptron {

    Vector *l;
    size_t ls;

    Vector *b;
    size_t bs;

    Matrix *w;
    size_t ws;
} Perceptron;

#endif // PERCEPTRON_INTERNAL_H_
