#include "linear_algebra.h"

bool matrix_to_vector(struct Matrix *m, struct Vector *v) {

    if (m->c != 1 && m->r != 1) return false;

    if (m->c == 1) {
        if (!vector(v, m->r)) return false;
        if (!matrix_select_column(m, 0, v->v, m->r)) return false;
    }

    if (m->r == 1) {
        if (!vector(v, m->c)) return false;
        if (!matrix_select_row(m, 0, v->v, m->c)) return false;
    }

    return true;
}

bool vector_to_vertical_matrix(struct Vector *v, struct Matrix *m) {

    if (!matrix(m, v->l, 1)) return false;

    for (int i = 0; i < v->l; i++) {
        m->m[i] = v->v[i];
    }

    return true;
}

bool vector_to_horizontal_matrix(struct Vector *v, struct Matrix *m) {

    if (!matrix(m, 1, v->l)) return false;

    for (int i = 0; i < v->l; i++) {
        m->m[i] = v->v[i];
    }

    return true;
}

bool matrix_vector_multiply(struct Matrix *m, struct Vector *v, struct Vector *r) {

    if (m->c != v->l) return false;
    if (!vector(r, m->r)) return false;

    for (int i = 0; i < m->r; i++) {
        for (int j = 0; j < m->c; j++) {
            r->v[i] += m->m[j + i * m->c] * v->v[j];
        }
    }

    return true;
}

bool vector_matrix_multiply(struct Vector *v, struct Matrix *m, struct Vector *r) {

    if (m->r != v->l) return false;
    if (!vector(r, m->c)) return false;

    for (int i = 0; i < m->r; i++) {
        for (int j = 0; j < m->c; j++) {
            r->v[j] += m->m[j + i * m->c] * v->v[i];
        }
    }

    return true;
}