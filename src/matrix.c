#include "matrix.h"

#include <string.h>
#include <stdio.h>
#include <math.h>

/* #define MATRIX_MULTITHREAD */

#ifdef MATRIX_MULTITHREAD
#include  <pthread.h>
#define MATRIX_MAX_THREADS 4
#define MATRIX_THREAD_PART 4
#endif

typedef struct Matrix {
    size_t r, c;
    float *d;
} Matrix;

typedef struct WorkerData {
    Matrix *a;
    Matrix *b;
    Matrix *r;
    size_t threads;
} WorkerData;

void *matrix_multiplication_worker(void *data);

Matrix *matrix_create(size_t r, size_t c) {

    Matrix *m = (Matrix*) malloc(sizeof(Matrix));
    if (m == NULL) return NULL;

    float *d = (float*) calloc(r * c, sizeof(float));
    if (d == NULL) {
        free(m);
        return NULL;
    }

    m->c = c;
    m->r = r;
    m->d = d;

    return m;
}

void matrix_destroy(Matrix *m) {
    free(m->d);
    free(m);
}

Matrix *matrix_scalar_add(const Matrix *m, float n) {

    Matrix *r = matrix_create(m->r, m->c);
    if (r == NULL) return NULL;

    for (size_t i = 0; i < m->r * m->c; i++) {
        r->d[i] = m->d[i] + n;
    }

    return r;
}

void matrix_scalar_add_l(Matrix *m, float n) {

    for (size_t i = 0; i < m->r * m->c; i++) {
        m->d[i] += n;
    }
}

Matrix *matrix_scalar_subtract(const Matrix *m, float n) {

    Matrix *r = matrix_create(m->r, m->c);
    if (r == NULL) return NULL;

    for (size_t i = 0; i < m->r * m->c; i++) {
        r->d[i] = m->d[i] - n;
    }

    return r;
}

void matrix_scalar_subtract_l(Matrix *m, float n) {

    for (size_t i = 0; i < m->r * m->c; i++) {
        m->d[i] -= n;
    }
}

Matrix *matrix_scalar_multiply(const Matrix *m, float n) {

    Matrix *r = matrix_create(m->r, m->c);
    if (r == NULL) return NULL;

    for (size_t i = 0; i < m->r * m->c; i++) {
        r->d[i] = m->d[i] * n;
    }

    return r;
}

void matrix_scalar_multiply_l(Matrix *m, float n) {

    for (size_t i = 0; i < m->r * m->c; i++) {
        m->d[i] *= n;
    }
}

Matrix *matrix_copy(const Matrix *m) {

  Matrix *r = matrix_create(m->r, m->c);
  if (r == NULL) return NULL;

  memcpy(r->d, m->d, m->r * m->c * sizeof(float));

  return r;
}

int matrix_copy_values(const Matrix *from, Matrix *to) {

  if (matrix_is_dimensions_equal(from, to) == 0) return 0;

  memcpy(to->d, from->d, to->r * to->c * sizeof(float));

  return 1;
}

float *matrix_to_array(const Matrix *m) {

    float *arr = (float*) calloc(m->r * m->c, sizeof(float));
    if (arr == NULL) return NULL;

    memcpy(arr, m->d, m->r * m->c * sizeof(float));

    return arr;
}

int matrix_is_dimensions_equal(const Matrix *a, const Matrix *b) {
    if (a->c != b->c) return 0;
    if (a->r != b->r) return 0;
    return 1;
}

Matrix *matrix_add(const Matrix *a, const Matrix *b) {

    if (matrix_is_dimensions_equal(a, b) == 0) return NULL;

    Matrix *r = matrix_create(a->r, a->c);
    if (r == NULL) return NULL;

    for (size_t i = 0; i < a->r * a->c; i++) {
        r->d[i] = a->d[i] + b->d[i];
    }

    return r;
}

int matrix_add_l(Matrix *a, const Matrix *b) {

    if (matrix_is_dimensions_equal(a, b) == 0) return 0;

    for (size_t i = 0; i < a->r * a->c; i++) {
        a->d[i] += b->d[i];
    }

    return 1;
}

