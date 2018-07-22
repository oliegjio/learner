#include "matrix.h"

bool matrix(struct Matrix *m, int r, int c) {

    float *mem = (float*) malloc(r * c * sizeof(float));

    if (mem == NULL) {

        m->c = 0;
        m->r = 0;
        m->m = NULL;
        
        return false;
    }

    m->c = c;
    m->r = r;
    m->m = mem;

    matrix_fill_by_float(m, 0);

    return true;
}

void matrix_fill_by_float(struct Matrix *m, int v) {
    for (int i = 0; i < m->r; i++) {
        for (int j = 0; j < m->c; j++) {
            matrix_set(m, i, j, v);
        }
    }
}

bool matrix_is_dimensions_equal(struct Matrix *a, struct Matrix *b) {
    if (a->c != b->c) return false;
    if (a->r != b->r) return false;
    return true;
}

bool matrix_add(struct Matrix *a, struct Matrix *b, struct Matrix *r) {
    
    if (!matrix_is_dimensions_equal(a, b)) return false;

    if (!matrix(r, a->r, a->c)) return false;

    float a_value, b_value;

    for (int i = 0; i < a->r; i++) {
        for (int j = 0; j < a->c; j++) {

            matrix_get(a, i, j, &a_value);
            matrix_get(b, i, j, &b_value);

            matrix_set(r, i, j, a_value + b_value);
        }
    }

    return true;
}

bool matrix_substract(struct Matrix *a, struct Matrix *b, struct Matrix *r) {
    
    if (!matrix_is_dimensions_equal(a, b)) return false;

    if (!matrix(r, a->r, a->c)) return false;

    float a_value, b_value;

    for (int i = 0; i < a->r; i++) {
        for (int j = 0; j < a->c; j++) {

            matrix_get(a, i, j, &a_value);
            matrix_get(b, i, j, &b_value);

            matrix_set(r, i, j, a_value - b_value);
        }
    }

    return true;
}

bool matrix_transpose(struct Matrix *m, struct Matrix *r) {

    if (!matrix(r, m->c, m->r)) return false;

    float value;

    for (int i = 0; i < m->r; i++) {
        for (int j = 0; j < m->c; j++) {
            matrix_get(m, i, j, &value);
            matrix_set(r, j, i, value);
        }
    }

    return true;
}

bool matrix_can_multiply(struct Matrix *a, struct Matrix *b) {
    if (a->c != b->r) return false;
    return true;
}

bool matrix_select_column(struct Matrix *m, int n, float *v) {
    
    if (n > m->c) return false;
    if (n < 0) return false;

    float value;

    for (int i = 0; i < m->r; i++) {
        matrix_get(m, n, i, &value);
        v[i] = value;
    }

    return true;
}

bool matrix_select_row(struct Matrix *m, int n, float *v) {

    if (n > m->r) return false;
    if (n < 0) return false;

    float value;

    for (int i = 0; i < m->c; i++) {
        matrix_get(m, i, n, &value);
        v[i] = value;
    }

    return true;
}

void matrix_scalar_multiply(struct Matrix *m, float n) {

    float value;    

    for (int i = 0; i < m->r; i++) {
        for (int j = 0; j < m->c; j++) {
            matrix_get(m, i, j, &value);
            matrix_set(m, i, j, value * n);
        }
    }
}

bool matrix_multiply(struct Matrix *a, struct Matrix *b, struct Matrix *r) {

    if (!matrix_can_multiply(a, b)) return false;

    if (!matrix(r, a->r, b->c)) return false;

    float a_value, b_value, sum;

    for (int i = 0; i < r->r; i++) {
        for (int j = 0; j < r->c; j++) {
            sum = 0.0f;
            for (int k = 0; k < a->c; k++) {
                matrix_get(a, i, k, &a_value);
                matrix_get(b, k, j, &b_value);
                sum += a_value * b_value;
            }
            matrix_set(r, i, j, sum);
        }
    }

    return true;
}

bool matrix_is_in_bounds(struct Matrix *m, int r, int c) {
    if (r < 0 || r > m->r) return false;
    if (c < 0 || c > m->c) return false;
    return true;
}

bool matrix_get(struct Matrix *m, int r, int c, float *v) {

    if (!matrix_is_in_bounds(m, r, c)) return false;

    *v = m->m[c + r * m->c];

    return true;
}

bool matrix_set(struct Matrix *m, int r, int c, float v) {

    if (!matrix_is_in_bounds(m, r, c)) return false;

    m->m[c + r * m->c] = v;

    return true;
}

bool matrix_from_array(struct Matrix *m, int r, int c, float *arr) {

    if (!matrix(m, r, c)) return false;    

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            matrix_set(m, i, j, arr[j + i * c]);
        }
    }

    return true;
}

void matrix_fill_by_array(struct Matrix *m, float *arr) {

    for (int i = 0; i < m->r; i++) {
        for (int j = 0; j < m->c; j++) {
            matrix_set(m, i, j, arr[j + i * m->c]);
        }
    }
}

bool matrix_map(struct Matrix *m, struct Matrix *r, float (*f)(float)) {
    
    if (!matrix(r, m->r, m->c)) return false;

    float value;

    for (int i = 0; i < m->r; i++) {
        for (int j = 0; j < m->c; j++) {
            matrix_get(m, i, j, &value);
            matrix_set(r, i, j, (*f)(value));
        }
    }

    return true;
}

void matrix_clear(struct Matrix *m) {
    free(m->m);
    m->m = NULL;
    m->c = 0;
    m->r = 0;
}

void matrix_print(struct Matrix *m) {
    
    float value;

    for (int i = 0; i < m->r; i++) {
        for (int j = 0; j < m->c; j++) {
            matrix_get(m, i, j, &value);
            printf("%f  ", value);
        }
        printf("\n");
    }
}