/// не мiстиь процес 3;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <string.h>

#ifdef __linux__ 
#include <unistd.h>
#define _SLEEP(s) sleep((s));
#elif _WIN32
#include <Windows.h>
#define _SLEEP(s) Sleep((s) * 1000);
#endif

//#define SCAN_FROM_STDOUT
#define SIZE_OF_MESSAGE 32
#define MSG "Today is 30.11.2020."
#define RANK_TO_EXCLUDE 3 /* != 0 */

int main(int argc, char *argv[])
{
	const int rank_to_exclude = RANK_TO_EXCLUDE;
	int size, rank, newsize = -1, newrank = -1;
	char *mssg_to_send = NULL;
	MPI_Group oldgroup, group;
	MPI_Comm newcomm;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Comm_group(MPI_COMM_WORLD, &oldgroup);
	MPI_Group_excl(oldgroup, size > 3 /* bug with 1 */, &rank_to_exclude, &group);

	MPI_Comm_create(MPI_COMM_WORLD, group, &newcomm);


	if (newcomm != MPI_COMM_NULL)
	{
		mssg_to_send = (char *)malloc(SIZE_OF_MESSAGE * sizeof(char));
		MPI_Comm_size(newcomm, &newsize);
		MPI_Comm_rank(newcomm, &newrank);

		if (rank == 0)
		{
#ifndef SCAN_FROM_STDOUT
			strcpy(mssg_to_send, MSG);
#else
			scanf("%[^\n]s", mssg_to_send);
			getchar();
			printf("%s\n", mssg_to_send);
#endif //SCAN_FROM_STDOUT
		}

		MPI_Bcast(mssg_to_send, SIZE_OF_MESSAGE, MPI_CHAR, 0, newcomm);
	}

	printf("MPI_COMM_WORLD: % d from % d. New comm : % d from % d. Message = %s\n",
		rank, size, newrank, newsize, mssg_to_send);


	MPI_Group_free(&oldgroup);
	MPI_Group_free(&group);

	if (newcomm != MPI_COMM_NULL)
	{
		free(mssg_to_send);
		MPI_Comm_free(&newcomm);
	}

	MPI_Finalize();
	return 0;
}