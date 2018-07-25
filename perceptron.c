#include "perceptron.h"

bool perceptron(struct Perceptron *p, int *c, int cs) {

    if (cs < 3) return false;

    struct Vector *l_mem = (struct Vector *) calloc(cs, sizeof(struct Vector));

    if (l_mem == NULL) {
        goto cleanup_from_layers;
    }

    p->l = l_mem;

    for (int i = 0; i < cs; i++) {

        if (!vector(&p->l[i], c[i])) {

            for (int j = 0; j < i; j++) {
                free(&p->l[j]);
            }
            free(p->l);

            goto cleanup_from_layers;
        }
    }

    struct Matrix *w_mem = (struct Matrix *) calloc(cs - 1, sizeof(struct Matrix));

    if (w_mem == NULL) {
        goto cleanup_from_weights;
    }

    p->w = w_mem;

    for (int i = 0; i < cs - 1; i++) {

        if (!matrix(&p->w[i], c[i + 1], c[i])) {

            for (int j = 0; j < i; j++) {
                free(&p->w[j]);
            }
            free(p->w);

            goto cleanup_from_weights;
        }
    }

    struct Vector *b_mem = (struct Vector *) calloc(cs - 1, sizeof(struct Vector));

    if (b_mem == NULL) {
        goto cleanup_from_biases;
    }

    p->b = b_mem;

    for (int i = 0; i < cs - 1; i++) {

        if (!vector(&p->b[i], c[i + 1])) {

            for (int j = 0; j < i; j++) {
                free(&p->b[j]);
            }
            free(p->b);

            goto cleanup_from_biases;
        }
    }

    p->ls = cs;
    p->ws = cs - 1;
    p->bs = cs - 1;

    return true;

    cleanup_from_biases: {

        for (int i = 0; i < cs -1; i++) {
            free(&p->w[i]);
        }
        free(p->w);

        goto cleanup_from_weights;
    }

    cleanup_from_weights: {

        for (int i = 0; i < cs; i++) {
          free(&p->l[i]);
        }
        free(p->l);

        goto cleanup_from_layers;
    }

    cleanup_from_layers: {

        p->l = NULL;
        p->w = NULL;
        p->ls = 0;
        p->ws = 0;

        return false;
    }
}

void perceptron_clear(struct Perceptron *p) {

    for (int i = 0; i < p->ls; i++) {
        vector_clear(&p->l[i]);
    }
    free(p->l);

    for (int i = 0; i < p->ws; i++) {
        matrix_clear(&p->w[i]);
    }
    free(p->w);

    for (int i = 0; i < p->bs; i++) {
        vector_clear(&p->b[i]);
    }
    free(p->b);

    p->l = NULL;
    p->w = NULL;
    p->b = NULL;
    p->ls = 0;
    p->ws = 0;
    p->bs = 0;
}

void perceptron_print(struct Perceptron *p) {

    int neurons = 0;
    int connections = 0;
    int biases = 0;

    for (int i = 0; i < p->ls; i++) {

        neurons += p->l[i].l;

        if (i == 0) {

            printf("Layer %d (INTPUT LAYER): has %d neurons ", i + 1, p->l[i].l);

        } else if (i < p->ls - 1) {

            printf("Layer %d (HIDDEN LAYER): has %d neurons, %d biases ", i + 1, p->l[i].l, p->b[i - 1].l);

        } else {

            printf("Layer %d (OUTPUT LAYER): has %d neurons, %d biases ", i + 1, p->l[i].l, p->b[i - 1].l);
        }

        if (i < p->ls - 1) {

            connections += p->w[i].c * p->w[i].r;
            biases += p->b[i].l;

            printf("and %d connections to Layer %d \n", p->w[i].r * p->w[i].c, i + 2);

        } else {

            printf("\n");
        }
    }

    printf("SUMMARY: %d neurons, %d connections, %d biases \n", neurons, connections, biases);
}

bool perceptron_feedforward(struct Perceptron *p, float *i, float *o, int s) {

    if (s != p->l[0].l) return false;

    struct Vector result;

    for (int i = 0; i < p->ws; i++) {

        if (!matrix_vector_multiply(&p->w[i], &p->l[i], &result)) printf("1! \n");
        if (!vector_copy_values(&result, &p->l[i + 1])) printf("2! \n");

        vector_clear(&result);

        if (!vector_add(&p->l[i + 1], &p->b[i], &result)) printf("3! \n");
        if (!vector_copy_values(&result, &p->l[i + 1])) printf("4! \n");

        vector_clear(&result);

        if (!vector_map(&p->l[i + 1], &perceptron_sigmoid, &result)) printf("5! \n");
        if (!vector_copy_values(&result, &p->l[i + 1])) printf("6! \n");

        vector_clear(&result);
    }

    if (!vector_to_array(&p->l[p->ws], o, s)) printf("6! \n");
//    if (!vector(o, p->l[p->ws].l)) 
//    if (!vector_copy_values(&p->l[p->ws], o)) printf("7! \n");

    return true;
}

void perceptron_randomize(struct Perceptron *p, float min, float max) {

    for (int i = 0; i < p->ws; i++) {
        for (int j = 0; j < p->w[i].r * p->w[i].c; j++) {

            p->w[i].m[j] = ((float) rand() / (float) RAND_MAX) * (max - min) + min;

        }
        for (int j = 0; j < p->b[i].l; j++) {
            p->b[i].v[j] = ((float) rand() / (float) RAND_MAX) * (max - min) + min;
        }
    }
}

float perceptron_sigmoid(float x) {
    return 1 / (1 + exp(-x));
}