#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

int main()
{
    printf("ALI has started\n");

    MPI_Init(NULL, NULL);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    printf("Core %d\n", world_rank);

    MPI_Finalize();

    printf("ALI has finished\n");
    return 0;
}