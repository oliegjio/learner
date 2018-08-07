#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct Matrix {
    size_t c;
    size_t r;
    float *m;
} Matrix;

int matrix(Matrix *m, size_t r, size_t c);
int matrix_from_array(Matrix *m, size_t r, size_t c, float *arr, size_t s);
int matrix_to_array(Matrix *m, float *arr);
void matrix_free(Matrix *m);
int matrix_resize(Matrix *a, size_t r, size_t c);

int matrix_copy_values(Matrix *from, Matrix *to);

int matrix_is_dimensions_equal(Matrix *a, Matrix *b);
int matrix_is_in_bounds(Matrix *m, size_t r, size_t c);
int matrix_can_multiply(Matrix *a, Matrix *b);

int matrix_select_column(Matrix *m, size_t n, float *v);
int matrix_select_row(Matrix *m, size_t n, float *v);

int matrix_add(Matrix *a, Matrix *b, Matrix *r);
int matrix_subtract(Matrix *a, Matrix *b, Matrix *r);
int matrix_multiply(Matrix *a, Matrix *b, Matrix *r);
int matrix_scalar_multiply(Matrix *m, float n, Matrix *r);
int matrix_scalar_add(Matrix *m, float n, Matrix *r);
int matrix_scalar_subtract(Matrix *m, float n, Matrix *r);
int matrix_transpose(Matrix *m, Matrix *r);
int matrix_map(Matrix *m, float (*f)(float), Matrix *r);
int matrix_equal(Matrix *a, Matrix *b);

int matrix_get(Matrix *m, size_t r, size_t c, float *v);
int matrix_set(Matrix *m, size_t r, size_t c, float v);
size_t matrix_columns(Matrix *m);
size_t matrix_rows(Matrix *m);

void matrix_print(Matrix *m);

#endif // MATRIX_H_