#include "vector.h"

#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct Vector {
    size_t s;
    float *d;
} Vector;

Vector *vector_create(size_t s) {

    Vector *v = (Vector*) malloc(sizeof(Vector));
    if (v == NULL) return NULL;

    float *d = (float*) calloc(s, sizeof(float));
    if (d == NULL) {
        free(v);
        return NULL;
    }

    v->d = d;
    v->s = s;

    return v;
}

void vector_destroy(Vector *v) {
    free(v->d);
    free(v);
}

Vector *vector_from_array(const float *arr, size_t s) {

    Vector *r = vector_create(s);
    if (r == NULL) return NULL;

    memcpy(r->d, arr, s * sizeof(float));

    return r;
}

int vector_set_value(Vector *v, size_t i, float n) {

    if (i > v->s || i < 0) return 0;

    v->d[i] = n;

    return 1;
}

int vector_get_value(const Vector *v, size_t i, float *n) {

    if (i > v->s || i < 0) return 0;

    *n = v->d[i];

    return 1;
}

void vector_print(const Vector *v) {

    for (int i = 0; i < v->s; i++) {
        printf("%f  ", v->d[i]);
    }
    printf("\n");
}

size_t vector_size(const Vector *v) {
    return v->s;
}

Vector *vector_add(const Vector *a, const Vector *b) {

    if (a->s != b->s) return NULL;

    Vector *r = vector_create(a->s);
    if (r == NULL) return NULL;

    for (int i = 0; i < a->s; i++) {
        r->d[i] = a->d[i] + b->d[i];
    }

    return r;
}

Vector *vector_subtract(const Vector *a, const Vector *b) {

    if (a->s != b->s) return NULL;

    Vector *r = vector_create(a->s);
    if (r == NULL) return NULL;

    for (int i = 0; i < a->s; i++) {
        r->d[i] = a->d[i] - b->d[i];
    }

    return r;
}

float *vector_to_array(const Vector *v) {

    float *arr = (float*) calloc(v->s, sizeof(float));
    if (arr == NULL) return NULL;

    memcpy(arr, v->d, v->s * sizeof(float));

    return arr;
}

Vector *vector_scalar_multiply(const Vector *v, float n) {

    Vector *r = vector_create(v->s);
    if (r == NULL) return NULL;

    for (int i = 0; i < r->s; i++) {
        r->d[i] = v->d[i] * n;
    }

    return r;
}

Vector *vector_scalar_add(const Vector *v, float n) {

    Vector *r = vector_create(v->s);
    if (r == NULL) return NULL;

    for (int i = 0; i < r->s; i++) {
        r->d[i] = v->d[i] + n;
    }

    return r;
}

Vector *vector_scalar_subtract(const Vector *v, float n) {

    Vector *r = vector_create(v->s);
    if (r == NULL) return NULL;

    for (int i = 0; i < r->s; i++) {
        r->d[i] = v->d[i] - n;
    }

    return r;
}

Vector *vector_normalize(const Vector *v) {

    Vector *r = vector_create(v->s);
    if (r == NULL) return NULL;

    float abs = vector_modulus(v);

    for (int i = 0; i < r->s; i++) {
        r->d[i] = v->d[i] / abs;
    }

    return r;
}

float vector_modulus(const Vector *v) {

    float abs = 0;

    for (int i = 0; i < v->s; i++) {
        abs += powf(v->d[i], 2.0f);
    }

    return sqrt(abs);
}

int vector_equal(const Vector *a, const Vector *b) {

    if (a->s != b->s) return 0;

    for (int i = 0; i < a->s; i++) {
        if (a->d[i] != b->d[i]) return 0;
    }

    return 1;
}

Vector *vector_map(const Vector *v, float (*f)(float)) {

    Vector *r = vector_create(v->s);
    if (r == NULL) return NULL;

    for (int i = 0; i < r->s; i++) {
        r->d[i] = (*f)(v->d[i]);
    }

    return r;
}

int vector_angle_rad(const Vector *a, const Vector *b, float *r) {

    float dot_product;

    if (vector_dot_product(a, b, &dot_product) == 0) return 0;

    *r = acos(dot_product / (vector_modulus(a) * vector_modulus(b)));

    return 1;
}

int vector_angle_deg(const Vector *a, const Vector *b, float *r) {

    float rad;
    if (vector_angle_rad(a, b, &rad) == 0) return 0;

    *r = rad * 180 / M_PI;

    return 1;
}

int vector_dot_product(const Vector *a, const Vector *b, float *r) {

    if (a->s != b->s) return 0;

    *r = 0;

    for (int i = 0; i < a->s; i++) {
        *r += a->d[i] * b->d[i];
    }

    return 1;
}

Vector *vector_cross_product(const Vector *a, const Vector *b) {

    if (a->s != 3 || b->s != 3) return NULL;

    Vector *r = vector_create(a->s);
    if (r == NULL) return NULL;

    r->d[0] = a->d[1] * b->d[2] - a->d[2] * b->d[1];
    r->d[1] = -(a->d[0] * b->d[2] - a->d[2] * b->d[0]);
    r->d[2] = a->d[0] * b->d[1] - a->d[1] * b->d[0];

    return r;
}

int vector_triple_product(const Vector *a, const Vector *b, const Vector *c, float *r) {

    if (a->s != 3 || b->s != 3 || c->s != 3) return 0;

    Vector *cross = vector_cross_product(b, c);
    if (cross == NULL) return 0;

    if (vector_dot_product(a, cross, r) == 0) return 0;

    vector_destroy(cross);

    return 1;
}

Vector *vector_copy(const Vector *v) {

    Vector *r = (Vector*) malloc(sizeof(Vector));
    if (r == NULL) return NULL;

    r->s = v->s;
    memcpy(r->d, v->d, v->s * sizeof(float));

    return r;
}

int vector_copy_values(const Vector *from, Vector *to) {

    if (from->s != to->s) return 0;

    memcpy(to->d, from->d, to->s * sizeof(float));

    return 1;
}

int vector_push_back(Vector *v, float n) {

    float *d = (float*) realloc(v->d, v->s + 1);
    if (d == NULL) return 0;

    d[v->s] = n;
    v->d = d;
    v->s = v->s + 1;

    return 1;
}

int vector_pop_back(Vector *v) {

    if (v->s == 0) return 0;

    float *d = (float*) realloc(v->d, v->s - 1);
    if (d == NULL) return 0;

    v->d = d;
    v->s = v->s - 1;

    return 1;
}