Matrix *matrix_subtract(const Matrix *a, const Matrix *b) {

    if (matrix_is_dimensions_equal(a, b) == 0) return NULL;

    Matrix *r = matrix_create(a->r, a->c);
    if (r == NULL) return NULL;

    for (size_t i = 0; i < a->r * a->c; i++) {
        r->d[i] = a->d[i] - b->d[i];
    }

    return r;
}

int matrix_subtract_l(Matrix *a, const Matrix *b) {

    if (matrix_is_dimensions_equal(a, b) == 0) return 0;

    for (size_t i = 0; i < a->r * a->c; i++) {
        a->d[i] -= b->d[i];
    }

    return 1;
}

Matrix *matrix_transpose(const Matrix *m) {

    Matrix *r = matrix_create(m->c, m->r);
    if (r == NULL) return NULL;

    for (size_t i = 0; i < m->r; i++) {
        for (size_t j = 0; j < m->c; j++) {
            r->d[i + j * r->c] = m->d[j + i * m->c];
        }
    }

    return r;
}

int matrix_transpose_l(Matrix *m) {

    float *d = (float*) calloc(m->c * m->r, sizeof(float));
    if (d == NULL) return 0;

    for (size_t i = 0; i < m->r; i++) {
        for (size_t j = 0; j < m->c; j++) {
            d[i + j * m->r] = m->d[j + i * m->c];
        }
    }

    free(m->d);
    m->d = d;

    size_t t = m->r;
    m->r = m->c;
    m->c = t;

    return 1;
}

int matrix_can_multiply(const Matrix *a, const Matrix *b) {
    if (a->c != b->r) return 0;
    return 1;
}

float *matrix_column_to_array(const Matrix *m, size_t n) {

    if (n > m->c || n < 0) return NULL;

    float *arr = (float*) calloc(m->r, sizeof(float));
    if (arr == NULL) return NULL;

    for (size_t i = 0; i < m->r; i++) {
        arr[i] = m->d[n + i * m->c];
    }

    return arr;
}

float *matrix_row_to_array(const Matrix *m, size_t n) {

    if (n > m->r || n < 0) return NULL;

    float *arr = (float*) calloc(m->c, sizeof(float));
    if (arr == NULL) return NULL;

    for (size_t i = 0; i < m->c; i++) {
        arr[i] = m->d[i + n * m->c];
    }

    return arr;
}

#ifdef MATRIX_MULTITHREAD
void *matrix_multiplication_worker(void *data) {

    Matrix *a = ((WorkerData*) data)->a;
    Matrix *b = ((WorkerData*) data)->b;
    Matrix *r = ((WorkerData*) data)->r;
    size_t threads = ((WorkerData*) data)->threads;

    if (r->r < threads) pthread_exit(0);

    size_t from = threads * (size_t) ceilf(r->r / MATRIX_MAX_THREADS);
    size_t to = (threads + 1) * (size_t) ceilf(r->r / MATRIX_MAX_THREADS);

    for (size_t i = from; i < to; i++) {
        for (size_t j = 0; j < r->c; j++) {
            for (size_t k = 0; k < a->c; k++) {
                r->d[j + i * r->c] += a->d[k + i * a->c] * b->d[j + k * b->c];
            }
        }
    }

    pthread_exit(0);
}
#endif

