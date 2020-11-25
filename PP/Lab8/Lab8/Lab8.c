/*
	ВАРІАНТ 9: Метод трапецiй ∫︀2^𝑥*sin(𝑥)𝑑𝑥;
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <mpi.h>

#define _start -3.
#define _finish 3.
#define _eps 1e-7

#define DEBUG

/* Обчислення пiдiнтегральної функцiї */
inline double function(double x)
{
	return pow(2, x) * sin(x); 
}

/* Перевiрка правила Рунге */
inline bool check_Runge(double I2, double I, double epsilon)
{
	return (fabs(I2 - I) / 3.) < epsilon;
}

/* Iнтегрування методом трапецій */
double integrate(double start, double finish, double epsilon, int rank) // rank for DEBUG
{
#ifdef DEBUG
	double starttime = MPI_Wtime();
#endif // DEBUG

	int numIterations = 1;	/* Початкова кiлькiсть iтерацiй */
	double last_res = 0.;	/* Результат iнтeгрування на попередньому кроцi */
	double res = -1.;		/* Поточний результат iнтегрування */
	double h = 0.;
	int i;
	do
	{
		numIterations *= 2;
		last_res = res;
		res = 0.;
		h = (finish - start) / numIterations;

		for (i = 1; i < numIterations - 1; ++i)
			res += function(start + i * h);
		res += (function(start) + function(finish)) / 2.;
		res *= h;
	} while (!check_Runge(res, last_res, epsilon));

#ifdef DEBUG
	printf("rank %d:   numIterations = %-10d time = %-10lf\n", rank, numIterations, MPI_Wtime() - starttime);
#endif // DEBUG
	
	return res;
}

int main(int argc, char * argv[])
{
	double starttime_gl, endtime_gl;
	int size, rank, i;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	/* Введення даних в масив з 3-х змiнних.
	Вiдбувається у задачi 0.
	input[0] -- нижня межа iнтегрування
	input[1] -- верхня межа iнтегрування
	input[2] -- допустима абсолютна похибка */
	double input[3];

	if (rank == 0)
	{
		starttime_gl = MPI_Wtime();
		input[0] = _start;
		input[1] = _finish;
		input[2] = _eps;
		printf("a \t= %.4lf \nb \t= %.4lf \neps \t= %.1e\n\n", _start, _finish, _eps);
		// Зчитування 3 чисел типу double  
		// for (i = 0; i < 3; i++)
		//     scanf_s("%lf", &input[i]);
	} 
	

	/* Передача введених даних вiд задачi 0 до всiх iнших задач */
	MPI_Bcast(input, 3, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	double start	= input[0];
	double finish	= input[1];
	double epsilon	= input[2];
	double step		= (finish - start) / size;

	double res = integrate(start + rank * step, start + (rank + 1) * step, epsilon / size, rank);

	/* Передача промiжного результату iнтегрування вiд усiх задач,
	окрiм задачi 0, до задачi 0 */
	if (rank != 0)
	{
		MPI_Request send_req;
		MPI_Isend(&res, 1, MPI_DOUBLE, 0, rank, MPI_COMM_WORLD, &send_req);///////???????
		//MPI_Wait(&send_req, MPI_STATUS_IGNORE);
	}

	/* Прийом задачею 0 промiжних результатiв iнтегрування
	вiд усiх iнших задач */
#ifdef DEBUG
	MPI_Barrier(MPI_COMM_WORLD);
#endif // DEBUG

	if (rank == 0)
	{
		MPI_Request *recv_reqs = malloc((size - 1) * sizeof(MPI_Request));	//MPI_Request recv_reqs[size - 1];
		MPI_Status *status = malloc((size - 1) * sizeof(MPI_Status));		//MPI_Status status[size - 1];
		double *resall = malloc((size - 1) * sizeof(double));				//double resall[size - 1];
		for (i = 0; i < (size - 1); i++)
			MPI_Irecv(&resall[i], 1, MPI_DOUBLE, (i + 1), (i + 1), MPI_COMM_WORLD, &recv_reqs[i]);

		MPI_Waitall(size - 1, recv_reqs, status);

		for (i = 0; i < (size - 1); i++)
			res += resall[i];

		/* Виведення задачею 0 результату роботи програми */
		printf("I = %.12f\n", res);
		free(recv_reqs);
		free(status);
		free(resall);

		endtime_gl = MPI_Wtime();
		printf("Program ended in %lf seconds\n\n", endtime_gl - starttime_gl);
	}

	MPI_Finalize();
	return 0;
}