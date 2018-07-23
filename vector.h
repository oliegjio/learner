#ifndef VECTOR
#define VECTOR

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

struct Vector {
    float *v;
    int l;
};

bool vector(struct Vector *v, int l);
bool vector_from_array(struct Vector *v, float *arr, int l);
bool vector_to_array(struct Vector *v, float *arr, int l);
void vector_clear(struct Vector *v);
bool vector_resize(struct Vector *v, int l);

bool vector_add(struct Vector *a, struct Vector *b, struct Vector *r);
bool vector_subtract(struct Vector *a, struct Vector *b, struct Vector *r);
bool vector_scalar_multiply(struct Vector *v, float n, struct Vector *r);
bool vector_dot_product(struct Vector *a, struct Vector *b, float *r);
bool vector_cross_product(struct Vector *a, struct Vector *b, struct Vector *r);
bool vector_triple_product(struct Vector *a, struct Vector *b, struct Vector *c, float *r);
bool vector_normalize(struct Vector *v, struct Vector *r);
bool vector_angle(struct Vector *a, struct Vector *b, float *r);
float vector_absolute(struct Vector *v);
bool vector_equal(struct Vector *a, struct Vector *b);
bool vector_map(struct Vector *m, float (*f)(float), struct Vector *r);

bool vector_get(struct Vector *v, int i, float *n);
bool vector_set(struct Vector *v, int i, float n);
int vector_length(struct Vector *v);

void vector_print(struct Vector *v);

#endif