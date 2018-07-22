#include "matrix.h"

bool matrix_init(struct Matrix *m, int c, int r) {

    float *mem = (float*) malloc(r * c * sizeof(float));

    if (mem == NULL) return false;

    m->c = c;
    m->r = r;
    m->m = mem;

    return true;
}

bool matrix_is_dimensions_equal(struct Matrix *a, struct Matrix *b) {
    if (a->c != b->c) return false;
    if (a->r != b->r) return false;
    return true;
}

bool matrix_add(struct Matrix *a, struct Matrix *b, struct Matrix *r) {
    
    if (!matrix_is_dimensions_equal(a, b)) return false;

    float a_value, b_value;

    for (int i = 0; i < a->c; i++) {
        for (int j = 0; j < a->r; j++) {

            matrix_get(a, i, j, &a_value);
            matrix_get(b, i, j, &b_value);

            matrix_set(r, i, j, a_value + b_value);
        }
    }

    return true;
}

bool matrix_substract(struct Matrix *a, struct Matrix *b, struct Matrix *r) {
    
    if (!matrix_is_dimensions_equal(a, b)) return false;

    float a_value, b_value;

    for (int i = 0; i < a->c; i++) {
        for (int j = 0; j < a->r; j++) {

            matrix_get(a, i, j, &a_value);
            matrix_get(b, i, j, &b_value);

            matrix_set(r, i, j, a_value - b_value);
        }
    }

    return true;
}

bool matrix_can_multiply(struct Matrix *a, struct Matrix *b) {
    if (a->c != b->r) return false;
    return true;
}

bool matrix_select_column(struct Matrix *m, int n, float *r) {
    
    if (n > m->c) return false;
    if (n < 0) return false;

    float value;

    for (int i = 0; i < m->r; i++) {
        matrix_get(m, n, i, &value);
        r[i] = value;
    }

    return true;
}

bool matrix_select_row(struct Matrix *m, int n, float *r) {

    if (n > m->r) return false;
    if (n < 0) return false;

    float value;

    for (int i = 0; i < m->c; i++) {
        matrix_get(m, i, n, &value);
        r[i] = value;
    }

    return true;
}

bool matrix_multiply(struct Matrix *a, struct Matrix *b, struct Matrix *r) {

    if (!matrix_can_multiply(a, b)) return false;

    

    return true;
}

bool matrix_is_in_bounds(struct Matrix *m, int x, int y) {
    if (x < 0 || x > m->c) return false;
    if (y < 0 || y > m->r) return false;
    return true;
}

bool matrix_get(struct Matrix *m, int x, int y, float *r) {

    if (!matrix_is_in_bounds(m, x, y)) return false;

    *r = m->m[x + y * m->c];

    return true;
}

bool matrix_set(struct Matrix *m, int x, int y, float v) {

    if (!matrix_is_in_bounds(m, x, y)) return false;

    m->m[x + y * m->c] = v;

    return true;
}

bool matrix_from_array(struct Matrix *m, int c, int r, float *arr) {

    if (!matrix_init(m, c, r)) return false;    

    for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++) {
            matrix_set(m, i, j, arr[i + j * c]);
        }
    }

    return true;
}

void matrix_fill_by_array(struct Matrix *m, float *arr) {

    for (int i = 0; i < m->c; i++) {
        for (int j = 0; j < m->r; j++) {
            matrix_set(m, i, j, arr[i + j * m->c]);
        }
    }
}

void matrix_clear(struct Matrix *m) {
    free(m->m);
    m->c = 0;
    m->r = 0;
}