#ifndef LINEAR_ALGEBRA
#define LINEAR_ALGEBRA

#include "matrix.h"
#include "vector.h"

bool matrix_to_vector(struct Matrix *m, struct Vector *v);
bool vector_to_vertical_matrix(struct Vector *v, struct Matrix *m);
bool vector_to_horizontal_matrix(struct Vector *v, struct Matrix *m);

bool matrix_vector_multiply(struct Matrix *m, struct Vector *v, struct Vector *r);
bool vector_matrix_multiply(struct Vector *v, struct Matrix *m, struct Vector *r);

#endif // LINEAR_ALGEBRA