#ifndef LINEAR_ALGEBRA
#define LINEAR_ALGEBRA

#include "matrix.h"
#include "vector.h"

bool matrix_to_vector(Matrix *m, Vector *v);
bool vector_to_vertical_matrix(Vector *v, Matrix *m);
bool vector_to_horizontal_matrix(Vector *v, Matrix *m);

bool matrix_vector_multiply(Matrix *m, Vector *v, Vector *r);
bool vector_matrix_multiply(Vector *v, Matrix *m, Vector *r);
bool vector_vector_multiply(Vector *a, Vector *b, Matrix *r);

#endif // LINEAR_ALGEBRA