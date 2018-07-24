#include "perceptron.h"

bool perceptron(struct Perceptron *p, int *c, int cs) {

    if (cs < 3) return false;

    struct Vector *v_mem = (struct Vector *) calloc(cs, sizeof(struct Vector));

    if (v_mem == NULL) {

        p->l = NULL;
        p->w = NULL;
        p->ls = 0;
        p->ws = 0;

        return false;
    }

    p->l = v_mem;

    for (int i = 0; i < cs; i++) {

        if (!vector(&p->l[i], c[i])) {

            for (int j = 0; j < i; j++) {
                free(&p->l[j]);
            }
            free(p->l);

            p->l = NULL;
            p->w = NULL;
            p->ls = 0;
            p->ws = 0;

            return false;
        }
    }

    struct Matrix *m_mem = (struct Matrix *) calloc(cs - 1, sizeof(struct Matrix));

    if (m_mem == NULL) {

        for (int i = 0; i < cs; i++) {
            free(&p->l[i]);
        }
        free(p->l);

        p->l = NULL;
        p->w = NULL;
        p->ls = 0;
        p->ws = 0;

        return false;
    }

    p->w = m_mem;

    for (int i = 0; i < cs - 1; i++) {

        if (!matrix(&p->w[i], c[i + 1], c[i])) {

            for (int j = 0; j < i; j++) {
                free(&p->w[j]);
            }
            free(p->w);

            for (int j = 0; j < cs; j++) {
                free(&p->l[j]);
            }
            free(p->l);

            p->l = NULL;
            p->w = NULL;
            p->ls = 0;
            p->ws = 0;

            return false;
        }
    }

    p->ls = cs;
    p->ws = cs - 1;

    return true;
}

void perceptron_clear(struct Perceptron *p) {

    for (int i = 0; i < p->ls; i++) {
        free(&p->l[i]);
    }
    free(p->l);

    for (int i = 0; i < p->ws; i++) {
        free(&p->w[i]);
    }
    free(p->w);

    p->ls = 0;
    p->ws = 0;
}