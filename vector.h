#ifndef VECTOR
#define VECTOR

#include <stdlib.h>
#include <stdbool.h>

struct Vector {
    float *v;
    int l;
};

bool vector(struct Vector *v, int l);

void vector_fill_with_float(struct Vector *v, float n);

bool vector_get(struct Vector *v, int i, float *n);
bool vector_set(struct Vector *v, int i, float n);

#endif