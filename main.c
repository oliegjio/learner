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

    matrix(&m1, 500, 500);
    matrix_randomize(&m1, 10, 15);

    matrix(&m2, 500, 500);
    matrix_randomize(&m2, 10, 15);

    matrix_multiply(&m1, &m2, &m3);

    matrix_print(&m3);
    

    return 0;
}