Matrix *matrix_multiply(const Matrix *a, const Matrix *b) {

    if (matrix_can_multiply(a, b) == 0) return NULL;

    Matrix *r = matrix_create(a->r, b->c);
    if (r == NULL) return NULL;

#ifdef MATRIX_MULTITHREAD

    pthread_t threads[MATRIX_MAX_THREADS];
    WorkerData data[MATRIX_MAX_THREADS];

    for (size_t i = 0; i < MATRIX_MAX_THREADS; i++) {

        data[i].a = a;
        data[i].b = b;
        data[i].r = r;
        data[i].threads = i + 1;

        pthread_create(&threads[i], NULL, matrix_multiplication_worker, (void*) &data);
    }

    for (size_t i = 0; i < MATRIX_MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

#else

    for (size_t i = 0; i < r->r; i++) {
        for (size_t j = 0; j < r->c; j++) {
            for (size_t k = 0; k < a->c; k++) {
                r->d[j + i * r->c] += a->d[k + i * a->c] * b->d[j + k * b->c];
            }
        }
    }

#endif

    return r;
}

int matrix_multiply_l(Matrix *a, const Matrix *b) {

    if (matrix_can_multiply(a, b) == 0) return 0;

    float *d = (float*) calloc(a->r * b->c, sizeof(float));
    if (d == NULL) return 0;

    for (size_t i = 0; i < a->r; i++) {
        for (size_t j = 0; j < b->c; j++) {
            for (size_t k = 0; k < a->c; k++) {
                d[j + i * b->c] += a->d[k + i * a->c] * b->d[j + k * b->c];
            }
        }
    }

    free(a->d);
    a->d = d;

    a->c = b->c;

    return 1;
}

int matrix_multiply_r(const Matrix *a, Matrix *b) {

    if (matrix_can_multiply(a, b) == 0) return 0;

    float *d = (float*) calloc(a->r * b->c, sizeof(float));
    if (d == NULL) return 0;

    for (size_t i = 0; i < a->r; i++) {
        for (size_t j = 0; j < b->c; j++) {
            for (size_t k = 0; k < a->c; k++) {
                d[j + i * b->c] += a->d[k + i * a->c] * b->d[j + k * b->c];
            }
        }
    }

    free(b->d);
    b->d = d;

    b->r = a->r;

    return 1;
}

Matrix *matrix_hadamard_product(const Matrix *a, const Matrix *b) {

    if (matrix_is_dimensions_equal(a, b) == 0) return NULL;

    Matrix *r = matrix_create(a->r, a->c);
    if (r == NULL) return NULL;

    for (size_t i = 0; i < a->r * a->c; i++) {
        r->d[i] = a->d[i] * b->d[i];
    }

    return r;
}

int matrix_hadamard_product_l(Matrix *a, const Matrix *b) {

    if (matrix_is_dimensions_equal(a, b) == 0) return 0;

    for (size_t i = 0; i < a->r * a->c; i++) {
        a->d[i] *= b->d[i];
    }

    return 1;
}

int matrix_is_in_bounds(const Matrix *m, size_t r, size_t c) {
    if (r < 0 || r > m->r) return 0;
    if (c < 0 || c > m->c) return 0;
    return 1;
}

int matrix_get_value(const Matrix *m, size_t r, size_t c, float *v) {

    if (matrix_is_in_bounds(m, r, c) == 0) return 0;

    *v = m->d[c + r * m->c];

    return 1;
}

int matrix_set_value(Matrix *m, size_t r, size_t c, float v) {

    if (matrix_is_in_bounds(m, r, c) == 0) return 0;

    m->d[c + r * m->c] = v;

    return 1;
}

Matrix *matrix_from_array(const float *arr, size_t r, size_t c) {

    Matrix *m = matrix_create(r, c);
    if (m == NULL) return NULL;

    memcpy(m->d, arr, r * c * sizeof(float));

    return m;
}

Matrix *matrix_map(const Matrix *m, float (*f)(float)) {

    Matrix *r = matrix_create(m->r, m->c);
    if (r == NULL) return NULL;

    for (size_t i = 0; i < m->r * m->c; i++) {
        r->d[i] = (*f)(m->d[i]);
    }

    return r;
}

void matrix_map_l(Matrix *m, float (*f)(float)) {

    for (size_t i = 0; i < m->r * m->c; i++) {
        m->d[i] = (*f)(m->d[i]);
    }
}

int matrix_equal(const Matrix *a, const Matrix *b) {

    if (matrix_is_dimensions_equal(a, b) == 0) return 0;

    for (size_t i = 0; i < a->r * a->c; i++) {
        if (a->d[i] != b->d[i]) return 0;
    }

    return 1;
}

size_t matrix_columns(const Matrix *m) {
    return m->c;
}

size_t matrix_rows(const Matrix *m) {
    return m->r;
}

void matrix_print(const Matrix *m) {

    for (size_t i = 0; i < m->r; i++) {
        for (size_t j = 0; j < m->c; j++) {
            printf("%f  ", m->d[j + i * m->c]);
        }
        printf("\n");
    }
}
