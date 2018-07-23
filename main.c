#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "matrix.h"

float plus3(float n) { return n * 100; }
float (*f)(float) = &plus3;

int main(int argc, char *argv[]) {

    srand(time(NULL));

    struct Matrix m1;
    struct Matrix m2;
    struct Matrix m3;

    float arr1[] = {1, 2, 3, 4, 5, 6};
    matrix_from_array(&m1, 2, 3, arr1);

    float arr2[] = {1, 2, 3, 4, 5, 6};
    matrix_from_array(&m2, 2, 3, arr2);

    bool result = matrix_equal(&m1, &m2);

    if (result) printf("TRUE");
    else printf("FALSE");
    

    return 0;
}