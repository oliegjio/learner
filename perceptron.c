#include "perceptron.h"

bool perceptron(Perceptron *p, int *c, int cs) {

    if (cs < 3) return false;

    Vector *l_mem = (Vector *) calloc(cs, sizeof(Vector));

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

    Matrix *w_mem = (Matrix *) calloc(cs - 1, sizeof(Matrix));

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

    Vector *b_mem = (Vector *) calloc(cs - 1, sizeof(Vector));

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

void perceptron_clear(Perceptron *p) {

    for (int i = 0; i < p->ls; i++) {
        vector_clear(&p->l[i]);
    }
    free(p->l);

    for (int i = 0; i < p->ws; i++) {
        matrix_free(&p->w[i]);
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

void perceptron_print(Perceptron *p) {

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

bool perceptron_feedforward(Perceptron *p, float *i, int is, float *o, int os) {

    if (is != p->l[0].l) return false;
    if (os != p->l[p->ws].l) return false;

    Vector buffer;

    for (int i = 0; i < p->ls; i++) {
        vector_set_values(&p->l[i], 0);
    }
    if (!vector_copy_array_values(i, is, &p->l[0])) return false;

    for (int i = 0; i < p->ws; i++) {

        if (!matrix_vector_multiply(&p->w[i], &p->l[i], &buffer)) return false;
        if (!vector_copy_vector_values(&buffer, &p->l[i + 1])) return false;

        vector_clear(&buffer);

        if (!vector_add(&p->l[i + 1], &p->b[i], &buffer)) return false;
        if (!vector_copy_vector_values(&buffer, &p->l[i + 1])) return false;

        vector_clear(&buffer);

        if (!vector_map(&p->l[i + 1], &perceptron_sigmoid, &buffer)) return false;
        if (!vector_copy_vector_values(&buffer, &p->l[i + 1])) return false;

        vector_clear(&buffer);
    }

    if (!vector_to_array(&p->l[p->ws], o, os)) return false;

    return true;
}

void perceptron_randomize(Perceptron *p, float min, float max) {

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

float perceptron_sigmoid_derivative(float x) {
//    return perceptron_sigmoid(x) * (1 - perceptron_sigmoid(x));
    return x * (1 - x);
}

bool perceptron_train(Perceptron *p, float *i, int is, float *t, int ts) {

    float out[ts];
    if (!perceptron_feedforward(p, i, is, out, ts)) return false;

    Vector output_errors;
    Vector targets;
    Vector d_outputs;
    Matrix m_outputs;
    Matrix ml_outputs;
    Matrix hidden_t;
    Matrix ho_deltas;
    Vector f_deltas;
    Matrix f_weights;

    const float learning_rate = 0.1f;

    if (!vector_from_array(&targets, t, ts)) return false;


    if (!vector_subtract(&targets, &p->l[p->ws], &output_errors)) printf("1! \n");
    if (!vector_map(&p->l[p->ws], *perceptron_sigmoid_derivative, &d_outputs)) printf("2! \n");
    if (!vector_vector_multiply(&d_outputs, &output_errors, &m_outputs)) printf("3! \n");
    if (!matrix_scalar_multiply(&m_outputs, learning_rate, &ml_outputs)) printf("4! \n");

    if (!matrix_vector_multiply(&ml_outputs, &p->l[p->ws], &f_deltas)) printf("5! \n");

    if (!matrix_add(&p->w[p->ws - 1], &f_deltas, &f_weights)) printf("6! \n");
    if (!matrix_copy_values(&f_weights, &p->w[p->ws - 1])) printf("7! \n");


    for (int i = p->ws; i > 0; i--) {
        
        
        
    }

    vector_clear(&targets);

    printf("DONE! \n");

    return true;
}