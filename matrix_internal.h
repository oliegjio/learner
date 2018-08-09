#ifndef MATRIX_INTERNAL_H_
#define MATRIX_INTERNAL_H_

typedef struct Matrix {
    size_t r, c;
    float *d;
} Matrix;

#endif // MATRIX_INTERNAL_H_
