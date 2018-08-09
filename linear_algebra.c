#include "linear_algebra.h"
#include "matrix_internal.h"
#include "vector_internal.h"

#include <string.h>

Vector *matrix_to_vector(const Matrix *m) {

    if (m->c != 1 && m->r != 1) return NULL;

    Vector *v = vector_create(m->r * m->c);
    if (v == NULL) return NULL;

    memcpy(v->d, m->d, m->r * m->c * sizeof(float));

    return v;
}

Matrix *vector_to_vertical_matrix(const Vector *v) {

    Matrix *r = matrix_create(v->s, 1);
    if (r == NULL) return NULL;

    memcpy(r->d, v->d, v->s * sizeof(float));

    return r;
}

Matrix *vector_to_horizontal_matrix(const Vector *v) {

    Matrix *r = matrix_create(1, v->s);
    if (r == NULL) return NULL;

    memcpy(r->d, v->d, v->s * sizeof(float));

    return r;
}
