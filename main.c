#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

int main(int argc, char *argv[]) {

    struct Matrix m1;
    struct Matrix m2;
    struct Matrix m3;

    float arr1[] = {6, 3, 9, 1, 7, 2};
    matrix_from_array(&m1, 2, 3, arr1);

    float arr2[] = {5, 2, 4, 8, 9, 1};
    matrix_from_array(&m2, 3, 2, arr2);

    matrix_multiply(&m1, &m2, &m3);
    matrix_scalar_multiply(&m3, 2.0);

    printf("%f", m3.m[5]);

    return 0;
}