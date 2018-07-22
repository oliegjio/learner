#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

int main(int argc, char *argv[]) {

    const int COLS = 2;
    const int ROWS = 2;

    struct Matrix m1;
    struct Matrix m2;
    struct Matrix m3;

    float arr1[] = {1, 3, 3, 4};
    matrix_from_array(&m1, 2, 2, arr1);

    float arr2[] = {4, 3, 2, 1};
    matrix_from_array(&m2, 2, 2, arr2);

    matrix_add(&m1, &m2, &m3);

    printf("%f", m3.m[1]);

    return 0;
}