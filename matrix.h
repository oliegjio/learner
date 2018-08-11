#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdlib.h>

typedef struct Matrix Matrix;

Matrix *matrix_create(size_t r, size_t c);
void matrix_destroy(Matrix *m);

Matrix *matrix_from_array(const float *arr, size_t r, size_t c);
float *matrix_to_array(const Matrix *m);

Matrix* matrix_copy(const Matrix *m);
int matrix_copy_values(const Matrix *from, Matrix *to);

int matrix_is_dimensions_equal(const Matrix *a, const Matrix *b);
int matrix_is_in_bounds(const Matrix *m, size_t r, size_t c);
int matrix_can_multiply(const Matrix *a, const Matrix *b);

float *matrix_column_to_array(const Matrix *m, size_t n);
float *matrix_row_to_array(const Matrix *m, size_t n);

int matrix_add_l(Matrix *a, const Matrix *b);
int matrix_subtract_l(Matrix *a, const Matrix *b);
int matrix_multiply_l(Matrix *a, const Matrix *b);
int matrix_multiply_r(const Matrix *a, Matrix *b);
void matrix_scalar_add_l(Matrix *m, float n);
void matrix_scalar_subtract_l(Matrix *m, float n);
void matrix_scalar_multiply_l(Matrix *m, float n);
int matrix_transpose_l(Matrix *m);
int matrix_hadamard_product_l(Matrix *a, const Matrix *b);
void matrix_map_l(Matrix *m, float (*f)(float));

Matrix *matrix_add(const Matrix *a, const Matrix *b);
Matrix *matrix_subtract(const Matrix *a, const Matrix *b);
Matrix *matrix_multiply(const Matrix *a, const Matrix *b);
Matrix *matrix_hadamard_product(const Matrix *a, const Matrix *b);
Matrix *matrix_scalar_add(const Matrix *m, float n);
Matrix *matrix_scalar_subtract(const Matrix *m, float n);
Matrix *matrix_scalar_multiply(const Matrix *m, float n);
Matrix *matrix_transpose(const Matrix *m);
Matrix *matrix_map(const Matrix *m, float (*f)(float));

int matrix_equal(const Matrix *a, const Matrix *b);

int matrix_get_value(const Matrix *m, size_t r, size_t c, float *v);
int matrix_set_value(Matrix *m, size_t r, size_t c, float v);
size_t matrix_columns(const Matrix *m);
size_t matrix_rows(const Matrix *m);

void matrix_print(const Matrix *m);

#endif // MATRIX_H_
