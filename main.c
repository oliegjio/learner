#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

float plus3(float n) { return n * 100; }
float (*f)(float) = &plus3;

int main(int argc, char *argv[]) {

    struct Matrix m1;
    struct Matrix m2;
    struct Matrix m3;

    float arr1[] = {6, 3, 9, 1, 7, 2};
    matrix_from_array(&m1, 2, 3, arr1);

    float arr2[] = {5, 2, 4, 8, 9, 1};
    matrix_from_array(&m2, 2, 3, arr2);

    matrix_add(&m1, &m2, &m3);
    matrix_scalar_multiply(&m3, 2.0);



    struct Matrix m4;
    struct Matrix m5;
    float arr4[] = {1, 2, 3, 4, 5, 6};
    matrix_from_array(&m4, 3, 2, arr4);

    matrix_print(&m4);

    matrix_transpose(&m4, &m5);

    matrix_print(&m5);

    struct Matrix m6;

    matrix_map(&m5, &m6, f);

    matrix_print(&m6);

    return 0;
}