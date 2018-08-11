#include "perceptron.h"
#include "matrix_internal.h"

#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct Perceptron {

    Matrix **l;
    size_t ls;

    Matrix **b;
    size_t bs;

    Matrix **w;
    size_t ws;

} Perceptron;

typedef enum AllocateMode {
    LAYERS_MODE = 0,
    BIASES_MODE,
    WEIGHTS_MODE
} AllocateMode;

Matrix **perceptron_allocate_matrices(const int *c, size_t cs, AllocateMode mode);
void perceptron_destroy_matrices(Matrix **ms, size_t s);

float perceptron_sigmoid(float x);
float perceptron_sigmoid_d(float x);

Perceptron *perceptron_create(const int *c, size_t cs) {

    if (cs < 3) return NULL;

    Perceptron *p = (Perceptron*) malloc(sizeof(Perceptron));
    if (p == NULL) return NULL;

    Matrix **l, **b, **w;

    l = perceptron_allocate_matrices(c, cs, LAYERS_MODE);
    if (l == NULL) goto cleanup_from_layers;
    p->l = l;

    b = perceptron_allocate_matrices(c, cs - 1, BIASES_MODE);
    if (b == NULL) goto cleanup_from_biases;
    p->b = b;

    w = perceptron_allocate_matrices(c, cs - 1, WEIGHTS_MODE);
    if (w == NULL) goto cleanup_from_weights;
    p->w = w;

    p->ls = cs;
    p->bs = cs - 1;
    p->ws = cs - 1;

    return p;

    cleanup_from_weights: {
        perceptron_destroy_matrices(p->b, cs - 1);
        goto cleanup_from_biases;
    }
    cleanup_from_biases: {
        perceptron_destroy_matrices(p->l, cs);
        goto cleanup_from_layers;
    }
    cleanup_from_layers: {
        free(p);
        return NULL;
    }
}

void perceptron_destroy_matrices(Matrix **ms, size_t s) {

    for (size_t i = 0; i < s; i++) {
        matrix_destroy(ms[i]);
    }
    free(ms);
}

Matrix **perceptron_allocate_matrices(const int *c, size_t cs, AllocateMode mode) {

    Matrix **r = (Matrix**) malloc(cs * sizeof(Matrix*));
    if (r == NULL) return NULL;

    Matrix *l;

    for (size_t i = 0; i < cs; i++) {

        switch (mode) {
            case LAYERS_MODE: l = matrix_create(c[i], 1); break;
            case BIASES_MODE: l = matrix_create(c[i + 1], 1); break;
            case WEIGHTS_MODE: l = matrix_create(c[i + 1], c[i]); break;
            default: return NULL;
        }

        if (l == NULL) {
            for (size_t j = 0; j < i; j++) {
                matrix_destroy(r[j]);
            }
            free(r);
            return NULL;
        }

        r[i] = l;
    }

    return r;
}


void perceptron_destroy(Perceptron *p) {

    perceptron_destroy_matrices(p->l, p->ls);
    perceptron_destroy_matrices(p->b, p->bs);
    perceptron_destroy_matrices(p->w, p->ws);

    free(p);
}

void perceptron_print(const Perceptron *p) {

    size_t neurons = 0;
    size_t connections = 0;
    size_t biases = 0;

    for (size_t i = 0; i < p->ls; i++) {

        neurons += p->l[i]->r;

        if (i == 0) {

            printf("Layer %zu (INTPUT LAYER): has %zu neurons ", i + 1, p->l[i]->r);

        } else if (i < p->ls - 1) {

            printf("Layer %zu (HIDDEN LAYER): has %zu neurons, %zu biases ", i + 1, p->l[i]->r, p->b[i - 1]->r);

        } else {

            printf("Layer %zu (OUTPUT LAYER): has %zu neurons, %zu biases ", i + 1, p->l[i]->r, p->b[i - 1]->r);
        }

        if (i < p->ls - 1) {

            connections += p->w[i]->c * p->w[i]->r;
            biases += p->b[i]->r;

            printf("and %zu connections to Layer %zu \n", p->w[i]->r * p->w[i]->c, i + 2);

        } else {

            printf("\n");
        }
    }

    printf("SUMMARY: %zu neurons, %zu connections, %zu biases \n", neurons, connections, biases);
}

int perceptron_feedforward(Perceptron *p, const float *i, size_t is, float *o, size_t os) {

    if (is != p->l[0]->r) return 0;
    if (os != p->l[p->ws]->r) return 0;

    Matrix *buffer;

    memcpy(p->l[0]->d, i, is * sizeof(float));

    for (size_t i = 0; i < p->ws; i++) {

        if ((buffer = matrix_multiply(p->w[i], p->l[i])) == NULL) return 0;
        if (matrix_copy_values(buffer, p->l[i + 1]) == 0) return 0;

        matrix_destroy(buffer);

        if (matrix_add_l(p->l[i + 1], p->b[i]) == 0) return 0;
        matrix_map_l(p->l[i + 1], &perceptron_sigmoid);
    }

    memcpy(o, p->l[p->ws]->d, os * sizeof(float));

    return 1;
}

void perceptron_randomize(Perceptron *p, float min, float max) {

    for (size_t i = 0; i < p->ws; i++) {
        for (size_t j = 0; j < p->w[i]->r * p->w[i]->c; j++) {
            p->w[i]->d[j] = ((float) rand() / (float) RAND_MAX) * (max - min) + min;
        }
        for (size_t j = 0; j < p->b[i]->r * p->b[i]->c; j++) {
            p->b[i]->d[j] = ((float) rand() / (float) RAND_MAX) * (max - min) + min;
        }
    }
}


float perceptron_sigmoid(float x) {
    return 1 / (1 + exp(-x));
}

float perceptron_sigmoid_d(float x) {
    return x * (1 - x);
}

int perceptron_train(Perceptron *p, const float *i, size_t is, float *t, size_t ts) {

    float o[ts];
    if (perceptron_feedforward(p, i, is, o, ts) == 0) return 0;

    float lr = 0.1;
    Matrix *delta, *gradient, *error, *transposed, *target;

    if ((target = matrix_from_array(t, ts, 1)) == NULL) return 0;

    for (size_t i = 0; i < p->ws; i++) {

        if (i == 0) {
            if ((error = matrix_subtract(target, p->l[p->ls - (i + 1)])) == NULL) return 0;
        } else {
            if ((transposed = matrix_transpose(p->w[p->ws - i])) == NULL) return 0;
            if (matrix_multiply_r(transposed, error) == 0) return 0;
            matrix_destroy(transposed);
        }

        if ((gradient = matrix_map(p->l[p->ls - (i + 1)], &perceptron_sigmoid_d)) == NULL) return 0;
        if (matrix_hadamard_product_l(gradient, error) == 0) return 0;
        matrix_scalar_multiply_l(gradient, lr);

        if ((transposed = matrix_transpose(p->l[p->ls - (i + 2)])) == NULL) return 0;
        if ((delta = matrix_multiply(gradient, transposed)) == NULL) return 0;
        matrix_destroy(transposed);

        if (matrix_add_l(p->w[p->ws - (i + 1)], delta) == 0) return 0;
        if (matrix_add_l(p->b[p->bs - (i + 1)], gradient) == 0) return 0;
        matrix_destroy(delta);
        matrix_destroy(gradient);

    }

    matrix_destroy(target);
    matrix_destroy(error);

    return 1;
}
