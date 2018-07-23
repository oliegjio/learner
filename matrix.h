#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct Matrix {
    int c;
    int r;
    float *m;
};

bool matrix(struct Matrix *m, int r, int c);
bool matrix_from_array(struct Matrix *m, int r, int c, float *arr, int s);
bool matrix_to_array(struct Matrix *m, float *arr, int s);
void matrix_clear(struct Matrix *m);
bool matrix_resize(struct Matrix *a, int r, int c);

bool matrix_is_dimensions_equal(struct Matrix *a, struct Matrix *b);
bool matrix_is_in_bounds(struct Matrix *m, int r, int c);
bool matrix_can_multiply(struct Matrix *a, struct Matrix *b);

bool matrix_select_column(struct Matrix *m, int n, float *v, int s);
bool matrix_select_row(struct Matrix *m, int n, float *v, int s);

bool matrix_add(struct Matrix *a, struct Matrix *b, struct Matrix *r);
bool matrix_subtract(struct Matrix *a, struct Matrix *b, struct Matrix *r);
bool matrix_multiply(struct Matrix *a, struct Matrix *b, struct Matrix *r);
bool matrix_scalar_multiply(struct Matrix *m, float n, struct Matrix *r);
bool matrix_transpose(struct Matrix *m, struct Matrix *r);
bool matrix_map(struct Matrix *m, float (*f)(float), struct Matrix *r);
bool matrix_equal(struct Matrix *a, struct Matrix *b);

bool matrix_get(struct Matrix *m, int r, int c, float *v);
bool matrix_set(struct Matrix *m, int r, int c, float v);
int matrix_columns(struct Matrix *m);
int matrix_rows(struct Matrix *m);

void matrix_print(struct Matrix *m);

#endif // MATRIX_H