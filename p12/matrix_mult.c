#include "csapp.h"

void matrix_mult(int** a, int** b, int** c, size_t n);
void matrix_mult_tr(int** a, int** b, int** c, size_t n);
void print(int** a, size_t n);
void* column_computation(void* vargp);
void validate(int** a, int** b, size_t n);

struct thread_args {
    int **a;
    int **b;
    int **c;
    int column;
    int n;
};

int main(int argc, char** argv)
{
    srand(time(NULL));
    const int n = 5;
    const int divider = 9999;

    int** a = Malloc(n * sizeof(int *));
    for (size_t i = 0; i < n; ++i) {
        a[i] = Malloc(n * sizeof(int));
        for (size_t k = 0; k < n; ++k) {
            a[i][k] = rand() % divider;
        }
    }
    int** b = Malloc(n * sizeof(int *));
    for (size_t i = 0; i < n; ++i) {
        b[i] = Malloc(n * sizeof(int));
        for (size_t k = 0; k < n; ++k) {
            b[i][k] = rand() % divider;
        }
    }
    int** c = Malloc(n * sizeof(int *));
    for (size_t i = 0; i < n; ++i) {
        c[i] = Malloc(n * sizeof(int));
    }
    int** d = Malloc(n * sizeof(int *));
    for (size_t i = 0; i < n; ++i) {
        d[i] = Malloc(n * sizeof(int));
    }
    matrix_mult(a, b, c, n);
    print(c, n);
    printf("----------------------\n");
    matrix_mult_tr(a, b, d, n);
    print(d, n);
    printf("----------------------\n");
    validate(c, d, n);
    for (size_t i = 0; i < n; ++i) {
        Free(a[i]);
        Free(b[i]);
        Free(c[i]);
        Free(d[i]);
    }
    Free(a);
    Free(b);
    Free(c);
    Free(d);
}

void validate(int** a, int** b, size_t n)
{
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (a[i][j] != b[i][j]) {
                printf("FAILED at (%zu, %zu) : {%d vs %d }\n", i, j, a[i][j], b[i][j]);
                return ;
            }
        }
    }
    printf("PASS\n");
}

void matrix_mult(int** a, int** b, int** c, size_t n)
{
    for (size_t j = 0; j < n; ++j) {
        for (size_t i = 0; i < n; ++i) {
            c[i][j] = 0;
            for (size_t k = 0; k < n; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void* column_computation(void* vargp) 
{
    struct thread_args* args = vargp;
    for (size_t i = 0; i < args->n; ++i) {
        args->c[i][args->column] = 0;
        for (size_t k = 0; k < args->n; ++k) {
            args->c[i][args->column] += args->a[i][k] * args->b[k][args->column];
        }
    }
    Free(args);
}

void matrix_mult_tr(int** a, int** b, int** c, size_t n)
{
    pthread_t* tids = Malloc(sizeof(pthread_t) * n);
    for (size_t i = 0; i < n; ++i) {
        struct thread_args* vargp = Malloc(sizeof(struct thread_args));
        vargp->a = a;
        vargp->b = b;
        vargp->c = c;
        vargp->column = i;
        vargp->n = n;
        Pthread_create(&tids[i], NULL, column_computation, vargp); 
    }
    for (size_t i = 0; i < n; ++i) {
        Pthread_join(tids[i], NULL);
    }
    Free(tids);
}

void print(int** a, size_t n)
{
    for (size_t i = 0; i < n; ++i) {
        printf("[  ");
        for (size_t j = 0; j < n; ++j) {
            printf("%09d  ", a[i][j]);
        }
        printf("]\n");
    }
}
