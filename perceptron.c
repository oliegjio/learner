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

    Matrix **l = perceptron_allocate_matrices(c, cs, LAYERS_MODE);
    if (l == NULL) goto cleanup_from_layers;
    p->l = l;

    Matrix **b = perceptron_allocate_matrices(c, cs - 1, BIASES_MODE);
    if (b == NULL) goto cleanup_from_biases;
    p->b = b;

    Matrix **w = perceptron_allocate_matrices(c, cs - 1, WEIGHTS_MODE);
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

    for (int i = 0; i < s; i++) {
        matrix_destroy(ms[i]);
    }
    free(ms);
}

Matrix **perceptron_allocate_matrices(const int *c, size_t cs, AllocateMode mode) {

    Matrix **r = (Matrix**) malloc(cs * sizeof(Matrix*));
    if (r == NULL) return NULL;

    Matrix *l;

    for (int i = 0; i < cs; i++) {

        switch (mode) {
            case LAYERS_MODE: l = matrix_create(c[i], 1); break;
            case BIASES_MODE: l = matrix_create(c[i + 1], 1); break;
            case WEIGHTS_MODE: l = matrix_create(c[i + 1], c[i]); break;
            default: return NULL;
        }

        if (l == NULL) {
            for (int j = 0; j < i; j++) {
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

    int neurons = 0;
    int connections = 0;
    int biases = 0;

    for (int i = 0; i < p->ls; i++) {

        neurons += p->l[i]->r;

        if (i == 0) {

            printf("Layer %d (INTPUT LAYER): has %d neurons ", i + 1, p->l[i]->r);

        } else if (i < p->ls - 1) {

            printf("Layer %d (HIDDEN LAYER): has %d neurons, %d biases ", i + 1, p->l[i]->r, p->b[i - 1]->r);

        } else {

            printf("Layer %d (OUTPUT LAYER): has %d neurons, %d biases ", i + 1, p->l[i]->r, p->b[i - 1]->r);
        }

        if (i < p->ls - 1) {

            connections += p->w[i]->c * p->w[i]->r;
            biases += p->b[i]->r;

            printf("and %d connections to Layer %d \n", p->w[i]->r * p->w[i]->c, i + 2);

        } else {

            printf("\n");
        }
    }

    printf("SUMMARY: %d neurons, %d connections, %d biases \n", neurons, connections, biases);
}

int perceptron_feedforward(Perceptron *p, const float *i, int is, float *o, int os) {

    if (is != p->l[0]->r) return 0;
    if (os != p->l[p->ws]->r) return 0;

    Matrix *buffer;

    memcpy(p->l[0]->d, i, is * sizeof(float));

    for (int i = 0; i < p->ws; i++) {

        buffer = matrix_multiply(p->w[i], p->l[i]);
        if (buffer == NULL) return 0;
        if (matrix_copy_values(buffer, p->l[i + 1]) == 0) return 0;

        matrix_destroy(buffer);

        buffer = matrix_add(p->l[i + 1], p->b[i]);
        if (buffer == NULL) return 0;
        if (matrix_copy_values(buffer, p->l[i + 1]) == 0) return 0;

        matrix_destroy(buffer);

        buffer = matrix_map(p->l[i + 1], &perceptron_sigmoid);
        if (buffer == NULL) return 0;
        if (matrix_copy_values(buffer, p->l[i + 1]) == 0) return 0;

        matrix_destroy(buffer);
    }

    memcpy(o, p->l[p->ws]->d, os * sizeof(float));

    return 1;
}

void perceptron_randomize(Perceptron *p, float min, float max) {

    for (int i = 0; i < p->ws; i++) {
        for (int j = 0; j < p->w[i]->r * p->w[i]->c; j++) {
            p->w[i]->d[j] = ((float) rand() / (float) RAND_MAX) * (max - min) + min;
        }
        for (int j = 0; j < p->b[i]->r * p->b[i]->c; j++) {
            p->b[i]->d[j] = ((float) rand() / (float) RAND_MAX) * (max - min) + min;
        }
    }
}


float perceptron_sigmoid(float x) {
    return 1 / (1 + exp(-x));
}

float perceptron_sigmoid_d(float x) {
    // return perceptron_sigmoid(x) * (1 - perceptron_sigmoid(x));
    return x * (1 - x);
}

int perceptron_train(Perceptron *p, const float *i, int is, float *t, int ts) {

    float o[ts];
    if (perceptron_feedforward(p, i, is, o, ts) == 0) return 0;

    Matrix *output = matrix_from_array(o, ts, 1);
    if (output == NULL) return 0;

    Matrix *target = matrix_from_array(t, ts, 1);
    if (target == NULL) return 0;

    float lr = 0.5;
    Matrix *delta, *gradient, *error, *old_error, *transposed;

    // printf("BEFORE: \n");
    // matrix_print(p->w[p->ws - 2]);
    // printf("\n");

    /* === FIRST === */

    // ERROR
    if ((error = matrix_subtract(target, output)) == NULL) return 0;

    // GRADIENT
    if ((gradient = matrix_map(output, &perceptron_sigmoid_d)) == NULL) return 0;
    if (matrix_hadamard_product_i(gradient, error) == 0) return 0;
    matrix_scalar_multiply_i(gradient, lr);

    // DELTA
    if ((transposed = matrix_transpose(p->l[p->ls - 2])) == NULL) return 0;
    if ((delta = matrix_multiply(gradient, transposed)) == NULL) return 0;

    // ADJUST
    if (matrix_add_i(p->w[p->ws - 1], delta) == 0) return 0;
    if (matrix_add_i(p->b[p->bs - 1], gradient) == 0) return 0;

    old_error = matrix_copy(error);

    matrix_destroy(delta); matrix_destroy(gradient);
    matrix_destroy(error); matrix_destroy(transposed);

    /* === SECOND === */

    // ERROR
    if ((transposed = matrix_transpose(p->w[p->ws - 1])) == NULL) return 0;
    if ((error = matrix_multiply(transposed, old_error)) == NULL) return 0;
    matrix_destroy(old_error);
    matrix_destroy(transposed);

    // GRADIENT
    if ((gradient = matrix_map(p->l[p->ls - 2], &perceptron_sigmoid_d)) == NULL) return 0;
    if (matrix_hadamard_product_i(gradient, error) == 0) return 0;
    matrix_scalar_multiply_i(gradient, lr);

    // DELTA
    if ((transposed = matrix_transpose(p->l[p->ls - 3])) == NULL) return 0;
    if ((delta = matrix_multiply(gradient, transposed)) == NULL) return 0;

    // ADJUST
    if (matrix_add_i(p->w[p->ws - 2], delta) == 0) return 0;
    if (matrix_add_i(p->b[p->bs - 2], gradient) == 0) return 0;

    matrix_destroy(delta); matrix_destroy(gradient);
    matrix_destroy(error); matrix_destroy(transposed);

    /* === END === */

    // printf("AFTER: \n");
    // matrix_print(p->w[p->ws - 2]);
    // printf("\n");

    matrix_destroy(output);
    matrix_destroy(target);

    return 1;
}
