/*
ВАРІАНТ 9: знаходить максимальний елемент матрицi;
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <Windows.h>
#include <unistd.h>
#include <mpi.h>

#define _M_ROWS 6720
#define _M_COLUMNS 5040
//#define _DEBUG
#define _CLOCK

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
			printf("% 5.2lf", arr[i * r + j]);
		printf("\n");
	}
}

void printArr(double *arr, int c, int r, int size)
{
	int i, j;
	for (i = 0; (i < c) && (i * r) < size; ++i)
	{
		for (j = 0; (j < r) && (i * r + j) < size; ++j)
			printf("% 5.2lf", arr[i * r + j]);
		printf("\n");
	}
}

void clrMatrix(double *arr, int size)
{
	int i;
	for (i = 0; i < size; ++i)
		arr[i] = 0;
}

double findMin(double *arr, int size)
{
	int i;
	double min = arr[0];
	for (i = 1; i < size; ++i)
		if (arr[i] < min)
			min = arr[i];
	return min;
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

	double *arr_orig, *arr_recv = (double *)malloc(M_SIZE_LOC * sizeof(double)); ///PLEASE HELP ME
	double min_loc, min_glob;

	//arr_orig = (double *)malloc(M_COLUMNS * M_ROWS * sizeof(double));
	//clrMatrix(arr_orig, M_COLUMNS * M_ROWS);
	//clrMatrix(arr_recv, M_COLUMNS * M_ROWS);

	if (rank == 0)
	{
		arr_orig = (double *)malloc(M_SIZE_GLOB * sizeof(double));
		genMatrix(arr_orig, M_ROWS, M_COLUMNS);

#ifdef _DEBUG
		printMatrix(arr_orig, M_ROWS, M_COLUMNS);
#endif // _DEBUG
	}


#ifdef _CLOCK
	double starttime;
	if (rank == 0)
		starttime = MPI_Wtime();
#endif // _CLOCK
	

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Scatter(arr_orig, M_SIZE_LOC, MPI_DOUBLE,
				arr_recv, M_SIZE_LOC, MPI_DOUBLE,
				0, MPI_COMM_WORLD);
	
	
	min_loc = findMin(arr_recv, M_SIZE_LOC);

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Reduce(&min_loc, &min_glob, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);

	if (rank == 0) 
		printf("\nMIN = %lf\n\n", min_glob);

#ifdef _DEBUG
	sleep(rank * 1);
	printf("\n\nRank %d: \n", rank);
	printArr(arr_recv, M_ROWS, M_COLUMNS, M_SIZE_LOC);
	sleep(1);
	MPI_Barrier(MPI_COMM_WORLD);
#endif // _DEBUG

	if (rank == 0)
		free(arr_orig);
	free(arr_recv);

#ifdef _CLOCK
	if (rank == 0)
		printf("\nProgram runed on %d processes ended in %.5lf seconds\n\n", size, MPI_Wtime() - starttime);
#endif // _CLOCK

	MPI_Finalize();
	return 0;
}