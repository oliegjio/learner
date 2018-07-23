#include "matrix.h"

bool matrix(struct Matrix *m, int r, int c) {

    float *mem = (float*) calloc(r * c, sizeof(float));

    if (mem == NULL) {

        m->c = 0;
        m->r = 0;
        m->m = NULL;
        
        return false;
    }

    m->c = c;
    m->r = r;
    m->m = mem;

    return true;
}

void matrix_fill_by_float(struct Matrix *m, int v) {
    for (int i = 0; i < m->r; i++) {
        for (int j = 0; j < m->c; j++) {
            m->m[j + i * m->c] = v;
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

    for (int i = 0; i < a->r; i++) {
        for (int j = 0; j < a->c; j++) {
            r->m[j + i * r->c] = a->m[j + i * a->c] + b->m[j + i * b->c];
        }
    }

    return true;
}

bool matrix_subtract(struct Matrix *a, struct Matrix *b, struct Matrix *r) {
    
    if (!matrix_is_dimensions_equal(a, b)) return false;

    if (!matrix(r, a->r, a->c)) return false;

    for (int i = 0; i < a->r; i++) {
        for (int j = 0; j < a->c; j++) {
            r->m[j + i * r->c] = a->m[j + i * a->c] - b->m[j + i * b->c];
        }
    }

    return true;
}

bool matrix_transpose(struct Matrix *m, struct Matrix *r) {

    if (!matrix(r, m->c, m->r)) return false;

    for (int i = 0; i < m->r; i++) {
        for (int j = 0; j < m->c; j++) {
            r->m[i + j * r->c] = m->m[j + i * m->c];
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

    for (int i = 0; i < m->r; i++) {
        v[i] = m->m[n + i * m->c];
    }

    return true;
}

bool matrix_select_row(struct Matrix *m, int n, float *v) {

    if (n > m->r) return false;
    if (n < 0) return false;

    for (int i = 0; i < m->c; i++) {
        v[i] = m->m[i + n * m->c];
    }

    return true;
}

bool matrix_scalar_multiply(struct Matrix *m, struct Matrix *r, float n) {

    if (!matrix(r, m->r, m->c)) return false;

    for (int i = 0; i < m->r; i++) {
        for (int j = 0; j < m->c; j++) {
            r->m[j + i * m->c] = m->m[j + i * m->c] * n;
        }
    }

    return true;
}

bool matrix_multiply(struct Matrix *a, struct Matrix *b, struct Matrix *r) {

    if (!matrix_can_multiply(a, b)) return false;

    if (!matrix(r, a->r, b->c)) return false;

    for (int i = 0; i < r->r; i++) {
        for (int j = 0; j < r->c; j++) {
            for (int k = 0; k < a->c; k++) {
                r->m[j + i * r->c] += a->m[k + i * a->c] * b->m[j + k * b->c];
            }
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
            m->m[j + i * m->c] = arr[j + i * m->c];
        }
    }

    return true;
}

bool matrix_map(struct Matrix *m, struct Matrix *r, float (*f)(float)) {
    
    if (!matrix(r, m->r, m->c)) return false;

    for (int i = 0; i < m->r; i++) {
        for (int j = 0; j < m->c; j++) {
            r->m[j + i * r->c] = (*f)(m->m[j + i * m->c]);
        }
    }

    return true;
}

bool matrix_equal(struct Matrix *a, struct Matrix *b) {
    
    if (!matrix_is_dimensions_equal(a, b)) return false;

    for (int i = 0; i < a->r; i++) {
        for (int j = 0; j < a->c; j++) {
            if (a->m[j + i * a->c] != b->m[j + i * b->c]) return false;
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

int matrix_columns(struct Matrix *m) {
    return m->c;
}

int matrix_rows(struct Matrix *m) {
    return m->r;
}

bool matrix_like(struct Matrix *a, struct Matrix *b) {

    if (matrix(b, a->r, a->c)) return true;
    else return false;
}

bool matrix_resize(struct Matrix *m, int r, int c) {

    matrix_clear(m);

    if (matrix(m, r, c)) return true;
    else return false;
}

void matrix_print(struct Matrix *m) {

    for (int i = 0; i < m->r; i++) {
        for (int j = 0; j < m->c; j++) {
            printf("%f  ", m->m[j + i * m->c]);
        }
        printf("\n");
    }
}

void matrix_randomize(struct Matrix *m, float from, float to) {

    for (int i = 0; i < m->r; i++) {
        for (int j = 0; j < m->c; j++) {
            m->m[j + i * m->c] = rand() * to + from;
        }
    }
}