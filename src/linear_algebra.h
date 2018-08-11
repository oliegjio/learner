#ifndef LINEAR_ALGEBRA_H_
#define LINEAR_ALGEBRA_H_

#include "matrix.h"
#include "vector.h"

Vector *matrix_to_vector(const Matrix *m);
Matrix *vector_to_vertical_matrix(const Vector *v);
Matrix *vector_to_horizontal_matrix(const Vector *v);

#endif // LINEAR_ALGEBRA_H_
