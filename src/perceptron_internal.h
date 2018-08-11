#ifndef PERCEPTRON_INTERNAL_H_
#define PERCEPTRON_INTERNAL_H_

typedef struct Perceptron {

    Matrix **l;
    size_t ls;

    Matrix **b;
    size_t bs;

    Matrix **w;
    size_t ws;
    
} Perceptron;

#endif // PERCEPTRON_INTERNAL_H_
