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

    matrix(&m1, 3, 3);

    return 0;
}