#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <omp.h>

#define PRINT_PROCESS
#define PARALLEL

#define UNIQ_VAR_IMPL_2(lineone, prefix) _uniq_var_##lineone##prefix
#define UNIQ_VAR_IMPL(lineone, prefix) UNIQ_VAR_IMPL_2(lineone, prefix)
#define UNIQ_VAR(prefix) UNIQ_VAR_IMPL(__LINE__, prefix)

#define CLOCK(func)                                                                \
{                                                                                  \
    double UNIQ_VAR(_start) = omp_get_wtime();                                     \
    func;                                                                          \
    double UNIQ_VAR(_end) = omp_get_wtime();                                       \
    printf("Час виконання %s: %f с\n", #func, UNIQ_VAR(_end) - UNIQ_VAR(_start));  \
}

#define CLOCK_MSG(func, msg)                                                               \
{                                                                                          \
    double UNIQ_VAR(_start) = omp_get_wtime();                                             \
    func;                                                                                  \
    double UNIQ_VAR(_end) = omp_get_wtime();                                               \
    printf("Час виконання %s %s: %f с\n", #func, msg, UNIQ_VAR(_end) - UNIQ_VAR(_start));  \
}

#define MTRX_PRINT(A, m_size)                       \
{                                                   \
    printf("Матриця " #A ":\n");                    \
    printMatrix(A, (m_size), (m_size));             \
}


void genMatrix(int** arr, int c, int r)
{
#ifdef PARALLEL
#pragma omp parallel
    srand(rand());
#pragma omp for
#endif
    for (int i = 0; i < c; ++i)
        for (int j = 0; j < r; ++j)
            arr[i][j] = rand() % 10;
}                                      

void clrMatrix(int** arr, int c, int r)
{
#ifdef PARALLEL
#pragma omp parallel for
#endif
    for (int i = 0; i < c; ++i)
        for (int j = 0; j < r; ++j)
            arr[i][j] = 0;
}

void printMatrix(int** arr, int c, int r)
{
    for (int i = 0; i < c; ++i) {
        for (int j = 0; j < r; ++j)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}

void mltpMatrix(int** A, int** B, int** X, int size)
{
    for (int i = 0; i < size; i++)
        for (int k = 0; k < size; k++)
            for (int j = 0; j < size; j++)
                X[i][j] += A[i][k] * B[k][j];
}

void mltpMatrix_par(int** A, int** B, int** X, int size)
{
#pragma omp parallel for schedule(auto)
    for (int i = 0; i < size; i++)
        for (int k = 0; k < size; k++)
            for (int j = 0; j < size; j++)
                X[i][j] += A[i][k] * B[k][j];
}

void mltpMatrix_red(int** A, int** B, int** X, int size)
{
    double sum = 0;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            sum = 0;
#pragma omp parallel for reduction(+:sum)
            for (int k = 0; k < size; k++)
                sum += A[i][k] * B[k][j];
            X[i][j] = sum;
        }
}

int main()
{
    SetConsoleOutputCP(65001);
    int m_size;
    printf("Введіть розмір матриці: ");
    scanf("%d", &m_size);

    int *A[m_size], *B[m_size], *X[m_size];

    for (int i = 0; i < m_size; ++i)
    {
        A[i] = (int *)malloc(m_size * sizeof(int));
        B[i] = (int *)malloc(m_size * sizeof(int));
        X[i] = (int *)malloc(m_size * sizeof(int));
    }

    genMatrix(A, m_size, m_size);//CLOCK(genMatrix(A, m_size, m_size))
    genMatrix(B, m_size, m_size);

#ifdef PRINT_PROCESS
    MTRX_PRINT(A, m_size);
    printf("\n");
    MTRX_PRINT(B, m_size);
    printf("\n");
#endif

    clrMatrix(X, m_size, m_size);
    CLOCK_MSG(mltpMatrix(A, B, X, m_size), "у послідовному режимі");     // Послідовна реалізація
#ifdef PRINT_PROCESS
    MTRX_PRINT(X, m_size);
    printf("\n");
#endif  // PRINT_PROCESS

    clrMatrix(X, m_size, m_size);
    CLOCK_MSG(mltpMatrix_par(A, B, X, m_size), "у паралельному режимі"); // Паралельна реалізація
#ifdef PRINT_PROCESS
    MTRX_PRINT(X, m_size);
    printf("\n");
#endif // PRINT_PROCESS

    return 0;
}
