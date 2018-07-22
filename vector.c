#include "vector.h"

bool vector(struct Vector *v, int l) {

    float *mem = (float *) malloc(l * sizeof(float));

    if (mem == NULL) return false;

    v->v = mem;
    v->l = l;

    return true;
}

bool vector_set(struct Vector *v, int i, float n) {

    if (i > v->l || i < 0) return false;

    v->v[i] = n;

    return true;
}

bool vector_get(struct Vector *v, int i, float *n) {

    if (i > v->l || i < 0) return false;

    *n = v->v[i];

    return true;
}

void vector_fill_with_float(struct Vector *v, float n) {

    for (int i = 0; i < v->l; i++) {
        vector_set(v, i, n);
    }
}