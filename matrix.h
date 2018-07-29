#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Matrix {
    int c;
    int r;
    float *m;
} Matrix;

bool matrix(Matrix *m, int r, int c);
bool matrix_from_array(Matrix *m, int r, int c, float *arr, int s);
bool matrix_to_array(Matrix *m, float *arr, int s);
void matrix_clear(Matrix *m);
bool matrix_resize(Matrix *a, int r, int c);

bool matrix_copy_values(Matrix *from, Matrix *to);

bool matrix_is_dimensions_equal(Matrix *a, Matrix *b);
bool matrix_is_in_bounds(Matrix *m, int r, int c);
bool matrix_can_multiply(Matrix *a, Matrix *b);

bool matrix_select_column(Matrix *m, int n, float *v, int s);
bool matrix_select_row(Matrix *m, int n, float *v, int s);

bool matrix_add(Matrix *a, Matrix *b, Matrix *r);
bool matrix_subtract(Matrix *a, Matrix *b, Matrix *r);
bool matrix_multiply(Matrix *a, Matrix *b, Matrix *r);
bool matrix_scalar_multiply(Matrix *m, float n, Matrix *r);
bool matrix_transpose(Matrix *m, Matrix *r);
bool matrix_map(Matrix *m, float (*f)(float), Matrix *r);
bool matrix_equal(Matrix *a, Matrix *b);

bool matrix_get(Matrix *m, int r, int c, float *v);
bool matrix_set(Matrix *m, int r, int c, float v);
int matrix_columns(Matrix *m);
int matrix_rows(Matrix *m);

void matrix_print(Matrix *m);

#endif // MATRIX_H