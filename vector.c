#include "vector.h"

bool vector(struct Vector *v, int l) {

    float *mem = (float *) calloc(l, sizeof(float));

    if (mem == NULL) {

        v->v = NULL;
        v->l = 0;

        return false;
    }

    v->v = mem;
    v->l = l;

    return true;
}

bool vector_from_array(struct Vector *v, float *arr, int l) {
    
    if (!vector(v, l)) return false;

    for (int i = 0; i < l; i++) {
        v->v[i] = arr[i];
    }

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

void vector_print(struct Vector *v) {

    for (int i = 0; i < v->l; i++) {
        printf("%f  ", v->v[i]);
    }
    printf("\n");
}

int vector_length(struct Vector *v) {
    return v->l;
}

bool vector_add(struct Vector *a, struct Vector *b, struct Vector *r) {

    if (a->l != b->l) return false;
    if (!vector(r, a->l)) return false;

    for (int i = 0; i < a->l; i++) {
        r->v[i] = a->v[i] + b->v[i];
    }

    return true;
}

bool vector_subtract(struct Vector *a, struct Vector *b, struct Vector *r) {

    if (a->l != b->l) return false;
    if (!vector(r, a->l)) return false;

    for (int i = 0; i < a->l; i++) {
        r->v[i] = a->v[i] - b->v[i];
    }

    return true;
}

bool vector_to_array(struct Vector *v, float *arr, int l) {
    
    if (v->l != l) return false;

    for (int i = 0; i < v->l; i++) {
        arr[i] = v->v[i];
    }

    return true;
}

bool vector_scalar_multiply(struct Vector *v, float n, struct Vector *r) {

    if (!vector(r, v->l)) return false;

    for (int i = 0; i < r->l; i++) {
        r->v[i] = v->v[i] * n;
    }

    return true;
}

void vector_clear(struct Vector *v) {
    free(v->v);
    v->v = NULL;
    v->l = 0;
}

bool vector_resize(struct Vector *v, int l) {
    
    vector_clear(v);

    if (vector(v, l)) return true;
    else return false;
}

bool vector_normalize(struct Vector *v, struct Vector *r) {

    if (!vector(r, v->l)) return false;

    float abs = vector_absolute(v);

    for (int i = 0; i < r->l; i++) {
        r->v[i] = v->v[i] / abs;
    }

    return true;
}

float vector_absolute(struct Vector *v) {
    
    float abs = 0;

    for (int i = 0; i < v->l; i++) {
        abs += powf(v->v[i], 2.0f);
    }

    return sqrt(abs);
}

bool vector_equal(struct Vector *a, struct Vector *b) {

    if (a->l != b->l) return false;

    for (int i = 0; i < a->l; i++) {
        if (a->v[i] != b->v[i]) return false;
    }

    return true;
}

bool vector_map(struct Vector *v, float (*f)(float), struct Vector *r) {

    if (!vector(r, v->l)) return false;

    for (int i = 0; i < r->l; i++) {
        r->v[i] = (*f)(v->v[i]);
    }

    return true;
}

bool vector_angle(struct Vector *a, struct Vector *b, float *r) {
    
    float dot_product;

    if (!vector_dot_product(a, b, &dot_product)) return false;

    *r = acos(dot_product / (vector_absolute(a) * vector_absolute(b)));    

    return true;
}

bool vector_dot_product(struct Vector *a, struct Vector *b, float *r) {

    if (a->l != b->l) return false;

    *r = 0;

    for (int i = 0; i < a->l; i++) {
        *r += a->v[i] * b->v[i];
    }

    return true;
}

bool vector_cross_product(struct Vector *a, struct Vector *b, struct Vector *r) {
    
    if (a->l != 3 || b->l != 3) return false;
    if (!vector(r, 3)) return false;
    
    r->v[0] = a->v[1] * b->v[2] - a->v[2] * b->v[1];
    r->v[1] = -(a->v[0] * b->v[2] - a->v[2] * b->v[0]);
    r->v[2] = a->v[0] * b->v[1] - a->v[1] * b->v[0];

    return true;
}

bool vector_triple_product(struct Vector *a, struct Vector *b, struct Vector *c, float *r) {

    if (a->l != 3 || b->l != 3 || c->l != 3) return false;

    struct Vector cross_vector;

    if (!vector_cross_product(b, c, &cross_vector)) return false;
    if (!vector_dot_product(a, &cross_vector, r)) return false;

    vector_clear(&cross_vector);

    return true;
}