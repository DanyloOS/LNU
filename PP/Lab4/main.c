#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <helper.h>
#include <math.h>



static const int M_SIZE = 500;

#define PRINT_QM(ARR, SIZE)             \
{                                       \
    printf("%s:\n", #ARR);              \
    printMatrix(ARR, (SIZE), (SIZE));   \
    printf("\n");                       \
}

void genMatrix(double** arr, int size, double min, double max)
{
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            arr[i][j] = i*size + j + 1 + rand() % 10;
}

void genMatrix_old(double** arr, int size, double min, double max)
{
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            arr[i][j] = rand() % (int)(max - min) + min;
}

void printMatrix(double** arr, int c, int r)
{
    for (int i = 0; i < c; ++i) {
        for (int j = 0; j < r; ++j)
            printf("% .2f ", arr[i][j]);
        printf("\n");
    }
}


void LU(double** A, double** L, double** U, int n)
{
    for (long i = 0; i < n; ++i)
        for (long j = 0; j < n; ++j)
        {
            double sum = 0;
            if (i <= j) {
                for (long k = 0; k < i; ++k)
                    sum += L[i][k] * U[k][j];
                U[i][j] = A[i][j] - sum;
            } else {
                for (long k = 0; k < j; ++k)
                    sum += L[i][k] * U[k][j];
                L[i][j] = (A[i][j] - sum) / U[j][j];
            }
        }
}

void LU_for(double** A, double** L, double** U, int n)
{
#pragma omp parallel for ordered
    for (long i = 0; i < n; ++i)
        for (long j = 0; j < n; ++j)
        {
            double sum = 0;
            if (i <= j) {
                for (long k = 0; k < i; ++k)
                    sum += L[i][k] * U[k][j];
                U[i][j] = A[i][j] - sum;
            } else {
                for (long k = 0; k < j; ++k)
                    sum += L[i][k] * U[k][j];
                L[i][j] = (A[i][j] - sum) / U[j][j];
//#pragma omp ordered
                {
                    L[i][j] /= U[j][j];
                }
            }
        }
}

void LU_tasks(double** A, double** L, double** U, int n)
{
#pragma omp single
    {
#pragma omp taskloop
        for (long i = 0; i < n; ++i)
            for (long j = 0; j < n; ++j)
            {
                double sum = 0;
                if (i <= j) {
                    for (long k = 0; k < i; ++k)
                        sum += L[i][k] * U[k][j];
                    U[i][j] = A[i][j] - sum;
                } else {
                    for (long k = 0; k < j; ++k)
                        sum += L[i][k] * U[k][j];
                    L[i][j] = (A[i][j] - sum) / U[j][j];
                }
            }
#pragma omp taskwait
    }
}

void mltpMatrix(double** A, double** B, double** X, int size)
{
#pragma omp parallel for
    for (int i = 0; i < size; i++)
        for (int k = 0; k < size; k++)
            for (int j = 0; j < size; j++)
                X[i][j] += A[i][k] * B[k][j];
}

void clrMatrix(double** L, double** U, double** X, int size)
{
#pragma omp parallel for
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            L[i][j] = 0;
            U[i][j] = 0;
            X[i][j] = 0;
        }
    L[i][i] = 1;
    }
}


void checkMatrik(double** A, double** B, int size)
{
#pragma omp parallel for
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (fabs(A[i][j] - B[i][j]) > 1e-9)
            {
#pragma omp critical
                {
                    printf("A[%d][%d] != B[%d][%d] : %f != %f\n", i, j, i, j, A[i][j], B[i][j]);
                }
            }
}

int main()
{
    //srand(time(NULL));
    double *A[M_SIZE], *L[M_SIZE], *U[M_SIZE], *X[M_SIZE];

    for (int i = 0; i < M_SIZE; ++i) {
        A[i] = (double *)malloc(M_SIZE * sizeof(double));
        L[i] = (double *)malloc(M_SIZE * sizeof(double));
        U[i] = (double *)malloc(M_SIZE * sizeof(double));
        X[i] = (double *)malloc(M_SIZE * sizeof(double));
    }

    genMatrix(A, M_SIZE, -10, 10);
    clrMatrix(L, U, X, M_SIZE);


    CLOCK(LU(A, L, U, M_SIZE));
    mltpMatrix(L, U, X, M_SIZE);
    checkMatrix(A, X, M_SIZE);





    clrMatrix(L, U, X, M_SIZE);
    CLOCK(LU_for(A, L, U, M_SIZE));
    mltpMatrix(L, U, X, M_SIZE);
    checkMatrix(A, X, M_SIZE);



    clrMatrix(L, U, X, M_SIZE);

    double time1_start = omp_get_wtime();
#pragma omp parallel
    {
        LU_tasks(A, L, U, M_SIZE);
    }
    double time1_end = omp_get_wtime();
    printf("Elapsed time for %s: %f\n", "LU_tasks",  time1_end - time1_start);

    mltpMatrix(L, U, X, M_SIZE);
    checkMatrix(A, X, M_SIZE);




printf("\nLU finished!\n");
    for (int i = 0; i < M_SIZE; ++i) {
        free(A[i]);
        free(L[i]);
        free(U[i]);
        free(X[i]);
    }
    return 0;
}
