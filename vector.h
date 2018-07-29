#ifndef VECTOR
#define VECTOR

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

typedef struct Vector {
    float *v;
    int l;
} Vector;

bool vector(Vector *v, int l);
bool vector_from_array(Vector *v, float *arr, int l);
bool vector_to_array(Vector *v, float *arr, int l);
void vector_clear(Vector *v);
bool vector_resize(Vector *v, int l);

bool vector_copy_vector_values(Vector *from, Vector *to);
bool vector_copy_array_values(float *from, int s, Vector *to);
void vector_set_values(Vector *v, float f);

bool vector_add(Vector *a, Vector *b, Vector *r);
bool vector_subtract(Vector *a, Vector *b, Vector *r);
bool vector_scalar_multiply(Vector *v, float n, Vector *r);
bool vector_dot_product(Vector *a, Vector *b, float *r);
bool vector_cross_product(Vector *a, Vector *b, Vector *r);
bool vector_triple_product(Vector *a, Vector *b, Vector *c, float *r);
bool vector_normalize(Vector *v, Vector *r);
bool vector_angle(Vector *a, Vector *b, float *r);
float vector_absolute(Vector *v);
bool vector_equal(Vector *a, Vector *b);
bool vector_map(Vector *m, float (*f)(float), Vector *r);

bool vector_get(Vector *v, int i, float *n);
bool vector_set(Vector *v, int i, float n);
int vector_length(Vector *v);

void vector_print(Vector *v);

#endif