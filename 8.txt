#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, x=100;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank==0 && size>1)
    {
        MPI_Send(&x,1,MPI_INT,1,0,MPI_COMM_WORLD);
        printf("Process 0 sent data\n");
    }

    if(rank==1)
    {
        MPI_Recv(&x,1,MPI_INT,0,0,MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
        printf("Process 1 received: %d\n",x);
    }

    MPI_Bcast(&x,1,MPI_INT,0,MPI_COMM_WORLD);

    printf("Process %d received broadcast: %d\n",rank,x);

    MPI_Finalize();
    return 0;
}
