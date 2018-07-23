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

    float arr1[3] = {9, 2, 3};
    vector_from_array(&v1, 3, arr1, 3);

    float arr2[3] = {4, 5, 2};
    vector_from_array(&v2, 3, arr2, 3);

    float arr3[3] = {8, 7, 1};
    vector_from_array(&v3, 3, arr3, 3);

    vector_print(&v1);
    vector_print(&v2);
    vector_print(&v3);

    float result;
    vector_triple_product(&v1, &v2, &v3, &result);

    printf("%f", result);

    return 0;
}