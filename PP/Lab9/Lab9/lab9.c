/*
ВАРІАНТ 9: знаходить максимальний елемент матрицi;
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <time.h>

#ifdef __linux__ 
#include <unistd.h>
#define _SLEEP(s) sleep((s));
#elif _WIN64
#include <Windows.h>
#define _SLEEP(s) Sleep((s) * 1000);
#endif


#define _M_ROWS 10 //1680
#define _M_COLUMNS 8 //5040
#define DEBUG
#define _CLOCK
//#define _HEAVY_FUNC
#define __printNum_FORMAT "% 8.2lf"

void genMatrix(double *arr, int r, int c)
{
    srand(time(NULL));
    int i, j;
    for (i = 0; i < r; ++i)
        for (j = 0; j < c; ++j)
            arr[i * c + j] = ((double)rand() / RAND_MAX) * 1000.;
}

void printMatrix(double *arr, int c, int r)
{    
    int i, j;
    for (i = 0; i < c; ++i)
    {
        for (j = 0; j < r; ++j)
            printf(__printNum_FORMAT, arr[i * r + j]);
        printf("\n");
    }
}

void printArr(double *arr, int c, int r, int size)
{
    int i, j;
    for (i = 0; (i * r) < size; ++i)
    {
        for (j = 0; (j < r) && (i * r + j) < size; ++j)
            printf(__printNum_FORMAT, arr[i * r + j]);
        printf("\n");
    }
}

void clrMatrix(double *arr, int size)
{
    int i;
    for (i = 0; i < size; ++i)
        arr[i] = 0;
}

double findMax(double *arr, int size)
{
    int i;
    double max = arr[0];
    for (i = 1; i < size; ++i)
        if (arr[i] > max)
            max = arr[i];

#ifdef _HEAVY_FUNC
    struct timespec ts;
    int milliseconds = size / 1000;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#endif // _HEAVY_FUNC and __linux__

    return max;
}

int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int M_COLUMNS = _M_COLUMNS, M_ROWS = _M_ROWS;
    const int M_SIZE_GLOB = M_COLUMNS * M_ROWS;
    const int M_SIZE_LOC = M_SIZE_GLOB / size;

    double *arr_orig = NULL, *arr_recv = (double *)malloc(M_SIZE_LOC * sizeof(double));
    double max_loc, max_glob;

    if (rank == 0)
    {
        arr_orig = (double *)malloc(M_SIZE_GLOB * sizeof(double));
        genMatrix(arr_orig, M_ROWS, M_COLUMNS);

#ifdef DEBUG
        printf("Init matrix:\n");
        printMatrix(arr_orig, M_ROWS, M_COLUMNS);
#endif // DEBUG
    }


#ifdef _CLOCK
    double starttime;
    if (rank == 0)
        starttime = MPI_Wtime();
#endif // _CLOCK
    

    MPI_Scatter(arr_orig, M_SIZE_LOC, MPI_DOUBLE,
                arr_recv, M_SIZE_LOC, MPI_DOUBLE,
                0, MPI_COMM_WORLD);
    
    
    max_loc = findMax(arr_recv, M_SIZE_LOC);
#ifdef DEBUG
    _SLEEP(rank * 1);
    printf("\n\nRank %d MAX = %lf: \n", rank, max_loc);
    printArr(arr_recv, M_ROWS, M_COLUMNS, M_SIZE_LOC);
    _SLEEP(1);

    MPI_Barrier(MPI_COMM_WORLD);
#endif // DEBUG


    MPI_Reduce(&max_loc, &max_glob, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("\nMAX = %lf\n", max_glob);
#ifdef _CLOCK
        printf("Program runed on %d processes with Matrix_size %d*%d ended in %.5lf seconds\n\n", 
            size, M_COLUMNS, M_ROWS, MPI_Wtime() - starttime);
#endif // _CLOCK
    }
    

    if (rank == 0)
    {
        double master_max_glob = findMax(arr_orig, M_SIZE_GLOB);
        //printf("\nCOMPAIRING:\n"
        //    "% 16.8lf - single thread\n"
        //    "% 16.8lf - multi thread\n", master_max_glob, max_glob);
        free(arr_orig);
    }
    free(arr_recv);


    MPI_Finalize();
    return 0;
}
