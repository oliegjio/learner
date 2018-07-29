#include "vector.h"

bool vector(Vector *v, int l) {

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

bool vector_from_array(Vector *v, float *arr, int l) {
    
    if (!vector(v, l)) return false;

    for (int i = 0; i < l; i++) {
        v->v[i] = arr[i];
    }

    return true;
}

bool vector_set(Vector *v, int i, float n) {

    if (i > v->l || i < 0) return false;

    v->v[i] = n;

    return true;
}

bool vector_get(Vector *v, int i, float *n) {

    if (i > v->l || i < 0) return false;

    *n = v->v[i];

    return true;
}

void vector_print(Vector *v) {

    for (int i = 0; i < v->l; i++) {
        printf("%f  ", v->v[i]);
    }
    printf("\n");
}

int vector_length(Vector *v) {
    return v->l;
}

bool vector_add(Vector *a, Vector *b, Vector *r) {

    if (a->l != b->l) return false;
    if (!vector(r, a->l)) return false;

    for (int i = 0; i < a->l; i++) {
        r->v[i] = a->v[i] + b->v[i];
    }

    return true;
}

bool vector_subtract(Vector *a, Vector *b, Vector *r) {

    if (a->l != b->l) return false;
    if (!vector(r, a->l)) return false;

    for (int i = 0; i < a->l; i++) {
        r->v[i] = a->v[i] - b->v[i];
    }

    return true;
}

bool vector_to_array(Vector *v, float *arr, int l) {
    
    if (v->l != l) return false;

    for (int i = 0; i < v->l; i++) {
        arr[i] = v->v[i];
    }

    return true;
}

bool vector_scalar_multiply(Vector *v, float n, Vector *r) {

    if (!vector(r, v->l)) return false;

    for (int i = 0; i < r->l; i++) {
        r->v[i] = v->v[i] * n;
    }

    return true;
}

void vector_clear(Vector *v) {
    free(v->v);
    v->v = NULL;
    v->l = 0;
}

bool vector_resize(Vector *v, int l) {
    
    vector_clear(v);

    if (vector(v, l)) return true;
    else return false;
}

bool vector_normalize(Vector *v, Vector *r) {

    if (!vector(r, v->l)) return false;

    float abs = vector_absolute(v);

    for (int i = 0; i < r->l; i++) {
        r->v[i] = v->v[i] / abs;
    }

    return true;
}

float vector_absolute(Vector *v) {
    
    float abs = 0;

    for (int i = 0; i < v->l; i++) {
        abs += powf(v->v[i], 2.0f);
    }

    return sqrt(abs);
}

bool vector_equal(Vector *a, Vector *b) {

    if (a->l != b->l) return false;

    for (int i = 0; i < a->l; i++) {
        if (a->v[i] != b->v[i]) return false;
    }

    return true;
}

bool vector_map(Vector *v, float (*f)(float), Vector *r) {

    if (!vector(r, v->l)) return false;

    for (int i = 0; i < r->l; i++) {
        r->v[i] = (*f)(v->v[i]);
    }

    return true;
}

bool vector_angle(Vector *a, Vector *b, float *r) {
    
    float dot_product;

    if (!vector_dot_product(a, b, &dot_product)) return false;

    *r = acos(dot_product / (vector_absolute(a) * vector_absolute(b)));    

    return true;
}

bool vector_dot_product(Vector *a, Vector *b, float *r) {

    if (a->l != b->l) return false;

    *r = 0;

    for (int i = 0; i < a->l; i++) {
        *r += a->v[i] * b->v[i];
    }

    return true;
}

bool vector_cross_product(Vector *a, Vector *b, Vector *r) {
    
    if (a->l != 3 || b->l != 3) return false;
    if (!vector(r, 3)) return false;
    
    r->v[0] = a->v[1] * b->v[2] - a->v[2] * b->v[1];
    r->v[1] = -(a->v[0] * b->v[2] - a->v[2] * b->v[0]);
    r->v[2] = a->v[0] * b->v[1] - a->v[1] * b->v[0];

    return true;
}

bool vector_triple_product(Vector *a, Vector *b, Vector *c, float *r) {

    if (a->l != 3 || b->l != 3 || c->l != 3) return false;

    Vector cross_vector;

    if (!vector_cross_product(b, c, &cross_vector)) return false;
    if (!vector_dot_product(a, &cross_vector, r)) return false;

    vector_clear(&cross_vector);

    return true;
}

bool vector_copy_vector_values(Vector *from, Vector *to) {

    if (from->l != to->l) return false;

    for (int i = 0; i < to->l; i++) {
        to->v[i] = from->v[i];
    }

    return true;
}

bool vector_copy_array_values(float *from, int s, Vector *to) {

    if (s != to->l) return false;

    for (int i = 0; i < s; i++) {
        to->v[i] = from[i];
    }
    
    return true;
}

void vector_set_values(Vector *v, float f) {

    for (int i = 0; i < v->l; i++) {
        v->v[i] = f;
    }
}