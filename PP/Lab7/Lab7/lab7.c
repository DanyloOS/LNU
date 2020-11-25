/*
9. master = 0, передаЇ в 3 розмiр масиву (long double), 2 передаЇ iмС¤ процесора, 1 Ц
вектор float [0, 0.05 ..10]
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


//#define DEBUG
#define rank_master 0
#define f0to3_arrsize 30
#define f1to0_farr 100
#define f2to0_procname 200
#define f3to0_ldarr 300

static const int MSG_COUNT = 3;

#ifdef DEBUG													
#define PRINT_INFO(my_rank)	printf("Hi. I am %d and i`m on %d line!\n", my_rank, __LINE__);
#else
#define PRINT_INFO(my_rank)
#endif	

#ifdef DEBUG													
#define PRINT_TAG(my_tag)	printf("statustag = %d\n", my_tag);
#else
#define PRINT_TAG(my_tag)
#endif	



int main(int argc, char *argv[])
{
	int my_rank, num_procs, i;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

	PRINT_INFO(my_rank)
		if (num_procs != 4)
		{
			if (my_rank == rank_master)
				printf("EROR! Bad arg. Program shoudl start with '-n 4' instead of '-n %d'\n"
					"Aborting.\n", num_procs);

			MPI_Barrier(MPI_COMM_WORLD);
			MPI_Abort(MPI_COMM_WORLD, 0);
			MPI_Finalize();
			return -1;
		}


	switch (my_rank)
	{
	case 0: // master
	{
		PRINT_INFO(my_rank)
		float *f_arr;
		long double *ld_arr;
		char *proc_name;
		int f_arr_size, name_len, ld_arr_size = 5, msgs_count = MSG_COUNT;
		MPI_Status status;
		MPI_Send(&ld_arr_size, 1, MPI_INT, 3, f0to3_arrsize, MPI_COMM_WORLD);

		while (msgs_count)
		{
			MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			PRINT_TAG(status.MPI_TAG)
			switch (status.MPI_TAG)
			{
			case f1to0_farr:
			{
				MPI_Get_count(&status, MPI_FLOAT, &f_arr_size);
				f_arr = (float *)malloc(f_arr_size * sizeof(float));
				MPI_Recv(f_arr, f_arr_size, MPI_FLOAT, 1, f1to0_farr, MPI_COMM_WORLD, &status);
				printf("f_arr: \n");
				for (i = 0; i < f_arr_size; ++i)
					printf("\t%f", f_arr[i]);
				printf("\n");
				//free(f_arr); //////////
			} break;
			case f2to0_procname:
			{
				MPI_Get_count(&status, MPI_CHAR, &name_len);
				proc_name = (char *)malloc(name_len * sizeof(char));
				MPI_Recv(proc_name, name_len, MPI_CHAR, 2, f2to0_procname, MPI_COMM_WORLD, &status);
				printf("proc_name = %s\n", proc_name);
				//free(proc_name); //////////
			} break;
			case f3to0_ldarr:
			{
				ld_arr = (long double *)malloc(ld_arr_size);
				MPI_Recv(ld_arr, ld_arr_size, MPI_LONG_DOUBLE, 3, f3to0_ldarr, MPI_COMM_WORLD, &status);
				for (i = 0; i < ld_arr_size; ++i)
					printf("ld_arr[%d] = %Lf\n", i, ld_arr[i]);
				//free(ld_arr); //////////
			} break;
			}

			--msgs_count;
		}

#ifdef DEBUG		
		PRINT_INFO(my_rank)
			MPI_Barrier(MPI_COMM_WORLD);
		PRINT_INFO(my_rank)
#endif
	} break;

	case 1:
	{
		PRINT_INFO(my_rank)
		float range_a, range_b, range_step;
		range_a = 0;
		range_b = 10;
		range_step = 0.05;
		int f_arr_size = (range_b - range_a) / range_step + 1;


		float *f_arr = (float *)malloc(f_arr_size * sizeof(float));

		for (i = 0; i < f_arr_size; ++i)
			f_arr[i] = range_step * i;

		MPI_Send(f_arr, f_arr_size, MPI_FLOAT, rank_master, f1to0_farr, MPI_COMM_WORLD);

#ifdef DEBUG		
		PRINT_INFO(my_rank)
			MPI_Barrier(MPI_COMM_WORLD);
		PRINT_INFO(my_rank)
#endif
			//free(f_arr);
	} break;

	case 2:
	{
		PRINT_INFO(my_rank)
		char proc_name[MPI_MAX_PROCESSOR_NAME];
		int name_len;
		MPI_Get_processor_name(proc_name, &name_len);
		MPI_Send(proc_name, name_len, MPI_CHAR, rank_master, f2to0_procname, MPI_COMM_WORLD);

#ifdef DEBUG		
		PRINT_INFO(my_rank)
			MPI_Barrier(MPI_COMM_WORLD);
		PRINT_INFO(my_rank)
#endif

	} break;

	case 3:
	{
		//srand(time(NULL));
		PRINT_INFO(my_rank)
		int arr_size;
		MPI_Status status;
		MPI_Recv(&arr_size, 1, MPI_INT, rank_master, f0to3_arrsize, MPI_COMM_WORLD, &status);
		PRINT_INFO(my_rank)
		long double *arr = (long double *)malloc(arr_size * sizeof(long double));

		for (i = 0; i < arr_size; ++i)
			arr[i] = (rand() % 10 + 1) * ((double)rand() / RAND_MAX);
		MPI_Send(arr, arr_size, MPI_LONG_DOUBLE, rank_master, f3to0_ldarr, MPI_COMM_WORLD);

#ifdef DEBUG		
		PRINT_INFO(my_rank)
			MPI_Barrier(MPI_COMM_WORLD);
		PRINT_INFO(my_rank)
#endif
			//free(arr);
	}
	} //switch


	MPI_Barrier(MPI_COMM_WORLD);
	if (my_rank == 0)
		printf("Program finished!\n");
	MPI_Finalize();
	return 0;
}
