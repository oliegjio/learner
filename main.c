#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "linear_algebra.h"

float plus3(float n) { return n * 100; }
float (*f)(float) = &plus3;

int main(int argc, char *argv[]) {

    srand(time(NULL));

    struct Matrix m1;
    struct Matrix m2;
    struct Matrix m3;

    struct Vector v1;
    struct Vector v2;
    struct Vector v3;
    struct Vector v4;

    float arr1[] = {1, 2, 3};
    vector_from_array(&v1, arr1, 3);

    float arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3};
    matrix_from_array(&m1, 3, 4, arr2, 12);

    matrix_print(&m1);

    vector_matrix_multiply(&v1, &m1, &v4);

    vector_print(&v4);

    return 0;
}