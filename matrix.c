#include "matrix.h"

#include <string.h>

int matrix(Matrix *m, size_t r, size_t c) {

    float *mem = (float*) calloc(r * c, sizeof(float));

    if (mem == NULL) {

        m->c = 0;
        m->r = 0;
        m->m = NULL;
        
        return -1;
    }

    m->c = c;
    m->r = r;
    m->m = mem;

    return 1;
}

int matrix_scalar_add(Matrix *m, float n, Matrix *r) {

    if (matrix(r, m->r, m->c) == 0) return 0;

    for (size_t i = 0; i < m->r; i++) {
        for (size_t j = 0; j < m->c; j++) {
            r->m[j + i * m->c] = m->m[j + i * m->c] + n;
        }
    }

    return 1;
}

int matrix_scalar_subtract(Matrix *m, float n, Matrix *r) {

    if (matrix(r, m->r, m->c) == 0) return 0;

    for (size_t i = 0; i < m->r; i++) {
        for (size_t j = 0; j < m->c; j++) {
            r->m[j + i * m->c] = m->m[j + i * m->c] - n;
        }
    }

    return 1;
}

int matrix_copy_values(Matrix *from, Matrix *to) {

    if (from->c != to->c) return 0;
    if (from->r != to->r) return 0;

    for (size_t i = 0; i < to->c * to->r; i++) {
        to->m[i] = from->m[i];
    }

    return 1;
}

int matrix_to_array(Matrix *m, float *arr) {

    float *mem = (float*) calloc(m->r * m->c, sizeof(float));

    if (mem == NULL || m->m == NULL) return 0;

    memcpy(mem, m->m, m->r * m->c);
    arr = mem;

    return 1;
}

int matrix_is_dimensions_equal(Matrix *a, Matrix *b) {
    if (a->c != b->c) return 0;
    if (a->r != b->r) return 0;
    return 1;
}

int matrix_add(Matrix *a, Matrix *b, Matrix *r) {
    
    if (matrix_is_dimensions_equal(a, b) == 0) return 0;

    if (matrix(r, a->r, a->c) == 0) return 0;

    for (size_t i = 0; i < a->r; i++) {
        for (size_t j = 0; j < a->c; j++) {
            r->m[j + i * r->c] = a->m[j + i * a->c] + b->m[j + i * b->c];
        }
    }

    return 1;
}

int matrix_subtract(Matrix *a, Matrix *b, Matrix *r) {
    
    if (matrix_is_dimensions_equal(a, b) == 0) return 0;

    if (matrix(r, a->r, a->c) == 0) return 0;

    for (size_t i = 0; i < a->r; i++) {
        for (size_t j = 0; j < a->c; j++) {
            r->m[j + i * r->c] = a->m[j + i * a->c] - b->m[j + i * b->c];
        }
    }

    return 1;
}

int matrix_transpose(Matrix *m, Matrix *r) {

    if (matrix(r, m->c, m->r) == 0) return 0;

    for (size_t i = 0; i < m->r; i++) {
        for (size_t j = 0; j < m->c; j++) {
            r->m[i + j * r->c] = m->m[j + i * m->c];
        }
    }

    return 1;
}

int matrix_can_multiply(Matrix *a, Matrix *b) {
    if (a->c != b->r) return 0;
    return 1;
}

int matrix_select_column(Matrix *m, size_t n, float *v) {
    
    if (n > m->c || n < 0) return 0;

    float *mem = (float*) calloc(m->r, sizeof(float));
    if (mem == NULL) return 0;

    for (size_t i = 0; i < m->r; i++) {
        v[i] = m->m[n + i * m->c];
    }

    v = mem;

    return 1;
}

int matrix_select_row(Matrix *m, size_t n, float *v) {

    if (n > m->r || n < 0) return 0;

    float *mem = (float*) calloc(m->c, sizeof(float));
    if (mem == NULL) return 0;

    for (size_t i = 0; i < m->c; i++) {
        v[i] = m->m[i + n * m->c];
    }

    v = mem;

    return 1;
}

int matrix_scalar_multiply(Matrix *m, float n, Matrix *r) {

    if (matrix(r, m->r, m->c) < 0) return 0;

    for (size_t i = 0; i < m->r; i++) {
        for (size_t j = 0; j < m->c; j++) {
            r->m[j + i * m->c] = m->m[j + i * m->c] * n;
        }
    }

    return 1;
}

int matrix_multiply(Matrix *a, Matrix *b, Matrix *r) {

    if (matrix_can_multiply(a, b) < 0) return 0;

    if (matrix(r, a->r, b->c) < 0) return 0;

    for (size_t i = 0; i < r->r; i++) {
        for (size_t j = 0; j < r->c; j++) {
            for (size_t k = 0; k < a->c; k++) {
                r->m[j + i * r->c] += a->m[k + i * a->c] * b->m[j + k * b->c];
            }
        }
    }

    return 1;
}

int matrix_is_in_bounds(Matrix *m, size_t r, size_t c) {
    if (r < 0 || r > m->r) return 0;
    if (c < 0 || c > m->c) return 0;
    return 1;
}

int matrix_get(Matrix *m, size_t r, size_t c, float *v) {

    if (matrix_is_in_bounds(m, r, c) < 0) return 0;

    *v = m->m[c + r * m->c];

    return 1;
}

int matrix_set(Matrix *m, size_t r, size_t c, float v) {

    if (matrix_is_in_bounds(m, r, c) < 0) return 0;

    m->m[c + r * m->c] = v;

    return 1;
}

int matrix_from_array(Matrix *m, size_t r, size_t c, float *arr, size_t s) {

    if (r * c != s) return 0;
    if (matrix(m, r, c) < 0) return 0;

    for (size_t i = 0; i < r; i++) {
        for (size_t j = 0; j < c; j++) {
            m->m[j + i * m->c] = arr[j + i * m->c];
        }
    }

    return 1;
}

int matrix_map(Matrix *m, float (*f)(float), Matrix *r) {
    
    if (matrix(r, m->r, m->c) < 0) return 0;

    for (size_t i = 0; i < m->r; i++) {
        for (size_t j = 0; j < m->c; j++) {
            r->m[j + i * r->c] = (*f)(m->m[j + i * m->c]);
        }
    }

    return 1;
}

int matrix_equal(Matrix *a, Matrix *b) {
    
    if (matrix_is_dimensions_equal(a, b) < 0) return 0;

    for (size_t i = 0; i < a->r; i++) {
        for (size_t j = 0; j < a->c; j++) {
            if (a->m[j + i * a->c] != b->m[j + i * b->c]) return -1;
        }
    }

    return 1;
}

void matrix_free(Matrix *m) {
    free(m->m);
    m->m = NULL;
    m->c = 0;
    m->r = 0;
}

size_t matrix_columns(Matrix *m) {
    return m->c;
}

size_t matrix_rows(Matrix *m) {
    return m->r;
}

int matrix_resize(Matrix *m, size_t r, size_t c) {

    matrix_free(m);

    if (matrix(m, r, c)) return 1;
    else return 0;
}

void matrix_print(Matrix *m) {

    for (size_t i = 0; i < m->r; i++) {
        for (size_t j = 0; j < m->c; j++) {
            printf("%f  ", m->m[j + i * m->c]);
        }
        printf("\n");
    }
}