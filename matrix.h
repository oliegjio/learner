#ifndef MATRIX_H
#define MATRIX_H

#define CXR(m,x,y) (m[x]);

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct Matrix {
    int c;
    int r;
    float *m;
};

bool matrix_init(struct Matrix *m, int c, int r);
bool matrix_from_array(struct Matrix *m, int c, int r, float *arr);
void matrix_fill_by_array(struct Matrix *m, float *arr);
void matrix_clear(struct Matrix *m);

bool matrix_is_dimensions_equal(struct Matrix *a, struct Matrix *b);
bool matrix_is_in_bounds(struct Matrix *m, int x, int y);
bool matrix_can_multiply(struct Matrix *a, struct Matrix *b);

bool matrix_select_column(struct Matrix *m, int n, float *r);
bool matrix_select_row(struct Matrix *m, int n, float *r);

bool matrix_add(struct Matrix *a, struct Matrix *b, struct Matrix *r);
bool matrix_substract(struct Matrix *a, struct Matrix *b, struct Matrix *r);
bool matrix_multiply(struct Matrix *a, struct Matrix *b, struct Matrix *r);

bool matrix_get(struct Matrix *m, int x, int y, float *r);
bool matrix_set(struct Matrix *m, int x, int y, float v);

#endif // MATRIX_H