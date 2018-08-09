#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdlib.h>

typedef struct Vector Vector;

Vector *vector_create(size_t s);
void vector_destroy(Vector *v);

Vector *vector_from_array(const float *arr, size_t s);
float *vector_to_array(const Vector *v);

Vector *vector_copy(const Vector *v);
int vector_copy_values(const Vector *from, Vector *to);

Vector *vector_add(const Vector *a, const Vector *b);
Vector *vector_subtract(const Vector *a, const Vector *b);
Vector *vector_scalar_multiply(const Vector *v, float n);
Vector *vector_scalar_add(const Vector *v, float n);
Vector *vector_scalar_subtract(const Vector *v, float n);
int vector_dot_product(const Vector *a, const Vector *b, float *r);
Vector *vector_cross_product(const Vector *a, const Vector *b);
int vector_triple_product(const Vector *a, const Vector *b, const Vector *c, float *r);
Vector *vector_normalize(const Vector *v);
int vector_angle_rad(const Vector *a, const Vector *b, float *r);
int vector_angle_deg(const Vector *a, const Vector *b, float *r);
float vector_modulus(const Vector *v);
int vector_equal(const Vector *a, const Vector *b);
Vector *vector_map(const Vector *v, float (*f)(float));

int vector_push_back(Vector *v, float n);
int vector_pop_back(Vector *v);

int vector_get_value(const Vector *v, size_t i, float *n);
int vector_set_value(Vector *v, size_t i, float n);
size_t vector_size(const Vector *v);

void vector_print(const Vector *v);

#endif // VECTOR_H_
